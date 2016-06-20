//
//  BeginLayer.cpp
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//



#include "EditMenu.h"
#include "SaveIndex.h"
#include "GameLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;




//CCScene* EditMenu::scene()
//{
//    CCScene *scene = CCScene::create();
//    EditMenu *layer = EditMenu::create();
//    scene->addChild(layer,-100);
//    return scene;
//}

EditMenu::EditMenu()
{

}
EditMenu::~EditMenu(){
}

bool EditMenu::init(CCNode* layer_)
{
    if(!CCLayer::init()){
        return false;
    }
    
    layer=layer_;
    layer->addChild(this,1000);
    
    
    {
        CCMenuItemImage *button = CCMenuItemImage::create(
                                                          "game/black.jpg",
                                                          "game/black.jpg",
                                                          this,
                                                          NULL );
        CCMenu* Menu = CCMenu::create(button, NULL);
        Menu->setPosition(CCPointZero);
        this->addChild(Menu,0);
        button->setAnchorPoint(ccp(0.5f,0));
        button->setPosition(ccp(screenSize.width*0.5f,0));
        button->setOpacity(200);
    }
    
    {
        CCSprite* pane=CCSprite::create("ui/back.png");
        this->addChild(pane,1);
        pane->setScale(0.4f*screenSize.height/pane->getContentSize().height);
        pane->setPosition(ccpPercent(50, 70));
        
//        {
//            CCMoveTo* a1=CCMoveTo::create(0.4f, ccpPercent(50, 70));
//            pane->runAction(a1);
//        }
        
        
        
        //名字输入框 name
        CCSprite* npane=CCSprite::create("ui/number_pane.png");
        npane->setScale(0.8f*pane->boundingBox().size.width/npane->getContentSize().width);
        this->addChild(npane,1);
        npane->setPosition(ccpPercent(50, 83));
        
        
        level_edit = createEditBox(npane->boundingBox().size, "ui/number_pane.jpg", "Marker Felt", 50, ccRED, "点击输入关卡数", ccWHITE, 10, 5, -1);
        this->addChild(level_edit,0);
        level_edit->setDelegate(this); //进行注册
        level_edit->setPosition(npane->getPosition());
        
        
        {
            char text[200];
            sprintf(text, "您可输入数字1——%d来进入对应关卡",CCUserDefault::sharedUserDefault()->getIntegerForKey(PASS_LEVEL)+1);
            
            CCLabelTTF* word = CCLabelTTF::create(text, "ttf/word.ttf", pane->getContentSize().height*0.06f);
            word->setAnchorPoint(ccp(0.5f,0.5f));
            pane->addChild(word, 1);
            word->setPosition(ccpContent(pane->getContentSize(), 50, 60));
            word->setColor(ccBLACK);
        }
        
        {
            CCMenuItemImage *button = CCMenuItemImage::create(
                                                              "ui/button.png",
                                                              "ui/button.png",
                                                              this,
                                                              menu_selector(EditMenu::enter_game) );
            CCMenu* Menu = CCMenu::create(button, NULL);
            Menu->setPosition(CCPointZero);
            pane->addChild(Menu,1);
            button->setScale(0.2f*pane->getContentSize().height/button->getContentSize().height);
            button->setPosition(ccpContent(pane->getContentSize(), 70, 25));
            
            CCLabelTTF* word = CCLabelTTF::create("进入游戏", "ttf/word.ttf", button->getContentSize().height*0.3f);
            word->setAnchorPoint(ccp(0.5f,0.5f));
            button->addChild(word, 1);
            word->setPosition(ccpContent(button->getContentSize(), 50, 50));
            word->setColor(ccBLACK);
            button1=button;
        }
        
        {
            CCMenuItemImage *button = CCMenuItemImage::create(
                                                              "ui/button.png",
                                                              "ui/button.png",
                                                              this,
                                                              menu_selector(EditMenu::menu_clean) );
            CCMenu* Menu = CCMenu::create(button, NULL);
            Menu->setPosition(CCPointZero);
            pane->addChild(Menu,1);
            button->setScale(0.2f*pane->getContentSize().height/button->getContentSize().height);
            button->setPosition(ccpContent(pane->getContentSize(), 30, 25));
            
            CCLabelTTF* word = CCLabelTTF::create("返回", "ttf/word.ttf", button->getContentSize().height*0.3f);
            word->setAnchorPoint(ccp(0.5f,0.5f));
            button->addChild(word, 1);
            word->setPosition(ccpContent(button->getContentSize(), 50, 50));
            word->setColor(ccBLACK);
            button2=button;
        }
        
    }
    

    
    
    return true;
}

void EditMenu::tick(float dt){
    

    
    
}



