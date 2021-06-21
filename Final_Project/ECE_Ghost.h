/*
Description:
This program is the header file of ECE_Ghost. It contains eight public functions to 1.to 4.draw the
ghost in red green pink and orange color 5.use BFS algorithm to calculate the direction of the ghost
(shortest path algorithm) 6. move the ghost based on the positions of pacman and ghost 7. run away from
the pacman after it eats the power up 8. check whether the ghost catches the pacman. The position and direction
of ghost are set as public and the maze information is set as private. It also contains the declaration of quardratic.
*/
#pragma once
#include <GL/glut.h>
//creat a structure called node for BFS algorithm
struct node {
	int x; //x position
	int z; //z position
	int parentNode; //parrent node
	int direction; //direction of the ghost
};
class ECE_Ghost //declare a class called ECE_Ghost to draw the ghost and move it in the shortest path algorithm
{
public:
	void drawRed(); //draw the red ghost based on xRed and zRed and power up (for changing color)
	void drawGreen(); //draw the green ghost based on xGreen and zGreen and power up (for changing color)
	void drawPink(); //draw the pink ghost based on xPink and zPink and power up (for changing color)
	void drawOrange(); //draw the orange ghost based on xOrange and zOrange and power up (for changing color)
	//using BFS algorithm to find the direction of ghost.The inputs are the ghost position and pacman position and output is the moving direction of the ghost
	int BFS(float x, float z, float pmx, float pmz);
	//move the ghost based on the shortest path algorithm. Input is the positions of pacman and ghost and the color of the ghost. It changes the position of the ghost based on the color
	void move(float x, float z, float pmx, float pmz, int color);
	//move the ghost away from the pacman based on the reverse shortest path algorithm. Input is the positions of pacman and ghost and the color of the ghost. It changes the position of the ghost based on the color
	void runAway(float x, float z, float pmx, float pmz, int color);
	//chech whether ghost catches pacman.Input is the positions of pacman and ghost.if catch, return 1.
	bool catchPacman (float x, float z, float pmx, float pmz);
	float xRed = 0.0f; //initial red position
	float zRed = -1.4f;
	float xGreen = -1.0f; //initial green position
	float zGreen = -0.5f;
	float xPink = 0.0f; //initial pink position
	float zPink = -0.5f;
	float xOrange = 1.0f; //initial orange position
	float zOrange = -0.5f;
	int direction = 1;
	bool powerUp = 0;
private:
	
	GLUquadricObj* quardratic = gluNewQuadric(); //set quardratic
	bool maze[22][19] =
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