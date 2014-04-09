//
//  TestHome.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 02/04/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__TestHome__
#define __App42Cocos2dX3_0Sample__TestHome__

#include <iostream>
#include "cocos2d.h"
#include "App42API.h"

USING_NS_CC;
class TestHome : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestHome);
};
#endif /* defined(__App42Cocos2dX3_0Sample__TestHome__) */
