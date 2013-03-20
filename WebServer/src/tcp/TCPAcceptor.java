package tcp;

import java.io.IOException;
import java.net.*;

import lsr.concurrence.webserver.Configuration;

/**
 * 
 * @author Zhivka Gucevska, Valentin Rutz
 * 
 * 
 *
 */

public class TCPAcceptor extends Thread {
	public final int PORT = Configuration.config.getIntProperty("server.port", Configuration.DEFAULT_SERVER_PORT);
	private static TCPAcceptor instance = null;
	private ServerSocket serverSocket = null;
	private TasksBuffer tasks;
	
	private TCPAcceptor() {
		try {
			serverSocket = new ServerSocket(PORT);
		} catch (IOException e) {
			System.out.println("Server could not connect to port: " + PORT);
		}
		tasks = new TasksBuffer();
	}

	public static TCPAcceptor getInstance() {
		if (instance == null) {
			instance = new TCPAcceptor();
		}
		return instance;
	}
	
	public void run() {
		while(true) {
			try {
				Socket clientSocket = serverSocket.accept();
				tasks.addWorker(new Worker(clientSocket));
			} catch (IOException e) {
				System.out.println("Server crashed listening to port: " + PORT);
			}
		}
    }
	
}
