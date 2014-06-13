//
//  Number.h
//  Number
//
//  Created by kerukerupappa on 2013/12/01.
//
//

#ifndef __NumberGame__NumberScene__
#define __NumberGame__NumberScene__

#include <iostream>
#include <cocos2d.h>

class NumberScene : public cocos2d::CCLayer
{
private:
    int nextNumber;
    float gameTime;
    
    void makeButtons();
    void makeTimerLabel();
    void makeHighScoreLabel();
    void showCountdown();
    void startShuffle();
    void playCountdownSound();
    void countTimer(float time);
    void afterGame();
    virtual void menuRetryButton(CCNode * node);
    
    
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(NumberScene);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    void keyBackClicked();
    void menuOKCallback();
    void menuNGCallback();
    
};

#endif /* defined(__NumberGame__NumberScene__) */
