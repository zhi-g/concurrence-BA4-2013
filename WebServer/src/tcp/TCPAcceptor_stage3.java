package tcp;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

import lsr.concurrence.webserver.Configuration;

public class TCPAcceptor_stage3 extends Thread {

	public final int PORT = Configuration.config.getIntProperty("server.port", Configuration.DEFAULT_SERVER_PORT);
	private static TCPAcceptor_stage3 instance = null;
	private ServerSocket serverSocket = null;
	private TasksBuffer readTasks;
	private TasksBuffer processTasks;

	//Initializing the server with a Socket to listen to and two buffers: one to establish new connections (readTasks)
	//and the other one to store the ready-to-be-processed tasks (processTasks)
	private TCPAcceptor_stage3() {
		try {
			serverSocket = new ServerSocket(PORT);
			readTasks = new TasksBuffer();
			processTasks = new TasksBuffer();
		} catch (IOException e) {
			System.out.println("Server could not connect to port: " + PORT);
			System.exit(-1);
		}
	}

	//Method to implement the Singleton pattern
	public static TCPAcceptor_stage3 getInstance() {
		if (instance == null) {
			instance = new TCPAcceptor_stage3();
		}
		return instance;
	}
	
	//Getter to give the ReadTasks the buffer to store the ProcessTasks
	public TasksBuffer getProcessBuffer() {
		return processTasks;
	}

	// Listening to the port and adding ReadTasks to open the connection in the readTasks buffer
	// If IOException, then we stop listening to the port. That stops the server and so we kill the worker Threads.
	public void run() {
		while (true) {
			try {
				Socket clientSocket = serverSocket.accept();
				readTasks.addTask(new ReadTask(clientSocket));
			} catch (IOException e) {
				System.out.println("Server crashed listening to port: " + PORT);
				Worker.killThreads();
			}
		}
	}

}
