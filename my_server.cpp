#include "my_server.h"
#include "Socket.h"

my_server::my_server(boost::asio::io_context& io_context, const int port)
	: acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
	socket_(io_context),
	context_(boost::asio::ssl::context::sslv23)
	, io_context_(io_context)
{
	if (filesystem::exists("server.conf"))
	{
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("server.conf", pt);
		std::string on = pt.get<std::string>("SSL.use");
		if (on == "on") ssl_on = true;
		else if (on == "off") ssl_on = false;
		else ssl_on = false;

		cert_path = pt.get<std::string>("SSL.cert");
		key_path = pt.get<std::string>("SSL.key");

	}
	else
	{
		ssl_on = false;
	}

	if (ssl_on)
	{
		context_.set_options(boost::asio::ssl::context::sslv23);
		context_.set_options( // ssl옵션 구성
			boost::asio::ssl::context::default_workarounds // 다양한 버그 해결 방법을 구현하십시오
			| boost::asio::ssl::context::no_sslv2 // sslv2 비활성화
			| boost::asio::ssl::context::single_dh_use); // tmp_dh 인자를 사용할땐 항상 새키를 작성하라
		context_.set_password_callback(std::bind(&my_server::get_password, this)); // 비밀번호 콜백 설정

		// 서버의 인증서 모음들 클라가 보낸 인증방식들 중에서 맞는게 있어야 함 아마도..
		// 서버 설정
		context_.use_certificate_chain_file(cert_path); // 인증서 체인을 컨텍스트로 로드 file가 안붙은건 버퍼에서 로드
		context_.use_private_key_file(key_path, boost::asio::ssl::context::pem); // 개인키를 컨텍스트로 로드
		//context_.use_tmp_dh_file("C:\\Program Files\\OpenSSL-Win64\\bin\\dh2048.pem"); //Diffie-Hellman 매개변수를 이 파일을 통해 얻어라
	}

	file_register();
	do_accept();
}

my_server::~my_server()
{
}

std::string my_server::get_password()
{
	return "test";
}

void my_server::register_handle(const std::string& method, const std::string& location, const std::string& lua_file_name)
{
	if (method == "GET")
	{
		route_.get(location, LuaManager::Instance()->RegisterHandler(lua_file_name));
	}
	else if (method == "POST")
	{
		route_.post(location, LuaManager::Instance()->RegisterHandler(lua_file_name));
	}
}

void my_server::do_accept()
{
	acceptor_.async_accept(socket_, [this](boost::system::error_code ec)
		{
			if (!ec)
			{
				std::shared_ptr<Socket> sock;
				if (ssl_on)
				{
					sock = std::make_shared<SslSocket>(std::move(socket_), context_);
				}
				else
				{
					sock = std::make_shared<NormalSocket>(std::move(socket_));
				}
				auto session = std::make_shared<Session>(sock, route_, verifier_, request_parser_);
				session->start();
			}
			do_accept();
		});
}

void my_server::file_register()
{
	Route route;
	std::ifstream ifs("config.json");
	nlohmann::json j_complete = nlohmann::json::parse(ifs);
	if (ifs.is_open())
	{
		for (auto i = 0; i < j_complete["files"].size(); ++i)
		{
			if (filesystem::exists(j_complete["files"][i].get<std::string>()))
			{
				auto r = LuaManager::Instance()->RegisterRouter(j_complete["files"][i].get<std::string>().c_str());

				register_handle(r.method, r.location, j_complete["files"][i].get<std::string>());
			}
		}

		if (filesystem::exists(j_complete["directory"].get<std::string>()))
		{
			filesystem::directory_iterator end;
			for (filesystem::directory_iterator iter(j_complete["directory"].get<std::string>()); iter != end; ++iter)
			{
				if (iter->path().extension() == ".lua")
				{
					std::string path(iter->path().parent_path().string());
					path += "\\";
					path += iter->path().filename().string();
					auto r = LuaManager::Instance()->RegisterRouter(path);
					register_handle(r.method, r.location, path);
				}
			}
		}
	}

	ifs.close();
}