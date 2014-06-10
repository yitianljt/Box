#import <UIKit/UIKit.h>
#import "GADBannerViewDelegate.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate,GADBannerViewDelegate> {
    UIWindow *window;
    GADBannerView* bannerView_;

    
}

-(void) showBanner;
-(void) hideBanner;
@property(nonatomic, readonly) RootViewController* viewController;

@end

