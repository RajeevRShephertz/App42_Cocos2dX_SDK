//
//  TestEmailService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 08/04/14.
//
//

#include "TestEmailService.h"
#include "TestHome.h"


#define GO_HOME 1081

USING_NS_CC;

Scene* TestEmailService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestEmailService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestEmailService::init()
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
     * Back Button
     */
    auto backButtonItem = MenuItemImage::create(
                                                "BackButton.png",
                                                "BackButton.png",
                                                CC_CALLBACK_1(TestEmailService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(x_pos ,origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * ConfigureMail
     */
    auto configureMailLabel = LabelTTF::create("ConfigureMail", "Marker Felt", 24);
    configureMailLabel->setColor(Color3B::WHITE);
    auto configureMailItem  = MenuItemLabel::create(configureMailLabel, CC_CALLBACK_1(TestEmailService::configureEmail, this));
    configureMailItem->setPosition(Point(x_pos,y_pos));

    
    /**
     * RemoveConfiguration
     */
    auto removeConfigurationLabel = LabelTTF::create("RemoveConfiguration", "Marker Felt", 24);
    removeConfigurationLabel->setColor(Color3B::WHITE);
    auto removeConfigurationItem  = MenuItemLabel::create(removeConfigurationLabel, CC_CALLBACK_1(TestEmailService::removeConfiguration, this));
    y_pos -= button_y_Offset;
    removeConfigurationItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetConfigurations
     */
    auto getConfigurationLabel = LabelTTF::create("GetConfigurations", "Marker Felt", 24);
    getConfigurationLabel->setColor(Color3B::WHITE);
    auto getConfigurationItem  = MenuItemLabel::create(getConfigurationLabel, CC_CALLBACK_1(TestEmailService::getConfiguration, this));
    y_pos -= button_y_Offset;
    getConfigurationItem->setPosition(Point(x_pos,y_pos));
    
    
    /**
     * SendMail
     */
    auto sendMailLabel = LabelTTF::create("SendMail", "Marker Felt", 24);
    sendMailLabel->setColor(Color3B::WHITE);
    auto sendMailItem  = MenuItemLabel::create(sendMailLabel, CC_CALLBACK_1(TestEmailService::sendMail, this));
    y_pos -= button_y_Offset;
    sendMailItem->setPosition(Point(x_pos,y_pos));
    
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(backButtonItem,
                             configureMailItem,
                             removeConfigurationItem,
                             getConfigurationItem,
                             sendMailItem, NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void TestEmailService::configureEmail(Ref *sender)
{
    Util::setTraceEnabled(true);
    EmailService *emailService = App42API::BuildEmailService();
    string emailHost = "smtp.gmail.com";
    string emailId = "sachin.grover@shephertz.co.in";
    emailService->createMailConfiguration(emailHost, 465, emailId, "1990sachinn", true, this, app42callfuncND_selector(TestEmailService::onEmailRequestCompleted));
}

void TestEmailService::removeConfiguration(Ref *sender)
{
    Util::setTraceEnabled(true);
    EmailService *emailService = App42API::BuildEmailService();
    string emailId = "sachin.grover@shephertz.co.in";
    emailService->removeEmailConfiguration(emailId,this, app42callfuncND_selector(TestEmailService::onEmailRequestCompleted));
}

void TestEmailService::getConfiguration(Ref *sender)
{
    Util::setTraceEnabled(true);
    EmailService *emailService = App42API::BuildEmailService();
    emailService->getEmailConfigurations(this, app42callfuncND_selector(TestEmailService::onEmailRequestCompleted));
}

void TestEmailService::sendMail(Ref *sender)
{
    Util::setTraceEnabled(true);
    EmailService *emailService = App42API::BuildEmailService();
    
    string sendTo = "rajeev.ranjan@shephertz.co.in";
    string fromEmail = "sachin.grover@shephertz.co.in";
    string sub = "Test";
    string msg = "Test Email Service";
    
    emailService->sendMail(sendTo, sub, msg,fromEmail,PLAIN_TEXT_MIME_TYPE,this, app42callfuncND_selector(TestEmailService::onEmailRequestCompleted));
}

/**
 * Callback Methods
 */
void TestEmailService::onEmailRequestCompleted(App42CallBack *sender, void *response)
{
    App42EmailResponse *emailResponse = (App42EmailResponse*)response;
    printf("\ncode=%d",emailResponse->getCode());
    printf("\nResponse Body=%s",emailResponse->getBody().c_str());

    if(!emailResponse->isSuccess)
    {
        printf("\nerrordetails:%s",emailResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",emailResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",emailResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",emailResponse->httpErrorCode);
    }
    else
    {
        printf("\n From=%s",emailResponse->from.c_str());
        printf("\n To=%s",emailResponse->to.c_str());
        printf("\n Subject=%s",emailResponse->subject.c_str());
        printf("\n Body=%s",emailResponse->body.c_str());

        for(std::vector<App42Configuration>::iterator it = emailResponse->configurationArray.begin(); it != emailResponse->configurationArray.end(); ++it)
        {
            printf("\n EmailId=%s",it->emailId.c_str());
            printf("\n Host=%s\n",it->host.c_str());
            printf("\n Port=%d\n",it->port);
            printf("\n SSL=%d\n",it->ssl);
        }
    }
}


void TestEmailService::menuCloseCallback(Ref* pSender)
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