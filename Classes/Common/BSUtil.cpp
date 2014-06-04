#include "BSUtil.h"
#include "BSData.h"
#include <map>
#include <algorithm>

using namespace std;

const unsigned int kMaxPlaceHolders = 10;
const unsigned int kMaxStringLen = 1024*100;

//一些有用的函数

BSTimeMS BSGetCurrentTimeMS()
{
    timeval tp={0};
    gettimeofday(&tp, 0);
    BSTimeMS tm = (tp.tv_sec - 1337599892) * 1000 + tp.tv_usec / 1000;
    //CCLOG("timeofday:%d", tm);
    return tm;
}

unsigned int BSGetCurrentTimeSec() {
    return BSGetCurrentTimeMS() / 1000;
}

unsigned int BSGetTimeOfDay() {
    time_t t = time(NULL);
    tm* time = localtime(&t);
    return (time->tm_hour * 3600) + (time->tm_min * 60) + time->tm_sec;
}

double BSGetTimeDifferenceToDate(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute, unsigned int seconds) {
    time_t now;
    time(&now);
    tm date = *localtime(&now);
//    CCLOG("localtime, year:%i, month:%i, day:%i, hour:%i, min:%i", date.tm_year, date.tm_mon, date.tm_mday, date.tm_hour, date.tm_min);
    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;
    date.tm_hour = hour;
    date.tm_min = minute;
    date.tm_sec = seconds;
//    CCLOG("targettime, year:%i, month:%i, day:%i, hour:%i, min:%i", date.tm_year, date.tm_mon, date.tm_mday, date.tm_hour, date.tm_min);
    return difftime(mktime(&date), now);
}

const char* BSStringFromSecondsClockStyle(unsigned int sec)
{
    unsigned int h = sec / 3600;
    unsigned int m = (sec % 3600) / 60;
    unsigned int s = sec % 60;
    char timeStr[50] = {0};
    if (h > 0) {
        sprintf(timeStr, "%02d:%02d:%02d",h,m,s);
    }
    else {
        sprintf(timeStr, "%02d:%02d", m, s);
    }
    CCString* str = CCString::create(timeStr);
    return str->getCString();
}

const char* BSStringFromSecondsPlainStyle(unsigned int sec) {
    char str[64] = {0};
    sec = sec / 60;
    if (sec <= 0) {
        sprintf(str, "刚刚");
    } else if (sec < 60){
        sprintf(str, "%u分钟前", sec);
    } else if(sec >= 60 && sec < 60 * 24){
        sprintf(str, "%u小时前", sec / 60);
    } else {
        sprintf(str, "%u天前", sec / 60 / 24);
    }
    return CCString::create(str)->getCString();
}

bool BSStringReplace(std::string& strBase, const std::string& strSrc, const std::string& strDes) {
    std::string::size_type pos = 0;  
    std::string::size_type srcLen = strSrc.size();  
    std::string::size_type desLen = strDes.size();  
    pos=strBase.find(strSrc, pos);
    bool isChanged = false;
    while ((pos != std::string::npos))
    {  
        strBase.replace(pos, srcLen, strDes);  
        pos=strBase.find(strSrc, (pos+desLen));
        isChanged = true;
    }  
    return isChanged;
}

const char* BSStringByAppending(const char *pStr, const char *pAppend) {
    char buff[255] = {0}; 
    sprintf(buff, "%s%s", pStr, pAppend); 
    CCString* str = new CCString(buff); 
    str->autorelease(); 
    return str->getCString();
}

const char* BSStringFromInteger(int pVal) {
    char buff[12] = {0};
    sprintf(buff, "%i", pVal);
    CCString* str = new CCString(buff);
    str->autorelease();
    return str->getCString();
}

