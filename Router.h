#pragma once
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include "LuaManager.h"
using namespace std;

struct Route
{
	std::string method;
	std::string location;
};

template<class LocationT, class LuaFuncT>
class Router
{
public:
	typedef vector<std::pair<LocationT, LuaFuncT>> RouteVec;

private:
	RouteVec route_get_;
	RouteVec route_post_;

public:
	Router() = default;
	~Router() {}

	std::string handle(const Request& request)
	{
		//lua_.to_lua();
		LuaManager::Instance()->Push(request);

		std::string result = "";
		LuaFuncT* func = NULL;
		if (Find(request.method_, request.uri_, func))
		{
			result = (*func)(request).tostring();

			return result;
		}
		return result;
	}

	bool get(const LocationT& location, const LuaFuncT& lua_func)
	{
		auto iter = find_if(route_get_.begin(), route_get_.end(), [location](std::pair<LocationT, LuaFuncT>& data) {
			if (data.first == location) return true;
			else return false;
			});

		if (iter == route_get_.end())
		{
			route_get_.push_back(std::make_pair(location, lua_func));
			return true;
		}
		return false;
	}

	bool post(const LocationT& location, const LuaFuncT& lua_func)
	{
		auto iter = find_if(route_post_.begin(), route_post_.end(), [location](std::pair<LocationT, LuaFuncT>& data) {
			if (data.first == location) return true;
			else return false;
			});

		if (iter == route_post_.end())
		{
			route_post_.push_back(std::make_pair(location, lua_func));
			return true;
		}
		return false;
	}

	std::string do_func(const std::string& method, const LocationT& location)
	{
		std::string result = "";
		LuaFuncT* func = NULL;
		if (Find(method, location, func))
		{
			//(*func)();
			result = (*func)().tostring();

			return result;
		}
		return result;
	}

	bool Find(const string& method, const LocationT& location, LuaFuncT*& func)
	{
		RouteVec* route_; // 임시로 지정
		if (method == "GET")
		{
			route_ = &route_get_;
		}
		else if (method == "POST")
		{
			route_ = &route_post_;
		}
		else
		{
			return false;
		}
		auto iter = find_if(route_->begin(), route_->end(), [location](std::pair<LocationT, LuaFuncT>& data) {
			if (data.first == location) return true;
			else return false;
			});

		if (iter != route_->end())
		{
			func = &((*iter).second);
			return true;
		}
		return false;
	}
};