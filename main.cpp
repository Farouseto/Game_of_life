#include <SDL.h>
#include "Button.h"

int LayerNow = 0; //The layer of buttons that will be displayed on the screen
std::string Name;
int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 600;
SDL_Window *Window = NULL;
SDL_Renderer *Render = NULL;
SDL_Texture *buttonset = NULL;

void init ()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
            std::cout << "Can't init SDL: " << SDL_GetError() << std::endl;
    }

    Window = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (Window == NULL)
    {
             std::cout << "Can't create window: " << SDL_GetError() << std::endl;
    }

    Render = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (Render == NULL)
    {
             std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
    }

    SDL_Surface *Buttonset = SDL_LoadBMP("Buttonset.bmp");
    if (Buttonset == NULL)
    {
        std::cout << "Can't create Buttonset: " << SDL_GetError() << std::endl;
    }
    SDL_SetColorKey(Buttonset,SDL_TRUE,SDL_MapRGB(Buttonset->format,0,0xFF,0xFF));
    buttonset = SDL_CreateTextureFromSurface(Render,Buttonset);

    LoadButton();
}

void Quit()
{
    SDL_DestroyWindow(Window);
    Window = NULL;

    SDL_DestroyRenderer(Render);
    Render = NULL;

    SDL_Quit();

    ButtonClose();
}

void DrawBatton(int x, int y, int h, int w, int ImX, int ImY)
{
     SDL_Rect Rect = {x, y, h, w};
     SDL_Rect Cut = {ImX, ImY, h, w};
     SDL_RenderCopy(Render,buttonset,&Cut,&Rect);

     SDL_RenderPresent(Render);
}

void ButtonAnimation()
{
    int x = 0, y = 0, h = 0, w = 0, ImX = 0, ImY = 0;
    GetPB(Name, LayerNow, x, y, h, w, ImX, ImY);
    DrawBatton(x, y, h, w, ImX, ImY);
}

void ButtonRendering()
{
    int x = 0, y = 0, h = 0, w = 0, ImX = 0, ImY = 0, size = 0;
    int *Link = GetLink(LayerNow, size);
    for (int i = 0; i <= size; i++)
    {
        x = *(Link + 0 + (6 * i));
        y = *(Link + 1 + (6 * i));
        h = *(Link + 2 + (6 * i));
        w = *(Link + 3 + (6 * i));
        ImX = *(Link + 4 + (6 * i));
        ImY = *(Link + 5 + (6 * i));
        DrawBatton(x, y, h, w, ImX, ImY);
    }
    if (Name != "Nothing") ButtonAnimation();
    SDL_RenderPresent(Render);
}

void ButBACK()
{
    LayerNow--;
}

void ButPLAY()
{
    LayerNow++;
}

main(int argc, char ** args)
{
    init();

    SDL_Event Event;
    bool Done = false;
    while (!Done)
    {
        while (SDL_PollEvent(&Event) != 0)
        {
            switch (Event.type)
            {
            case SDL_QUIT:
                {
                    Done = true;
                    break;
                }
            case SDL_MOUSEMOTION:
                {
                    Name = ButtonStates(Event.motion.x, Event.motion.y, LayerNow);
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                {
                    switch (LayerNow)
                    {
                        case 0:
                            {
                                if (Name == "PLAY") ButPLAY();
                                break;
                            }
                        case 1:
                            {
                                if (Name == "BACK") ButBACK();
                                break;
                            }
                    }
                }
            }
        }

        ButtonRendering();
    }
    //DrawBattons();

    std::cout << __cplusplus << std::endl;

    Quit();
    return 0;
};
