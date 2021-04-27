
#include "Text.h"
#include "MainObject.h"
#include "BaseObject.h"

Text::Text()
{
    ;
}
Text::~Text()
{
    ;
}
bool Text::LoadText(TTF_Font*font,SDL_Renderer*screen)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(),text_color);
    if(text_surface)
    {
        texture=SDL_CreateTextureFromSurface(screen,text_surface);
        width=text_surface->w;
        height=text_surface->h;
        SDL_FreeSurface(text_surface);
    }
    return texture!=NULL;
}
void Text::SetColor(const int& type)
{
    if(type==0)
    {
        SDL_Color color={0,0,255};
        text_color=color;
    }
    else if(type==1)
    {
        SDL_Color color={255,0,255};
        text_color=color;
    }
    else if(type==2)
    {
        SDL_Color color={0,255,0};
        text_color=color;
    }
}
void Text::RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip /* = NULL */, double angle /* = 0.0 */, SDL_Point* center /* = NULL */, SDL_RendererFlip flip /* = SDL_FLIP_NONE */)
{
    SDL_Rect renderQuad = { x, y, width, height};
    if(clip != NULL )
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip );
}
void Text::FreeText()
{
    if(texture!=NULL)
    {
        SDL_DestroyTexture(texture);
        texture=NULL;
    }
}
