#ifndef CHARACTER_H
#define CHARACTER_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
using namespace std;

class Character{
  public:
    Character();
    virtual bool init()=0;
    //Loads media 
    virtual bool loadMedia()=0;
    //Frees media and shuts down SDL
    virtual void close()=0;
    virtual SDL_Surface* loadSurface()=0;
    virtual void runfunc ()=0;
  protected:
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    const int SCREEN_WIDTH=640;
    const int SCREEN_HEIGHT=480;
    //The surface contained by the window
    SDL_Surface* gScreenSurface = NULL;

    //Current displayed image
    SDL_Surface* gImage = NULL;
};

#endif
