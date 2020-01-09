#include <iostream>
#include "Arena.h"
#include "Player.h"
#include "Robot.h"
#include <string>
#include<stdlib.h>

using namespace std;

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = NULL;
    m_nRobots = 0;
}

Arena::~Arena()
{
      // Delete the player and all remaining dynamically allocated robots.
    delete m_player;   //deallocate player 
    for(int i = 0; i < m_nRobots; i++)  //deaalocate robots elemnts
	{
        delete m_robots[i];
    }
}

int Arena::rows() const
{
      // Return the number of rows in the arena.
    return m_rows;
}

int Arena::cols() const
{
      // Return the number of columns in the arena.
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::robotCount() const
{
    return m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const
{
    // Return the number of robots at row r, column c.
    int numRobotsAt=0;
    for(int i = 0; i < m_nRobots; i++)  //to check if the robots has same row and column position
    {
    	if( m_robots[i]->row() == r && m_robots[i]->col() == c )
    	 numRobotsAt++;
    }
    return numRobotsAt;  // This implementation compiles, but is incorrect.
}

void Arena::display(string msg) const
{
      // Position (row,col) in the arena coordinate system is represented in
      // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
        // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

        // Indicate each robot's position
      // If one robot is at some grid point, set the char to 'R'.
      // If it's 2 though 8, set it to '2' through '8'.
      // For 9 or more, set it to '9'.

	for( int i = 0; i < m_nRobots; i++ )
	{
	
    if( m_robots != NULL )
    {
    	char& gridChar = grid[m_robots[i]->row()-1][m_robots[i]->col()-1];
    	if(gridChar == '.')
    	{
    		gridChar='R';   //mark the robot position
    	}else if( gridChar == 'R' )   //if there is already exits one robot 
    	 {
    	 	gridChar= '2';   //mark two robots at same position
    	 }else if( gridChar == '2' )    
    	 {
    	 	gridChar= '3';   //mark 3 robots at same position
    	 }else if( gridChar == '3' )   
    	 {
    	 	gridChar= '4';   //mark 4 robots at same position
    	 }else if( gridChar == '4' )    
    	 {
    	 	gridChar= '5';   //mark 5 robots at same position
    	 }else if( gridChar == '5' )    
    	 {
    	 	gridChar= '6';   //mark 6 robots at same position
    	 }else if( gridChar == '6' )    
    	 {
    	 	gridChar= '7';   //mark 7 robots at same position
    	 }else if( gridChar == '7' )    
    	 {
    	 	gridChar= '8';   //mark 8 robots at same position
    	 }else if( gridChar == '8' )    
    	 {
    	 	gridChar= '9';   //mark 9 robots at same position
    	 }else
    	 	gridChar= '9';   //mark 9 robots at same position for # of robots more than 9
    }
	}
	
		    

        // Indicate player's position
    if (m_player != NULL)
    {
          // Set the char to '@', unless there's also a robot there,
          // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

        // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

        // Write message, robot, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << robotCount() << " robots remaining." << endl;
    if (m_player == NULL)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Arena::addRobot(int r, int c)
{
      // If MAXROBOTS have already been added, return false.  Otherwise,
      // dynamically allocate a new robot at coordinates (r,c).  Save the
      // pointer to the newly allocated robot and return true.
	if( m_nRobots == MAXROBOTS)
	
	return false;
	
	 m_robots[m_nRobots] = new Robot(this, r, c);
	 m_nRobots++;
	 return true;
}

bool Arena::addPlayer(int r, int c)
{
      // Don't add a player if one already exists
    if (m_player != NULL)
        return false;

      // Dynamically allocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    return true;
}

void Arena::damageRobotAt(int r, int c)
{
      // Damage one robot at row r, column c if at least one is there.
      // If the robot does not survive the damage, destroy it.
    bool stillAlive = false;
    int i = 0;

    while (i < m_nRobots)
    {
        if (nRobotsAt(r, c) > 0)
        {
            if (m_robots[i]->row() == r && m_robots[i]->col() == c)  //check if the robots at this position Live or not
            {
                stillAlive = m_robots[i]->takeDamageAndLive();
                break;   //jump out the loop
            }
        }
        i++; 
    }
    if ( i < m_nRobots && stillAlive == false)   //robot die & make sure deleting robot is not the last robot left.
    {
        delete m_robots[i];   //damage the robot.
        m_robots[i] = m_robots[m_nRobots - 1];  // swap the last element with deleting element.
        m_nRobots--; 
    }  
}

bool Arena::moveRobots()
{
    for (int k = 0; k < m_nRobots; k++)
    {
     	m_robots[k]->move();  //call member function move.

        if (m_robots[k]->row() == m_player->row() && m_robots[k]->col() == m_player->col())  //when robot and player at same position
        {
            m_player->setDead();  //call member function to set player dead.
        }
      //Have the k-th robot in the arena make one move.
      //If that move results in that robot being in the same
      //position as the player, the player dies.
    }

      // return true if the player is still alive, false otherwise
    return ! m_player->isDead();  
}

