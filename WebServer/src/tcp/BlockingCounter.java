package tcp;

//TODO javadoc Rutz
public class BlockingCounter {

	private int counter;

	public BlockingCounter() {
		counter = 1;
	}

	synchronized void await(int number) {
		while (counter != number) {
			try {
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	synchronized void increment() {
		counter++;
		notifyAll();
	}

}