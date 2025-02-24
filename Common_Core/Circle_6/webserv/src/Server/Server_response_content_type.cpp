#include "Server.hpp"

string Server::getContentType(const string& filename) const 
{
	static std::map<string, string>	extensionToType;

	if (extensionToType.empty()) {
		// Image types
		extensionToType["jpg"] = "image/jpeg";
		extensionToType["jpeg"] = "image/jpeg";
		extensionToType["png"] = "image/png";
		extensionToType["gif"] = "image/gif";
		extensionToType["svg"] = "image/svg+xml";
		extensionToType["webp"] = "image/webp";
		// Text types
		extensionToType["txt"] = "text/plain";
		extensionToType["html"] = "text/html";
		extensionToType["css"] = "text/css";
		extensionToType["js"] = "application/javascript";
		// Audio types
		extensionToType["mp3"] = "audio/mpeg";
		extensionToType["wav"] = "audio/wav";
		extensionToType["ogg"] = "audio/ogg";
		// Video types
		extensionToType["mp4"] = "video/mp4";
		extensionToType["webm"] = "video/webm";
		extensionToType["ogg"] = "video/ogg";
		// Application types
		extensionToType["json"] = "application/json";
		extensionToType["xml"] = "application/xml";
		extensionToType["pdf"] = "application/pdf";
		extensionToType["zip"] = "application/zip";
	}
	std::size_t	dotPos = filename.find_last_of('.');
	if (dotPos != string::npos) {
		string	extension = filename.substr(dotPos + 1);

		std::map<string, string>::iterator it = extensionToType.find(extension);
		if (it != extensionToType.end()) {
			return (it->second);
		}
	}
	return ("application/octet-stream");
}
