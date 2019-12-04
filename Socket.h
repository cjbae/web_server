#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <functional>

using Handler = std::function<void(const boost::system::error_code&, std::size_t)>;
using HandshakeHandler = std::function<void(const boost::system::error_code&)>;

struct Socket
{
	virtual ~Socket() = default;
	virtual void HandShake(const boost::asio::ssl::stream_base::handshake_type&, HandshakeHandler handler) = 0;

	void Read(const boost::asio::mutable_buffer& buffer, Handler handler)
	{
		DoRead(buffer, handler);
	}
	void Write(const boost::asio::const_buffer& buffer, Handler handler)
	{
		DoWrite(buffer, handler);
	}
	virtual void ShutDown(boost::system::error_code& ignored_ec) = 0;
	virtual void Close() = 0;

private:
	virtual void DoRead(const boost::asio::mutable_buffer& buffer, Handler handler) = 0;
	virtual void DoWrite(const boost::asio::const_buffer& buffer, Handler handler) = 0;
protected:
	enum { max_length = 10000 };
	std::vector<char> recv_data_;
	std::array<char, max_length> data_;
};


class NormalSocket
	: public Socket
{
public:
	NormalSocket(boost::asio::ip::tcp::socket socket);
	void HandShake(const boost::asio::ssl::stream_base::handshake_type&, HandshakeHandler handler) {}
	void DoRead(const boost::asio::mutable_buffer& buffer, Handler handler);
	void ShutDown(boost::system::error_code& ignored_ec);
	void Close();
	void DoWrite(const boost::asio::const_buffer& buffer, Handler handler);
private:
	boost::asio::ip::tcp::socket socket_;
};


class SslSocket
	: public Socket
{
public:
	SslSocket(boost::asio::ip::tcp::socket socket, boost::asio::ssl::context& context);
	void HandShake(const boost::asio::ssl::stream_base::handshake_type&, HandshakeHandler handler);
	void DoRead(const boost::asio::mutable_buffer& buffer, Handler handler);
	void ShutDown(boost::system::error_code& ignored_ec);
	void Close();
	void DoWrite(const boost::asio::const_buffer& buffer, Handler handler);
private:
	boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
};