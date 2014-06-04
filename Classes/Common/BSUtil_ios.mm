#include "BSUtil.h"
#include <ctime>
#import <sys/socket.h>
#import <netinet/in.h>
#import <netinet6/in6.h>
#import <arpa/inet.h>
#import <ifaddrs.h>
#import <net/if.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#import <CommonCrypto/CommonDigest.h>
#import "BSReachability.h"

NSString* md5(NSString* str){
    
    if(str == nil || [str length] == 0)
        return nil;
    
    const char *value = [str UTF8String];
    
    unsigned char outputBuffer[CC_MD5_DIGEST_LENGTH];
    CC_MD5(value, strlen(value), outputBuffer);
    
    NSMutableString *outputString = [[NSMutableString alloc] initWithCapacity:CC_MD5_DIGEST_LENGTH * 2];
    for(NSInteger count = 0; count < CC_MD5_DIGEST_LENGTH; count++){
        [outputString appendFormat:@"%02x",outputBuffer[count]];
    }
    
    return [outputString autorelease];
}

const char* BSMd5(const char * src){
    NSString* str = [NSString stringWithUTF8String:src];
    return [md5(str) UTF8String];
}

NSString * getMacAddress() {
    
    int                 mib[6];
    size_t              len;
    char                *buf;
    unsigned char       *ptr;
    struct if_msghdr    *ifm;
    struct sockaddr_dl  *sdl;
    
    mib[0] = CTL_NET;
    mib[1] = AF_ROUTE;
    mib[2] = 0;
    mib[3] = AF_LINK;
    mib[4] = NET_RT_IFLIST;
    
    if ((mib[5] = if_nametoindex("en0")) == 0) {
        printf("Error: if_nametoindex error\n");
        return NULL;
    }
    
    if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
        printf("Error: sysctl, take 1\n");
        return NULL;
    }
    
    if ((buf = (char*)malloc(len)) == NULL) {
        printf("Could not allocate memory. error!\n");
        return NULL;
    }
    
    if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
        printf("Error: sysctl, take 2");
        free(buf);
        return NULL;
    }
    
    ifm = (struct if_msghdr *)buf;
    sdl = (struct sockaddr_dl *)(ifm + 1);
    ptr = (unsigned char *)LLADDR(sdl);
    NSString *outstring = [NSString stringWithFormat:@"%02X:%02X:%02X:%02X:%02X:%02X",
                           *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
    free(buf);
    
    return outstring;
}

const char* BSGetDeviceIDLegally() {
#if TARGET_IPHONE_SIMULATOR
    NSString * dev = DEVELOPER_NAME;
    return CCString::create(std::string("IPHONE-SIMULATOR-FAKE-UUID-") + [[dev uppercaseString] UTF8String])->getCString();
#else
    if (BSGetOSVersion() >= 6.0) {
        return [[[[UIDevice currentDevice] identifierForVendor] UUIDString] UTF8String];
    }
    else {
        NSString* mac = getMacAddress();
        return BSMd5([mac UTF8String]);
    }
#endif
}

CCImage* BSGetUIImageFromSprite(CCSprite* pSprite) {
    CCRenderTexture* renderTex = CCRenderTexture::create(pSprite->getContentSize().width, pSprite->getContentSize().height);
    pSprite->setAnchorPoint(ccp(0, 0));
    renderTex->begin();
    pSprite->visit();
    renderTex->end();
    return renderTex->newCCImage();
}

@interface BSWebViewHelper : NSObject <UIWebViewDelegate>

@property(assign) UIActivityIndicatorView* indicator;

@end

@implementation BSWebViewHelper

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    NSLog(@"width:%f, height:%f", webView.frame.size.width/2, webView.frame.size.height/2);
    return YES;
}

- (void)webViewDidStartLoad:(UIWebView *)webView
{
    NSLog(@"webview start load");
    [self.indicator startAnimating];
}
- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    NSLog(@"webview finish load");
    [self.indicator stopAnimating];
}
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    NSLog(@"webview finish load with error");
    [self.indicator stopAnimating];
}

@end

