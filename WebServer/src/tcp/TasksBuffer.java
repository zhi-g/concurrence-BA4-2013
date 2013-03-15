package tcp;

import java.util.concurrent.Semaphore;

public class TasksBuffer {
	final int THREAD_POOL_SIZE = 4;
	final int BUFFER_SIZE = 50;
	private Worker[] buffer;
	private int input = 0;
	private int output = 0;
	private TaskConsumer[] consumers;
	private Semaphore nbTasks;

	TasksBuffer() {
		buffer = new Worker[BUFFER_SIZE];
		consumers = new TaskConsumer[THREAD_POOL_SIZE];
		nbTasks = new Semaphore(BUFFER_SIZE);
		nbTasks.drainPermits();
		startConsumers();
	}

	private void startConsumers() {
		for (int i = 0; i < THREAD_POOL_SIZE; i++) {
			consumers[i] = new TaskConsumer(this);
			consumers[i].start();
		}
	}

	void addWorker(Worker task) {
		buffer[input] = task;
		input = (input + 1) % BUFFER_SIZE;
		nbTasks.release();
	}

	Worker retrieveWorker() {
		try {
			nbTasks.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		Worker worker = buffer[output];
		buffer[output] = null;
		output = (output + 1)%BUFFER_SIZE;
		return worker;
	}
}
