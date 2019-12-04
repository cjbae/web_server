#include "Session.h"


Session::Session(
	SocketPtr socket, Router<std::string, luabridge::LuaRef>& router,
	Verifier& verifer, RequestParser& request_parser)
	: route_(router)
	, verifier_(verifer)
	, request_parser_(request_parser)
	, socket_(socket)
{
	recv_data_.resize(max_length);
}

Session::~Session()
{
}

void Session::start()
{
	auto self(shared_from_this());
	socket_->HandShake(boost::asio::ssl::stream_base::server,
		[this, self](const boost::system::error_code& error)
		{
			if (!error)
			{
			}
		});
	do_read();
}

void Session::do_write_my(const std::string& message)
{
	//response_generator_.to_buffers(message);
	auto self(shared_from_this());
	socket_->Write(boost::asio::const_buffer(message.c_str(), message.size()), [this, self](const boost::system::error_code ec, const std::size_t size)
		{
			if (!ec)
			{
				boost::system::error_code ignored_ec;
				socket_->ShutDown(ignored_ec);
			}

			if (ec != boost::asio::error::operation_aborted)
			{
				boost::system::error_code ignored_ec;
				socket_->ShutDown(ignored_ec);
				socket_->Close();
			}
		});
}

std::string Session::make_response_message()
{
	// test
	std::string lua_name;
	std::string response_message = route_.handle(request_);

	if (response_message.size() == 0)
	{
		set_bad_message(not_found_info, not_found_body, response_message, request_);
		return response_message;
	}

	return response_message;
}
void Session::do_read()
{
	auto self(shared_from_this());
	socket_->Read(boost::asio::buffer(data_), [self, this](const boost::system::error_code ec, const std::size_t length)
		{
			if (!ec)
			{
				if (length >= max_length)
				{
					recv_data_.reserve(data_.size() + max_length);
					std::copy(data_.begin(), data_.end(), std::back_inserter(recv_data_));

					do_read();
				}
				else
				{
					std::copy(data_.begin(), data_.begin() + length, std::back_inserter(recv_data_));

					std::string recv_data = std::string(data_.begin(), data_.end());

					if (request_parser_.parser(request_, recv_data))
					{
						auto result = verifier_.verifier(request_);
						do_write_my(make_response_message());
					}

					recv_data_.clear();
				}
			}
			else
			{
				std::cout << ec.message() << std::endl;
			}
		});
}