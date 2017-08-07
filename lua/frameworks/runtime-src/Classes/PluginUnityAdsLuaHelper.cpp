
#include "PluginUnityAdsLuaHelper.h"
#include "PluginUnityAds/PluginUnityAds.h"
#include "SDKBoxLuaHelper.h"

class UnityAdsListenerLua : public sdkbox::UnityAdsListener {
public:
    UnityAdsListenerLua(): mLuaHandler(0) {
    }

    ~UnityAdsListenerLua() {
        resetHandler();
    }

    void setHandler(int luaHandler) {
        if (mLuaHandler == luaHandler) {
            return;
        }
        resetHandler();
        mLuaHandler = luaHandler;
    }

    void resetHandler() {
        if (0 == mLuaHandler) {
            return;
        }

        LUAENGINE->removeScriptHandler(mLuaHandler);
        mLuaHandler = 0;
    }

    void unityAdsDidClick(const std::string& placementId) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("unityAdsDidClick")));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }

    void unityAdsPlacementStateChanged(const std::string& placementId,
                                       sdkbox::PluginUnityAds::SBUnityAdsPlacementState oldState,
                                       sdkbox::PluginUnityAds::SBUnityAdsPlacementState newState) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("unityAdsPlacementStateChanged")));
        dict.insert(std::make_pair("placementId", LuaValue::stringValue(placementId)));
        dict.insert(std::make_pair("oldState", LuaValue::intValue(oldState)));
        dict.insert(std::make_pair("newState", LuaValue::intValue(newState)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);

    }

    void unityAdsReady(const std::string& placementId) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("unityAdsReady")));
        dict.insert(std::make_pair("placementId", LuaValue::stringValue(placementId)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }

    void unityAdsDidError(sdkbox::PluginUnityAds::SBUnityAdsError error, const std::string& message) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("unityAdsDidError")));
        dict.insert(std::make_pair("error", LuaValue::intValue(error)));
        dict.insert(std::make_pair("message", LuaValue::stringValue(message)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }

    void unityAdsDidStart(const std::string& placementId) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("unityAdsDidStart")));
        dict.insert(std::make_pair("placementId", LuaValue::stringValue(placementId)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }

    void unityAdsDidFinish(const std::string& placementId, sdkbox::PluginUnityAds::SBUnityAdsFinishState state) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("unityAdsDidFinish")));
        dict.insert(std::make_pair("placementId", LuaValue::stringValue(placementId)));
        dict.insert(std::make_pair("state", LuaValue::intValue(state)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }


private:
    int mLuaHandler;
};

int lua_PluginUnityAdsLua_PluginUnityAds_setListener(lua_State* tolua_S) {
    int argc = 0;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginUnityAds",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2 , "LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        UnityAdsListenerLua* lis = static_cast<UnityAdsListenerLua*> (sdkbox::PluginUnityAds::getListener());
        if (NULL == lis) {
            lis = new UnityAdsListenerLua();
        }
        lis->setHandler(handler);
        sdkbox::PluginUnityAds::setListener(lis);

        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginUnityAds::setListener",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginUnityAdsLua_PluginUnityAds_setListener'.",&tolua_err);
#endif
    return 0;
}


static int lua_createTable(lua_State* L, const std::map<std::string, int>& map) {
    lua_newtable(L);

    std::map<std::string, int>::const_iterator it = map.begin();
    while (it != map.end()) {
        lua_pushstring(L, it->first.c_str());
        lua_pushinteger(L, it->second);
        lua_settable(L, -3);
        it++;
    }

    return 1;
}

static int lua_setTable(lua_State* L, int table, const std::string& name, const std::map<std::string, int>& map) {
    if (table < 0) {
        table = lua_gettop(L) + table + 1;
    }
    lua_pushstring(L, name.c_str());
    lua_createTable(L, map);
    lua_rawset(L, table);

    return 0;
}

int lua_PluginUnityAdsLua_constants(lua_State* L) {
    if (NULL == L) {
        return 0;
    }

    lua_pushstring(L, "sdkbox.PluginUnityAds");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1)) {

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
        lua_setTable(L, -1, "SBUnityAdsError", enums);

        enums.clear();
        enums.insert(std::make_pair("kUnityAdsFinishStateError", 0));
        enums.insert(std::make_pair("kUnityAdsFinishStateSkipped", 1));
        enums.insert(std::make_pair("kUnityAdsFinishStateCompleted", 2));
        lua_setTable(L, -1, "SBUnityAdsFinishState", enums);

        enums.clear();
        enums.insert(std::make_pair("kUnityAdsPlacementStateReady", 0));
        enums.insert(std::make_pair("kUnityAdsPlacementStateNotAvailable", 1));
        enums.insert(std::make_pair("kUnityAdsPlacementStateDisabled", 2));
        enums.insert(std::make_pair("kUnityAdsPlacementStateWaiting", 3));
        enums.insert(std::make_pair("kUnityAdsPlacementStateNoFill", 4));
        lua_setTable(L, -1, "SBUnityAdsPlacementState", enums);
    }
    lua_pop(L, 1);

    return 1;
}

int extern_PluginUnityAds(lua_State* L) {
    if (NULL == L) {
        return 0;
    }

    lua_pushstring(L, "sdkbox.PluginUnityAds");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1)) {
        tolua_function(L,"setListener", lua_PluginUnityAdsLua_PluginUnityAds_setListener);
    }
    lua_pop(L, 1);

    lua_PluginUnityAdsLua_constants(L);

    return 1;
}

TOLUA_API int register_all_PluginUnityAdsLua_helper(lua_State* L) {
    tolua_module(L,"sdkbox",0);
    tolua_beginmodule(L,"sdkbox");

    extern_PluginUnityAds(L);

    tolua_endmodule(L);
    return 1;
}
