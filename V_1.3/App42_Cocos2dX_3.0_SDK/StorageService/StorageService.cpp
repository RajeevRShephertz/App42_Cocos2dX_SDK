//
//  StorageService.cpp
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 21/10/13.
//
//

#include "StorageService.h"
#include "App42Constants.h"
#include "cJSON.h"
#include <map>
#include "Signing.h"
#include "BodyBuilder.h"
#include "cocos-ext.h"
#include "App42StorageResponse.h"
#include "Connector.h"


// define the static..
StorageService* StorageService::_instance = NULL;

StorageService* StorageService::Initialize(string apikey, string secretkey)
{
	if(_instance == NULL)
    {
		_instance = new StorageService();
	}
    _instance->Init(apikey, secretkey);
    return _instance;
}

StorageService* StorageService::getInstance()
{
	return _instance;
}

void StorageService::Terminate()
{
	if(_instance != NULL)
    {
		delete _instance;
		_instance = NULL;
	}
}

StorageService::StorageService()
{
    
}

string BuildStorageBody(string json)
{
	cJSON *bodyJSON = cJSON_CreateObject();
	cJSON *app42JSON = cJSON_CreateObject();
	cJSON *storageJSON = cJSON_CreateObject();
    
	cJSON_AddStringToObject(storageJSON, "jsonDoc", json.c_str());
	cJSON_AddItemReferenceToObject(app42JSON, "storage", storageJSON);
    
	cJSON_AddItemReferenceToObject(bodyJSON, "app42", app42JSON);
	char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
	string bodyString = cptrFormatted;
    
	cJSON_Delete(storageJSON);
	cJSON_Delete(app42JSON);
	cJSON_Delete(bodyJSON);
	free(cptrFormatted);
	return bodyString;
}


void StorageService::InsertJsonDocument(string dbName, string collectionName, string json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
        Util::throwExceptionIfStringNullOrBlank(json, "Json String");
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
        
        string storageBody = BuildStorageBody(json);
        signParams["body"] = storageBody;
        
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
        Util::executePost(baseUrl, headers, storageBody.c_str(), response, httpresponse_selector(App42StorageResponse::onComplete));

    }
    catch (exception *e)
    {
        throw e;
    }
}


void StorageService::FindAllCollections(string dbName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
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
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["dbName"] = dbName;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/findCollections/dbName/";
    resource.append(dbName);
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
    Util::executeGet(url,headers, response, httpresponse_selector(App42StorageResponse::onComplete));
}

void StorageService::FindAllDocuments(string dbName, string collectionName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
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
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["dbName"] = dbName;
    signMap["collectionName"] = collectionName;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/findAll/dbName/";
	resource.append(dbName+ "/collectionName/");
	resource.append(collectionName);
	string url = getBaseUrl(resource);
    url.append("?");
    /**
     * Creating Headers
     */
    //Util::app42Trace("\n baseUrl = %s",url.c_str());
    std::vector<std::string> headers;
    map<string, string> metaHeaders;
    populateMetaHeaderParams(metaHeaders);
    Util::BuildHeaders(metaHeaders, headers);
    
    Util::BuildHeaders(apiKey, timestamp, VERSION, signature, headers);
    /**
     * Initiating Http call
     */
    Util::executeGet(url,headers, response, httpresponse_selector(App42StorageResponse::onComplete));

}

void StorageService::FindAllDocuments(string dbName, string collectionName,int max, int offset, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
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
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["dbName"] = dbName;
    signMap["collectionName"] = collectionName;
    signMap["max"] = Util::ItoA(max);
    signMap["offset"] = Util::ItoA(offset);
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/findAll/dbName/";
	resource.append(dbName+ "/collectionName/");
	resource.append(collectionName);
    resource.append("/"+Util::ItoA(max));
    resource.append("/"+Util::ItoA(offset));
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
    Util::executeGet(url,headers, response, httpresponse_selector(App42StorageResponse::onComplete));
    
}


