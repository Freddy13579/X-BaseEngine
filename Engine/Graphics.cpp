#include <iostream>

#include "include\SDL.h"
#include "include\SDL_image.h"

class Graphics{

    public:

    //Generate a Window and return its pointer back;
    SDL_Window* XCreate_Window(const char* title, int width, int height){
        SDL_Window *wind = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width,height, SDL_WINDOW_SHOWN);
        return wind;
    }

    //Generate renderer for a window. Renderer - needed for drawing
    SDL_Renderer* XCreate_Renderer(SDL_Window *wind){
        SDL_Renderer* rend = SDL_CreateRenderer(wind, -1,0);
        return rend;
    }

    //Clears the render of a window with a rgba color.
    void Xwindow_clear(SDL_Renderer *rend, int r, int g, int b, int a){

        SDL_SetRenderDrawColor(rend,r,g,b,a);
        SDL_RenderClear(rend);
        SDL_RenderPresent(rend);
    }

    //Destroys window (What did you expect?)
    void XDestroyWindow(SDL_Window *x){
        SDL_DestroyWindow(x);
    }

    void XdrawImage(SDL_Texture* img, SDL_Renderer *rend, SDL_Rect* srcRect, SDL_Rect* dstRect){

        SDL_RenderCopy(rend, img, NULL,dstRect);

    }

    SDL_Texture* XLoadTexture(const char *path, SDL_Renderer* rend){
        SDL_Surface* tmp = IMG_Load(path);

        SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(rend, tmp);
        SDL_FreeSurface(tmp);
    return loadedTexture;
    }

    void Xpaint(SDL_Renderer* rend){

        SDL_RenderPresent(rend);
    }
};