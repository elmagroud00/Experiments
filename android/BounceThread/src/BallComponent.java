import java.awt.*;
import java.util.*;
import javax.swing.*;

public class BallComponent extends JPanel {
	private ArrayList<Ball> balls = new ArrayList<Ball>();
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2 = (Graphics2D)g;
		for(Ball b : balls) {
			g2.fill(b.getShape());
		}
	}

	public void add(Ball b) {
		// TODO Auto-generated method stub
		balls.add(b);
	}
}
