//
//  BeginLayer.cpp
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//



#include "LevelLayer.h"
#include "SaveIndex.h"
#include "EditMenu.h"
#include "BeginLayer.h"
#include "ShopMenu.h"
#include "HLAdManagerWrapper.hpp"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;




CCScene* LevelLayer::scene()
{
    CCScene *scene = CCScene::create();
    LevelLayer *layer = LevelLayer::create();
    scene->addChild(layer,-100);
    return scene;
}

LevelLayer::LevelLayer()
{
    pageid=0;
    levelpass=CCUserDefault::sharedUserDefault()->getIntegerForKey(PASS_LEVEL);
}
LevelLayer::~LevelLayer(){
}

bool LevelLayer::init()
{
    if(!CCLayerColor::initWithColor(ccc4(37, 51, 122, 255))){
        return false;
    }
    this->setTouchEnabled(true);
    this->schedule(schedule_selector(LevelLayer::tick));
    
    init_pane();
    
    {
        for(int i=0; i<5; i++){
            pagepoint[i]=CCSprite::create("game/round.png");
            this->addChild(pagepoint[i],100);
            pagepoint[i]->setScale(0.02*screenSize.width/pagepoint[i]->getContentSize().width);
            pagepoint[i]->setPosition(ccpPercent(50+(i-2)*5, 20));
        }
    }
    
    {
        CCMenuItemImage *button = CCMenuItemImage::create(
                                                          "ui/right.png",
                                                          "ui/right.png",
                                                          this,
                                                          menu_selector(LevelLayer::pane_left) );
        CCMenu* Menu = CCMenu::create(button, NULL);
        Menu->setPosition(CCPointZero);
        this->addChild(Menu,10);
        button->setAnchorPoint(ccp(0.5f,0.5));
        button->setScale(0.09*screenSize.width/button->getContentSize().width);
        button->setPosition(ccpPercent(93, 60));
    }
    {
        CCMenuItemImage *button = CCMenuItemImage::create(
                                                          "ui/left.png",
                                                          "ui/left.png",
                                                          this,
                                                          menu_selector(LevelLayer::pane_right) );
        CCMenu* Menu = CCMenu::create(button, NULL);
        Menu->setPosition(CCPointZero);
        this->addChild(Menu,10);
        button->setAnchorPoint(ccp(0.5f,0.5));
        button->setScale(0.09*screenSize.width/button->getContentSize().width);
        button->setPosition(ccpPercent(7, 60));
    }
    
    
    {
        CCMenuItemImage *button = CCMenuItemImage::create(
                                                          "ui/button.png",
                                                          "ui/button.png",
                                                          this,
                                                          menu_selector(LevelLayer::back_menu) );
        CCMenu* Menu = CCMenu::create(button, NULL);
        Menu->setPosition(CCPointZero);
        this->addChild(Menu,1);
        button->setScale(0.07*screenSize.height/button->getContentSize().height);
        button->setAnchorPoint(ccp(0, 0.5f));
        button->setPosition(ccpPercent(3, 15));
        
        CCLabelTTF* word = CCLabelTTF::create("返回", "ttf/word.ttf", button->getContentSize().height*0.3f);
        word->setAnchorPoint(ccp(0.5f,0.5f));
        button->addChild(word, 1);
        word->setPosition(ccpContent(button->getContentSize(), 50, 50));
        word->setColor(ccBLACK);
    }
    
    {
//        CCMenuItemImage *button = CCMenuItemImage::create(
//                                                          "ui/button.png",
//                                                          "ui/button.png",
//                                                          this,
//                                                          menu_selector(LevelLayer::shop_menu) );
//        CCMenu* Menu = CCMenu::create(button, NULL);
//        Menu->setPosition(CCPointZero);
//        this->addChild(Menu,1);
//        button->setScale(0.07*screenSize.height/button->getContentSize().height);
//        button->setAnchorPoint(ccp(1, 0.5f));
//        button->setPosition(ccpPercent(97, 15));
//        
//        CCLabelTTF* word = CCLabelTTF::create("解锁全部", "ttf/word.ttf", button->getContentSize().height*0.3f);
//        word->setAnchorPoint(ccp(0.5f,0.5f));
//        button->addChild(word, 1);
//        word->setPosition(ccpContent(button->getContentSize(), 50, 50));
//        word->setColor(ccBLACK);
    }
    
    HLAdManagerWrapper::showUnsafeInterstitial();
    
    
    return true;
}

void LevelLayer::tick(float dt){
    for(int i=0; i<5; i++){
        pagepoint[i]->setColor(ccc3(150, 150, 150));
    }
    pagepoint[pageid]->setColor(ccWHITE);
}

