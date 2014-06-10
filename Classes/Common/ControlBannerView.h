//
//  ControlBannerView.h
//  CrazyBox
//
//  Created by jintao on 14-6-9.
//
//

#ifndef __CrazyBox__ControlBannerView__
#define __CrazyBox__ControlBannerView__

#include <iostream>
#include "cocos2d.h"


#define SINGLETON_IMPL(className)\
className* className::_shared = NULL;\


#define SINGLETON(className)\
public:\
className(){};\
virtual bool init();\
public:\
static className* _shared;\
static className* shared(){\
if(!_shared) {_shared = new className();_shared->init();}\
return _shared;\
};\
void destroy() {if(_shared) {delete _shared; _shared = NULL;}};\

class ControlBannerView :public cocos2d::Ref
{
    SINGLETON(ControlBannerView);
    void showAdmo();
};




#endif /* defined(__CrazyBox__ControlBannerView__) */
