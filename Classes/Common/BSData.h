#ifndef __SAT_BSData_H__
#define __SAT_BSData_H__
#include <vector>
#include <map>
#include <stdarg.h>
#include "cJSON.h"
#include <string>
#include "cocoa/CCObject.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCArray.h"
#include "cocos2d.h"
#include "tea.h"

using namespace std;
using namespace cocos2d;

#define SATEND 0xffffffff//TODO:在64位机器上运行可能有问题


/**
 希望这个BSData在用于构建jsonrpc时，能实现如下使用方法：
 JSONRPC* jsonrpc = new jsonrpc("http://xxxxxx");
 BSDict* params = new BSDict();
 params["x"] = 1;
 params["y"] = "I am a string";
 params["d"] = BSArray("test", "test", "test", BSNull());
 
 BSData是采用cocos2d-x的内存管理机制
 
 **/
enum ValType{
    BOOLEAN,
    NUM,
    STR,
    ARRAY,
    DICT,
    NIL
}; 

class CC_DLL BSData : public cocos2d::CCObject {
public:
	CCArray* _valArray;
	CCDictionary* _valDict;
	int _valInt; //有数据，当BOOL和NUM时
	double _valDouble; //有数据，当NUM时
	char* _valStr;
public:
	ValType _type;
protected:
	/**默认构造器不允许外部调用**/
    BSData();
	void init();
public:
	/**各种构造器**/
	BSData(bool pData);
    BSData(unsigned int pData);
	BSData(int pData);
	BSData(double pData);
	BSData(const char* pData);
	BSData(string pData);
	BSData(vector<int>& pData);
    /**拷贝构造**/
	BSData(const BSData& pTarget);
	/**析构函数**/
	~BSData();
	/**访问运算符**/
    bool has(const string & key) const;
	BSData& operator[] (unsigned int i);
	const BSData& operator[] (unsigned int i) const;
	BSData& operator[] (const string& key);
	const BSData& operator[] (const string& key) const;
    bool find(const string& key) const;
    /**赋值运算符**/
    BSData& operator=(const BSData& pTarget);

    CCObject* copyWithZone(cocos2d::CCZone *pZone);
    CCArray* keys() const;
public:
	/** 生成对应的cJSON结构体 **/
	cJSON* toJSON() const;
	static BSData* fromJSON(const cJSON* json);
public:
	bool isNULL() const {return _type == NIL;}
    bool asBool() const {CCAssert(_type == BOOLEAN, "not Boolean"); return _valInt;};
	int asInt() const {CCAssert(_type == NUM, "not Number!"); return _valInt;}
    unsigned int asUInt() const {CCAssert(_type == NUM, "not Number!"); return static_cast<unsigned int>(_valInt);}
	double asDouble() const {CCAssert(_type == NUM, "not Number!"); return _valDouble;}
    double asFloat() const {CCAssert(_type == NUM, "not Number!"); return static_cast<float>(_valDouble);}
    char* asNewString() const{ CCAssert(_type == STR, "not String!"); char* str = new char[strlen(_valStr) + 1]; strcpy(str, _valStr); return str;}
    std::string toString() const;
    const char* asString() const;
    unsigned int size() const;
    ValType type() const {return _type;};
    
};

class BSDict : public BSData {
public:
	BSDict(){
		_type = DICT;
		_valDict = new CCDictionary();
	}
    BSDict(const BSData& pData) : BSData(pData){}
	void append(const string& key, BSData* val) {
		_valDict->setObject(val, key);
	}
    void append(BSDict& pDict);
};

class BSArray : public BSData {
public:
	BSArray() {
		_type = ARRAY;
		_valArray = new CCArray();
	}
    BSArray(const BSData& pData) : BSData(pData){}
	void append(BSData* pObj) {
		_valArray->addObject(pObj);
	}
};

class BSNull : public BSData {
public:
	BSNull() {
		_type = NIL;
	}
};

const char*  BSDataDump(const BSData* pObj);
bool BSDataDumpToFile(const string& pFile, const BSData* pObj, TEA* pDecrypter);
BSData* BSDataLoad(const char* str);
BSData* BSDataLoadFromFile(const string& pFile, TEA* pDecrypter = NULL);
#endif