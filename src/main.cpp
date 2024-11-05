#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* gWindow;
SDL_Renderer* gRenderer;

bool init();
bool loadMedia(SDL_Texture* InOutTexture);
SDL_Texture* loadTexture(std::string path);
void close();



int main(int argc, char** argv)
{
    //Init app & create window
    if(!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        bool quitApp = false;

        SDL_Texture* texture = nullptr;
        loadMedia(texture);
        
        //Game Loop
        while (!quitApp)
        {
            SDL_Event e;
            //Handle events on queue
            while (SDL_PollEvent( &e ) != 0)
            {
                if(e.type == SDL_QUIT)
                {
                    quitApp = true;
                }
            }

            //Clear screen
            SDL_RenderClear(gRenderer);

            //Render Texture on screen
            SDL_RenderCopy(gRenderer, texture, NULL, NULL);

            //Update screen
            SDL_RenderPresent(gRenderer);
        }
    }

    //Free resources & Close app 
    close();
    
    return 0;
}


bool init()
{
    //Initialization flag
    bool success = true;

    //Init SDL modules
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf(" SDL_VIDEO could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("My Little Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == nullptr)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create Renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == nullptr)
            {
                printf("Renderer could not ve created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF,0xFF,0xFF);

                //Initialize Images Formats Loading
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    
    return success;
}

bool loadMedia(SDL_Texture* InOutTexture)
{
    //Loading flag
    bool success = true;

    //Load PNG texture
    InOutTexture = loadTexture("Assets/Images/crossaire.png");
    if(InOutTexture == nullptr)
    {
        printf("Texture could not be loaded!\n");
        success = false;
    }

    return success;
}

SDL_Texture* loadTexture(std::string path)
{
    //The returned texture
    //Load image at specified path
    SDL_Texture* newTexture = IMG_LoadTexture(gRenderer, path.c_str());
    
    if(newTexture == nullptr)
    {
        printf("Unable to load image & create texture from %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }

    return newTexture;
}

void close()
{
    
    //Destroy app window
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    //Quit sdl modules
    IMG_Quit();
    SDL_Quit();
}