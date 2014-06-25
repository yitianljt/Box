//
//  LayerLaunch.cpp
//  ShareTest
//
//  Created by jintao on 14-5-18.
//
//

#include "LayerLaunch.h"
#include "GameControl.h"
#include "cocos-ext.h"
#include "UILayout.h"
#include "CCSGUIReader.h"
#include "ShowYouAd.h"

USING_NS_CC;
USING_NS_CC_EXT;


COM_CREATE_FUNC_IMPL(LayerLaunch);


LayerLaunch::LayerLaunch()
{}
LayerLaunch::~LayerLaunch(){}

bool LayerLaunch::init()
{
    Size sizeWin = Director::getInstance()->getWinSize();
    if (!Layer::init()) {
        return false;
    }
    
    LayerColor* layerBg = CCLayerColor::create(Color4B(255, 255, 0, 0), sizeWin.width, sizeWin.height);
    addChild(layerBg,0);
    //MenuItemLabel* btnItem = CCMenuItemLabel::create(CCLabelTTF::create("开始游戏", "黑体", 40), this, menu_selector(LayerLaunch::callbackStart));
    MenuItemLabel* btnItem = MenuItemLabel::create(LabelTTF::create("开始游戏", "黑体", 40), [](Ref* sender){
        //ShowYouAd::shared()->showYouWallSpot();
        Director::getInstance()->replaceScene(GameControl::scene(kSceneGame));
                });
    

    
    Menu* menu = Menu::create(btnItem,NULL);
    menu->setPosition(Point(sizeWin.width/2,sizeWin.height/2));
    layerBg->addChild(menu, 1);
    
    
    /*
    cocos2d::ui::Layout* equipe_root =dynamic_cast<cocos2d::ui::Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ccs/NewUi01_1.json"));
    
*/
    

   // equipe_root->getChildByName("Button_4")->addTouchEventListener(this,cocos2d::ui::SEL_TouchEvent(Layer));
   // startBtn->addTouchEventListener(this,cocos2d::ui::SEL_TouchEvent(&MainScene::touchCallBack));

    
    
    return true;
}

void LayerLaunch::touchCallBack(CCObject *pSender, cocos2d::ui::TouchEventType type)
{
    CCLOG("touchEvent");
}

void LayerLaunch::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, bool transformUpdated)
{
/*
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    //检测是否有OpenGL错误发生，如果有则打印错误
    CHECK_GL_ERROR_DEBUG();
    
    //平滑模式，即高洛德着色
    //    glEnable(GL_LINE_SMOOTH);
    //绘制一条件,参1为起点，参2为终点，ccp为生成CCPoint的宏
    ccDrawLine( ccp(0, 0), ccp(s.width, s.height) );
    
    //检测是否有OpenGL错误发生，如果有则打印错误
    CHECK_GL_ERROR_DEBUG();
    
    //设置线宽
    glLineWidth( 5.0f );
    //设置后面要进行绘制时所用的色彩
    ccDrawColor4B(255,0,0,255);
    //绘制线条
    ccDrawLine( ccp(0, s.height), ccp(s.width, 0) );
 
 */

}

void LayerLaunch::onEnter()
{
    Layer::onEnter();
    
    auto box = Node::create();
    Vec2 points[4] = {Vec2(-100, -100), Vec2(-100, 100), Vec2(100, 100), Vec2(100, -100)};
    box->setPhysicsBody(PhysicsBody::createPolygon(points, 4));
    addChild(box);
    
    
}
void LayerLaunch::onExit()
{
    Layer::onExit();
}

void LayerLaunch::callbackStart(Ref* obj)
{
    CCLOG("callbackStart");
    Director::getInstance()->replaceScene(GameControl::scene(kSceneGame));
}