void BSOpenUrl(const char* pUrl, bool pIsInApp) {
//    pIsInApp = false;
    if (pIsInApp) {
        const float TOOLBAR_HEIGHT = 40;
        UIWebView* web = [[UIWebView alloc] init];
        BSWebViewHelper* webHelper = [[BSWebViewHelper alloc] init];
//        [web setAutoresizesSubviews:YES];
//        [web setAutoresizingMask:UIViewAutoresizingFlexibleWidth];
        [web setDelegate:webHelper];
//        if (BSGetOSVersion() >= 6.0) {
//            UIViewController* rootView = [[[UIApplication sharedApplication] keyWindow] rootViewController];
//            [web setFrame:CGRectMake(0, TOOLBAR_HEIGHT, BSIsRetina() ? BSWinSize().width/2 : BSWinSize().width, BSIsRetina() ? BSWinSize().height/2 : BSWinSize().height)];
//            [rootView.view addSubview:web];
//        }
//        else {
//            UIView* eaglView = [[[[UIApplication sharedApplication] keyWindow] subviews] objectAtIndex:0];
//            [web setFrame:CGRectMake(0, TOOLBAR_HEIGHT, BSIsRetina() ? BSWinSize().height/2 : BSWinSize().height, BSIsRetina() ? BSWinSize().width/2 : BSWinSize().width)];
//            [eaglView addSubview:web];
//        }
        [web setFrame:CGRectMake(0, TOOLBAR_HEIGHT, BSIsRetina() ? BSWinSize().height/2 : BSWinSize().height, BSIsRetina() ? BSWinSize().width/2 : BSWinSize().width)];
        [[[UIApplication sharedApplication] keyWindow] addSubview:web];

        
        UIActivityIndicatorView* indicator = [[UIActivityIndicatorView alloc]
                      initWithFrame:CGRectMake(web.frame.size.width/2, web.frame.size.height/2, 20,20)];
        [indicator setActivityIndicatorViewStyle:UIActivityIndicatorViewStyleGray];
        [indicator setHidesWhenStopped:YES];
        [web addSubview:indicator];
        [webHelper setIndicator:indicator];

        NSURLRequest* request = [NSURLRequest requestWithURL:[NSURL URLWithString:[NSString stringWithUTF8String:pUrl]]];
        [web loadRequest:request];
        [web scalesPageToFit];
    }
    else {
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:pUrl]]];
    }
}

bool BSOpenApp(const char* aAppURL,const char* aDownloadURL)
{
	NSString *stringURL = [NSString stringWithUTF8String:aAppURL];
    
    NSURL *url=[NSURL URLWithString:stringURL];
    
    BOOL exist = [[UIApplication sharedApplication] openURL:url];
    
    if(exist == NO)
	{
        stringURL = [NSString stringWithUTF8String:aDownloadURL];
        url = [NSURL URLWithString:stringURL];
        [[UIApplication sharedApplication] openURL:url];
	}
	return exist;
}

