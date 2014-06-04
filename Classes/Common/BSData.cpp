#include "BSData.h"
#include "BSResource.h"
#include "BSFileUtil.h"

/**默认构造器不允许外部调用**/
BSData::BSData() {
    init();
}

void BSData::init() {
    _type = NIL;
    _valInt = 0;
    _valDouble = 0;
    _valDict = NULL;
    _valArray = NULL;
    _valStr = NULL;
}
/**赋值构造**/
BSData::BSData(const BSData& pTarget) {
    init();
    if(this == &pTarget) return;
    _type = pTarget._type;
    _valInt = pTarget._valInt;
    _valDouble = pTarget._valDouble;
    //对方的valStr被重新复制了一份
    if(pTarget._type == STR) {
        _valStr = new char[strlen(pTarget._valStr) + 1];
        strcpy(_valStr, pTarget._valStr);
    }
    //如果本身是array或者dict的话，会首先release掉他们。同时也会触发他们的removeAllObjects，同时也会触发他们里面所有BSData的release。
    //然后会利用target的内容重新生成array或者dict。同时也会触发他们里面所有的BSData的retain
    if(pTarget._type == ARRAY) {
        if(_valArray) {
            _valArray->release();
        }
        _valArray = CCArray::create();
        _valArray->retain();
        _valArray->addObjectsFromArray(pTarget._valArray);
    }
    if(pTarget._type == DICT) {
        if(_valDict) {
            _valDict->release();
        }
        _valDict = CCDictionary::createWithDictionary(pTarget._valDict);
        _valDict->retain();
    }
}
/**各种构造器**/
BSData::BSData(bool pData) {
    init();
    _valInt = pData;
    _type = BOOLEAN;
}
BSData::BSData(unsigned int pData){
    init();
    //std::cerr<<"on constructor from int, int:" << pData << std::endl;
    _valInt = pData;
    _valDouble = static_cast<double>(pData);
    _type = NUM;
    _valArray = NULL;
    _valDict = NULL;
}
BSData::BSData(int pData){
    //std::cerr<<"on constructor from int, int:" << pData << std::endl;
    init();
    _valInt = pData;
    _valDouble = static_cast<double>(pData);
    _type = NUM;
    _valArray = NULL;
    _valDict = NULL;
}
BSData::BSData(double pData) {
    //std::cerr<<"on constructor from double, double:" << pData << std::endl;
    init();
    _valDouble = pData;
    _valInt = static_cast<int>(pData);
    _type = NUM;
    _valArray = NULL;
    _valDict = NULL;
}
BSData::BSData(const char* pData) {
    //std::cerr<<"on constructor from char, char:" << pData << std::endl;
    init();
    _valStr = new char[strlen(pData) + 1];
    strcpy(_valStr, pData);
    _type = STR;
    _valArray = NULL;
    _valDict = NULL;
}
BSData::BSData(string pData) {
    //std::cerr<<"on constructor from string, char:" << pData << std::endl;
    init();
    _valStr = new char[pData.size() + 1];
    strcpy(_valStr, pData.c_str());
    _type = STR;
    _valArray = NULL;
    _valDict = NULL;
}
BSData::BSData(vector<int>& pData) {
    //std::cerr<<"on constructor from vector" << std::endl;
    init();
    _valArray = new CCArray();
    _type = ARRAY;
    for(unsigned int i = 0; i < pData.size(); i++) {
        _valArray->addObject(new BSData(pData[i]));
    }
    _valDict = NULL;
}
/**析构函数**/
BSData::~BSData() {
    switch (_type) {
        case ARRAY:
            _valArray->release();
            break;
        case DICT:
            _valDict->release();
        case STR:
            delete[] _valStr;
        default:
            break;
    }
}

bool BSData::has(const string & key)const {
    CCAssert(_valDict, "call operator[] to a non-dict BSData");
    BSData* val = dynamic_cast<BSData *>(_valDict->objectForKey(key));
    return val != NULL;
}

