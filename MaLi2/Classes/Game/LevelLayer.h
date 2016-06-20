//
//  BeginLayer.h
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//

#ifndef __zuanshimicheng__LevelLayer__
#define __zuanshimicheng__LevelLayer__

#include "cocos2d.h"
#include "GameHelper.h"
#include "Add_function.h"
#include "GameLayer.h"


class LevelLayer : public cocos2d::CCLayerColor
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    LevelLayer();
    ~LevelLayer();
    
    void tick(float dt);
    
    
    void init_pane();

    void enter_game(Ref* obj);
    void back_menu(Ref* obj);
    void shop_menu(Ref* obj);
    
    
    
//    void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
//    void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
//    void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
    
    void pane_left(Ref* obj);
    void pane_right(Ref* obj);
    
public:
    CREATE_FUNC(LevelLayer);
    
    
    CCSprite* pane;
    int pageid;
    
    
    bool istouch;
    CCPoint touchp;
    
    CCSprite* pagepoint[5];
    
    int levelpass;

};

#endif /* defined(__zuanshimicheng__BeginLayer__) */
