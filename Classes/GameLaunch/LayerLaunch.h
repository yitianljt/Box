//
//  LayerLaunch.h
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#ifndef __ShareTest__LayerLaunch__
#define __ShareTest__LayerLaunch__

#include <iostream>
#include "cocos2d.h"
#include "Common.h"



class LayerLaunch:public cocos2d::Layer
{
public:
    LayerLaunch();
    ~LayerLaunch();
    COM_CREATE_FUNC(LayerLaunch);
    
    
    virtual void onEnter();
    virtual void onExit();
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, bool transformUpdated) override;
    void callbackStart(cocos2d::Ref* obj);
   // void touchCallBack(cocos2d::CCObject *pRef,cocos2d::ui::TouchEventType type);

    
};

#endif /* defined(__ShareTest__LayerLaunch__) */
