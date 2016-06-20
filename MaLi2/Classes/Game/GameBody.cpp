//
//  BeginLayer.cpp
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//



#include "GameBody.h"
#include "GameLayer.h"
#include "OverMenu.h"
#include "BeginLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

#define ballscale 0.2f
#define balldisper 1.5f

GameBody::GameBody()
{
    isover=false;
    isbegin=false;
    iswin=false;
    
    shootball_arr=new CCArray();
    shootball_arr->init();
    
    roundball_arr=new CCArray();
    roundball_arr->init();
    
    roundline_arr=new CCArray();
    roundline_arr->init();
    
    speedid=1;
    
    score=0;
    
    gamelevel=CCUserDefault::sharedUserDefault()->getIntegerForKey(GAME_LEVEL);
    if(gamelevel==0){
        gamelevel=1;
    }
}
GameBody::~GameBody()
{
    
}


bool GameBody::init(CCNode* layer_, CCPoint p)
{
    if(!CCLayer::init()){
        return false;
    }
    this->setTouchEnabled(true);
    
    read_level();
    
    layer=layer_;
    layer->addChild(this);
    

    pane=CCSprite::create("game/pane.jpg");
    layer->addChild(pane);
    pane->setPosition(p);
    pane->setScale(screenSize.width/pane->getContentSize().width);
    pane->setOpacity(0);
    
    init_mainround();
    init_tube();
    
    this->schedule(schedule_selector(GameBody::tick));
    
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(GameBody::onTouchesBegan, this);
    
    
    return true;
}


void GameBody::init_mainround(){
    mainround=CCSprite::create("game/round.png");
    pane->addChild(mainround,2);
    mainround->setPosition(ccpContent(pane->getContentSize(), 50, 60));
    mainround->setScale(0.3f*pane->getContentSize().width/mainround->getContentSize().width);
    mainround->setColor(ccWHITE);
    
    {
        char number[200];
        sprintf(number, "%d", gamelevel);
        CCLabelTTF* word = CCLabelTTF::create(number, "ttf/word.ttf", mainround->getContentSize().height*0.4f);
        mainround->addChild(word);
        word->setAnchorPoint(ccp(0.5f,0.5f));
        word->setPosition(ccpContent(mainround->getContentSize(), 50, 50));
        word->setTag(120);
        word->setColor(ccc3(37, 51, 122));
    }
    
    int count=data.round_count;
    if(count>0){
        float ro=360/count;
        
        for(int i=0; i<count; i++){
            mainround->setRotation(ro*i);
            add_ball();
            ((CCSprite*)(roundball_arr->lastObject()))->removeAllChildrenWithCleanup(true);
        }
    }
    score=0;
    isbegin=true;
    
    speed_change();
}

void GameBody::init_tube(){
    tube=CCSprite::create("game/pane.jpg");
    pane->addChild(tube,1);
    tube->setAnchorPoint(ccp(0.5f,1));
    tube->setScale(ballscale*mainround->getContentSize().width*mainround->getScale()/tube->getContentSize().width);
    tube->setPosition(ccp(mainround->getPosition().x, mainround->getPosition().y-mainround->getContentSize().height*mainround->getScale()*balldisper));
    tube->setColor(ccRED);
    tube->setOpacity(0);
    
    
    for(int i=0; i<data.shoot_count; i++){
        CCSprite* ball=CCSprite::create("game/round.png");
        tube->addChild(ball,1);
        ball->setScale(tube->getContentSize().width/ball->getContentSize().width);
        ball->setPosition(ccpContent(tube->getContentSize(), 50, -100-200*i));
        ball->setColor(ccWHITE);
        
        {
            char number[200];
            sprintf(number, "%d", data.shoot_count-i);
            CCLabelTTF* word = CCLabelTTF::create(number, "ttf/word.ttf", ball->getContentSize().height*0.6f);
            ball->addChild(word);
            word->setAnchorPoint(ccp(0.5f,0.5f));
            word->setPosition(ccpContent(ball->getContentSize(), 50, 50));
            word->setColor(ccc3(37, 51, 122));
        }
        
        
        
        shootball_arr->addObject(ball);
    }

}

void GameBody::speed_change(){
    if(speedid==0){speedid=1;}
    else if(speedid==1){speedid=0;}
    
    speed=data.speed[speedid];
    
    CCDelayTime* d=CCDelayTime::create(data.speedtime[speedid]);
    CCCallFunc * f=CCCallFunc::create(this, callfunc_selector(GameBody::speed_change));
    CCSequence* l=(CCSequence*)CCSequence::create(d,f,NULL);
    mainround->runAction(l);
}


void GameBody::tick(float dt){
    if(isover==false){
        mainround->setRotation(mainround->getRotation()+dt*speed);
        if(mainround->getRotation()>360){
            mainround->setRotation(mainround->getRotation()-360);
        }
        if(mainround->getRotation()<360){
            mainround->setRotation(mainround->getRotation()+360);
        }
    }
    
    
    
    int count=roundball_arr->count();
    if(count>0){
        for(int i=0; i<count; i++){
            CCSprite* rball=(CCSprite*)roundball_arr->objectAtIndex(i);
            rball->setRotation(-mainround->getRotation());
        }
    }
    mainround->getChildByTag(120)->setRotation(-mainround->getRotation());
}

