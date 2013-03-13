package tcp;

import java.io.IOException;
import java.net.*;
import java.io.*;

import lsr.concurrence.http.*;
import lsr.concurrence.webserver.*;

public class Worker implements Runnable {

	private Socket clientSocket;
	private HttpRequestStream httpInput;
	private HttpRequest request;
	private HttpResponse response;
	private OutputStream httpOutput;
	private StaticSite site;
	private boolean openedConnection;

	public Worker(Socket clientSocket) {
		this.clientSocket = clientSocket;
		try {
			site = new StaticSite();
		} catch (IOException e) {
			// TODO Auto-generated catch block
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
			System.err
					.println("Impossible de récupérer les flux de la socket!");
			e.printStackTrace();
		}
		
		openedConnection =  true;

		try {
			while (openedConnection) {
				try {
					request = httpInput.readRequest();
					response = site.respondTo(request);
					response.writeTo(httpOutput);
				} catch (IOException e) {
					openedConnection =  false;
				} catch (URISyntaxException e) {
					// TODO Auto-generated catch block
					System.err.println("Mauvaise URI pour accéder aux fichiers!");
					e.printStackTrace();
				}
			}
		} finally {
			try {
				httpOutput.close();
				clientSocket.close();
			} catch (Exception e) {}
		}
	}
}
