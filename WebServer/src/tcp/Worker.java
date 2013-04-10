package tcp;

//TODO javadoc Rutz

public class Worker extends Thread {
	private static boolean stayingAlive = true;
	private TasksBuffer tasks;

	public Worker(TasksBuffer buffer) {
		tasks = buffer;
	}

	public void run() {
		while (stayingAlive) {
			// System.out.println("Worker "+ Thread.currentThread().toString() +
			// " waits for a permit");
			// System.out.println("Permit acquired for thread: " +
			// Thread.currentThread().getId());
			Task currentWorker = tasks.retrieveTask();
			currentWorker.run();
			// System.out.println("Task retrieved for thread: " +
			// Thread.currentThread().getId());
			currentWorker.run();
			// System.out.println("Task launched by thread: " +
			// Thread.currentThread().getId());

		}
	}

	public static void killThreads() {
		stayingAlive = false;
	}
}
