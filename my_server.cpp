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
		context_.set_options( // ssl�ɼ� ����
			boost::asio::ssl::context::default_workarounds // �پ��� ���� �ذ� ����� �����Ͻʽÿ�
			| boost::asio::ssl::context::no_sslv2 // sslv2 ��Ȱ��ȭ
			| boost::asio::ssl::context::single_dh_use); // tmp_dh ���ڸ� ����Ҷ� �׻� ��Ű�� �ۼ��϶�
		context_.set_password_callback(std::bind(&my_server::get_password, this)); // ��й�ȣ �ݹ� ����

		// ������ ������ ������ Ŭ�� ���� ������ĵ� �߿��� �´°� �־�� �� �Ƹ���..
		// ���� ����
		context_.use_certificate_chain_file(cert_path); // ������ ü���� ���ؽ�Ʈ�� �ε� file�� �Ⱥ����� ���ۿ��� �ε�
		context_.use_private_key_file(key_path, boost::asio::ssl::context::pem); // ����Ű�� ���ؽ�Ʈ�� �ε�
		//context_.use_tmp_dh_file("C:\\Program Files\\OpenSSL-Win64\\bin\\dh2048.pem"); //Diffie-Hellman �Ű������� �� ������ ���� ����
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