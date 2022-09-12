// Color modulation allows you to alter the color of your rendered textures. Here we're 
// going to modulate a texture using various colors.

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

            Uint8 r{255};
            Uint8 g{255};
            Uint8 b{255};

            while(!quit) {
                while(SDL_PollEvent(&e)!=0) {
                    if(e.type==SDL_QUIT) {
                        quit = true;
                    }
                    else if(e.type==SDL_KEYDOWN) {
                        switch(e.key.keysym.sym) {
                            case SDLK_q:
                                r += 16;
                                break;
                            case SDLK_w:
                                g += 16;
                                break;
                            case SDLK_e:
                                b += 16;
                                break;
                            case SDLK_a:
                                r -= 16;
                                break;
                            case SDLK_s:
                                g -= 16;
                                break;
                            case SDLK_d:
                                b -= 16;
                                break;
                        }
                    }
                }
                SDL_RenderClear(renderer);
                myTex.setColor(r,g,b);
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