void GameBody::shoot_ball(){
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/shoot.mp3", false);
    
    if(isover==true){return;}
    if(shootball_arr->count()<=0){return;}
    
    CCSprite* shootball=(CCSprite*)shootball_arr->objectAtIndex(0);
    CCMoveTo* a1=CCMoveTo::create(0.2f, ccpContent(tube->getContentSize(), 50, 100));
    CCFadeTo* a2=CCFadeTo::create(0.0f, 0);
    CCCallFunc * f=CCCallFunc::create(this, callfunc_selector(GameBody::add_ball));
    CCSequence* l=(CCSequence*)CCSequence::create(a1,a2,f,NULL);
    shootball->runAction(l);
    shootball_arr->removeObject(shootball);
    
//    shootball->runAction(ActionRemove::create(0.25f));
    Add_function::removeDelay(shootball, 0.25f);
    
    int count=shootball_arr->count();
    for(int i=0; i<count; i++){
        CCSprite* ball=(CCSprite*)shootball_arr->objectAtIndex(i);
        ball->runAction(CCMoveTo::create(0.2f, ccpContent(tube->getContentSize(), 50, -100-200*i)));
    }
}


void GameBody::add_ball(){
    
    float angle=mainround->getRotation()*M_PI/180;
    float px=balldisper*100*sinf(angle);
    float py=-balldisper*100*cosf(angle);
    
    
    CCSprite* ball=CCSprite::create("game/round.png");
    mainround->addChild(ball,-1);
    ball->setScale(ballscale*mainround->getContentSize().width/ball->getContentSize().width);
    ball->setPosition(ccpContent(mainround->getContentSize(), 50+px, 50+py));
    ball->setColor(ccWHITE);
    
    {
        char number[200];
        sprintf(number, "%d", data.shoot_count-score);
        CCLabelTTF* word = CCLabelTTF::create(number, "ttf/word.ttf", ball->getContentSize().height*0.6f);
        ball->addChild(word);
        word->setAnchorPoint(ccp(0.5f,0.5f));
        word->setPosition(ccpContent(ball->getContentSize(), 50, 50));
        word->setTag(120);
        word->setColor(ccc3(37, 51, 122));
    }
    
    
    CCSprite* line=CCSprite::create("game/line.jpg");
    mainround->addChild(line,-2);
    line->setAnchorPoint(ccp(0.5,0));
    line->setScaleX(0.02*ball->getContentSize().width/line->getContentSize().width);
    line->setScaleY(balldisper*ball->getContentSize().height/line->getContentSize().height);
    line->setPosition(ccpContent(mainround->getContentSize(), 50, 50));
    line->setRotation(-mainround->getRotation()+180);
    line->setColor(ccWHITE);
    roundline_arr->addObject(line);
    
    {
        int count=roundball_arr->count();
        if(count>0){
            for(int i=0; i<count; i++){
                CCSprite* rball=(CCSprite*)roundball_arr->objectAtIndex(i);
                if(ccpDistance(ball->getPosition(), rball->getPosition())<ball->boundingBox().size.width){
                    ball->setColor(ccc3(245, 59, 98));
                    rball->setColor(ccc3(245, 59, 98));
                    
                    ((CCSprite*)roundline_arr->objectAtIndex(i))->setColor(ccc3(245, 59, 98));
                    line->setColor(ccc3(245, 59, 98));
                    
                    if(isover==false){
                        game_over();
                    }
                }
            }
        }
    }
    
    score++;
    roundball_arr->addObject(ball);
    
    

    
    if(shootball_arr->count()==0&&isbegin==true&&isover==false&&roundball_arr->count()==data.round_count+data.shoot_count){
        game_win();
    }
    
}

#pragma mark-
#pragma mark 结束
void GameBody::game_over(){
    isover=true;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/hit.mp3", false);
    
    CCMoveBy* a1=CCMoveBy::create(0.025f, ccpContent(pane->getContentSize(), -0.5, 0));
    CCMoveBy* a2=CCMoveBy::create(0.05f, ccpContent(pane->getContentSize(), 1, 0));
    CCMoveBy* a3=CCMoveBy::create(0.05f, ccpContent(pane->getContentSize(), -1, 0));
    CCMoveBy* a4=CCMoveBy::create(0.025f, ccpContent(pane->getContentSize(), 0.5, 0));
    CCSequence* l1=(CCSequence*)CCSequence::create(a2,a3,NULL);
    CCRepeat* r=CCRepeat::create(l1, 10);
    CCDelayTime* d1=CCDelayTime::create(0.5f);
    CallFunc * f=CallFunc::create(CC_CALLBACK_0(GameBody::back_menu, this));
    CCSequence* l=(CCSequence*)CCSequence::create(a1,r,a4,d1,f,NULL);
    mainround->runAction(l);
    
    
    mainround->runAction(CCTintTo::create(0.5f, 245, 59, 98));
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey(TITLE_MODE, 1);
    CCUserDefault::sharedUserDefault()->flush();
    
    
//    {
//        int check=CCUserDefault::sharedUserDefault()->getIntegerForKey(SAVE_FIRST_GAME);
//        if(check==0){
//            CCUserDefault::sharedUserDefault()->setIntegerForKey(SAVE_FIRST_GAME, 1);
//
//        
//            int weixincount=BBGetOnlineParam((char*)"WeiXinTime", (char*)"2");
//            CCUserDefault::sharedUserDefault()->setIntegerForKey(SAVE_WEIXIN_TIME, weixincount);
//            CCUserDefault::sharedUserDefault()->flush();
//        }
//    
//    }
}