void LevelLayer::init_pane(){
    pane=CCSprite::create("game/pane.jpg");
    this->addChild(pane);
    pane->setScale(0.5f*screenSize.height/pane->getContentSize().height);
    pane->setPosition(ccpPercent(50, 60));
    pane->setOpacity(0);
    
    for(int i=0; i<8; i++){
        for(int j=0; j<5; j++){
            CCSprite* part=CCSprite::create("ui/unlock.png");
            pane->addChild(part,1);
            part->setScale(0.15f*pane->getContentSize().width/part->getContentSize().width);
            part->setPosition(ccpContent(pane->getContentSize(), 50+(j-2)*20, 100-i*15));
//            part->setColor(ccBLACK);
            part->setTag(pageid*40+i*5+j+1);
            
            {
                char text[200];
                sprintf(text, "%d",part->getTag());
                
                CCLabelTTF* word = CCLabelTTF::create(text, "ttf/word.ttf", part->getContentSize().width*0.5f);
                word->setAnchorPoint(ccp(0.5f,0.5f));
                part->addChild(word, 1);
                word->setPosition(ccpContent(part->getContentSize(), 50, 50));
                word->setColor(ccWHITE);
                
                if(part->getTag()>levelpass+1){
//                    word->setVisible(false);
                    Add_function::setTextureByFile(part, "ui/lock.png");
                }
            }
        }
    }
}


void LevelLayer::enter_game(Ref* obj){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(1.0f, GameLayer::scene()));
}

void LevelLayer::back_menu(Ref* obj){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(1.0f, BeginLayer::scene()));
}

void LevelLayer::shop_menu(Ref* obj){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
    ShopMenu* menu=new ShopMenu();
    menu->init(this);
}

#pragma mark-
#pragma mark
//void LevelLayer::ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent){
//    CCTouch *touch = (CCTouch*)pTouches->anyObject();
//    CCPoint Point = this->convertTouchToNodeSpace(touch);
//    
//    istouch=true;
//    touchp=Point;
//    
//}

//void LevelLayer::ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent){
//    CCTouch *touch = (CCTouch*)pTouches->anyObject();
//    CCPoint Point = this->convertTouchToNodeSpace(touch);
//    
//    if(istouch==true){
//        if(Point.x-touchp.x>screenSize.width*0.05f){
//            pane_right();
//            istouch=false;
//        }
//        if(Point.x-touchp.x<-screenSize.width*0.05f){
//            pane_left();
//            istouch=false;
//        }
//    }
//}

//void LevelLayer::ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent){
//    CCTouch *touch = (CCTouch*)pTouches->anyObject();
//    CCPoint Point = pane->convertTouchToNodeSpace(touch);
//    
//    
//    int count=pane->getChildrenCount();
//    for(int i=0; i<count; i++){
//        CCSprite* part=(CCSprite*)pane->getChildren()->objectAtIndex(i);
//        if(part->boundingBox().containsPoint(Point)){
//            CCUserDefault::sharedUserDefault()->setIntegerForKey(GAME_LEVEL, part->getTag());
//            CCUserDefault::sharedUserDefault()->flush();
//            
//            if(part->getTag()>levelpass+1){
//                return;
//            }
//            
//            CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(1.0f, GameLayer::scene()));
//            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
//        }
//    }
//}


void LevelLayer::pane_left(Ref* obj){
    float speed=0.5f;
    
    pane->runAction(CCMoveTo::create(speed, ccp(-0.5*screenSize.width, pane->getPosition().y)));
//    pane->runAction(ActionRemove::create(speed));
    Add_function::removeDelay(pane, speed);
    pageid++;
    if(pageid>=5){
        pageid=0;
    }
    
    init_pane();
    pane->setPosition(ccp(1.5*screenSize.width, pane->getPosition().y));
    pane->runAction(CCMoveTo::create(speed, ccp(0.5*screenSize.width, pane->getPosition().y)));
    
}

void LevelLayer::pane_right(Ref* obj){
    float speed=0.5f;
    
    pane->runAction(CCMoveTo::create(speed, ccp(1.5*screenSize.width, pane->getPosition().y)));
//    pane->runAction(ActionRemove::create(speed));
    Add_function::removeDelay(pane, speed);
    pageid--;
    if(pageid<0){
        pageid=4;
    }
    
    init_pane();
    pane->setPosition(ccp(-0.5*screenSize.width, pane->getPosition().y));
    pane->runAction(CCMoveTo::create(speed, ccp(0.5*screenSize.width, pane->getPosition().y)));
}


