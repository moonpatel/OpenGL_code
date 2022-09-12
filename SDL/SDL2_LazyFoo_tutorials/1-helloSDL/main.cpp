#include <iostream>

#include <SDL2/SDL.h>

using namespace std;


int main() {
    // SDL is composed of eight subsystems - Audio, CDROM, Event Handling, File I/O, Joystick Handling,
    // Threading, Timers and Video
    // automatically initializes the Event Handling, File I/O and Threading subsystems 
    // and it takes a parameter specifying which other subsystems to initialize
    // SDL_Init(SDL_INIT_VIDEO);   // default subsystems like Event Handling, File I/O and Threading subsystems are
                                // initialised automatically along the one mentioned here that is video subsystem

    // to initialise the video and timers subsystem you can call and check for errors simultaneously
    // SDL_Init() returns -1 if it fails to initializer
    if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_TIMER)<0) {
        cout << "Could not initialize SDL: " << SDL_GetError() << "\n";     // SDL_GetError() gets the error description
        exit(-1);
    }

    // Initialisation was successful go ahead
    cout << "SDL was initialised" << "\n";


    cout << "Shutting down SDL" << "\n";


    SDL_Quit();     // exits all the activated subsysyems
                    // call just before an SDL program is terminated
    cout << "Quitting" << "\n";

    return 0;
}