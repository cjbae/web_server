#pragma once
#include "Request.h"
class RequestParser
{
public:
	RequestParser() {}
	~RequestParser() {}

	bool parser(Request& request, std::string& data);

	// 한줄씩 저장한 데이터를 request에 메소드와 헤드로 나눠서 저장한다.

	// 버전
	void parse_version(Request& request, std::string& message);

	// 메소드
	void parse_method(Request& request, std::string& message);

	// url
	void parse_uri(Request& request, std::string& message);

	// 헤더
	void parse_header(Request& request, std::vector<std::string>& request_list);

	// 헤더에서 accept, encoding, language
	void parse_accept(Request& request, std::string content);
	void parse_encoding(Request& request, std::string content);
	void parse_language(Request& request, std::string content);

};