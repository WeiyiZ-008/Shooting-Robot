#include <iostream>
#include "Player.h"
#include "Arena.h"
#include "Globals.h"
#include<stdlib.h>
using namespace std;

Player::Player(Arena* ap, int r, int c)
{
    if (ap == NULL)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
      // Return what row the player is at.
    return m_row;      
}

int Player::col() const
{
      // Return what column the player is at.
    return m_col;      
}

int Player::age() const
{
      // Return the player's age.
    return m_age;
}

string Player::takeComputerChosenTurn()
{
    // TODO:  Replace this implementation:
        
	if(m_arena->nRobotsAt(m_row,m_col+1)==0 && m_arena->nRobotsAt(m_row,m_col-1)==0 && m_arena->nRobotsAt(m_row+1,m_col)== 0 && m_arena->nRobotsAt(m_row-1,m_col)==0) //when there is not robot within 1 distance 
    {
        if (m_arena->nRobotsAt(m_row, m_col + 2) > 0 || m_arena->nRobotsAt(m_row, m_col - 2) > 0 || m_arena->nRobotsAt(m_row + 2, m_col) > 0 || m_arena->nRobotsAt(m_row - 2, m_col) > 0)  //when there is a robot in 2 distance
        {
            if (m_arena->nRobotsAt(m_row, m_col + 2) > 0) // hvae robot in right direction
            {
                bool effectiveShot = shoot(RIGHT);
                if (effectiveShot == true)
                    return "Shot and hit!";
                else 
                   return "Shot and missed!";
            }
            if (m_arena->nRobotsAt(m_row, m_col - 2) > 0) // hvae robot in left direction
            {
                bool effectiveShot = shoot(LEFT);
                if (effectiveShot == true)
                    return "Shot and hit!";
                else
                    return "Shot and missed!";
            }
            if (m_arena->nRobotsAt(m_row + 2, m_col) > 0) // hvae robot in down direction
            {
                bool effectiveShot = shoot(DOWN);
                if (effectiveShot == true)
                    return "Shot and hit!";
                else
                    return "Shot and missed!";
            }
            if (m_arena->nRobotsAt(m_row - 2, m_col) > 0) // hvae robot in up direction
            {
                bool effectiveShot = shoot(UP);
                if (effectiveShot == true)
                    return "Shot and hit!";
                else
                    return "Shot and missed!";
            }
        }
        else    // no movement
        {
            stand();
            return "Stood.";
        }
    }
    else  //no robot within 1 distance, which is safe condition, can move player
    {
        if (m_arena->nRobotsAt(m_row + 1, m_col) == 0) // down direction is safe for moving 1 distance 
        {
            move(DOWN);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row - 1, m_col) == 0) // up direction is safe for moving 1 distance
        {
            move(UP);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row, m_col + 1) == 0) // right direction is safe for moving 1 distance
        {
            move(RIGHT);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row, m_col - 1) == 0) // left direction is safe for moving 1 distance
        {
            move(LEFT);
            return "Moved.";
        }
    }
    stand();    //no movement
    return "Stood.";
                
    // Your replacement implementation should do something intelligent
    // and return a string that describes what happened.  When you've
    // decided what action to take, take it by calling move, shoot, or stand.
    // This function must return one of the following four strings:
    //     "Moved."
    //     "Shot and hit!"
    //     "Shot and missed!"
    //     "Stood."

    // Here's one possible strategy:
    //   If moving in some direction would put me in less immediate danger
    //     than standing, then move in that direction.
    //   else shoot in the direction of the nearest robot I can hit.

    // A more aggressive strategy is possible, where you hunt down robots.
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    switch (dir)
    {
      case UP:
      	if (m_row > 1 && m_row <= m_arena->rows())   //second row ~ lats row
        {
            m_row--;
            m_age++;
            break;
        }
        stand();
      	break;
        // Move the player up one row if possible.
      case DOWN:
      	if (m_row > 0 && m_row < m_arena->rows())   //first row ~ lats row
        {
            m_row++;
            m_age++;
            break;
        }
        stand();
      	break;
      case LEFT:
      	if (m_col > 1 && m_col <= m_arena->cols())   //second column ~ lats column
        {
            m_col--;
            m_age++;
            break;
        }
        stand();
      	break;
      case RIGHT:
      	if (m_col > 0 && m_col < m_arena->cols())   //first column ~ lats second column
        {
            m_col++;
            m_age++;
            break;
        }
        stand();
      	break;
        // Implement the other movements.
    }
}

bool Player::shoot(int dir)
{
    m_age++;

    if (rand() % 3 == 0)  // miss with 1/3 probability
    {
		return false;
    }
    else if (dir == UP)   // when shooting up direction
    {
        for (int i = 0; i <= MAXSHOTLEN; i++)  //to check if there is any robot within the shoot distance
        {
            if (m_arena->nRobotsAt(m_row - i, m_col) > 0 && m_row - i > 0)  //make sure is not out of the boundary
            {
                m_arena->damageRobotAt(m_row - i, m_col);
                return true;
            }
        }
    }else if (dir == DOWN)     //when shooting downward
    {
        for (int i = 0; i <= MAXSHOTLEN; i++) //to check if there is any robot within the shoot distance
        {
            if (m_arena->nRobotsAt(m_row + i, m_col) > 0 && m_row + i > 0)
            {
                m_arena->damageRobotAt(m_row + i, m_col);
                return true;
            }
        }
    }else if (dir == LEFT)   //when shooting left direction
    {
        for (int i = 0; i <= MAXSHOTLEN; i++)   //to check if there is any robot within the shoot distance
        {
            if (m_arena->nRobotsAt(m_row, m_col - i) > 0 && m_col - i > 0)
            {
                m_arena->damageRobotAt(m_row, m_col - i);
                return true;
            }
        }
    }else if (dir == RIGHT)  //when shooting right direction
    {
        for (int i = 0; i <= MAXSHOTLEN; i++)   //to check if there is any robot within the shoot distance
        {
            if (m_arena->nRobotsAt(m_row, m_col + i) > 0 && m_col + i > 0)
            {
                m_arena->damageRobotAt(m_row, m_col + i);
                return true;
            }
        }
    }
   // return false;   //if miss the shoot
    
      // Damage the nearest robot in direction dir, returning
      // true if a robot is hit and damaged, false if not hit.
}

bool Player::isDead() const
{
      // Return whether the player is dead.
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

