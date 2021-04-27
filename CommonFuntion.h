#ifndef COMMONFUNTION_H_INCLUDED
#define COMMONFUNTION_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include "BaseObject.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Text.h"

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;
static TTF_Font* g_font_text = NULL;
static TTF_Font* g_font_menu = NULL;

const int SCREEN_WIDTH = 1530;
const int SCREEN_HEIGHT = 700;
const int COLOR_KEY_R = 180;
const int COLOR_KEY_G = 180;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR =0Xff;

namespace SDLCommonFunc
{
  int Random(int min, int max);
  bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
  int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font,const std::string& str1,const std::string& str2,const std::string& img_name);
}

#endif // COMMONFUNTION_H_INCLUDED
