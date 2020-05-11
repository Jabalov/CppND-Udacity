# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## File and Class Structure

There are 5 classes in My Submitted implementation.<br>

| class name | Purpose                                                                                                 |
| ---------- | ------------------------------------------------------------------------------------------------------- |
| Controller | Interact with users, let users use keyboard to control the snake in the game.                           |
| Game       | Game class stores the state in the game, the function object **run** has the game run in loops til end. |
| Renderer   | render the game to the screen.                                                                          |
| Snake      | contains attributes to keep track of the Snake speed, size, and location.                               |
| Logger     | Read, Write and print the history record for players.                                                   |

## Rubric Points 

1. The project demonstrates an understanding of C++ functions and control structures in all classes.
   
2. The project reads data from a file and process the data, or the program writes data to a file.
   
3. The project uses Object Oriented Programming techniques. The **Logger class** and **Other classes** are defined to improve the program.
   
5. Implemented a Monitor Object Pattern Class named Motivate, to send motivational warnings to the player using concepts i learned about like **like threads, shared pointers, locks, condition variables, mutex**.
   
