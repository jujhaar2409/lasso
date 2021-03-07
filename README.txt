Lasso Project for CS101

Compile on MacOS:
s++ -o lasso coin.cpp display.cpp game.cpp lasso.cpp main.cpp MovingObject.cpp random.cpp
./lasso

Features added to the game:
- Multiple game modes added(Arcade mode, Bomb mode, Magnet mode and Mega mode)
- Page to pick game mode added in game(with explanation of each)
- Coin now moves in a parabolic path at a random angle
- Multiple Coins
- Bomb Coin added: gives a -1 score on collecting
- Magnet Coin added: magnetises the lasso for 5 seconds
- Frenzy Coin added: introduces extra coins for 10 seconds
- Time limit of 30 seconds in the game, shows a final score screen after that
- Final score screen: choose to play a new game or view instructions again after viewing your score
- Instructions page added in game
- Coin info page added in game

Controls of the game:
+/= and -: Increase and decrease the speed of the lasso respectively
[ and ]: Change the angle of the lasso
t: Throws the lasso
l: 'loops' the lasso, which means that the coin can be caught at this moment, if it is within range
y: 'yanks' the lasso, brings lasso back to starting position
q: press q any time to quit game

