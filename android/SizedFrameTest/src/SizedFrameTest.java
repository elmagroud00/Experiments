import java.awt.*;
import javax.swing.*;

public class SizedFrameTest {
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				SizedFrame frame = new SizedFrame();
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		});
	}
}

class SizedFrame extends JFrame {
	public SizedFrame() {
		Toolkit kit = Toolkit.getDefaultToolkit();
		Dimension screenSize = kit.getScreenSize();
		int screenHeight = screenSize.height;
		int screenWidth = screenSize.width;
		
		setSize(screenHeight / 2, screenWidth / 2);
		setLocationByPlatform(true);
		
		Image img = kit.getImage("/Users/sijiewang/Pictures/4.gif");
		setIconImage(img);
		setTitle("SizedFrame");
	}
}
