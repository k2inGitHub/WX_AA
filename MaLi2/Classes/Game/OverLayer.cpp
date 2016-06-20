//
//  BeginLayer.cpp
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//



#include "OverLayer.h"
#include "BeginLayer.h"
#include "GameLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;




CCScene* OverLayer::scene()
{
    CCScene *scene = CCScene::create();
    OverLayer *layer = OverLayer::create();
    scene->addChild(layer,-100);
    return scene;
}

OverLayer::OverLayer()
{
    game_mode=CCUserDefault::sharedUserDefault()->getIntegerForKey("gamemode");
    game_score=CCUserDefault::sharedUserDefault()->getIntegerForKey("gamelevel")-1;
    
    char name[200];
    sprintf(name, "bestscore%d", game_mode);
    bestscore=CCUserDefault::sharedUserDefault()->getIntegerForKey(name);
    
    if(game_score>bestscore){
        bestscore=game_score;
        CCUserDefault::sharedUserDefault()->setIntegerForKey(name, bestscore);
        CCUserDefault::sharedUserDefault()->flush();
        
        isnewscore=true;
        
        int subscore=bestscore;

    }
    
    {
        char text[100];
        sprintf(text, "mode:%d,score:%d",game_mode,(int)game_score);
    }
    {
        if(CCUserDefault::sharedUserDefault()->getIntegerForKey("eachscore")==0){
            char text[100];
            sprintf(text, "mode:%d,score:%d",game_mode,(int)game_score);
            
            CCUserDefault::sharedUserDefault()->setIntegerForKey("eachscore", 1);
            CCUserDefault::sharedUserDefault()->flush();
        }
    }
}
OverLayer::~OverLayer(){
}

