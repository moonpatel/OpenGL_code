#include <iostream>

#include <SDL2/SDL.h>

using namespace std;

const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

int main() {
    // The window we will be referring to
    SDL_Window* window = NULL;

    // The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO)<0) {
        cout << "Error in SDL_Init() : " << SDL_GetError() << "\n";
        return 1;
    }
    else {
        // Create window
        window = SDL_CreateWindow("SDL Tutorials",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED
                                    ,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL) {
            cout << "Error in SDL_CreateWindow() : " << SDL_GetError() << "\n";
            SDL_Quit();
            return 1;
        }
        else {
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // fill the surface white
            SDL_FillRect(screenSurface,NULL,SDL_MapRGB(screenSurface->format,0xFF,0xFF,0xFF));

            // update the surface
            // each time something is drawn to the window update the window surface to show
            // the results
            SDL_UpdateWindowSurface(window);

            // wait two seconds
            SDL_Delay(2000);
        }
    }

    // destroy the window
    SDL_DestroyWindow(window);
    // quit SDL subsystems
    SDL_Quit();

    return 0;
}