# CppND-System-Monitor

### This is Project Two From the Udacity C++ Nanodegree Program [Udacity](https://www.udacity.com)

Starter code for System Monitor Project in the Object Oriented Programming Course of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 



### This project uses GCC 8 in order to take advantage of std::filesystem which is available in C++ 17 and is REQUIRED in order for this project to build. 
### Below are the steps I used to successfully build and run the project using the Workspace provided by Udacity:
* - Enable the GPU in the Udacity Workspace and clicke the "GO TO DESKTOP" button to launch the Project Workspace GUI
* - Launch the terminal avialiable on the Desktop
* - If desired change to the /home/workspace directory, but you can clone the project wherever you choose
* - Clone the project: `git clone https://github.com/thewickk/CPP_SystemMonitor_Project.git`
* - Install GCC/G++ v8+
* - `sudo add-apt-repository ppa:ubuntu-toolchain-r/test`
* - Hit **Enter** to accept the repository and GPG Key
* - `sudo apt-get update`
* - `sudo apt-get install gcc-8 g++-8`
* - `sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 800 --slave /usr/bin/g++ g++ /usr/bin/g++-8`
* - GCC and G++ 8 should now be installed and set to default. You can verify with the following command:
* - `gcc --version`

## Build and Run the Program

1. Change into the repository directory: `cd CPP_SystemMonitor_Project.git`

2. Build the project: `make builde`

3. Launch the application: `./build/monitor`


## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.


Install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts


