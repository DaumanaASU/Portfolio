/**
 * Author: David Umana Fleck
 *
 * Contains abstract Drawable class
 * 
 * @author     David Umana Fleck
 * @version    1.0
 */

import java.awt.*;
import java.util.LinkedList;

/**
 * Drawable class, draws plots inside the panels.
 */
public abstract class Drawable{

	protected LinkedList<Integer> values = new LinkedList<Integer>();

	/**
    * Setter method for value, adds the given value into the values linkedList, if
    * there are already 20 elements, the head element is removed before adding a
    * new element.
    *
    * @param v integer to be added to the list.
    */
   public void setValue(int v) {
		if (values.size() < 20)
		{
			values.add(v);
		}
		else
		{
			values.remove();
			values.add(v);
		}
	}

	/**
    * draw method to be used by the child classes.
    */
   public void draw(Graphics g) {

	}

}