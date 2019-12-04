#include "RequestParser.h"


bool RequestParser::parser(Request& request, std::string& data)
{
	data.erase(remove(data.begin(), data.end(), '\r'), data.end());

	auto first_pos = data.find("\n\n");
	if (first_pos == std::string::npos)
	{
		return false;
	}
	int size = data.size();
	if (size > first_pos + 2) {
		auto second_pos = data.find("\n\n", first_pos);
		if (second_pos == std::string::npos)
		{
			return false;
		}
	}

	std::vector<std::string> request_list;

	int prev_pos = 0;
	size = 0;
	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i] == '\n')
		{
			std::string s = data.substr(prev_pos, size);
			request_list.push_back(s);
			prev_pos = i + 1;
			size = 0;
		}
		else ++size;
	}

	parse_version(request, request_list[0]);
	parse_uri(request, request_list[0]);
	parse_method(request, request_list[0]);
	parse_header(request, request_list);

	auto second_pos = data.find("\n\n", first_pos);
	if (second_pos != std::string::npos)
	{
		auto size = find_if(request.headers_.begin(), request.headers_.end(), [](header& data) {
			if (data.key == "Content-Length") return true;
			else return false;
			});

		if (size != request.headers_.end())
		{
			request.body_ = data.substr(second_pos + 2, atoi((*size).value.c_str()));
			request.body_ = request.body_;
		}
	}
	return true;
}

void RequestParser::parse_version(Request& request, std::string& message)
{
	auto find_ver_pos = message.find("HTTP/");
	if (find_ver_pos != std::string::npos)
	{
		request.version_ = message.substr(find_ver_pos + 5, 3);
	}
}

void RequestParser::parse_method(Request& request, std::string& message)
{
	if (message.find("GET") != std::string::npos)
	{
		request.method_ = "GET";
		return;
	}
	if (message.find("POST") != std::string::npos)
	{
		request.method_ = "POST";
		return;
	}
}

void RequestParser::parse_accept(Request& request, std::string content)
{
	bool end = false;
	while (1)
	{
		auto pos = content.find(',');
		if (pos == std::string::npos)
		{
			end = true;
			pos = content.size() - 1;
		}
		std::string type = content.substr(0, pos);

		auto q_pos = type.find(';');
		if (q_pos == std::string::npos)
		{
			//request.mime_type_.push_back(type);
			content = content.assign(content, pos + 1, content.size() - 1);
		}
		else
		{
			type = type.assign(type, 0, q_pos);
			//request.mime_type_.push_back(type);
			content = content.assign(content, pos + 1, content.size() - 1);
		}
		if (end)
		{
			break;
		}
	}
}

void RequestParser::parse_encoding(Request& request, std::string content)
{
	content.erase(remove(content.begin(), content.end(), ' '), content.end());
	bool end = false;
	while (1)
	{
		auto pos = content.find(',');
		if (pos == std::string::npos)
		{
			end = true;
			pos = content.size() - 1;
		}
		std::string type = content.substr(0, pos);

		auto q_pos = type.find(';');
		if (q_pos == std::string::npos)
		{
			//request.encoding_type_.push_back(type);
			content = content.assign(content, pos + 1, content.size() - 1);
		}
		else
		{
			type = type.assign(type, 0, q_pos);
			//request.encoding_type_.push_back(type);
			content = content.assign(content, pos + 1, content.size() - 1);
		}
		if (end)
		{
			break;
		}
	}
}

void RequestParser::parse_language(Request& request, std::string content)
{
	bool end = false;
	while (1)
	{
		auto pos = content.find(',');
		if (pos == std::string::npos)
		{
			end = true;
			pos = content.size() - 1;
		}
		std::string type = content.substr(0, pos);

		auto q_pos = type.find(';');
		if (q_pos == std::string::npos)
		{
			//request.language_.push_back(type);
			content = content.assign(content, pos + 1, content.size() - 1);
		}
		else
		{
			type = type.assign(type, 0, q_pos);
			//request.language_.push_back(type);
			content = content.assign(content, pos + 1, content.size() - 1);
		}
		if (end)
		{
			break;
		}
	}
}

void RequestParser::parse_uri(Request& request, std::string& message)
{
	int url_size = 0;
	auto find_ver_pos = message.find("HTTP/");
	auto find_method_pos = message.find("GET");
	if (find_method_pos == std::string::npos)
	{
		find_method_pos = message.find("POST");
		if (find_method_pos == std::string::npos)
		{
			request.uri_ = "";
			return;
		}
		else
		{
			url_size = message.size() - 14;
			request.uri_ = message.substr(5, url_size);
		}
	}
	else
	{
		url_size = message.size() - 13;
		request.uri_ = message.substr(4, url_size);
	}
	if (request.uri_ == "/favicon.ico") request.uri_ = "";

	auto uri_pos = request.uri_.find('?');

	if (uri_pos != std::string::npos)
	{
		//request.test_submit_uri_ = request.url_.substr(uri_pos, request.url_.size() - uri_pos);
		request.uri_ = request.uri_.substr(0, uri_pos);
	}
	request.uri_;


	//if(request.url_.size() != 0 && request.url_.find("address=") != std::string::npos)
 //   {
 //       request.url_ = request.url_.substr(9, request.url_.size() - 1);

 //       if(request.url_.find("http%3A%2F%2F") != std::string::npos)
 //       {
 //           request.url_ = request.url_.substr(13, request.url_.size() - 1);
 //       }
 //   }

//   if(message.find("GET") != std::string::npos)
//   {
//       request.url_ = message.substr(5, find_ver_pos - 5);

//       if(request.url_.size() != 1 && request.url_.find("address=") != std::string::npos)
//       {
//           request.url_ = request.url_.substr(9, request.url_.size() - 1);

//           if(request.url_.find("http%3A%2F%2F") != std::string::npos)
//           {
//               request.url_ = request.url_.substr(13, request.url_.size() - 1);
//           }
//       }
//   }
   //std::cout << "request.url2 - " << request.url_ << ", " << request.url_.size() << std::endl;
}

void RequestParser::parse_header(Request& request, std::vector<std::string>& request_list)
{
	for (int i = 1; i < request_list.size(); ++i)
	{
		auto pos = request_list[i].find(": ");
		if (pos == std::string::npos) continue;
		std::string head(request_list[i].substr(0, pos));

		std::string content(request_list[i].substr(pos + 2, request_list[i].size() - 1));

		request.headers_.push_back(header(head, content));

		if (head == "Accept")
		{
			parse_accept(request, content);
		}
		else if (head == "Accept-Encoding")
		{
			parse_encoding(request, content);
		}
		else if (head == "Accept-Language")
		{
			parse_language(request, content);
		}
	}
	auto iter = find_if(request.headers_.begin(), request.headers_.end(), [](header& data) {
		if (data.key == "filename") return true;
		else return false;
		});

	if (iter != request.headers_.end())
	{
		request.body_ = request_list[request_list.size() - 1];
	}
}