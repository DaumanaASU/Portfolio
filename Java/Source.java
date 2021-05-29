/**
 * Author: David Umana Fleck
 *
 * Contains Source class
 * 
 * @author     David Umana Fleck
 * @version    1.0
 */

import java.util.Observable;

/**
 * Source class extends Observable. Contains create and getValue methods.
 */
public class Source extends Observable{

	private int value;

	/**
    * Creates a random number between 0 and 250, it also notifies observes of the change.
    */
   public void create() {
      value = (int) (Math.random() * 251);
      setChanged();
      notifyObservers();
	}

	/**
    * Getter method for the integer value
    *
    * @return the number value
    */
   public int getValue() {
		return value;
	}

}
