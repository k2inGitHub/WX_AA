//
//  BeginLayer.cpp
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//



#include "OverMenu.h"
#include "GameLayer.h"
#include "SaveIndex.h"
#include "BeginLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

OverMenu::OverMenu()
{

}
OverMenu::~OverMenu()
{
    
}

bool OverMenu::init(CCNode* layer_)
{
    if(!CCLayer::init()){
        return false;
    }
    layer=layer_;
    
/*
    BBProductPraise();

    layer->addChild(this,50);
    this->schedule(schedule_selector(OverMenu::tick));

    
    int score=((GameLayer*)layer)->gamebody->score;
    if(((GameLayer*)layer)->gamebody->game_mode==MODE_SHUANGZI){
        score=((GameLayer*)layer)->gamebody->score+((GameLayer*)layer)->gamebody2->score;
    }
    
    bool ishigh=false;
    
    int modeid=CCUserDefault::sharedUserDefault()->getIntegerForKey("gamemode");
    char modehighscore[200];
    sprintf(modehighscore, "highscore%d",modeid);
    int highscore=CCUserDefault::sharedUserDefault()->getIntegerForKey(modehighscore);
    if(score>highscore){
        highscore=score;
        CCUserDefault::sharedUserDefault()->setIntegerForKey(modehighscore, highscore);
        CCUserDefault::sharedUserDefault()->flush();
        ishigh=true;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/newscore.mp3", false);
    }
    
    
    

    {
        CCMenuItemImage *button = CCMenuItemImage::create(
                                                          "game/black.jpg",
                                                          "game/black.jpg",
                                                          this,
                                                          NULL );
        CCMenu* Menu = CCMenu::create(button, NULL);
        Menu->setPosition(CCPointZero);
        this->addChild(Menu,-1);
        button->setAnchorPoint(ccp(0.5f,0));
        button->setPosition(ccp(screenSize.width*0.5f,0));
        button->setOpacity(150);
    }
    

    {
        pane=CCSprite::create("over/back.png");
        this->addChild(pane,1);
        pane->setScale(0.3f*screenSize.height/pane->getContentSize().height);
        pane->setPosition(ccpPercent(50, 155));
        
        {
            CCMoveTo* a1=CCMoveTo::create(0.4f, ccpPercent(50, 60));
            pane->runAction(a1);
        }
        
        {
            CCLabelTTF* word = CCLabelTTF::create("游戏结束", "ttf/word.ttf", pane->getContentSize().height*0.2f);
            word->setAnchorPoint(ccp(0.5f,0.5f));
            pane->addChild(word, 10);
            word->setPosition(ccpContent(pane->getContentSize(), 50, 120));
            word->setColor(ccGRAY);
        }
        
        {
            char* name;
            GAME_MODE gamemode=((GameLayer*)layer)->game_mode;
            char* gamecenterid;
            if(gamemode==MODE_WANMEI){
                name=(char*)"完美模式";
                gamecenterid=(char*)"com.wizardgame.kaixindiediele.wanmei";
            }
            if(gamemode==MODE_SHANDIAN){
                name=(char*)"闪电模式";
                gamecenterid=(char*)"com.wizardgame.kaixindiediele.shandian";
            }
            if(gamemode==MODE_NIUZHUAN){
                name=(char*)"扭转模式";
                gamecenterid=(char*)"com.wizardgame.kaixindiediele.niuzhuan";
            }
            if(gamemode==MODE_SHUANGZI){
                name=(char*)"双子模式";
                gamecenterid=(char*)"com.wizardgame.kaixindiediele.shuangzi";
            }
            if(gamemode==MODE_XIANSHI){
                name=(char*)"限时模式";
                gamecenterid=(char*)"com.wizardgame.kaixindiediele.xianshi";
            }
            if(gamemode==MODE_JINGDIAN){
                name=(char*)"经典模式";
                gamecenterid=(char*)"com.wizardgame.kaixindiediele.jingdian";
            }
            
            CCLabelTTF* word = CCLabelTTF::create(name, "ttf/word.ttf", pane->getContentSize().height*0.15f);
            word->setAnchorPoint(ccp(0.5f,0.5f));
            pane->addChild(word, 10);
            word->setPosition(ccpContent(pane->getContentSize(), 50, 80));
            word->setColor(ccc3(255, 0, 255));
            
            
            if(ishigh==true){
                BBSubmitScore(highscore, gamecenterid);
            }
        }
        
        
        
        {
            char number[200];
            sprintf(number, "%d", score);
            
            CCLabelTTF* word = CCLabelTTF::create(number, "ttf/word.ttf", pane->getContentSize().height*0.2f);
            word->setAnchorPoint(ccp(0.5f,0.5f));
            pane->addChild(word, 10);
            word->setPosition(ccpContent(pane->getContentSize(), 50, 50));
            word->setColor(ccBLACK);
            
            if(ishigh==true){
                CCLabelTTF* hword = CCLabelTTF::create("(新记录！)", "ttf/word.ttf", pane->getContentSize().height*0.1f);
                hword->setAnchorPoint(ccp(0.5f,0.5f));
                pane->addChild(hword, 10);
                hword->setPosition(ccpContent(pane->getContentSize(), 50, 40));
                hword->setColor(ccRED);
                
                word->setPosition(ccpContent(pane->getContentSize(), 50, 60));
            }
        }
        
        {
            char text[200];
            sprintf(text, "最佳：%d", highscore);
            
            CCLabelTTF* word = CCLabelTTF::create(text, "ttf/word.ttf", pane->getContentSize().height*0.1f);
            word->setAnchorPoint(ccp(0.5f,0.5f));
            pane->addChild(word, 10);
            word->setPosition(ccpContent(pane->getContentSize(), 50, 20));
            word->setColor(ccBLACK);
        }
        
        {
            CCMenuItemImage *button = CCMenuItemImage::create(
                                                              "over/replay.png",
                                                              "over/replay.png",
                                                              layer,
                                                              menu_selector(GameLayer::replaceScene) );
            CCMenu* Menu = CCMenu::create(button, NULL);
            Menu->setPosition(CCPointZero);
            pane->addChild(Menu,1);
            button->setScale(0.3f*pane->getContentSize().height/button->getContentSize().height);
            button->setPosition(ccpContent(pane->getContentSize(), 90, -80));
            
            {
                button->setOpacity(0);
                CCDelayTime* d=CCDelayTime::create(0.5f);
                CCFadeTo* a1=CCFadeTo::create(0.5f, 255);
                CCSequence* l=(CCSequence*)CCSequence::create(d,a1,NULL);
                button->runAction(l);
            }
        }
        
        {
            CCMenuItemImage *button = CCMenuItemImage::create(
                                                              "over/home.png",
                                                              "over/home.png",
                                                              layer,
                                                              menu_selector(OverMenu::back_menu) );
            CCMenu* Menu = CCMenu::create(button, NULL);
            Menu->setPosition(CCPointZero);
            pane->addChild(Menu,1);
            button->setScale(0.3f*pane->getContentSize().height/button->getContentSize().height);
            button->setPosition(ccpContent(pane->getContentSize(), 10, -80));
            
            {
                button->setOpacity(0);
                CCDelayTime* d=CCDelayTime::create(0.5f);
                CCFadeTo* a1=CCFadeTo::create(0.5f, 255);
                CCSequence* l=(CCSequence*)CCSequence::create(d,a1,NULL);
                button->runAction(l);
            }
        }
        
        {
            CCMenuItemImage *button = CCMenuItemImage::create(
                                                              "over/gamecenter.png",
                                                              "over/gamecenter.png",
                                                              layer,
                                                              menu_selector(OverMenu::game_center) );
            CCMenu* Menu = CCMenu::create(button, NULL);
            Menu->setPosition(CCPointZero);
            pane->addChild(Menu,1);
            button->setScale(0.3f*pane->getContentSize().height/button->getContentSize().height);
            button->setPosition(ccpContent(pane->getContentSize(), 50, -80));
            
            {
                button->setOpacity(0);
                CCDelayTime* d=CCDelayTime::create(0.5f);
                CCFadeTo* a1=CCFadeTo::create(0.5f, 255);
                CCSequence* l=(CCSequence*)CCSequence::create(d,a1,NULL);
                button->runAction(l);
            }
        }
        
        {
            CCMenuItemImage *button = CCMenuItemImage::create(
                                                              "over/weixin.png",
                                                              "over/weixin.png",
                                                              layer,
                                                              menu_selector(OverMenu::share_weixin) );
            CCMenu* Menu = CCMenu::create(button, NULL);
            Menu->setPosition(CCPointZero);
            pane->addChild(Menu,1);
            button->setScale(0.25f*pane->getContentSize().height/button->getContentSize().height);
            button->setPosition(ccpContent(pane->getContentSize(), 85, -30));
            
            {
                button->setOpacity(0);
                CCDelayTime* d=CCDelayTime::create(0.5f);
                CCFadeTo* a1=CCFadeTo::create(0.5f, 255);
                CCSequence* l=(CCSequence*)CCSequence::create(d,a1,NULL);
                button->runAction(l);
            }
            
            int check=BBGetOnlineParam((char*)"weixin", (char*)"0");
            if(check==0){
                button->setVisible(false);
            }
        }
        
        {
            CCMenuItemImage *button = CCMenuItemImage::create(
                                                              "over/friend.png",
                                                              "over/friend.png",
                                                              layer,
                                                              menu_selector(OverMenu::share_friend) );
            CCMenu* Menu = CCMenu::create(button, NULL);
            Menu->setPosition(CCPointZero);
            pane->addChild(Menu,1);
            button->setScale(0.25f*pane->getContentSize().height/button->getContentSize().height);
            button->setPosition(ccpContent(pane->getContentSize(),15, -30));
            
            {
                button->setOpacity(0);
                CCDelayTime* d=CCDelayTime::create(0.5f);
                CCFadeTo* a1=CCFadeTo::create(0.5f, 255);
                CCSequence* l=(CCSequence*)CCSequence::create(d,a1,NULL);
                button->runAction(l);
            }
            
            int check=BBGetOnlineParam((char*)"weixin", (char*)"0");
            if(check==0){
                button->setVisible(false);
            }
        }
    }
    
    
    {
        float umeng_delay=BBGetOnlineParam((char*)"FullScreenDelay", (char*)"1");
        CCDelayTime* d=CCDelayTime::create(umeng_delay);
        CCCallFunc * f=CCCallFunc::create(this, callfunc_selector(OverMenu::show_full_ad));
        CCSequence* l=(CCSequence*)CCSequence::create(d,f,NULL);
        runAction(l);
    }
    
    */
    
    
    return true;
}

void OverMenu::tick(float dt){
    
}


void OverMenu::back_menu(Ref* obj){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, BeginLayer::scene(), ccBLACK));
}

void OverMenu::game_center(){
}


void OverMenu::menu_share(){

}

void OverMenu::share_weixin(){

}

void OverMenu::share_friend(){

}

void OverMenu::show_full_ad(){

}

