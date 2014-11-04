LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../Source/libs/cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../Source/libs/cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../Source/libs/cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Source/Game/AppDelegate.cpp \
                   ../../../Source/Game/Command/CommandDirector.cpp \
                   ../../../Source/Game/Gameplay/Behaviour/Behaviour.cpp \
                   ../../../Source/Game/Gameplay/Behaviour/DestroyBehaviour.cpp \
                   ../../../Source/Game/Gameplay/Behaviour/DestroyBehaviourFunctions.cpp \
                   ../../../Source/Game/Gameplay/Behaviour/MovementBehaviours.cpp \
                   ../../../Source/Game/Gameplay/Component/BehaviourComponent.cpp \
                   ../../../Source/Game/Gameplay/Component/Component.cpp \
                   ../../../Source/Game/Gameplay/Component/ComponentModifiers.cpp \
                   ../../../Source/Game/Gameplay/Component/GamepadComponent.cpp \
                   ../../../Source/Game/Gameplay/Component/MovementStateComponents.cpp \
                   ../../../Source/Game/Gameplay/Component/PositionComponent.cpp \
                   ../../../Source/Game/Gameplay/Component/TimeComponent.cpp \
                   ../../../Source/Game/Gameplay/Component/ViewComponent.cpp \
                   ../../../Source/Game/Gameplay/Component/ViewOpacityMaskComponent.cpp \
                   ../../../Source/Game/Gameplay/Component/WeaponComponent.cpp \
                   ../../../Source/Game/Gameplay/Gamepad.cpp \
                   ../../../Source/Game/Gameplay/Map.cpp \
                   ../../../Source/Game/Gameplay/MapObject.cpp \
                   ../../../Source/Game/Gameplay/ObjectsFastFactory.cpp \
                   ../../../Source/Game/Gameplay/Player.cpp \
                   ../../../Source/Game/Gameplay/View/MapView.cpp \
                   ../../../Source/Game/Gameplay/View/StarsView.cpp \
                   ../../../Source/Game/Screens/GameScreen.cpp \
                   ../../../Source/Game/Screens/MenuScreen.cpp \
                   ../../../Source/MelonGames/Services/FilesService.cpp \
                   ../../../Source/MelonGames/Services/Service.cpp \
                   ../../../Source/MelonGames/Services/ServicesManager.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Source \
                    $(LOCAL_PATH)/../../../Source/Game \

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
