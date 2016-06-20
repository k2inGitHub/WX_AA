//
//  BeginLayer.h
//  zuanshimicheng
//
//  Created by zhangrui on 14-2-12.
//
//

#ifndef __zuanshimicheng__ShopMenu__
#define __zuanshimicheng__ShopMenu__

#include "cocos2d.h"
#include "GameHelper.h"
#include "Add_function.h"



class ShopMenu : public CCLayer
{
public:
    
    virtual bool init(CCNode* layer_);
    ShopMenu();
    ~ShopMenu();
    
    
    void tick(float dt);
    
    
    void menu_clean(Ref* obj);
    
    void buy();
    void re_buy();
    
    void productPurchased(CCObject *obj);
    void productPurchaseFailed(CCObject *obj);

    
public:
    CCNode* layer;
    
    CCSprite* pane;
    
    int shopid;
    
};

#endif /* defined(__zuanshimicheng__BeginLayer__) */
