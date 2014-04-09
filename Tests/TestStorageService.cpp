//
//  TestStorageService.cpp
//  App42Cocos2dXSDK_3.0Beta2_Sample
//
//  Created by Rajeev Ranjan on 31/03/14.
//
//

#include "TestStorageService.h"
#include "TestHome.h"


#define GO_HOME 1031

USING_NS_CC;

Scene* TestStorageService::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestStorageService::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool TestStorageService::init()
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
                                                CC_CALLBACK_1(TestStorageService::menuCloseCallback, this));
    
	backButtonItem->setPosition(Point(origin.x + visibleSize.width/2 ,
                                      origin.y + backButtonItem->getContentSize().height/2));
    backButtonItem->setTag(GO_HOME);

    /**
     * Insert Doc
     */
    auto insertDocLabel = LabelTTF::create("Insert Doc", "Marker Felt", 24);
    insertDocLabel->setColor(Color3B::WHITE);
    auto insertDocItem  = MenuItemLabel::create(insertDocLabel, CC_CALLBACK_1(TestStorageService::insertJsonDocument, this));
    insertDocItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindAllDocuments
     */
    auto findAllDocumentLabel = LabelTTF::create("FindAllDocuments", "Marker Felt", 24);
    findAllDocumentLabel->setColor(Color3B::WHITE);
    auto findAllDocumentItem  = MenuItemLabel::create(findAllDocumentLabel, CC_CALLBACK_1(TestStorageService::findAllDocuments, this));
    y_pos -= button_y_Offset;
    findAllDocumentItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindAllDocumentsByPaging
     */
    auto findAllDocumentByPagingLabel = LabelTTF::create("FindAllDocumentsByPaging", "Marker Felt", 24);
    findAllDocumentByPagingLabel->setColor(Color3B::WHITE);
    auto findAllDocumentByPagingItem  = MenuItemLabel::create(findAllDocumentByPagingLabel, CC_CALLBACK_1(TestStorageService::findAllDocumentsByPaging, this));
    y_pos -= button_y_Offset;
    findAllDocumentByPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindAllDocumentCount
     */
    auto findAllDocumentCountLabel = LabelTTF::create("FindAllDocumentsCount", "Marker Felt", 24);
    findAllDocumentCountLabel->setColor(Color3B::WHITE);
    auto findAllDocumentCountItem  = MenuItemLabel::create(findAllDocumentCountLabel, CC_CALLBACK_1(TestStorageService::findAllDocumentsCount, this));
    y_pos -= button_y_Offset;
    findAllDocumentCountItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindDocumentsByQuery
     */
    auto findDocumentsByQueryLabel = LabelTTF::create("FindDocumentsByQuery", "Marker Felt", 24);
    findDocumentsByQueryLabel->setColor(Color3B::WHITE);
    auto findDocumentsByQueryItem  = MenuItemLabel::create(findDocumentsByQueryLabel, CC_CALLBACK_1(TestStorageService::findDocumentByQuery, this));
    y_pos -= button_y_Offset;
    findDocumentsByQueryItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindDocumentsByKeyValue
     */
    auto findDocumentsByKeyValueLabel = LabelTTF::create("FindDocumentsByKeyValue", "Marker Felt", 24);
    findDocumentsByKeyValueLabel->setColor(Color3B::WHITE);
    auto findDocumentsByKeyValueItem  = MenuItemLabel::create(findDocumentsByKeyValueLabel, CC_CALLBACK_1(TestStorageService::findDocumentsByKeyValue, this));
    y_pos -= button_y_Offset;
    findDocumentsByKeyValueItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindDocumentsByQueryWithPaging
     */
    auto findDocumentsByQueryPagingLabel = LabelTTF::create("FindDocumentsByQueryWithPaging", "Marker Felt", 24);
    findDocumentsByQueryPagingLabel->setColor(Color3B::WHITE);
    auto findDocumentsByQueryPagingItem  = MenuItemLabel::create(findDocumentsByQueryPagingLabel, CC_CALLBACK_1(TestStorageService::findDocumentByQueryWithPaging, this));
    y_pos -= button_y_Offset;
    findDocumentsByQueryPagingItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * FindDocsByQueryWithPagingOrderBy
     */
    auto findDocsByQueryWithPagingOrderByLabel = LabelTTF::create("FindDocsByQueryWithPagingOrderBy", "Marker Felt", 24);
    findDocsByQueryWithPagingOrderByLabel->setColor(Color3B::WHITE);
    auto findDocsByQueryWithPagingOrderByItem  = MenuItemLabel::create(findDocsByQueryWithPagingOrderByLabel, CC_CALLBACK_1(TestStorageService::findDocumentByQueryWithPagingOrderBy, this));
    y_pos -= button_y_Offset;
    findDocsByQueryWithPagingOrderByItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * DeleteDocumentsById
     */
    auto deleteDocumentsByIdLabel = LabelTTF::create("DeleteDocumentsById", "Marker Felt", 24);
    deleteDocumentsByIdLabel->setColor(Color3B::WHITE);
    auto deleteDocumentsByIdItem  = MenuItemLabel::create(deleteDocumentsByIdLabel, CC_CALLBACK_1(TestStorageService::deleteDocumentByKeyValue, this));
    y_pos -= button_y_Offset;
    deleteDocumentsByIdItem->setPosition(Point(x_pos,y_pos));
    /**
     * DeleteDocumentsByKeyValue
     */
    auto deleteDocumentsByKeyValueLabel = LabelTTF::create("DeleteDocumentsByKeyValue", "Marker Felt", 24);
    deleteDocumentsByKeyValueLabel->setColor(Color3B::WHITE);
    auto deleteDocumentsByKeyValueItem  = MenuItemLabel::create(deleteDocumentsByKeyValueLabel, CC_CALLBACK_1(TestStorageService::deleteDocumentByKeyValue, this));
    y_pos -= button_y_Offset;
    deleteDocumentsByKeyValueItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * DeleteAllDocuments
     */
    auto deleteAllDocumentsLabel = LabelTTF::create("DeleteAllDocuments", "Marker Felt", 24);
    deleteAllDocumentsLabel->setColor(Color3B::WHITE);
    auto deleteAllDocumentsItem  = MenuItemLabel::create(deleteAllDocumentsLabel, CC_CALLBACK_1(TestStorageService::deleteAllDocuments, this));
    y_pos -= button_y_Offset;
    deleteAllDocumentsItem->setPosition(Point(x_pos,y_pos));
    
    /**
     * AddOrUpdateKeys
     */
    auto addOrUpdateKeysLabel = LabelTTF::create("AddOrUpdateKeys", "Marker Felt", 24);
    addOrUpdateKeysLabel->setColor(Color3B::WHITE);
    auto addOrUpdateKeysItem  = MenuItemLabel::create(addOrUpdateKeysLabel, CC_CALLBACK_1(TestStorageService::addOrUpdateKeys, this));
    y_pos -= button_y_Offset;
    addOrUpdateKeysItem->setPosition(Point(x_pos,y_pos));

    
    /**
     * Create menu, it's an autorelease object
     */
    auto menu = Menu::create(backButtonItem,insertDocItem,
                             findAllDocumentItem,
                             findAllDocumentByPagingItem,
                             findAllDocumentCountItem,
                             findDocumentsByQueryItem,
                             findDocumentsByKeyValueItem,
                             findDocumentsByQueryPagingItem,
                             findDocsByQueryWithPagingOrderByItem,
                             deleteDocumentsByIdItem,
                             deleteDocumentsByKeyValueItem,
                             deleteAllDocumentsItem,
                             addOrUpdateKeysItem, NULL);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    
    dbName = "jsonDocument2";
    collectionName = "TestingScore";
    docId = "";
    return true;
}

