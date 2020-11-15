/*Author: Rachel Offutt, University of Tennessee
*Date Last Modified: Nov. 13, 2020
*/
bool allConnected(vector <int> R, vector <vector <int > > matrix);
void enumerate(vector <vector <int > > matrix, vector <int> R, vector <int> P, vector <int> X, vector <int> partiteSets, multimap<int,vector <int>> &cliques );
vector <int> choosePivot(vector <int> P , vector <int> X, vector < vector <int >> matrix);
vector <int> intersection( vector <int> setA, vector <int> matrixRow);
int coverPartition(vector <int> R, vector <int> partiteSets);

