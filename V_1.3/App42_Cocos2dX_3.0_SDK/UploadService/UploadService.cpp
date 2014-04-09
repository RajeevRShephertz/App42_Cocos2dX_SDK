//
//  UploadService.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 04/04/14.
//
//

#include "UploadService.h"
#include "App42Constants.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "cocos-ext.h"
#include "App42UploadResponse.h"
#include "Connector.h"

// define the static..
UploadService* UploadService::_instance = NULL;

UploadService* UploadService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new UploadService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

UploadService* UploadService::getInstance()
{
	return _instance;
}

void UploadService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}

UploadService::UploadService()
{
    
}

void UploadService::UploadFile(string fileName, string filePath,string fileType, string description,App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42UploadResponse *response = new App42UploadResponse::App42UploadResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(fileName, "File Name");
        Util::throwExceptionIfStringNullOrBlank(filePath, "File Path");
        Util::throwExceptionIfStringNullOrBlank(fileType, "File Type");
        Util::throwExceptionIfStringNullOrBlank(description, "Description");
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
    
    try {
        /**
         * Creating SignParams and signature
         */
        map<string, string> signParams;
        string timestamp = Util::getTimeStamp();
        populateSignParams(signParams);
        signParams["dbName"] = dbName;
        signParams["collectionName"] = collectionName;
        
        
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "storage/insert/dbName/";
        resource.append(dbName + "/collectionName/");
        resource.append(collectionName);
        string baseUrl = getBaseUrl(resource);
        
        baseUrl.append("?");
        
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
        //Util::executePost(baseUrl, headers, storageBody.c_str(), response, httpresponse_selector(App42StorageResponse::onComplete));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}
