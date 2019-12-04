#include "Socket.h"


///////////////////////////////////////////////////////////////
NormalSocket::NormalSocket(boost::asio::ip::tcp::socket socket)
	: socket_(std::move(socket))
{
}

void NormalSocket::DoRead(const boost::asio::mutable_buffer& buffer, Handler handler)
{
	socket_.async_read_some(buffer, handler);
}

void NormalSocket::ShutDown(boost::system::error_code& ignored_ec)
{
	socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
}

void NormalSocket::Close()
{
	socket_.close();
}

void NormalSocket::DoWrite(const boost::asio::const_buffer& buffer, Handler handler)
{
	boost::asio::async_write(socket_, buffer, handler);
}

//////////////////////////////////////

SslSocket::SslSocket(boost::asio::ip::tcp::socket socket, boost::asio::ssl::context& context)
	: socket_(std::move(socket), context)
{
}



void SslSocket::HandShake(const boost::asio::ssl::stream_base::handshake_type& type, HandshakeHandler handler)
{
	socket_.async_handshake(type, handler);
}


void SslSocket::DoRead(const boost::asio::mutable_buffer& buffer, Handler handler)
{
	socket_.async_read_some(buffer, handler);
}

void SslSocket::ShutDown(boost::system::error_code& ignored_ec)
{
	socket_.lowest_layer().shutdown(socket_.lowest_layer().shutdown_both);
}

void SslSocket::Close()
{
	socket_.lowest_layer().close();
}

void SslSocket::DoWrite(const boost::asio::const_buffer& buffer, Handler handler)
{
	boost::asio::async_write(socket_, buffer, handler);
}