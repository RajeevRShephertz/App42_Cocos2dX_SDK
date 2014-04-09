//
//  TestPushNotificationService.cpp
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#include "TestPushNotificationService.h"
#include "TestHome.h"


#define GO_HOME 1021

USING_NS_CC;

Scene* TestPushNotificationService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestPushNotificationService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestPushNotificationService::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    channelName = "App42TestPushChannelReturnss";
    description = "Testing channel";
    userName = "DhruvChopra12345";
    deviceToken = "b1d6b70a7fe5a29be43b823f7bd3aa072f60d849c931b3465915773b835f00f3";
    message = "Hello from cocos2d-X!";
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    
    float button_y_Offset =30;
    float y_pos = visibleSize.height-button_y_Offset;
    float x_pos = origin.x + visibleSize.width/2;
    
    /**
     * Back Button
     */
    auto backButtonItem = MenuItemImage::create(
                                                "BackButton.png",
                                                "BackButton.png",
                                                CC_CALLBACK_1(TestPushNotificationService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * Register Device Token
     */
    auto registerDeviceTokenLabel = LabelTTF::create("RegisterDevice", "Marker Felt", 24);
    registerDeviceTokenLabel->setColor(Color3B::WHITE);
    auto registerDeviceTokenItem  = MenuItemLabel::create(registerDeviceTokenLabel, CC_CALLBACK_1(TestPushNotificationService::registerDeviceToken, this));
    //y_pos -= button_y_Offset;
    registerDeviceTokenItem->setPosition(Point(x_pos,y_pos));

    
    /**
     * Create Channel
     */
    auto createChannelLabel = LabelTTF::create("CreateChannel", "Marker Felt", 24);
    createChannelLabel->setColor(Color3B::WHITE);
    auto createChannelItem  = MenuItemLabel::create(createChannelLabel, CC_CALLBACK_1(TestPushNotificationService::createChannel, this));
    y_pos -= button_y_Offset;
    createChannelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Subscribe To Channel
     */
    auto subscribeToChannelLabel = LabelTTF::create("SubscribeToChannel", "Marker Felt", 24);
    subscribeToChannelLabel->setColor(Color3B::WHITE);
    auto subscribeToChannelItem  = MenuItemLabel::create(subscribeToChannelLabel, CC_CALLBACK_1(TestPushNotificationService::subscribeToChannel, this));
    y_pos -= button_y_Offset;
    subscribeToChannelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Subscribe Device To Channel
     */
    auto subscribeDeviceToChannelLabel = LabelTTF::create("SubscribeDeviceToChannel", "Marker Felt", 24);
    subscribeDeviceToChannelLabel->setColor(Color3B::WHITE);
    auto subscribeDeviceToChannelItem  = MenuItemLabel::create(subscribeDeviceToChannelLabel, CC_CALLBACK_1(TestPushNotificationService::subscribeDeviceToChannel, this));
    y_pos -= button_y_Offset;
    subscribeDeviceToChannelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Unsubscribe To Channel
     */
    auto unsubscribeToChannelLabel = LabelTTF::create("UnsubscribeToChannel", "Marker Felt", 24);
    unsubscribeToChannelLabel->setColor(Color3B::WHITE);
    auto unsubscribeToChannelItem  = MenuItemLabel::create(unsubscribeToChannelLabel, CC_CALLBACK_1(TestPushNotificationService::unsubscribeToChannel, this));
    y_pos -= button_y_Offset;
    unsubscribeToChannelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Unsubscribe Device To Channel
     */
    auto unsubscribeDeviceToChannelLabel = LabelTTF::create("UnsubscribeDeviceToChannel", "Marker Felt", 24);
    unsubscribeDeviceToChannelLabel->setColor(Color3B::WHITE);
    auto unsubscribeDeviceToChannelItem  = MenuItemLabel::create(unsubscribeDeviceToChannelLabel, CC_CALLBACK_1(TestPushNotificationService::unsubscribeDeviceToChannel, this));
    y_pos -= button_y_Offset;
    unsubscribeDeviceToChannelItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Delete DeviceToken for user
     */
    auto deleteDeviceTokenLabel = LabelTTF::create("DeleteDeviceToken", "Marker Felt", 24);
    deleteDeviceTokenLabel->setColor(Color3B::WHITE);
    auto deleteDeviceTokenItem  = MenuItemLabel::create(deleteDeviceTokenLabel, CC_CALLBACK_1(TestPushNotificationService::deleteDevice, this));
    y_pos -= button_y_Offset;
    deleteDeviceTokenItem->setPosition(Point(x_pos,y_pos));

    /**
     *  Delete All Devices for user
     */
    auto deleteAllDevicesLabel = LabelTTF::create("DeleteAllDevices", "Marker Felt", 24);
    deleteAllDevicesLabel->setColor(Color3B::WHITE);
    auto deleteAllDevicesItem  = MenuItemLabel::create(deleteAllDevicesLabel, CC_CALLBACK_1(TestPushNotificationService::deleteAllDevices, this));
    y_pos -= button_y_Offset;
    deleteAllDevicesItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Unsubscribe device
     */
    auto unsubscribeDeviceLabel = LabelTTF::create("UnsubscribeDevice", "Marker Felt", 24);
    unsubscribeDeviceLabel->setColor(Color3B::WHITE);
    auto unsubscribeDeviceItem  = MenuItemLabel::create(unsubscribeDeviceLabel, CC_CALLBACK_1(TestPushNotificationService::unsubscribrDevice, this));
    y_pos -= button_y_Offset;
    unsubscribeDeviceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  Resubscribe device
     */
    auto resubscribeDeviceLabel = LabelTTF::create("ResubscribeDevice", "Marker Felt", 24);
    resubscribeDeviceLabel->setColor(Color3B::WHITE);
    auto resubscribeDeviceItem  = MenuItemLabel::create(resubscribeDeviceLabel, CC_CALLBACK_1(TestPushNotificationService::resubscribeDevice, this));
    y_pos -= button_y_Offset;
    resubscribeDeviceItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  SendPushMessageToUser
     */
    auto sendPushToUserLabel = LabelTTF::create("SendPushMessageToUser", "Marker Felt", 24);
    sendPushToUserLabel->setColor(Color3B::WHITE);
    auto sendPushToUserItem  = MenuItemLabel::create(sendPushToUserLabel, CC_CALLBACK_1(TestPushNotificationService::sendPushMessageToUser, this));
    y_pos -= button_y_Offset;
    sendPushToUserItem->setPosition(Point(x_pos,y_pos));
    /**
     *  SendPushJsonToUser
     */
    auto sendPushJsonToUserLabel = LabelTTF::create("SendPushJsonToUser", "Marker Felt", 24);
    sendPushJsonToUserLabel->setColor(Color3B::WHITE);
    auto sendPushJsonToUserItem  = MenuItemLabel::create(sendPushJsonToUserLabel, CC_CALLBACK_1(TestPushNotificationService::sendPushJsonToUser, this));
    y_pos -= button_y_Offset;
    sendPushJsonToUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  SendPushToAll
     */
    auto sendPushToAllLabel = LabelTTF::create("SendPushToAll", "Marker Felt", 24);
    sendPushToAllLabel->setColor(Color3B::WHITE);
    auto sendPushToAllItem  = MenuItemLabel::create(sendPushToAllLabel, CC_CALLBACK_1(TestPushNotificationService::sendPushMessageToAll, this));
    y_pos -= button_y_Offset;
    sendPushToAllItem->setPosition(Point(x_pos,y_pos));
    
    /**
     *  SendPushToAllByType
     */
    auto sendPushToAllByTypeLabel = LabelTTF::create("SendPushToAllByType", "Marker Felt", 24);
    sendPushToAllByTypeLabel->setColor(Color3B::WHITE);
    auto sendPushToAllByTypeItem  = MenuItemLabel::create(sendPushToAllByTypeLabel, CC_CALLBACK_1(TestPushNotificationService::sendPushMessageToAllByType, this));
    y_pos -= button_y_Offset;
    sendPushToAllByTypeItem->setPosition(Point(x_pos,y_pos));
    
    
    /**
     * Create menu, it's an autorelease object
     */
    auto menu = Menu::create(backButtonItem,
                             registerDeviceTokenItem,
                             createChannelItem,
                             subscribeToChannelItem,
                             subscribeDeviceToChannelItem,
                             unsubscribeToChannelItem,
                             unsubscribeDeviceToChannelItem,
                             deleteDeviceTokenItem,
                             deleteAllDevicesItem,
                             unsubscribeDeviceItem,
                             resubscribeDeviceItem,
                             sendPushToUserItem,
                             sendPushJsonToUserItem,
                             sendPushToAllItem,
                             sendPushToAllByTypeItem, NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}


void TestPushNotificationService::registerDeviceToken(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->RegisterDeviceToken(deviceToken, userName, IOS, this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

void TestPushNotificationService::createChannel(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->CreateChannel(channelName,description, this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

void TestPushNotificationService::subscribeToChannel(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->SubscribeToChannel(channelName,userName, this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

void TestPushNotificationService::unsubscribeToChannel(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->UnsubscribeFromChannel(channelName,userName, this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

void TestPushNotificationService::deleteDevice(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->DeleteDeviceToken(deviceToken,userName, this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

void TestPushNotificationService::deleteAllDevices(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->DeleteAllDevices(userName, this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

void TestPushNotificationService::unsubscribrDevice(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->UnsubscribeDevice(deviceToken, userName,this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

void TestPushNotificationService::resubscribeDevice(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->ResubscribeDevice(deviceToken, userName,this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

void TestPushNotificationService::sendPushMessageToUser(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->SendPushMessageToUser(userName,message,this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

void TestPushNotificationService::sendPushJsonToUser(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    std::map<string,string> messageMap;
    messageMap["alert"]= "Hello! How are you?";
    messageMap["badge"]= "2";
    messageMap["sound"]= "Default";
    pushService->SendPushMessageToUser(userName, messageMap,this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

void TestPushNotificationService::sendPushMessageToAll(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->SendPushMessageToAll(message,this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

void TestPushNotificationService::sendPushMessageToAllByType(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->SendPushMessageToAllByType(message,IOS,this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

void TestPushNotificationService::subscribeDeviceToChannel(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->SubscribeToChannel(channelName,userName,deviceToken, IOS, this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}
void TestPushNotificationService::unsubscribeDeviceToChannel(Ref *sender)
{
    Util::setTraceEnabled(true);
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    
    pushService->UnsubscribeDeviceToChannel(channelName,userName,deviceToken,this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

/**
 * Callbacks
 */

void TestPushNotificationService::onPushRequestCompleted(App42CallBack *sender, void *response)
{
    App42PushNotificationResponse *pushResponse = (App42PushNotificationResponse*)response;
    printf("\ncode=%d",pushResponse->getCode());
    printf("\nResponse Body=%s",pushResponse->getBody().c_str());
    if (!pushResponse->isSuccess)
    {
        printf("\nerrordetails:%s",pushResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",pushResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",pushResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",pushResponse->httpErrorCode);
    }
    else
    {
        for(std::vector<App42PushNotification>::iterator it = pushResponse->notifications.begin(); it != pushResponse->notifications.end(); ++it)
        {
            printf("\n UserName=%s",it->userName.c_str());
            printf("\n Message=%s\n",it->message.c_str());
            
            for(std::vector<App42Channel>::iterator channel = it->channelArray.begin(); channel != it->channelArray.end(); ++channel)
            {
                printf("\n Channel Name=%s",channel->channelName.c_str());
                printf("\n Description=%s\n",channel->description.c_str());
            }
        }
    }
}


void TestPushNotificationService::menuCloseCallback(Ref* pSender)
{
    MenuItem *item = (MenuItem*)pSender;
    int senderTag = item->getTag();
    switch (senderTag)
    {
        case GO_HOME:
        {
            // create a scene. it's an autorelease object
            auto scene = TestHome::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        default:
            break;
    }
}