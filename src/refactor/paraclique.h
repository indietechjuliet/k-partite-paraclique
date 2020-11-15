/*Author: Rachel Offutt, University of Tennessee
*Date Last Modified: Nov. 14, 2020
*/


void printParacliqueandImputed(vector <int> paraclique,vector <vector <int> > matrix, ofstream& fout);
void computeParaclique(int glom, vector <int> &paraclique, vector <vector <int> > &matrix);
bool countAdjacentAddImputed(int target, int glom, vector < vector <int> > &matrix,  vector < int >  &paraclique);
