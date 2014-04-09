//
//  TestRewardService.h
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#ifndef __App42Cocos2dXSDK_3_0Beta2_Sample__TestRewardService__
#define __App42Cocos2dXSDK_3_0Beta2_Sample__TestRewardService__

#include <iostream>
#include "cocos2d.h"
#include "App42API.h"

class TestRewardService : public cocos2d::Layer, public App42CallBack
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestRewardService);
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    void createUser();
    void authenticateUser();
    void getUserWithUserName();
    void getAllUser();
    
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
private:
    std::string apiKey;
    std::string secretKey;
    
};

#endif /* defined(__App42Cocos2dXSDK_3_0Beta2_Sample__TestRewardService__) */
