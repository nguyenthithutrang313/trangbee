#ifndef BLOCKOBJECT_H_INCLUDED
#define BLOCKOBJECT_H_INCLUDED

#include "BaseObject.h"
#include "CommonFuntion.h"

class BlockObject : BaseObject
{
public:
    BlockObject();
    ~BlockObject();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void SetPos(const int& xp, const int& yp);
    void SetXPos(const int&xp);
    SDL_Rect GetRectPos() const { return this->GetRect(); }
    void ShowImg(SDL_Renderer* screen);
    void DoRun(UINT& x_val);
    bool GetStateBack() const { return back_; }
    void SetBack(bool m) {back_ = m; }
private:
    bool back_;
};
class TubeBlock
{
public:
    TubeBlock();
    ~TubeBlock();
    bool InitBlock(SDL_Renderer* screen, const int& xp);
    void RenderImg(SDL_Renderer* screen);
    void DoMoving();
    bool GetIsBack() const { return back_; }
    void SetIsBack(bool isBack);
    SDL_Rect GetTopRect();
    void SetRectVal(const UINT& xp);
    void GetRectSlot();
    bool CheckPass(SDL_Rect rect);
    bool GetIsPass() const { return pass; }
    void SetIsPass(const bool& p) {pass = p;}
    bool CheckCol(SDL_Rect fl_rect);
private:
    BlockObject TopBlk;
    BlockObject BottomBlk;
    UINT x_val;
    bool back_;
    bool pass;
    SDL_Rect slot_rect;
};
class BlockManager
{
public:
    BlockManager();
    ~BlockManager();

    bool InitBlockList(SDL_Renderer* screen);
    void Render(SDL_Renderer* screen);
    void StopMoving(const bool& stop);
    void SetBirdRect(SDL_Rect pRect)
                        { bird_rect = pRect; }
    bool GetColState()
                        const { return is_col; }
    int GetCount()
                        const { return mcount; }
    int Getlevel()
                        const { return mlevel; }
    void FreeBlock();
private:
    std::vector<TubeBlock*> BlockList;
    UINT x_pos;
    bool stop_moving;
    SDL_Rect bird_rect;
    int mcount;
    int mlevel;
    bool is_col;
};



#endif // BLOCKOBJECT_H_INCLUDED
