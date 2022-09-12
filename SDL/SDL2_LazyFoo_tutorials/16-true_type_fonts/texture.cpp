#include <iostream>
#include <SDL2/SDL_image.h>
#include "texture.h"

extern SDL_Renderer* renderer;
extern TTF_Font* font;

using std::cout;

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

bool texture::loadFromRenderedText(std::string textureText, SDL_Color textColor) {
    // free existing textures
    free();

    // render the text on a surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,textureText.c_str(),textColor);
    if(textSurface==NULL) {
        cout << "Could not render text\n";
        cout << TTF_GetError() << "\n";
        return false;
    }
    else {
        // create texture out of rendered text
        tex = SDL_CreateTextureFromSurface(renderer,textSurface);
        if(tex==NULL) {
            cout << "Could not create texture from surface\n";
            cout << SDL_GetError() << "\n";
            return false;
        }
        else {
            // get texture dimensions
            width = textSurface->w;
            height = textSurface->h;
        }
        // get rid of old surface
        SDL_free(textSurface);
    }

    // return success
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


void texture::render(int x, int y, SDL_Rect* clip, double rotation_angle, SDL_Point* center, SDL_RendererFlip flip) {
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