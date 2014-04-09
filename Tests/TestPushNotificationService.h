//
//  TestPushNotificationService.h
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#ifndef __App42Cocos2dXSDK_3_0Beta2_Sample__TestPushNotificationService__
#define __App42Cocos2dXSDK_3_0Beta2_Sample__TestPushNotificationService__

#include <iostream>
#include "cocos2d.h"
#include "App42API.h"

class TestPushNotificationService : public cocos2d::Layer, public App42CallBack
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestPushNotificationService);
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    void registerDeviceToken(Ref *sender);
    void createChannel(Ref *sender);
    void subscribeToChannel(Ref *sender);
    void unsubscribeToChannel(Ref *sender);
    void subscribeDeviceToChannel(Ref *sender);
    void unsubscribeDeviceToChannel(Ref *sender);
    void deleteDevice(Ref *sender);
    void deleteAllDevices(Ref *sender);
    void unsubscribrDevice(Ref *sender);
    void resubscribeDevice(Ref *sender);
    
    void sendPushMessageToUser(Ref *sender);
    void sendPushJsonToUser(Ref *sender);
    void sendPushMessageToAll(Ref *sender);
    void sendPushMessageToAllByType(Ref *sender);
    
    // a selector callback
    void onPushRequestCompleted(App42CallBack *sender, void *response);
    void menuCloseCallback(Ref* pSender);
    
private:
    std::string apiKey;
    std::string secretKey;
    std::string channelName;
    std::string description;
    std::string userName;
    std::string deviceToken;
    std::string message;

};

#endif /* defined(__App42Cocos2dXSDK_3_0Beta2_Sample__TestPushNotificationService__) */
