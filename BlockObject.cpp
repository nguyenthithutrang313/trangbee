#include "BlockObject.h"

BlockObject::BlockObject()
{
    back_ = false;
}
BlockObject::~BlockObject()
{
    ;
}
bool BlockObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImage(path, screen);
    return ret;
}
void BlockObject::SetPos(const int& xp, const int& yp)
{
    this->SetRect(xp, yp);
}
void BlockObject::SetXPos(const int& xp)
{
    SDL_Rect rect = this->GetRect();
    this->SetRect(xp, rect.y);
}
void BlockObject::ShowImg(SDL_Renderer* screen)
{
    this->Render(screen);
}
void BlockObject::DoRun(UINT& x_val)
{
    this->rect.x += x_val;
    if (rect.x + rect.w < 0)
    {
        back_ = true;
    }
}
TubeBlock::TubeBlock()
{
    x_val= -3;
    back_= false;
    pass = false;
}
TubeBlock::~TubeBlock()
{
    ;
}
bool TubeBlock::InitBlock(SDL_Renderer* screen , const int& xp)
{
    int num= SDLCommonFunc::Random(1,10);
    int number= num;
    num= num*14;
    bool ret1 = TopBlk.LoadImg("img//top_tube.png", screen);
    bool ret2 = BottomBlk.LoadImg("img//bottom_tube.png", screen);
    if(number % 2 == 0)
    {
        TopBlk.SetPos(xp,-250-num);
        BottomBlk.SetPos(xp,460-num);
    }
    else
    {
        TopBlk.SetPos(xp,-250+num);
        BottomBlk.SetPos(xp,460+num);
    }
    if(ret1 && ret2)
        return true;
    return false;
}
void TubeBlock::RenderImg(SDL_Renderer* screen)
{
    TopBlk.ShowImg(screen);
    BottomBlk.ShowImg(screen);
}
void TubeBlock::DoMoving()
{
    TopBlk.DoRun(x_val);
    BottomBlk.DoRun(x_val);
    if (TopBlk.GetStateBack() || BottomBlk.GetStateBack())
    {
       back_ = true;
    }
}
SDL_Rect TubeBlock::GetTopRect()
{
   return TopBlk.GetRectPos();
}
void TubeBlock::SetRectVal(const UINT& xp)
{
    TopBlk.SetXPos(xp);
    BottomBlk.SetXPos(xp);
}
void TubeBlock::SetIsBack(bool isBack)
{
    back_ = isBack;
    TopBlk.SetBack(isBack);
    BottomBlk.SetBack(isBack);
}
void TubeBlock::GetRectSlot()
{
    SDL_Rect rect_top = TopBlk.GetRectPos();
    slot_rect.x = rect_top.x + rect_top.w;
    slot_rect.y = rect_top.y + rect_top.h;
    slot_rect.w = 5;
    slot_rect.h = 160;
}
bool TubeBlock::CheckPass(SDL_Rect rect)
{
    bool ret = false;
    ret = SDLCommonFunc::CheckCollision(rect, slot_rect);
    return ret;
}
bool TubeBlock::CheckCol(SDL_Rect fl_rect)
{
    bool ret1 = SDLCommonFunc::CheckCollision(fl_rect, TopBlk.GetRectPos());
    bool ret2 = SDLCommonFunc::CheckCollision(fl_rect, BottomBlk.GetRectPos());
    if (ret1 || ret2)
    {
        return true;
    }
    return false;
}
BlockManager::BlockManager()
{
    x_pos=0;
    mcount=0;
    mlevel=0;
    stop_moving=false;
    is_col=false;
}
BlockManager::~BlockManager()
{
    FreeBlock();
}
int arr[]={1250, 1500, 1750, 2000, 2250, 2500};
bool BlockManager::InitBlockList(SDL_Renderer* screen)
{
    TubeBlock* block1= new TubeBlock();
    TubeBlock* block2= new TubeBlock();
    TubeBlock* block3= new TubeBlock();
    TubeBlock* block4= new TubeBlock();
    TubeBlock* block5= new TubeBlock();
    TubeBlock* block6= new TubeBlock();
    int ret;
    ret=block1->InitBlock(screen,arr[0]);
    if(ret==false) return false;
    ret=block2->InitBlock(screen,arr[1]);
    if(ret==false) return false;
    ret=block3->InitBlock(screen,arr[2]);
    if(ret==false) return false;
    ret=block4->InitBlock(screen,arr[3]);
    if(ret==false) return false;
    ret=block5->InitBlock(screen,arr[4]);
    if(ret==false) return false;
    ret=block6->InitBlock(screen,arr[5]);
    if (ret=false) return false;
    BlockList.push_back(block1);
    BlockList.push_back(block2);
    BlockList.push_back(block3);
    BlockList.push_back(block4);
    BlockList.push_back(block5);
    BlockList.push_back(block6);
    x_pos= 5.5;
    return true;
}void BlockManager::StopMoving(const bool& stop)
{
    stop_moving= stop;
}
void BlockManager::Render(SDL_Renderer* screen)
{
    for(int i=0; i<BlockList.size(); i++)
    {
        TubeBlock* pBlock=BlockList.at(i);
        pBlock->GetRectSlot();
        if(!stop_moving)
        {
            pBlock->DoMoving();
            bool ret=pBlock->GetIsBack();
            if(ret==true)
            {
                TubeBlock* endBlock=BlockList.at(x_pos);
                SDL_Rect end_rect= endBlock->GetTopRect();
                UINT xp= end_rect.x + 250;
                pBlock->SetRectVal(xp);
                pBlock->SetIsBack(false);
                pBlock->SetIsPass(false);
                x_pos= i;
            }
            bool isCol = pBlock->CheckCol(bird_rect);
            if(isCol== true)
            {
                is_col= true;
                Mix_Chunk* beep_sound = Mix_LoadWAV("sound//punch.wav");
                if (beep_sound != NULL)
                    Mix_PlayChannel(-1, beep_sound, 0);
                break;
            }
            ret = pBlock->CheckPass(bird_rect);
            if(ret==true)
            {
                if(pBlock->GetIsPass()==false)
                {
                    Mix_Chunk* beep_sound = Mix_LoadWAV("sound//ting.wav");
                    if (beep_sound != NULL)
                        Mix_PlayChannel(-1, beep_sound, 0);
                    mcount++;
                    if(mcount==1)
                        {
                            mlevel++;
                        }
                    if(mcount==10*mlevel+2)
                        {
                            mlevel++;
                        }
                    pBlock->SetIsPass(true);
                }
            }
        }
        pBlock->RenderImg(screen);
    }
}
void BlockManager::FreeBlock()
{
    for(int i=0; i<BlockList.size(); i++)
    {
        TubeBlock* pBlock=BlockList.at(i);
        delete pBlock;
        pBlock=NULL;
    }
    BlockList.clear();
}