const char* BSStringFromFormat(const char* pText...) {
    CCString* str = NULL;
    va_list ap;
    va_start(ap, pText);
    char* pBuf = (char*)malloc(kMaxStringLen);
    if (pBuf != NULL)
    {
        vsnprintf(pBuf, kMaxStringLen, pText, ap);
        str = CCString::create(pBuf);
        free(pBuf);
    }
    va_end(ap);
    return str->getCString();
}

const char* BSStringJoin(const char* pParamSplit, const char** pArray, unsigned int pLen) {
    string str;
    for (unsigned int i = 0; i < pLen; i++) {
        str += pArray[i];
        if (i != pLen -1) {
            str += pParamSplit;
        }
    }
    return CCString::create(str)->getCString();
}

void BSMakeCachedAnimation(const char* pNameFormat, unsigned int pStartNum, unsigned int pEndNum, float pInterval, const char* pCacheName, bool pIsLoop, bool isReverse /* = false */) {
    CCArray* array = CCArray::create();
    for (unsigned int i = pStartNum; i <= pEndNum; i++) {
        char name[256] = {0};
        sprintf(name, pNameFormat, i);
        array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
    }
    
    if (isReverse) {
        array->reverseObjects();
    }
    
    if (pIsLoop) {
        for (unsigned int i = pEndNum; i >= pStartNum; i--) {
            char name[256] = {0};
            sprintf(name, pNameFormat, i);
            array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
        }
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(array, pInterval);
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, pCacheName);
}


ccColor3B BSColorFromName(const char* pName) {
    //初始化颜色映射表
    std::map<std::string, ccColor3B> colorDict = std::map<std::string, ccColor3B>();
    colorDict["RED"] = ccc3(240, 0, 0);
    colorDict["BLUE"] = ccc3(0, 216, 216);
    colorDict["ORANGE"] = ccc3(240, 170, 0);
    colorDict["YELLOW"] = ccYELLOW;
    colorDict["GREEN"] = ccGREEN;
    colorDict["BLACK"] = ccBLACK;
    colorDict["GRAY"] = ccGRAY;
    
    std::string name = std::string(pName);
    CCAssert(colorDict.find(name) != colorDict.end(), "color not found");
    return colorDict[pName];
}

bool BSIsStartOfChinese(unsigned char pCh) {
    pCh = pCh % 256;
    return pCh >= 192 && pCh < 253;
}

bool BSIsAscii(char pCh) {
    return pCh >= 0 && pCh <= 126;
}

bool BSIsAsciiNumber(char pCh) {
    return pCh >= '0' && pCh <= '9';
}

class RectComparor {
public:
    bool operator() (const CCRect& a, const CCRect& b) {
        return a.origin.x < b.origin.x;
    }
};

void BSSliceRects(std::vector<CCRect>& pOriginalRects, std::vector<CCRect>& pRects) {
    //首先根据x轴排序
    sort(pOriginalRects.begin(), pOriginalRects.end(), RectComparor());
    pRects.assign(pOriginalRects.begin(), pOriginalRects.end());
    //一个一个加入到结果集中
//    for (unsigned int i = 0; i < pOriginalRects.size(); i++) {
//        const CCRect& rect = pOriginalRects[i];
//        for (unsigned int k = 0; k < pRects.size(); k++) {
//            //扫描结果集, 如果有重合部分, 则截断
//        }
//    }
}

float BSPointDistance(const CCPoint& a, const CCPoint& b) {
    return sqrtf(powf(a.x - b.x, 2.0f) + powf(a.y - b.y, 2.0f));
}

int BSVersionCompare(const char* version1, const char* version2) {
    unsigned int major1 = 0;
    unsigned int minor1 = 0;
    unsigned int revision1 = 0;
    unsigned int major2 = 0;
    unsigned int minor2 = 0;
    unsigned int revision2 = 0;
    sscanf(version1, "%d.%d.%d", &major1, &minor1, &revision1);
    sscanf(version2, "%d.%d.%d", &major2, &minor2, &revision2);
    return major1 * 1000000 + minor1 * 1000 + revision1 - (major2 * 1000000 + minor2 * 1000 + revision2);
}

