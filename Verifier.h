#pragma once
#include <iostream>
#include <fstream>
#include "Request.h"
#include "ResponseCodes.h"
#include <string>

enum
{
	max_url_size = 50
};

class Verifier
{
public:
	ResponseCodes response_codes;

	Verifier();
	~Verifier();

	// 메인
	ResponseCodes::response_code verifier(Request& request);

	// 메소드와 헤드 검사
	ResponseCodes::response_code method_check(const Request& request);
	ResponseCodes::response_code head_check(const Request& request);

	// 응답 코드에 맞는지 에러 검사
	bool ver_not_supported_check(const std::string& version);
	bool http_method_check(const std::string& method);
	bool http_head_check(const std::string& head);
	bool forbidden_check(const std::string& address);
	bool grammar_check(const std::string& content);
	bool url_too_long_check(const std::string& url);


	// content-type 결정 함수
	void mime_type_check(Request& request);
	// encoding 검사 함수
	ResponseCodes::response_code encoding_check(Request& request);
	// language 검사 함수
	ResponseCodes::response_code language_check(Request& request);

	// 헤드에 잡문자가 있는지 확인하는 함수
	bool is_ctl(const int c);

	bool post_method_check(const std::string& method)
	{
		if (method == "POST") return true;
		else return false;
	}

	bool get_method_check(const std::string& method)
	{
		if (method == "GET") return true;
		else return false;
	}

	bool test_language_check(Request& request)
	{
		//if (request.language_.size() == 0) {
		//	return false;
		//}
		//for (auto type : request.language_)
		//{
		//	auto find_iter = find(response_codes.language_.begin(), response_codes.language_.end(), type);
		//	if (find_iter != response_codes.language_.end())
		//	{
		//		request.final_language_ = *find_iter;
		//		return true;
		//	}
		//}
		return false;
	}

	bool test_file_check(const Request& request)
	{
		//if (request.test_file_name_.size() == 0) {
		//	return false;
		//}
		return false;
	}
};