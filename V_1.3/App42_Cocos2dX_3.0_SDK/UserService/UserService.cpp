//
//  UserService.cpp
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 08/10/13.
//
//

#include "UserService.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "cocos-ext.h"
#include "Connector.h"

using namespace cocos2d;

// define the static..
UserService* UserService::_instance = NULL;

UserService::UserService()
{
    
}

UserService* UserService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new UserService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

UserService* UserService::getInstance()
{
	return _instance;
}

void UserService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}

string UserService::getJsonStringFromVector(vector<string>roles)
{
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *rolesJSON = cJSON_CreateArray();

    std::vector<string>::iterator it;
    
    for(it=roles.begin(); it!=roles.end(); ++it)
    {
        cJSON_AddItemToArray(rolesJSON, cJSON_CreateString(it->c_str()));
    }
    cJSON_AddItemReferenceToObject(bodyJSON, "role", rolesJSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(rolesJSON);
    cJSON_Delete(bodyJSON);

    free(cptrFormatted);
    
    return bodyString;

}

string UserService::buildCreateUserBody(string username, string password, string email,string roleList)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *userJSON = cJSON_CreateObject();
    
    // first construct the user
    if (username.length())
    {
        cJSON_AddStringToObject(userJSON, "userName", username.c_str());
    }
    
    if (email.length())
    {
        cJSON_AddStringToObject(userJSON, "email", email.c_str());
    }
    
    if (password.length())
    {
        cJSON_AddStringToObject(userJSON, "password", password.c_str());
    }
    
    if (roleList.length())
    {
        cJSON_AddStringToObject(userJSON, "roles", roleList.c_str());
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "user", userJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(userJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

string UserService::buildChangePasswordBody(string username, string oldPwd, string newPwd)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *userJSON = cJSON_CreateObject();
    
    // first construct the user
    if (username.length())
    {
        cJSON_AddStringToObject(userJSON, "userName", username.c_str());
    }
    
    if (oldPwd.length())
    {
        cJSON_AddStringToObject(userJSON, "oldPassword", oldPwd.c_str());
    }
    
    if (newPwd.length())
    {
        cJSON_AddStringToObject(userJSON, "newPassword", newPwd.c_str());
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "user", userJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(userJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

string UserService::buildProfileData(App42UserProfile userProfile)
{
    string profileData = "";
    //construct profile data
    if (userProfile.firstName.length())
    {
        profileData.append("first_name:" + userProfile.firstName + "!");
    }
    
    if (userProfile.lastName.length())
    {
        profileData.append("last_name:" + userProfile.lastName + "!");
    }
    
    if (userProfile.getSex().length())
    {
        profileData.append("sex:" + userProfile.getSex() + "!");
    }
    
    
    if (userProfile.mobile.length())
    {
        profileData.append("mobile:" + userProfile.mobile + "!");
    }
    
    
    if (userProfile.line1.length())
    {
        profileData.append("line1:" + userProfile.line1 + "!");
    }
    
    
    if (userProfile.line2.length())
    {
        profileData.append("line2:" + userProfile.line2 + "!");
    }
    
    
    if (userProfile.city.length())
    {
        profileData.append("city:" + userProfile.city + "!");
    }
    
    
    if (userProfile.state.length())
    {
        profileData.append("state:" + userProfile.state + "!");
    }
    
    
    if (userProfile.country.length())
    {
        profileData.append("country:" + userProfile.country + "!");
    }
    
    
    if (userProfile.pincode.length())
    {
        profileData.append("pincode:" + userProfile.pincode + "!");
    }
    
    
    if (userProfile.homeLandLine.length())
    {
        profileData.append("home_land_line:" + userProfile.homeLandLine + "!");
    }
    
    
    if (userProfile.officeLandLine.length())
    {
        profileData.append("office_land_line:" + userProfile.officeLandLine + "!");
    }
    
    
    if (userProfile.dateOfBirth.length())
    {
        profileData.append("date_of_birth:" + userProfile.dateOfBirth + "!");
    }
    
    return profileData;
}

string UserService::buildCreateOrUpdateProfileBody(App42User user)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *userJSON = cJSON_CreateObject();
    cJSON *profileJSON = cJSON_CreateObject();

    // first construct the user
    if (user.userName.length())
    {
        cJSON_AddStringToObject(userJSON, "userName", user.userName.c_str());
    }
    
    //construct profile
    App42UserProfile userProfile = user.profile;
    if (userProfile.firstName.length())
    {
        cJSON_AddStringToObject(profileJSON, "firstName", userProfile.firstName.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "firstName", "");
        
    if (userProfile.lastName.length())
    {
        cJSON_AddStringToObject(profileJSON, "lastName", userProfile.lastName.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "lastName", "");
    
    if (userProfile.getSex().length())
    {
        cJSON_AddStringToObject(profileJSON, "sex", userProfile.getSex().c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "sex", "");
    
    if (userProfile.mobile.length())
    {
        cJSON_AddStringToObject(profileJSON, "mobile", userProfile.mobile.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "mobile", "");
    
    if (userProfile.line1.length())
    {
        cJSON_AddStringToObject(profileJSON, "line1", userProfile.line1.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "line1", "");

    if (userProfile.line2.length())
    {
        cJSON_AddStringToObject(profileJSON, "line2", userProfile.line2.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "line2", "");
    
    if (userProfile.city.length())
    {
        cJSON_AddStringToObject(profileJSON, "city", userProfile.city.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "city", "");
    
    if (userProfile.state.length())
    {
        cJSON_AddStringToObject(profileJSON, "state", userProfile.state.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "state", "");
    
    if (userProfile.country.length())
    {
        cJSON_AddStringToObject(profileJSON, "country", userProfile.country.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "country", "");
    
    if (userProfile.pincode.length())
    {
        cJSON_AddStringToObject(profileJSON, "pincode", userProfile.pincode.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "pincode", "");
    
    if (userProfile.homeLandLine.length())
    {
        cJSON_AddStringToObject(profileJSON, "homeLandLine", userProfile.homeLandLine.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "homeLandLine", "");
    
    if (userProfile.officeLandLine.length())
    {
        cJSON_AddStringToObject(profileJSON, "officeLandLine", userProfile.officeLandLine.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "officeLandLine", "");
    
    if (userProfile.dateOfBirth.length())
    {
        cJSON_AddStringToObject(profileJSON, "dateOfBirth", userProfile.dateOfBirth.c_str());
    }
    else
        cJSON_AddStringToObject(profileJSON, "dateOfBirth", "");
    
    char *profileJSONStr = cJSON_PrintUnformatted(profileJSON);
    cJSON_AddStringToObject(userJSON, "profileData", profileJSONStr);
    free(profileJSONStr);
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "user", userJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(profileJSON);
    cJSON_Delete(userJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

string UserService::buildLogoutBody(string sessionId)
{
    
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON *app42JSON = cJSON_CreateObject();
    cJSON *userJSON = cJSON_CreateObject();
    
    // first construct the user
    if (sessionId.length())
    {
        cJSON_AddStringToObject(userJSON, "id", sessionId.c_str());
    }
    
    // add user to app42
    cJSON_AddItemReferenceToObject(app42JSON, "session", userJSON);
    
    // add app42 to body
    cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
    
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
    string bodyString = cptrFormatted;
    
    cJSON_Delete(userJSON);
    cJSON_Delete(app42JSON);
    cJSON_Delete(bodyJSON);
    
    free(cptrFormatted);
    
    return bodyString;
    
}

void UserService::CreateUser(string username, string password, string email,App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfStringNullOrBlank(password, "Password");
        Util::throwExceptionIfStringNullOrBlank(email, "Email");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    map<string, string> postMap;
    populateSignParams(postMap);
    string createUserbody = buildCreateUserBody(username, password, email,"");
    postMap["body"] = createUserbody;
    
    string signature = Util::signMap(secretKey, postMap);
    string timestamp = Util::getTimeStamp();
    
    string baseUrl = getBaseUrl("user");
    baseUrl.append("?");
   // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
   // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    Util::executePost(baseUrl, headers, createUserbody.c_str(), response, httpresponse_selector(App42UserResponse::onComplete));
    
}


void UserService::CreateUser(string username, string password, string email,vector<string>roleList,App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfStringNullOrBlank(password, "Password");
        Util::throwExceptionIfStringNullOrBlank(email, "Email");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    map<string, string> postMap;
    populateSignParams(postMap);
    string createUserbody = buildCreateUserBody(username, password, email,getJsonStringFromVector(roleList));
    postMap["body"] = createUserbody;
    
    
    string signature = Util::signMap(secretKey, postMap);
    string timestamp = Util::getTimeStamp();
    
    string baseUrl = getBaseUrl("user/role");
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    Util::executePost(encodedUrl, headers, createUserbody.c_str(), response, httpresponse_selector(App42UserResponse::onComplete));
    
}


void UserService::AssignRoles(string userName, vector<string> roleList,App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    map<string, string> postMap;
    populateSignParams(postMap);
    string createUserbody = buildCreateUserBody(userName, "", "",getJsonStringFromVector(roleList));
    postMap["body"] = createUserbody;
    
    
    string signature = Util::signMap(secretKey, postMap);
    string timestamp = Util::getTimeStamp();
    
    string baseUrl = getBaseUrl("user/assignrole");
    baseUrl.append("?");
    string encodedUrl = url_encode(baseUrl);
    // Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    // Util::app42Trace("\n createUserbody = %s",createUserbody.c_str());
    
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    Util::executePost(encodedUrl, headers, createUserbody.c_str(), response, httpresponse_selector(App42UserResponse::onComplete));
    
}

void UserService::Authenticate(string username, string password, App42CallBack *pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfStringNullOrBlank(password, "Password");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
        
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack *)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    map<string, string> postMap;
    populateSignParams(postMap);
    string postBody = buildCreateUserBody(username, password, "","");
    postMap["body"] = postBody;
    
    string signature = Util::signMap(secretKey, postMap);
    string timestamp = Util::getTimeStamp();
    // now build query string and append it to the url
    //string queryString = Util::BuildQueryString(apiKey, timestamp, VERSION, signature);
    
    string baseUrl = getBaseUrl("user/authenticate");
    baseUrl.append("?");//.append(queryString);
    //Util::app42Trace("\n baseUrl = %s",baseUrl.c_str());
    //Util::app42Trace("\n createUserbody = %s",postBody.c_str());
    
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    Util::executePost(baseUrl, headers, postBody.c_str(), response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::GetUser(string username, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    string resource = "user/";
	resource.append(username);
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	getMap["userName"] = username;
	string signature = Util::signMap(secretKey, getMap);
    //string queryString = Util::BuildQueryString(apiKey, timestamp, VERSION, signature);
    url.append("?");//.append(queryString);
    
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    Util::executeGet(url,headers, response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::GetUserByEmailId(string emailId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(emailId, "EmailId");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	getMap["emailId"] = emailId;
	string signature = Util::signMap(secretKey, getMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("email/" + emailId);
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(url,headers, response, httpresponse_selector(App42UserResponse::onComplete));
}


void UserService::GetAllUsers(App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        e = NULL;
        return;
    }
    
    string resource = "user/";
    
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    Util::executeGet(url,headers, response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::GetAllUsers(int max, int offset, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        e = NULL;
        return;
    }
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["max"] = Util::ItoA(max);
    signMap["offset"] = Util::ItoA(offset);
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
    resource.append("paging/");
    resource.append(Util::ItoA(max)+"/");
    resource.append(Util::ItoA(offset));

	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(url,headers, response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::GetAllUsersCount(App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        e = NULL;
        return;
    }
    
    string resource = "user/";
    resource.append("count/all");
	string url = getBaseUrl(resource);
	string timestamp = Util::getTimeStamp();
    
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	string signature = Util::signMap(secretKey, getMap);
    url.append("?");
    
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    Util::executeGet(url,headers, response, httpresponse_selector(App42UserResponse::onComplete));
}


void UserService::LockUser(string username, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
   
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildCreateUserBody(username, "", "","");
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("lock");
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(url, headers, postBody.c_str(), response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::UnlockUser(string username, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildCreateUserBody(username, "", "","");
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("unlock");
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(url, headers, postBody.c_str(), response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::GetLockedUsers(App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        e = NULL;
        return;
    }
    
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	string signature = Util::signMap(secretKey, getMap);
    
    
    /**
     * Creating URL
     */
    string resource = "user/";
    resource.append("locked");
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(url,headers, response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::GetLockedUsers(int max, int offset, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        e = NULL;
        return;
    }
    
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["max"] = Util::ItoA(max);
    signMap["offset"] = Util::ItoA(offset);
	string signature = Util::signMap(secretKey, signMap);
    
    
    /**
     * Creating URL
     */
    string resource = "user/";
    resource.append("locked/");
    resource.append(Util::ItoA(max)+"/");
    resource.append(Util::ItoA(offset));
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(url,headers, response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::GetLockedUsersCount(App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        e = NULL;
        return;
    }
    
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	string signature = Util::signMap(secretKey, getMap);
    
    
    /**
     * Creating URL
     */
    string resource = "user/";
    resource.append("count/locked");
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(url,headers, response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::UpdateEmail(string username,string emailAddress, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfStringNullOrBlank(emailAddress, "Email Address");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildCreateUserBody(username, "", emailAddress,"");
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(url, headers, postBody.c_str(), response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::DeleteUser(string username, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "EmailId");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> getMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, getMap);
	getMap["userName"] = username;
	string signature = Util::signMap(secretKey, getMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append(username);
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeDelete(url,headers, response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::ChangeUserPassword(string username,string oldPassword,string newPassword, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfStringNullOrBlank(oldPassword, "Old Password");
        Util::throwExceptionIfStringNullOrBlank(newPassword, "New Password");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildChangePasswordBody(username, oldPassword, newPassword);
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("changeUserPassword");
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(url, headers, postBody.c_str(), response, httpresponse_selector(App42UserResponse::onComplete));
}


void UserService::ResetUserPassword(string username, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(username, "User Name");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildCreateUserBody(username, "", "", "");
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("resetAppUserPassword");
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(url, headers, postBody.c_str(), response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::createOrUpdateProfile(App42User user, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(user.userName, "User Name");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildCreateOrUpdateProfileBody(user);
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append("profile");
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(url, headers, postBody.c_str(), response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::GetUsersByProfileData(App42UserProfile profileData,App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        //Util::throwExceptionIfStringNullOrBlank(user.userName, "User Name");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
	string signature = Util::signMap(secretKey, signMap);
    /**
     * Creating URL
     */
    string parameters = buildProfileData(profileData);
    string resource = "user/";
	resource.append("profile/");
    resource.append(parameters);
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(url, headers,response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::Logout(string sessionId,App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(sessionId, "SessionId");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    string postBody = buildLogoutBody(sessionId);
    signMap["body"] = postBody;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "";
	resource.append("session");
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executePut(url, headers, postBody.c_str(), response, httpresponse_selector(App42UserResponse::onComplete));
}

void UserService::GetRolesByUser(string userName,App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UserResponse *response = new App42UserResponse::App42UserResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(userName, "User Name");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
    }
    catch (App42Exception *e)
    {
        std::string ex = e->what();
        response->httpErrorCode = e->getHttpErrorCode();
        response->appErrorCode  = e->getAppErrorCode();
        response->errorDetails  = ex;
        response->isSuccess = false;
        if (pTarget && pSelector)
        {
            (pTarget->*pSelector)((App42CallBack*)pTarget, response);
        }
        delete e;
        e = NULL;
        return;
    }
    
	string timestamp = Util::getTimeStamp();
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
    populateSignParams(signMap);
    signMap["userName"] = userName;
	string signature = Util::signMap(secretKey, signMap);
    /**
     * Creating URL
     */
    string resource = "user/";
	resource.append(userName);
    resource.append("/roles");
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating Headers
     */
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    
    /**
     * Initiating Http call
     */
    Util::executeGet(url, headers,response, httpresponse_selector(App42UserResponse::onComplete));
}

