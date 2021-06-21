/*
Author: Yunsong Zhang
Class: ECE 6122
Last Date Modified: Nov 24, 2020
Description:
This program is the implementation file of the ECE_Ghost.h.It contains eight public functions to 1.to 4.draw the
ghost in red green pink and orange color 5.use BFS algorithm to calculate the direction of the ghost
(shortest path algorithm) 6. move the ghost based on the positions of pacman and ghost 7. run away from
the pacman after it eats the power up 8. check whether the ghost catches the pacman.
*/
#include <GL/glut.h>
#include "ECE_Ghost.h"
#pragma warning(disable: 6385) //dataoverflow, I restrict the position which will not cause this warning
#pragma warning(disable: 6386) //dataoverflow, I restrict the position which will not cause this warning
//draw the red ghost based on xRed and zRed and power up (for changing color)
void ECE_Ghost::drawRed()
{
	if (powerUp == 1) //if the pacman eats power up
	{
		glColor3f(1.0, 1.0, 1.0); //set the color to white
	}
	else 
	{
		glColor3f(1.0, 0.0, 0.0); //set the color to red
	}
	glPushMatrix();
		glTranslatef(xRed, -0.2f, zRed); //translate to the position
			glPushMatrix();
			switch (this->direction) //change the eye position based on the moving direction
			{
			case 0:
				glRotatef(180, 0, 1, 0); //rotate it along the x axis
				break;
			case 1:
				break;
			case 2:
				glRotatef(270, 0, 1, 0); //rotate it along the x axis
				break;
			case 3:
				glRotatef(90, 0, 1, 0); //rotate it along the x axis
				break;
			}
			glTranslatef(0.0f, 0.45f, 0.0f); //up translate
			glutSolidSphere(0.45, 30, 30); //draw the head
			glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(-0.12f, 0.1f, 0.225f); //up translate
				glutSolidSphere(0.225, 30, 30); //draw the eye
				glPushMatrix();
					glColor3f(0.0, 0.0, 0.0);
					glTranslatef(-0.02f, 0.1f, 0.16f);
					glutSolidSphere(0.08, 30, 30); //draw the eye
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(0.12f, 0.1f, 0.225f); //up translate 
				glutSolidSphere(0.225, 30, 30); //draw the eye
				glPushMatrix();
					glColor3f(0.0, 0.0, 0.0);
					glTranslatef(0.02f, 0.1f, 0.16f);
					glutSolidSphere(0.08, 30, 30); //draw the eye
				glPopMatrix();
				if (powerUp == 1)//if the pacman eats power up
				{
					glColor3f(1.0, 1.0, 1.0); //set the color to white
				}
				else
				{
					glColor3f(1.0, 0.0, 0.0); //set the color to red
				}
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glRotatef(270, 1, 0, 0); //rotate it along the x axis
			gluCylinder(quardratic, 0.45, 0.45, 0.45, 32, 32); //draw the body
		glPopMatrix();
		
		glPushMatrix();
			glRotatef(90, 1, 0, 0); //rotate it along the x axis
			gluDisk(quardratic, 0.0, 0.45, 30, 30); //draw bottom
		glPopMatrix();
	glPopMatrix();
}
//draw the green ghost based on xGreen and zGreen and power up (for changing color)
void ECE_Ghost::drawGreen()
{
	if (powerUp == 1)//if the pacman eats power up
	{
		glColor3f(1.0, 1.0, 1.0);//set the color to white
	}
	else
	{
		glColor3f(0.0, 1.0, 0.0); //set the color to green
	}
	glPushMatrix();
		glTranslatef(xGreen, -0.2f, zGreen);//translate to the position
		glPushMatrix();
			switch (this->direction) //change the eye position based on the moving direction
			{
			case 0:
				glRotatef(180, 0, 1, 0); //rotate it along the x axis
				break;
			case 1:
				break;
			case 2:
				glRotatef(270, 0, 1, 0); //rotate it along the x axis
				break;
			case 3:
				glRotatef(90, 0, 1, 0); //rotate it along the x axis
				break;
			}
			glTranslatef(0.0f, 0.45f, 0.0f);//up translate
			glutSolidSphere(0.45, 30, 30);//draw the head
			glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(-0.12f, 0.1f, 0.225f); //up translate
				glutSolidSphere(0.225, 30, 30); //draw the eye
				glPushMatrix();
					glColor3f(0.0, 0.0, 0.0);
					glTranslatef(-0.02f, 0.1f, 0.16f);
					glutSolidSphere(0.08, 30, 30); //draw the eye
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(0.12f, 0.1f, 0.225f); //up translate 
				glutSolidSphere(0.225, 30, 30); //draw the eye
				glPushMatrix();
					glColor3f(0.0, 0.0, 0.0);
					glTranslatef(0.02f, 0.1f, 0.16f);
					glutSolidSphere(0.08, 30, 30); //draw the eye
				glPopMatrix();
				if (powerUp == 1)//if the pacman eats power up
				{
					glColor3f(1.0, 1.0, 1.0);
				}
				else
				{
					glColor3f(0.0, 1.0, 0.0);
				}
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glRotatef(270, 1, 0, 0);//rotate it along the a axis
			gluCylinder(quardratic, 0.45, 0.45, 0.45, 32, 32);//draw the body
		glPopMatrix();

		glPushMatrix();
			glRotatef(90, 1, 0, 0);//rotate it along the x axis
			gluDisk(quardratic, 0.0, 0.45, 30, 30);//draw bottom
		glPopMatrix();
	glPopMatrix();
}
//draw the pink ghost based on xPink and zPink and power up (for changing color)
void ECE_Ghost::drawPink()
{
	if (powerUp == 1)//if the pacman eats power up
	{
		glColor3f(1.0, 1.0, 1.0);//set the color to white
	}
	else
	{
		glColor3f(1.0, 0.0, 1.0);//set the color to pink
	}
	glPushMatrix();
		glTranslatef(xPink, -0.2f, zPink);//translate to the position
		glPushMatrix();
			switch (this->direction)//change the eye position based on the moving direction
			{
			case 0:
				glRotatef(180, 0, 1, 0); //rotate it along the x axis
				break;
			case 1:
				break;
			case 2:
				glRotatef(270, 0, 1, 0); //rotate it along the x axis
				break;
			case 3:
				glRotatef(90, 0, 1, 0); //rotate it along the x axis
				break;
			}
			glTranslatef(0.0f, 0.45f, 0.0f);//up translate
			glutSolidSphere(0.45, 30, 30);//draw the head
			glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(-0.12f, 0.1f, 0.225f); //up translate
				glutSolidSphere(0.225, 30, 30); //draw the eye
				glPushMatrix();
					glColor3f(0.0, 0.0, 0.0);
					glTranslatef(-0.02f, 0.1f, 0.16f);
					glutSolidSphere(0.08, 30, 30); //draw the eye
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(0.12f, 0.1f, 0.225f); //up translate 
				glutSolidSphere(0.225, 30, 30); //draw the eye
				glPushMatrix();
					glColor3f(0.0, 0.0, 0.0);
					glTranslatef(0.02f, 0.1f, 0.16f);
					glutSolidSphere(0.08, 30, 30); //draw the eye
				glPopMatrix();
				if (powerUp == 1)//if the pacman eats power up
				{
					glColor3f(1.0, 1.0, 1.0);
				}
				else
				{
					glColor3f(1.0, 0.0, 1.0);
				}
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glRotatef(270, 1, 0, 0);//rotate it along the a axis
			gluCylinder(quardratic, 0.45, 0.45, 0.45, 32, 32);//draw the body
		glPopMatrix();

		glPushMatrix();
			glRotatef(90, 1, 0, 0);//rotate it along the x axis
			gluDisk(quardratic, 0.0, 0.45, 30, 30);//draw bottom
		glPopMatrix();
	glPopMatrix();
}
//draw the orange ghost based on xOrange and zOrange and power up (for changing color)
void ECE_Ghost::drawOrange()
{
	if (powerUp == 1)//if the pacman eats power up
	{
		glColor3f(1.0, 1.0, 1.0);//set the color to white
	}
	else
	{
		glColor3f(255.0f / 255.0f, 128.0f / 255.0f, 64.0f / 255.0f);//set the color to orange
	}
	glPushMatrix();
		glTranslatef(xOrange, -0.2f, zOrange);//translate to the position
		glPushMatrix();
			switch (this->direction)//change the eye position based on the moving direction
			{
			case 0:
				glRotatef(180, 0, 1, 0); //rotate it along the x axis
				break;
			case 1:
				break;
			case 2:
				glRotatef(270, 0, 1, 0); //rotate it along the x axis
				break;
			case 3:
				glRotatef(90, 0, 1, 0); //rotate it along the x axis
				break;
			}
			glTranslatef(0.0f, 0.45f, 0.0f);//up translate
			glutSolidSphere(0.45, 30, 30);//draw the head
			glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(-0.12f, 0.1f, 0.225f); //up translate
				glutSolidSphere(0.225, 30, 30); //draw the eye
				glPushMatrix();
					glColor3f(0.0, 0.0, 0.0);
					glTranslatef(-0.02f, 0.1f, 0.16f);
					glutSolidSphere(0.08, 30, 30); //draw the eye
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glColor3f(1.0, 1.0, 1.0);
				glTranslatef(0.12f, 0.1f, 0.225f); //up translate 
				glutSolidSphere(0.225, 30, 30); //draw the eye
				glPushMatrix();
					glColor3f(0.0, 0.0, 0.0);
					glTranslatef(0.02f, 0.1f, 0.16f);
					glutSolidSphere(0.08, 30, 30); //draw the eye
				glPopMatrix();
				if (powerUp == 1)//if the pacman eats power up
				{
					glColor3f(1.0, 1.0, 1.0);
				}
				else
				{
					glColor3f(255.0f / 255.0f, 128.0f / 255.0f, 64.0f / 255.0f);
				}
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glRotatef(270, 1, 0, 0);//rotate it along the a axis
			gluCylinder(quardratic, 0.45, 0.45, 0.45, 32, 32);//draw the body
		glPopMatrix();

		glPushMatrix();
			glRotatef(90, 1, 0, 0);//rotate it along the x axis
			gluDisk(quardratic, 0.0, 0.45, 30, 30);//draw bottom
		glPopMatrix();
	glPopMatrix();
}
//using BFS algorithm to find the direction of ghost.The inputs are the ghost position and pacman position and output is the moving direction of the ghost
int ECE_Ghost::BFS(float xF, float zF, float pmxF, float pmzF)
{
	//set the coordinates of ghost and pacman as integer
	int x = (int)xF;
	int z = (int)zF;
	int pmx = (int)pmxF;
	int pmz = (int)pmzF;
	//set the chain length to 500(breath)
	struct node chain[500];
	int head = 0; //the parrent node
	int tail = 1; //the child node
	int directionX[4] = { 0,0,-1,1 }; //-1 is left 1 is right
	int directionZ[4] = { -1,1,0,0 }; //-1 is up 1 is down
	int route[22][19];
	//copy the maze information
	for (int i = 0; i < 22; ++i)//loop the z axis 
	{
		for (int j = 0; j < 19; ++j) //loop the x axis
		{
			route[i][j] = this->maze[i][j];
		}
	}
	//check whether next movement can catch the pacman
	for (int i = 0; i < 4; ++i) //loop the four directions
	{
		int xPos = x + directionX[i];//the x axis of the ghost
		int zPos = z + directionZ[i];//the y axis of the ghost
		if (route[zPos + 11][xPos + 9] == 0 && xPos == pmx && zPos == pmz) //whether it can catch pacman in the next movement
		{
			return i;//return the direction which can catch pacman
		}
	}
	//set the information of the parrent node
	chain[head].x = x;
	chain[head].z = z;
	chain[head].parentNode = -1;
	chain[head].direction = -1;
	route[z + 11][x + 9] = 1;
	//loop all possibilities to catch pacman
	while (head < tail)//the chain is not empty
	{
		//loop all four directions
		for (int i = 0; i < 4; ++i) 
		{
			int xPos = chain[head].x + directionX[i];//the x axis of the ghost
			int zPos = chain[head].z + directionZ[i];//the y axis of the ghost
			//check whether it is at the left port
			if (xPos == -10 && zPos == -1) 
			{
				xPos = 9;
			}
			//check whether it is at the right port
			if (xPos == 10 && zPos == -1)
			{
				xPos = -9;
			}
			//check whether this position is not wall and has not been reached
			if (route[zPos + 11][xPos + 9] == 0) 
			{
				//set the child node
				route[zPos + 11][xPos + 9] = 1;
				chain[tail].x = xPos;
				chain[tail].z = zPos;
				chain[tail].parentNode = head;
				chain[tail].direction = i;
				tail++;
			}
			//check whether it catches the pacman
			if (xPos == pmx && zPos == pmz) 
			{
				//set t as the parrent node
				int t = chain[tail - 1].parentNode;
				//check whether it only moves one step
				if (t == 0) 
				{
					return chain[tail - 1].direction;
				}
				//loop all parrent node
				while (chain[t].parentNode != 0) 
				{
					//set t as the parrent node of the node in this breath
					int temp = chain[t].parentNode;
					t = temp;
				}
				//return the direction of the parrent node
				return chain[t].direction;
			}
		}
		head++;
	}
	//no solution
	return 4;
}
//move the ghost based on the shortest path algorithm. Input is the positions of pacman and ghost and the color of the ghost. It changes the position of the ghost based on the color
void ECE_Ghost::move(float xF, float zF, float pmxF, float pmzF, int color)
{
	//check whether ghost is in the ghost home
	if (xF >= -2 && xF <= 2 && zF > -2 && zF <= 0) 
	{
		return;
	}
	//set the positions of pacman and ghost as integer
	int x = (int)xF;
	int z = (int)zF;
	int pmx = (int)pmxF;
	int pmz = (int)pmzF;
	//check whether ghost catch pacman
	if (x == pmx && z == pmz)
	{
		return;
	}
	//move the ghost based on the BFS algorithm
	switch (BFS(xF, zF, pmxF, pmzF)) 
	{
	case 0: //up
		z -= 1; 
		this->direction = 0;
		break;
	case 1: //down
		z += 1;
		this->direction = 1;
		break;
	case 2: //left
		if (x == -9 && z == -1)//check whether it is at the left port 
		{
			x = 9;
		}
		else 
		{
			x -= 1;
		}
		this->direction = 2;
		break;
	case 3:
		if (x == 9 && z == -1)//check whether it is at the right port 
		{
			x = -9;
		}
		else
		{
			x += 1;
		}
		this->direction = 3;
		break;
	}
	switch (color) //set the postion of the ghost based on the color
	{
	case 0:
		xRed = (float)x;
		zRed = (float)z;
		break;
	case 1:
		xGreen = (float)x;
		zGreen = (float)z;
		break;
	case 2:
		xPink = (float)x;
		zPink = (float)z;
		break;
	case 3:
		xOrange = (float)x;
		zOrange = (float)z;
		break;
	}
}
//move the ghost away from the pacman based on the reverse shortest path algorithm. Input is the positions of pacman and ghost and the color of the ghost. It changes the position of the ghost based on the color
void ECE_Ghost::runAway(float xF, float zF, float pmxF, float pmzF, int color)
{
	//check whether ghost is in the ghost home
	if (xF >= -2 && xF <= 2 && zF > -2 && zF <= 0)
	{
		return;
	}
	//set the positions of pacman and ghost as integer
	int x = (int)xF;
	int z = (int)zF;
	int pmx = (int)pmxF;
	int pmz = (int)pmzF;
	//check whether ghost catch pacman
	if (x == pmx && z == pmz)
	{
		return;
	}
	//move the ghost based on the reverse application of BFS algorithm
	switch (BFS(xF, zF, pmxF, pmzF))
	{
	case 0: //ghost should not move up
		if (this->maze[z + 11 + 1][x + 9] == 0 && x != 10 && x != -10)//move down if possible
		{
			z += 1;
			this->direction = 1;
		}
		else if (x != 9 && this->maze[z + 11][x + 9 + 1] == 0)//move left if possible
		{
			x += 1;
			this->direction = 3;
		}
		else if (x == 9) //move left if possible
		{
			x = -9;
			this->direction = 3;
		}
		else if (x != -9 && this->maze[z + 11][x + 9 - 1] == 0) //move right if possible
		{
			x -= 1;
			this->direction = 2;
		}
		else if (x == -9) //move right if possible
		{
			x = 9;
			this->direction = 2;
		}
		else if (this->maze[z + 11 - 1][x + 9] == 0 && x != 10 && x != -10) //move up if possible
		{
			z -= 1;
			this->direction = 0;
		}
		break;
	case 1: //ghost should not move down
		if (this->maze[z + 11 - 1][x + 9] == 0 && x != 10 && x != -10)//move up if possible
		{
			z -= 1;
			this->direction = 0;
		}
		else if (x != 9 && this->maze[z + 11][x + 9 + 1] == 0)//move right if possible
		{
			x += 1;
			this->direction = 3;
		}
		else if (x == 9)//move right if possible
		{
			x = -9;
			this->direction = 3;
		}
		else if (x != -9 && this->maze[z + 11][x + 9 - 1] == 0)//move left if possible
		{
			x -= 1;
			this->direction = 2;
		}
		else if (x == -9)//move left if possible
		{
			x = 9;
			this->direction = 2;
		}
		else if (this->maze[z + 11 + 1][x + 9] == 0 && x != 10 && x != -10)//move down if possible
		{
			z += 1;
			this->direction = 1;
		}
		break;
	case 2://ghost should not move left
		if (x != 9 && this->maze[z + 11][x + 9 + 1] == 0)//move right if possible
		{
			x += 1;
			this->direction = 3;
		}
		else if (x == 9)//move right if possible
		{
			x += 1;
			this->direction = 3;
		}
		else if (this->maze[z + 11 - 1][x + 9] == 0 && x != 10 && x != -10)//move up if possible
		{
			z -= 1;
			this->direction = 0;
		}
		else if (this->maze[z + 11 + 1][x + 9] == 0 && x != 10 && x != -10)//move down if possible
		{
			z += 1;
			this->direction = 1;
		}
		else if (x != -9 && this->maze[z + 11][x + 9 - 1] == 0)//move left if possible
		{
			x -= 1;
			this->direction = 2;
		}
		else if (x == -9)//move left if possible
		{
			x -= 1;
			this->direction = 2;
		}
		break;
	case 3://ghost should not move right
		if (x != -9 && this->maze[z + 11][x + 9 - 1] == 0)//move left if possible
		{
			x -= 1;
			this->direction = 2;
		}
		else if (x == -9)//move left if possible
		{
			x -= 1;
			this->direction = 2;
		}
		else if (this->maze[z + 11 - 1][x + 9] == 0 && x != 10 && x != -10)//move up if possible
		{
			z -= 1;
			this->direction = 0;
		}
		else if (this->maze[z + 11 + 1][x + 9] == 0 && x != 10 && x != -10)//move down if possible
		{
			z += 1;
			this->direction = 1;
		}
		else if (x != 9 && this->maze[z + 11][x + 9 + 1] == 0)//move right if possible
		{
			x += 1;
			this->direction = 3;
		}
		else if (x == 9)//move right if possible
		{
			x += 1;
			this->direction = 3;
		}
		break;
	}
	if (x == 10) //move from the right port
	{
		x = -9;
	}
	if (x == -10) //move from the left port
	{
		x = 9;
	}
	switch (color)//set the position of the ghost based on the color
	{
	case 0:
		xRed = (float)x;
		zRed = (float)z;
		break;
	case 1:
		xGreen = (float)x;
		zGreen = (float)z;
		break;
	case 2:
		xPink = (float)x;
		zPink = (float)z;
		break;
	case 3:
		xOrange = (float)x;
		zOrange = (float)z;
		break;
	}
}
//chech whether ghost catches pacman.Input is the positions of pacman and ghost.if catch, return 1.
bool ECE_Ghost::catchPacman(float xF, float zF, float pmxF, float pmzF)
{
	//set the positions of pacman and ghost as integer
	int x = (int)xF;
	int z = (int)zF;
	int pmx = (int)pmxF;
	int pmz = (int)pmzF;
	//check whether pacman is caught
	if (x == pmx && z == pmz) 
	{
		return 1;//catch
	}
	return 0;
}