/**访问运算符**/
BSData& BSData::operator[] (unsigned int i) {
    CCAssert(_valArray, "call operator[] to a non-array BSData");
    return *dynamic_cast<BSData*>(_valArray->objectAtIndex(i));
}
const BSData& BSData::operator[] (unsigned int i) const{
    CCAssert(_valArray, "call operator[] to a non-array BSData");
    return *dynamic_cast<BSData*>(_valArray->objectAtIndex(i));
}
BSData& BSData::operator[] (const string& key) {
    CCAssert(_valDict, "call operator[] to a non-dict BSData");
    BSData* val = dynamic_cast<BSData *>(_valDict->objectForKey(key));
    if(val == NULL) {
        val = new BSData();
        _valDict->setObject(val, key);
        val->release();
    }
    return *val;
}
const BSData& BSData::operator[] (const string& key) const {
    CCAssert(_valDict, "call operator[] to a non-dict BSData");
    BSData* val = dynamic_cast<BSData *>(_valDict->objectForKey(key));
    CCAssert(val, "call operator[] to a const BSData without the key-value pair you want");
    return *val;
}
bool BSData::find(const string& key) const {
    CCAssert(_valDict, "call find to a non-dict BSData");
    return _valDict->objectForKey(key) ? true : false;
}
/**拷贝构造**/
BSData& BSData::operator=(const BSData& pTarget) {
    //CCLOG("on operator=");
    if(this == &pTarget) return *this;
    _type = pTarget._type;
    _valInt = pTarget._valInt;
    _valDouble = pTarget._valDouble;
    //对方的valStr被重新复制了一份
    if(pTarget._type == STR) {
        _valStr = new char[strlen(pTarget._valStr) + 1];
        strcpy(_valStr, pTarget._valStr);
    }
    //如果本身是array或者dict的话，会首先release掉他们。同时也会触发他们的removeAllObjects，同时也会触发他们里面所有BSData的release。
    //然后会利用target的内容重新生成array或者dict。同时也会触发他们里面所有的BSData的retain
    if(pTarget._type == ARRAY) {
        if(_valArray) {
            _valArray->release();
        }
        _valArray = CCArray::create();
        _valArray->retain();
        _valArray->addObjectsFromArray(pTarget._valArray);
    }
    if(pTarget._type == DICT) {
        if(_valDict) {
            _valDict->release();
        }
        _valDict = CCDictionary::createWithDictionary(pTarget._valDict);
        _valDict->retain();
    }
    return *this;
}



CCObject* BSData::copyWithZone(cocos2d::CCZone *pZone) {
    return new BSData(*this);
}

CCArray* BSData::keys() const{
    CCAssert(_type == DICT, "not dict");
    return _valDict->allKeys();
}


cJSON *BSData::toJSON() const {
	cJSON *json = NULL;
	CCArray* keys;
	//std::cerr << "to json, type:" << type << std::endl;
	switch(_type) {
        case BOOLEAN:
            json = cJSON_CreateBool(_valInt);
            break;
        case NUM:
            json = cJSON_CreateNumber(_valDouble);
            break;		
        case STR:
            json = cJSON_CreateString(_valStr);
            break;
        case ARRAY:
            json = cJSON_CreateArray();
            for(unsigned int i = 0; i < _valArray->count(); i++) {			
                cJSON_AddItemToArray(json, dynamic_cast<BSData*>(_valArray->objectAtIndex(i))->toJSON());
            }
            break;
        case DICT:
            json = cJSON_CreateObject();
            keys = _valDict->allKeys();
            if (keys) {
                for(unsigned int i = 0; i < keys->count(); i++) {
                    //std::cerr << "visit child:" << it->first << std::endl;
                    const char* key = dynamic_cast<CCString*>(keys->objectAtIndex(i))->getCString();
                    cJSON_AddItemToObject(json, key, dynamic_cast<BSData*>(_valDict->objectForKey(key))->toJSON());
                }
            }
            
            break;
        case NIL:
            json = cJSON_CreateNull();
            break;
	}
	return json;
}

/**从cJSON结构体转化回来**/
BSData* BSData::fromJSON(const cJSON* json) {
	BSData* data;
	switch (json->type) {
	case cJSON_Number:
		//这里没有release，需要让调用的人release
		data =  new BSData(json->valuedouble);
		break;
	case cJSON_String:
		//这里没有release，需要让调用的人release
		data = new BSData(json->valuestring);
		break;
	case cJSON_True:
		//这里没有release，需要让调用的人release
		data = new BSData(true);
		break;
	case cJSON_False:
		//这里没有release，需要让调用的人release
		data = new BSData(false);
		break;
	case cJSON_Array:	
		//这里没有release，需要让调用的人release
		data = new BSArray();
		for(cJSON* item = json->child; item != NULL; item = item->next) {
			BSData* val = fromJSON(item);
			dynamic_cast<BSArray *>(data)->append(val);
			val->release(); //调用了fromJSON需要release一下，保持refCount为1
		}
		break;
	case cJSON_Object:
		data = new BSDict();
		for(cJSON* item = json->child; item != NULL; item = item->next) {
			BSData* val = fromJSON(item);
			dynamic_cast<BSDict*>(data)->append(item->string, val);
			val->release();//调用了fromJSON需要release一下，保持refCount为1
		}
		break;
    case cJSON_NULL:
    default:
            //这里没有release，需要让调用的人release
            data =  new BSNull();
            break;
	}
	return data;
}

