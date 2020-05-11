#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "player.h"
#include "SDL2/SDL_image.h"
using namespace std;

class Renderer
{
public:
      Renderer(const size_t screen_width, const size_t screen_height, const size_t grid_width, const size_t grid_height);
      ~Renderer();

      void Render(Snake const snake, SDL_Point const &food, int level);
      void UpdateWindowTitle(int score, int fps, string player_);

      void RenderSecondLevelBorder(int wh, int ht, int level);

private:
      SDL_Window *sdl_window;
      SDL_Renderer *sdl_renderer;
      //For the image background
      SDL_Texture *LoadImage(const string &image_path, SDL_Renderer *sdl_renderer);
      SDL_Texture *background;

      const size_t screen_width;
      const size_t screen_height;
      const size_t grid_width;
      const size_t grid_height;
};

#endif