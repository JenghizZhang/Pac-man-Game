/*
Author: Yunsong Zhang
Class: ECE 6122
Last Date Modified: Nov 24, 2020
Description:
This program is the implementation file of the header file ECE_Pacman.
It contains four public functions to 1.draw the Pacman 2. move the pacman 
3. check the position of pacman to find whether this position is wall
4. check the direction and position of pacman (if the pacman move at this direction,
will this position is wall)
*/
#include <GL/glut.h>
#include "ECE_Pacman.h"
//draw the Pacman based on xPacman and zPacman (the coordinate of pacman)
void ECE_Pacman::draw()
{
    glColor3f(1, 1, 0); //set the color to yellow
    glPushMatrix();
        glTranslatef(xPacman, 0.2f, zPacman);//translate the sphere to the correct position
        glutSolidSphere(0.55, 30, 30);//draw a sphere with radius 0.6
    glPopMatrix();
}
//check the position of pacman to find whether this position is wall. Input x and z is the coordinate and if it is wall, return 1.
bool ECE_Pacman::touchEdge(float xPos, float zPos) 
{
    //set the input coordinate as integer
    int x = (int)xPos;
    int z = (int)zPos;
    if (maze[z + 11][x + 9] == 1) //check whether it is wall
    {
        return 1; //is wall
    }
    else 
    {
        return 0; //not wall
    }
}
//check the direction (input) and position of pacman (if the pacman move at this direction, will this position is wall). If it is wall, retun 1.
bool ECE_Pacman::directionCheck(int direction)
{
    //set the coordinate as integer
    int x = (int)xPacman;
    int z = (int)zPacman;
    switch (direction) //check whether it will be wall based on the direction
    {
    case 0:
        if (this->touchEdge(xPacman, zPacman - 1) == 1) //is wall
        {
            return 1;
        }
        break;
    case 1:
        if (this->touchEdge(xPacman, zPacman + 1) == 1) //is wall
        {
            return 1;
        }
        break;
    case 2:
        if (this->touchEdge(xPacman - 1, zPacman) == 1) //is wall
        {
            return 1;
        }
        break;
    case 3:
        if (this->touchEdge(xPacman + 1, zPacman) == 1) //is wall
        {
            return 1;
        }
        break;
    }
    return 0;//is not wall
}
//change xPacman and zPacman based on the input direction, and check whether it reaches the wall
void ECE_Pacman::move(int direction) 
{
    switch (direction)//move the pacman based on the input direction
    {
    case 0: //up
        this->zPacman -= 1; 
        if (this->touchEdge(xPacman, zPacman) == 1) //is wall, then stop
        {
            this->zPacman += 1;
        }
        break;
    case 1: //down
        this->zPacman += 1;
        if (this->touchEdge(xPacman, zPacman) == 1) //is wall, then stop
        {
            this->zPacman -= 1;
        }
        break;
    case 2: //left
        if (this->xPacman == -9 && this->zPacman == -1) //check whether it leaves from the left port
        {
            this->xPacman = 9;
        }
        else
        {
            this->xPacman -= 1;
            if (this->touchEdge(xPacman, zPacman) == 1)//is wall, then stop
            {
                this->xPacman += 1;
            }
        }
        break;
    case 3: //right
        if (this->xPacman == 9 && this->zPacman == -1)//check whether it leaves from the right port
        {
            this->xPacman = -9;
        }
        else
        {
            this->xPacman += 1;
            if (this->touchEdge(xPacman, zPacman) == 1)//is wall, then stop
            {
                this->xPacman -= 1;
            }
        }
        break;
    }
}