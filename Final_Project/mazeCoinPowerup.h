/*
Description:
This program is the header file of mazeCoinPowerup. It contains four public functions to 1. draw the
maze, coins, and power up 2. check the coin eaten by pacman 3. check the power up eaten by pacman 4.
check whether all coins and power ups are eaten by the pacman (win the game).The coin and power up information
is set as public and the maze wall information is set as private. It also declared the quardratic.
*/
#pragma once
#include <GL/glut.h>
//declare a class called mazeCoinPowerup to draw the maze, coins, and power up and check the informantion (whether being eaten) of the coins and power up.
class mazeCoinPowerup 
{
public:
	//draw the maze, coins, and power up. mazeNum is for changing the maze.Here it should be 1 beacuse I only specified one maze information. We can add a new maze then use mazeNum = 2 to change the maze
	void draw(int mazeNum);
	//check the state (eaten or not) of all coins. If it is eaten, set its value to 0. Input x and z is the coordinate of the pacman
	void checkCoin(float x, float z);
	//check the state (eaten or not) of all power ups. If it is eaten, set its value to 0. Input x and z is the coordinate of the pacman.If pacman eats a power up, return 0.
	bool checkPower(float x, float z);
	//check whether all coins and power up are eaten.If yes, return 1.
	bool checkWin();
	int coinPosNum1[152][3] = //sphere to build coins.The first and second are the x,z position.The third is whether it is eaten for the final lab.
	{
		//first line z=-10 (16 coins)
		{-8,-10,1},{-7,-10,1},{-6,-10,1},{-5,-10,1},{-4,-10,1},{-3,-10,1},{-2,-10,1},{-1,-10,1},
		{1,-10,1},{2,-10,1},{3,-10,1},{4,-10,1},{5,-10,1},{6,-10,1},{7,-10,1},{8,-10,1},
		//second line z=-9 (4 coins) 20
		{-5,-9,1},{-1,-9,1},{1,-9,1},{5,-9,1},
		//third line z=-8 (6 coins) 26
		{-8,-8,1},{-5,-8,1},{-1,-8,1},{1,-8,1},{5,-8,1},{8,-8,1},
		//fourth line z=-7 (17 coins) 43
		{-8,-7,1},{-7,-7,1},{-6,-7,1},{-5,-7,1},{-4,-7,1},{-3,-7,1},{-2,-7,1},{-1,-7,1},{0,-7,1},
		{1,-7,1},{2,-7,1},{3,-7,1},{4,-7,1},{5,-7,1},{6,-7,1},{7,-7,1},{8,-7,1},
		//fifth line z=-6 (6 coins) 49
		{-8,-6,1},{-5,-6,1},{-3,-6,1},{3,-6,1},{5,-6,1},{8,-6,1},
		//sixth line z=-5 (14 coins) 63
		{-8,-5,1},{-7,-5,1},{-6,-5,1},{-5,-5,1},{-3,-5,1},{-2,-5,1},{-1,-5,1},
		{1,-5,1},{2,-5,1},{3,-5,1},{5,-5,1},{6,-5,1},{7,-5,1},{8,-5,1},
		//seventh to thirteenth line z=-4 to 2 (14 coins) 77
		{-5,-4,1},{5,-4,1},
		{-5,-3,1},{5,-3,1},
		{-5,-2,1},{5,-2,1},
		{-5,-1,1},{5,-1,1},
		{-5,0,1},{5,0,1},
		{-5,1,1},{5,1,1},
		{-5,2,1},{5,2,1},
		//fourteenth line z=3 (16 coins) 93
		{-8,3,1},{-7,3,1},{-6,3,1},{-5,3,1},{-4,3,1},{-3,3,1},{-2,3,1},{-1,3,1},
		{1,3,1},{2,3,1},{3,3,1},{4,3,1},{5,3,1},{6,3,1},{7,3,1},{8,3,1},
		//fifteenth line z=4 (6 coins) 99
		{-8,4,1},{-5,4,1},{-1,4,1},{1,4,1},{5,4,1},{8,4,1},
		//sixteenth line z=5 (12 coins) 111
		{-7,5,1},{-5,5,1},{-4,5,1},{-3,5,1},{-2,5,1},{-1,5,1},
		{1,5,1},{2,5,1},{3,5,1},{4,5,1},{5,5,1},{7,5,1},
		//seventeenth line z=6 (6 coins) 117
		{-7,6,1},{-5,6,1},{-3,6,1},{3,6,1},{5,6,1},{7,6,1},
		//eighteenth line z=7 (14 coins) 131
		{-8,7,1},{-7,7,1},{-6,7,1},{-5,7,1},{-3,7,1},{-2,7,1},{-1,7,1},
		{1,7,1},{2,7,1},{3,7,1},{5,7,1},{6,7,1},{7,7,1},{8,7,1},
		//nineteenth line z=8 (4 coins) 135
		{-8,8,1},{-1,8,1},{1,8,1},{8,8,1},
		//twentieth line z=9 (17 coins) 152
		{-8,9,1},{-7,9,1},{-6,9,1},{-5,9,1},{-4,9,1},{-3,9,1},{-2,9,1},{-1,9,1},{0,9,1},
		{1,9,1},{2,9,1},{3,9,1},{4,9,1},{5,9,1},{6,9,1},{7,9,1},{8,9,1}
	};
	int powerPosNum1[4][3] = { {-8,-9,1},{8,-9,1},{-8,5,1},{8,5,1} }; //4 power up.The first and second are the x,z position.The third is whether it is eaten for the final lab.

private:
	GLUquadricObj* quardratic = gluNewQuadric(); //set quardratic
	int zCylinderNum1[30][3] = //cylinder along z axis.It has 30 cylinders and the first and second element are the x,z position, and the third is length
	{
		//above z axis
		{-9,2,8},{-6,0,2},{-6,4,2},{-4,0,2},{-4,6,2},{0,2,2},
		{0,6,2},{4,0,2},{4,6,2},{6,4,2},{6,0,2},{9,2,8},
		//below z axis
		{-9,-11,7},{-7,-9,1},{-6,-9,1},{-6,-4,2},{-4,-9,1},
		{-2,-9,1},{-4,-6,4},{-2,-2,2},{0,-11,3},{0,-6,2},
		{2,-2,2},{2,-9,1},{4,-6,4},{4,-9,1},{6,-9,1},{6,-4,2},
		{7,-9,1},{9,-11,7}
	};
	int xCylinderNum1[34][3] = //cylinder along x axis.It has 34 cylinders and the first and second element are the x,z position, and the third is length
	{
		//above z axis
		{-9,0,3},{-9,2,3},{-9,10,18},{-7,4,1},{-7,8,5},{-4,4,2},
		{-2,2,4},{-2,6,4},{2,4,2},{2,8,5},{6,4,1},{6,0,3},{6,2,3},
		{8,6,1},{-9,6,1},{-2,0,4},
		//below z axis
		{-9,-2,3},{6,-2,3},{-9,-4,3},{6,-4,3},{-4,-4,2},{2,-4,2},
		{-2,-6,4},{-7,-6,1},{6,-6,1},{-7,-8,1},{-7,-9,1},{6,-8,1},
		{6,-9,1},{-4,-8,2},{-4,-9,2},{2,-8,2},{2,-9,2},{-9,-11,18}
	};
	float xDoor[2][3] = { {-2.0f,-2.0f,1.4f},{0.6f,-2.0f,1.4f} }; //cylinders to build the door for the ghosts.The first and second element are the x,z position, and the third is length
	
};