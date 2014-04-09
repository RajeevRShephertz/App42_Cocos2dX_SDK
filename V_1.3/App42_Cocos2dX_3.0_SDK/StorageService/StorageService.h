//
//  StorageService.h
//  App42CPPSDK
//
//  Created by Rajeev Ranjan on 21/10/13.
//
//

#ifndef __App42CPPSDK__StorageService__
#define __App42CPPSDK__StorageService__

#include <iostream>
#include "App42Service.h"

using namespace std;

class StorageService : public App42Service
{
    
private:
    StorageService();
	static StorageService* _instance;
public:
    
	/**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
	
    static StorageService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of UserService.
     *
     * @return UserService - UserService Object
     */
	static StorageService* getInstance();
    
    void InsertJsonDocument(string dbName, string collectionName, string json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
	void FindAllCollections(string dbName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
	void FindAllDocuments(string dbName, string collectionName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void FindAllDocuments(string dbName, string collectionName,int max, int offset, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void FindAllDocumentsCount(string dbName, string collectionName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
	void FindDocumentById(string dbName, string collectionName, string docId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    //Deprecated---Use "FindDocumentsByQuery"
    void FindDocumentByQuery(string dbName, string collectionName, Query *query, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void FindDocumentsByQuery(string dbName, string collectionName, Query *query, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void FindDocumentsByQueryWithPaging(string dbName, string collectionName, Query *query, int max, int offset, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void FindDocsWithQueryPagingOrderBy(string dbName, string collectionName, Query *query, int max, int offset,string orderByKey,string orderByType, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
	void FindDocumentByKeyValue(string dbName, string collectionName, string key,string value, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void UpdateDocumentByDocId(string dbName, string collectionName, string docId,string newJsonDoc, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void UpdateDocumentByKeyValue(string dbName, string collectionName, string key,string value,string json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void SaveOrUpdateDocumentByKeyValue(string dbName, string collectionName, string key,string value,string json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    void DeleteDocumentsById(string dbName, string collectionName, string docId, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void DeleteDocumentsByKeyValue(string dbName, string collectionName, string key, string value, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);

    void DeleteAllDocuments(string dbName, string collectionName, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
    
    void AddOrUpdateKeys(string dbName, string collectionName, string docId,string json, App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
};

#endif /* defined(__App42CPPSDK__StorageService__) */
