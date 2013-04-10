package tcp;
//TODO javadoc Gucevska
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

public class TCPAcceptor_stage2 extends Thread {
	public final int PORT = Configuration.config.getIntProperty("server.port", Configuration.DEFAULT_SERVER_PORT);
	private static TCPAcceptor_stage2 instance = null;
	private ServerSocket serverSocket = null;
	private TasksBuffer tasks;
	
	private TCPAcceptor_stage2() {
		try {
			serverSocket = new ServerSocket(PORT);
		} catch (IOException e) {
			System.out.println("Server could not connect to port: " + PORT);
		}
		tasks = new TasksBuffer();
	}

	public static TCPAcceptor_stage2 getInstance() {
		if (instance == null) {
			instance = new TCPAcceptor_stage2();
		}
		return instance;
	}
	
	public void run() {
		while(true) {
			try {
				Socket clientSocket = serverSocket.accept();
				tasks.addTask(new ConnectionTask(clientSocket));
			} catch (IOException e) {
				System.out.println("Server crashed listening to port: " + PORT);
			}
		}
    }
	
	
}
