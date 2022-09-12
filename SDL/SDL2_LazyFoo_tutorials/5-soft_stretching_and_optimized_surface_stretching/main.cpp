// Another type of input used heavily in games is the keyboard. In this tutorial we're 
// going to make different images appear depending on which key you press.
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;
// Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
const int SCREEN_WIDTH{640}, SCREEN_HEIGHT{480};
SDL_Window* window = NULL;          // window we ware rendering to
SDL_Surface* screenSurface = NULL;   // surface contained by the window
SDL_Surface* KeyPressSurfacesArray[KEY_PRESS_SURFACE_TOTAL];    // images corresponding to a key press
SDL_Surface* currentSurface = NULL;     // current displayed image



bool init();        // Initialize SDL and create a window
bool loadMedia();   // load the bmp image in the program
void close();       // deallocate all the allocated resources
SDL_Surface* loadSurface(string path);  // Loads individual image


int main() {
    bool quit = false;      // main loop quit flag
    SDL_Event e;            // event handler
    SDL_Rect stretchRect;
    stretchRect.x=0;
    stretchRect.y=0;
    stretchRect.w=SCREEN_WIDTH;
    stretchRect.h=SCREEN_HEIGHT;

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
    }

    currentSurface = KeyPressSurfacesArray[KEY_PRESS_SURFACE_DEFAULT];

    // while the application is running
    while(!quit) {
        // handle the events on queue
        while(SDL_PollEvent(&e)!=0) {
            // user requests quit
            // SDL_QUIT event is when the user presses X button on the window
            if(e.type==SDL_QUIT) {
                quit = true;
            }
            // user presses a key
            // the SDL_KEYDOWN corresponds to the keyboard key press event
            else if(e.type == SDL_KEYDOWN) {
                // Select surfaces based on key presses
                switch(e.key.keysym.sym) {
                    case SDLK_UP:
                        currentSurface = KeyPressSurfacesArray[KEY_PRESS_SURFACE_UP];
                        break;
                    case SDLK_DOWN:
                        currentSurface = KeyPressSurfacesArray[KEY_PRESS_SURFACE_DOWN];
                        break;
                    case SDLK_LEFT:
                        currentSurface = KeyPressSurfacesArray[KEY_PRESS_SURFACE_LEFT];
                        break;
                    case SDLK_RIGHT:
                        currentSurface = KeyPressSurfacesArray[KEY_PRESS_SURFACE_RIGHT];
                        break;
                    default:
                        currentSurface = KeyPressSurfacesArray[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                }
            }
            // Apply the image
            SDL_BlitScaled(currentSurface,NULL,screenSurface,&stretchRect);

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

    // load default surface
    KeyPressSurfacesArray[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("/home/moon/Downloads/sample.bmp");
    if(KeyPressSurfacesArray[KEY_PRESS_SURFACE_DEFAULT]==NULL) {
        cout << "Failed to load bmp image\n";
        success = false;
    }

    // load up surface
    KeyPressSurfacesArray[KEY_PRESS_SURFACE_UP] = loadSurface("key_press/up.bmp");
    if(KeyPressSurfacesArray[KEY_PRESS_SURFACE_UP]==NULL) {
        cout << "Failed to load bmp image\n";
        success = false;
    }

    // load down surface
    KeyPressSurfacesArray[KEY_PRESS_SURFACE_DOWN] = loadSurface("key_press/down.bmp");
    if(KeyPressSurfacesArray[KEY_PRESS_SURFACE_DOWN]==NULL) {
        cout << "Failed to load bmp image\n";
        success = false;
    }

    // load left surface
    KeyPressSurfacesArray[KEY_PRESS_SURFACE_LEFT] = loadSurface("key_press/left.bmp");
    if(KeyPressSurfacesArray[KEY_PRESS_SURFACE_LEFT]==NULL) {
        cout << "Failed to load bmp image\n";
        success = false;
    }

    // load right surface
    KeyPressSurfacesArray[KEY_PRESS_SURFACE_RIGHT] = loadSurface("key_press/right.bmp");
    if(KeyPressSurfacesArray[KEY_PRESS_SURFACE_RIGHT]==NULL) {
        cout << "Failed to load bmp image\n";
        success = false;
    }

    return success;
}
void close() {
    // deallocate surface
    SDL_FreeSurface(currentSurface);
    currentSurface = NULL;

    // destroy window
    // also takes care of the screen surface
    SDL_DestroyWindow(window);
    window = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}
SDL_Surface* loadSurface(string path) {
    SDL_Surface* optimisedImage = NULL;
    // Load image at the specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface==NULL)
        cout << "Error in SDL_LoadBMP(): " << SDL_GetError() << "\n";
    else {
        // Convert surface to screen format
        optimisedImage = SDL_ConvertSurface(loadedSurface,screenSurface->format,0);
        if(optimisedImage==NULL) {
            cout << "Error in SDL_ConvertSurface(): " << SDL_GetError() << "\n";
        }
        // Free the previous image
        SDL_free(loadedSurface);
    }
    return optimisedImage;
}