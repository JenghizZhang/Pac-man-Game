source ./mesaSetup.sh
i. This code can run both on Windows and PACE-ICE. For Windows Visual Studio, nupengl.core need to be installed to run this program (like Lab 4).
   For PACE-ICE, mesa need to be setuped. Then, use g++ *.cpp -lGL -lglut -lGLU -lpthread -fopenmp to get a.out .
ii. Left, right, up, down arrow keys are to change pac-man's direction. Once the user presses these four keys, the game will start. 
   'R' and 'r' are to rotate the sight per 5 degrees. 
   'D' and 'd' are to set the ghosts to run away when the pac-man eats power-up, which is the default setting. It is impossible for the pac-man to eat ghosts in this setting because pac-man cannot catch them. 
   'S' and 's' are to set the ghosts to stand still when the pac-man eats power-up. Then, pac-man can catch ghosts.
   'ESC' is to exit the game.
iii.Video1.mp4 is for testing each key. Firstly, press 'r' to rotate the sight. Secondly, use left, right, up, down arrow keys to control the pac-man. Thirdly, after eating power-up, ghosts will run away, which is the defualt setting.
    Fourthly, press 's' to change the setting to stand still. Fifthly, after eating power-up, pac-man can catch ghosts(stand still) and ghosts need 5 seconds to respawn. Sixthly, the game will exit if pac-man dies 3 times.
    Seventhly, press 'd' to make the ghost run away after eating power-up. Eighthly, press 'ESC' to exit the game.
    Video2.mp4 is for testing that ghosts and pac-man can go thorough the left and right warp tunnels.
    Video3.mp4 is for testing if all of the coins and power-up are eaten, the game should win.
    