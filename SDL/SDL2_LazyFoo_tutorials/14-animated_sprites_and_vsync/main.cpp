// Animation in a nutshell is just showing one image after another to create the illusion
// of motion. Here we'll be showing different sprites to animate a stick figure

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

// walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect spriteClips[WALKING_ANIMATION_FRAMES];
texture spriteSheetTexture;

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
            int frame=0;    // current animation frame

            while(!quit) {
                while(SDL_PollEvent(&e)!=0) {
                    if(e.type==SDL_QUIT) {
                        quit = true;
                    }
                }
                SDL_RenderClear(renderer);

                SDL_Rect* currentClip = &spriteClips[frame/8];
                spriteSheetTexture.render((SCREEN_WIDTH-currentClip->w)/2,(SCREEN_HEIGHT-currentClip->h)/2,currentClip);

                SDL_RenderPresent(renderer);

                frame++;
                if(frame/8>=WALKING_ANIMATION_FRAMES) {
                    frame=0;
                }
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
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
    if(!spriteSheetTexture.loadFromFile("textures/foo.png")) {
        cout << "Could not load texture\n";
        success = false;
    }
    else {
        // set sprite clips
        spriteClips[0] = SDL_Rect{0,0,64,205};
        spriteClips[1] = SDL_Rect{64,0,64,205};
        spriteClips[2] = SDL_Rect{128,0,64,205};
        spriteClips[3] = SDL_Rect{192,0,64,205};
    }

    return success;
}

void close() {
    // free the textures
    spriteSheetTexture.free();

    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}