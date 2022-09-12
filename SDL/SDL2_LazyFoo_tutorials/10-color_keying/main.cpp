// A major new addition to SDL 2 is the texture rendering API. This gives you fast,
// flexible hardware based rendering. In this tutorial we'll be using this new rendering technique.

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "texture.h"


using namespace std;


const int SCREEN_WIDTH{640}, SCREEN_HEIGHT{480};
SDL_Window* window = NULL;          // window we are rendering to
SDL_Renderer* renderer = NULL;          // renderer that renders textures to the window

// scene textures
texture fooTexture;
texture BGTexture;

// initialises library
bool init() {
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO)<0) {
        cout << "SDL could not be initialised!\n";
        cout << "Error in SDL_Init(): " << SDL_GetError() << "\n";
        success = false;
    }
    else {
        window = SDL_CreateWindow("SDL Tutorial",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window == NULL) {
            cout << "Window coud not be created!\n";
            cout << "Error in SDL_Create_Window(): " << SDL_GetError() << "\n";
            success = false;
        }
        else {
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer==NULL) {
                cout << "Renderer could not be created!\n";
                cout << "Error in SDL_CreateRendere(): " << SDL_GetError() << "\n";
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(renderer,0x0,0x0,0x0,0xFF);

                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags)) {
                    cout << "SDL_image could not be initialised!\n";
                    cout << "Error in IMG_Init(): " << SDL_GetError() << "\n";
                    success = false;
                }
            }
        }
    }

    return success;
}

// loads media
bool loadMedia() {
    bool success = true;

    if(!fooTexture.loadFromFile("textures/foo.png")) {
        cout << "Could not load foo texture!\n";
        success = false;
    }
    if(!BGTexture.loadFromFile("textures/background.png")) {
        cout << "Could not load background texture!\n";
        success = false;
    }

    return success;
}

void close() {
    // free the textures
    fooTexture.free();
    BGTexture.free();

    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main() {
    SDL_Event e;
    if(!init()) {
        cout << "Failed to initialise!\n";
        cout << SDL_GetError() << "\n";
        return 1;
    }
    else {
        if(!loadMedia()) {
            cout << "Failed to load media!\n" << SDL_GetError() << "\n";
            return 1;
        }
        else {
            bool quit = false;

            while(!quit) {
                while(SDL_PollEvent(&e)!=0) {
                    if(e.type==SDL_QUIT) {
                        quit = true;
                    }
                }
                SDL_SetRenderDrawColor(renderer,0x0,0x0,0x0,0xFF);
                SDL_RenderClear(renderer);

                BGTexture.render(0,0);
                fooTexture.render(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);

                SDL_RenderPresent(renderer);
            }
        }
    }
    close();

    return 0;
}