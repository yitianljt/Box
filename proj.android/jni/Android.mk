LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/SpriteBlock.cpp \
                   ../../Classes/SpriteRunner.cpp \
                   ../../Classes/Common/BaseComScene.cpp \
                   ../../Classes/Common/ComSound.cpp \
                   ../../Classes/Common/CommonTool.cpp \
                   ../../Classes/Common/ControlBannerView.cpp \
                   ../../Classes/Common/GameControl.cpp \
                   ../../Classes/GameLaunch/SceneLaunch.cpp \
                   ../../Classes/GameLaunch/LayerLaunch.cpp \
                   ../../Classes/GameMain/CloudLayer.cpp \
                   ../../Classes/GameMain/LayerGame.cpp \
                   ../../Classes/GameMain/SceneGame.cpp \
                   ../../Classes/GameMain/ShowYouAd.cpp \
                   ../../Classes/GameResult/GameResult.cpp \
                   ../../Classes/GameResult/ResultLayer.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Common
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/GameLaunch
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/GameMain
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/GameResult
LOCAL_C_INCLUDES +=$(LOCAL_PATH)/../../cocos2d/extensions

 
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

$(call import-module,Box2D)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
$(call import-module,network)
$(call import-module,extensions)
