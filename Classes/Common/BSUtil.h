#ifndef bscommon_BSUtil_h
#define bscommon_BSUtil_h
#include "cocos2d.h"
#include "BSData.h"
using namespace cocos2d;
using namespace std;

typedef unsigned int BSTimeMS;

const char* BSMd5(const char* src);

BSTimeMS BSGetCurrentTimeMS();
double BSGetTimeDifferenceToDate(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute, unsigned int seconds);
bool BSStringReplace(std::string& strBase, const std::string& strSrc, const std::string& strDes);
unsigned int BSGetCurrentTimeSec();

const char* BSGetDeviceIDLegally();
//返回类似08:01:01这样的倒计时
const char* BSStringFromSecondsClockStyle(unsigned int sec);
//返回类似“刚刚”，“2分钟之前”，“2小时之前”
const char* BSStringFromSecondsPlainStyle(unsigned int sec);
const char* BSStringByAppending(const char *pStr, const char *pAppend);
const char* BSStringFromInteger(int pVal);
const char* BSStringFromFormat(const char* pStr...);
const char* BSStringJoin(const char* pParamSplit, const char** pArray, unsigned int pLen);

template <class K, class V>
void BSFreeMap(typename std::map<K, V>::iterator begin, typename std::map<K, V>::iterator end) {
    for(typename std::map<K, V>::iterator it = begin; it != end; it++) delete it->second;
}
template <class K, class V>
void BSFreeMap(typename std::map<K, V> *map) {
    BSFreeMap<K, V>(map->begin(), map->end());
    map->clear();
}

template <class V>
void BSFreeVector(typename std::vector<V>::iterator begin, typename std::vector<V>::iterator end) {
    for(typename std::vector<V>::iterator it = begin; it != end; it++) {
        delete *it;
    }
}
template <class V>
void BSFreeVector(typename std::vector<V> *vector) {
    BSFreeVector<V>(vector->begin(), vector->end());
    vector->clear();
}

template <class V>
void BSRemoveVectorItem(typename std::vector<V> *vector, V pKey) {
    vector->erase(remove(vector->begin(), vector->end(), pKey), vector->end());
}

unsigned int BSGetTimeOfDay();
unsigned int BSGetSystemUpTime();

void BSMakeCachedAnimation(const char* pNameFormat, unsigned int pStartNum, unsigned int pEndNum, float pInterval, const char* pCacheName, bool pIsLoop = false, bool isReverse = false);

ccColor3B BSColorFromName(const char* pName);

bool BSIsStartOfChinese(unsigned char pCh);
bool BSIsAscii(char pCh);
bool BSIsAsciiNumber(char pCh);

void BSOpenUrl(const char* pUrl, bool pIsInApp);

bool BSOpenApp(const char* aAppURL,const char* aDownloadURL);

void BSSliceRects(std::vector<CCRect>& pOriginalRects, std::vector<CCRect>& pRects);

float BSPointDistance(const CCPoint& a, const CCPoint& b);

int BSVersionCompare(const char* pVer1, const char* pVer2);

const char* BSGetCurrentVersion();

bool BSIsUsingWifi();

bool BSIsNetworkAvailable();

bool BSIsRetina();

void BSCopyToClipboard(const char* pText);

std::string BSFormat(const char *format, ...);

//
unsigned int BSUTFStringBytes(const char* pStr);

//计算在指定的宽度内能显示多少个字符
//注意：返回的是byte个数，而不是字符
unsigned int BSCountStringCanDisplayInWidth(const char* pUTFString, const char* pFont, unsigned int pFontSize, float pWidth, float& pDisplayWidth);

//利用各平台提供的方法实现
float BSMeasureStringWidth(const char* pUTFString, unsigned int pLen, const char* pFont, unsigned int pFontSize);

void BSMessageBox(const char* pTitle, const char* pText);

int BSCalcStringLength(const char* pStr);

void BSLogMemoryUsage();

const char* BSUrlEncode(const char* pUrl);

template <typename T>
T BSRand(T from, T to) {
    return static_cast<T>((double) rand() / RAND_MAX * (to - from) + from);
}

unsigned int BSRoll(unsigned int* pProbs, unsigned int pProbCnt);
unsigned int BSRoll(const BSData& pProb);

bool BSIsPointInSquareRange(const CCPoint& pSrc, const CCPoint& pDst, int pRange);

CCPoint BSMiddlePos(CCNode* pNode);

void BSReplaceControlWithSamePosition(CCNode *newControl, CCNode *oldControl);

float BSAngleForTwoPoint(const CCPoint & pa, const CCPoint & pb);

CCSprite * BSAddStrokeToLabel(cocos2d::CCLabelTTF *label, float width, cocos2d::ccColor3B color, GLubyte opacity);

void BSAssert(bool pCondition, const char* pMessage);

CCSize BSWinSize();

float BSGetOSVersion();

void BSRateApp(const char* pAppID);

const char* BSMakeKeyForTea(const char* pStr);

void BSAlert(const char* pTitle, const char* pMessage, const char* pOk, const char* pCancel, CCObject* pTarget, SEL_CallFuncO pSelector);

const char* BSGenerateOrderID();
bool BSIsIPad();
#endif
