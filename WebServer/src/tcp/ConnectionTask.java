package tcp;

//TODO javadoc Gucevska
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.URISyntaxException;

import lsr.concurrence.http.HttpRequestStream;
import lsr.concurrence.http.HttpResponse;
import lsr.concurrence.webserver.StaticSite;
/**
 * Classe ConnectionTask est une Task qui lit et repond aux requêtes 
 * d'un client.
 * 
 * @author Zhivka Gucevska, Valentin Rutz
 *
 */
public class ConnectionTask extends Task {
	
	private StaticSite site;
	//champs qui correspondent à la connection
	private HttpRequestStream httpInput;
	private HttpResponse response;
	private OutputStream httpOutput;
	private boolean openedConnection;

	/**
	 * Constructeur public de la classe ConnectionTask.
	 * 
	 * @param clientSocket le socket dont cette ConnectionTask doit s'occuper
	 * 
	 */
	public ConnectionTask(Socket clientSocket) {
		super.clientSocket = clientSocket;
		try {
			site = new StaticSite(); 
		} catch (IOException e) {
			System.err.println("Impossible d'accéder aux fichiers du serveur");
			e.printStackTrace();
		}
	}

	@Override
	public void run() {
		openedConnection =  true;

		try {
			httpInput = new HttpRequestStream(clientSocket.getInputStream());
			httpOutput = clientSocket.getOutputStream();
		} catch (IOException e) {
			// problème avec la connection et on peut pas acceder au flux
			System.err.println("Impossible de récupérer les flux de la socket!");
			e.printStackTrace();
			openedConnection =  true;
		}

		try {
			while (openedConnection) {
				try {
					//lit, calcule une réponse et repond au requête
					request = httpInput.readRequest(); 
					response = site.respondTo(request);
					response.writeTo(httpOutput);
				} catch (IOException e) {
					//probleme avec la connection, elle a été probablement fermée
//					System.out.println("Interruption Thread: " + Thread.currentThread().getName());
					openedConnection = false;
				} catch (URISyntaxException e) {
					System.err.println("Mauvaise URI pour accéder aux fichiers!");
					e.printStackTrace();
				}
			}
		} finally {
			try {
				httpOutput.close();
				clientSocket.close();
			} catch (Exception e) {
			}
		}
	}

}