void StorageService::FindAllDocumentsCount(string dbName, string collectionName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
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
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["dbName"] = dbName;
    signMap["collectionName"] = collectionName;
	string signature = Util::signMap(secretKey, signMap);
    /**
     * Creating URL
     */
    string resource = "storage/findAll/count/dbName/";
	resource.append(dbName+ "/collectionName/");
	resource.append(collectionName);
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
    Util::executeGet(url,headers, response, httpresponse_selector(App42StorageResponse::onComplete));
    
}

void StorageService::FindDocumentById(string dbName, string collectionName, string docId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
        Util::throwExceptionIfStringNullOrBlank(docId, "Doc ID");
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
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["dbName"] = dbName;
    signMap["collectionName"] = collectionName;
    signMap["docId"] = docId;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/findDocById/dbName/";
	resource.append(dbName + "/collectionName/");
	resource.append(collectionName + "/docId/");
	resource.append(docId);
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
    Util::executeGet(url,headers, response, httpresponse_selector(App42StorageResponse::onComplete));

}

void StorageService::FindDocumentByQuery(string dbName, string collectionName, Query *query, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    FindDocumentsByQuery(dbName, collectionName, query, pTarget, pSelector);
}

void StorageService::FindDocumentsByQuery(string dbName, string collectionName, Query *query, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
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
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["dbName"] = dbName;
    signMap["collectionName"] = collectionName;
    signMap["jsonQuery"] = query->getString();
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/findDocsByQuery/dbName/";
	resource.append(dbName + "/collectionName/");
	resource.append(collectionName);
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating QueryParams
     */
    map<string, string> queryParamsMap;
    queryParamsMap["jsonQuery"]=query->getString();
    string queryString = buildQueryString(queryParamsMap);
    url.append(queryString);
    
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
    Util::executeGet(url.c_str(),headers, response, httpresponse_selector(App42StorageResponse::onComplete));
    
}

void StorageService::FindDocumentsByQueryWithPaging(string dbName, string collectionName, Query *query, int max, int offset, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
        Util::throwExceptionIfTargetIsNull(pTarget, "Callback's Target");
        Util::throwExceptionIfCallBackIsNull(pSelector, "Callback");
        Util::throwExceptionIfMaxIsNotValid(max, "Max");
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
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["dbName"] = dbName;
    signMap["collectionName"] = collectionName;
    signMap["jsonQuery"] = query->getString();
    signMap["max"] = Util::ItoA(max);
    signMap["offset"] = Util::ItoA(offset);
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/findDocsByQuery/dbName/";
	resource.append(dbName + "/collectionName/");
	resource.append(collectionName);
    resource.append("/"+Util::ItoA(max));
    resource.append("/"+Util::ItoA(offset));
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating QueryParams
     */
    map<string, string> queryParamsMap;
    queryParamsMap["jsonQuery"]=query->getString();
    string queryString = buildQueryString(queryParamsMap);
    url.append(queryString);
    
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
    Util::executeGet(url.c_str(),headers, response, httpresponse_selector(App42StorageResponse::onComplete));
    
}


void StorageService::FindDocsWithQueryPagingOrderBy(string dbName, string collectionName, Query *query, int max, int offset,string orderByKey,string orderByType, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
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
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["dbName"] = dbName;
    signMap["collectionName"] = collectionName;
    signMap["jsonQuery"] = query->getString();
    signMap["max"] = Util::ItoA(max);
    signMap["offset"] = Util::ItoA(offset);
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/findDocsByQuery/dbName/";
	resource.append(dbName + "/collectionName/");
	resource.append(collectionName);
    resource.append("/"+Util::ItoA(max));
    resource.append("/"+Util::ItoA(offset));
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating QueryParams
     */
    map<string, string> queryParamsMap;
    if (orderByKey.c_str()!= NULL)
    {
        queryParamsMap["orderByKey"]=orderByKey;
    }
    if (orderByType.c_str()!= NULL)
    {
        queryParamsMap["orderByType"]=orderByType;
    }
    queryParamsMap["jsonQuery"]=query->getString();
    string queryString = buildQueryString(queryParamsMap);
    url.append(queryString);
    
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
    Util::executeGet(url.c_str(),headers, response, httpresponse_selector(App42StorageResponse::onComplete));
    
}

