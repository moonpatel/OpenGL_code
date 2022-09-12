// rendering some basic shapes
#include <iostream>
#include <string>

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
// Textures in SDL have their own data type intuitively called an SDL_Texture. When we deal 
// with SDL textures you need an SDL_Renderer to render it to the screen
SDL_Texture* loadTexture(string path);      //loads individual image as texture
SDL_Texture* currentTexture = NULL;     // currently displayed texture
SDL_Renderer* renderer = NULL;          // renderer that renders textures to the window

bool init();        // Initialize SDL and create a window
bool loadMedia();   // load the bmp image in the program
void close();       // deallocate all the allocated resources

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
        }
        // clear screen
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(renderer);

        // render red filled rectangle
        SDL_Rect fillRect{SCREEN_WIDTH/4,SCREEN_HEIGHT/4,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
        SDL_SetRenderDrawColor(renderer,0xFF,0x0,0x0,0xFF);
        SDL_RenderFillRect(renderer,&fillRect);
        
        // render a green rectangle outline
        SDL_Rect outlineRect{SCREEN_WIDTH/8,SCREEN_HEIGHT/6,SCREEN_WIDTH*3/4,SCREEN_HEIGHT*3/4};
        SDL_SetRenderDrawColor(renderer,0x0,0x0,0xFF,0xFF);
        SDL_RenderDrawRect(renderer,&outlineRect);

        // draw a horizontal line
        SDL_SetRenderDrawColor(renderer,0x0,0xFF,0x0,0xFF);
        SDL_RenderDrawLine(renderer,0,SCREEN_HEIGHT/2,SCREEN_WIDTH,SCREEN_HEIGHT/2);

        // draw a vertical dotted line
        SDL_SetRenderDrawColor(renderer,0x3F,0xF7,0xAA,0xFF);
        for(int i=0; i<SCREEN_HEIGHT; i+=3) {
            SDL_RenderDrawPoint(renderer,SCREEN_WIDTH/2,i);
        }

        // update the screen
        SDL_RenderPresent(renderer);
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
            // create a rendered for window 
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer==NULL) {
                cout << "Error in SDL_CreateRenderer(): " << SDL_GetError() << "\n";
                success = false;
            }
            else {
                // Initialize renderer colour
                SDL_SetRenderDrawColor(renderer,0xF2,0x3F,0xAF,0xFF);
                
                // Initialise PNG loading
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)) {
                    cout << "PNG image could not be loaded." << "\n";
                    cout << "Error in IMG_Init(): " << IMG_GetError() << "\n";
                    success = false;
                }
                else {
                    // get the window surface
                    screenSurface = SDL_GetWindowSurface(window);
                }
            }
        }
    }
    return success;
}
bool loadMedia() {
    bool success = true;        // loading success flag
    // we load no media 
    // SDL's primitive rendering allows you to render shapes without loading special graphics.
    return success;
}
void close() {
    // destroy the texture
    SDL_DestroyTexture(currentTexture);
    currentTexture = NULL;

    // destroy window
    // also takes care of the screen surface
    SDL_DestroyTexture(currentTexture);
    SDL_DestroyWindow(window);
    currentTexture = NULL;
    window = NULL;


    IMG_Quit();
    // Quit SDL subsystems
    SDL_Quit();
}
SDL_Texture* loadTexture(string path) {
    // the final texture
    SDL_Texture* newTexture = NULL;
    // load the image on a new surface
    SDL_Surface* loadedSurace = IMG_Load(path.c_str());
    if(loadedSurace==NULL)
        cout << "Error in IMG_Load(): " << SDL_GetError() << "\n";
    else {
        // create texture from new surface
        newTexture = SDL_CreateTextureFromSurface(renderer,loadedSurace);
        if(newTexture==NULL) {
            cout << "Error in creating texture from surface" << "\n";
            cout << "Error in SDL_CreateTextureFromSurface(): " << SDL_GetError() << "\n";
        }

        // free loadedSurface
        SDL_FreeSurface(loadedSurace);
    }
    return newTexture;
}