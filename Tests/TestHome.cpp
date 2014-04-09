//
//  TestHome.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 02/04/14.
//
//

#include "TestHome.h"
#include "TestUserService.h"
#include "TestPushNotificationService.h"
#include "TestStorageService.h"
#include "TestGameService.h"
#include "TestRewardService.h"
#include "TestScoreboardService.h"
#include "TestEmailService.h"

USING_NS_CC;

//PushTest42
#define APP_KEY     "67359321652c10b15fd5f659d096a2051745aa4f339b936d6ce5dccb165de863"
#define SECRET_KEY  "2d44878dd428046f23bd4b3807ce83e982db9900f4c5a8305255da4764c76610"

#define USER_SERVICE        101
#define PUSH_SERVICE        102
#define STORAGE_SERVICE     103
#define GAME_SERVICE        104
#define SCOREBOARD_SERVICE  105
#define REWARD_SERVICE      106
#define SCORE_SERVICE       107
#define EMAIL_SERVICE       108

Scene* TestHome::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestHome::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestHome::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    
    float button_y_Offset =30;
    float y_pos = visibleSize.height-button_y_Offset;
    float x_pos = origin.x + visibleSize.width/2;
    
    
    /**
     * User Service Test
     */
    auto userServiceLabel = LabelTTF::create("User Service", "Marker Felt", 24);
    userServiceLabel->setColor(Color3B::WHITE);
    auto userServiceItem  = MenuItemLabel::create(userServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    userServiceItem->setTag(USER_SERVICE);
    userServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Storage Service Test
     */
    auto storageServiceLabel = LabelTTF::create("Storage Service", "Marker Felt", 24);
    storageServiceLabel->setColor(Color3B::WHITE);
    auto storageServiceItem  = MenuItemLabel::create(storageServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    storageServiceItem->setTag(STORAGE_SERVICE);
    y_pos -= button_y_Offset;
    storageServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Push Service Test
     */
    auto pushServiceLabel = LabelTTF::create("Push Service", "Marker Felt", 24);
    pushServiceLabel->setColor(Color3B::WHITE);
    auto pushServiceItem  = MenuItemLabel::create(pushServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    pushServiceItem->setTag(PUSH_SERVICE);
    y_pos -= button_y_Offset;
    pushServiceItem->setPosition(Point(x_pos,y_pos));

    /**
     * Game Service Test
     */
    auto gameServiceLabel = LabelTTF::create("Game Service", "Marker Felt", 24);
    gameServiceLabel->setColor(Color3B::WHITE);
    auto gameServiceItem  = MenuItemLabel::create(gameServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    gameServiceItem->setTag(GAME_SERVICE);
    y_pos -= button_y_Offset;
    gameServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Scoreboard Service Test
     */
    auto scoreboardServiceLabel = LabelTTF::create("Scoreboard Service", "Marker Felt", 24);
    scoreboardServiceLabel->setColor(Color3B::WHITE);
    auto scoreboardServiceItem  = MenuItemLabel::create(scoreboardServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    scoreboardServiceItem->setTag(SCOREBOARD_SERVICE);
    y_pos -= button_y_Offset;
    scoreboardServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Reward Service Test
     */
    auto rewardServiceLabel = LabelTTF::create("Reward Service", "Marker Felt", 24);
    rewardServiceLabel->setColor(Color3B::WHITE);
    auto rewardServiceItem  = MenuItemLabel::create(rewardServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    rewardServiceItem->setTag(REWARD_SERVICE);
    y_pos -= button_y_Offset;
    rewardServiceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Email Service Test
     */
    auto emailServiceLabel = LabelTTF::create("Email Service", "Marker Felt", 24);
    emailServiceLabel->setColor(Color3B::WHITE);
    auto emailServiceItem  = MenuItemLabel::create(emailServiceLabel, CC_CALLBACK_1(TestHome::menuCloseCallback, this));
    emailServiceItem->setTag(EMAIL_SERVICE);
    y_pos -= button_y_Offset;
    emailServiceItem->setPosition(Point(x_pos,y_pos));


    
    // create menu, it's an autorelease object
    auto menu = Menu::create(userServiceItem,
                             storageServiceItem,
                             pushServiceItem,
                             gameServiceItem,
                             scoreboardServiceItem,
                             rewardServiceItem,
                             emailServiceItem,NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    
    App42API::Initialize(APP_KEY, SECRET_KEY);
    
    return true;
}


void TestHome::menuCloseCallback(Ref* pSender)
{
    MenuItem *item = (MenuItem*)pSender;
    int senderTag = item->getTag();
    switch (senderTag)
    {
        case USER_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestUserService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case PUSH_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestPushNotificationService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case STORAGE_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestStorageService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case GAME_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestGameService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case SCOREBOARD_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestScoreboardService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case SCORE_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestScoreboardService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        case EMAIL_SERVICE:
        {
            // create a scene. it's an autorelease object
            auto scene = TestEmailService::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        default:
            break;
    }
}

