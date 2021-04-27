#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "BaseObject.h"
#include <string>
#include <SDL_ttf.h>

class Text
{
public:
    enum TextColor
    {
        BLUE_TEXT=0,
        PINK_TEXT=1,
        GREEN_TEXT=2,
    };
     Text();
    ~Text();
    bool LoadText(TTF_Font* gFont, SDL_Renderer* screen);
    void SetText(const std::string&text)
                        { str_val=text;}
    std::string GetText()
                        const { return str_val;}
    void SetColor(const int&type);
    void RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int GetWidth()
                        const {return width;}
    int GetHeight()
                        const { return height;}
    void FreeText();
private:
    std::string str_val;
    SDL_Color text_color;
    SDL_Texture* texture;
    int width;
    int height;
};

#endif // TEXT_H_INCLUDED
