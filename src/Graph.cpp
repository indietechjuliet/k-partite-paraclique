
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Graph
{
	std::vector<std::vector<int> > matrix;
	std::vector<std::set<int> > partiteSets;
	std::map<int, std::string> label_map;
	std::map<std::string, int> int_map;

};