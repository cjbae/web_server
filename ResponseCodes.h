#pragma once
#include <iostream>
#include <string>
#include <vector>

// 헤더, 접속 가능 주소, 컨텐츠 타입, 응답코드 저장해놓는 클래스
// 다른 코드에서 이런거 필요할때 여기서 갖다 쓰려고..

namespace html_method1
{
	const std::string not_found("HTTP/1.1 404 Not Found\r\n");
	const std::string ok("HTTP/1.1 200 OK\r\n");
	const std::string forbidden("HTTP/1.1 403 Forbidden\r\n");
	const std::string ver_not_supported("HTTP/1.1 505 HTTP Version Not Supported\r\n");
	const std::string bad_request("HTTP/1.1 400 Bad Request\r\n");
	const std::string method_not_allowed("HTTP/1.1 405 Method Not Allowed\r\n");
	const std::string url_too_long("HTTP/1.1 414 URI Too Long\r\n");
	const std::string unsupported_media_type("HTTP/1.1 415 Unsupported Media Type\r\n");
	const std::string test_ok("HTTP/1.1 200 test_ok\r\n");
}

namespace html_message1
{
	const std::string not_found("<html>"
		"<head><title>Not Found</title></head>"
		"<body><h1>404 Not Found</h1></body>"
		"</html>");
	const std::string bad_request("<html>"
		"<head><title>Bad Request</title></head>"
		"<body><h1>400 Bad Request</h1></body>"
		"</html>");
	const std::string ok("<html>"
		"<head><title>connect</title>"
		"<meta http-equiv=\"refresh\" content=\"0;URL=http://"
		"\">"
		"</head>"
		"<body><h1></h1></body>"
		"</html>");
	const std::string forbidden("<html>"
		"<head><title>Forbidden</title></head>"
		"<body><h1>403 Forbidden</h1></body>"
		"</html>");

	const std::string ver_not_supported("<html>"
		"<head><title>HTTP Version Not Supported</title></head>"
		"<body><h1>505 HTTP Version Not Supported</h1></body>"
		"</html>");
	const std::string method_not_allowed("<html>"
		"<head><title>Method Not Allowed</title></head>"
		"<body><h1>405 Method Not Allowed</h1></body>"
		"</html>");
	const std::string url_too_long("<html>"
		"<head><title>URI Too Long</title></head>"
		"<body><h1>414 URI Too Long</h1></body>"
		"</html>");
	const std::string unsupported_media_type("<html>"
		"<head><title>Unsupported Media Type</title></head>"
		"<body><h1>415 Unsupported Media Type</h1></body>"
		"</html>");

	const std::string test_ok("<html>"
		"<head><title>test_ok</title></head>"
		"<body><h1>test_ok</h1></body>"
		"</html>");

	const std::string test_redirect("<form method = \"post\" name = \"id\" action = \'http://10.103.13.230:3000/TEST2\'>"
		"address : <input name = \'address\' type = \'text\' / ><br>"
		"< input type = \'submit\' value = \'login\'\'>"
		"< \/ form>"
	);
}

// 헤더 종류
namespace info
{
	const std::string Accept("Accept");
	const std::string Accept_Language("Accept-Language");
	const std::string Upgrade_Insecure_Requests("Upgrade-Insecure-Requests");
	const std::string User_Agent("User-Agent");
	const std::string Accept_Encoding("Accept-Encoding");
	const std::string Host("Host");
	const std::string Connection("Connection");
	const std::string Cache_Control("Cache-Control");
	const std::string Date("Date");
	const std::string Origin("Origin");
	const std::string Referer("Referer");
	const std::string Accept_Charset("Accept-Accept-Charset");
	const std::string Purpose("Purpose");
	const std::string Content_Length("Content-Length");
	const std::string Content_Type("Content-Type");
	const std::string Cookie("Cookie");

	const std::string filename("filename");
	const std::string Postman_Token("Postman-Token");
};

// 접속 가능한 주소 저장
namespace access_address
{
	const std::string Somansa_mail("mail.somansa.com");
	const std::string Somansa_notes("notes.somansa.com");
};

// content-type 
namespace mime_types
{
	const std::string html("text/html");
	const std::string gif("image/gif");
	const std::string jpg("image/jpeg");
	const std::string png("image/png");
};

// language
namespace language
{
	const std::string ko_kr("ko-KR");
	const std::string ko("ko");
	const std::string en_us("en_US");
	const std::string en("en");
};

// encoding-type
namespace encoding_types
{
	const std::string gzip("gzip");
	const std::string deflate("deflate");
};

class ResponseCodes
{
public:
	std::vector<std::string> access_address_;
	std::vector<std::string> info_;
	std::vector<std::string> mime_type_;
	std::vector<std::string> language_;
	std::vector<std::string> endoding_type_;

	// 코드 종류
	enum response_code
	{
		ok,
		not_found,
		forbidden,
		ver_not_supported,
		bad_request,
		method_not_allowed,
		url_too_long,
		unsupported_media_type,
		test_ok
	};

	ResponseCodes()
	{
		info_.push_back(info::Accept);
		info_.push_back(info::Accept_Encoding);
		info_.push_back(info::Accept_Language);
		info_.push_back(info::Cache_Control);
		info_.push_back(info::Connection);
		info_.push_back(info::Host);
		info_.push_back(info::Upgrade_Insecure_Requests);
		info_.push_back(info::User_Agent);
		info_.push_back(info::Date);
		info_.push_back(info::Referer);
		info_.push_back(info::Origin);
		info_.push_back(info::Accept_Charset);
		info_.push_back(info::Purpose);
		info_.push_back(info::Content_Length);
		info_.push_back(info::Content_Type);
		info_.push_back(info::Cookie);
		info_.push_back(info::filename);
		info_.push_back(info::Postman_Token);


		access_address_.push_back(access_address::Somansa_mail);
		access_address_.push_back(access_address::Somansa_notes);

		mime_type_.push_back(mime_types::html);
		mime_type_.push_back(mime_types::gif);
		mime_type_.push_back(mime_types::jpg);
		mime_type_.push_back(mime_types::png);

		language_.push_back(language::ko);
		language_.push_back(language::ko_kr);
		language_.push_back(language::en_us);
		language_.push_back(language::en);

		endoding_type_.push_back(encoding_types::gzip);
		endoding_type_.push_back(encoding_types::deflate);
	}

	~ResponseCodes()
	{

	}
};