//Author: Rachel Offutt - University of Tennessee
//Date Last Modified: Nov. 14, 2020


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include<bits/stdc++.h>
#include "inputprep.h"
using namespace std;


//resetIntrapartiteEdges - for every intrpartitie edge added to the nodes in every 
//partite sets for finding maximal cliques, remove these edges
void resetIntrapartiteEdges(vector < vector <int> > &matrix)
{
	for(int i = 0; i < matrix.size(); i++)
	{
		for(int j = 0; j < matrix[i].size(); j++)
		{
			if(matrix[i][j] == 3)
				matrix[i][j] = 0;
		}
	}
}

//addIntrapartiteEdges - takes a matrix and the bounds of each partite set
//Adds the intrapartite edges to the graphs as 2's instead of 1's so we can remove
//these edges later if needed. These edges are needed for the maximal clique finding to work.

void addIntrapartiteEdges(vector <vector < int> > &matrix, vector <set<int> >& partiteSets)
{
	set<int>::iterator j,k;

	for(int i = 0; i < partiteSets.size(); i++)
	{
		j=partiteSets[i].begin();
		while(j!=partiteSets[i].end())
		{
			k=j;
			k++;
			while (k!=partiteSets[i].end())
			{
				matrix[*j][*k]=2;
				matrix[*k][*j]=2;
				k++;
			}
			j++;
		}
	}
}


