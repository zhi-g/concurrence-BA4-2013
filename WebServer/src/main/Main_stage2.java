package main;

//TODO javadoc Gucevska
import tcp.TCPAcceptor_stage2;
/**
 * Calsse contenant la methode main de stage 2.
 * 
 * @author Zhivka Gucevska, Valentin Rutz
 * 
 *
 */
public class Main_stage2 {
	/**
	 * Methode main pour stage 2 qui lance le TCPAcceptor correspondant.
	 * 
	 */
	public static void main(String[] args) {
		TCPAcceptor_stage2.getInstance().start();
	}
}
