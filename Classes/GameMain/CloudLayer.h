//
//  CloudLayer.h
//  CrazyBox
//
//  Created by jintao on 14-6-4.
//
//

#ifndef __CrazyBox__CloudLayer__
#define __CrazyBox__CloudLayer__

#include <iostream>
#include "cocos2d.h"

typedef enum
{
	kCloudBack,
	kCloudFront,
}CloudDepth;

class CloudLayer:public cocos2d::Layer
{
public:
    CloudLayer(float width,CloudDepth depth);
    ~CloudLayer();
    static CloudLayer* create(float width,CloudDepth depth);
    virtual bool init(float width);
    virtual void onEnter();
    virtual void onExit();
    CC_SYNTHESIZE(float, _cloudLayerWidth, cloudLayerWidth );
    
private:
    CloudDepth _cloudDepth;
    float      _curwidth;
    //float      _cloudLayerWidth;
    
};

#endif /* defined(__CrazyBox__CloudLayer__) */