// 格式化字符串，并返回std::string
// windows和linux的api行为不一致，需要区别对待
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
// windows下直接分配5K内存，如果超出，则截断
std::string BSFormat(const char *format, ...){
    const int kFormatBufferSize = 64 * 1024;
    char buff[kFormatBufferSize] = "";
    int size = 0;
    memset(buff, 0, sizeof(buff));
    va_list ap;
    va_start(ap, format);
    size = vsnprintf_s( buff, sizeof(buff), _TRUNCATE, format, ap);
    if( size>-1 && size < kFormatBufferSize) {
        return string(buff, size);
    }
    return string(format);
}
#else
//linux系统下，不停尝试扩大buffer，直至成功
//iOS和linux应该一样？
std::string BSFormat(const char *format, ...){ 
    static const int kFormatBufferSize = 128;
    
    char *buffer;
    int n, size = strlen(format);
    if( size == 0)
        return string("");
    
    // 初始缓冲区大小
    size = MAX(size, kFormatBufferSize);
    
    if( (buffer = (char*)malloc(size)) == NULL ) 
        return string(format);  
    
    va_list ap;  
    while(1){
        va_start(ap, format);
        n = vsnprintf(buffer, size, format, ap);
        va_end(ap);
        
        // 成功!
        if(n>-1&&n<size) { 
            string s(buffer,n);
            free(buffer);
            return s;
        }
        
        if(n>-1){ // glibc 2.1，会返回确切需要的缓冲大小
            size = n + 1;
        } else {  // glibc 2.0, 不知道确切大小
            size *= 2;
        }
        // 重新申请内存
        if( (buffer=(char*)realloc(buffer, size)) == NULL ) {
            free(buffer);
            return string(format);
        }
    }
}
#endif

unsigned int BSUTFStringBytes(const char* pUTFString) {
    unsigned char firstChar = pUTFString[0];
//    CCLOG("first char:%02X, sizeof char:%u", (unsigned char)firstChar, sizeof(char));
    unsigned char flag = firstChar & 0x80;
//    CCLOG("flag:%02X", (unsigned char)flag);
    if (flag == 0x0) {
        //单字节
        return 1;
    }
    flag = firstChar & 0xe0;
//    CCLOG("flag:%02X", (unsigned char)flag);
    if (flag == 0xc0) {
        return 2;
    }
    flag = firstChar & 0xf0;
//    CCLOG("flag:%02X", (unsigned char)flag);
    if (flag == 0xe0) {
        return 3;
    }
    flag = firstChar & 0xf8;
//    CCLOG("flag:%02X", (unsigned char)flag);
    if (flag == 0xf0) {
        return 4;
    }
//    int p = pUTFString[0];
    return 0;
}

unsigned int BSCountStringCanDisplayInWidth(const char* pUTFString, const char* pFont, unsigned int pFontSize, float pWidth, float& pDisplayWidth) {
    unsigned int sz = strlen(pUTFString);
    //如果有换行，则最多到换行的位置
    string str(pUTFString);
    size_t pos = str.find("\n");
    if (pos != string::npos) {
        sz = pos + 2;
    }
    unsigned int i = 0;
    pDisplayWidth = 0;
//    CCLOG("count string:%s, width:%f, max string size:%i", pUTFString, pWidth, sz);
    while (i < sz && pDisplayWidth < pWidth) {
        unsigned int byteCnt = BSUTFStringBytes(pUTFString + i);
//        CCLog("utf string byte:%u, i:%u, sz:%u", byteCnt, i, sz);
        pDisplayWidth = BSMeasureStringWidth(pUTFString, i + byteCnt, pFont, pFontSize);
//        CCLog("measure string %s, width:%f", string(pUTFString + i, pUTFString+i+byteCnt).c_str(), BSMeasureStringWidth(pUTFString + i, byteCnt, pFont, pFontSize));
        i += byteCnt;
    }
    return i;
}

