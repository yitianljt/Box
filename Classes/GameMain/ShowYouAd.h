//
//  ShowYouAd.h
//  CrazyBox
//
//  Created by jintao on 14-6-12.
//
//

#ifndef __CrazyBox__ShowYouAd__
#define __CrazyBox__ShowYouAd__

#include "cocos2d.h"
#include "Common.h"

class ShowYouAd :public cocos2d::Ref
{
    SINGLETON(ShowYouAd);
public:
    void showYouWallSpot();

};

#endif /* defined(__CrazyBox__ShowYouAd__) */
