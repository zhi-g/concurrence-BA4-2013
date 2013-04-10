package tcp;

//TODO javadoc Gucevska
import java.net.Socket;

import lsr.concurrence.http.HttpRequest;

public abstract class Task implements Runnable {

	protected Socket clientSocket;
	protected HttpRequest request;
}
