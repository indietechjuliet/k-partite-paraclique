/* Author: Rachel Offutt, University of Tennessee
*This file contains the the necessary functions needed for the enumerate() subroutine
*to caculate the k-partite maximal cliques
*Date Last Modified: Nov. 13, 2020
*/


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include<bits/stdc++.h>
#include "helper.h"
#include "enumerate.h"
#include "inputprep.h"
#include "paraclique.h"
using namespace std;


/*Enumerate() is the main subroutine of this program. Input: a graph G=(V,E) as an adjecency 
*matrix ("matrix"), a set of vertices (R) that covers the partite sets, two disjoint sets (P and X),
*a list of the partite set boundaries (parititeSets) used for checking if R covers all partiteSets,
*and an output stream for outputting maximal cliques (fout)
*/
void enumerate(vector <vector <int > > matrix, vector <int> R, vector <int> P, vector <int> X, vector <int> partiteSets, multimap<int,vector <int>> &cliques )
{
	//If there are no more vertices that can extend the clique
	if(P.size() == 0 && X.size() == 0)
	{
		//outtput maximal clique to the output file
		if(coverPartition(R, partiteSets) && allConnected(R,matrix))
		{
			cliques.insert(make_pair(R.size(), R));
	
		}
		return;
	}
	//Choose a pivots (or pivots) that maximize P U X | N(pivot)
	vector <int>  pivot = choosePivot(P, X, matrix);
	if (pivot.size() > 0)
	{
		for(int f =0; f < pivot.size(); f++)
		{
			for(int v = 0; v < matrix[pivot[f]].size(); v++)
			{
				vector <int>::iterator it;
				it = find(P.begin(), P.end(), v);
				if(it != P.end() && matrix[pivot[f]][v]  == 0)
				{


					vector <int> PnNv = intersection(P, matrix[v]);
					vector <int> XnNv = intersection(X, matrix[v]);
					R.push_back(v);
					enumerate(matrix, R, PnNv, XnNv, partiteSets, cliques);
					P.erase(it);
					X.push_back(v);
					R.pop_back();
				}
			}
		}
	}

}

//allConnected - determine if a set R is a clique and covers all partitie sets
bool allConnected(vector <int> R, vector <vector <int > > matrix)
{
        for(int i = 0; i < R.size(); i++)
        {
                for(int j = i+1; j < R.size(); j++)
                {
                        if(matrix[R[i]][R[j]] == 0)
                                return false;
                }
        }
        return true;
}

//Intersection - returns the intersection o two sets
vector <int> intersection( vector <int> setA, vector <int> matrixRow)
{
	vector <int>::iterator it;

	vector <int> intersect;
	for(int i = 0; i < matrixRow.size(); i++)
	{
		it = find(setA.begin(), setA.end(), i);
		if(it != setA.end() && matrixRow[i] == 1)
		{
			intersect.push_back(i);
		}
	}
	return intersect;
}
/*ChoosePivot - Choose vertice(s) that maximize P U X | N(pivot)
*/
vector <int> choosePivot(vector <int> P , vector <int> X, vector < vector <int >> matrix)
{
	vector <int> PuX;

	PuX = P;

	vector <int> pivot;
	vector <pair < int, int> > temp;
	vector<int>::iterator it;
	
	//Union P and X together into a new vector
	for(int i = 0; i < X.size(); i++)
	{
		it  = find(PuX.begin(), PuX.end(), X[i]);
		if(it == PuX.end())
			PuX.push_back(X[i]);
	}

	//If there is only one possible vertex, chose as the pivot and return
	if(PuX.size() == 1)
	{
		pivot.push_back(PuX[0]);
		return pivot;
	}
	
	//Loop through P U X, and keep track of the number that maximizes P U X | N(pivot)
	//(we keep track but lop back through later to get the pivots because there could be
	//several pivots that maximize P U X | N(pivot)
	int maxcount = 0;
	for(int u = 0; u < PuX.size(); u++)
	{
		vector <int> Nu = matrix[PuX[u]];
		int count  = 0;
		for(int n = 0; n < Nu.size(); n++)
		{
			it = find(P.begin(), P.end(), n);
			if(Nu[n] != 0 && it != P.end())
				count++;
		}

		temp.push_back(make_pair(PuX[u], count));
		if(count >= maxcount)
		{
			maxcount = count;
		}

	}

	//for every pivot that maximizes P U X | N(pivot), add to the pivot vector.
	//We need to check all that have the same maximize value
	for(int i = 0; i < temp.size(); i++)
	{
		if(temp[i].second == maxcount)
		{
			pivot.push_back(temp[i].first);
		}
	}
	return pivot;
}

/*coverPartition() - takes a clique and the boundaries of each disjoint set in the graph
*Output: returns true or false if the clique covers all partite sets of the graph
*/
int coverPartition(vector <int> R, vector <int> partiteSets)
{
	
	vector <int> found;
	found.resize(partiteSets.size(), 0);
	for(int i = 0; i < partiteSets.size(); i++)
	{
		if(i+1 < partiteSets.size())
		{
			for(int node = 0; node < R.size(); node++)
			{
				if (R[node] > partiteSets[i] && R[node] < partiteSets[i+1])
				{
					if(found[i] ==1)
					{

					}
					found[i] = 1;
					break;
				}

			}

		}
		else
		{
			for(int node = 0; R.size(); node++)
			{
				if(R[node] > partiteSets[i])
				{
					found[i] = 1;
					break;
				}
			}

		}
	}

	for(int i = 0; i < found.size(); i++)
	{
		if(found[i] == 0)
			return false;
	}
	return true;

}


