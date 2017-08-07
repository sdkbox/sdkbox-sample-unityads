#include "PluginUnityAdsJS.hpp"
#include "PluginUnityAds/PluginUnityAds.h"
#include "SDKBoxJSHelper.h"
#include "sdkbox/Sdkbox.h"


#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 52
#elif MOZJS_MAJOR_VERSION >= 33
template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS_ReportErrorUTF8(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}
#else
template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        JS_AddObjectRoot(cx, &pp->obj);
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    vp.set(BOOLEAN_TO_JSVAL(true));
    return true;
}
#endif
#elif defined(JS_VERSION)
template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    TypeTest<T> t;
    T* cobj = new T();
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    assert(p);
    JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
    js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));

    return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return JS_FALSE;
}
#endif
JSClass  *jsb_sdkbox_PluginUnityAds_class;
#if MOZJS_MAJOR_VERSION < 33
JSObject *jsb_sdkbox_PluginUnityAds_prototype;
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginUnityAdsJS_PluginUnityAds_isSupported(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        bool ret = sdkbox::PluginUnityAds::isSupported();
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginUnityAdsJS_PluginUnityAds_isSupported : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginUnityAdsJS_PluginUnityAds_isSupported(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        bool ret = sdkbox::PluginUnityAds::isSupported();
        jsval jsret;
        jsret = JS::BooleanValue(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginUnityAdsJS_PluginUnityAds_isReady(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginUnityAdsJS_PluginUnityAds_isReady : Error processing arguments");
        bool ret = sdkbox::PluginUnityAds::isReady(arg0);
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginUnityAdsJS_PluginUnityAds_isReady : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginUnityAdsJS_PluginUnityAds_isReady(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        bool ret = sdkbox::PluginUnityAds::isReady(arg0);
        jsval jsret;
        jsret = JS::BooleanValue(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginUnityAdsJS_PluginUnityAds_getPlacementState(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginUnityAdsJS_PluginUnityAds_getPlacementState : Error processing arguments");
        int ret = (int)sdkbox::PluginUnityAds::getPlacementState(arg0);
        JS::RootedValue jsret(cx);
        jsret = JS::Int32Value(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginUnityAdsJS_PluginUnityAds_getPlacementState : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginUnityAdsJS_PluginUnityAds_getPlacementState(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginUnityAds::SBUnityAdsPlacementState ret = sdkbox::PluginUnityAds::getPlacementState(arg0);
        jsval jsret;
        jsret = JS::Int32Value(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginUnityAdsJS_PluginUnityAds_show(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_PluginUnityAdsJS_PluginUnityAds_show : Error processing arguments");
        sdkbox::PluginUnityAds::show(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginUnityAdsJS_PluginUnityAds_show : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginUnityAdsJS_PluginUnityAds_show(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        sdkbox::PluginUnityAds::show(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginUnityAdsJS_PluginUnityAds_init(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        bool ret = sdkbox::PluginUnityAds::init();
        JS::RootedValue jsret(cx);
        jsret = JS::BooleanValue(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginUnityAdsJS_PluginUnityAds_init : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginUnityAdsJS_PluginUnityAds_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        bool ret = sdkbox::PluginUnityAds::init();
        jsval jsret;
        jsret = JS::BooleanValue(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


void js_PluginUnityAdsJS_PluginUnityAds_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginUnityAds)", obj);
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginUnityAdsJS_PluginUnityAds(JSContext *cx, JS::HandleObject global) {
    static JSClass PluginAgeCheq_class = {
        "PluginUnityAds",
        JSCLASS_HAS_PRIVATE,
        nullptr
    };
    jsb_sdkbox_PluginUnityAds_class = &PluginAgeCheq_class;

#if MOZJS_MAJOR_VERSION < 52
    jsb_sdkbox_PluginUnityAds_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_PluginUnityAds_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_PluginUnityAds_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_PluginUnityAds_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_PluginUnityAds_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_PluginUnityAds_class->resolve = JS_ResolveStub;
    jsb_sdkbox_PluginUnityAds_class->convert = JS_ConvertStub;
    jsb_sdkbox_PluginUnityAds_class->finalize = js_PluginUnityAdsJS_PluginUnityAds_finalize;
    jsb_sdkbox_PluginUnityAds_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
#endif

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("isSupported", js_PluginUnityAdsJS_PluginUnityAds_isSupported, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isReady", js_PluginUnityAdsJS_PluginUnityAds_isReady, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPlacementState", js_PluginUnityAdsJS_PluginUnityAds_getPlacementState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("show", js_PluginUnityAdsJS_PluginUnityAds_show, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_PluginUnityAdsJS_PluginUnityAds_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, nullptr);
    JSObject* objProto = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_sdkbox_PluginUnityAds_class,
        dummy_constructor<sdkbox::PluginUnityAds>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, objProto);
#if (SDKBOX_COCOS_JSB_VERSION >= 2)
#if MOZJS_MAJOR_VERSION >= 52
    jsb_register_class<sdkbox::PluginUnityAds>(cx, jsb_sdkbox_PluginUnityAds_class, proto);
#else
    jsb_register_class<sdkbox::PluginUnityAds>(cx, jsb_sdkbox_PluginUnityAds_class, proto, JS::NullPtr());
#endif
#else
    TypeTest<sdkbox::PluginUnityAds> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_PluginUnityAds_class;
        p->proto = objProto;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
#endif

    // add the proto and JSClass to the type->js info hash table
    JS::RootedValue className(cx);
    JSString* jsstr = JS_NewStringCopyZ(cx, "PluginUnityAds");
    className = JS::StringValue(jsstr);
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
}
#else
void js_register_PluginUnityAdsJS_PluginUnityAds(JSContext *cx, JSObject *global) {
    jsb_sdkbox_PluginUnityAds_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_PluginUnityAds_class->name = "PluginUnityAds";
    jsb_sdkbox_PluginUnityAds_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_PluginUnityAds_class->delProperty = JS_DeletePropertyStub;
    jsb_sdkbox_PluginUnityAds_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_PluginUnityAds_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_PluginUnityAds_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_PluginUnityAds_class->resolve = JS_ResolveStub;
    jsb_sdkbox_PluginUnityAds_class->convert = JS_ConvertStub;
    jsb_sdkbox_PluginUnityAds_class->finalize = js_PluginUnityAdsJS_PluginUnityAds_finalize;
    jsb_sdkbox_PluginUnityAds_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("isSupported", js_PluginUnityAdsJS_PluginUnityAds_isSupported, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isReady", js_PluginUnityAdsJS_PluginUnityAds_isReady, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPlacementState", js_PluginUnityAdsJS_PluginUnityAds_getPlacementState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("show", js_PluginUnityAdsJS_PluginUnityAds_show, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_PluginUnityAdsJS_PluginUnityAds_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_PluginUnityAds_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_PluginUnityAds_class,
        dummy_constructor<sdkbox::PluginUnityAds>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27
//  JS_SetPropertyAttributes(cx, global, "PluginUnityAds", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::PluginUnityAds> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_sdkbox_PluginUnityAds_class;
        p->proto = jsb_sdkbox_PluginUnityAds_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}
#endif
#elif defined(JS_VERSION)
void js_register_PluginUnityAdsJS_PluginUnityAds(JSContext *cx, JSObject *global) {
    jsb_sdkbox_PluginUnityAds_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_sdkbox_PluginUnityAds_class->name = "PluginUnityAds";
    jsb_sdkbox_PluginUnityAds_class->addProperty = JS_PropertyStub;
    jsb_sdkbox_PluginUnityAds_class->delProperty = JS_PropertyStub;
    jsb_sdkbox_PluginUnityAds_class->getProperty = JS_PropertyStub;
    jsb_sdkbox_PluginUnityAds_class->setProperty = JS_StrictPropertyStub;
    jsb_sdkbox_PluginUnityAds_class->enumerate = JS_EnumerateStub;
    jsb_sdkbox_PluginUnityAds_class->resolve = JS_ResolveStub;
    jsb_sdkbox_PluginUnityAds_class->convert = JS_ConvertStub;
    jsb_sdkbox_PluginUnityAds_class->finalize = js_PluginUnityAdsJS_PluginUnityAds_finalize;
    jsb_sdkbox_PluginUnityAds_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    JSPropertySpec *properties = NULL;

    JSFunctionSpec *funcs = NULL;

    static JSFunctionSpec st_funcs[] = {
        JS_FN("isSupported", js_PluginUnityAdsJS_PluginUnityAds_isSupported, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isReady", js_PluginUnityAdsJS_PluginUnityAds_isReady, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPlacementState", js_PluginUnityAdsJS_PluginUnityAds_getPlacementState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("show", js_PluginUnityAdsJS_PluginUnityAds_show, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_PluginUnityAdsJS_PluginUnityAds_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_sdkbox_PluginUnityAds_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_sdkbox_PluginUnityAds_class,
        dummy_constructor<sdkbox::PluginUnityAds>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "PluginUnityAds", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<sdkbox::PluginUnityAds> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_sdkbox_PluginUnityAds_class;
        p->proto = jsb_sdkbox_PluginUnityAds_prototype;
        p->parentProto = NULL;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}
#endif
#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginUnityAdsJS(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "sdkbox", &ns);

    js_register_PluginUnityAdsJS_PluginUnityAds(cx, ns);

    sdkbox::setProjectType("js");
}
#else
void register_all_PluginUnityAdsJS(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, obj, "sdkbox", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "sdkbox", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_PluginUnityAdsJS_PluginUnityAds(cx, obj);

    sdkbox::setProjectType("js");
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginUnityAdsJS(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    jsval nsval;
    JSObject *ns;
    JS_GetProperty(cx, obj, "sdkbox", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "sdkbox", &nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_PluginUnityAdsJS_PluginUnityAds(cx, obj);

    sdkbox::setProjectType("js");
}
#endif