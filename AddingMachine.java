package AddingMachinePkg;

/**
 * <h1>Adding Machine</h1>
 * Adding Machine program adds and subtracts
 * a number from a running total.
 * Maintains a memory from the running
 * operations. Said memory can be cleared.
 *
 * @author      David Alejandro Umana Fleck
 * @version     2.0
 */
public class AddingMachine {
    private int total;
    private String history;


    /**
     * Initializes total to 0
     */
    public AddingMachine () {
        total = 0;  // not needed - included for clarity
        history = Integer.toString(total);
    }

    /**
     * Get Total
     * @return value of Total
     */
    public int getTotal () {
        return total;
    }

    /**
     * Get history
     * @return history string
     */
    public String getHistory(){
        return history;
    }

    /**
     * Adds value to the total
     * @param value
     */
    public void add (int value) {
        total = total + value;
        history = history + " + " + Integer.toString(value);
    }

    /**
     * Subtracts value from the total
     * @param value
     */
    public void subtract (int value) {
        total = total - value;
        history = history + " - " + Integer.toString(value);
    }

    /**
     * Prints history of operations
     * @return history of transactions
     */
    public String toString () {
        return getHistory();
    }

    /**
     * Clears the memory
     * Restarts history with current total.
     */
    public void clear() {
        history = Integer.toString(total);
    }
}