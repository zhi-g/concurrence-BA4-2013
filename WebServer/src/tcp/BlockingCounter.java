package tcp;

public class BlockingCounter {
	
	private int counter = 1;
	
	public BlockingCounter() {
		
	}
	
	synchronized void await(int number){
		while(counter != number) {
			try {
				wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	synchronized void increment(){
		counter++;
		notifyAll();
	}
	
}
