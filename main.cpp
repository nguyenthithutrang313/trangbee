

#include "CommonFuntion.h"
#include "BaseObject.h"
#include <string>
#include "MainObject.h"
#include "BlockObject.h"
#include "Time.h"
#include "Text.h"

BaseObject gBackground;

using namespace std;
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if( ret < 0 )
        success= false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    gWindow = SDL_CreateWindow("Game CPP SDL2 Flappy Bird:",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(gWindow == NULL)
        success = false;
    else
    {
        gScreen = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
        if(gScreen == NULL)
            success=false;
        else
        {
            SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR , RENDER_DRAW_COLOR);
            int imgFlags=IMG_INIT_PNG;
            if( !(IMG_Init(imgFlags) && imgFlags))
                success=false;
        }
        if(TTF_Init()==-1)
        {
            success=false;
        }
        g_font_text = TTF_OpenFont("font//dlxfont_.ttf",21);
        g_font_menu = TTF_OpenFont("font//dlxfont_.ttf",45);
        if (g_font_text == NULL || g_font_menu == NULL)
        {
            success=false;
        }
        if (Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) == -1)
        {
            success=false;
        }
    }
    return success;
}
bool LoadBackground()
{
    bool ret = gBackground.LoadImage("img//background5.jpg",gScreen);
    if( ret == false )
        return false;
    return true;
}
void close()
{   gBackground.Free();
    SDL_DestroyRenderer(gScreen);
    gScreen = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
    IMG_Quit();
}
int main( int argc, char* argv[])
{
    if(InitData() == false)
        return -1;
    bool quit = false;
    int ret_menu = SDLCommonFunc::ShowMenu(gScreen, g_font_menu,"Play ^^", "Exit", "img//menu.png");
    if(ret_menu==0)
         {
           quit = false;
         }
    else
         {
           quit = true;
         }
    if(LoadBackground() == false)
        {
            return -1;
        }
    BaseObject gGround;
    bool ret= gGround.LoadImage("img//ground.png",gScreen);
    if(ret==false)
        {
            return -1;
        }
    gGround.SetRect(0,660);
    MainObject bird;
    BlockManager tube;

    Text text_count_;
    text_count_.SetColor(Text::BLUE_TEXT);

    Text text_score_;
    text_score_.SetColor(Text::BLUE_TEXT);

    Text text_level;
    text_level.SetColor(Text::BLUE_TEXT);

    Text text_level_str;
    text_level_str.SetColor(Text::BLUE_TEXT);

    ret=bird.LoadImg("img//bird.png", gScreen);
    bird.SetRect(100,0);
    if(ret == false)
    {
        return -1;
    }
    ret= tube.InitBlockList(gScreen);
    if(ret == false)
        return -1;
    while(!quit)
       {
        while(SDL_PollEvent(&gEvent)!=0)
        {
            if(gEvent.type == SDL_QUIT)
            {
              quit = true;
            }
            bird.HandleInputAction(gEvent,gScreen);
        }
        SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gScreen);
        gBackground.Render(gScreen, NULL);
        tube.SetBirdRect(bird.GetRect());
        bool isfalling= bird.GetFalling();
        if(isfalling==true)
        {
            tube.StopMoving(true);
        }
        tube.Render(gScreen);
        bool end_game = tube.GetColState();
        if(end_game == true)
        {
            bird.SetFalling(true);
        }
        bird.LoadBirdIsDie(gScreen);
        bird.ShowImg(gScreen);

        std::string score="Score: ";
        text_score_.SetText(score);
        text_score_.LoadText(g_font_text, gScreen);
        text_score_.RenderText(gScreen, 20,20);

        int count = tube.GetCount();
        std::string count_str = std::to_string(count);
        text_count_.SetText(count_str);
        text_count_.LoadText(g_font_text, gScreen);
        text_count_.RenderText(gScreen, 150,20);

        std::string level="Level: ";
        text_level_str.SetText(level);
        text_level_str.LoadText(g_font_text, gScreen);
        text_level_str.RenderText(gScreen,580,20);

        int m_level = tube.Getlevel();
        std::string level_str = std::to_string(m_level);
        text_level.SetText(level_str);
        text_level.LoadText(g_font_text, gScreen);
        text_level.RenderText(gScreen,710,20);

        gGround.Render(gScreen);
        SDL_RenderPresent(gScreen);

        bool GameOver=bird.Die();
        if(GameOver==true)
        {
            cout << endl;
            cout << "Flappy Bird :" << endl;
            cout << "Your score: " << count << endl;
            cout << "Your level: " << m_level << endl;
            cout << endl;
            string str_= "Score:";
            str_= str_+ count_str;
            Sleep(500);
            int ret_menu= SDLCommonFunc::ShowMenu(gScreen,g_font_menu,str_,"Exit","img//gameover1.png");
            if(ret_menu==1)
            {   quit=true;
                continue;
            }
         }
         SDL_Delay(21-3*m_level);
    }
    close();
    return 0;
}
