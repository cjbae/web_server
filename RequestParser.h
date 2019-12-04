#pragma once
#include "Request.h"
class RequestParser
{
public:
	RequestParser() {}
	~RequestParser() {}

	bool parser(Request& request, std::string& data);

	// ���پ� ������ �����͸� request�� �޼ҵ�� ���� ������ �����Ѵ�.

	// ����
	void parse_version(Request& request, std::string& message);

	// �޼ҵ�
	void parse_method(Request& request, std::string& message);

	// url
	void parse_uri(Request& request, std::string& message);

	// ���
	void parse_header(Request& request, std::vector<std::string>& request_list);

	// ������� accept, encoding, language
	void parse_accept(Request& request, std::string content);
	void parse_encoding(Request& request, std::string content);
	void parse_language(Request& request, std::string content);

};