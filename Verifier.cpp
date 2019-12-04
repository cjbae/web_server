#include "Verifier.h"

Verifier::Verifier() {}
Verifier::~Verifier() {}

ResponseCodes::response_code Verifier::verifier(Request& request)
{
	mime_type_check(request);

	auto result = encoding_check(request);
	if (ResponseCodes::response_code::ok != result)
	{
		return result;
	}

	result = language_check(request);
	if (ResponseCodes::response_code::ok != result)
	{
		return result;
	}

	result = method_check(request);
	if (ResponseCodes::response_code::ok != result)
	{
		return result;
	}

	result = head_check(request);
	if (ResponseCodes::response_code::ok != result)
	{
		return result;
	}

	return ResponseCodes::response_code::ok;
}

bool Verifier::ver_not_supported_check(const std::string& version)
{
	if (version == "1.1") return true;
	else return false;
}

bool Verifier::http_method_check(const std::string& method)
{
	if (method == "GET") return true;
	else if (method == "POST") return true;

	else return false;
}

bool Verifier::http_head_check(const std::string& head)
{
	auto iter = find(response_codes.info_.begin(), response_codes.info_.end(), head);
	if (iter == response_codes.info_.end())
	{
		return false;
	}
	else return true;
}

bool Verifier::forbidden_check(const std::string& address)
{
	auto find_iter = find(response_codes.access_address_.begin(), response_codes.access_address_.end(), address);
	if (find_iter != response_codes.access_address_.end())
	{
		return true;
	}
	else return false;
}

bool Verifier::grammar_check(const std::string& content)
{
	for (auto c : content)
	{
		if (is_ctl(c))
		{
			return false;
		}
	}
	return true;
}

bool Verifier::url_too_long_check(const std::string& url)
{
	if (url.size() <= max_url_size)
	{
		return true;
	}
	else return false;
}


ResponseCodes::response_code Verifier::method_check(const Request& request)
{
	if (ver_not_supported_check(request.version_) == false)
	{
		return ResponseCodes::response_code::ver_not_supported;
	}

	if (http_method_check(request.method_) == false)
	{
		return ResponseCodes::response_code::method_not_allowed;
	}
	//else if (request.method_ == "POST")
	//{
	//	std::ofstream out("C:\\Users\\somansa\\Desktop\\http practice\\test.txt");
	//	if (out.is_open())
	//	{
	//		out << request.file_body_;
	//	}
	//}

	if (request.uri_.size() > 0)
	{
		if (url_too_long_check(request.uri_) == false)
		{
			return ResponseCodes::response_code::url_too_long;
		}
		if (forbidden_check(request.uri_) == false)
		{
			return ResponseCodes::response_code::forbidden;
		}
	}
	return ResponseCodes::response_code::ok;
}

ResponseCodes::response_code Verifier::head_check(const Request& request)
{
	for (auto head : request.headers_)
	{
		if (http_head_check(head.key) == false)
		{
			return ResponseCodes::response_code::not_found;
		}
		if (grammar_check(head.value) == false)
		{
			return ResponseCodes::response_code::bad_request;
		}
	}
	return ResponseCodes::response_code::ok;
}

void Verifier::mime_type_check(Request& request)
{
	/*if(request.mime_type_.size() == 0) request.final_mime_type_ = "text/html";
	for(auto type : request.mime_type_)
	{
		auto find_iter = find(response_codes.mime_type_.begin(), response_codes.mime_type_.end(), type);
		if(find_iter == response_codes.mime_type_.end())
		{
			request.final_mime_type_ = "text/html";
		}
		else
		{
			request.final_mime_type_ = *find_iter;
		}
	}*/
}

ResponseCodes::response_code Verifier::encoding_check(Request& request)
{
	/* if(request.encoding_type_.size() == 0) return ResponseCodes::response_code::unsupported_media_type;
	 for(auto type : request.encoding_type_)
	 {
		 auto find_iter = find(response_codes.endoding_type_.begin(), response_codes.endoding_type_.end(), type);
		 if(find_iter != response_codes.endoding_type_.end())
		 {
			 request.final_encoding_type_ = *find_iter;
			 return ResponseCodes::response_code::ok;
		 }
	 }*/
	return ResponseCodes::response_code::unsupported_media_type;
}

ResponseCodes::response_code Verifier::language_check(Request& request)
{
	/*if (request.language_.size() == 0) {
		return ResponseCodes::response_code::unsupported_media_type;
	}
	for(auto type : request.language_)
	{
		auto find_iter = find(response_codes.language_.begin(), response_codes.language_.end(), type);
		if(find_iter != response_codes.language_.end())
		{
			request.final_language_ = *find_iter;
			return ResponseCodes::response_code::ok;
		}
	}*/
	return ResponseCodes::response_code::unsupported_media_type;
}

bool Verifier::is_ctl(const int c)
{
	return (c >= 0 && c <= 31) || (c == 127);
}