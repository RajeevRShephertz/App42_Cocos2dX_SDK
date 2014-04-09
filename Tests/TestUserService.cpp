//
//  TestUserService.cpp
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#include "TestUserService.h"
#include "TestHome.h"


#define GO_HOME 1011


USING_NS_CC;

Scene* TestUserService::createScene()
{
    // 'scene' is an autorelease Object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease Object
    auto layer = TestUserService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestUserService::init()
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
    float x_pos = origin.x + visibleSize.width/4;
    
    
    /**
     * Create User
     */
    auto createUserLabel = LabelTTF::create("Create User", "Marker Felt", 24);
    createUserLabel->setColor(Color3B::WHITE);
    auto createUserItem  = MenuItemLabel::create(createUserLabel, CC_CALLBACK_1(TestUserService::createUser, this));
    createUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Create User With Roles
     */
    auto createUserWithRolesLabel = LabelTTF::create("CreateUserWithRoles", "Marker Felt", 24);
    createUserWithRolesLabel->setColor(Color3B::WHITE);
    auto createUserWithRolesItem  = MenuItemLabel::create(createUserWithRolesLabel, CC_CALLBACK_1(TestUserService::createUserWithRoles, this));
    y_pos = y_pos-button_y_Offset;
    createUserWithRolesItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * AssignRoles
     */
    auto assignRolesLabel = LabelTTF::create("AssignRoles", "Marker Felt", 24);
    assignRolesLabel->setColor(Color3B::WHITE);
    auto assignRolesItem  = MenuItemLabel::create(assignRolesLabel, CC_CALLBACK_1(TestUserService::assignRoles, this));
    y_pos = y_pos-button_y_Offset;
    assignRolesItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Authenticate User
     */
    auto authenticateUserLabel = LabelTTF::create("Authenticate User", "Marker Felt", 24);
    authenticateUserLabel->setColor(Color3B::WHITE);
    auto authenticateUserItem  = MenuItemLabel::create(authenticateUserLabel, CC_CALLBACK_1(TestUserService::authenticateUser, this));
    y_pos = y_pos-button_y_Offset;
    authenticateUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get User With User Name
     */
    auto getUserLabel = LabelTTF::create("Get User", "Marker Felt", 24);
    getUserLabel->setColor(Color3B::WHITE);
    auto getUserItem  = MenuItemLabel::create(getUserLabel, CC_CALLBACK_1(TestUserService::getUserWithUserName, this));
    y_pos = y_pos-button_y_Offset;
    getUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get User With EmailID
     */
    auto getUserByEmailLabel = LabelTTF::create("GetUserByEmailId", "Marker Felt", 24);
    getUserByEmailLabel->setColor(Color3B::WHITE);
    auto getUserByEmailItem  = MenuItemLabel::create(getUserByEmailLabel, CC_CALLBACK_1(TestUserService::getUserWithEmailId, this));
    y_pos = y_pos-button_y_Offset;
    getUserByEmailItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get All Users
     */
    auto getAllUserLabel = LabelTTF::create("GetAllUser", "Marker Felt", 24);
    getAllUserLabel->setColor(Color3B::WHITE);
    auto getAllUserItem  = MenuItemLabel::create(getAllUserLabel, CC_CALLBACK_1(TestUserService::getAllUser, this));
    y_pos = y_pos-button_y_Offset;
    getAllUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get All Users By Paging
     */
    auto getAllUserByPagingLabel = LabelTTF::create("GetAllUserByPaging", "Marker Felt", 24);
    getAllUserByPagingLabel->setColor(Color3B::WHITE);
    auto getAllUserByPagingItem  = MenuItemLabel::create(getAllUserByPagingLabel, CC_CALLBACK_1(TestUserService::getAllUsersByPaging, this));
    y_pos = y_pos-button_y_Offset;
    getAllUserByPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Get All Users Count
     */
    auto getAllUsersCountLabel = LabelTTF::create("GetAllUsersCount", "Marker Felt", 24);
    getAllUsersCountLabel->setColor(Color3B::WHITE);
    auto getAllUsersCountItem  = MenuItemLabel::create(getAllUsersCountLabel, CC_CALLBACK_1(TestUserService::getAllUsersCount, this));
    y_pos = y_pos-button_y_Offset;
    getAllUsersCountItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Lock User
     */
    auto lockUserLabel = LabelTTF::create("LockUser", "Marker Felt", 24);
    lockUserLabel->setColor(Color3B::WHITE);
    auto lockUserItem  = MenuItemLabel::create(lockUserLabel, CC_CALLBACK_1(TestUserService::lockUser, this));
    y_pos = y_pos-button_y_Offset;
    lockUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * UnLock User
     */
    auto unlockUserLabel = LabelTTF::create("UnLockUser", "Marker Felt", 24);
    unlockUserLabel->setColor(Color3B::WHITE);
    auto unlockUserItem  = MenuItemLabel::create(unlockUserLabel, CC_CALLBACK_1(TestUserService::unlockUser, this));
    y_pos = y_pos-button_y_Offset;
    unlockUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetLockedUsers
     */
    auto getAllLockedUsersLabel = LabelTTF::create("GetLockedUsers", "Marker Felt", 24);
    getAllLockedUsersLabel->setColor(Color3B::WHITE);
    auto getAllLockedUsersItem  = MenuItemLabel::create(getAllLockedUsersLabel, CC_CALLBACK_1(TestUserService::getLockedUsers, this));
    y_pos = y_pos-button_y_Offset;
    getAllLockedUsersItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetLockedUsersByPaging
     */
    auto getLockedUsersPagingLabel = LabelTTF::create("GetLockedUsersByPaging", "Marker Felt", 24);
    getLockedUsersPagingLabel->setColor(Color3B::WHITE);
    auto getLockedUsersPagingItem  = MenuItemLabel::create(getLockedUsersPagingLabel, CC_CALLBACK_1(TestUserService::getLockedUsersByPaging, this));
    y_pos = y_pos-button_y_Offset;
    getLockedUsersPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetLockedUsersCount
     */
    auto getAllLockedUsersCountLabel = LabelTTF::create("GetLockedUsersCount", "Marker Felt", 24);
    getAllLockedUsersCountLabel->setColor(Color3B::WHITE);
    auto getAllLockedUsersCountItem  = MenuItemLabel::create(getAllLockedUsersCountLabel, CC_CALLBACK_1(TestUserService::getLockedUsersCount, this));
    y_pos = y_pos-button_y_Offset;
    getAllLockedUsersCountItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Update Email
     */
    auto updateEmailLabel = LabelTTF::create("UpdateEmail", "Marker Felt", 24);
    updateEmailLabel->setColor(Color3B::WHITE);
    auto updateEmailItem  = MenuItemLabel::create(updateEmailLabel, CC_CALLBACK_1(TestUserService::updateEmail, this));
    y_pos = visibleSize.height-button_y_Offset;;
    x_pos += visibleSize.width/2;
    updateEmailItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Delete User
     */
    auto deleteUserLabel = LabelTTF::create("DeleteUser", "Marker Felt", 24);
    deleteUserLabel->setColor(Color3B::WHITE);
    auto deleteUserItem  = MenuItemLabel::create(deleteUserLabel, CC_CALLBACK_1(TestUserService::deleteUser, this));
    y_pos = y_pos-button_y_Offset;
    deleteUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Change User Password
     */
    auto changePwdLabel = LabelTTF::create("ChangePassword", "Marker Felt", 24);
    changePwdLabel->setColor(Color3B::WHITE);
    auto changePwdItem  = MenuItemLabel::create(changePwdLabel, CC_CALLBACK_1(TestUserService::changePassword, this));
    y_pos = y_pos-button_y_Offset;
    changePwdItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Reset User Password
     */
    auto resetPwdLabel = LabelTTF::create("ResetPassword", "Marker Felt", 24);
    resetPwdLabel->setColor(Color3B::WHITE);
    auto resetPwdItem  = MenuItemLabel::create(resetPwdLabel, CC_CALLBACK_1(TestUserService::resetPassword, this));
    y_pos = y_pos-button_y_Offset;
    resetPwdItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Create or Update User Profile
     */
    auto profileLabel = LabelTTF::create("Create/UpdateUserProfile", "Marker Felt", 24);
    profileLabel->setColor(Color3B::WHITE);
    auto profileItem  = MenuItemLabel::create(profileLabel, CC_CALLBACK_1(TestUserService::createOrUpdateProfile, this));
    y_pos = y_pos-button_y_Offset;
    profileItem->setPosition(Point(x_pos,y_pos));

    /**
     * Get Users By Profile
     */
    auto getUsersByProfileLabel = LabelTTF::create("GetUsersByProfile", "Marker Felt", 24);
    getUsersByProfileLabel->setColor(Color3B::WHITE);
    auto getUsersByProfileItem  = MenuItemLabel::create(getUsersByProfileLabel, CC_CALLBACK_1(TestUserService::getUserByProfileData, this));
    y_pos = y_pos-button_y_Offset;
    getUsersByProfileItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * LogOut
     */
    auto logoutLabel = LabelTTF::create("LogOut", "Marker Felt", 24);
    logoutLabel->setColor(Color3B::WHITE);
    auto logoutItem  = MenuItemLabel::create(logoutLabel, CC_CALLBACK_1(TestUserService::logout, this));
    y_pos = y_pos-button_y_Offset;
    logoutItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * GetRolesByUser
     */
    auto getRolesByUserLabel = LabelTTF::create("GetRolesByUser", "Marker Felt", 24);
    getRolesByUserLabel->setColor(Color3B::WHITE);
    auto getRolesByUserItem  = MenuItemLabel::create(getRolesByUserLabel, CC_CALLBACK_1(TestUserService::getRolesByUser, this));
    y_pos = y_pos-button_y_Offset;
    getRolesByUserItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * Back Button
     */
    auto backButtonItem = MenuItemImage::create(
                                           "BackButton.png",
                                           "BackButton.png",
                                           CC_CALLBACK_1(TestUserService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(origin.x + visibleSize.width/2 ,
                                 origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);
    
    /**
     * Create Menu
     */
    auto menu = Menu::create(createUserItem,
                             createUserWithRolesItem,
                             assignRolesItem,
                             authenticateUserItem,
                             getUserItem,
                             getUserByEmailItem,
                             backButtonItem,
                             getAllUserItem,
                             getAllUserByPagingItem,
                             getAllUsersCountItem,
                             lockUserItem,
                             unlockUserItem,
                             getAllLockedUsersItem,
                             getLockedUsersPagingItem,
                             getAllLockedUsersCountItem,
                             updateEmailItem,
                             deleteUserItem,
                             changePwdItem,
                             resetPwdItem,
                             profileItem,
                             getUsersByProfileItem,
                             logoutItem,
                             getRolesByUserItem,NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}



void TestUserService::createUser(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->CreateUser("Rajeev_1235452334", "9934273686", "rajeev123545223344@gmail.com",this,app42callfuncND_selector(TestUserService::onUserRequestCompleted));
    
}

void TestUserService::createUserWithRoles(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    
    vector<string>roles;
    roles.push_back("s_admin");
    roles.push_back("s_manager");
    roles.push_back("s_techlead");

    
    user->CreateUser("Rajeev_Ranjan1", "9934273686", "rajeev.ranjan1@gmail.com",roles,this,app42callfuncND_selector(TestUserService::onUserRequestCompleted));
    
}


void TestUserService::assignRoles(Ref *sender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    
    vector<string>roles;
    roles.push_back("s_Manager");
    
    user->AssignRoles("Rajeev_Ranjan1", roles, this,app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::authenticateUser(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->Authenticate("Rajeev_1234", "gsp.<:VYT95", this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getUserWithUserName(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->GetUser("Rajeev_1234", this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));

}

void TestUserService::getUserWithEmailId(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->GetUserByEmailId("rajeev123545@gmail.com", this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
    
}

void TestUserService::getAllUser(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->GetAllUsers(this,app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getAllUsersByPaging(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->GetAllUsers(2,1,this,app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}


void TestUserService::getAllUsersCount(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->GetAllUsersCount(this,app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::lockUser(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->LockUser("Rajeev_1234",this,app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::unlockUser(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->UnlockUser("Rajeev_1234",this,app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getLockedUsers(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->GetLockedUsers(this,app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getLockedUsersByPaging(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->GetLockedUsers(1,0,this,app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}


void TestUserService::getLockedUsersCount(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->GetLockedUsersCount(this,app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::updateEmail(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->UpdateEmail("Rajeev_1234","rajeev.ranjan@shephertz.co.in", this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::deleteUser(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->DeleteUser("Rajeev_123545", this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::changePassword(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->ChangeUserPassword("Rajeev_1234", "gsp.<:VYT95", "9934273686r", this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::resetPassword(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *user = App42API::BuildUserService();
    user->ResetUserPassword("Rajeev_1234", this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}


void TestUserService::createOrUpdateProfile(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    App42User user;
    user.userName = "Rajeev_1234";
    App42UserProfile userProfile;
    userProfile.firstName = "Rajeev";
    userProfile.lastName = "Ranjan";
    userProfile.mobile = "9934273686";
    user.profile = userProfile;
    userService->createOrUpdateProfile(user, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getUserByProfileData(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();

    App42UserProfile userProfile;
    userProfile.firstName = "Rajeev";
    userProfile.lastName = "Ranjan";
    userProfile.mobile = "9934273686";
    userProfile.setSex(userProfile.MALE);
    printf("Sex=%s",userProfile.getSex().c_str());
    userService->GetUsersByProfileData(userProfile, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::logout(Ref* pSender)
{
    Util::setTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    string sessionId = "";
    userService->Logout(sessionId, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}

void TestUserService::getRolesByUser(Ref *sender)
{
    Util::setTraceEnabled(true);
    UserService *userService = App42API::BuildUserService();
    
    string userName = "Rajeev_Ranjan1";
    userService->GetRolesByUser(userName, this, app42callfuncND_selector(TestUserService::onUserRequestCompleted));
}




/**
 * Callback Methods
 */
void TestUserService::onUserRequestCompleted(App42CallBack *sender, void *response)
{
    App42UserResponse *userResponse = (App42UserResponse*)response;
    printf("\ncode=%d",userResponse->getCode());
    printf("\nResponse Body=%s",userResponse->getBody().c_str());
    printf("\nTotalRecords=%d",userResponse->getTotalRecords());
    if (!userResponse->isSuccess)
    {
        printf("\nerrordetails:%s",userResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",userResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",userResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",userResponse->httpErrorCode);
    }
    else
    {
        for(std::vector<App42User>::iterator it = userResponse->users.begin(); it != userResponse->users.end(); ++it)
        {
            printf("\n UserName=%s",it->userName.c_str());
            printf("\n Email=%s",it->email.c_str());
            printf("\n isAccountLocked=%d",it->isAccountLocked);
            printf("\n FirstName=%s",it->profile.firstName.c_str());
            printf("\n LastName=%s",it->profile.lastName.c_str());
            printf("\n Mobile=%s",it->profile.mobile.c_str());
            printf("\n Sex=%s",it->profile.getSex().c_str());
            printf("\n Line1=%s",it->profile.line1.c_str());
            
            
            std::vector<string>::iterator iit;
            
            for(iit=it->roleList.begin(); iit!=it->roleList.end(); ++iit)
            {
                printf("\n%s",iit->c_str());
            }
        }
    }
}


void TestUserService::menuCloseCallback(Ref* pSender)
{
    MenuItem *item = (MenuItem*)pSender;
    int senderTag = item->getTag();
    switch (senderTag)
    {
        case GO_HOME:
        {
            // create a scene. it's an autorelease Object
            auto scene = TestHome::createScene();
            
            // run
            Director::getInstance()->replaceScene(scene);
            
            break;
        }
        default:
            break;
    }
}