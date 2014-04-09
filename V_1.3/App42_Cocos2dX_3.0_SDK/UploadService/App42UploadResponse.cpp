//
//  App42UploadResponse.cpp
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 04/04/14.
//
//

#include "App42UploadResponse.h"
#include "Common.h"


App42UploadResponse::App42UploadResponse(App42CallBack *pTarget, SEL_App42CallFuncND pSelector)
:App42Response(pTarget,pSelector)
{
    
}

App42UploadResponse::~App42UploadResponse()
{
    
}

void App42UploadResponse::onComplete(cocos2d::Node *sender, void *data)
{
    App42Response::onComplete(sender, data);
    init();
    
    if (_app42Target && _app42Selector)
    {
        (_app42Target->*_app42Selector)((App42CallBack *)_app42Target, this);
    }
}

void App42UploadResponse::init()
{
    if(_result != 200)
    {
        Util::app42Trace("App42StorageResult failed result is %d", _result);
        buildErrorMessage();
        return;
    }
    
    // parse the body
    cJSON *ptrBody = cJSON_Parse(_body.c_str());
    cJSON* ptrApp42 = Util::getJSONChild("app42", ptrBody);
    cJSON* ptrResponse = Util::getJSONChild("response", ptrApp42);
    cJSON* ptrUpload = Util::getJSONChild("upload", ptrResponse);
    if (ptrUpload)
    {
        cJSON* ptrFiles = Util::getJSONChild("files", ptrResponse);
        if (ptrFiles)
        {
            cJSON* ptrFile = Util::getJSONChild("file", ptrResponse);
            if (ptrFile)
            {
                
                cJSON* child = ptrFile;
                if(child->type == cJSON_Array)
                {
                    child = child->child;
                }
                while(child != NULL && child->type == cJSON_Object)
                {
//                    App42Upload app42Upload;
//                    cJSON *nameJson = Util::getJSONChild("name", child);
//                    if (nameJson!=NULL)
//                    {
//                        
//                        //file->setn(Util::getJSONString("$oid", docIdJson));
//                        cJSON_DeleteItemFromObject(child, "name");
//                    }
//                    char *doc = cJSON_PrintUnformatted(json);
//                    jsonDocumnet->setJsonDoc(doc);
//                    free(doc);
//                    
//                    uploadArray.push_back(file);
                    child = child->next;
                }
            }
        }
    }
}