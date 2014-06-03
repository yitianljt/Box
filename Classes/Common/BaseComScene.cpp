//
//  BaseCommon.cpp
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#include "BaseComScene.h"

USING_NS_CC;
bool BaseComScene::init()
{
    
    if (CCScene::init()) {
        return true;
    }
    return false;
}


BaseComScene::~BaseComScene()
{
    for (std::string value : notificationValues) {
        CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, value.c_str());
    }
}


