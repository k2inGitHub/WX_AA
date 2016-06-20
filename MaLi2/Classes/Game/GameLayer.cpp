//
//  BeginLayer.cpp
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//



#include "GameLayer.h"
#include "BeginLayer.h"
#include "OverLayer.h"
#include "EditMenu.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


CCScene* GameLayer::scene()
{
    CCScene *scene = CCScene::create();
    GameLayer *layer = GameLayer::create();
    scene->addChild(layer,-100);
    return scene;
}

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer(){
}

bool GameLayer::init()
{
    if(!CCLayerColor::initWithColor(ccc4(37, 51, 122, 255))){
        return false;
    }
    this->setTouchEnabled(true);
    this->schedule(schedule_selector(GameLayer::tick));

    
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/bg.mp3", true);

    
//    {
//        CCSprite* bg=CCSprite::create("game/bg.png");
//        this->addChild(bg,-1);
//        bg->setScaleX(screenSize.width/bg->getContentSize().width);
//        bg->setScaleY(screenSize.height/bg->getContentSize().height);
//        bg->setPosition(ccpPercent(50, 50));
//    }

    gamebody=new GameBody();
    gamebody->init(this, ccpPercent(50, 50));
    
    
    
//    CCMenuItemImage *button = CCMenuItemImage::create(
//                                                      "icon7.png",
//                                                      "icon7.png",
//                                                      this,
//                                                      menu_selector(GameLayer::replaceScene) );
//    CCMenu* Menu = CCMenu::create(button, NULL);
//    Menu->setPosition(CCPointZero);
//    this->addChild(Menu,1);
//    button->setPosition(ccpPercent(90, 90));
//    button->setScale(0.1f*screenSize.width/button->getContentSize().width);
//    
//    
//    
//    {
//        CCMenuItemImage *button = CCMenuItemImage::create(
//                                                          "icon7.png",
//                                                          "icon7.png",
//                                                          this,
//                                                          menu_selector(GameLayer::level_up) );
//        CCMenu* Menu = CCMenu::create(button, NULL);
//        Menu->setPosition(CCPointZero);
//        this->addChild(Menu,1);
//        button->setPosition(ccpPercent(90, 70));
//        button->setScale(0.1f*screenSize.width/button->getContentSize().width);
//    }
//    
//    {
//        CCMenuItemImage *button = CCMenuItemImage::create(
//                                                          "icon7.png",
//                                                          "icon7.png",
//                                                          this,
//                                                          menu_selector(GameLayer::level_down) );
//        CCMenu* Menu = CCMenu::create(button, NULL);
//        Menu->setPosition(CCPointZero);
//        this->addChild(Menu,1);
//        button->setPosition(ccpPercent(10, 70));
//        button->setScale(0.1f*screenSize.width/button->getContentSize().width);
//    }
    

//    EditMenu* box=new EditMenu();
//    box->init(this);
    
    
    
    return true;
}

void GameLayer::tick(float dt){

}


void GameLayer::replaceScene(){

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, GameLayer::scene(), ccBLACK));
    
}

#pragma mark-
#pragma mark 点击
//void GameLayer::ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent){
//
//}


void GameLayer::level_up(){
    CCUserDefault::sharedUserDefault()->setIntegerForKey(GAME_LEVEL, gamebody->gamelevel+1);
    CCUserDefault::sharedUserDefault()->flush();
    replaceScene();
}

void GameLayer::level_down(){
    CCUserDefault::sharedUserDefault()->setIntegerForKey(GAME_LEVEL, gamebody->gamelevel-1);
    CCUserDefault::sharedUserDefault()->flush();
    replaceScene();
}
