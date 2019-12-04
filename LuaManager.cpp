#include "LuaManager.h"


LuaManager::LuaManager()
{
	L_ = luaL_newstate();
	luaL_openlibs(L_);

	RegisterObjects();
}

LuaManager::~LuaManager()
{
	lua_close(L_);
}

LuaManager* LuaManager::Instance()
{
	static LuaManager obj;
	return &obj;
}


luabridge::LuaRef LuaManager::RegisterHandler(const std::string& file_name)
{
	luaL_dofile(L_, file_name.c_str());
	luabridge::LuaRef v1 = luabridge::getGlobal(L_, "make_response_message");
	return v1;
}

Route LuaManager::RegisterRouter(const std::string& file_name)
{
	luaL_dofile(L_, file_name.c_str());
	luabridge::LuaRef v1 = luabridge::getGlobal(L_, "getRouteInfo");
	Route r;
	return v1(r);
}

void LuaManager::RegisterObjects()
{
	luabridge::getGlobalNamespace(L_)
		.beginClass<header>("header")
		.addData("key", &header::key)
		.addData("value", &header::value)
		.endClass();

	luabridge::getGlobalNamespace(L_)
		.beginClass<Request>("Request")
		.addConstructor<void(*)()>()
		.addData("method_", &Request::method_)
		.addData("version_", &Request::version_)
		.addData("uri_", &Request::uri_)
		.addData("body_", &Request::body_)
		.addData("headers_", &Request::headers_)
		.addFunction("getHeader", &Request::getHeader)
		.addFunction("header_size", &Request::header_size)
		.endClass();

	luabridge::getGlobalNamespace(L_)
		.beginClass<Route>("route")
		.addData("method", &Route::method)
		.addData("location", &Route::location)
		.endClass();
}