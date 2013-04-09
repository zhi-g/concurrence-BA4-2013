package tcp;

import java.util.concurrent.Semaphore;

public class Worker extends Thread {
	private static boolean stayingAlive = true;
	private TasksBuffer tasks;
	private static Semaphore nbConsumers = new Semaphore(1);

	public Worker(TasksBuffer buffer) {
		tasks = buffer;
	}

	public void run() {
		while (stayingAlive) {
			try {
				nbConsumers.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			Task currentWorker = tasks.retrieveTask();
			nbConsumers.release();
			currentWorker.run();
		}
	}
	
	public static void killThreads() {
		stayingAlive = false;
	}
}