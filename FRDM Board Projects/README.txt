These are projects created using the FRDM-KL46Z board and some simple external components such as LEDs, button switches and a breadboard.


The Morse Code Generator will translate any phrase into Morse Code by flashing one of the FRDM board's built in LEDs. The phrase is written inside the code so it runs constantly without need for user input. 


The Simon Game utilizes 4 LEDs and a switch associated to each of the lights. The game will randomly select one of the lights and flash it for a short time. The user most then push the corresponding button, if he presses the correct button then the game will flash two lights in order, the first one the same as it was the first time, the second one randomly selected, this time the flash will be slightly shorter so as to speed up the game. The user most then press the two buttons in the correct order. The game continues then making a pattern which grows longer each time while also becoming quicker. 


The Stop Light uses 4 LEDs in a line and one button. The game will randomly select one of the lights as the target light it will then turn the lights on sequentially turning on one light before turning off and turning on the light next to it until it reaches the end and it starts going back, essentially racing back and forth across the four LEDs the aim of the game is to press the button when the target light is on, if one is successful the game selects a new target and starts the light starts moving faster each time until one fails.


The Get the Angle Game makes use of the 4 LEDs and the accelerometer built into the FRDM board. The game randomly selects a target angle from 7 possible angles and displays it with the use of the LEDs in the following manner:


-90° = LED 1 is on
-60° = LED 1 and 2 are on
-30° = LED 2 is on
0°   = LED 2 and 3 are on
30°  = LED 3 is on
60°  = LED 3 and 4 are on
90°  = LED 4 is on


The aim is to tilt the board to the target angle and hold it there until a timer runs out. The program gets positioning data from the accelerometer and uses it to calculate the angle every millisecond. While the timer is running the lights will be changing along with the angle. As the levels progress the timer becomes shorter giving less time to get to the desired angle each time.