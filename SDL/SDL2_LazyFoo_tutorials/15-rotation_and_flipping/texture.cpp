// SDL 2's hardware accelerated texture rendering also gives ability to give us
// fast image flipping and rotation. In this tutorial we'll be using this to make
// an arrow texture spin and flip.

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

// set color modulation
void texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    // modulate texture
    SDL_SetTextureColorMod(tex,red,green,blue);
}

void texture::render(int x, int y, SDL_Rect* clip=NULL, double rotation_angle=0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
    // set the space on window for rendering
    SDL_Rect renderQuad{x,y,width,height};

    // set clip rendering dimensions
    if(clip!=NULL) {
        renderQuad.w=clip->w;
        renderQuad.h=clip->h;
    }

    // render to screen
    SDL_RenderCopyEx(renderer,tex,clip,&renderQuad,rotation_angle,center,flip);
}

void texture::setBlendMode(SDL_BlendMode blending) {
    // set blending function
    SDL_SetTextureBlendMode(tex,blending);    
}

void texture::setAlpha(Uint8 alpha) {
    // modulate texture alpha
    SDL_SetTextureAlphaMod(tex,alpha);
}

int texture::getWidth() {
    return width;
}

int texture::getHeight() {
    return height;
}