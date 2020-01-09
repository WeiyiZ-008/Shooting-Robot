#include <iostream>
#include <cmath>
#include "Arena.h"
#include "Robot.h"
#include "Globals.h"
#include<stdlib.h>

using namespace std;

Robot::Robot(Arena* ap, int r, int c)
{
    if (ap == NULL)
    {
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    hit_times = 0;
   // hit_robot = false;
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const
{
      // Return what column the robot is at.
    return m_col;    
}

void Robot::move()
{
      // Attempt to move in a random direction; if we can't move, don't move
    switch (rand() % 4)
    {
      case UP:    //to check if the robot move within the grid   second-row ~ bottle-row
      		if (m_row > 1 && m_row <= m_arena->rows())
            {
                m_row--;
            }
      		break;
        // Move the robot up one row if possible.
      case DOWN:
      		if (m_row > 0 && m_row < m_arena->rows())  //first-row ~ last second-row
            {
                m_row++;
            }
      	    break;
      case LEFT:
      	    if (m_col > 1 && m_col <= m_arena->cols())  //second-column ~ last-column
            {
                m_col--;
            }
      	    break;
      case RIGHT:
      		if (m_col > 0 && m_col < m_arena->cols())  //first-column ~ last second-column
            {
                m_col++;
            }
      	    break;
        // Implement the other movements.
    }
}

bool Robot::takeDamageAndLive()
{
	//hit_robot = true;
	hit_times++;
	if( hit_times == 2)  //the situation that robot has been hit once before
	 {
	 	return false;
	 }else if( hit_times < 2)
		return true;
      // If the robot has been hit once before, return false (since a
      // second hit kills a robot).  Otherwise, return true (since the robot
      // survived the damage).
}

