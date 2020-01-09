#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Robot.h"
#include "Player.h"
#include "Arena.h"
#include "Game.h"
#include "Globals.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main()
{
	int cao;
      // Initialize the random number generator.  (You don't need to
      // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));

      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(5, 5, 5);

      // Play the game
    g.play();
    cin >> cao;
}
