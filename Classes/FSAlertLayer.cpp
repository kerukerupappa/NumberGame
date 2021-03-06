//
//  FSAlertLayer.cpp
//  NumberGame
//
//  Created by kerukerupappa on 2013/12/28.
//
//

#include "FSAlertLayer.h"

USING_NS_CC;

// ceate with 2 buttons
FSAlertLayer* FSAlertLayer::create(const char* message, CCObject *target, SEL_CallFuncN okSelector, SEL_CallFuncN ngSelector)
{
    FSAlertLayer* layer = FSAlertLayer::create();
    layer->setStyle(message, target, okSelector, ngSelector);
    return layer;
}


// create with only 1 button
FSAlertLayer* FSAlertLayer::create(const char *message, cocos2d::CCObject *target, cocos2d::SEL_CallFuncN okSelector)
{
    return FSAlertLayer::create(message, target, okSelector, NULL);
}


bool FSAlertLayer::init()
{
    // half clear black bgcolor
    if (! CCLayerColor::initWithColor(ccc4(0, 0, 0, 100))) {
        return false;
    }
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
    
    CCSize vsize = pDirector->getVisibleSize();
    
    // bg
    CCSprite* frame = CCSprite::create("images/retray_background.png");
    frame->setTag(FSAlertLayerTagFrame);
    frame->setPosition(ccp(vsize.width / 2, vsize.height / 2));
    this->addChild(frame);
    
    return true;
}


void FSAlertLayer::setStyle(const char* message, cocos2d::CCObject *target, cocos2d::SEL_CallFuncN okSelector, cocos2d::SEL_CallFuncN ngSelector)
{
    this->target        = target;
    this->okSelector    = okSelector;
    this->ngSelector    = ngSelector;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    // message
    CCLabelTTF *pMsg = CCLabelTTF::create(message, "", 42);
    pMsg->setPosition(ccp(visibleSize.width / 2 +100, visibleSize.height/2+36));
    this->addChild(pMsg);
    
    // OK Button
    CCMenuItemImage *pNGItem = CCMenuItemImage::create("images/retray_button_cancel.png", "images/retray_button_canel.png", this, menu_selector(FSAlertLayer::menuAlertClose));
    
    int btnHeight = visibleSize.height / 2 - this->getChildByTag(FSAlertLayerTagFrame)->getContentSize().height / 2 + pNGItem->getContentSize().height / 2 + 10;
    
    pNGItem->setTag(FSAlertLayerTagNG);
    pNGItem->setPosition(ccp(visibleSize.width / 2, btnHeight));
    
    CCMenu* pMenu = CCMenu::create(pNGItem, NULL);
    pMenu->setPosition(CCPointZero);
    pMenu->setTag(FSAlertLayerTagMenu);
    this->addChild(pMenu);
    
    // set as 2 buttons
    if (okSelector) {
        pNGItem->setPosition(ccp(visibleSize.width / 2 - pNGItem->getContentSize().width / 2-10, btnHeight +10));
        
        // NG btn
        CCMenuItemImage* pOKItem = CCMenuItemImage::create("images/retray_button_ok.png",
                                                           "images/retray_button_ok.png", this, menu_selector(FSAlertLayer::menuAlertOK));
        pOKItem->setTag(FSAlertLayerTagOK);
        pOKItem->setPosition(ccp(visibleSize.width / 2 + pOKItem->getContentSize().width / 2+10, btnHeight +10));
        pMenu->addChild(pOKItem);
    }
}


// touch event disable other layers
bool FSAlertLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    return true;
}


void FSAlertLayer::menuAlertOK(CCObject* pSender)
{
    CCLOG("OK");
    
    this->menuAlertClose(pSender);
    
    if (this->target && this->okSelector) {
        (this->target->*this->okSelector)(this);
    }
}


void FSAlertLayer::menuAlertClose(cocos2d::CCObject *pSender)
{
    this->removeFromParentAndCleanup(true);
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    if (((CCNode*)pSender)->getTag() == FSAlertLayerTagNG && this->target && this->ngSelector) {
        (this->target->*this->ngSelector)(this);
    }
}