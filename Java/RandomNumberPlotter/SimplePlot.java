/**
 * Author: David Umana Fleck
 *
 * Contains SimplePlot class
 * 
 * @author     David Umana Fleck
 * @version    1.0
 */

import java.awt.*;
import javax.swing.*;

/**
 * SimplePlot class extends Drawable. contains draw method.
 */
public class SimplePlot extends Drawable {

	/**
    * Draw method, creates a simple line plot over a light grey background.
    * 
    * @param g Graphics object
    */
   public void draw(Graphics g) {
      g.setColor(Color.lightGray);
      g.fillRect(0,0,400,300);
      for (int i = 1; i < values.size(); i++)
      {
         int x1 = (i-1) * 20;
         int y1 = values.get(i-1);
         int x2 = i * 20;
         int y2 = values.get(i);
         g.setColor(Color.BLACK);
         g.drawLine(x1, 300-y1, x2, 300-y2);
      }
	}

}
