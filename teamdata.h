#ifndef _TEAMDATA_H_
#define _TEAMDATA_H_

#include <string>

#include <vector>	// added header to define winPercentages_.
#include <iostream> // added header to print error if file doesn't open.
#include <fstream>	// added header to read given file and store in json object.
#include "json.hpp" // added header to use json objects.

using namespace std; // namespaces being used are std and nlohmann.
using namespace nlohmann;	// namespaces being used are std and nlohmann.

class TeamData
{
public:
	TeamData(std::string filename);
	int numPlayers() const;
	double winPercentages(int i, int j) const { return winPercentages_[i][j]; }

private:
	// TODO: decide the type of this variable.
	vector<vector<float>> winPercentages_; // winPercentages_ is a 2d vector of type float
	int numPlayers_;

}; // class TeamData

#endif // _TEAMDATA_H_