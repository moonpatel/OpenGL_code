// One way to render text with SDL is with the extension library SDL_ttf. SDL_ttf allows you to create 
// images from TrueType fonts which we'll use here to create textures from font text.


#include <iostream>
#include <string>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "texture.h"

const int SCREEN_WIDTH{640};
const int SCREEN_HEIGHT{480};

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
texture textTexture;

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
                SDL_RenderClear(renderer);

                textTexture.render((SCREEN_WIDTH-textTexture.getWidth())/2,(SCREEN_HEIGHT-textTexture.getHeight())/2);

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
                    cout << "Error in IMG_Init(): " << IMG_GetError() << "\n";
                    success = false;
                }

                if(!TTF_Init()<0) {
                    cout << "SDL_ttf could not be initialised!\n";
                    cout << "Error in TTF_Init(): " << TTF_GetError() << "\n";
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

    // load font from the given path
    font = TTF_OpenFont("fonts/sample.ttf",27);
    if(font == NULL) {
        cout << "Could not open font at fonts/sample.ttf\n";
        cout << TTF_GetError() << "\n";
        success = false;
    }
    else {
        SDL_Color textColor = {255,255,255};
        if(!textTexture.loadFromRenderedText("WELCOME! test render",textColor)) {
            cout << "Could not render text\n";
            success = false;
        }
    }

    return success;
}

void close() {
    // free the textures
    textTexture.free();
    TTF_CloseFont(font);
    font = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}