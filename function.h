
#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

	void printmap(std::vector<std::vector<int>> map, int N);
	std::vector<std::vector<int>> makemap(int N, int a, int b, bool wall);
	std::vector<std::vector<int>> muv(std::vector<std::vector<int>> map, int N, std::string &name, bool &muve1);
	std::vector<std::vector<int>> muv2(std::vector<std::vector<int>> map, int N);
	std::vector<std::vector<int>> muv3(std::vector<std::vector<int>> map, int N, std::string &name, bool &muve1);
	bool checkVin(std::vector<std::vector<int>> map, int N, int &area);
	bool checkLose(std::vector<std::vector<int>> map, int N);
	std::vector<std::vector<int>> bestMuv(std::vector<std::vector<int>> map, int N);
	void saveGame(std::vector<std::vector<int>> map, int N, std::string &name, bool &muve1);

#endif