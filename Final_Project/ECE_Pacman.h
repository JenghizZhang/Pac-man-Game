/*
Description:
This program is the header file of ECE_Pacman. It contains four public functions to 1.draw the
Pacman 2. move the pacman 3. check the position of pacman to find whether this position is wall
4. check the direction and position of pacman (if the pacman move at this direction, will this
position is wall). The position of pacman is set as public and the maze information is set as private.
*/
#pragma once
#include <GL/glut.h>

class ECE_Pacman //declare a class called ECE_Pacman to draw the Pacman and move its position
{
public:
	//draw the Pacman based on xPacman and zPacman (the coordinate of pacman)
	void draw();
	//change xPacman and zPacman based on the input direction, and check whether it reaches the wall
	void move(int direction);
	//check the direction (input) and position of pacman (if the pacman move at this direction, will this position is wall). If it is wall, retun 1.
	bool directionCheck(int direction);
	//check the position of pacman to find whether this position is wall. Input x and z is the coordinate and if it is wall, return 1.
	bool touchEdge(float x, float z);
	//set the initial position
	float xPacman = 0;
	float zPacman = 5;
private:
	bool maze[22][19] = //set the maze information
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, //z=-11
		{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1}, //z=-10
		{1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1}, //z=-9
		{1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1}, //z=-8
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //z=-7
		{1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1}, //z=-6
		{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1}, //z=-5
		{1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1}, //z=-4
		{1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,1,1,1,1}, //z=-3
		{1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1}, //z=-2
		{0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0}, //z=-1
		{1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1}, //z=0
		{1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,1,1,1,1}, //z=1
		{1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1}, //z=2
		{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1}, //z=3
		{1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1}, //z=4
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1}, //z=5
		{1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1}, //z=6
		{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1}, //z=7
		{1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1}, //z=8
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //z=9
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, //z=10
	};
};