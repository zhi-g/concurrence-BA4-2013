package main;

import tcp.TCPAcceptor_stage2;

public class Main_stage2 {
	public static void main(String[] args) {
		//Just launching the TCPAcceptor of the stage 3.
		TCPAcceptor_stage2.getInstance().start();
	}
}