package tcp;

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
				readTasks.addTask(new ReadTask(clientSocket));
			} catch (IOException e) {
				System.out.println("Server crashed listening to port: " + PORT);
			}
		}
	}

}