int BSCalcStringLength(const char* pszText) {
    unsigned int sz = strlen(pszText);
    unsigned int i = 0;
    unsigned int len = 0;
    while (i < sz) {
        unsigned int byteCnt = BSUTFStringBytes(pszText + i);
        if (*(pszText + i) == '\n') {
            len += 0;
        }
        else {
            len += 1;
        }
        i += byteCnt;
    }
    return len;
}

unsigned int BSRoll(unsigned int* pProbs, unsigned int pProbCnt) {
    unsigned int base = 0;
    for (unsigned int i = 0; i < pProbCnt; i++) {
        base += pProbs[i];
    }
    unsigned int r = rand() % base;
    unsigned int sum = 0;
    for (unsigned int i = 0; i < pProbCnt; i++) {
        if (r >= sum && r < sum + pProbs[i]) {
            return i;
        }
        else {
            sum += pProbs[i];
        }
    }
    return -1;
}

unsigned int BSRoll(const BSData& pProbs) {
    unsigned int* probs = new unsigned int[pProbs.size()/2];
    unsigned int* keys = new unsigned int[pProbs.size()/2];
    for (unsigned int i = 0; i < pProbs.size(); i++) {
        if (i % 2 == 0) {
            keys[i/2] = pProbs[i].asInt();
        }
        else {
            probs[i/2] = pProbs[i].asInt();
        }
    }
    unsigned int result = keys[BSRoll(probs, pProbs.size()/2)];
    delete [] probs;
    delete [] keys;
    return result;
}

bool BSIsPointInSquareRange(const CCPoint& pSrc, const CCPoint& pDst, int pRange) {
    if (pRange < 0) {
        return true; //小于0代表全体
    }
    int xRange = abs(static_cast<int>(pDst.x - pSrc.x));
    int yRange = abs(static_cast<int>(pDst.y - pSrc.y));
    return xRange <= pRange && yRange <= pRange;
}

CCPoint BSMiddlePos(CCNode* pNode) {
    return ccp(pNode->getContentSize().width/2, pNode->getContentSize().height/2);
}

void BSReplaceControlWithSamePosition(CCNode *newControl, CCNode *oldControl) {
    newControl->setPosition(oldControl->getPosition());
    oldControl->getParent()->addChild(newControl);
    oldControl->removeFromParentAndCleanup(true);
}

float BSAngleForTwoPoint(const CCPoint & pa, const CCPoint & pb) {
    double dy = pb.y - pa.y;
    double dx = pb.x - pa.x;
    
    double atanyx = ::abs(dx) < FLT_EPSILON ? 0 : atan2(dy, dx);
    return -atanyx * 180 / M_PI;
}


