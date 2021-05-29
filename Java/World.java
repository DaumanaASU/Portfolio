/**
 * Author: David Umana Fleck
 *
 * World is the main file in the program.
 * 
 * @author     David Umana Fleck
 * @version    1.0
 */

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

/**
 * World extends JFrame and implements ActionListener, it contains the World constructor, and
 * the main method, as well as the actionPerformed method.
 */
public class World extends JFrame implements ActionListener {
   Source source = new Source();

	/**
    * World Constructor, it creates and initializes the different plots and a Jbutton. It also
    * creates the Frame in which the plots and the button will be displayed.
    */
   public World() {            
      SimplePlot simplePlot = new SimplePlot();
      MarkedPlot markedPlot = new MarkedPlot();
      BarPlot barPlot = new BarPlot();
      markedPlot.add(simplePlot);
      barPlot.add(markedPlot);
      
      PlotPanel plot1 = new PlotPanel(barPlot);
      PlotPanel plot2 = new PlotPanel(markedPlot);
      PlotPanel plot3 = new PlotPanel(simplePlot);
      
      source.addObserver(plot1);
      source.addObserver(plot2);
      source.addObserver(plot3);
      
      JButton button = new JButton("Run");
      button.setBackground(Color.WHITE);
      button.setSize(400, 100);
      button.addActionListener(this);
      
      
      JPanel plotPane = new JPanel();
      plotPane.setLayout(new BoxLayout(plotPane, BoxLayout.Y_AXIS));
      plotPane.setPreferredSize(new Dimension(400, 900));
      plotPane.add(plot1);
      plotPane.add(plot2);
      plotPane.add(plot3);
      JPanel buttonPane = new JPanel();
      buttonPane.setLayout(new BorderLayout(0, 0));
      buttonPane.setPreferredSize(new Dimension(400,60));
      buttonPane.add(button);
      
      add(plotPane, BorderLayout.NORTH);
      add(buttonPane, BorderLayout.PAGE_END);

	}

	/**
    * Main method from the program. Initializes World, and defines aspects of the JFrame.
    */
   public static void main(String[] args) {
      World world = new World();
      world.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      world.setSize(400, 1000);
      world.setVisible(true);
	}

   /**
    * actionPerformed method, when the button is pressed, calls source.create(), and 
    * repaint();
    * @param e button is pressed 
    */
   @Override
	public void actionPerformed(ActionEvent e) {
      source.create();
      repaint();
	}

}
