/*Author: Rachel Offutt, University of Tennessee
*Date Last Modified: Nov. 14, 2020
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include<bits/stdc++.h>
using namespace std;

struct Graph
{
	std::vector<std::vector<int> > matrix;
	std::vector<std::set<int> > partiteSets;
	std::map<int, string> label_map;
	std::map<string, int> int_map;
};

void printParacliqueandImputed(vector <int> paraclique,Graph& matrix, ofstream& fout);
void computeParaclique(int glom, vector <int> &paraclique, vector <vector <int> > &matrix);
bool countAdjacentAddImputed(int target, int glom, vector < vector <int> > &matrix,  vector < int >  &paraclique);
