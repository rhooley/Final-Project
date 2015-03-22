#ifndef LINK_H
#define LINK_H
#include <SDL2/SDL.h>
#include "Character.h"
#include <stdio.h>
#include <iostream>
using namespace std;

class Link: public Character {
 public:
  Link();
  bool init();
  //Loads media
  bool loadMedia();
  //Frees media and shuts down SDL
  void close();
  SDL_Surface* loadSurface( string path );
  void runfunc(); //runs funcs to display image
 private: 
  string imagename;  //character image
};

Link :: Link (){
  imagename= "link.bmp";
}

bool Link::init() {
  bool success = true;
  if(SDL_Init(SDL_INIT_VIDEO)<0){
    cout<<"SDL could not initialize! SDL Error"<<SDL_GetError()<<"\n";
  } else {
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT , SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
      {
	printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
	success=false;
      }
    else
      {

	    //Get window surface
	    gScreenSurface = SDL_GetWindowSurface( gWindow );
	  
      }
  }
  return success;
}

bool Link::loadMedia()
{
  //Loading success flag
  bool success = true;

  //Load default surface
  gImage = loadSurface( imagename );
  if( gImage == NULL )
    {
      printf( "Failed to load default image!\n" );
      success = false;
    }
  return success;
}

void Link::close(){
  SDL_FreeSurface( gImage );
  gImage = NULL;
  //Destroy window
  SDL_DestroyWindow( gWindow );
  gWindow=NULL;
  //Quit SDL subsystems
  SDL_Quit();

}

SDL_Surface* Link::loadSurface( string path )
{

  //The final optimized image
  SDL_Surface* optimizedSurface = NULL;

  //Load image at specified path
  SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
  if( loadedSurface == NULL )
    {
      cout<<"Unable to load image"<<SDL_GetError()<<"\n";
    }
  else {
    //Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
    if( optimizedSurface == NULL ) {
      printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
  }

  return optimizedSurface;
}

void Link::runfunc (){
  //Main loop flag
  bool quit = false;
  SDL_Rect stretchRect;
  //Event handler
  SDL_Event e;

  //Start up SDL and create window
  if( !init() ){
    printf( "Failed to initialize!\n" );
  } else {
    //Load media
    if( !loadMedia() ){
      printf( "Failed to load media!\n" );
    } else{

      while( !quit ){
	//Handle events on queue
	while( SDL_PollEvent( &e ) != 0 ){
	  //User requests quit
	  if( e.type == SDL_QUIT ){
	    quit = true;
	
	  } else {

	    stretchRect.x = 0;
	    stretchRect.y = 0;
	    stretchRect.w = SCREEN_WIDTH;
	    stretchRect.h = SCREEN_HEIGHT;
	    SDL_BlitScaled( gImage, NULL, gScreenSurface, &stretchRect );
	    //Update the surface
	    SDL_UpdateWindowSurface( gWindow );

	  }
	}

      }
    }
    //Free resources and close SDL
    close();
}

#endif