void GameBody::game_win(){
    int count=roundball_arr->count();
    if(count>0){
        for(int i=0; i<count; i++){
            {
                CCSprite* ball=(CCSprite*)roundball_arr->objectAtIndex(i);
                
                CCDelayTime* d=CCDelayTime::create(0.05f*count-i*0.05f);
                CCTintTo* a1= CCTintTo::create(0.1f, 0, 255, 0);
                CCSequence* l=(CCSequence*)CCSequence::create(d,a1,NULL);
                ball->runAction(l);
            }
            {
                CCSprite* line=(CCSprite*)roundline_arr->objectAtIndex(i);
                
                CCDelayTime* d=CCDelayTime::create(0.05f*count-i*0.05f);
                CCTintTo* a1= CCTintTo::create(0.1f, 0, 255, 0);
                CCSequence* l=(CCSequence*)CCSequence::create(d,a1,NULL);
                line->runAction(l);
            }
        }
        
        mainround->runAction(CCTintTo::create(0.5f, 0, 255, 0));
        
        {
            CCDelayTime* d1=CCDelayTime::create(2.0f+count*0.05f);
            CCCallFunc * f=CCCallFunc::create(this, callfunc_selector(GameBody::back_menu));
            CCSequence* l=(CCSequence*)CCSequence::create(d1,f,NULL);
            mainround->runAction(l);
        }
        
        iswin=true;
        
        int passlevel=CCUserDefault::sharedUserDefault()->getIntegerForKey(PASS_LEVEL);
        if(gamelevel>passlevel){
            CCUserDefault::sharedUserDefault()->setIntegerForKey(PASS_LEVEL, gamelevel);
//            BBSubmitScore(gamelevel, "com.vidoshow.youzhongshejinqu.levelno");
        }
        if(gamelevel<200){
            CCUserDefault::sharedUserDefault()->setIntegerForKey(GAME_LEVEL, gamelevel+1);
        }
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey(TITLE_MODE, 2);
        CCUserDefault::sharedUserDefault()->flush();
    }
}

void GameBody::back_menu(){
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3", false);
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, BeginLayer::scene(), ccWHITE));
    
    if(iswin==true){
        CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1.0f, BeginLayer::scene()));
    }
    else{
        CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(1.0f, BeginLayer::scene()));
    }
}


#pragma mark-
#pragma mark 点击
void GameBody::onTouchesBegan(const std::vector<cocos2d::Touch*>& pTouches,Event *pEvent){
    shoot_ball();
}


#pragma mark-
#pragma mark 读关卡
void GameBody::read_level(){
    
    {
        data.round_count=10;
        data.shoot_count=40;
        data.speed[0]=50;
        data.speedtime[0]=30;
        data.speed[1]=100;
        data.speedtime[1]=30;
    }
    char name[200];
    sprintf(name, "data/level.txt");
    std::string path;
    path = FileUtils::getInstance()->fullPathForFilename(name);
    
//    string dpath = CCFileUtils::sharedFileUtils()->getDocumentsPath() + name;
//    path=dpath.c_str();


    long size = 0;
    unsigned char* content = FileUtils::getInstance()->getFileData(path, "rb", &size);
    if(content){
        for(int k=0; k<1000; k++){
            char name[200];
            sprintf(name, "LEVEL%d,", gamelevel);
            strArray lines;
            Add_function::splitByline(std::string(reinterpret_cast<const char*>(content)), lines);
            for(int i = 0; i < lines.size(); i++){
                string line = lines[i];
                size_t slashPos = line.find(name);
                if(slashPos != std::string::npos) {
                    strArray compfirst;
                    Add_function::splitByToken(line.substr(slashPos, line.length() - slashPos).c_str(), ",", compfirst);
                    data.round_count=atoi(compfirst[1].c_str());
                    data.shoot_count=atoi(compfirst[2].c_str());
                    data.speed[0]=atof(compfirst[3].c_str());
                    data.speedtime[0]=atof(compfirst[4].c_str());
                    data.speed[1]=atof(compfirst[5].c_str());
                    data.speedtime[1]=atof(compfirst[6].c_str());
                }
            }
        }
    }
    
}


