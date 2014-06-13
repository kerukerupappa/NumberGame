//
//  NumberScene.cpp
//  Number
//
//  Created by kerukerupappa on 2013/12/01.
//
//

#include "NumberScene.h"
#include "MoveTiledSprite.h"
#include "SimpleAudioEngine.h"
#include "Animation.h"
#include "GameStartScene.h"
#include "FSAlertLayer.h"

#define BM_FONT_SIZE(__SIZE , __BASE) (CC_CONTENT_SCALE_FACTOR() * ((float)__SIZE / (float)__BASE))
#define BM_FONT_SIZE64(__SIZE) (BM_FONT_SIZE(__SIZE , 64))


using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

enum {
    kTagTimerLabel = 100,
    kTagHighScoreLabel = 200
};

CCString *saveKey = new CCString("highscore");

bool isStart = false;

CCScene* NumberScene::scene()
{
    CCScene* scene = CCScene::create();
    NumberScene* layer = NumberScene::create();
    scene->addChild(layer);
    
    return scene;
}
/**
 * 初期処理
 */
bool NumberScene::init()
{
    if(!CCLayer::init()){
        return false;
        
    }
    
    // ゲームが進まないようにフラグを設定
    isStart = false;
    
    setKeypadEnabled( true );
    
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
    
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if (platform == kTargetIphone || platform == kTargetIpad){
        //SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sounds/caf/back_bgm.caf");
        //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/caf/back_bgm.caf", true);
        
        SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/ogg/button_push.caf");
        SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/ogg/pow.caf");
    }else{
        //SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sounds/ogg/back_bgm.ogg");
        //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/ogg/back_bgm.ogg", true);
        
        SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/ogg/button_push.ogg");
        SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/ogg/pow.ogg");
    }
    
    MoveTiledSprite* tileBG = MoveTiledSprite::createWithSprite("images/background.png" , 1 , 1);
    this->addChild(tileBG);
    
    
    // 変数初期化
    nextNumber = 1;
    gameTime = 0;
    srand((unsigned)time(NULL));
    
    // タップイベントを取得する
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    // ボタンを作成し配置する
    makeButtons();
    
    // ハイスコア表示
    makeHighScoreLabel();
    
    // タイマーを表示
    makeTimerLabel();
    
    // カウントダウン
    showCountdown();
    
    return true;
    
}

/**
 * カウントダウン
 */
void NumberScene::showCountdown()
{
    this->scheduleOnce(schedule_selector(NumberScene::playCountdownSound), 1);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 「3」の表示
    CCSprite* pNum3 = CCSprite::create("images/3.png");
    pNum3->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    pNum3->setScale(0);
    pNum3->runAction(Animation::num3Animation());
    this->addChild(pNum3, 1);
    
    // 「2」の表示
    CCSprite* pNum2 = CCSprite::create("images/2.png");
    pNum2->setPosition(pNum3->getPosition());
    pNum2->setScale(0);
    pNum2->runAction(Animation::num2Animation());
    this->addChild(pNum2, 1);
    
    // 「1」の表示
    CCSprite* pNum1 = CCSprite::create("images/1.png");
    pNum1->setPosition(pNum3->getPosition());
    pNum1->setScale(0);
    pNum1->runAction(Animation::num1Animation());
    this->addChild(pNum1, 1);
    
    // 「GO」の表示
    CCSprite* pGo = CCSprite::create("images/0.png");
    pGo->setPosition(pNum3->getPosition());
    pGo->setScale(0);
    pGo->runAction(Animation::num0Animation(this, callfunc_selector(NumberScene::startShuffle)));
    this->addChild(pGo, 1);
    
}

/**
 * ゲームスタート
 */
void NumberScene::startShuffle()
{
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if (platform == kTargetIphone || platform == kTargetIpad){
        //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/caf/back_bgm.caf", true);
        
    }else{
        //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/ogg/back_bgm.ogg", true);
        
    }
    
    // ゲームスタート
    isStart = true;
    
    // タイマー開始
    this->schedule(schedule_selector(NumberScene::countTimer));
    
}

