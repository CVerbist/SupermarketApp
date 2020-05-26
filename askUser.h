#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

#include "jsonHelp.h"

class askUser
{

public:

	// Asks the users any kind of input through the screen
	string askInput(string appQuery);
	string chooseList(json& chooseJson, string typeJson);
};

