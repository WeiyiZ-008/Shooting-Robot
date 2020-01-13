# Shooting-Robot
Simple version of game Battle City. Simulate by using 2D matrix.
- The game allows the user to select the player's action: u/d/l/r for movement,
su/sd/sl/sr for shooting, and just hitting enter for standing. The user may also type q to
prematurely quit the game, or c to have the computer select the player's move.
- When it's the robots' turn, each robot picks a random direction (up, down, left, or
right) with equal probability. The robot moves one step in that direction if it can; if the
robot attempts to move out of the arena, however, (e.g., down, when on the bottom
row), it does not move. More than one robot may occupy the same position; in that
case, instead of R, the display will show a digit character indicating the number of
robots at that position (where 9 indicates 9 or more). If after the robots move, a robot
occupies the same position as the player, the player dies.


# Project of Data Structure
At each turn the player may take one of these actions:
- Stand. In this case, the player does not move or shoot.
- Move one step up, down, left, or right. If the player attempts to move out of the
arena (e.g., down, when on the bottom row), the result is the same as standing. It
is allowable for the player to move to a position currently occupied by a robot. If
no robot occupies that position after the robots have moved, the player survived
the turn.
- Shoot in one of the four directions up, down, left, or right. If there is at least one
robot within 5 steps in that direction (this only matters with anything larger than a
6x6 arena), the nearest one in that direction is the candidate victim. If more than
one robot is nearest (i.e., they occupy the same position), only one robot at that
position is the candidate victim. With 2/3 probability, the candidate victim is
damaged; with 1/3 probability, the shot is ineffective and no robot is damaged. A
robot that has been damaged for the second time is destroyed (i.e., to destroy a
robot takes two shots that hit).

# Game
- To create a Game, you specify a number of rows and columns and the number of robots to start with. The Game object creates an appropriately sized Arena and populates it with the Player and the Robots.
- A game may be played.

# Arena
- When an Arena object of a particular size is created, it has no robots or player. In the Arena coordinate system, row 1, column 1 is the upper-left-most position that can be occupied by a Robot or Player. (If an Arena were created with 10 rows and 20 columns, then the lower-right-most position that could be occupied would be row 10, column 20.)
- You may tell the Arena object to create or destroy a Robot at a particular position.
- You may tell the Arena object to create a Player at a particular position.
- You may tell the Arena object to have all the robots in it make their move.
- You may ask the Arena object its size, how many robots are at a particular position, and how many robots altogether are in the Arena.
- You may ask the Arena object for access to its player.
- An Arena object may be displayed on the screen, showing the locations of the robots and player, along with other status information.

# Player
- A Player is created at some position (using the Arena coordinate system, where row 1, column 1 is the upper-left-most position, etc.).
- You may tell a Player to stand, move in a direction, or shoot in a direction.
- You may tell a Player to take an action of its choice.
- You may tell a Player it has died.
- You may ask a Player for its position, alive/dead status, and age. (The age is the count of how many turns the player has survived.)

# Robot
- A robot is created at some position (using the Arena coordinate system, where row 1, column 1 is the upper-left-most position, etc.).
- You may tell a Robot to move.
- You may ask a Robot object for its position.
