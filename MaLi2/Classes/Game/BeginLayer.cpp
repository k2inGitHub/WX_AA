//
//  BeginLayer.cpp
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//



#include "BeginLayer.h"
#include "SaveIndex.h"
#include "EditMenu.h"
#include "LevelLayer.h"
#include "ShopMenu.h"
#include "HLAdManagerWrapper.hpp"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;




CCScene* BeginLayer::scene()
{
    CCScene *scene = CCScene::create();
    BeginLayer *layer = BeginLayer::create();
    scene->addChild(layer,-100);
    return scene;
}

BeginLayer::BeginLayer()
{
    int level=CCUserDefault::sharedUserDefault()->getIntegerForKey(GAME_LEVEL);
    if(level==0){
        CCUserDefault::sharedUserDefault()->setIntegerForKey(GAME_LEVEL, 1);
        CCUserDefault::sharedUserDefault()->flush();
    }
}
BeginLayer::~BeginLayer(){
}

bool BeginLayer::init()
{
    if(!CCLayerColor::initWithColor(ccc4(37, 51, 122, 255))){
        return false;
    }
    


    
    if(CCUserDefault::sharedUserDefault()->getIntegerForKey(TITLE_MODE)!=0){

    }
    else{

    }
    
    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/bg.mp3", true);

    
    {
        CCLabelTTF* title = CCLabelTTF::create("射进去", "ttf/word.ttf", screenSize.height*0.1f);
        title->setAnchorPoint(ccp(0.5f,0.5f));
        this->addChild(title, 1);
        title->setPosition(ccpPercent(50, 80));
        title->setColor(ccBLUE);
        
        
        int titlekind=CCUserDefault::sharedUserDefault()->getIntegerForKey(TITLE_MODE);
        if(titlekind==1){
            title->setString("挑战失败");
            title->setColor(ccc3(245, 59, 98));
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/over.mp3", false);

        }
        if(titlekind==2){
            title->setString("挑战成功");
            title->setColor(ccGREEN);
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/win.mp3", false);
        }
        if(titlekind==0){
            title->setOpacity(0);
            CCSprite* tit=CCSprite::create("ui/title.png");
            this->addChild(tit,2);
            tit->setScale(0.3*screenSize.height/tit->getContentSize().height);
            tit->setPosition(ccpPercent(50, 70));
        
        }
    }
    
//    {
//        CCMenuItemImage *button = CCMenuItemImage::create(
//                                                          "ui/gamecenter.png",
//                                                          "ui/gamecenter.png",
//                                                          this,
//                                                          menu_selector(BeginLayer::enter_gamecenter) );
//        CCMenu* Menu = CCMenu::create(button, NULL);
//        Menu->setPosition(CCPointZero);
//        this->addChild(Menu,1);
//        button->setScale(0.1*screenSize.height/button->getContentSize().height);
//        button->setPosition(ccpPercent(30, 30));
//    }
    
    {
        CCMenuItemImage *button = CCMenuItemImage::create(
                                                          "ui/entergame.png",
                                                          "ui/entergame.png",
                                                          this,
                                                          menu_selector(BeginLayer::enter_game) );
        CCMenu* Menu = CCMenu::create(button, NULL);
        Menu->setPosition(CCPointZero);
        this->addChild(Menu,1);
        button->setScale(0.1*screenSize.height/button->getContentSize().height);
        button->setPosition(ccpPercent(50, 30));
        
        {
            char text[200];
            sprintf(text, "LEVEL:%d",CCUserDefault::sharedUserDefault()->getIntegerForKey(GAME_LEVEL));
            
            CCLabelTTF* word = CCLabelTTF::create(text, "ttf/word.ttf", button->getContentSize().width*0.09f);
            word->setAnchorPoint(ccp(0.0f,0.5f));
            button->addChild(word, 1);
            word->setPosition(ccpContent(button->getContentSize(), 55, 20));
            word->setColor(ccBLACK);
        }
    }
    
    {
        CCMenuItemImage *button = CCMenuItemImage::create(
                                                          "ui/button.png",
                                                          "ui/button.png",
                                                          this,
                                                          menu_selector(BeginLayer::select_level) );
        CCMenu* Menu = CCMenu::create(button, NULL);
        Menu->setPosition(CCPointZero);
        this->addChild(Menu,1);
        button->setScale(0.07*screenSize.height/button->getContentSize().height);
        button->setAnchorPoint(ccp(0, 1));
        button->setPosition(ccpPercent(3, 97));
        
        CCLabelTTF* word = CCLabelTTF::create("选择关卡", "ttf/word.ttf", button->getContentSize().height*0.3f);
        word->setAnchorPoint(ccp(0.5f,0.5f));
        button->addChild(word, 1);
        word->setPosition(ccpContent(button->getContentSize(), 50, 50));
        word->setColor(ccBLACK);
    }
    
//    {
//        CCMenuItemImage *button = CCMenuItemImage::create(
//                                                          "ui/button.png",
//                                                          "ui/button.png",
//                                                          this,
//                                                          menu_selector(BeginLayer::no_add) );
//        CCMenu* Menu = CCMenu::create(button, NULL);
//        Menu->setPosition(CCPointZero);
//        this->addChild(Menu,1);
//    
//        button->setScale(0.07*screenSize.height/button->getContentSize().height);
//        button->setAnchorPoint(ccp(1, 1));
//        button->setPosition(ccpPercent(97, 97));
//        button->setVisible(false);
//        
//        CCLabelTTF* word = CCLabelTTF::create("去除广告", "ttf/word.ttf", button->getContentSize().height*0.3f);
//        word->setAnchorPoint(ccp(0.5f,0.5f));
//        button->addChild(word, 1);
//        word->setPosition(ccpContent(button->getContentSize(), 50, 50));
//        word->setColor(ccBLACK);
//    }
    
//    {
//        CCMenuItemImage *button = CCMenuItemImage::create(
//                                                          "ui/weixin.png",
//                                                          "ui/weixin.png",
//                                                          this,
//                                                          menu_selector(BeginLayer::share_weixin) );
//        CCMenu* Menu = CCMenu::create(button, NULL);
//        Menu->setPosition(CCPointZero);
//        this->addChild(Menu,1);
//        button->setScale(0.07f*screenSize.height/button->getContentSize().height);
//        button->setPosition(ccpPercent(30, 15));
//        
//        
//        int check=BBGetOnlineParam((char*)"weixin", (char*)"0");
//        if(check==0){
//            button->setVisible(false);
//        }
//    }
    
//    {
//        CCMenuItemImage *button = CCMenuItemImage::create(
//                                                          "ui/friend.png",
//                                                          "ui/friend.png",
//                                                          this,
//                                                          menu_selector(BeginLayer::share_friend) );
//        CCMenu* Menu = CCMenu::create(button, NULL);
//        Menu->setPosition(CCPointZero);
//        this->addChild(Menu,1);
//        button->setScale(0.07f*screenSize.height/button->getContentSize().height);
//        button->setPosition(ccpPercent(70, 15));
//        friendbutton=button;
//        
//        {
//            int weixincount=CCUserDefault::sharedUserDefault()->getIntegerForKey(SAVE_WEIXIN_TIME);
//            
//            if(weixincount>0&&CCUserDefault::sharedUserDefault()->getIntegerForKey(TITLE_MODE)==1){
//                char text[200];
//                sprintf(text, "分享成功可直接跳过该关,剩余%d次",weixincount);
//                
//                CCLabelTTF* word = CCLabelTTF::create(text, "ttf/word.ttf", button->getContentSize().height*0.2f);
//                word->setAnchorPoint(ccp(0.5f,0.5f));
//                button->addChild(word, 1);
//                word->setPosition(ccpContent(button->getContentSize(), 50, 120));
//                word->setColor(ccWHITE);
//                word->setTag(120);
//            }
//        }
//        
//        
//        int check=BBGetOnlineParam((char*)"weixin", (char*)"0");
//        if(check==0){
//            button->setVisible(false);
//        }
//    }
    
//    {
//        float umeng_delay=BBGetOnlineParam((char*)"FullScreenDelay", (char*)"1");
//        CCDelayTime* d=CCDelayTime::create(umeng_delay);
//        CCCallFunc * f=CCCallFunc::create(this, callfunc_selector(BeginLayer::show_full_ad));
//        CCSequence* l=(CCSequence*)CCSequence::create(d,f,NULL);
//        runAction(l);
//    }
    
    HLAdManagerWrapper::showUnsafeInterstitial();
    
    return true;
}

