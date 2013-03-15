package tcp;

import java.util.concurrent.Semaphore;

public class TaskConsumer extends Thread {
	private TasksBuffer tasks;
	private static Semaphore nbConsumers;
	
	public TaskConsumer(TasksBuffer buffer) {
		tasks = buffer;
		nbConsumers = new Semaphore(1);
	}
	
	public void run() {
		try {
			nbConsumers.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		tasks.retrieveWorker().run();
		nbConsumers.release();
    }
}
