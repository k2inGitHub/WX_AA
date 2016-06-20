//
//  BeginLayer.h
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//

#ifndef __zuanshimicheng__OverMenu__
#define __zuanshimicheng__OverMenu__

#include "cocos2d.h"
#include "GameHelper.h"
#include "Add_function.h"


class OverMenu : public CCLayer
{
public:
    
    virtual bool init(CCNode* layer_);
    OverMenu();
    ~OverMenu();
    
    
    void tick(float dt);
    
    void back_menu(Ref* obj);
    
    void game_center();
    
    void menu_share();
    
    void share_weixin();
    void share_friend();
    
    void show_full_ad();
    
public:
    CCNode* layer;
    
    CCSprite* pane;
    
};

#endif /* defined(__zuanshimicheng__BeginLayer__) */
