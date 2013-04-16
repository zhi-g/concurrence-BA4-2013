package tcp;

public class Worker extends Thread {
	private static boolean stayingAlive = true;
	private TasksBuffer tasks;

	public Worker(TasksBuffer buffer) {
		tasks = buffer;
	}

	public void run() {
		//While we have a connection, we retrieve a Task from the taskBuffer and we run it.
		while (stayingAlive) {
			Task currentWorker = tasks.retrieveTask();
			currentWorker.run();

		}
	}

	//Method to kill properly the worker Threads if need to be.
	public static void killThreads() {
		stayingAlive = false;
	}
}
