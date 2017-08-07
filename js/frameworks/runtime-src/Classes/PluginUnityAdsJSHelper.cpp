#include "PluginUnityAdsJSHelper.h"
#include "PluginUnityAds/PluginUnityAds.h"
#include "SDKBoxJSHelper.h"

static JSContext* s_cx = nullptr;

#if (COCOS2D_VERSION < 0x00030000)
#define Ref CCObject
#define Director CCDirector
#define getInstance sharedDirector
#define schedule scheduleSelector
#endif

class UnityAdsCallbackJS: public cocos2d::Ref {
public:
    UnityAdsCallbackJS();
    void schedule();
    void notityJs(float dt);
    void transParams(JSContext* cx);

    std::string _name;

    JS::Value _paramVal[3];
    int _paramLen;

    std::string _placementid;
    std::string _message;
    sdkbox::PluginUnityAds::SBUnityAdsError _error;
    sdkbox::PluginUnityAds::SBUnityAdsFinishState _finishState;
    sdkbox::PluginUnityAds::SBUnityAdsPlacementState _oldPlacementState;
    sdkbox::PluginUnityAds::SBUnityAdsPlacementState _newPlacementState;
};

class UnityAdsListenerJS : public sdkbox::UnityAdsListener, public sdkbox::JSListenerBase
{
public:
    UnityAdsListenerJS():sdkbox::JSListenerBase() {
    }

    void unityAdsDidClick(const std::string& placementId) {
        UnityAdsCallbackJS* cb = new UnityAdsCallbackJS();
        cb->_name = "unityAdsDidClick";
        cb->_placementid = placementId;
        cb->schedule();
    }

    void unityAdsPlacementStateChanged(const std::string& placementId,
                                       sdkbox::PluginUnityAds::SBUnityAdsPlacementState oldState,
                                       sdkbox::PluginUnityAds::SBUnityAdsPlacementState newState) {
        UnityAdsCallbackJS* cb = new UnityAdsCallbackJS();
        cb->_name = "unityAdsPlacementStateChanged";
        cb->_placementid = placementId;
        cb->_oldPlacementState = oldState;
        cb->_newPlacementState = newState;
        cb->schedule();
    }

    void unityAdsReady(const std::string& placementId) {
        UnityAdsCallbackJS* cb = new UnityAdsCallbackJS();
        cb->_name = "unityAdsReady";
        cb->_placementid = placementId;
        cb->schedule();
    }

    void unityAdsDidError(sdkbox::PluginUnityAds::SBUnityAdsError error,
                          const std::string& message) {
        UnityAdsCallbackJS* cb = new UnityAdsCallbackJS();
        cb->_name = "unityAdsDidError";
        cb->_error = error;
        cb->_message = message;
        cb->schedule();
    }

    void unityAdsDidStart(const std::string& placementId) {
        UnityAdsCallbackJS* cb = new UnityAdsCallbackJS();
        cb->_name = "unityAdsDidStart";
        cb->_placementid = placementId;
        cb->schedule();
    }

    void unityAdsDidFinish(const std::string& placementId,
                           sdkbox::PluginUnityAds::SBUnityAdsFinishState state) {
        UnityAdsCallbackJS* cb = new UnityAdsCallbackJS();
        cb->_name = "unityAdsDidFinish";
        cb->_placementid = placementId;
        cb->_finishState = state;
        cb->schedule();
    }

    void invokeJS(const char* func, UnityAdsCallbackJS* cb) {
        if (!s_cx) {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = func;
        JS::RootedObject obj(cx, getJSDelegate());
        JSAutoCompartment ac(cx, obj);

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue func_handle(cx);
#else
        bool hasAction;
        jsval retval;
        JS::RootedValue func_handle(cx);
#endif
#elif defined(JS_VERSION)
        JSBool hasAction;
        jsval retval;
        jsval func_handle;
#endif

        cb->transParams(cx);
        JS::Value* pVals = cb->_paramVal;
        int valueSize = cb->_paramLen;

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JS::NullValue()) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            if (0 == valueSize) {
                JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::empty(), &retval);
            } else {
                JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(valueSize, pVals), &retval);
            }
#else
            if (0 == valueSize) {
                JS_CallFunctionName(cx, obj, func_name, 0, nullptr, &retval);
            } else {
                JS_CallFunctionName(cx, obj, func_name, valueSize, pVals, &retval);
            }
#endif
        }
    }

};


UnityAdsCallbackJS::UnityAdsCallbackJS():
_paramLen(0) {
}

void UnityAdsCallbackJS::schedule() {
    retain();
    cocos2d::Director::getInstance()->getScheduler()->schedule(schedule_selector(UnityAdsCallbackJS::notityJs), this, 0.1, 0, 0.0f, false);
    autorelease();
}

void UnityAdsCallbackJS::notityJs(float dt) {
    sdkbox::UnityAdsListener* lis = sdkbox::PluginUnityAds::getListener();
    UnityAdsListenerJS* l = dynamic_cast<UnityAdsListenerJS*>(lis);
    if (l) {
        l->invokeJS(_name.c_str(), this);
    }
    release();
}

