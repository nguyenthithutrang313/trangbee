#include "CommonFuntion.h"
#include "BaseObject.h"
#include "Text.h"

int SDLCommonFunc::Random(int min, int max)
{
    return rand()%(max-min+1)+min;
}
bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
  bool check=false;
  int left1 =object1.x;
  int right1 =object1.x+object1.w;
  int top1 =object1.y;
  int bottom1=object1.y+object1.h;
  int left2 = object2.x;
  int right2 = object2.x + object2.w;
  int top2 = object2.y;
  int bottom2 = object2.y + object2.h;

    if (right1 > left2 && right1 < right2)
  {
    if (top1 > top2 && top1 < bottom2)
    {
      check = true;
    }
  }
  if (right1 > left2 && right1 < right2)
  {
    if (bottom1 > top2 && bottom1 < bottom2)
    {
      check = true;
    }
  }
  if (top1 == top2 && right1 == right2 && bottom1 == bottom2)
  {
    check = true;
  }
  if (left1 > left2 && left1 < right2)
  {
    if (top1 > top2 && top1 < bottom2)
    {
      check= true;
    }
  }
  if (left1 > left2 && left1 < right2)
  {
    if (bottom1 > top2 && bottom1 < bottom2)
    {
      check= true;
    }
  }
  if (right1 > left2 && right1 < right2)
  {
    if (top1 > top2 && top1 < bottom2)
    {
      check= true;
    }
  }
  if (right1 > left2 && right1 < right2)
  {
    if (bottom1 > top2 && bottom1 < bottom2)
    {
      check= true;
    }
  }
  if (left1 > left2 && left1 < right2)
  {
    if (top1 > top2 && top1 < bottom2)
    {
      check= true;
    }
  }
  if (left1 > left2 && left1 < right2)
  {
    if (bottom1 > top2 && bottom1 < bottom2)
    {
      check= true;
    }
  }
  return check;
}
int SDLCommonFunc::ShowMenu(SDL_Renderer* gScreen, TTF_Font* font,const std::string& str1,const std::string& str2,const std::string& img_name)
{
    char* char1=(char*)str1.c_str();
    char* char2=(char*)str2.c_str();
    int size1= str1.length();
    int size2= str2.length();

    const int number=2;
    char* labels[number];
    labels[0]= new char[size1+1];
    labels[1]= new char[size2+1];
    strcpy_s(labels[0],size1+1,char1);
    strcpy_s(labels[1],size2+1,char2);

    SDL_Texture* menu[number];
    bool selected[number]= {0,0};
    SDL_Rect pos[number];
    pos[0].x=SCREEN_WIDTH*0.4-200;
    pos[0].y=SCREEN_HEIGHT*0.8-200 ;
    pos[1].x=SCREEN_WIDTH*0.4-200;
    pos[1].y=SCREEN_HEIGHT*0.8-100 ;

    Text text_object[number];
    text_object[0].SetText(labels[0]);
    text_object[0].SetColor(Text::BLUE_TEXT);
    text_object[0].LoadText(font, gScreen);
    text_object[1].SetText(labels[1]);
    text_object[1].SetColor(Text::BLUE_TEXT);
    text_object[1].LoadText(font, gScreen);

    BaseObject gBackground;

    int xm=0;
    int ym=0;

    char* img_file = (char*)img_name.c_str();
    bool ret=gBackground.LoadImage(img_file,gScreen);

    SDL_Event event;
    while(true)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEMOTION:
                    xm= event.motion.x;
                    ym= event.motion.y;
                    for(int i=0; i<number; i++)
                    {
                        if(xm >= pos[i].x && xm <= pos[i].x + pos[i].w && ym >= pos[i].y && ym <= pos[i].y + pos[i].h)
                        {
                            if (selected[i]==0)
                            {
                                selected[i]= 1;
                                text_object[i].SetText(labels[i]);
                                text_object[i].SetColor(Text::PINK_TEXT);
                                text_object[i].LoadText(font, gScreen);
                            }
                        }
                        else
                        {
                            if (selected[i]==1)
                            {
                                selected[i]= 0;
                                text_object[i].FreeText();
                                text_object[i].SetText(labels[i]);
                                text_object[i].SetColor(Text::GREEN_TEXT);
                                text_object[i].LoadText(font, gScreen);
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    xm= event.button.x;
                    ym= event.button.y;
                    for (int i=0; i<number; i++) {
                        if (xm >= pos[i].x && xm <= pos[i].x + pos[i].w && ym >= pos[i].y && ym <= pos[i].y + pos[i].h)
                        {
                            text_object[0].FreeText();
                            text_object[1].FreeText();
                            gBackground.Free();
                            return i;
                        }
                    }
                    break;
                }
            }
            gBackground.Render(gScreen, NULL);

            for (int i=0; i<number; i++)
            {
                text_object[i].RenderText(gScreen, pos[i].x, pos[i].y);
                pos[i].w= text_object[i].GetWidth();
                pos[i].h= text_object[i].GetHeight();
            }
            SDL_RenderPresent(gScreen);
        }
    return 0;
}
