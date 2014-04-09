App42_Cocos2dX_SDK
==================

Migration Note:-

__The way of providing response callback in every API is changed in this release__

Please follow the steps mentioned below for migrating your build from previous version to this version:
```
//TestPushNotificationService.h
#include "App42API.h"

// Your Callback Class must inherit App42CallBack in order to define callbacks
class TestPushNotificationService : public cocos2d::Layer, public App42CallBack
{
   void registerDeviceToken(Ref *sender);
   
   //Callback method declaration
   void onPushRequestCompleted(App42CallBack *sender, void *response);
}
```

```
//TestPushNotificationService.cpp

void TestPushNotificationService::registerDeviceToken(Ref *sender)
{
	//Calling PushNotification service API
    PushNotificationService *pushService = App42API::BuildPushNotificationService();
    pushService->RegisterDeviceToken(deviceToken, userName, IOS, this, app42callfuncND_selector(TestPushNotificationService::onPushRequestCompleted));
}

//Callback method definition
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

```

__To know more you can go through the Tests__
