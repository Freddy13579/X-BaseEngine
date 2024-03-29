#pragma once
#include <iostream>

#include "include\SDL.h"
#include "include\SDL_image.h"
#include "include\SDL_ttf.h"
#include <array>
#include <vector>

class Graphics{

    public:

    std::vector<SDL_Texture*> textureArray;

    SDL_Texture* screenTexture;

    //Generate a Window and return its pointer back;
    SDL_Window* Create_Window(const char* title, int width, int height, int flag){
        SDL_Window *wind = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width,height, flag);
        return wind;
    }

    //Generate renderer for a window. Renderer - needed for drawing
    SDL_Renderer* Create_Renderer(SDL_Window *wind){
        SDL_Renderer* rend = SDL_CreateRenderer(wind, -1,0);
        return rend;
    }


    //Generates surface -> texture -> return
    SDL_Texture* text_Texture(SDL_Renderer* Renderer, const char* Text, TTF_Font *Font, SDL_Color Color){
        if(Font == NULL){std::cout << "text_Texture Error: "<< TTF_GetError() << std::endl;}
        SDL_Surface* temp = TTF_RenderText_Solid(Font, Text, Color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, temp);
        if(texture == NULL){std::cout << "text_Texture Error: "<< SDL_GetError() << std::endl;}
        SDL_FreeSurface(temp);
        textureArray.push_back(texture);
        return texture;
    }

    void init_TTF(){
        TTF_Init();
    }

    //Clears the render of a window with a rgba color.
    void window_clear(SDL_Renderer *rend, int r, int g, int b, int a){

        SDL_SetRenderDrawColor(rend,r,g,b,a);
        SDL_RenderClear(rend);
    }

    //Destroys window (What did you expect?)
    void DestroyWindow(SDL_Window *x){
        SDL_DestroyWindow(x);
    }

    void drawTexture(SDL_Texture* img, SDL_Renderer *rend, SDL_Rect* srcRect, SDL_Rect* dstRect){
        Engine engine = Engine();
        SDL_Rect scaleRec;
        scaleRec.x = dstRect->x*engine.scale;
        scaleRec.y = dstRect->y*engine.scale;
        scaleRec.w = dstRect->w*engine.scale;
        scaleRec.h = dstRect->h*engine.scale;

        if (SDL_RenderCopy(rend, img, srcRect,&scaleRec) != 0){
            std::cout << "drawTexture Error: " << SDL_GetError() << std::endl;
        }

    }

    SDL_Texture* loadTexture(const char *path, SDL_Renderer* rend){
        SDL_Surface* tmp = IMG_Load(path);
        SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(rend, tmp);
        SDL_FreeSurface(tmp);
    return loadedTexture;
    }

    void paint(SDL_Renderer* rend){
        SDL_RenderPresent(rend);
    }

    void quit(){
        for(int i = 0; i < textureArray.size(); i++){
            SDL_DestroyTexture(textureArray[i]);
        }
        delete this;
    }
};