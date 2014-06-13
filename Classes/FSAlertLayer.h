//
//  FSAlertLayer.h
//  NumberGame
//
//  Created by kerukerupappa on 2013/12/28.
//
//

#ifndef __NumberGame__FSAlertLayer__
#define __NumberGame__FSAlertLayer__

#include <iostream>
#include "cocos2d.h"

#define FSAlertLayerTagMenu     101
#define FSAlertLayerTagOK       102
#define FSAlertLayerTagNG       103
#define FSAlertLayerTagFrame    110


class FSAlertLayer : public cocos2d::CCLayerColor
{
public:
    static FSAlertLayer* create(const char* message, CCObject* target, cocos2d::SEL_CallFuncN okSelector, cocos2d::SEL_CallFuncN ngSelector);
    static FSAlertLayer* create(const char* message, CCObject* target, cocos2d::SEL_CallFuncN okSelector);
    
    virtual bool init();
    void setStyle(const char* message, CCObject* target, cocos2d::SEL_CallFuncN okSelector, cocos2d::SEL_CallFuncN ngSelector);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    void menuAlertOK(CCObject* pSender);
    void menuAlertClose(CCObject* pSender);
    
    CREATE_FUNC(FSAlertLayer);
    
private:
    cocos2d::CCObject* target;
    cocos2d::SEL_CallFuncN okSelector;
    cocos2d::SEL_CallFuncN ngSelector;
};

#endif /* defined(__NumberGame__FSAlertLayer__) */
