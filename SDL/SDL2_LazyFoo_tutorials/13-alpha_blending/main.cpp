// Thanks to new hardware accelerated rendering, transparency is muc faster in SDL2.0. Here we'll
// use alpha modulation (which works much like color modulation) to control the transparency of a 
// texture

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture.h"

const int SCREEN_WIDTH{640};
const int SCREEN_HEIGHT{480};

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
texture myTex;
texture backgroundTexture;

bool init();
bool loadMedia();
void close();


int main() {
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
            SDL_Event e;
            Uint8 a = 255;

            while(!quit) {
                while(SDL_PollEvent(&e)!=0) {
                    if(e.type==SDL_QUIT) {
                        quit = true;
                    }
                    else if(e.type==SDL_KEYDOWN) {
                        // increase alpha on w
                        if(e.key.keysym.sym==SDLK_w) {
                            if(a+32>255) {
                                a=255;
                            }
                            else {
                                a += 32;
                            }
                        }
                        else if(e.key.keysym.sym==SDLK_s) {
                            if(a-32<0) {
                                a=0;
                            }
                            else {
                                a-=32;
                            }
                        }
                    }
                }
                SDL_RenderClear(renderer);

                // render background
                backgroundTexture.render(0,0);
                // render front blended
                myTex.setAlpha(a);
                myTex.render(0,0);

                SDL_RenderPresent(renderer);
            }
        }
    }


    return 0;
}

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

bool loadMedia() {
    // success flag
    bool success = true;

    // load sprite sheet texture
    if(!myTex.loadFromFile("textures/sample.png")) {
        cout << "Could not load texture\n";
        success = false;
    }
    else {
        // set standard alpha blending
        myTex.setBlendMode(SDL_BLENDMODE_BLEND);
    }

    if(!backgroundTexture.loadFromFile("textures/background.png")) {
        cout << "Could not load texture background.png\n";
        success = false;
    }

    return success;
}

void close() {
    // free the textures
    myTex.free();

    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}