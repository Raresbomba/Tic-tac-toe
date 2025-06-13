#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

///Starts up SDL and creates window
bool init();

///Loads media
bool loadMedia();

///closes window and shuts down SDL
void shut();

///The window that is being rendered
SDL_Window* gWindow = NULL;

///The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

///The image that will be loaded on the screen
SDL_Surface* gTitle = NULL;

bool init(){

    ///Initialization flag
    bool success = true;

    ///Initialization of SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not be initialized! SDL Error: %s\n",SDL_GetError());
        success = false;
    }
    else{

        ///Window creation
        gWindow=SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL){
            printf("Window could not be created! SDL Error: %s\n",SDL_GetError());
            success = false;
        }
        else{

            ///Get Window Surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia(){

    ///Loading success flag
    bool success = true;

    ///Load image
    gTitle = SDL_LoadBMP("assets/images/title.bmp");
    if(gTitle == NULL){
        printf("Unable to load image %s! SDL Error: %s\n", "assets/images/title.bmp", SDL_GetError());
        success = false;
    }
    return success;
}

void shut(){

    ///Deallocation of surface
    SDL_FreeSurface(gTitle);
    gTitle = NULL;

    ///Destroying window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    ///Quitting SDL subsystems
    SDL_Quit();
}


int main(int argc, char *argv[]) {
    
    if(!init()){
        printf("Failed to initialize window!");
    }
    else{

        if(!loadMedia()){
            printf("Failed to load media! SDL Error: %s\n",SDL_GetError());
        }
        else{

            ///Applying the image
            if(SDL_BlitSurface(gTitle, NULL, gScreenSurface, NULL) < 0){
                printf("Failed to blit the surface! SDL Error: %s\n",SDL_GetError());
            }
            else{

                ///Updating the surface
                if(SDL_UpdateWindowSurface(gWindow) < 0){
                    printf("Failed to update the surface! SDL Error: %s\n",SDL_GetError());
                }
                else{

                    ///Hack to get the window to stay up
                    SDL_Event e;
                    bool quit = false;
                    while(!quit){
                        while(SDL_PollEvent(&e)){
                            if(e.type == SDL_Quit) quit = true;
                        }
                        SDL_Delay(10);
                    }
                }
            }
        }
    }
    shut();
    return 0;
}
