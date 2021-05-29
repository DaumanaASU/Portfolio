/**
 * Author: David Umana Fleck
 *
 * Contains BarPlot class
 * 
 * @author     David Umana Fleck
 * @version    1.0
 */

import java.awt.*;

/**
 * BarPlot class extends DecoratedPlot, contains draw method.
 */
public class BarPlot extends DecoratedPlot {

	/**
    * Draw method creates a line plot decorated with square marks on the value
    * superimposed over a bar plot, on a white background
    *
    * @param g Graphics object
    */
   public void draw(Graphics g) {
      g.setColor(Color.WHITE);
      g.fillRect(0,0,400,300);
      for (int i = 0; i < values.size(); i++)
      {
         int x = (i) * 20;
         int y = values.get(i);
         g.setColor(Color.GRAY);
         g.fillRect(x-5,300-y,10,y);
         g.setColor(Color.BLACK);
         g.fillRect(x-5,300-y,10,10);
      }
      for (int i = 1; i < values.size(); i++)
      {
         int x1 = (i-1) * 20;
         int y1 = values.get(i-1);
         int x2 = i * 20;
         int y2 = values.get(i);
         g.setColor(Color.BLACK);
         g.drawLine(x1, 300-y1, x2, 300-y2);
      }
      super.draw(g);

	}

}