void EditMenu::enter_game(Ref* obj){
    int level=atoi(level_edit->getText());
    
    if(level==0||level>CCUserDefault::sharedUserDefault()->getIntegerForKey(PASS_LEVEL)+1){
        char text[200];
        sprintf(text, "目前您只能进入第%d关或之前的关卡",CCUserDefault::sharedUserDefault()->getIntegerForKey(PASS_LEVEL)+1);
        
//        BBMessageBox(text, "关卡无效");
        return;
    }
    
    menu_clean(NULL);
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey(GAME_LEVEL, level);
    CCUserDefault::sharedUserDefault()->flush();
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, GameLayer::scene(), ccBLACK));
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1.0f, GameLayer::scene()));
}

void EditMenu::menu_clean(Ref* obj){
    this->removeAllChildrenWithCleanup(true);
    this->release();
}




EditBox* EditMenu::createEditBox(const CCSize& _size, const char* _imageName, const char* _fontName, int _fontSize,
                                     const ccColor3B& _fontColor, const char* _pText, const ccColor3B& _pColor, int _maxLength,
                                     int _inputMode, int _inputFlag)
{
    EditBox* editBox = EditBox::create(_size, Scale9Sprite::create(_imageName));
//    editBox->setFontName(_fontName);
//    editBox->setFontSize(_fontSize);
    editBox->setFontColor(_fontColor);
    editBox->setPlaceHolder(_pText);
    editBox->setPlaceholderFontColor(_pColor);
    editBox->setMaxLength(_maxLength);
    
//    //使用默认传 -1
//    switch (_inputMode) {
//        case 0://开启任何文本的输入键盘,包括换行
//        {
//            editBox->setInputMode(kEditBoxInputModeAny);
//        }
//            break;
//        case 1://开启 邮件地址 输入类型键盘
//        {
//            editBox->setInputMode(kEditBoxInputModeEmailAddr);
//        }
//            break;
//        case 2://开启 数字符号 输入类型键盘
//        {
//            editBox->setInputMode(kEditBoxInputModeNumeric);
//        }
//            break;
//        case 3://开启 电话号码 输入类型键盘
//        {
//            editBox->setInputMode(kEditBoxInputModePhoneNumber);
//        }
//            break;
//        case 4://开启 URL 输入类型键盘
//        {
//            editBox->setInputMode(kEditBoxInputModeUrl);
//        }
//            break;
//        case 5://开启 数字 输入类型键盘，允许小数点
//        {
//            editBox->setInputMode(kEditBoxInputModeDecimal);
//        }
//            break;
//        case 6://开启任何文本的输入键盘,不包括换行
//        {
//            editBox->setInputMode(kEditBoxInputModeSingleLine);
//        }
//            break;
//        case 7://0到9纯数字输入
//        {
//            //            editBox->setInputMode(kEditBoxInputModePadNumber);
//        }
//            break;
//        default:
//            break;
//    }
    
//    //使用默认传 -1
//    switch (_inputFlag) {
//        case 0://密码形式输入
//        {
//            editBox->setInputFlag(kEditBoxInputFlagPassword);
//        }
//            break;
//        case 1://敏感数据输入、存储输入方案且预测自动完成
//        {
//            editBox->setInputFlag(kEditBoxInputFlagSensitive);
//        }
//            break;
//        case 2://每个单词首字母大写,并且伴有提示
//        {
//            editBox->setInputFlag(kEditBoxInputFlagInitialCapsWord);
//        }
//            break;
//        case 3://第一句首字母大写,并且伴有提示
//        {
//            editBox->setInputFlag(kEditBoxInputFlagInitialCapsSentence);
//        }
//            break;
//        case 4://所有字符自动大写
//        {
//            editBox->setInputFlag(kEditBoxInputFlagInitialCapsAllCharacters);
//        }
//            break;
//        default:
//            break;
//    }
//    
//    //设置返回类型 就是键盘右下角那个键是 return 、Done 、Send 、Search 、Go等字样
//    editBox->setReturnType(kKeyboardReturnTypeDone);
    return editBox;
}


//开始编辑
void EditMenu::editBoxEditingDidBegin(EditBox* editBox)
{
    CCLog("Begin");
    button1->setVisible(false);
    button2->setVisible(false);
}
//编辑框文字改变
void EditMenu::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    CCLog("Changed");
}
//触发return后的回调函数
void EditMenu::editBoxEditingDidEnd(EditBox* editBox)
{
    button1->setVisible(true);
    button2->setVisible(true);
    CCLog("End");
}
//结束编辑
void EditMenu::editBoxReturn(EditBox* editBox)
{
    CCLog("Return");
    CCLog("输入框内容为：%s",editBox->getText());
}

