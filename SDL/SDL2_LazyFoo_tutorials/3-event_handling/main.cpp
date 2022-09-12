#include <iostream>

#include <SDL2/SDL.h>

using namespace std;

const int SCREEN_WIDTH{640}, SCREEN_HEIGHT{480};
SDL_Window* window = NULL;          // window we ware rendering to
SDL_Surface* screenSurface = NULL;   // surface contained by the window
SDL_Surface* imageSurface = NULL;   // image surface we will load and show on screen

bool init();        // Initialize SDL and create a window
bool loadMedia();   // load the bmp image in the program
void close();       // deallocate all the allocated resources

int main() {
    bool quit = false;      // main loop quit flag
    SDL_Event e;            // event handler

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
            // apply the image
            SDL_BlitSurface(imageSurface,NULL,screenSurface,NULL);
            // update the surface
            SDL_UpdateWindowSurface(window);
            // wait 1 seconds
            SDL_Delay(1000);
        }
    }

    // while the application is running
    while(!quit) {
        // handle events on queue
        // SDL_PollEvent takes the SDL_Event type's address as input and pass the most recent 
        // event (example: keyboard button press, mouse movement etc) in the
        // event queue that occured. If no recent events occured it returns 0
        while(SDL_PollEvent(&e)!=0) {
            // user requests quit
            // SDL_QUIT event is when the user presses X button on the window
            if(e.type==SDL_QUIT) {
                quit = true;
            }
            // Apply the image
            SDL_BlitSurface(imageSurface,NULL,screenSurface,NULL);

            // update the surface
            SDL_UpdateWindowSurface(window);
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