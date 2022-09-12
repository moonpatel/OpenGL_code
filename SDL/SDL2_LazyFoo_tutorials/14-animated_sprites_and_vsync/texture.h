#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <SDL2/SDL.h>
#include <string>

class texture {
public:
    texture();      // constructor
    ~texture();     // destructor

    bool loadFromFile(std::string path);    // load texture from the given path
    void render(int x, int y, SDL_Rect* clip=NULL);      // render to a given path
    void free();        // deallocate texture from free store
    void setColor(Uint8 red, Uint8 green, Uint8 blue);  // set color modulation
    void setBlendMode(SDL_BlendMode blending);      // set blending
    void setAlpha(Uint8 alpha);         // set alpha modulation

    // get texture dimensions
    int getWidth();
    int getHeight();
private:
    SDL_Texture* tex;
    int width;
    int height;    
};

#endif