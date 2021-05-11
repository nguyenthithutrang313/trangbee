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
  int x1 = object1.x;
  int w1 = object1.w;
  int y1 = object1.y;
  int h1 = object1.h;
  int x2 = object2.x;
  int w2 = object2.w;
  int y2 =object2.y;
  int h2 =object2.h;

    if(x1+w1 > x2 && x1+w1 < x2+w2)
  {
    if(y1 > y2 && y1 < y2+h2)
    {
      check = true;
    }
  }
  if(x1+w1 > x2 && x1+w1 < x2+w2)
  {
    if(y1+w1 > y2 && y1+w1 < y2+w2)
    {
      check = true;
    }
  }
  if(y1==y2 && x1+w1 == x2+w2 && y1+h1 == y2+h2)
  {
    check = true;
  }
  if(x1 > x2 && x1 < x2+w2)
  {
    if(y1 > y2 && y1 < y2+h2)
    {
      check= true;
    }
  }
  if(x1 > x2 && x1 < x2+w2)
  {
    if(y1+h1 > y2 && y1+h1 < y2+h2)
    {
      check= true;
    }
  }
  if(x1+w1 > x2 && x1+w1 < x2+w2)
  {
    if(y1 > y2 && y1 < y2+h2)
    {
      check= true;
    }
  }
  if(x1+w1 > x2 && x1+w1 < x2+w2)
  {
    if(y1+h1 > y2 && y1+h1 < y2+h2)
    {
      check= true;
    }
  }
  if(x1 > x2 && x1 < x2+w2)
  {
    if(y1 > y2 && y1 < y2+h2)
    {
      check= true;
    }
  }
  if(x1 > x2 && x1 < x2+w2)
  {
    if(y1+h1 > y2 && y1+h1 < y2+h2)
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
    bool color[number]= {0,1};
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
                            if (color[i]==0)
                            {
                                color[i]= 1;
                                text_object[i].SetText(labels[i]);
                                text_object[i].SetColor(Text::PINK_TEXT);
                                text_object[i].LoadText(font, gScreen);
                            }
                        }
                        else
                        {
                            if (color[i]==1)
                            {
                                color[i]= 0;
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
