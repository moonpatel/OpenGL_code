// Sometimes you only want to render part of a texture. A lot of times games like to keep multiple 
// images on the same sprite sheet as opposed to having a bunch of textures. Using clip rendering, 
// we can define a portion of the texture to render as opposed to rendering the whole thing.

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture.h"

const int SCREEN_WIDTH{640};
const int SCREEN_HEIGHT{480};

using namespace std;

SDL_Window* window = NULL;      // window we are rendering to 
SDL_Renderer* renderer = NULL;  // the renderer for the window

// screen sprites
SDL_Rect spriteClips[4];
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

            while(!quit) {
                while(SDL_PollEvent(&e)!=0) {
                    if(e.type==SDL_QUIT) {
                        quit = true;
                    }
                }

                // clear screen
                SDL_RenderClear(renderer);
                // render sprites
                spriteSheetTexture.render(0,0,&spriteClips[0]);
                spriteSheetTexture.render(SCREEN_WIDTH-spriteClips[1].w,0,&spriteClips[1]);
                spriteSheetTexture.render(0,SCREEN_HEIGHT-spriteClips[2].h,&spriteClips[2]);
                spriteSheetTexture.render(SCREEN_WIDTH-spriteClips[3].w,SCREEN_HEIGHT-spriteClips[3].h,&spriteClips[3]);

                // update screen
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
    if(!spriteSheetTexture.loadFromFile("textures/dots.png")) {
        cout << "Could not load texture\n";
        success = false;
    }
    else {
        int width{},height{};
        width = spriteSheetTexture.getWidth()/2;
        height = spriteSheetTexture.getHeight()/2;
        spriteClips[0]=SDL_Rect{0,0,width,height};
        spriteClips[1]=SDL_Rect{width,0,width,height};
        spriteClips[2]=SDL_Rect{0,height,width,height};
        spriteClips[3]=SDL_Rect{width,height,width,height};
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
