package tcp;

public class BlockingCounter {

	private int counter;

	//Initializing the counter of the class to 1
	public BlockingCounter() {
		counter = 1;
	}

	//If it isn't the number the caller expects, it has to wait until the increment() method notify them and with the while we check the condition again.
	//Used to make the ProcessTask wait until they can actually send the response to the query.
	//We don't catch the Interrupted exception as we never call interrupt() in our code.
	synchronized void await(int number) {
		while (counter != number) {
			try {
				wait();
			} catch (InterruptedException e) {}
		}
	}

	//Increment the counter and notify all the waiting Threads (see await())
	synchronized void increment() {
		counter++;
		notifyAll();
	}

}