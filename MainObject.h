#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED
#include "CommonFuntion.h"
#include "BaseObject.h"

class MainObject : public BaseObject
{
public:
  MainObject();
  ~MainObject();

  bool LoadImg(std::string path, SDL_Renderer* screen);
  void ShowImg(SDL_Renderer* des);
  void HandleInputAction(SDL_Event events,SDL_Renderer* screen);
  void LoadBirdIsDie(SDL_Renderer* des);
  bool GetFalling() const { return is_falling; }
  void SetFalling(bool falling) { is_falling = falling; }
  void DoGround(SDL_Renderer* screen);
  bool Die() const { return die; }
private:
  bool is_falling;
  float x_val;
  float y_val;
  bool die;
};


#endif // MAINOBJECT_H_INCLUDED
