#pragma once

#include "Request.h"
#include "Router.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h" 
#include "lualib.h" 
}

#include "LuaBridge/LuaBridge.h"
#include "LuaBridge/RefCountedPtr.h"

#ifdef _WIN32
#pragma comment(lib, "lua53.lib")
#endif

struct Route;

class LuaManager
{
private:
	LuaManager();
	~LuaManager();
public:
	// singleton
	static LuaManager* Instance();

	luabridge::LuaRef RegisterHandler(const std::string& file_name);
	Route RegisterRouter(const std::string& filename);

	template <typename Req>
	auto Push(const Req& req)
	{
		luabridge::push(L_, req);
	}
private:
	void RegisterObjects();
private:
	lua_State* L_;
};

