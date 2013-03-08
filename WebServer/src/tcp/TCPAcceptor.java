package tcp;

import java.io.IOException;
import java.net.ServerSocket;

public class TCPAcceptor extends Thread {
	public final int PORT = 8080;
	private static TCPAcceptor instance = null;
	private ServerSocket serverSocket = null;
	
	private TCPAcceptor() {
		try {
			serverSocket = new ServerSocket(PORT);
		} catch (IOException e) {
			System.out.println("Server could not connect to port: " + PORT);
		}
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
				serverSocket.accept();
			} catch (IOException e) {
				System.out.println("Server crashed listening to port: " + PORT);
			}
		}
    }
	
}
