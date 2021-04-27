
#include "MainObject.h"
#include "CommonFuntion.h"
#include "BaseObject.h"

MainObject::MainObject()
{
    is_falling = false;
    y_val = 1;
}
MainObject::~MainObject()
{
   ;
}
void MainObject::HandleInputAction(SDL_Event events,SDL_Renderer* screen)
{
  if(events.type == SDL_KEYDOWN)
  {
    switch( events.key.keysym.sym )
    {
    case SDLK_UP:
      {
        if(is_falling== false)
        {
            y_val= -8;
        }
      }
    }
  }
  else  if(events.type == SDL_KEYUP)
  {
    switch(events.key.keysym.sym)
    {
    case SDLK_UP:
        {
            y_val=4;
        }
        break;
    }
  }
}
bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret;
  ret=BaseObject::LoadImage(path, screen);
  return ret;
}
void MainObject::ShowImg(SDL_Renderer* des)
{
   BaseObject::Render(des);
}
void MainObject::DoGround(SDL_Renderer* screen)
{
    y_val= 0;
    rect.y= 660-rect.h;
    die= true;
}
void MainObject::LoadBirdIsDie(SDL_Renderer* des)
{
    rect.y += y_val;
    if((rect.y + rect.h) >= 660)
    {
        LoadImg("img//bird_is_die.png", des);
        is_falling = true;
        DoGround(des);
    }
}
