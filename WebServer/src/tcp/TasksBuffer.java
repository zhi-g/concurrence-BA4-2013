package tcp;
import java.util.concurrent.Semaphore;
import lsr.concurrence.webserver.Configuration;
/**
 * 
 * @author Zhivka Gucevska, Valentin Rutz
 *
 */

public class TasksBuffer {
	final int THREAD_POOL_SIZE = Configuration.config.getIntProperty("thread_pool_size", 4);
	final int BUFFER_SIZE = 50;
	private Task[] buffer;
	private int input = 0;
	private int output = 0;
	private Worker[] users;
	private Semaphore emptyBuffer;
	private Semaphore fullBuffer;
	private Semaphore nbUsers = new Semaphore(1);

	public TasksBuffer() {
		buffer = new Task[BUFFER_SIZE];
		users = new Worker[THREAD_POOL_SIZE];
		emptyBuffer = new Semaphore(BUFFER_SIZE);
		fullBuffer = new Semaphore(BUFFER_SIZE);
		emptyBuffer.drainPermits();
		startUsers();
	}

	private void startUsers() {
		for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
			users[i] = new Worker(this);
			users[i].start();
		}
	}

	void addTask(Task task) {
		// System.out.println("addWorker:"+ Thread.currentThread().getName());
		try {
			fullBuffer.acquire();
			nbUsers.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		buffer[input] = task;
		input = (input + 1) % BUFFER_SIZE;
		nbUsers.release();
		emptyBuffer.release();
	}

	Task retrieveTask() {
		// System.out.println("retrieveWorker before acquire:"+
		// Thread.currentThread().getName());
		try {
			emptyBuffer.acquire();
			nbUsers.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		// System.out.println("retrieveWorker after acquire:"+
		// Thread.currentThread().getName());
		Task task = buffer[output];
		buffer[output] = null;
		output = (output + 1) % BUFFER_SIZE;
		nbUsers.release();
		fullBuffer.release();
		return task;
	}
}
