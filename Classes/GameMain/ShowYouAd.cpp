//
//  ShowYouAd.cpp
//  CrazyBox
//
//  Created by jintao on 14-6-12.
//
//

#include "ShowYouAd.h"


SINGLETON_IMPL(ShowYouAd);

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDRORD
void ShowYouAd::showYouWallSpot()
{

}


#endif

bool ShowYouAd::init()
{
	return true;
}