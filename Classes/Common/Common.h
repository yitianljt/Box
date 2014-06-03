//
//  Common.h
//  ShareTest
//
//  Created by jintao on 14-5-24.
//
//

#ifndef ShareTest_Common_h
#define ShareTest_Common_h

#include "cocos2d.h"

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


#define SINGLETON_IMPL(className)\
className* className::_shared = NULL;\



#define COM_CREATE_FUNC(className)\
public:\
virtual bool init();\
static className* create();\


#define COM_CREATE_FUNC_IMPL(className)\
className* className::create() {\
className* node = new className();\
node->init();\
node->autorelease();\
return node;\
}\

typedef struct {
    cocos2d::Rect original;
    cocos2d::Rect actual;
}ColliderBox;

#define FIX_VALUE(_value, _min, _max) \
if (_value < _min)        \
_value = _min;        \
else if (_value > _max)   \
_value = _max;        \





#endif