void BeginLayer::tick(float dt){
    

    
    
}

void BeginLayer::enter_game(Ref* obj){
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, GameLayer::scene(), ccWHITE));
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1.0f, GameLayer::scene()));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
}

void BeginLayer::enter_gamecenter(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
}

void BeginLayer::select_level(Ref* obj){
//    EditMenu* menu=new EditMenu();
//    menu->init(this);
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(1.0f, LevelLayer::scene()));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
}

void BeginLayer::no_add(){
    ShopMenu* menu=new ShopMenu();
    menu->shopid=1;
    menu->init(this);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
}


void BeginLayer::share_weixin(){

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
}

void BeginLayer::share_friend(){

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
    
    int weixincount=CCUserDefault::sharedUserDefault()->getIntegerForKey(SAVE_WEIXIN_TIME);
    if(weixincount>0){
        friendbutton->getChildByTag(120)->setVisible(false);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(SAVE_WEIXIN_IS_FRIEND, 1);
        CCUserDefault::sharedUserDefault()->flush();
    }
}

void BeginLayer::show_full_ad(){
//    int fullrom=BBGetOnlineParam((char*)"FullScreenRom", (char*)"3");
//    if(fullrom!=0&&CCUserDefault::sharedUserDefault()->getIntegerForKey(TITLE_MODE)!=0){
//        int rom=CCRANDOM_0_1()*fullrom;
//        if(rom==0){
//            BBShowAdFullBanner();
//        }
//    }
}

