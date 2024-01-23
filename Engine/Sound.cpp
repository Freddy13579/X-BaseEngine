#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include "include\SDL.h"
#include "include\SDL_mixer.h"

class Sound{

    public:

    /*MAIN VOIDS ------------------------------------------------------------------*/

    //Initalizes SDL_mixer library.
    void XinitSound(){
        Mix_Init(MIX_INIT_MP3);
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){ std::cout << "XinitSound ERROR: "<< Mix_GetError() << std::endl;}
        
    }

    //Calls Mix_Quit function.
    void XquitSound(){
        //Fucking Pray for no memory leaks
        Mix_Quit();
    }

    //Just calculates whitch number to throw to the mixer. Could be private
    int XcalculateVolume(int volume){
        int v = (MIX_MAX_VOLUME * volume)/100;
        return v;
    }

    std::array<int,3> XcalculatePanning2D(int Volume, int srcX, int srcY, int recX, int recY, float area, float falloff){
        int locX = recX - srcX;
        int locY = recY - srcY;
        int dist = std::sqrt(locX*locX+locY*locY);

        int finalVolume = Volume*((falloff/2-dist)/(falloff/2));
        int right;
        int left;
        if (locX>0){right = (area/2-locX)/(area/2)*100;left = (right-100)*-1;}
        if (locX<0){left = (area/2+locX)/(area/2)*100;right = (left-100)*-1;}
        if(right<0){right=0;}
        if(left<0){left=0;}
        if(right>100){right=100;}
        if(left>100){left=100;}
        if(finalVolume<0){finalVolume=0;}
        return {finalVolume, left, right};
    }

    /*SOUND VOIDS -----------------------------------------------------------------*/

    Mix_Music* XloadMusic(const char* filepath){
        Mix_Music *m;
        m = Mix_LoadMUS(filepath);
        if(m==NULL){std::cout<<"XloadMusic Error: "<<Mix_GetError()<<std::endl;}
        return m;
    }

    Mix_Chunk* XloadSound(const char* filepath){
        Mix_Chunk *ch;
        ch = Mix_LoadWAV(filepath);
        if(ch==NULL){std::cout<<"XloadSound Error: "<<Mix_GetError()<<std::endl;}
        return ch;
    }

    //The most basic, dont see much potencial.
    int XplayMusic(Mix_Music* music, int volume, int loops){
        Mix_VolumeMusic(XcalculateVolume(volume));
        return Mix_PlayMusic(music, loops);
    }

    //The best of all for all situations. Noises, soundtracks everything.
    int XplaySound(Mix_Chunk* sound,int channel, int volume, int loops){
        int ch = Mix_PlayChannel(channel, sound, loops);
        Mix_Volume(ch, XcalculateVolume(volume));
        return ch;
    }

    //Panned version of the XplaySound.
    int XplaySoundPanned(Mix_Chunk* sound, int channel, Uint8 left, Uint8 right, int volume, int loops){
        int ch = Mix_PlayChannel(channel, sound, loops);
        Mix_Volume(ch, XcalculateVolume(volume));
        Mix_SetPanning(ch, left, right);
        return ch;
    }

    //Play sound the same way as XplaySound() but with a fade in period.
    int XfadeInSound(Mix_Chunk* sound,int channel, int volume, int loops, int time){
        int ch = Mix_FadeInChannel(channel, sound, loops, time);
        Mix_Volume(ch, XcalculateVolume(volume));
        return ch;
    }

    //Halts channel with a fadeout
    int XfadeOutChannel(int channel, int time){
        return Mix_FadeOutChannel(channel, time);
    }

    void XpauseChannel(int channel){
        Mix_Pause(channel);
    }

    void XplayChannel(int channel){
        Mix_Resume(channel);
    }

    int XstopChannel(int channel){
        return Mix_HaltChannel(channel);
    }

    /*SETTINGS VOIDS ------------------------------------------------------------------*/

    int XsetChannelPanning(int channel, Uint8 left, Uint8 right){
        return Mix_SetPanning(channel, left, right);
    }

    int XsetVolume(int channel, int volume){
        return Mix_Volume(channel, XcalculateVolume(volume));
    }
};