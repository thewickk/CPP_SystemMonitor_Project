# CppND-System-Monitor

### This is Project Two From the Udacity C++ Nanodegree Program [Udacity](https://www.udacity.com)

Starter code for System Monitor Project in the Object Oriented Programming Course of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 



## This project uses GCC 8 in order to take advantage of std::filesystem which is available in C++ 17 and is REQUIRED in order for this project to build. Below are the steps to install gcc 8+ on an Ubuntu 18.04 system and set it as the default:
* `sudo apt update -y`
* `sudo apt install gcc-8 g++-8`
* `sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 800 --slave /usr/bin/g++ g++ /usr/bin/g++8`

You can verify that gcc 8+ is now the version you system is using by running these commands:
* `sudo update-alternatives --display gcc`
* `gcc --version`

## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.


Install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions

1. Clone the project repository: `git@github.com:thewickk/CPP_SystemMonitor_Project.git`

2. Change into the dircetory: `cd CPP_SystemMonitor_Project` and build the project: `make build`

3. Run the resulting executable: `./build/monitor`
![Starting System Monitor](images/starting_monitor.png)

