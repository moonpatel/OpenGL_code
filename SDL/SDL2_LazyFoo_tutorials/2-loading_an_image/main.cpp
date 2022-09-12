#include <iostream>

#include <SDL2/SDL.h>

using namespace std;

const int SCREEN_WIDTH{640}, SCREEN_HEIGHT{480};    // Window dimensions
SDL_Window* window = NULL;          // window we ware rendering to
SDL_Surface* screenSurface = NULL;   // surface contained by the window
SDL_Surface* imageSurface = NULL;   // image surface we will load and show on screen

bool init();        // Initialize SDL and create a window
bool loadMedia();   // load the bmp image in the program
void close();       // deallocate all the allocated resources

int main() {
    // start SDL and create window
    if(!init())  {
        cout << "Failed to initialize" << "\n";
        return 1;
    }
    else {
        // load media
        if(!loadMedia()) {
            cout << "Failed to load media" << "\n";
            return 1;
        }
        else {
            // apply the imageSurface on the screenSurface
            SDL_BlitSurface(imageSurface,NULL,screenSurface,NULL);
            // update the surface so the modified screenSurface is now visible on the screen
            SDL_UpdateWindowSurface(window);
            // wait 1 second
            SDL_Delay(1000);
        }
    }

    // free resources and close SDL
    close();

    return 0;
}

bool init() {
    bool success = true;        // Initialization flag

    // initialize window and check for errors
    if(SDL_Init(SDL_INIT_VIDEO)<0) {
        cout << "SDL could not initialized" << "\n" << 
                "Error in SDL_Init(): " << SDL_GetError() << "\n";
        success = false;
    }
    else {
        // create the window
        window = SDL_CreateWindow("SDL Tutorial",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window == NULL) {
            cout << "Error in SDL_CreateWindow() : " << SDL_GetError() << "\n";
            success = false;
        }
        else {
            // get the window surface
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}
bool loadMedia() {
    bool success = true;        // loading success flag

    // Load the bmp image
    imageSurface = SDL_LoadBMP("/home/moon/Downloads/sample.bmp");
    if(imageSurface==NULL) {
        cout << "Error in SDL_LoadBMP() : " << SDL_GetError() << "\n";
        success = false;
    }
    else
        return success;
}
void close() {
    // deallocate surface
    SDL_FreeSurface(imageSurface);
    imageSurface = NULL;

    // destroy window
    // also takes care of the screen surface
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}