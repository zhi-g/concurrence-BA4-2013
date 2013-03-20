package tcp;

import java.util.concurrent.Semaphore;

public class TaskConsumer extends Thread {
	private static boolean stayingAlive = true;
	private TasksBuffer tasks;
	private static Semaphore nbConsumers = new Semaphore(1);

	public TaskConsumer(TasksBuffer buffer) {
		tasks = buffer;
	}

	public void run() {
		while (stayingAlive) {
			try {
				nbConsumers.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			Worker currentWorker = tasks.retrieveWorker();
			nbConsumers.release();
			currentWorker.run();
		}
	}
	
	public static void killThreads() {
		stayingAlive = false;
	}
}
