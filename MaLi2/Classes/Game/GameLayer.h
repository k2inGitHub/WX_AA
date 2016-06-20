//
//  BeginLayer.h
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//

#ifndef __zuanshimicheng__GameLayer__
#define __zuanshimicheng__GameLayer__

#include "cocos2d.h"
#include "GameHelper.h"
#include "Add_function.h"
#include "GameBody.h"
#include "SaveIndex.h"


class GameLayer : public cocos2d::CCLayerColor
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    GameLayer();
    ~GameLayer();
    
    void tick(float dt);

public:
    
    CREATE_FUNC(GameLayer);
    void replaceScene();
    
//    void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    
    void level_up();
    void level_down();
    
public:
    GameBody* gamebody;


    
    CCSprite* tap;
};

#endif /* defined(__zuanshimicheng__BeginLayer__) */
