#include "SDL.h"
#include "SDL_rect.h"
#include<vector>

class Screen
{
    SDL_Event e;  //using this e when we will close the window of the terminal 
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;

    //constructor
    public:
    Screen()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(640*2, 480*2, 0, &window, &renderer); //setting the resolution of the window[MULTIPLY current initial resolution by 2] i.e 640X480p
        SDL_RenderSetScale(renderer, 2, 2);
    }

    //making a function for adding a new pixel to the vector "points" we made above, this function will tell it to add a new pixel
    void pixel(float x, float y)
    {
        points.push_back({x,y});  //this emplace will add a new point/pixel to our vector "points"
    }

    //making a function to SHOW the pixels
    void show()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //this will set the BACKGROUND as BLACK
        SDL_RenderClear(renderer);  //clear the screen

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //this will set the color of the pixel that will be drawing the shape as WHITE
        for(auto& point: points)
        {
            SDL_RenderDrawPointF(renderer, point.x, point.y);
        }
        SDL_RenderPresent(renderer);
    
    }

    void clear()
    {
        points.clear();
    }

    void input()
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                SDL_Quit();
                exit(0);
            }
        }
    }

};