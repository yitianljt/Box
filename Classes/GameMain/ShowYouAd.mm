//
//  ShowYouAd.cpp
//  CrazyBox
//
//  Created by jintao on 14-6-12.
//
//

#include "ShowYouAd.h"
#import  "YouMiWallSpot.h"
#import "YouMiWall.h"
#import "YouMiView.h"


void ShowYouAd::showYouWallSpot()
{
//    if ([YouMiWallSpot isReady]) {
//        [YouMiWallSpot showSpotViewWithBlock:^{
//            NSLog(@"积分插播退出");
//        }];
//    }
    //无积分
    [YouMiWall showOffers:NO didShowBlock:^{
        NSLog(@"有米推荐墙已显示");
    } didDismissBlock:^{
        NSLog(@"有米推荐墙已退出");
    }];

    // 创建广告条
//    YouMiView* adView = [[YouMiView alloc] initWithContentSizeIdentifier:YouMiBannerContentSizeIdentifier320x50 delegate:nil];
//    
//    //可以设置委托[可选]
//    adView.delegate = self;
//    //设置文字广告的属性[可选]
//    adView.indicateTranslucency = YES;
//    adView.indicateRounded = NO;
//    //添加对应的关键词 [可选]
//    [adView addKeyword:@"女性"];
//    
//    // 开始请求广告
//    [adView start];
//    
//    // 把广告条添加到特定的view中 [例如]
//    [self.view addSubview:adView];

}