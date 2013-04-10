package tcp;
//TODO javadoc Rutz
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

    public ProcessTask(HttpRequest request, Socket socket, int k,
	    BlockingCounter counter) {
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

    @Override
    public void run() {
	try {
	    httpOutput = clientSocket.getOutputStream();
	    counter.await(ID);
	    response = site.respondTo(request);
	    response.writeTo(httpOutput);
//	    System.out.println("Response " + ID + " sent for socket "+ clientSocket.toString() + " in thread " + Thread.currentThread().getId());
	    counter.increment();
	} catch (IOException e) {
	    
	} catch (URISyntaxException e) {
	    e.printStackTrace();
	}
    }

}
