#pragma once

#include "externalCode/json.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using json = nlohmann::json;

class jsonHelp
{
public:
	void writeJson(json& jsonToWrite, string nameOfFile);
	json readJson(string nameOfFile);
};

