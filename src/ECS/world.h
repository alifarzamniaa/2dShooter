#ifndef WORLD_H
#define WORLD_H
#include "../Logger/logger.h"
#include "componentManager.h"
#include "entityManager.h"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

class World
{
  public:
    World(int initNumberOfEntity) : wWidth(640), wHeight(360), em(initNumberOfEntity)
    {
        window = SDL_CreateWindow("2d Shooter", wWidth, wHeight, SDL_WINDOW_RESIZABLE);
        if (window)
        {
            renderer = SDL_CreateRenderer(window, nullptr);
            if (!renderer)
            {
                Logger::Error("cannot create renderer in world class");
            }
        }
        else
        {
            Logger::Error("cannot create window in world class");
        }
    }

  public:
    ComponentManager cm;
    EntityManager em;
    SDL_Window* window;
    SDL_Renderer* renderer;
    const int wWidth;
    const int wHeight;
};
#endif
