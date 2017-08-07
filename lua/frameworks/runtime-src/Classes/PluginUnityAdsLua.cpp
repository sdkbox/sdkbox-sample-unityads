#include "PluginUnityAdsLua.hpp"
#include "PluginUnityAds/PluginUnityAds.h"
#include "SDKBoxLuaHelper.h"
#include "sdkbox/Sdkbox.h"



int lua_PluginUnityAdsLua_PluginUnityAds_isSupported(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginUnityAds",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginUnityAdsLua_PluginUnityAds_isSupported'", nullptr);
            return 0;
        }
        bool ret = sdkbox::PluginUnityAds::isSupported();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginUnityAds:isSupported",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginUnityAdsLua_PluginUnityAds_isSupported'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginUnityAdsLua_PluginUnityAds_isReady(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginUnityAds",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginUnityAds:isReady");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginUnityAdsLua_PluginUnityAds_isReady'", nullptr);
            return 0;
        }
        bool ret = sdkbox::PluginUnityAds::isReady(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginUnityAds:isReady",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginUnityAdsLua_PluginUnityAds_isReady'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginUnityAdsLua_PluginUnityAds_getPlacementState(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginUnityAds",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginUnityAds:getPlacementState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginUnityAdsLua_PluginUnityAds_getPlacementState'", nullptr);
            return 0;
        }
        int ret = (int)sdkbox::PluginUnityAds::getPlacementState(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginUnityAds:getPlacementState",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginUnityAdsLua_PluginUnityAds_getPlacementState'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginUnityAdsLua_PluginUnityAds_show(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginUnityAds",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginUnityAds:show");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginUnityAdsLua_PluginUnityAds_show'", nullptr);
            return 0;
        }
        sdkbox::PluginUnityAds::show(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginUnityAds:show",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginUnityAdsLua_PluginUnityAds_show'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginUnityAdsLua_PluginUnityAds_init(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginUnityAds",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginUnityAdsLua_PluginUnityAds_init'", nullptr);
            return 0;
        }
        bool ret = sdkbox::PluginUnityAds::init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginUnityAds:init",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginUnityAdsLua_PluginUnityAds_init'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginUnityAdsLua_PluginUnityAds_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PluginUnityAds)");
    return 0;
}

int lua_register_PluginUnityAdsLua_PluginUnityAds(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.PluginUnityAds");
    tolua_cclass(tolua_S,"PluginUnityAds","sdkbox.PluginUnityAds","",nullptr);

    tolua_beginmodule(tolua_S,"PluginUnityAds");
        tolua_function(tolua_S,"isSupported", lua_PluginUnityAdsLua_PluginUnityAds_isSupported);
        tolua_function(tolua_S,"isReady", lua_PluginUnityAdsLua_PluginUnityAds_isReady);
        tolua_function(tolua_S,"getPlacementState", lua_PluginUnityAdsLua_PluginUnityAds_getPlacementState);
        tolua_function(tolua_S,"show", lua_PluginUnityAdsLua_PluginUnityAds_show);
        tolua_function(tolua_S,"init", lua_PluginUnityAdsLua_PluginUnityAds_init);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::PluginUnityAds).name();
    g_luaType[typeName] = "sdkbox.PluginUnityAds";
    g_typeCast["PluginUnityAds"] = "sdkbox.PluginUnityAds";
    return 1;
}
TOLUA_API int register_all_PluginUnityAdsLua(lua_State* tolua_S)
{
	tolua_open(tolua_S);

	std::stringstream ss("sdkbox");
    std::vector<std::string> nsvec;
    std::string item;
    while (std::getline(ss, item, '.')) {
        nsvec.push_back(item);
    }
    int nsLen = nsvec.size();
    item = nsvec.front();
    nsvec.erase(nsvec.begin());

    tolua_module(tolua_S, item.c_str(), 0);
    tolua_beginmodule(tolua_S, item.c_str());

    while (nsvec.size() > 0) {
        item = nsvec.front();
        nsvec.erase(nsvec.begin());
        lua_pushstring(tolua_S, item.c_str()); // m name
        lua_rawget(tolua_S, -2);             // m value
        if (!lua_istable(tolua_S, -1)) {
            lua_pop(tolua_S, 1);             // m
            lua_newtable(tolua_S);           // m t
            lua_pushstring(tolua_S, item.c_str()); // m t name
            lua_pushvalue(tolua_S, -2);      // m t name t
            lua_rawset(tolua_S, -4);         // m t
        }
    }

	lua_register_PluginUnityAdsLua_PluginUnityAds(tolua_S);

	if (nsLen > 1) {
        lua_pop(tolua_S, nsLen - 1); // m
    }
	tolua_endmodule(tolua_S);

	sdkbox::setProjectType("lua");
	return 1;
}

