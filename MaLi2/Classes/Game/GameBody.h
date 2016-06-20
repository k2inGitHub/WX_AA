//
//  BeginLayer.h
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//

#ifndef __zuanshimicheng__GameBody__
#define __zuanshimicheng__GameBody__

#include "cocos2d.h"
#include "GameHelper.h"
#include "Add_function.h"



#include "Block.h"

struct LEVEL_DATA{
    int shoot_count;
    int round_count;
    float speed[2];
    float speedtime[2];
};



class GameBody : public CCLayer
{
public:
    
    virtual bool init(CCNode* layer_, CCPoint p);
    GameBody();
    ~GameBody();
    
    
    void init_mainround();
    void init_tube();
    
    void speed_change();
    
    
    void tick(float dt);
    
    void shoot_ball();
    void add_ball();
    
    
    void game_over();
    void game_win();
    
    void back_menu();
    
//    void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& pTouches,Event *pEvent);


    
    void read_level();
    
public:

    
    CCNode* layer;
    CCSprite* pane;
    
    CCSprite* mainround;
    
    bool isover;
    bool isbegin;
    
    CCSprite* tube;
    
    CCArray* shootball_arr;
    
    CCArray* roundball_arr;
    CCArray* roundline_arr;
    
    LEVEL_DATA data;
    
    int score;
    float speed;
    int speedid;
    
    int gamelevel;
    
    bool iswin;
    
};

#endif /* defined(__zuanshimicheng__BeginLayer__) */
