//
//  TestStorageService.h
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#ifndef __App42Cocos2dXSDK_3_0Beta2_Sample__TestStorageService__
#define __App42Cocos2dXSDK_3_0Beta2_Sample__TestStorageService__

#include <iostream>
#include "cocos2d.h"
#include "App42API.h"

class TestStorageService : public cocos2d::Layer, public App42CallBack
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestStorageService);
    
    void setAPIKey(std::string _apiKey);
    void setSecretKey(std::string _apiKey);
    
    
    /**
     * API Test methods
     */
    void insertJsonDocument(Ref *sender);
    void findAllDocuments(Ref *sender);
    void findAllDocumentsByPaging(Ref *sender);
    void findAllDocumentsCount(Ref *sender);
    void findDocumentByQuery(Ref *sender);
    void findDocumentByQueryWithPaging(Ref *sender);
    void findDocumentByQueryWithPagingOrderBy(Ref *sender);
    void findDocumentsByKeyValue(Ref *sender);
    void deleteDocumentById(Ref *sender);
    void deleteDocumentByKeyValue(Ref *sender);
    void deleteAllDocuments(Ref *sender);
    void addOrUpdateKeys(Ref *sender);
    /**
     * A selector callback
     */
    void onStorageRequestCompleted(App42CallBack *sender, void *response);
    void menuCloseCallback(Ref* pSender);
    
private:
    std::string apiKey;
    std::string secretKey;
    string dbName;
    string collectionName;
    string docId;
    
};

#endif /* defined(__App42Cocos2dXSDK_3_0Beta2_Sample__TestStorageService__) */
