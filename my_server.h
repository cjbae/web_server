#pragma once
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "Router.h"
#include "sslSession.h"
#include "httpSession.h"
#include <boost/asio/ssl.hpp>
#include <boost/property_tree/ptree.hpp> 
#include <boost/property_tree/ini_parser.hpp>
#include "json.hpp"
#include <filesystem>

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

using namespace boost::asio::ip;


class my_server
{
private:
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::acceptor acceptor_;

	Verifier verifier_;
	Router<std::string, luabridge::LuaRef> route_;
	RequestParser request_parser_;

	boost::asio::ssl::context context_;
	bool ssl_on;
	std::string cert_path;
	std::string key_path;
	boost::asio::io_context& io_context_;
	std::shared_ptr<Session> session_;
public:
	my_server(boost::asio::io_context& io_context, const int port);
	~my_server();

	void do_accept();
	void register_handle(const std::string& method, const std::string& location, const std::string& lua_file_name);

	std::string get_password();

	void file_register();
};


