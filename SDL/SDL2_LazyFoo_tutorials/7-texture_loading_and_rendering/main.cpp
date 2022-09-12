// A major new addition to SDL 2 is the texture rendering API. This gives you fast,
// flexible hardware based rendering. In this tutorial we'll be using this new rendering technique.

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


using namespace std;


const int SCREEN_WIDTH{640}, SCREEN_HEIGHT{480};
SDL_Window* window = NULL;          // window we ware rendering to
// Textures in SDL have their own data type intuitively called an SDL_Texture. When we deal 
// with SDL textures you need an SDL_Renderer to render it to the screen
SDL_Texture* currentTexture = NULL;     // currently displayed texture
SDL_Renderer* renderer = NULL;          // renderer that renders textures to the window

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

SDL_Texture* loadTexture(string path) {
    SDL_Texture* finalTexture = NULL;

    // surface on which image is loaded
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface==NULL) {
        cout << "Could not load image." << "\n";
        cout << "Error in IMG_Load(): " << SDL_GetError() << "\n";
    }
    else {
        finalTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
        if(finalTexture==NULL) {
            cout << "Could not create texture from surface" << "\n";
            cout << "Error in SDL_CreateTextureFromSurface(): " << SDL_GetError() << "\n";
        }

        SDL_free(loadedSurface);
    }

    return finalTexture;
}

bool loadMedia() {
    bool success = true;

    currentTexture = loadTexture("textures/sample.png");
    if(currentTexture==NULL) {
        cout << "Could not load texture!\n";
        cout << "Error in loadTexture(): " << SDL_GetError() << "\n";
        success = false;
    }

    return success;
}

void close() {
    SDL_DestroyTexture(currentTexture);
    currentTexture = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}


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
                SDL_RenderCopy(renderer,currentTexture,NULL,NULL);
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();

    return 0;
}