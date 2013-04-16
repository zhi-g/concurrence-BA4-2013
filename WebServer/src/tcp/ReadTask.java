package tcp;

import java.io.IOException;
import java.net.Socket;

import lsr.concurrence.http.HttpRequestStream;

public class ReadTask extends Task {

	private boolean openedConnection;
	private int k = 0;
	private BlockingCounter counter;
	private HttpRequestStream httpInput;
	private TasksBuffer buffer;

	//Initializing the Task with all it needs:
	//- the socket to catch the ingoing flux to read the query of the client
	//- the TaskBuffer used to store the ProcessTasks from the connection
	//		(notice that it is a reference from the buffer created in TCPAcceptor so that every ReadTask has the same buffer)
	//- the counter to check when it is the Task's turn to send the previously processed response
	public ReadTask(Socket clientSocket) {
		super.clientSocket = clientSocket;
		buffer = TCPAcceptor_stage3.getInstance().getProcessBuffer();
		counter = new BlockingCounter();
	}

	@Override
	public void run() {
		//Initializing the boolean that carries the condition of the opening of the connection to false
		//because it isn't initialized yet and simplifies the further code
		openedConnection = false;
		try {
			//We get the input Stream and if no error occurs we say the connection has been opened
			httpInput = new HttpRequestStream(clientSocket.getInputStream());
			openedConnection = true;
		} catch (IOException e) {}

		//If we could get the Stream, we read the request from it, increment the counter that corresponds to the number of read requests
		//and add the ProcessTask to the other TaskBuffer used only to store the tasks ready to be processed by the workers
		try {
			while (openedConnection) {
				try {
					request = httpInput.readRequest();
					k++;
					buffer.addTask(new ProcessTask(request, super.clientSocket, k, counter));
				} catch (IOException e) {
					openedConnection = false;
				}
			}
		} finally {
			try {
				//if any problem with the connection occurs, we close the socket because the connection is closed by the client
				super.clientSocket.close();
			} catch (IOException e) {}
		}
	}
}
