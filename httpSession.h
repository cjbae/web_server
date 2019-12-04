#pragma once
#include "Session.h"

/*class httpSession : protected Session, public std::enable_shared_from_this<httpSession>
{
private:
	boost::asio::ip::tcp::socket socket_;

public:
	httpSession(boost::asio::ip::tcp::socket socket, Router<std::string, luabridge::LuaRef>& router, Verifier& verifer, RequestParser& request_parser);

	virtual void start();

	virtual ~httpSession();

	virtual void do_write_my(const std::string& message);

	virtual void do_read();
};*/