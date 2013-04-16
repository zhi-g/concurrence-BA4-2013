package tcp;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.URISyntaxException;

import lsr.concurrence.http.HttpRequestStream;
import lsr.concurrence.http.HttpResponse;
import lsr.concurrence.webserver.StaticSite;

/**
 * Classe ConnectionTask est une Task qui lit et repond aux requêtes d'un
 * client.
 * 
 * @author Zhivka Gucevska, Valentin Rutz
 * 
 */
public class ConnectionTask extends Task {

	private StaticSite site;
	// champs qui correspondent à la connection
	private HttpRequestStream httpInput;
	private HttpResponse response;
	private OutputStream httpOutput;
	private boolean openedConnection;

	/**
	 * Constructeur public de la classe ConnectionTask.
	 * 
	 * @param clientSocket
	 *            le socket dont cette ConnectionTask doit s'occuper
	 * 
	 */
	public ConnectionTask(Socket clientSocket) {
		super.clientSocket = clientSocket;
		try {
			site = new StaticSite(); // création de site qui va calculer la
										// reponse
		} catch (IOException e) {
			// TODO: comment gerer cette exception
			System.err.println("Impossible d'accéder aux fichiers du serveur");
			e.printStackTrace();
		}
	}

	// la methode qui s'occupe de lire la requête, caluculer la réponse et
	// répondre
	@Override
	public void run() {

		openedConnection = true;

		try {
			httpInput = new HttpRequestStream(clientSocket.getInputStream());
			httpOutput = clientSocket.getOutputStream();
		} catch (IOException e) {
			// problème avec la connection et on peut pas acceder au flux
			// TODO: voir si necessaire printTrace
			System.err
					.println("Impossible de récupérer les flux de la socket!");
			e.printStackTrace();
			openedConnection = false; // on a pas reussit de recuperer le flux -
										// la connection n'est pas initialisé
										// correctement
		}

		try {
			while (openedConnection) {
				try {
					// lit, calcule une réponse et repond à la requête
					request = httpInput.readRequest();
					response = site.respondTo(request);
					response.writeTo(httpOutput);
				} catch (IOException e) {
					// probleme avec la connection, elle a été probablement
					// fermée
					openedConnection = false;
				} catch (URISyntaxException e) {
					// problème avec le fichier demander
					// TODO: qu'est-ce qu'on doit envoyer comme reponse ou bien
					// pas de reponse?
					System.err
							.println("Mauvaise URI pour accéder aux fichiers!");
					e.printStackTrace();
				}
			}
		} finally {
			// fermer proprement les flux
			try {
				httpOutput.close();
				clientSocket.close();
			} catch (Exception e) {
			}
		}
	}

}