std::string BSData::toString() const{
    //        BOOLEAN,
    //        NUM,
    //        STR,
    //        ARRAY,
    //        DICT,
    std::string ret_str = "";
    switch(_type){
        case STR:
            ret_str = _valStr;
            break;
        case NUM:
            ret_str = BSFormat("%d",_valInt);
            break;
        case ARRAY:
            ret_str = "[";
            if (_valArray && _valArray->count() > 0) {
                for(int i=0;i<_valArray->count();i++){
                    BSData *data = dynamic_cast<BSData *>(_valArray->objectAtIndex(i));
                    if (data) {
                        ret_str += data->toString();
                    } else {
                        ret_str += "NULL";
                    }
                    if (i < _valArray->count()-1) {
                        ret_str += ",";
                    }
                }
            }
            ret_str += "]";
            break;
        case DICT:
            ret_str = "this is dict";
            break;
        case BOOLEAN:
            ret_str += "";
            break;
        case NIL:
            ret_str += "NULL";
            break;
    }
    return ret_str;
}
const char* BSData::asString() const{
    if(_type != STR){
        CCLOG("this is BSData.asString():%d",_type);
        CCLOG("this is BSData.asSring() value=%s",toString().c_str());
        
    }
    CCAssert(_type == STR, "not String!"); return _valStr;}

unsigned int BSData::size() const{
    switch (_type) {
        case ARRAY:
            return _valArray->count();
        case DICT:
            return _valDict->count();
        case STR:
            return strlen(_valStr);
        default:
            return 0;
    }
}

#pragma mark -
#pragma mark BSDict
void BSDict::append(BSDict &pDict) {
    CCArray* keys = pDict.keys();
    CCObject* element;
    CCARRAY_FOREACH(keys, element) {
        const char* key = dynamic_cast<CCString*>(element)->getCString();
        this->append(key, &pDict[key]);
    }
    
}

#pragma mark -
#pragma mark Helpers

const char* BSDataDump(const BSData* obj) {
	cJSON* json = obj->toJSON();
	char* json_str = cJSON_Print(json);
	cJSON_Delete(json);
    CCString* str = CCString::create(json_str);
    delete [] json_str;
	return str->getCString();
}

bool BSDataDumpToFile(const string& pFile, const BSData* pObj, TEA* pEncrypter) {
    
    const char* content = BSDataDump(pObj);
    unsigned long dataSize = strlen(content);
    if (pEncrypter) {
        pEncrypter->SaveFile(pFile.c_str(), dataSize, content);
        return true;
        /*
        char* encrypt = new char[dataSize];
        memset(encrypt, 0, dataSize);
        int k = 0;
        int time = dataSize / 8;
        for (int i = 0; i < time; ++i)
        {
            pEncrypter->encrypt((const byte*)content + k, (byte*)encrypt + k);
            k+=8;
        }
        
        for (int i=k; i < dataSize; ++i) {
            encrypt[i] = content[i];
        }
        delete [] encrypt;
        return BSFileWrite(pFile.c_str(), encrypt, dataSize);*/
    }
    else {
        return BSFileWrite(pFile.c_str(), content, dataSize);
    }
}

BSData* BSDataLoad(const char* str) {
	cJSON* json = cJSON_Parse(str);
	BSData* data = json ? BSData::fromJSON(json) : NULL;
	if(json) cJSON_Delete(json);
	return data;
}

BSData* BSDataLoadFromFile(const string& pFile, TEA* pDecrypter) {
    unsigned long dataSize = 0;
    unsigned char* content = CCFileUtils::sharedFileUtils()->getFileData(pFile.c_str(), "r", &dataSize);
    if (content == NULL) {
        return NULL;
    }
    if (pDecrypter) {
        unsigned char* decrypt = new unsigned char[dataSize];
        memset(decrypt, 0, dataSize);
        int k = 0;
        int time = dataSize / 8;
        for (int i = 0; i < time; ++i)
        {
            pDecrypter->decrypt(content + k, decrypt + k);
            k+=8;
        }
        
        for (int i=k; i < dataSize; ++i) {
            decrypt[i] = content[i];
        }
        BSData* data = BSDataLoad(reinterpret_cast<char*>(decrypt));
        delete [] content;
        delete [] decrypt;
        return data;
    }
    else {
        BSData* data = BSDataLoad(reinterpret_cast<char*>(content));
        delete [] content;
        return data;
    }
}