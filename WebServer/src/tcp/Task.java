package tcp;

import java.net.Socket;

import lsr.concurrence.http.HttpRequest;
/**
 * Classe qui modelise le type de Tasks (tous de type Runnable) qu'on va gerer avec le TaskBuffer et les Workers
 * 
 * @author Zhivka Gucevska, Valentin Rutz
 *
 
 */
public abstract class Task implements Runnable {
	protected Socket clientSocket;
	protected HttpRequest request;
}
