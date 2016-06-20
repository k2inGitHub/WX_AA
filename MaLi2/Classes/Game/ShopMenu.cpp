//
//  BeginLayer.cpp
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//



#include "ShopMenu.h"
#include "GameLayer.h"
#include "SaveIndex.h"
#include "BeginLayer.h"
#include "LevelLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


#define SHOP_LEVEL "com.vidoshow.youzhongshejinqu.openall"
#define SHOP_AD "com.vidoshow.youzhongshejinqu.moveads"


ShopMenu::ShopMenu()
{
    shopid=0;
}
ShopMenu::~ShopMenu()
{
    
}

bool ShopMenu::init(CCNode* layer_)
{
    if(!CCLayer::init()){
        return false;
    }
    layer=layer_;
    


    layer->addChild(this,50);
    this->schedule(schedule_selector(ShopMenu::tick));

    

    

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
        pane=CCSprite::create("ui/back.png");
        this->addChild(pane,1);
        pane->setScale(0.3f*screenSize.height/pane->getContentSize().height);
        pane->setPosition(ccpPercent(50, 155));
        
        {
            CCMoveTo* a1=CCMoveTo::create(0.4f, ccpPercent(50, 60));
            pane->runAction(a1);
        }
        
        CCLabelTTF* word = CCLabelTTF::create("花费12元解锁全部200关", "ttf/word.ttf", pane->getContentSize().height*0.1f);
        word->setAnchorPoint(ccp(0.5f,0.5f));
        pane->addChild(word, 1);
        word->setPosition(ccpContent(pane->getContentSize(), 50, 70));
        word->setColor(ccBLACK);
        
        if(shopid==1){
            word->setString("花费6元去掉广告");
        }
        
//        {
//            int check=BBGetOnlineParam((char*)"PayNmuberHide", (char*)"0");
//            if(check!=0){
//                word->setString("解锁全部200关");
//                if(shopid==1){
//                    word->setString("去掉广告");
//                }
//            }
//        }
        
//        {
//            CCMenuItemImage *button = CCMenuItemImage::create(
//                                                              "ui/button.png",
//                                                              "ui/button.png",
//                                                              this,
//                                                              menu_selector(ShopMenu::buy) );
//            CCMenu* Menu = CCMenu::create(button, NULL);
//            Menu->setPosition(CCPointZero);
//            pane->addChild(Menu,1);
//            button->setScale(0.2f*pane->getContentSize().height/button->getContentSize().height);
//            button->setPosition(ccpContent(pane->getContentSize(), 80, 25));
//            
//            CCLabelTTF* word = CCLabelTTF::create("解锁", "ttf/word.ttf", button->getContentSize().height*0.3f);
//            word->setAnchorPoint(ccp(0.5f,0.5f));
//            button->addChild(word, 1);
//            word->setPosition(ccpContent(button->getContentSize(), 50, 50));
//            word->setColor(ccBLACK);
//            
//            if(shopid==1){
//                word->setString("去广告");
//            }
//        }
        
//        {
//            CCMenuItemImage *button = CCMenuItemImage::create(
//                                                              "ui/button.png",
//                                                              "ui/button.png",
//                                                              this,
//                                                              menu_selector(ShopMenu::re_buy) );
//            CCMenu* Menu = CCMenu::create(button, NULL);
//            Menu->setPosition(CCPointZero);
//            pane->addChild(Menu,1);
//            button->setScale(0.2f*pane->getContentSize().height/button->getContentSize().height);
//            button->setPosition(ccpContent(pane->getContentSize(), 50, 25));
//            
//            CCLabelTTF* word = CCLabelTTF::create("恢复购买", "ttf/word.ttf", button->getContentSize().height*0.3f);
//            word->setAnchorPoint(ccp(0.5f,0.5f));
//            button->addChild(word, 1);
//            word->setPosition(ccpContent(button->getContentSize(), 50, 50));
//            word->setColor(ccBLACK);
//        }
        
//        {
//            CCMenuItemImage *button = CCMenuItemImage::create(
//                                                              "ui/button.png",
//                                                              "ui/button.png",
//                                                              this,
//                                                              menu_selector(ShopMenu::menu_clean) );
//            CCMenu* Menu = CCMenu::create(button, NULL);
//            Menu->setPosition(CCPointZero);
//            pane->addChild(Menu,1);
//            button->setScale(0.2f*pane->getContentSize().height/button->getContentSize().height);
//            button->setPosition(ccpContent(pane->getContentSize(), 20, 25));
//            
//            CCLabelTTF* word = CCLabelTTF::create("取消", "ttf/word.ttf", button->getContentSize().height*0.3f);
//            word->setAnchorPoint(ccp(0.5f,0.5f));
//            button->addChild(word, 1);
//            word->setPosition(ccpContent(button->getContentSize(), 50, 50));
//            word->setColor(ccBLACK);
//        }
    }
    
    return true;
}

void ShopMenu::tick(float dt){
    
}



void ShopMenu::menu_clean(Ref* obj){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
    this->removeAllChildrenWithCleanup(true);
    this->release();
}




void ShopMenu::buy(){
//    InApp *inapp = InApp::shareInstance();
//    if(shopid==1){
//        inapp->purchaseProduct(this,
//                               callfuncO_selector(ShopMenu::productPurchased),
//                               callfuncO_selector(ShopMenu::productPurchaseFailed),
//                               SHOP_AD);
//    }
//    else{
//        inapp->purchaseProduct(this,
//                               callfuncO_selector(ShopMenu::productPurchased),
//                               callfuncO_selector(ShopMenu::productPurchaseFailed),
//                               SHOP_LEVEL);
//    }
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
}

void ShopMenu::re_buy(){
//    InApp *inapp = InApp::shareInstance();
//    if(shopid==1){
//        inapp->restoreProducts(this,
//                               callfuncO_selector(ShopMenu::productPurchased),
//                               callfuncO_selector(ShopMenu::productPurchaseFailed),
//                               SHOP_AD);
//    }
//    else{
//        inapp->restoreProducts(this,
//                               callfuncO_selector(ShopMenu::productPurchased),
//                               callfuncO_selector(ShopMenu::productPurchaseFailed),
//                               SHOP_LEVEL);
//    }
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
}


void ShopMenu::productPurchased(CCObject *obj)
{
//    const char*productId = ((CCString*)obj)->m_sString.c_str();
//
//    if (!strcmp(productId, SHOP_LEVEL)) {
//        CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "ProductPurchased");
//        
//        CCUserDefault::sharedUserDefault()->setIntegerForKey(PASS_LEVEL, 200);
//        CCUserDefault::sharedUserDefault()->flush();
//        
//        BBSubmitScore(199, "com.vidoshow.youzhongshejinqu.levelno");
//        
//        CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(1.0f, LevelLayer::scene()));
//        
//
//        BBEvent((char*)"Unlock_All_Level", (char*)"Unlock_All_Level");
//    }
//    if (!strcmp(productId, SHOP_AD)) {
//        CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "ProductPurchased");
//        
//        CCUserDefault::sharedUserDefault()->setIntegerForKey(NO_ADD, 1);
//        CCUserDefault::sharedUserDefault()->flush();
//        BBHideAdBanner();
//        
//        BBEvent((char*)"Remove_AD", (char*)"Remove_AD");
//    }
    
//    menu_clean();

}

void ShopMenu::productPurchaseFailed(CCObject *obj)
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "productPurchaseFailed");
}


