/*
Description:
This program is to draw the 3-D Pacman game using glut.By using the header files, it can build
all stuff in the game.It contains the logic function to run the game. It also enables lighting,
smooth, and depth. By pressing 'r' or 'R', the maze can be rotated clockwise by 5 degrees each
time the key is pressed. By pressing 's' or 'S',the ghost motion is set to stand still after the pacman
eats the power up. By pressing 'd' or 'D',the ghost motion is set to running away after the pacman
eats the power up. By pressing 'ESC', we can exit the program. By pressing left, right, up, down
arrow keys, we can control the pacman motion. Each ghost runs in it's own thread and they use the
shortest path algorithm to track pacman. The pacman motion and the main logic run in the main thread.
The rules are listed below:
1. The game starts as soon as the user presses any key.
2. The game ends when all the coins and powerup are consumed or pac-man dies three times.
3. When pac-man dies he and the ghosts are placed back at their starting locations.
4. When a ghost dies it must wait ~5 seconds to be respawned in the ghost home location.
5. Only one ghost every ~2 seconds can be released from the ghost home location.
6. Once pac-man consumes a power up he can kill ghosts for ~5 seconds. Change ghost color to white to
   indicate condition and then back to normal color. Ghosts should run away from pac-man during this
   time.
*/
#include <iostream>  
#include <GL/glut.h> //glut library
#include "mazeCoinPowerup.h"
#include "ECE_Pacman.h"
#include "ECE_Ghost.h"
#include <chrono>    // std::chrono::milliseconds
#include <thread>
#include <omp.h>
#include <mutex>
#define ESC 27

using namespace std;

