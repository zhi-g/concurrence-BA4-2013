package tcp;
//TODO javadoc Rutz
import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.Semaphore;

import lsr.concurrence.http.HttpRequestStream;

public class ReadTask extends Task {

    private boolean openedConnection;
    private int k = 0;
    private BlockingCounter counter;
    private HttpRequestStream httpInput;
    private TasksBuffer buffer;
    private static Semaphore nbProducers = new Semaphore(1);

    public ReadTask(Socket clientSocket) {
	super.clientSocket = clientSocket;
	buffer = TCPAcceptor_stage3.getInstance().getProcessBuffer();
	counter = new BlockingCounter();
    }

    @Override
    public void run() {
	openedConnection = false;
	try {
	    httpInput = new HttpRequestStream(clientSocket.getInputStream());
	    openedConnection = true;
	} catch (IOException e) {}

	try {
	    while (openedConnection) {
		try {
		    request = httpInput.readRequest();
		    k++;
		    nbProducers.acquire();
		    buffer.addTask(new ProcessTask(request, super.clientSocket,
			    k, counter));
		    nbProducers.release();
		} catch (IOException e) {
		    openedConnection = false;
		} catch (InterruptedException e) {
		    e.printStackTrace();
		}
	    }
	} finally {
	    try {
		super.clientSocket.close();
	    } catch (IOException e) {
		e.printStackTrace();
	    }
	}
    }
}
