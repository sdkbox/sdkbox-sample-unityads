#ifndef __PluginUnityAdsJS_h__
#define __PluginUnityAdsJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginUnityAdsJS_PluginUnityAds(JSContext *cx, JS::HandleObject global);
void register_all_PluginUnityAdsJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginUnityAdsJS_PluginUnityAds(JSContext *cx, JSObject* global);
void register_all_PluginUnityAdsJS(JSContext* cx, JSObject* obj);
#endif
#endif

