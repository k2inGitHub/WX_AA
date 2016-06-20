#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
using namespace cocos2d;
using namespace extension;



class HelloWorld : public CCLayer, public EditBoxDelegate
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    EditBox* createEditBox(const CCSize& _size, const char* _imageName, const char* _fontName, int _fontSize,
                             const ccColor3B& _fontColor, const char* _pText, const ccColor3B& _pColor, int _maxLength,
                             int _inputMode, int _inputFlag);
    
    virtual void editBoxEditingDidBegin(EditBox* editBox);
    virtual void editBoxEditingDidEnd(EditBox* editBox);
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(EditBox* editBox);
    
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__