string getJsonString(string key1, string value1,string key2,string value2)
{
    cJSON *bodyJSON = cJSON_CreateObject();
    cJSON_AddStringToObject(bodyJSON, key1.c_str(), value1.c_str());
    cJSON_AddStringToObject(bodyJSON, key2.c_str(), value2.c_str());
    char *cptrFormatted = cJSON_PrintUnformatted(bodyJSON);
	string bodyString = cptrFormatted;
    cJSON_Delete(bodyJSON);
	free(cptrFormatted);
    
	return bodyString;
}

void TestStorageService::insertJsonDocument(Ref *sender)
{
    Util::setTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    
    string jsonDoc = getJsonString("name", "Rajeev", "role", "Developer");
    storageService->InsertJsonDocument(dbName, collectionName, jsonDoc, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::findAllDocuments(Ref *sender)
{
    Util::setTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    
    storageService->FindAllDocuments(dbName, collectionName,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::findAllDocumentsByPaging(Ref *sender)
{
    Util::setTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    
    storageService->FindAllDocuments(dbName, collectionName,2,1,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::findAllDocumentsCount(Ref *sender)
{
    Util::setTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    storageService->FindAllDocumentsCount(dbName, collectionName,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::findDocumentByQuery(Ref *sender)
{
    Util::setTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    
    Query *query = QueryBuilder::BuildQuery("role", "Developer", APP42_OP_EQUALS);
    storageService->FindDocumentByQuery(dbName, collectionName,query,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}
void TestStorageService::findDocumentByQueryWithPaging(Ref *sender)
{
    Util::setTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    
    Query *query = QueryBuilder::BuildQuery("role", "Developer", APP42_OP_EQUALS);
    storageService->FindDocumentsByQueryWithPaging(dbName, collectionName,query,2,0,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}
void TestStorageService::findDocumentByQueryWithPagingOrderBy(Ref *sender)
{
    Util::setTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    Query *query = QueryBuilder::BuildQuery("role", "Developer", APP42_OP_EQUALS);
    storageService->FindDocsWithQueryPagingOrderBy(dbName, collectionName,query,4,0,"name",APP42_ORDER_ASCENDING,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::findDocumentsByKeyValue(Ref *sender)
{
    Util::setTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    string key="role";
    string value = "Developer";
    storageService->FindDocumentByKeyValue(dbName, collectionName,key,value,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}


void TestStorageService::deleteDocumentById(Ref *sender)
{
    Util::setTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    string docId = "";
    storageService->DeleteDocumentsById(dbName, collectionName,docId,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::deleteDocumentByKeyValue(Ref *sender)
{
    Util::setTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    string key = "role";
    string value = "Developer";
    storageService->DeleteDocumentsByKeyValue(dbName, collectionName,key,value,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::deleteAllDocuments(Ref *sender)
{
    Util::setTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    storageService->DeleteAllDocuments(dbName, collectionName,this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

void TestStorageService::addOrUpdateKeys(Ref *sender)
{
    Util::setTraceEnabled(true);
    StorageService *storageService = App42API::BuildStorageService();
    string jsonDoc = getJsonString("name", "Rajeev Ranjan", "age", "31");
    docId = "533e5c89e4b0ae7acf86b1f0";
    storageService->AddOrUpdateKeys(dbName, collectionName, docId, jsonDoc, this, app42callfuncND_selector(TestStorageService::onStorageRequestCompleted));
}

/***
 * Callbacks
 */

void TestStorageService::onStorageRequestCompleted(App42CallBack *sender, void *response)
{
    App42StorageResponse *storageResponse = (App42StorageResponse*)response;
    printf("\ncode=%d",storageResponse->getCode());
    printf("\nResponse Body=%s",storageResponse->getBody().c_str());
    printf("\nTotalRecords=%d",storageResponse->getTotalRecords());
    if (!storageResponse->isSuccess)
    {
        printf("\nerrordetails:%s",storageResponse->errorDetails.c_str());
        printf("\nerrorMessage:%s",storageResponse->errorMessage.c_str());
        printf("\nappErrorCode:%d",storageResponse->appErrorCode);
        printf("\nhttpErrorCode:%d",storageResponse->httpErrorCode);
    }
    else
    {
        for(std::vector<App42Storage>::iterator it = storageResponse->storages.begin(); it != storageResponse->storages.end(); ++it)
        {
            printf("\n DbName=%s",it->dbName.c_str());
            printf("\n CollectionName=%s",it->collectionName.c_str());
            printf("\n RecordCount=%lf\n",it->recordCount);
            
            for(std::vector<JSONDocument>::iterator iit = it->jsonDocArray.begin(); iit != it->jsonDocArray.end(); ++iit)
            {
                printf("\n CreatedAt=%s",iit->getCreatedAt().c_str());
                docId = iit->getDocId();
                printf("\n DocId=%s",docId.c_str());
                printf("\n Event=%s",iit->getEvent().c_str());
                printf("\n Owner=%s",iit->getOwner().c_str());
                printf("\n UpdatedAt=%s",iit->getUpdatedAt().c_str());
                printf("\n JsonDoc=%s\n",iit->getJsonDoc().c_str());
            }
        }
    }
}


void TestStorageService::menuCloseCallback(Ref* pSender)
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