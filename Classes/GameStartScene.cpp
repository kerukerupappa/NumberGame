//
//  GameStart.cpp
//  Number
//
//  Created by kerukerupappa on 2013/12/07.
//
//

#include "GameStartScene.h"
#include "NumberScene.h"
#include "AppMacros.h"
#include "MoveTiledSprite.h"
#include "SimpleAudioEngine.h"
#include "FSAlertLayer.h"
using namespace CocosDenshion;

USING_NS_CC;

bool isLoadBgm = false;

CCScene* GameStartScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameStartScene *layer = GameStartScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool GameStartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    setKeypadEnabled( true );
    
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
    
    if(!isLoadBgm){
        TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
        if (platform == kTargetIphone || platform == kTargetIpad){
            SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sounds/caf/back_bgm.caf");
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/caf/back_bgm.caf", true);
            
            SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/ogg/button_push.caf");
        }else{
            SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sounds/ogg/back_bgm.ogg");
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/ogg/back_bgm.ogg", true);
            
            SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/ogg/button_push.ogg");
        }
        isLoadBgm = true;
    }

    
    MoveTiledSprite* tileBG = MoveTiledSprite::createWithSprite("images/background.png" , 0.6, 0.6);
    this->addChild(tileBG);

    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640.0f, 960.0f, kResolutionExactFit);
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    

    /////////////////////////////
    // タイトル
    CCSprite* title = CCSprite::create("images/title.png");
    title->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2 + title->getContentSize().height*0.4));
    this->addChild(title);
    
   
    
    CCMenuItemImage *pButton1 =
    CCMenuItemImage::create(
                            "images/button_start_off.png",
                            "images/button_start_on.png",
                            this,
                            menu_selector(GameStartScene::cbMenuButton1)
                            );
    pButton1->setPosition(ccp(origin.x + visibleSize.width/2,
                              origin.y + visibleSize.height/2 - pButton1->getContentSize().height*2));
    
    CCMenu *pMenu = CCMenu::create(pButton1, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
    
    return true;
}


void GameStartScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void GameStartScene::cbMenuButton1(CCObject *pSender){
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if (platform == kTargetIphone || platform == kTargetIpad){
        SimpleAudioEngine::sharedEngine()->playEffect("sounds/caf/button_push.caf");
    }else{
        SimpleAudioEngine::sharedEngine()->playEffect("sounds/ogg/button_push.off");
    }
    gameStartDone();

}

void GameStartScene::gameStartDone()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f,NumberScene::scene()));
	//CCDirector::sharedDirector()->replaceScene( NumberScene::scene() );
}

void GameStartScene::keyBackClicked()
{
    CCDirector::sharedDirector()->end();
}

