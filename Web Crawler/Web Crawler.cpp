// Web Crawler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

struct Url {
    std::string scheme;
    std::string host;
    std::string port;
    std::string path;
    std::string query;
    std::string fragment;
};

Url parseUrl(std::string& str) {
    Url url;
    int pos = 0;

    // Check the scheme
    pos = str.find("://");
    if (pos == std::string::npos || str.substr(0, pos) != "http") {
        std::cerr << "Error: Scheme should be http" << std::endl;
        exit(1);
    }
    // If scheme is http set the struct
    url.scheme = "http";
    str = str.substr(pos + 3);
    pos += 3;

    // Parse the Fragment
    pos = str.find("#");
    if (pos != std::string::npos) {
        url.fragment = str.substr(pos + 1);
        str = str.substr(0, pos);  // Truncate from pos to end (truncating the end off)
    }

    // Parse the query
    pos = str.find("?");
    if (pos != std::string::npos) {
        url.query = str.substr(pos + 1);
        str = str.substr(0, pos);  // Truncate from pos to end (truncating the end off)
    }

    // Parse the path
    pos = str.find("/");
    if (pos != std::string::npos) {
        url.path = str.substr(pos);
        str = str.substr(0, pos);  // Truncate from pos to end (truncating the end off)
    }
    // Default if no path exists
    else {
        url.path = "/";
    }

    // Parse the host and port
    pos = str.find(":");
    if (pos != std::string::npos) {
        url.host = str.substr(0, pos);
        url.port = str.substr(pos + 1);
        str = str.substr(0, pos);  // Truncate from pos to end (truncating the end off)
    }
    else {
        url.host = str;
    }

    return url;
}

int main(int argc, char** argv)
{
	printf("Command Line : %s\n", argv[1]);

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <URI>" << std::endl;
        return 1;
    }

    std::string input = argv[1];
    Url url = parseUrl(input);

    if (url.scheme != "http") {
        std::cerr << "Error: Scheme should be http" << std::endl;
        return 1;
    }

    std::cout << "Scheme: " << url.scheme << std::endl;
    std::cout << "Host: " << url.host << std::endl;
    std::cout << "Port: " << url.port << std::endl;
    std::cout << "Path: " << url.path << std::endl;
    std::cout << "Query: " << url.query << std::endl;
    std::cout << "Fragment: " << url.fragment << std::endl;

    return 0;

    
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
