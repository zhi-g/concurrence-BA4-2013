package tcp;

//TODO javadoc Gucevska
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.URISyntaxException;

import lsr.concurrence.http.HttpRequestStream;
import lsr.concurrence.http.HttpResponse;
import lsr.concurrence.webserver.StaticSite;

public class ConnectionTask extends Task {

	private HttpRequestStream httpInput;
	private HttpResponse response;
	private OutputStream httpOutput;
	private StaticSite site;
	private boolean openedConnection;

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
		try {
			httpInput = new HttpRequestStream(clientSocket.getInputStream());
			httpOutput = clientSocket.getOutputStream();
		} catch (IOException e) {
			// TODO: comment gérer cette exception??
			System.err.println("Impossible de récupérer les flux de la socket!");
			e.printStackTrace();
		}

		openedConnection = true;

		try {
			while (openedConnection) {
				try {
					request = httpInput.readRequest();
					response = site.respondTo(request);
					response.writeTo(httpOutput);
				} catch (IOException e) {
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
