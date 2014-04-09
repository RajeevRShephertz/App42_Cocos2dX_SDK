//
//  UploadService.h
//  App42Cocos2dX3.0Sample
//
//  Created by Rajeev Ranjan on 04/04/14.
//
//

#ifndef __App42Cocos2dX3_0Sample__UploadService__
#define __App42Cocos2dX3_0Sample__UploadService__

#include <iostream>
#include "App42Service.h"

using namespace std;

class UploadService : public App42Service
{
    
private:
    UploadService();
	static UploadService* _instance;
public:
    
	/**
     * This is a constructor that takes
     *
     * @param apiKey
     * @param secretKey
     * @param server
     *
     */
	
    static UploadService* Initialize(string apikey, string secretkey);
    
	static void Terminate();
    
	/**
     * Builds the instance of UserService.
     *
     * @return UserService - UserService Object
     */
	static UploadService* getInstance();
    
    void UploadFile(string name, string filePath,string fileType, string description,App42CallBack* pTarget, SEL_App42CallFuncND pSelector);
};

#endif /* defined(__App42Cocos2dX3_0Sample__UploadService__) */
