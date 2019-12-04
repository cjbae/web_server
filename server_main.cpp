
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <atomic>
#include <thread>
#include <array>
#include <algorithm>
#include <vector>
#include <iterator>
//#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include "my_server.h"
#include "Router.h"
#include <functional>

#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string/predicate.hpp>
extern char* optarg;
int main(int argc, char** argv)
{
	//route.Add("aaa", "aaa", std::bind(&Tt::Func, test));
	//route.Add(0, boost::bind(&Func));

	//route.DoFunc("aaa", "aaa");
	//route.Do(0)
	int option = 0;
	int port;

	//if(argc < 3)
	//{
	//    std::cout << "option -p port gogo" << std::endl;
	//    return 0;
	//}
	//while((option = getopt(argc, argv, "p:")) != EOF)
	//{
	//    switch(option)
	//    {
	//        case 'p': 
	//            port = atoi(argv[2]);
	//            break;
	//        default: 
	//            std::cout << "option -p port gogo" << std::endl;
	//            return 0;
	//            break;
	//    }
	//}

	port = 3000;

	boost::asio::io_context io_context;
	std::string index = "C:\\Users\\somansa\\Desktop\\http practice\\";

	/*std::ifstream is(index + "index.html", std::ios::in | std::ios::binary);
	if (!is)
	{
		std::cout << "not index.html" << std::endl;
	}
	std::string root_html;
	char buf[512];
	while (is.read(buf, sizeof(buf)).gcount() > 0)
		root_html.append(buf, is.gcount());

	auto pos = root_html.find(".230:");
	pos += 5;
	if(pos != std::string::npos)
	{
		auto pos2 = root_html.find('\'', pos);
		if(pos2 != std::string::npos)
		{
			root_html.replace(pos, pos2-pos, argv[2]);
		}
	}
	is.close();

	std::ofstream out(index + "index.html");

	if(out.is_open())
	{
		out << root_html;
	}
	out.close();*/

	// parse and serialize JSON

	my_server s(io_context, port);

	io_context.run();
	io_context.stop();
}