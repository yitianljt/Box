#include "BSUtil.h"
#include <map>
#include "BSFileUtil.h"
#include <algorithm> 
#include "android/bs_jni.h"
#include "BSHttp.h"

const char* BSGetDeviceIDLegally() {
    std::string device_id = "android_"+BSCallJavaSimple("GetSystemInfo", "device_id");
    char *ret_device_id = new char[device_id.size()];
    strcpy(ret_device_id, device_id.c_str());
    return ret_device_id;
}

const char* BSMd5(const char * src){
    return CCString::create(BSCallJavaSimple("md5", src))->getCString();
}

void BSCopyToClipboard(const char *) {
    // TODO:
    CCLOG("[BSUtilAndroid] BSCopyToClipboard to be implemented.");
}

void BSLogMemoryUsage() {
    // TODO:
    CCLOG("[BSUtilAndroid] BSLogMemoryUsage to be implemented.");
}

void BSMessageBox(const char * pTitle, const char * pText) {
    CCMessageBox(pText, pTitle);
}

void BSOpenUrl(const char* pUrl, bool pIsInApp) {
    if (pIsInApp) {
        //TODO
        CCLOG("[BSUtilAndroid] openUrl to be implemented.");
    }
    else {
        BSCallJavaSimple("OpenUrl", pUrl);
    }
}

bool BSOpenApp(const char* aAppURL,const char* aDownloadURL)
{
	std::string param = "";
	param.append(aAppURL);
    param.append(kParamSplit);
    param.append(aDownloadURL);
	return BSCallJavaSimple("OpenApp",param) == "1";
}

const char* BSGetCurrentVersion() {
    return CCString::create(BSCallJavaSimple("GetSystemInfo", "version_name"))->getCString();
}

bool BSIsNetworkAvailable() {
    return BSCallJavaSimple("IsNetworkAvailable", "") == "1";
}

bool BSIsUsingWifi() {
    return BSCallJavaSimple("IsUsingWifi", "") == "1";
}

bool BSIsRetina() {
    return false;
}

unsigned int BSGetSystemUpTime() {
    return atoi(BSCallJavaSimple("GetSystemBootTime", "").c_str());
}

float BSMeasureStringWidth(const char* pUTFString, unsigned int pLen, const char* pFont, unsigned int pFontSize) {
    std::string param = "";
    param.append(pUTFString, pLen);
    param.append(kParamSplit);
    param.append(pFont);
    param.append(kParamSplit);
    param.append(BSFormat("%d",pFontSize));
    int ret_width = atoi(BSCallJavaSimple("MeasureStringWidth", param).c_str());
    return ret_width;
}

const char* BSUrlEncode(const char* pUrl) {
    CCString* str = CCString::create(curl_easy_escape( BSHttp::shared()->curl , pUrl , strlen(pUrl) ));
    str->autorelease();
    return str->getCString();
}

void BSRateApp(const char* pAppID) {
    
}

cocos2d::CCObject* g_alertTarget = NULL;
cocos2d::SEL_CallFuncO g_alertSelector = NULL;

void BSAlert(const char* pTitle, const char* pMessage, const char* pOk, const char* pCancel, CCObject* pTarget, SEL_CallFuncO pSelector) {
    std::string param = "";
    param.append(pTitle);
    param.append(kParamSplit);
    param.append(pMessage);
    param.append(kParamSplit);
    param.append(pOk);
    if (pCancel != NULL) {
        param.append(kParamSplit);
        param.append(pCancel);
    }
    g_alertTarget = pTarget;
    g_alertSelector = pSelector;
    BSCallJavaSimple("BSAlert", param);
}

bool BSIsIPad() {
    return false;
}