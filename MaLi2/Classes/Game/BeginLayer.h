//
//  BeginLayer.h
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//

#ifndef __zuanshimicheng__BeginLayer__
#define __zuanshimicheng__BeginLayer__

#include "cocos2d.h"
#include "GameHelper.h"
#include "Add_function.h"
#include "GameLayer.h"


class BeginLayer : public cocos2d::CCLayerColor
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    BeginLayer();
    ~BeginLayer();
    
    void tick(float dt);
public:
    CREATE_FUNC(BeginLayer);
    
    void enter_game(Ref* obj);
    
    void enter_gamecenter();
    
    void select_level(Ref* obj);
    void no_add();
    
    void share_weixin();
    void share_friend();
    
    void show_full_ad();
    
    
    CCMenuItemImage *friendbutton;
};

#endif /* defined(__zuanshimicheng__BeginLayer__) */
