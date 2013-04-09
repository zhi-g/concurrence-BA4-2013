package tcp;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.URISyntaxException;

import lsr.concurrence.http.HttpRequest;
import lsr.concurrence.http.HttpResponse;
import lsr.concurrence.webserver.StaticSite;

public class ProcessTask extends Task {

	private HttpResponse response;
	private OutputStream httpOutput;
	private StaticSite site;
	private BlockingCounter counter;
	private final int ID;

	public ProcessTask(HttpRequest request, Socket socket, int k, BlockingCounter counter) {
		super.request = request;
		super.clientSocket = socket;
		ID = k;
		this.counter = counter;
	}

	@Override
	public void run() {
		try {
			httpOutput = clientSocket.getOutputStream();
			counter.await(ID);
			response = site.respondTo(request);
			response.writeTo(httpOutput);
			counter.increment();
		} catch (IOException e) {
			// TODO: comment gérer cette exception??
			System.err.println("Impossible de récupérer les flux de la socket!");
			e.printStackTrace();
		} catch (URISyntaxException e) {
			e.printStackTrace();
		}
	}

}
