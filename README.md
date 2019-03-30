# dablotcode
code for dablot game

This is a Computer Science course project by Cleberson Pertile for the Structured Programming subject at Universidade Tuiuti do Parana (UTP), Professor Douglas Koerich.

*The game:*
The Dablot game is an ancient board game like Checkers, two players face each other turn-by-turn.
There are, however, different classes of pieces, which represent a kingdom fighting against a people.
On the kingdom's side, there's the King, the Prince, and the Warriors; On the people's side, there's the Farmer, his Son, and the Workers.

Pieces can only eliminate another if it's on the same class or below its own.

The game can end in three different ways:
1: eliminating all of the opponent's pieces;
2: blocking the opponent from moving;
3: a player can give up if he/she loses his greater piece (King or Farmer)

*The gameplay:*
To play this game, you'll need to clone the repo or download all the source codes and compile them (GCC works fine on Linux, Windows and Mac). The current language is brazilian-portuguese, but the game is basically played by typing the coordinates of the piece you want to move, and then the destination coordinates. If your piece can't move, you'll get a warning when you select it. Every possible move position is calculated by the game, so you'll get a warning if you try to move your piece somewhere impossible.

Eliminating other player's pieces is done by 'jumping' over them to the next empty tile. You can only jump one piece, so no double-elimination is possible.

Have fun :)