bool OverLayer::init()
{
    if(!CCLayerColor::initWithColor(ccc4(95, 158, 79, 0))){
        return false;
    }
    

    
    
    {
        CCSprite* title=CCSprite::create("begin/title.png");
        this->addChild(title);
        title->setScale(0.8*screenSize.width/title->getContentSize().width);
        title->setPosition(ccpPercent(50, 80));
    }
    
    {
        CCSprite* bg=CCSprite::create("game/bg.jpg");
        this->addChild(bg,-1);
        bg->setScaleX(screenSize.width/bg->getContentSize().width);
        bg->setScaleY(screenSize.height/bg->getContentSize().height);
        bg->setPosition(ccpPercent(50, 50));
    }
    

    CCSprite* pane=CCSprite::create("over/pane.png");
    this->addChild(pane,1);
    pane->setScale(0.8*screenSize.width/pane->getContentSize().width);
    pane->setPosition(ccpPercent(50, 55));
    
    {
        char name[200];
        sprintf(name, "begin/%d.png", game_mode);
        
        CCSprite* title=CCSprite::create(name);
        pane->addChild(title);
        title->setScale(0.2*pane->getContentSize().height/title->getContentSize().height);
        title->setPosition(ccpContent(pane->getContentSize(), 50, 83));
        title->setColor(ccc3(47, 104, 97));
    }
    
    
    {
        {
            CCSprite* new_word=CCSprite::create("over/newscore.png");
            pane->addChild(new_word,1);
            new_word->setPosition(ccpContent(pane->getContentSize(), 20, 50));
            new_word->setRotation(-30);
            
            if(isnewscore==false){
                new_word->setVisible(false);
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/over.mp3", false);
            }
            else{
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/newscore.mp3", false);
                
                new_word->setOpacity(0);
                new_word->setScale(3.0f);
                
                CCDelayTime* d=CCDelayTime::create(0.5f);
                CCFadeTo* a1=CCFadeTo::create(0.0f, 255);
                CCScaleTo* a2=CCScaleTo::create(0.3f, 1);
                CCSequence* l=(CCSequence*)CCSequence::create(d,a1,a2,NULL);
                new_word->runAction(l);
            }
        }
        
        
        {
            CCLabelTTF* score_show = CCLabelTTF::create("0", "ttf/word.ttf", pane->getContentSize().height*0.15f);
            score_show->setAnchorPoint(ccp(0.5f,0.5f));
            pane->addChild(score_show, 1);
            score_show->setPosition(ccpContent(pane->getContentSize(), 50, 50));
            score_show->setColor(ccc3(11, 11, 11));
            
            char text[200];
            sprintf(text, "成绩：%d关",game_score);
            score_show->setString(text);
        }
        
        {
            CCLabelTTF* score_show = CCLabelTTF::create("0", "ttf/word.ttf", pane->getContentSize().height*0.15f);
            score_show->setAnchorPoint(ccp(0.5f,0.5f));
            pane->addChild(score_show, 1);
            score_show->setPosition(ccpContent(pane->getContentSize(), 50, 20));
            score_show->setColor(ccc3(11, 11, 11));
            
            char text[200];
            sprintf(text, "最佳：%d关",bestscore);
            score_show->setString(text);
        }
        
//        {
//            CCMenuItemImage *button = CCMenuItemImage::create(
//                                                              "share/everyplay.png",
//                                                              "share/everyplay.png",
//                                                              this,
//                                                              menu_selector(OverLayer::everyplay) );
//            CCMenu* Menu = CCMenu::create(button, NULL);
//            Menu->setPosition(CCPointZero);
//            pane->addChild(Menu,1);
//            button->setScale(0.15*screenSize.width/button->getContentSize().width);
//            button->setPosition(ccpContent(pane->getContentSize(), 14, 80));
//            button->setVisible(false);
//            
//            if(CCUserDefault::sharedUserDefault()->getIntegerForKey("everyplay")==1){
//                button->setVisible(true);
//            }
//            
//            {
//                float scale=button->getScale();
//                CCScaleTo* a1=CCScaleTo::create(0.5f, scale*1.1f);
//                CCScaleTo* a2=CCScaleTo::create(0.5f, scale);
//                CCSequence* l=(CCSequence*)CCSequence::create(a1,a2,NULL);
//                CCRepeatForever* r=CCRepeatForever::create(l);
//                button->runAction(r);
//            }
//        }
    }

    
    
    {
        CCMenuItemImage *button = CCMenuItemImage::create(
                                                          "begin/button.png",
                                                          "begin/button.png",
                                                          this,
                                                          menu_selector(OverLayer::back_menu) );
        CCMenu* Menu = CCMenu::create(button, NULL);
        Menu->setPosition(CCPointZero);
        pane->addChild(Menu,1);
        button->setPosition(ccp(0.5f*button->boundingBox().size.width,-button->boundingBox().size.height*0.5f));
        Add_function::set_MenuItemImage_SelectedImage_Scale(button, 1.0f);
        
        CCSprite* word=CCSprite::create("over/backword.png");
        button->addChild(word, 1);
        word->setPosition(ccpContent(button->getContentSize(), 50, 50));
    }
    
    {
        CCMenuItemImage *button = CCMenuItemImage::create(
                                                          "begin/button.png",
                                                          "begin/button.png",
                                                          this,
                                                          menu_selector(OverLayer::replay_game) );
        CCMenu* Menu = CCMenu::create(button, NULL);
        Menu->setPosition(CCPointZero);
        pane->addChild(Menu,1);
        button->setPosition(ccp(pane->getContentSize().width-0.5f*button->boundingBox().size.width,-button->boundingBox().size.height*0.5f));
        Add_function::set_MenuItemImage_SelectedImage_Scale(button, 1.0f);
        
        CCSprite* word=CCSprite::create("over/resetword.png");
        button->addChild(word, 1);
        word->setPosition(ccpContent(button->getContentSize(), 50, 50));
    }
    
//    {
//        CCMenuItemImage *button = CCMenuItemImage::create(
//                                                          "begin/button.png",
//                                                          "begin/button.png",
//                                                          this,
//                                                          menu_selector(OverLayer::share_friend) );
//        CCMenu* Menu = CCMenu::create(button, NULL);
//        Menu->setPosition(CCPointZero);
//        pane->addChild(Menu,1);
//        button->setPosition(ccp(0.5f*button->boundingBox().size.width,-button->boundingBox().size.height*1.53f));
//        Add_function::set_MenuItemImage_SelectedImage_Scale(button, 1.0f);
//        
//        CCSprite* word=CCSprite::create("over/shareword.png");
//        button->addChild(word, 1);
//        word->setPosition(ccpContent(button->getContentSize(), 50, 50));
//    }
    
//    {
//        float delay=0.9f;
//        float umeng_delay=CCUserDefault::sharedUserDefault()->getFloatForKey("FullScreenDelay");
//        if(umeng_delay!=0){
//            delay=umeng_delay;
//        }
//        
//        CCDelayTime* d=CCDelayTime::create(delay);
//        CCCallFunc * f=CCCallFunc::create(this, callfunc_selector(OverLayer::show_full_ad));
//        CCSequence* l=(CCSequence*)CCSequence::create(d,f,NULL);
//        this->runAction(l);
//    }
    
    
    return true;
}

void OverLayer::tick(float dt){
    
}


void OverLayer::back_menu(Ref* obj){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, BeginLayer::scene(), ccWHITE));
}

void OverLayer::replay_game(Ref* obj){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("gamelevel", 1);
    CCUserDefault::sharedUserDefault()->flush();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, GameLayer::scene(), ccWHITE));
}

void OverLayer::show_full_ad(){
}

#pragma mark-
#pragma mark 分享


void OverLayer::share_friend(CCMenuItemImage*){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
}

void OverLayer::everyplay(CCMenuItemImage*){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
}

