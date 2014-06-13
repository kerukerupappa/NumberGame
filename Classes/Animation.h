#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_ACTION 1001

class Animation
{
public:
    // Chapter 6.3で説明した内容
    static CCFiniteTimeAction* catStartAction();

    // Chapter 6.4で説明した内容
    static CCFiniteTimeAction* vibrationAnimation();
    static CCFiniteTimeAction* boxesStartAction(CCObject* target, SEL_CallFunc selector);
    static CCFiniteTimeAction* boxesStartActionWithVibration(CCObject* target, SEL_CallFunc selector);

    // Chapter 6.5で追記する内容
    static CCFiniteTimeAction* num3Animation();
    static CCFiniteTimeAction* num2Animation();
    static CCFiniteTimeAction* num1Animation();
    static CCFiniteTimeAction* num0Animation(CCObject* target, SEL_CallFunc selector);

    // Chapter 6.6で追記する内容
    static CCFiniteTimeAction* moveFromLeftToCenter(float time);
    static CCFiniteTimeAction* moveFromLeftToRight(float time);
    static CCFiniteTimeAction* moveFromCenterToLeft(float time);
    static CCFiniteTimeAction* moveFromCenterToRight(float time);
    static CCFiniteTimeAction* moveFromRightToLeft(float time);
    static CCFiniteTimeAction* moveFromRightToCenter(float time);

    // Chapter 6.7で追記する内容
    static CCFiniteTimeAction* catEndAction();

    // Chapter 6.8で追記する内容
    static CCFiniteTimeAction* resultAnimation(CCObject* target, SEL_CallFunc selector);
};

#endif // __ANIMATION_H__