CCSprite * BSAddStrokeToLabel(cocos2d::CCLabelTTF * label, float size, cocos2d::ccColor3B color, GLubyte opacity) {
    CCPoint originalPos = label->getPosition();
    ccColor3B originalColor = label->getColor();
    GLubyte originalOpacity = label->getOpacity();
    bool originalVisibility = label->isVisible();
    ccBlendFunc originalBlend = label->getBlendFunc();
    
    label->setColor(color);
    label->setOpacity(opacity);
    ccBlendFunc bf = {GL_SRC_ALPHA, GL_ONE};
    label->setBlendFunc(bf);
    
    CCPoint bottomLeft = ccp(label->getTexture()->getContentSize().width * label->getAnchorPoint().x + size,
                             label->getTexture()->getContentSize().height * label->getAnchorPoint().y + size);
    CCRenderTexture* rt = CCRenderTexture::create(label->getTexture()->getContentSize().width + size * 2,
                                                  label->getTexture()->getContentSize().height + size * 2);
    /* 在原始位置绘制文字，用于镂空用 */
    label->setPosition(bottomLeft);
    rt->begin();
    label->visit();
    rt->end();
    CCImage * originText = rt->newCCImage();
    glBlendEquation(GL_BLEND_EQUATION_ALPHA);
    /* 在各个方向上移动文字，重叠得到未镂空的描边 */
    rt->begin();
    /* Bresenham's circle algorithm */
    int radis = 3 * size;
    for (int x = 0, y = radis, d = 3 - 2 * radis; x <= y; ++x) {
        float xx = x / 3.0F, yy = y / 3.0F;
        label->setPosition(ccp(bottomLeft.x + xx, bottomLeft.y + yy)); label->visit();
        label->setPosition(ccp(bottomLeft.x - xx, bottomLeft.y + yy)); label->visit();
        label->setPosition(ccp(bottomLeft.x + xx, bottomLeft.y - yy)); label->visit();
        label->setPosition(ccp(bottomLeft.x - xx, bottomLeft.y - yy)); label->visit();
        label->setPosition(ccp(bottomLeft.x + yy, bottomLeft.y + xx)); label->visit();
        label->setPosition(ccp(bottomLeft.x - yy, bottomLeft.y + xx)); label->visit();
        label->setPosition(ccp(bottomLeft.x + yy, bottomLeft.y - xx)); label->visit();
        label->setPosition(ccp(bottomLeft.x - yy, bottomLeft.y - xx)); label->visit();
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y --;
        }
    }
    rt->end();
    
    /* TODO: ugly workaround. rendertexture多次绘制颜色叠加，需要取色值大的那个，需要通过glBlendEquation(GL_MAX)实现。
     * see http://stackoverflow.com/questions/2143690/is-it-possible-to-achieve-maxas-ad-opengl-blending */
    CCImage * strokedText = rt->newCCImage();
    unsigned char * pStorke = strokedText->getData();
    unsigned char * pErase = originText->getData();
    for (int i = 0; i < strokedText->getDataLen(); ++i) {
        if ((unsigned int) pErase[i * 4] != 0) {
            *(unsigned int *) &pStorke[i * 4] = 0;
        } else if ((unsigned int) pStorke[i * 4] != 0) {
            unsigned char * pixel = &pStorke[i * 4];
            (*pixel++) = color.r;
            (*pixel++) = color.g;
            (*pixel++) = color.b;
             *pixel    = opacity;
        }
    }
    originText->release();
    
    /* 用RenderTexture构造一个Sprite，以实现支持透明度 FadeIn FadeOut */
    CCTexture2D * texture2D = new CCTexture2D();
    texture2D->initWithImage(strokedText);
    strokedText->release();
    CCSprite * sprite = CCSprite::createWithTexture(texture2D);
    texture2D->release();
    
    label->setPosition(originalPos);
    label->setColor(originalColor);
    label->setBlendFunc(originalBlend);
    label->setVisible(originalVisibility);
    label->setOpacity(originalOpacity);
    
    sprite->setPosition(ccp(label->getTexture()->getContentSize().width / 2, label->getTexture()->getContentSize().height / 2));
    label->addChild(sprite, -1);
    
    return sprite;
}

void BSAssert(bool pCondition, const char* pMessage) {
    if (!pCondition) {
        CCMessageBox(pMessage, "出错了，请截屏");
    }
}

CCSize BSWinSize() {
    return CCDirector::sharedDirector()->getWinSize();
}

const char* BSMakeKeyForTea(const char* pStr) {
    BSAssert(strlen(pStr) == 32, "做为TEA的密钥长度必须为32个字符");
    string res;
    for (unsigned int i = 0; i < 32; i++) {
        res += pStr[i];
        if (i % 2 == 1) {
            res+=' ';
        }
    }
    return CCString::create(res)->getCString();
}

const char* BSGenerateOrderID() {
    return BSMd5(BSStringFromFormat("%s%d%d", BSGetDeviceIDLegally(), time(NULL), BSRand(0, 1000000)));
}