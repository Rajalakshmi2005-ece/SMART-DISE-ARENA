# 🎲 Smart Digital Dice Arena
  A simple **2-player digital dice game** implemented using **Embedded C** on the **LPC21xx microcontroller**. This project simulates a dice game where two players take turns rolling a virtual dice, and their scores are displayed using an **LCD and 7-segment display**.

# Features
*  Two-player interactive gameplay
*  Random dice number generation (1–6)
*  LCD display for game messages
*  7-segment display for score tracking
*  5 rounds gameplay
*  Automatic winner detection

# Technologies Used
* Embedded C
* LPC21xx Microcontroller
* LCD Interface
* 7-Segment Display
* GPIO Programming

# Project Structure
* digital_dice.c     # Main program (game logic)
* diceheader.h       # Header file (display & utility functions)
  `
# How It Works
1. The game starts with a welcome message on the LCD.
2. Two players take turns pressing switches to roll the dice.
3. A random number (1–6) is generated using `rand()`.
4. Scores are updated and displayed:
   * LCD shows round and player info
   * 7-segment shows current scores
6. After 5 rounds:
   * The player with the highest score wins
   * Result is displayed on LCD

# Hardware Requirements
* LPC2129 ARM7 Development Board
* LCD Display (16x2)
* 7-Segment Display (4-digit)
* Push Buttons (for Player 1 & Player 2)
* Power Supply

# How to Run
1. Compile the code using an Embedded C compiler (Keil uVision recommended).
2. Flash the program to LPC21xx microcontroller.
3. Connect hardware as per pin configuration.
4. Power ON the system.
5. Press switches to play the game.

# Output Example
  * ROUND 1 PLAYER 1
    Dice: 4
  
  * ROUND 1 PLAYER 2
    Dice: 6

  * PLAYER 2 WIN
    
#  Notes
* Random number generation uses timer seed (`srand(T0TC)`).
* Display refresh is handled using multiplexing technique.
* Delay functions are used for timing control.

# Author
* Rajalakshmi S
