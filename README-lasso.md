# Lasso Project

**Important:** The code of the game is tested and developed on macOS. It may not be completely compatible with other Operating Systems. If the game has to be tried, please use macOS to do so. The instructions for compiling on macOS are at the bottom of the document.

## [Video Explaining the game](https://drive.google.com/file/d/1XvaYVPNi9NqEYwlOz7_cmPBPi6xjsq9b/view?usp=sharing)

## Features added to the game

- Multiple game modes added(Arcade mode, Bomb mode, Magnet mode and Mega mode)
- Lives and Bombs added
- Multiple Coins
- Bomb Coin 
- Bonus Coin 
- Magnet Coin
- Frenzy Coin(explained below)
- Time limit of 30 seconds in the game, shows a final score screen after that
- Coin now moves in a parabolic path at a random angle
- Coin spawns at a random location on the horizontal line
- Page to pick game mode added in game(with explanation of each)
- Instructions page added in game
- Coin info page added in game
- Final score screen: choose to play a new game or view instructions again after viewing your score
- About 900+ lines of code added

## Controls of the game
- **+/= and - :** Increase and decrease the speed of the lasso respectively
- **[ and ]:** Change the angle of the lasso
- **t:** Throws the lasso
- **l:** 'loops' the lasso, which means that the coin can be caught at this moment, if it is within range
- **y:** 'yanks' the lasso, brings lasso back to starting position
- **q:** press q any time to quit game

## Types of Coins

* **Regular:** Basic coin, gives a +1 to score
* **Bonus:** gives a +2 to score
* **Bomb:** Dangerous coin, gives a -1 to score and takes away a precious life!
* **Magnet:** Magnetizes lasso for 5s
* **Frenzy:** Increases number of coins for 10s

## Game Modes

* **Arcade Mode:** Basic mode, includes regular coins, bonus coins and frenzy coins
* **Bomb mode:** Includes bombs, bonus coins and regular coins
* **Magnet Mode:** Includes regular coins, bonus coins and magnet coins
* **Mega Mode:** Includes all coin types!

## General Instructions

In each game mode one has 30 seconds to maximize his score after which the game ends and asks you if you would like to play again. In the bomb and mega mode you must also conserve your lives by dodging the bombs!

### Compile on MacOS

```bash
s++ -o lasso coin.cpp display.cpp game.cpp lasso.cpp main.cpp MovingObject.cpp random.cpp
```
