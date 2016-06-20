#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
//    //添加一背景
//    CCSprite* background = CCSprite::create("HelloWorld.png");
//    background->setScale(2);
//    background->setPosition(ccp(size.width*0.5, size.height*0.5));
//    this->addChild(background);
    
    //名字输入框 name
    EditBox* name_edit = createEditBox(CCSize(size.width*0.8, 100), "icon7.png", "Marker Felt", 50, ccRED, "Name:", ccWHITE, 10, -1, -1);
    name_edit->setDelegate(this); //进行注册
    name_edit->setPosition(ccp(size.width*0.5, size.height*0.8));
    this->addChild(name_edit);
    
//    //年龄输入框 age
//    CCEditBox* age_edit = createEditBox(CCSize(size.width*0.8, 100), "green_edit.png", "Marker Felt", 50, ccGREEN, "Age:", ccWHITE, 20, 7, -1);
//    age_edit->setDelegate(this);
//    age_edit->setPosition(ccp(size.width*0.5, size.height*0.5));
//    this->addChild(age_edit);
//    
//    //密码输入框 password
//    CCEditBox* password_edit = createEditBox(CCSize(size.width*0.8, 100), "yellow_edit.png", "Marker Felt", 50, ccYELLOW, "Password:", ccWHITE, 20, 7, 0);
//    password_edit->setDelegate(this);
//    password_edit->setPosition(ccp(size.width*0.5, size.height*0.2));
//    this->addChild(password_edit);
    
    return true;
}


/*
 *_size:        输入框大小（决定框的宽高）
 *_imageName:   输入框底图（可任意大小的图）
 *_fontName:    所输入文字字体
 *_fontSize:    所输入文字大小
 *_fontColor:   所输入文字颜色
 *_pText:       当编辑框中没有任何字符的提示
 *_pColor:      当编辑框中没有任何字符的提示颜色
 *_maxLength:   最大输入文本长度
 *_inputMode:   设置输入键盘模式
 *_inputFlag:   设置输入显示类型
 *
 */
EditBox* HelloWorld::createEditBox(const CCSize& _size, const char* _imageName, const char* _fontName, int _fontSize,
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
////            editBox->setInputMode(kEditBoxInputModePadNumber);
//        }
//            break;
//        default:
//            break;
//    }
//
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
void HelloWorld::editBoxEditingDidBegin(EditBox* editBox)
{
    CCLog("Begin");
}
//编辑框文字改变
void HelloWorld::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    CCLog("Changed");
}
//触发return后的回调函数
void HelloWorld::editBoxEditingDidEnd(EditBox* editBox)
{
    CCLog("End");
}
//结束编辑
void HelloWorld::editBoxReturn(EditBox* editBox)
{
    CCLog("Return");
    CCLog("输入框内容为：%s",editBox->getText());
}