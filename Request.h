#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

// 클라이언트 request 담는다.

struct header
{
	std::string key;
	std::string value;
	header(std::string& k, std::string& v) : key(k), value(v) {}
};

class Request
{
public:
	std::string method_;
	std::string version_;
	std::string uri_;
	std::string body_;
	/*
		std::string test_uri_;

		std::string test_submit_uri_;
		std::string test_file_name_;

		std::string file_body_;

		std::string final_mime_type_;


		std::vector<std::string> mime_type_;

		std::string final_encoding_type_;
		std::vector<std::string> encoding_type_;

		std::string final_language_;
		std::vector<std::string> language_;*/

	std::vector<header> headers_;

	Request()
	{
	}
	~Request()
	{
	}

	header getHeader(int index) const
	{
		return headers_[index];
	}

	size_t header_size() const
	{
		return headers_.size();
	}

	// 예시로 하나만 주석
	//int to_lua_mime(lua_State* L)
	//{
	//	lua_createtable(L, mime_type_.size(), 0);
	//	int newTable = lua_gettop(L);
	//	int index = 1;
	//	std::vector<std::string>::const_iterator iter = mime_type_.begin();
	//	while (iter != mime_type_.end()) {
	//		lua_pushstring(L, (*iter).c_str());
	//		lua_rawseti(L, newTable, index);
	//		++iter;
	//		++index;
	//	}
	//	return 1;
	//}
};