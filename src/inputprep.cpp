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
using namespace std;


//resetIntrapartiteEdges - for every intrpartitie edge added to the nodes in every 
//partite sets for finding maximal cliques, remove these edges
void resetIntrapartiteEdges(vector < vector <int> > &matrix)
{
	for(int i = 0; i < matrix[0].size(); i++)
	{
		for(int j = 0; j < matrix[0].size(); j++)
		{
			if(matrix[i][j] == 2)
				matrix[i][j] = 0;
		}
	}
}

//addIntrapartiteEdges - takes a matrix and the bounds of each partite set
//Adds the intrapartite edges to the graphs as 2's instead of 1's so we can remove
//these edges later if needed. These edges are needed for the maximal clique finding to work.

void addIntrapartiteEdges(vector <vector < int> > &matrix, vector <int> partiteSets)
{
	for(int i = 0; i < partiteSets.size(); i++)
	{
		if(i+1 < partiteSets.size())
		{
			int cap = partiteSets[i+1];
			for(int a  = partiteSets[i]; a < cap; a++)
			{
				for(int b = partiteSets[i]; b < cap; b++)
				{
					//do not add self edges
					if(a != b)
					{
						matrix[a][b] = 2;
						matrix[b][a] = 2;
					}
				}
			}	

		}
		//last column of each row is a special case
		else
		{
			for(int a = partiteSets[i]; a < matrix[0].size(); a++)
			{
				for(int b = partiteSets[i]; b < matrix[0].size(); b++)
				{
					//do not add self edges
					if(a != b)

					{
						matrix[a][b] = 2;
						matrix[b][a] =2;
					}
				}
			}

		}
	}

}


