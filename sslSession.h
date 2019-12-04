#pragma once
#include "Session.h"
#include <boost/asio/ssl.hpp>

/*class sslSession : protected Session, public std::enable_shared_from_this<sslSession>
{
public:

private:
	boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
public:
	sslSession(boost::asio::ip::tcp::socket socket, boost::asio::ssl::context& context, Router<std::string, luabridge::LuaRef>& router, Verifier& verifer, RequestParser& request_parser);

	virtual void start();

	virtual ~sslSession();

	virtual void do_write_my(const std::string& message);

	virtual void do_read();

	void do_handshake();
};*/