/**
 * Author: David Umana Fleck
 *
 * Contains PlotPanel class
 * 
 * @author     David Umana Fleck
 * @version    1.0
 */

import javax.swing.*;
import java.awt.*;
import java.util.Observable;
import java.util.Observer;

/**
 * PlotPanel class extends JPanel and implements Observer. Contains PlotPanel constructor,
 * as well as update and paintComponent method.
 */
public class PlotPanel extends JPanel implements Observer {
   Drawable drawable;

	/**
    * PlotPanel constructor, sets given drawable object as the active drawable object.
    */
   public PlotPanel(Drawable drawable) {
      this.drawable = drawable;
	}
   
   /**
    / Update method calls setValue method from Srawable class, adding the latest random
    * number created by source class into a linkedList. Then calls repaint to update the
    * plots.
    *
    * @param o Observable from source, and arg object.
    */
   @Override
	public void update(Observable o, Object arg) {
      drawable.setValue(((Source)o).getValue());
      repaint();
      
	}

	/**
    * paintComponent method calls draw method from Drawable class, as long as the
    * drawable object is not null.
    *
    * @param g Graphics object
    */
   public void paintComponent(Graphics g) {
      if (drawable != null)
         drawable.draw(g);    
	}

}
