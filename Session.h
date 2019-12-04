#pragma once
#include "Request.h"
#include "Verifier.h"
#include "ResponseCodes.h"
#include "Router.h"
#include "RequestParser.h"
#include "LuaManager.h"
#include <functional>
#include <array>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "Socket.h"
// 연결 담당

const std::string not_found_info("HTTP/1.1 404 Not Found\r\n");

const std::string not_found_body("<html>"
	"<head><title>Not Found</title></head>"
	"<body><h1>404 Not Found</h1></body>"
	"</html>");

using SocketPtr = std::shared_ptr<Socket>;


class Session : public std::enable_shared_from_this<Session>
{
public:
	enum { max_length = 10000 };

private:
	std::vector<char> recv_data_;
	std::array<char, max_length> data_;
	SocketPtr socket_;
	//boost::asio::ip::tcp::socket& socket_;
	Request request_;


	Verifier& verifier_;
	Router<std::string, luabridge::LuaRef>& route_;
	RequestParser& request_parser_;

public:
	Session(SocketPtr socket,
		Router<std::string, luabridge::LuaRef>& router,
		Verifier& verifer,
		RequestParser& request_parser);

	virtual ~Session();

	virtual void start();
private:
	void do_read();
	std::string make_response_message();
	virtual void do_write_my(const std::string& message);

	void set_bad_message(const std::string& method, const std::string& content, std::string& send_message, const Request& request)
	{
		send_message += method;

		//if (request.final_language_.size() != 0)
		//{
		//	send_message += "Content-Language: ";
		//	send_message += request.final_language_;
		//	send_message += "\r\n";
		//}

		send_message += "Content-Length";
		send_message += ": ";
		send_message += std::to_string(content.size());
		send_message += "\r\n";
		send_message += "Content-Type";
		send_message += ": ";
		//send_message += request.final_mime_type_;
		send_message += "text/html";

		send_message += "\r\n";
		send_message += "\r\n";
		send_message += content;
	}
};
