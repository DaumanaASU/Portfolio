/**
 * Author: David Umana Fleck
 *
 * Contains DecoratedPlot class
 * 
 * @author     David Umana Fleck
 * @version    1.0
 */

import java.awt.*;

/**
 * DecoratedPlot class extedns Drawable, contains add, setValue and draw methods.
 */
public abstract class DecoratedPlot extends Drawable {

	protected Drawable drawable;

	/**
    * add method, adds existing drawable object.
    */
   public void add(Drawable d) {
      this.drawable = d;
	}

	/**
    * Setter method for given integer
    */
   public void setValue(int v) {
      super.setValue(v);
	}

   /**
    * draw Method, calls the draw method from super.
    */
   @Override
   public void draw(Graphics g) {
      super.draw(g);
	}

}