void StorageService::FindDocumentByKeyValue(string dbName, string collectionName, string key,string value, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
        Util::throwExceptionIfStringNullOrBlank(key, "Key");
        Util::throwExceptionIfStringNullOrBlank(value, "Value");
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
    
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["dbName"] = dbName;
    signMap["collectionName"] = collectionName;
    signMap["key"] = key;
	signMap["value"] = value;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/findDocByKV/dbName/";
	resource.append(dbName+ "/collectionName/");
	resource.append(collectionName+ "/");
	resource.append(key+ "/");
	resource.append(value+ "/");
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
    Util::executeGet(url,headers, response, httpresponse_selector(App42StorageResponse::onComplete));

}

void StorageService::UpdateDocumentByDocId(string dbName, string collectionName, string docId,string json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
        Util::throwExceptionIfStringNullOrBlank(docId, "Doc ID");
        Util::throwExceptionIfStringNullOrBlank(json, "Json String");
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
    /**
     * Creating SignParams and signature
     */
    map<string, string> postMap;
    string timestamp = Util::getTimeStamp();
    populateSignParams(postMap);
    postMap["dbName"] = dbName;
	postMap["collectionName"] = collectionName;
    postMap["docId"] = docId;
    string storageBody = BuildStorageBody(json);
    postMap["body"] = storageBody;
    
    string signature = Util::signMap(secretKey, postMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/updateByDocId/dbName/";
    resource.append(dbName + "/collectionName/");
	resource.append(collectionName+"/docId/");
    resource.append(docId);
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
    Util::executePut(baseUrl, headers, storageBody.c_str(), response, httpresponse_selector(App42StorageResponse::onComplete));
}

void StorageService::UpdateDocumentByKeyValue(string dbName, string collectionName, string key,string value,string json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
        Util::throwExceptionIfStringNullOrBlank(key, "Key");
        Util::throwExceptionIfStringNullOrBlank(value, "Value");
        Util::throwExceptionIfStringNullOrBlank(json, "Json String");
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
    /**
     * Creating SignParams and signature
     */
    map<string, string> postMap;
    string timestamp = Util::getTimeStamp();
    populateSignParams(postMap);
    postMap["dbName"] = dbName;
	postMap["collectionName"] = collectionName;
    postMap["key"] = key;
    postMap["value"] = value;
    string storageBody = BuildStorageBody(json);
    postMap["body"] = storageBody;
    
    string signature = Util::signMap(secretKey, postMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/update/dbName/";
    resource.append(dbName + "/collectionName/");
	resource.append(collectionName+"/");
    resource.append(key+"/");
    resource.append(value);
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
    Util::executePut(baseUrl, headers, storageBody.c_str(), response, httpresponse_selector(App42StorageResponse::onComplete));
}

void StorageService::SaveOrUpdateDocumentByKeyValue(string dbName, string collectionName, string key,string value,string json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
        Util::throwExceptionIfStringNullOrBlank(key, "Key");
        Util::throwExceptionIfStringNullOrBlank(value, "Value");
        Util::throwExceptionIfStringNullOrBlank(json, "Json String");
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
    /**
     * Creating SignParams and signature
     */
    map<string, string> postMap;
    string timestamp = Util::getTimeStamp();
    populateSignParams(postMap);
    postMap["dbName"] = dbName;
	postMap["collectionName"] = collectionName;
    postMap["key"] = key;
    postMap["value"] = value;
    string storageBody = BuildStorageBody(json);
    postMap["body"] = storageBody;
    string signature = Util::signMap(secretKey, postMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/saveorupdate/dbName/";
    resource.append(dbName + "/collectionName/");
	resource.append(collectionName+"/");
    resource.append(key+"/");
    resource.append(value);
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
    Util::executePut(baseUrl, headers, storageBody.c_str(), response, httpresponse_selector(App42StorageResponse::onComplete));
}

void StorageService::DeleteDocumentsById(string dbName, string collectionName, string docId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
        Util::throwExceptionIfStringNullOrBlank(docId, "Doc ID");
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
   
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["dbName"] = dbName;
    signMap["collectionName"] = collectionName;
    signMap["docId"] = docId;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/deleteDocById/dbName/";
	resource.append(dbName+ "/collectionName/");
	resource.append(collectionName+ "/docId/");
	resource.append(docId);
    
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
    Util::executeDelete(url,headers, response, httpresponse_selector(App42StorageResponse::onComplete));
    
}

void StorageService::DeleteDocumentsByKeyValue(string dbName, string collectionName, string key, string value, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
        Util::throwExceptionIfStringNullOrBlank(key, "Key");
        Util::throwExceptionIfStringNullOrBlank(value, "Value");
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
    
	string timestamp = Util::getTimeStamp();
    map<string, string> queryParamsMap;
    
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "key", value.c_str());
    char *cptrFormatted = cJSON_PrintUnformatted(json);
	string bodyString = cptrFormatted;
    free(cptrFormatted);
    cJSON_Delete(json);
    signMap["value"] = bodyString;
    queryParamsMap["value"] = bodyString;
    
    signMap["dbName"] = dbName;
    signMap["collectionName"] = collectionName;
    signMap["key"] = key;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/deletebykey/dbName/";
	resource.append(dbName+ "/collectionName/");
	resource.append(collectionName+ "/");
	resource.append(key);
	string url = getBaseUrl(resource);
    url.append("?");
    
    /**
     * Creating QueryParams
     */
    string queryString = buildQueryString(queryParamsMap);
    url.append(queryString);
    
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
    Util::executeDelete(url,headers, response, httpresponse_selector(App42StorageResponse::onComplete));
    
}

void StorageService::DeleteAllDocuments(string dbName, string collectionName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
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
    
	string timestamp = Util::getTimeStamp();
    /**
     * Creating SignParams and signature
     */
    map<string, string> signMap;
	Util::BuildGetSigningMap(apiKey, timestamp, VERSION, signMap);
    signMap["dbName"] = dbName;
    signMap["collectionName"] = collectionName;
	string signature = Util::signMap(secretKey, signMap);
    
    /**
     * Creating URL
     */
    string resource = "storage/deleteAll/dbName/";
	resource.append(dbName+ "/collectionName/");
	resource.append(collectionName);
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
    Util::executeDelete(url,headers, response, httpresponse_selector(App42StorageResponse::onComplete));
    
}

void StorageService::AddOrUpdateKeys(string dbName, string collectionName, string docId,string json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector)
{
    App42StorageResponse *response = new App42StorageResponse::App42StorageResponse(pTarget,pSelector);
    
    try
    {
        Util::throwExceptionIfStringNullOrBlank(dbName, "Database Name");
        Util::throwExceptionIfStringNullOrBlank(collectionName, "Collection Name");
        Util::throwExceptionIfStringNullOrBlank(json, "Json String");
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
        signParams["docId"] = docId;
        string storageBody = BuildStorageBody(json);
        signParams["body"] = storageBody;
        
        string signature = Util::signMap(secretKey, signParams);
        
        /**
         * Creating URL
         */
        string resource = "storage/updateKeysByDocId/dbName/";
        resource.append(dbName + "/collectionName/");
        resource.append(collectionName + "/docId/");
        resource.append(docId);
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
        Util::executePut(baseUrl, headers, storageBody.c_str(), response, httpresponse_selector(App42StorageResponse::onComplete));
        
    }
    catch (exception *e)
    {
        throw e;
    }
}
