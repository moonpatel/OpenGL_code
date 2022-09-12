#include <iostream>
#include <SDL2/SDL_image.h>
#include "texture.h"

extern SDL_Renderer* renderer;

texture::texture()
    : tex{nullptr}, width{0}, height{0} {}

texture::~texture() {
    // deallocate
    free();
}

bool texture::loadFromFile(std::string path) {
    // get rid of existing textures
    free();

    // the final texture
    SDL_Texture* newTexture = NULL;
    // load image at specified path
    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    if(tempSurface==NULL) {
        std::cout << "Could not load image at " << path << "\n";
        std::cout << "Error in IMG_Load(): " << SDL_GetError() << "\n";
    }
    else {
        // color key image i.e. set which color pixel is treated as transparent
        SDL_SetColorKey(tempSurface,SDL_TRUE,SDL_MapRGB(tempSurface->format,0x0,0x0,0x0));

        newTexture = SDL_CreateTextureFromSurface(renderer,tempSurface);
        if(newTexture==NULL) {
            std::cout << "Could not create texture from surface\n";
            std::cout << "Error in SDL_CreateTextureFromSurface(): " << SDL_GetError() << "\n";
        }
        else {
            // get image dimensions
            width = tempSurface->w;
            height = tempSurface->h;
        }

        // get rid of the surface
        SDL_free(tempSurface);
    }

    tex = newTexture;
    return tex!=NULL;
}

// deallocate textures if there are any
void texture::free() {
    if(tex!=NULL) {
        SDL_DestroyTexture(tex);
        width = 0;
        height = 0;
    }
}

void texture::render(int x, int y) {
    // render the texture in the window
    SDL_Rect renderRect{x,y,width,height};
    SDL_RenderCopy(renderer,tex,NULL,&renderRect);
}

int texture::getWidth() {
    return width;
}

int texture::getHeight() {
    return height;
}