void UnityAdsCallbackJS::transParams(JSContext* cx) {
    if (0 == _name.compare("unityAdsDidClick")
        || 0 == _name.compare("unityAdsReady")
        || 0 == _name.compare("unityAdsDidStart")) {
        _paramVal[0] = SB_STR_TO_JSVAL(cx, _placementid);
        _paramLen = 1;
    } else if (0 == _name.compare("unityAdsPlacementStateChanged")) {
        _paramVal[0] = SB_STR_TO_JSVAL(cx, _placementid);
        _paramVal[1] = JS::Int32Value(_oldPlacementState);
        _paramVal[2] = JS::Int32Value(_newPlacementState);
        _paramLen = 3;
    } else if (0 == _name.compare("unityAdsDidError")) {
        _paramVal[0] = JS::Int32Value(_error);
        _paramVal[1] = SB_STR_TO_JSVAL(cx, _message);
        _paramLen = 2;
    } else if (0 == _name.compare("unityAdsDidFinish")) {
        _paramVal[0] = SB_STR_TO_JSVAL(cx, _placementid);
        _paramVal[1] = JS::Int32Value(_finishState);
        _paramLen = 2;
    } else {
        _paramLen = 0;
    }
}


#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
bool js_PluginUnityAdsJS_PluginUnityAds_setListener(JSContext *cx, uint32_t argc, JS::Value *vp)
#else
bool js_PluginUnityAdsJS_PluginUnityAds_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
#elif defined(JS_VERSION)
JSBool js_PluginUnityAdsJS_PluginUnityAds_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
{
    s_cx = cx;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    if (argc == 1) {
        if (!args.get(0).isObject()){
            ok = false;
        }

        JSB_PRECONDITION2(ok, cx, false, "js_PluginUnityAdsJS_PluginUnityAds_setListener : Error processing arguments");
        UnityAdsListenerJS* wrapper = new UnityAdsListenerJS();
        wrapper->setJSDelegate(cx, args.get(0));
        sdkbox::PluginUnityAds::setListener(wrapper);

        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginUnityAdsJS_PluginUnityAds_setListener : wrong number of arguments");
    return false;
}

#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
void unityads_set_constants(JSContext* cx, const JS::RootedObject& obj, const std::string& name, const std::map<std::string, int>& params)
#else
void unityads_set_constants(JSContext* cx, JSObject* obj, const std::string& name, const std::map<std::string, int>& params)
#endif
{
    JS::RootedValue val(cx);
    sdkbox::std_map_string_int_to_jsval(cx, params, &val);

    JS::RootedValue rv(cx);
    rv = val;
#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
    JS_SetProperty(cx, obj, name.c_str(), rv);
#else
    JS_SetProperty(cx, obj, name.c_str(), rv.address());
#endif
}

#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
void unityads_register_constants(JSContext* cx, const JS::RootedObject& obj)
#else
void unityads_register_constants(JSContext* cx, JSObject* obj)
#endif
{
    std::map<std::string, int> enums;
    enums.clear();
    enums.insert(std::make_pair("kUnityAdsErrorNotInitialized", 0));
    enums.insert(std::make_pair("kUnityAdsErrorInitializedFailed", 1));
    enums.insert(std::make_pair("kUnityAdsErrorInvalidArgument", 2));
    enums.insert(std::make_pair("kUnityAdsErrorVideoPlayerError", 3));
    enums.insert(std::make_pair("kUnityAdsErrorInitSanityCheckFail", 4));
    enums.insert(std::make_pair("kUnityAdsErrorAdBlockerDetected", 5));
    enums.insert(std::make_pair("kUnityAdsErrorFileIoError", 6));
    enums.insert(std::make_pair("kUnityAdsErrorDeviceIdError", 7));
    enums.insert(std::make_pair("kUnityAdsErrorShowError", 8));
    enums.insert(std::make_pair("kUnityAdsErrorInternalError", 9));
    unityads_set_constants(cx, obj, "SBUnityAdsError", enums);

    enums.clear();
    enums.insert(std::make_pair("kUnityAdsFinishStateError", 0));
    enums.insert(std::make_pair("kUnityAdsFinishStateSkipped", 1));
    enums.insert(std::make_pair("kUnityAdsFinishStateCompleted", 2));
    unityads_set_constants(cx, obj, "SBUnityAdsFinishState", enums);

    enums.clear();
    enums.insert(std::make_pair("kUnityAdsPlacementStateReady", 0));
    enums.insert(std::make_pair("kUnityAdsPlacementStateNotAvailable", 1));
    enums.insert(std::make_pair("kUnityAdsPlacementStateDisabled", 2));
    enums.insert(std::make_pair("kUnityAdsPlacementStateWaiting", 3));
    enums.insert(std::make_pair("kUnityAdsPlacementStateNoFill", 4));
    unityads_set_constants(cx, obj, "SBUnityAdsPlacementState", enums);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginUnityAdsJS_helper(JSContext* cx, JS::HandleObject global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, global, "sdkbox.PluginUnityAds", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginUnityAdsJS_PluginUnityAds_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    unityads_register_constants(cx, pluginObj);
}
#else
void register_all_PluginUnityAdsJS_helper(JSContext* cx, JSObject* global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, JS::RootedObject(cx, global), "sdkbox.PluginUnityAds", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginUnityAdsJS_PluginUnityAds_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    unityads_register_constants(cx, pluginObj);
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginUnityAdsJS_helper(JSContext* cx, JSObject* global) {
    jsval pluginVal;
    JSObject* pluginObj;
    pluginVal = sdkbox::getJsObjOrCreat(cx, global, "sdkbox.PluginUnityAds", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginUnityAdsJS_PluginUnityAds_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    unityads_register_constants(cx, pluginObj);
}
#endif
