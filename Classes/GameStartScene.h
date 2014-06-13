//
//  GameStart.h
//  Number
//
//  Created by kerukerupappa on 2013/12/07.
//
//

#ifndef __NumberGame__GameStartScene__
#define __NumberGame__GameStartScene__

#include <iostream>
#include "cocos2d.h"


class GameStartScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // game start
    void gameStartDone();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameStartScene);
    
    void cbMenuButton1(CCObject *pSender);
    void cbMenuButton2(CCObject *pSender);

    void keyBackClicked();
};

#endif /* defined(__NumberGame__GameStartScene__) */
