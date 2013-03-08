package main;

import tcp.TCPAcceptor;

public class Main {
	public static void main(String[] args) {
		TCPAcceptor.getInstance().start();
	}
}