const char* BSGetCurrentVersion() {
    return [[[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"] UTF8String];
}

bool BSIsNetworkAvailable() {
    BSReachability *networkReachability = [BSReachability reachabilityForInternetConnection];
    NetworkStatus networkStatus = [networkReachability currentReachabilityStatus];
    if (networkStatus == NotReachable) {
        NSLog(@"There IS NO internet connection");
        return false;
    } else {
        NSLog(@"There IS internet connection");
        return true;
    }
}

bool BSIsUsingWifi() {
    struct ifaddrs *addresses;
    struct ifaddrs *cursor;
    bool wiFiAvailable = false;
    if (getifaddrs(&addresses) != 0) return false;
    
    cursor = addresses;
    while (cursor != NULL) {
    	if (cursor -> ifa_addr -> sa_family == AF_INET
    		&& !(cursor -> ifa_flags & IFF_LOOPBACK)) // Ignore the loopback address
    	{
    		// Check for WiFi adapter
    		if (strcmp(cursor -> ifa_name, "en0") == 0) {
    			wiFiAvailable = true;
    			break;
    		}
    	}
    	cursor = cursor -> ifa_next;
    }
    
    freeifaddrs(addresses);
    return wiFiAvailable;
}

bool BSIsRetina() {
    if ([[UIScreen mainScreen] respondsToSelector:@selector(displayLinkWithTarget:selector:)] &&
        ([UIScreen mainScreen].scale == 2.0)) {
        return true;
    }
    return false;
}

void BSCopyToClipboard(const char* pText) {
    UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
    [pasteboard setString:[NSString stringWithUTF8String:pText]];
}

unsigned int BSGetSystemUpTime() {
    struct timeval boottime;
    int mib[2] = {CTL_KERN, KERN_BOOTTIME};
    size_t size = sizeof(boottime);
    time_t now;
    time_t uptime = -1;
    (void)time(&now);
    if (sysctl(mib, 2, &boottime, &size, NULL, 0) != -1 && boottime.tv_sec != 0)
    {
        uptime = now - boottime.tv_sec;
    }
    return static_cast<unsigned int>(uptime);
}

float BSMeasureStringWidth(const char* pUTFString, unsigned int pLen, const char* pFont, unsigned int pFontSize) {
    UIFont* font = [UIFont fontWithName:[NSString stringWithUTF8String:pFont] size:CGFloat(pFontSize)];
    if (!font) {
        CCLOG("font not found");
    }
    char* str = new char[pLen + 1];
    strncpy(str, pUTFString, pLen);
    str[pLen] = '\0';
    CGSize sz = [[NSString stringWithUTF8String:str] sizeWithFont:font];
    delete [] str;
    return sz.width;
}

void BSMessageBox(const char* pTitle, const char* pText) {
    NSString * title = (pTitle) ? [NSString stringWithUTF8String : pTitle] : nil;
    NSString * msg = (pText) ? [NSString stringWithUTF8String : pText] : nil;
    UIAlertView * messageBox = [[UIAlertView alloc] initWithTitle: title
                                                          message: msg
                                                         delegate: nil
                                                cancelButtonTitle: @"OK"
                                                otherButtonTitles: nil];
    
    for (UIView *view in messageBox.subviews) {
        if([[view class] isSubclassOfClass:[UILabel class]]) {
            if ([[(UILabel*)view text] isEqualToString:msg]) {
                ((UILabel*)view).textAlignment = NSTextAlignmentLeft;
            }
        }
    }
    [messageBox autorelease];
    [messageBox show];

}

@interface BSAlertHelper : NSObject<UIAlertViewDelegate>
@property(assign) CCObject* target;
@property(assign) SEL_CallFuncO selector;
@end

@implementation BSAlertHelper

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    [alertView dismissWithClickedButtonIndex:buttonIndex animated:NO];
    if (buttonIndex == 0) {
        //取消
        if(self.target && self.selector) {
            (self.target->*self.selector)(reinterpret_cast<CCObject*>(false));
        }
    }
    else {
        if(self.target && self.selector) {
            (self.target->*self.selector)(reinterpret_cast<CCObject*>(true));
        }
    }
    [self release];
}

@end

void BSAlert(const char* pTitle, const char* pMessage, const char* pOk, const char* pCancel, CCObject* pTarget, SEL_CallFuncO pSelector)
{
    BSAlertHelper* helper = [[BSAlertHelper alloc] init];
    helper.target = pTarget;
    helper.selector = pSelector;
    NSString * title = (pTitle) ? [NSString stringWithUTF8String : pTitle] : nil;
    NSString * msg = (pMessage) ? [NSString stringWithUTF8String : pMessage] : nil;
    UIAlertView * messageBox = [[UIAlertView alloc] initWithTitle: title
                                                          message: msg
                                                         delegate: helper
                                                cancelButtonTitle: [NSString stringWithUTF8String:pCancel]
                                                otherButtonTitles: [NSString stringWithUTF8String:pOk], Nil];
    
    for (UIView *view in messageBox.subviews) {
        if([[view class] isSubclassOfClass:[UILabel class]]) {
            if ([[(UILabel*)view text] isEqualToString:msg]) {
                ((UILabel*)view).textAlignment = NSTextAlignmentLeft;
            }
        }
    }
    [messageBox autorelease];
    dispatch_async(dispatch_get_main_queue(), ^{
        [messageBox show];
    });
    
}


#import "mach/mach.h"

vm_size_t usedMemory(void) {
    struct task_basic_info info;
    mach_msg_type_number_t size = sizeof(info);
    kern_return_t kerr = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &size);
    return (kerr == KERN_SUCCESS) ? info.resident_size : 0; // size in bytes
}

vm_size_t freeMemory(void) {
    mach_port_t host_port = mach_host_self();
    mach_msg_type_number_t host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    vm_size_t pagesize;
    vm_statistics_data_t vm_stat;
    
    host_page_size(host_port, &pagesize);
    (void) host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stat, &host_size);
    return vm_stat.free_count * pagesize;
}

void logMemUsage(void) {
    // compute memory usage and log if different by >= 100k
    static long prevMemUsage = 0;
    long curMemUsage = usedMemory();
    long memUsageDiff = curMemUsage - prevMemUsage;
    
    if (memUsageDiff > 100000 || memUsageDiff < -100000) {
        prevMemUsage = curMemUsage;
        NSLog(@"Memory used %7.1f (%+5.0f), free %7.1f kb", curMemUsage/1000.0f, memUsageDiff/1000.0f, freeMemory()/1000.0f);
    }
}

void BSLogMemoryUsage() {
    logMemUsage();
    CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}

const char* BSUrlEncode(const char* pUrl) {
    NSString *encodedString = (NSString *)CFURLCreateStringByAddingPercentEscapes(
                                                                                  NULL,
                                                                                  (CFStringRef)[NSString stringWithUTF8String:pUrl],
                                                                                  NULL,
                                                                                  (CFStringRef)@"!*'();:@&=+$,/?%#[]",
                                                                                  kCFStringEncodingUTF8 );
    return [encodedString UTF8String];
}

float BSGetOSVersion() {
    return [[[UIDevice currentDevice] systemVersion] floatValue];
}

void BSRateApp(const char* pAppID) {
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 7.0) {
        BSOpenUrl(BSStringFromFormat("itms-apps://itunes.apple.com/app/id%s?at=10l6dK", pAppID), false);
    }
    else {
        BSOpenUrl(BSStringFromFormat("http://itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?pageNumber=0&sortOrdering=1&type=Purple+Software&mt=8&id=%s", pAppID), false);
    }
}

bool BSIsIPad() {
    if ( UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad )
    {
        return true; /* Device is iPad */
    }
    else {
        return false;
    }
}