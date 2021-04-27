#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include "CommonFuntion.h"
class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect( const int&x, const int&y)
                    {rect.x=x,rect.y=y;}
    SDL_Rect GetRect()
                    const { return rect;}
    SDL_Texture*GetObject()
                    const {return pObject;}

    bool LoadImage(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer*des, SDL_Rect* clip = NULL);
    void Free();
protected:
    SDL_Texture* pObject;
    SDL_Rect rect;
};

#endif // BASEOBJECT_H_INCLUDED
