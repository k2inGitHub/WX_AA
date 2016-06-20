//
//  BeginLayer.h
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//

#ifndef __zuanshimicheng__EditMenu__
#define __zuanshimicheng__EditMenu__

#include "cocos2d.h"
#include "GameHelper.h"
#include "Add_function.h"


#include "cocos-ext.h"
USING_NS_CC_EXT;

class EditMenu : public cocos2d::CCLayer, public EditBoxDelegate
{
public:
    
    virtual bool init(CCNode* layer_);
    EditMenu();
    ~EditMenu();
    
    void tick(float dt);
    
    void enter_game(Ref* obj);
    void menu_clean(Ref* obj);
    
    EditBox* createEditBox(const CCSize& _size, const char* _imageName, const char* _fontName, int _fontSize,
                             const ccColor3B& _fontColor, const char* _pText, const ccColor3B& _pColor, int _maxLength,
                             int _inputMode, int _inputFlag);
    
    virtual void editBoxEditingDidBegin(EditBox* editBox);
    virtual void editBoxEditingDidEnd(EditBox* editBox);
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(EditBox* editBox);
    
    
public:
    

    EditBox* box;
    CCNode* layer;
    
    EditBox* level_edit;
    
    CCMenuItemImage *button1;
    CCMenuItemImage *button2;
    
};

#endif /* defined(__zuanshimicheng__BeginLayer__) */
