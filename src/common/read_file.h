#pragma once

#include <string>
#include <fstream>
#include <iostream>



std::string readFile(std::string path) {
	
	std::string line, content;
	std::ifstream filestream(path, std::ios::in);

	if (!filestream.is_open()) {
		std::cout << "Path to file does not exist.";
		return "\0";
	}

	while (!filestream.eof()) {
		
		std::getline(filestream, line);
		content.append(line + "\n");

	}

	filestream.close();
	return content;
}
