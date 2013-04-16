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

	//Initializing the Task with all it needs:
	//- a request object to store the processed response
	//- the socket to catch the outgoing flux to send the response to the client
	//- the Static site to process the response
	//- an ID to check with the counter (the ID is sent by the ReadTask that handle the whole connection)
	//- the counter to check when it is the Task's turn to send the previously processed response
	public ProcessTask(HttpRequest request, Socket socket, int k, BlockingCounter counter) {
		super.request = request;
		super.clientSocket = socket;
		try {
			site = new StaticSite();
		} catch (IOException e) {
			e.printStackTrace();
		}
		ID = k;
		this.counter = counter;
	}

	// The run method get the outputStream, process the response to the request, wait for its turn,
	//write it on the stream and increment the counter to notify the next Task that it can send its own response
	//Handling the IOException isn't necessary because it means the connection has to be closed so we reach the end of the method
	@Override
	public void run() {
		try {
			httpOutput = clientSocket.getOutputStream();
			response = site.respondTo(request);
			counter.await(ID);
			response.writeTo(httpOutput);
			counter.increment();
		} catch (IOException e) {
		} catch (URISyntaxException e) {
			e.printStackTrace();
		}
	}

}
