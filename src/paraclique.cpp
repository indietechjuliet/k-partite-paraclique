/*Author: Rachel Offutt, University of Tennessee
*Date Last Modified: Nov. 14, 2020
*/


#include "paraclique.h"




//prints the current nodes in the paraclique and the imputed edges
void printParacliqueandImputed(vector <int> paraclique, Graph &g, ofstream& fout)
{
	fout<<"Complete Paraclique with Imputed Edges:\n";
	for(int i = 0; i < paraclique.size(); i++)
		fout<<g.label_map[paraclique[i]]<<" ";
	fout<<"\n\nImputed Edges:\n";

	for(int i = 0; i < g.matrix[0].size(); i++)
	{
		for(int j = 0; j <= i; j++)
		{
			if(g.matrix[i][j] == 3)
				fout <<g.label_map[i]<<" "<<g.label_map[j]<<'\n';
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
	//cout<<"paraclique size: "<<paraclique.size()<<"\n";
	for(int i = 0; i < paraclique.size(); i++)
	{
		if(matrix[target][paraclique[i]] != 1 && matrix[target][paraclique[i]] != 2)
			temp.push_back(paraclique[i]);
	}
	//cout<<"glom: "<<glom<<" temp size: "<<temp.size()<<"\n";
	//If the target node is not connected to fewer vertices than the glom factor, add the imputed 
	//edges and add theis node to the paraclique
	if((glom) >= temp.size())
	{
		
		for(int i = 0; i < temp.size(); i++)
		{
			matrix[temp[i]][target] = 3;
			matrix[target][temp[i]] = 3;
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
			//cout<<"doing inner check\n";
			innerrecheck = countAdjacentAddImputed(vBar[i], glom,  matrix, paraclique);
			if(!recheck && innerrecheck)
				recheck = true;

		}

	}while(recheck);
		

}