/**
 * カウントダウンの音作成
 */
void NumberScene::playCountdownSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("sounds/countdown.mp3");
}

/**
 * タップボタンを配置
 */
void NumberScene::makeButtons()
{
    
    // タイトル表示
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSprite* title = CCSprite::create("images/titlebar.png");
    title->setPosition(ccp(origin.x + visibleSize.width/2, visibleSize.height -30));
    this->addChild(title);
    
    
    CCMenuItemImage *pButton1 =
    CCMenuItemImage::create(
                            "images/button_back.png",
                            "images/button_back.png",
                            this,
                            menu_selector(NumberScene::keyBackClicked)
                            );
    pButton1->setPosition(ccp(origin.x +  pButton1->getContentSize().width /2 , visibleSize.height -40));
    
    CCMenu *pMenu = CCMenu::create(pButton1, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
    
    
    // 数値配列を初期化する
    vector<int> numbers;
    for(int i = 1 ; i < 26 ; i++){
        numbers.push_back(i);
        
    }
    
    // カードを5×5に配置する
    for(int x = 0; x < 5; x++){
        for(int y = 0 ; y < 5 ; y++){
            
            // ランダムで1つの値を取得する
            int index = rand() % numbers.size();
            
            CCString* fileName = CCString::createWithFormat("cards/frontside%02d.png",numbers[index]);
            CCSprite* button = CCSprite::create(fileName->getCString());
            button->setPosition(ccp((x + 0.5) * 128, (y + 0.5) * 172 + 10));
            button->setTag(numbers[index]);
            this->addChild(button);
            
            // 数値配列から値を削除する
            numbers.erase(numbers.begin() + index);
            
        }
    }
}

/**
 * タイマーのラベル作成
 */
void NumberScene::makeTimerLabel(){
    
    // タイマーを表示
    CCSize bgSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelBMFont *timerLabel = CCLabelBMFont::create("0.000s","fonts/futura-48.fnt" );
    timerLabel->setColor(ccc3(255, 0, 127));
    timerLabel->setScale(BM_FONT_SIZE64(60));
    timerLabel->setPosition(ccp(bgSize.width-timerLabel->getContentSize().width/2 ,bgSize.height-56));
    timerLabel->setTag(kTagTimerLabel);
    this->addChild(timerLabel);
    
}

/**
 * ハイスコアを表示
 */
void NumberScene::makeHighScoreLabel(){
    
    // 以前のハイスコアを取得
    float highScore = CCUserDefault::sharedUserDefault()->getFloatForKey(saveKey->getCString(),99.999f);
    
    // 以前のハイスコアを表示
    CCSize bgSize = CCDirector::sharedDirector()->getWinSize();
    CCString* highScoreString = CCString::createWithFormat("Hi.Score:%6.3fs",highScore);
    
    
    /*
    CCLabelTTF* highScoreLabel = CCLabelTTF::create(highScoreString->getCString(), "", 42.0f);
    highScoreLabel->setPosition(ccp(240, bgSize.height-30));
    highScoreLabel->setColor(ccc3(255, 0, 127));
    highScoreLabel->setTag(kTagHighScoreLabel);
    this->addChild(highScoreLabel);
    */
    
    CCLabelBMFont *highScoreLabel = CCLabelBMFont::create(highScoreString->getCString(),"fonts/futura-48.fnt" );
    highScoreLabel->setColor(ccc3(255, 0, 127));
    highScoreLabel->setScale(BM_FONT_SIZE64(40));
    highScoreLabel->setPosition(ccp(bgSize.width-highScoreLabel->getContentSize().width/2+60,bgSize.height-16));
    highScoreLabel->setTag(kTagHighScoreLabel);
    this->addChild(highScoreLabel);
    
}

/**
 * タイマーを加算
 */
void NumberScene::countTimer(float time){
    
    gameTime += time;
    
    // 時間を表示する
    CCSize bgSize = CCDirector::sharedDirector()->getWinSize();
    CCString* timeString = CCString::createWithFormat("%8.3fs",gameTime);
    CCLabelBMFont* timerLabel = (CCLabelBMFont*)this->getChildByTag(kTagTimerLabel);
    //timerLabel->setColor(ccc3(255, 0, 127));
    timerLabel->setString(timeString->getCString());
    timerLabel->setPosition(ccp(bgSize.width-timerLabel->getContentSize().width/2 ,bgSize.height-56));
    
}

/**
 * 再スタートボタンの作成
 */
void NumberScene::afterGame(){
    
    // タイマー停止
    this->unschedule(schedule_selector(NumberScene::countTimer));
    
    //　以前のハイスコアを取得
    float highScore = CCUserDefault::sharedUserDefault()->getFloatForKey(saveKey->getCString(),99.999f);
    
    CCLog("highScore: %f", highScore);
    if(highScore > gameTime){
        // ハイスコアを記録
        CCUserDefault::sharedUserDefault()->setFloatForKey(saveKey->getCString(), gameTime);
        CCUserDefault::sharedUserDefault()->flush();
        
        // ハイスコアを表示
        CCString* highScoreString = CCString::createWithFormat("Hi.Score:%6.3fs",gameTime);
        CCLabelTTF* highScoreLabel = (CCLabelTTF*) this->getChildByTag(kTagHighScoreLabel);
        highScoreLabel->setString(highScoreString->getCString());
        
    }
    
    // リトライボタンを表示
    CCString *score = CCString::createWithFormat("%8.3fs",gameTime);
    FSAlertLayer *alertLayer = FSAlertLayer::create(score->getCString(), this, callfuncN_selector(NumberScene::menuOKCallback), callfuncN_selector(NumberScene::menuNGCallback));
    
    // 適当に高い数値を入れて最上部に表示させる
    this->addChild(alertLayer, 100001);
    

    
}
/**
 * 再スタート処理
 */
void NumberScene::menuOKCallback(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
    
    CCScene* gameScene = (CCScene*)NumberScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
    
}
/**
 * キャンセル
 */
void NumberScene::menuNGCallback(){
    CCDirector::sharedDirector()->replaceScene( GameStartScene::scene() );
    
}
/**
 * 再スタート処理
 */
void NumberScene::menuRetryButton(CCNode *node){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
    
    CCScene* gameScene = (CCScene*)NumberScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
    
}

#pragma make - タップイベント

/**
 * タッチ開始
 */
bool NumberScene::ccTouchBegan(CCTouch *pTouch ,CCEvent *pEvent){
    return true;
    
}


/**
 * タッチ終了
 */
void NumberScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    
    // スタートされてない
    if(!isStart) return;
    
    // タップポイント取得
    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    
    CCNode* node = this->getChildByTag(nextNumber);
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if(node->boundingBox().containsPoint(touchPoint)){
        
        if (platform == kTargetIphone || platform == kTargetIpad){
            SimpleAudioEngine::sharedEngine()->playEffect("sounds/caf/button_push.caf");
        }else{
            SimpleAudioEngine::sharedEngine()->playEffect("sounds/ogg/button_push.ogg");
        }
        
        // 裏カードを作成する
        CCSprite* button = CCSprite::create("cards/backside.png");
        button->setPosition(node->getPosition());
        button->setTag(nextNumber);
        this->addChild(button);
        
        // 表カードを削除する
        //node->removeFromParentAndCleanup(true);
        
        if(nextNumber >= 25){
            // ゲーム終了処理
            afterGame();
            return;
        }
        
        nextNumber++;
        
    }else{
        if (platform == kTargetIphone || platform == kTargetIpad){
            SimpleAudioEngine::sharedEngine()->playEffect("sounds/caf/pow.caf");
        }else{
            SimpleAudioEngine::sharedEngine()->playEffect("sounds/ogg/pow.ogg");
        }
        
    }
    
}

/**
 * バックボタンのイベント
 */
void NumberScene::keyBackClicked()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f,GameStartScene::scene()));
	//CCDirector::sharedDirector()->end();

}





