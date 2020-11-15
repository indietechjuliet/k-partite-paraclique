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
#include<bits/stdc++.h>
using namespace std;

//prints the current nodes in the paraclique and the imputed edges
void printParacliqueandImputed(vector <int> paraclique,vector <vector <int> > matrix, ofstream& fout)
{
	fout<<"Complete Paraclique with Imputed Edges:\n";
	for(int i = 0; i < paraclique.size(); i++)
		fout<<paraclique[i]<<" ";
	fout<<"\n\nImputed Edges:\n";

	for(int i = 0; i < matrix[0].size(); i++)
	{
		for(int j = 0; j <= i; j++)
		{
			if(matrix[i][j] == 2)
				fout <<i<<" "<<j<<'\n';
		}
	}
}

//countAdjaccntAddImputed - this function serves two pruposes: to check if a target node's number
//of edges needed to be in the paraclique, and to add the imputed edges to the matrix and the node
//to the paraclique if the number of edges needed are less than the glom factor
bool countAdjacentAddImputed(int target, int glom, vector < vector <int> > &matrix,  vector < int >  &paraclique)
{
	vector <int> temp;
	//for every node in the current paracclique that is not connected to the target node,
	//add to the temporary vector
	for(int i = 0; i < paraclique.size(); i++)
	{
		if(matrix[target][paraclique[i]] != 1)
			temp.push_back(paraclique[i]);
	}

	//If the target node is not connected to fewer vertices than the glom factor, add the imputed 
	//edges and add theis node to the paraclique
	if((glom) >= temp.size())
	{
		
		for(int i = 0; i < temp.size(); i++)
		{
			matrix[temp[i]][target] = 2;
			matrix[target][temp[i]] = 2;
		}
		paraclique.push_back(target);

		return true;
	}
	return false;
}
//comouteParaclique - this function follows the paraclique computation method outlined in the 
//README on the Github
void computeParaclique(int glom, vector <int> &paraclique, vector <vector <int> > &matrix)
{
	vector <int> vBar;
	for(int i = 0; i < matrix[0].size(); i++)
	{
		vector <int>::iterator it;
		it = find(paraclique.begin(), paraclique.end(), i);
		if(it ==paraclique.end())
			vBar.push_back(i);
	}
	
	bool recheck = false;
	do
	{
		recheck = false;
		bool innerrecheck = false;
		for(int i = 0; i < vBar.size(); i++)
		{
			innerrecheck = countAdjacentAddImputed(vBar[i], glom,  matrix, paraclique);
			if(!recheck && innerrecheck)
				recheck = true;

		}

	}while(recheck);
		

}



