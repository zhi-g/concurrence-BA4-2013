package tcp;

//TODO javadoc Rutz
import java.util.concurrent.Semaphore;

public class Worker extends Thread {
    private static boolean stayingAlive = true;
    private TasksBuffer tasks;
    private  Semaphore nbConsumers;

    public Worker(TasksBuffer buffer, Semaphore semaphore) {
	tasks = buffer;
	nbConsumers = semaphore;
    }

    public void run() {
	while (stayingAlive) {
	    try {
//		System.out.println("Worker "+ Thread.currentThread().toString() + " waits for a permit");
		nbConsumers.acquire();
//		System.out.println("Permit acquired for thread: " + Thread.currentThread().getId());
		Task currentWorker = tasks.retrieveTask();
//		System.out.println("Task retrieved for thread: " + Thread.currentThread().getId());
		nbConsumers.release();
		currentWorker.run();
//		System.out.println("Task launched by thread: " + Thread.currentThread().getId());
	    } catch (InterruptedException e) {
		e.printStackTrace();
	    }

	}
    }

    public static void killThreads() {
	stayingAlive = false;
    }
}