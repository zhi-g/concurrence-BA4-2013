package tcp;

import java.util.concurrent.Semaphore;

import lsr.concurrence.webserver.Configuration;

public class TasksBuffer {
	final int THREAD_POOL_SIZE = Configuration.config.getIntProperty("thread_pool_size", 2);
	final int BUFFER_SIZE = 7;
	private Task[] buffer;
	private int input = 0;
	private int output = 0;
	private Worker[] consumers;
	private Semaphore emptyBuffer;
	private Semaphore fullBuffer;

	TasksBuffer() {
		buffer = new Task[BUFFER_SIZE];
		consumers = new Worker[THREAD_POOL_SIZE];
		emptyBuffer = new Semaphore(BUFFER_SIZE);
		fullBuffer = new Semaphore(BUFFER_SIZE);
		emptyBuffer.drainPermits();
		startConsumers();
	}

	private void startConsumers() {
		for (int i = 0; i < THREAD_POOL_SIZE; ++i) {
			consumers[i] = new Worker(this);
			consumers[i].start();
		}
	}

	void addTask(Task task) {
		System.out.println("addWorker:"+ Thread.currentThread().getName());
		try {
			fullBuffer.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		buffer[input] = task;
		input = (input + 1) % BUFFER_SIZE;
		emptyBuffer.release();
	}

	Task retrieveTask() {
		System.out.println("retrieveWorker before acquire:"+ Thread.currentThread().getName());
		try {
			emptyBuffer.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("retrieveWorker after acquire:"+ Thread.currentThread().getName());
		Task task = buffer[output];
		buffer[output] = null;
		output = (output + 1)%BUFFER_SIZE;
		fullBuffer.release();
		return task;
	}
}
