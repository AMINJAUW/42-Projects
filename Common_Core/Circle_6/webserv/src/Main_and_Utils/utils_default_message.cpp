#include "webserv.hpp"

string default_message(int code)
{
	static std::map<int, string> 	default_messages;
	int								generic = (code / 100) * 100; 
	if (default_messages.empty())
	{
		default_messages[100] = "Continue";
		default_messages[101] = "Switching Protocols";
		default_messages[200] = "OK";
		default_messages[201] = "Created";
		default_messages[202] = "Accepted";
		default_messages[203] = "Non-Authoritative Information";
		default_messages[204] = "No Content";
		default_messages[205] = "Reset Content";
		default_messages[206] = "Partial Content";
		default_messages[226] = "IM Used";
		default_messages[300] = "Multiple Choices";
		default_messages[301] = "Moved Permanently";
		default_messages[302] = "Found";
		default_messages[303] = "See Other";
		default_messages[304] = "Not Modified";
		default_messages[305] = "Use Proxy";
		default_messages[307] = "Temporary Redirect";
		default_messages[400] = "Bad Request";
		default_messages[401] = "Unauthorized";
		default_messages[402] = "Payment Required";
		default_messages[403] = "Forbidden";
		default_messages[404] = "Not Found";
		default_messages[405] = "Method Not Allowed";
		default_messages[406] = "Not Acceptable";
		default_messages[407] = "Proxy Authentication Required";
		default_messages[408] = "Request Timeout";
		default_messages[409] = "Conflict";
		default_messages[410] = "Gone";
		default_messages[411] = "Length Required";
		default_messages[412] = "Precondition Failed";
		default_messages[413] = "Content Too Large";
		default_messages[414] = "URI Too Long";
		default_messages[415] = "Unsupported Media Type";
		default_messages[416] = "Requested Range Not Satisfiable";
		default_messages[417] = "Expectation Failed";
		default_messages[500] = "Internal Server Error";
		default_messages[501] = "Not Implemented";
		default_messages[502] = "Bad Gateway";
		default_messages[503] = "Service Unavailable";
		default_messages[504] = "Gateway Timeout";
		default_messages[505] = "HTTP Version Not Supported";
	}
	if (default_messages.find(code) == default_messages.end())
		return (default_messages[generic]);
	else
		return (default_messages[code]);
}