int angle = 30; //set the initial angle for rotation
mazeCoinPowerup mazeNum1; //the maze
ECE_Pacman pacman; //the pacman
ECE_Ghost ghostRed, ghostGreen, ghostPink, ghostOrange; //four ghosts
//pacmanDirection is for hold the last direction of pacman if the new command motion causes it move to the wall
int pacmanDirection = -1; //set the initial moveing direction of pacman as -1 which means the pacman cannot move
//pacmanDirectionNew is for the available direction of pacman
int pacmanDirectionNew = -1; //set the initial moveing direction of pacman as -1 which means the pacman cannot move
//get the main thread ID
std::thread::id main_thread_id = std::this_thread::get_id();
//set the start time (release each ghost) to a very large value
double start_time=99999999;
//set the power up time (5 seconds after eatting power up) to a very large value
double powerUpTime = 99999999;
//set the red eaten time (ghost need 5 seconds to respawn) to a very large value
double redEatenTime = 99999999;
//set the green eaten time (ghost need 5 seconds to respawn) to a very large value
double greenEatenTime = 99999999;
//set the pink eaten time (ghost need 5 seconds to respawn) to a very large value
double pinkEatenTime = 99999999;
//set the orange eaten time (ghost need 5 seconds to respawn) to a very large value
double orangeEatenTime = 99999999;
//contain the state whether each ghost is eaten by the pacman after eatting power up
bool redRestart = 0;
bool greenRestart = 0;
bool pinkRestart = 0;
bool orangeRestart = 0;
//each thread is for moving the corresponding ghost
thread red, green, pink, orange;
//set the state of whether the ghost is relased from the ghost home
int redNum = 0, greenNum = 0, pinkNum = 0, orangeNum = 0;
//set the state of whether the game begins(we need to record the begin time) 
int timeNum = 0;
//set the state of the pacman eats power up
bool eatPowerUp = 0;
//set the die number for ending the game
int dieNum = 3;
//set whether the ghost is stand still for running away after pacman eats power up
bool ghostMotion = 0;
//this function is to reset all the values after pacman is eaten by the ghost
void restart(void) 
{
    pacmanDirection = -1;
    pacmanDirectionNew = -1;
    start_time = 99999999;
    powerUpTime = 99999999;
    redEatenTime = 99999999;
    greenEatenTime = 99999999;
    pinkEatenTime = 99999999;
    orangeEatenTime = 99999999;
    redRestart = 0;
    greenRestart = 0;
    pinkRestart = 0;
    orangeRestart = 0;
    redNum = 0;
    greenNum = 0;
    pinkNum = 0;
    orangeNum = 0;
    timeNum = 0;
    ghostRed.xRed = 0.0f;
    ghostRed.zRed = -1.4f;
    ghostRed.direction = 1;
    ghostGreen.xGreen = -1.0f;
    ghostGreen.zGreen = -0.5f;
    ghostGreen.direction = 1;
    ghostPink.xPink = 0.0f;
    ghostPink.zPink = -0.5f;
    ghostPink.direction = 1;
    ghostOrange.xOrange = 1.0f;
    ghostOrange.zOrange = -0.5f;
    ghostOrange.direction = 1;
    pacman.xPacman = 0;
    pacman.zPacman = 5;
}
//this function is to start and move the red ghost using the shortest path algorithm (using thread to call the function)
void redMove(void) 
{
    //release only once
    if (redNum == 0) //release the ghost
    {
        ghostRed.xRed = 0;
        ghostRed.zRed = -2;
        ghostRed.direction = 0;
        redNum++;
    }
    else 
    {
        ghostRed.move(ghostRed.xRed, ghostRed.zRed, pacman.xPacman, pacman.zPacman, 0);//move the ghost using shortest path algorithm
    }
    glutPostRedisplay();
}
//this function is to start and move the green ghost using the shortest path algorithm (using thread to call the function)
void greenMove(void)
{
    if (((omp_get_wtime() - start_time) >= 2 && powerUpTime == 99999999) || ((omp_get_wtime() - start_time) >= 7))//release the ghost after 2 second or after the power up time
    {
        if (greenNum == 0)//release only once
        {
            ghostGreen.xGreen = 0;
            ghostGreen.zGreen = -2;
            ghostGreen.direction = 0;
            greenNum++;
        }
        else
        {
            ghostGreen.move(ghostGreen.xGreen, ghostGreen.zGreen, pacman.xPacman, pacman.zPacman, 1);//move the ghost using shortest path algorithm
        }
    }
    glutPostRedisplay();
}
//this function is to start and move the pink ghost using the shortest path algorithm (using thread to call the function)
void pinkMove(void)
{
    if (((omp_get_wtime() - start_time) >= 4 && powerUpTime == 99999999) || ((omp_get_wtime() - start_time) >= 9))//release the ghost after 4 second or after the power up time
    {
        if (pinkNum == 0)//release only once
        {
            ghostPink.xPink = 0;
            ghostPink.zPink = -2;
            ghostPink.direction = 0;
            pinkNum++;
        }
        else
        {
            ghostPink.move(ghostPink.xPink, ghostPink.zPink, pacman.xPacman, pacman.zPacman, 2);//move the ghost using shortest path algorithm
        }
    }
    glutPostRedisplay();
}
//this function is to start and move the orange ghost using the shortest path algorithm (using thread to call the function)
void orangeMove(void)
{
    if (((omp_get_wtime() - start_time) >= 6 && powerUpTime == 99999999) || ((omp_get_wtime() - start_time) >= 11))//release the ghost after 6 second or after the power up time
    {
        if (orangeNum == 0)//release only once
        {
            ghostOrange.xOrange = 0;
            ghostOrange.zOrange = -2;
            ghostOrange.direction = 0;
            orangeNum++;
        }
        else
        {
            ghostOrange.move(ghostOrange.xOrange, ghostOrange.zOrange, pacman.xPacman, pacman.zPacman, 3);//move the ghost using shortest path algorithm
        }
    }
    glutPostRedisplay();
}
//this function is to initialize endThread (join all the thread)
void endThread(void);
//run away from the pacman if it eats power up (using thread to call the function)
void ghostRedRunAway(void) 
{
    ghostRed.runAway(ghostRed.xRed, ghostRed.zRed, pacman.xPacman, pacman.zPacman, 0);
}
//run away from the pacman if it eats power up (using thread to call the function)
void ghostGreenRunAway(void) 
{
    ghostGreen.runAway(ghostGreen.xGreen, ghostGreen.zGreen, pacman.xPacman, pacman.zPacman, 1);
}
//run away from the pacman if it eats power up (using thread to call the function)
void ghostPinkRunAway(void) 
{
    ghostPink.runAway(ghostPink.xPink, ghostPink.zPink, pacman.xPacman, pacman.zPacman, 2);
}
//run away from the pacman if it eats power up (using thread to call the function)
void ghostOrangeRunAway(void) 
{
    ghostOrange.runAway(ghostOrange.xOrange, ghostOrange.zOrange, pacman.xPacman, pacman.zPacman, 3);
}
//set the initialization for drawing objects (lighting, depth, and smooth)
void init(void)
{
    glShadeModel(GL_SMOOTH); //render objects smoothly
    glEnable(GL_DEPTH_TEST); //enable depth
    glEnable(GL_COLOR_MATERIAL); //using the color of the objects as the material color
    glEnable(GL_LIGHTING); //enable lighting
    glEnable(GL_LIGHT0); //using light0
}
// redisplay everything (the pacman motion, the ghost motion, coin state, and power up state)
void update(void) 
{
    //check if the new input direction will make pacman moves to the wall
    if (pacman.directionCheck(pacmanDirection) == 0)
    {
        //if not transfer the value to the direction of pacman
        pacmanDirectionNew = pacmanDirection;
    }
    //change the direction of pacman based on the input
    switch (pacmanDirectionNew)
        {
        case 0: //up
            pacman.move(0);
            break;
        case 1: //down
            pacman.move(1);
            break;
        case 2: //left
            pacman.move(2);
            break;
        case 3: //right
            pacman.move(3);
            break;
        }
    
    if (eatPowerUp == 0)//if pacman dose not eat power up
    {
        if (pacmanDirection != -1) //check whether the user press a key
        {
            red = thread(redMove); //move red ghost
            green = thread(greenMove); //move green ghost
            pink = thread(pinkMove); //move pink ghost
            orange = thread(orangeMove); //move orange ghost
            if (timeNum == 0) //check whether the game starts
            {
                timeNum++;
                start_time = omp_get_wtime(); //record the time
            }
            endThread(); //end all thread
        }
    }
    else //if pacman eats power up
    {
        if (ghostMotion == 0)//if ghost need to run away after pacman eats power up
        {
            red = thread(ghostRedRunAway);//red ghost run away
            green = thread(ghostGreenRunAway);//green ghost run away
            pink = thread(ghostPinkRunAway);//pink ghost run away
            orange = thread(ghostOrangeRunAway);//orange ghost run away
            endThread();//end all thread
        }
    }
    mazeNum1.checkCoin(pacman.xPacman, pacman.zPacman);//check the coin state
    if (mazeNum1.checkPower(pacman.xPacman, pacman.zPacman) == 0)//check the power up state
    {
        eatPowerUp = 1;
        powerUpTime = omp_get_wtime();//record the power up time
        ghostRed.powerUp = 1;
        ghostGreen.powerUp = 1;
        ghostPink.powerUp = 1;
        ghostOrange.powerUp = 1;
    }
    if ((omp_get_wtime() - powerUpTime) >= 5) //if the power up time is greater than 5 seconds
    {
        //power up state stop
        eatPowerUp = 0;
        ghostRed.powerUp = 0;
        ghostGreen.powerUp = 0;
        ghostPink.powerUp = 0;
        ghostOrange.powerUp = 0;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(300));//sleep the main thread for 0.3 second
    glutPostRedisplay();
}
//draw all of the objects in the maze and it lighting, check whether ghost eats pacman or pacman eats ghost, set the respawn state of each ghost
void display(void) 
{
    glClearColor(0.0, 0.0, 0.0, 0.0);// black background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear color and depth buffers

    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 0.0 };//set the light diffuse property (RGB)
    GLfloat light_position[] = { 15.0, 15.0, 15.0, 0.0 }; //set the position of the light with alpha is 0 which means parallel

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);//set the light diffuse property (RGB)
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);//set the position

    glPushMatrix();
        glRotatef((GLfloat)angle, 0.0, 1.0, 0.0);//rotate the maze along y axis based on the rotation angle
        glPushMatrix();
            mazeNum1.draw(1); //draw the maze coin and power up
            pacman.draw(); //draw the pacman
            ghostRed.drawRed(); //draw the red ghost
            ghostGreen.drawGreen(); //draw the green ghost
            ghostPink.drawPink(); //draw the pink ghost
            ghostOrange.drawOrange(); //draw the orange ghost
        glPopMatrix();
    glPopMatrix();
    
    if (eatPowerUp == 0) //if not eat power up
    {
        if ((ghostRed.catchPacman(ghostRed.xRed, ghostRed.zRed, pacman.xPacman, pacman.zPacman) == 1))//The red ghost catches pacman and restart the game
        {
            cout << "The red ghost catches you" << endl;
            dieNum--;
            restart();
        }
        if ((ghostGreen.catchPacman(ghostGreen.xGreen, ghostGreen.zGreen, pacman.xPacman, pacman.zPacman) == 1))//The green ghost catches pacman and restart the game
        {
            cout << "The green ghost catches you" << endl;
            dieNum--;
            restart();
        }
        if ((ghostPink.catchPacman(ghostPink.xPink, ghostPink.zPink, pacman.xPacman, pacman.zPacman) == 1))//The pink ghost catches pacman and restart the game
        {
            cout << "The pink ghost catches you" << endl;
            dieNum--;
            restart();
        }
        if ((ghostOrange.catchPacman(ghostOrange.xOrange, ghostOrange.zOrange, pacman.xPacman, pacman.zPacman) == 1))//The orange ghost catches pacman and restart the game
        {
            cout << "The orange ghost catches you" << endl;
            dieNum--;
            restart();
        }
    }
    else //if eat power up
    {
        if ((ghostRed.catchPacman(ghostRed.xRed, ghostRed.zRed, pacman.xPacman, pacman.zPacman) == 1)) //red ghost is eaten and set its time and position
        {
            ghostRed.xRed = 0.0f;
            ghostRed.zRed = -1.4f;
            ghostRed.direction = 1;
            redEatenTime = omp_get_wtime();
            redRestart = 0;
        }
        if ((ghostGreen.catchPacman(ghostGreen.xGreen, ghostGreen.zGreen, pacman.xPacman, pacman.zPacman) == 1))//green ghost is eaten and set its time and position
        {
            ghostGreen.xGreen = -1.0f;
            ghostGreen.zGreen = -0.5f;
            ghostGreen.direction = 1;
            greenEatenTime = omp_get_wtime();
            greenRestart = 0;
        }
        if ((ghostPink.catchPacman(ghostPink.xPink, ghostPink.zPink, pacman.xPacman, pacman.zPacman) == 1))//pink ghost is eaten and set its time and position
        {
            ghostPink.xPink = 0.0f;
            ghostPink.zPink = -0.5f;
            ghostPink.direction = 1;
            pinkEatenTime = omp_get_wtime();
            pinkRestart = 0;
        }
        if ((ghostOrange.catchPacman(ghostOrange.xOrange, ghostOrange.zOrange, pacman.xPacman, pacman.zPacman) == 1))//orange ghost is eaten and set its time and position
        {
            ghostOrange.xOrange = 1.0f;
            ghostOrange.zOrange = -0.5f;
            ghostOrange.direction = 1;
            orangeEatenTime = omp_get_wtime();
            orangeRestart = 0;
        }
    }
    if (((omp_get_wtime() - redEatenTime) >= 5)&& redRestart == 0)//check red ghost respawn time and set its position
    {
        ghostRed.xRed = 0;
        ghostRed.zRed = -2;
        ghostRed.direction = 0;
        redRestart = 1;
    }
    if (((omp_get_wtime() - greenEatenTime) >= 5) && greenRestart == 0)//check green ghost respawn time and set its position
    {
        ghostGreen.xGreen = 0;
        ghostGreen.zGreen = -2;
        ghostGreen.direction = 0;
        greenRestart = 1;
    }
    if (((omp_get_wtime() - pinkEatenTime) >= 5) && pinkRestart == 0)//check pink ghost respawn time and set its position
    {
        ghostPink.xPink = 0;
        ghostPink.zPink = -2;
        ghostPink.direction = 0;
        pinkRestart = 1;
    }
    if (((omp_get_wtime() - orangeEatenTime) >= 5) && orangeRestart == 0)//check orange ghost respawn time and set its position
    {
        ghostOrange.xOrange = 0;
        ghostOrange.zOrange = -2;
        ghostOrange.direction = 0;
        orangeRestart = 1;
    }
    glutSwapBuffers(); //swap buffers
    if (mazeNum1.checkWin() == 1) //check whether user wins the game
    {
        cout << "YOU WIN!!!!!" << endl;
        exit(0);
    }
    if (dieNum == 0) //check whether user loses the game
    {
        cout << "Sorry you lose" << endl;
        exit(0);
    }
}
// Reshape callback, and set the loot at point of the camera
void reshape(int w, int h)// Reshape callback, and set the loot at point of the camera
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // set viewport (drawing area) to entire window
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    //(float)w / (float)h is window aspect ratio
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glLoadIdentity(); // Reset transformations
    gluLookAt(15.5, 20.0, 15.0, 0.0, 0.0, -0.5, 0.0, 1.0, 0.0); // Set the camera
}
//when entering 'r' or 'R', rotate the maze
//when entering 's' or 'S', the ghost motion is set to stand still after eating the power up
//when entering 'd' or 'D', the ghost motion is set to running away after eating the power up
//when entering 'ESC', exit the game
void keyboard(unsigned char key, int x, int y) //when entering 'r' or 'R', rotate the maze
{
    switch (key) {
    case 'r':
    case 'R':
        angle = (angle - 5) % 360; //rotate the maze clockwise per 5 degree
        glutPostRedisplay(); //redisplay the maze
        break;
    case 's':
    case 'S':
        ghostMotion = 1;
        cout << "The ghost motion is set to standing still after eating the power up" << endl;
        break;
    case 'd':
    case 'D':
        ghostMotion = 0;
        cout << "The ghost motion is set to running away after eating the power up" << endl;
        break;
    case ESC: //set the ESC key
        exit(0);
        break;
    default:
        break;
    }
}
//record the user command to move the pacman
void pressSpecialKey(int key, int x, int y) 
{
    switch (key)
    {
    case GLUT_KEY_UP:
        pacmanDirection = 0;//up
        break;
    case GLUT_KEY_DOWN:
        pacmanDirection = 1;//down
        break;
    case GLUT_KEY_LEFT:
        pacmanDirection = 2;//left
        break;
    case GLUT_KEY_RIGHT:
        pacmanDirection = 3;//right
        break;
    }
}
//this function is to join all the thread
void endThread(void)
{
    red.join();
    green.join();
    pink.join();
    orange.join();
}
//set the drawing loop and its corresponding function
int main(int argc, char** argv)
{
    // general initializations
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB); //set mode with depth, double, and rgb
    glutInitWindowSize(500, 500); //set the window size
    glutInitWindowPosition(100, 100); //set the window position
    glutCreateWindow("3-D PacMan Maze"); //set the name of the window
    init(); // initialization
    glutIdleFunc(update); // incremental update
    glutDisplayFunc(display); // (re)display callback
    glutReshapeFunc(reshape); // window reshape callback
    glutKeyboardFunc(keyboard); // keyboard function callback
    glutSpecialFunc(pressSpecialKey);
    glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
    glutMainLoop();
    return 0;
}