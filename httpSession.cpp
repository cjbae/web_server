#include "httpSession.h"

/*httpSession::httpSession(boost::asio::ip::tcp::socket socket, Router<std::string, luabridge::LuaRef>& router, Verifier& verifer, RequestParser& request_parser)
	: socket_(std::move(socket)), Session(router, verifer, request_parser)
{
}

httpSession::~httpSession()
{
}

void httpSession::start()
{
	do_read();
}
void httpSession::do_write_my(const std::string& message)
{
	//response_generator_.to_buffers(message);
	auto self(shared_from_this());
	boost::asio::async_write(socket_, boost::asio::const_buffer(message.c_str(), message.size()), [this, self](const boost::system::error_code ec, const std::size_t size)
		{
			if (!ec)
			{
				boost::system::error_code ignored_ec;
				socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
			}

			if (ec != boost::asio::error::operation_aborted)
			{
				boost::system::error_code ignored_ec;
				socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
				socket_.close();
			}
		});
}

void httpSession::do_read()
{
	auto self(shared_from_this());
	socket_.async_read_some(boost::asio::buffer(data_), [self, this](const boost::system::error_code ec, const std::size_t length)
		{
			if (!ec)
			{
				if (length >= max_length)
				{
					recv_data_.reserve(recv_data_.size() + max_length);

					std::copy(data_.begin(), data_.end(), std::back_inserter(recv_data_));

					do_read();
				}
				else
				{
					std::copy(data_.begin(), data_.begin() + length, std::back_inserter(recv_data_));

					std::string recv_data = std::string(recv_data_.begin(), recv_data_.end());

					if (request_parser_.parser(request_, recv_data))
					{
						verifier_.verifier(request_);

						// 일단은 옛날방식
						//std::string response_message;
						//if (route_.DoFunc(request_, response_message) == false)
						//	set_bad_message(html_method::not_found, html_message::not_found, response_message, request_);
						//do_write_my(response_message);

						//lua_.init();

						//std::cout << make_response_message() << std::endl;

						do_write_my(make_response_message());
					}

					recv_data_.clear();
				}
			}
		});
}
*/