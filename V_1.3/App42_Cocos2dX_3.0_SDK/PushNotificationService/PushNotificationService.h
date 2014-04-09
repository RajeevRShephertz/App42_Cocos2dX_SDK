//
//  PushNotificationService.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 21/10/13.
//
//

#ifndef __App42CPPSDK__PushNotificationService__
#define __App42CPPSDK__PushNotificationService__

#include <iostream>
#include "App42Service.h"

using namespace std;

typedef enum DeviceType
{
    IOS,
    ANDROID,
    WP7,
    NOKIAX,
}DeviceType;

class PushNotificationService : public App42Service
{
    
private:
    PushNotificationService();
	static PushNotificationService* _instance;
    
    inline const char *getDeviceType(DeviceType deviceType)
    {
        static const char *strings[] = {"iOS", "ANDROID", "WP7","NokiaX"};
        
        return strings[deviceType];
    }
    
public:
    
    
    
	/**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
    static PushNotificationService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of PushNotificationService.
     *
     * @return PushNotificationService - PushNotificationService Object
     */
	static PushNotificationService* getInstance();
    
    
    void CreateChannel(string channel,string description,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void RegisterDeviceToken(string deviceToken, string userName, DeviceType deviceType, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void SendPushMessageToUser(string username,  string message, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void SendPushMessageToUser(string userName, map<string, string>messageMap, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void SendPushMessageToAll(string message, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void SubscribeToChannel(string channel, string userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void SubscribeToChannel(string userName,string channelName, string deviceToken, DeviceType deviceType, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void UnsubscribeFromChannel(string channel, string userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void UnsubscribeDeviceToChannel(string userName,string channelName, string deviceToken, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void SendPushMessageToChannel(string channel, string message, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void SendPushMessageToChannel(string channel, map<string, string>messageMap, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    void DeleteDeviceToken(string deviceToken, string userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    void DeleteAllDevices(string userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void UnsubscribeDevice(string deviceToken, string userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    void ResubscribeDevice(string deviceToken, string userName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void SendPushMessageToAllByType(string message,DeviceType deviceType, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
};
#endif /* defined(__App42CPPSDK__PushNotificationService__) */
