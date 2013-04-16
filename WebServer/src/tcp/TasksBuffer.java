package tcp;

import java.util.concurrent.Semaphore;
import lsr.concurrence.webserver.Configuration;

/**
 * 
 * @author Zhivka Gucevska, Valentin Rutz
 * 
 */

public class TasksBuffer {
	// parametres par default
	final int THREAD_POOL_SIZE = Configuration.config.getIntProperty(
			"thread_pool_size", 4);
	final int BUFFER_SIZE = 50;

	// le buffer
	private Task[] buffer;

	// compteurs qui marquent la position de lecture/ecriture dans le buffer
	private int input = 0;
	private int output = 0;

	// l'ensemble de Workers
	private Worker[] users;

	// semaphores qui bloquent la lecture/écriture si le buffer est vide/plein
	private Semaphore emptyBuffer;
	private Semaphore fullBuffer;

	// le semaphore qui laisse un seul worker d'acceder au baffer à la fois
	private Semaphore nbUsers = new Semaphore(1);

	/**
	 * Constructor publique qui crée un buffer de taille par default
	 * (initialisée dans le fichier .properties) avec de nombre de Workers par
	 * default. Les Workers sont lancés.
	 */
	public TasksBuffer() {
		buffer = new Task[BUFFER_SIZE];
		users = new Worker[THREAD_POOL_SIZE];
		emptyBuffer = new Semaphore(BUFFER_SIZE);
		fullBuffer = new Semaphore(BUFFER_SIZE);
		emptyBuffer.drainPermits();
		startUsers();
	}

	// creation et lancement de threads Workers
	private void startUsers() {
		for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
			users[i] = new Worker(this);
			users[i].start();
		}
	}

	// Methode qui sert à ajouter un task. Cette methode est bloquante lorsque
	// le buffer est plein ou si un autre Worker et en train de écrire/ lire de
	// buffer
	void addTask(Task task) {
		try {
			fullBuffer.acquire(); // bloque si le buffer est plein
			nbUsers.acquire(); // bloque si déjà un Worker lit/écrit sur le
								// buffer
		} catch (InterruptedException e) {
			// TODO: ??
			e.printStackTrace();
		}
		//ajouter Task
		buffer[input] = task;
		input = (input + 1) % BUFFER_SIZE;
		
		nbUsers.release(); //sortie de section critique
		emptyBuffer.release(); //ajouter un permission de lecture
	}

	// Methode qui sert à retirer un task. Cette methode est bloquante lorsque
	// le buffer est vide ou si un autre Worker et en train de écrire/ lire de
	// buffer
	Task retrieveTask() {
		try {
			emptyBuffer.acquire(); // bloque si le buffer est vide
			nbUsers.acquire();// bloque si déjà un Worker lit/écrit sur le
								// buffer
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		//retirer Taks 
		Task task = buffer[output];
		buffer[output] = null;
		output = (output + 1) % BUFFER_SIZE;
		
		nbUsers.release(); //sortie de section critique
		fullBuffer.release(); //ajouter un permission d'écriture
		return task;
	}
	
	//TODO: methode qui arrete les threads proprement?
}
