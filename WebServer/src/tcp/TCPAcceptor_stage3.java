package tcp;
//TODO javadoc Rutz
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

import lsr.concurrence.webserver.Configuration;

public class TCPAcceptor_stage3 extends Thread {

	public final int PORT = Configuration.config.getIntProperty("server.port",
			Configuration.DEFAULT_SERVER_PORT);
	private static TCPAcceptor_stage3 instance = null;
	private ServerSocket serverSocket = null;
	private TasksBuffer readTasks;
	private TasksBuffer processTasks;

	private TCPAcceptor_stage3() {
		try {
			serverSocket = new ServerSocket(PORT);
		} catch (IOException e) {
			System.out.println("Server could not connect to port: " + PORT);
		}
		readTasks = new TasksBuffer();
		processTasks = new TasksBuffer();
	}

	public static TCPAcceptor_stage3 getInstance() {
		if (instance == null) {
			instance = new TCPAcceptor_stage3();
		}
		return instance;
	}

	public TasksBuffer getProcessBuffer() {
		return processTasks;
	}

	public void run() {
		while (true) {
			try {	
				Socket clientSocket = serverSocket.accept();
//				System.out.println("After accepting: " + clientSocket.toString());
				readTasks.addTask(new ReadTask(clientSocket));
//				System.out.println("After adding ReadTask to buffer for socket: "+ clientSocket.toString());
			} catch (IOException e) {
				System.out.println("Server crashed listening to port: " + PORT);
			}
		}
	}

}
