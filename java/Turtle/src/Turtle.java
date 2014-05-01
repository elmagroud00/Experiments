import java.io.*;
import java.util.*;

public class Turtle {
	private String name;
	private Formatter f;
	public Turtle(String name, Formatter f){
		this.name = name;
		this.f = f;
	}
	public void move(int x, int y){
		f.format("%s The Turlte is at (%d, %d)", name, x, y);
	}
	public static void main(String[] args){
		PrintStream outAlias = System.out;
		Turtle tomy = new Turtle("Tommy", new Formatter(System.out));
		Turtle terry = new Turtle("Terry", new Formatter(outAlias));
		tomy.move(0,  1);
		terry.move(4, 8);
		tomy.move(3, 4);
		terry.move(2, 5);
		tomy.move(3, 3);
		terry.move(3, 3);
	}
}
