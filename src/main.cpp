/*Author: Rachel Offutt - University of Tennessee
*
*Main function of the program, take in command line arguetns, and reads in the 
*graph into an adjacency matrix
*
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
#include "helper.h"
#include "enumerate.h"
#include "inputprep.h"
#include "paraclique.h"
using namespace std;


int main(int argc, char* argv[])
{
		//Must have input file name, number of partite sets, and at least one partite set group
	if(argc < 5)
	{
		cerr<<"Invalid number of command line arguments. Please see github documentation\n"<<
		"for correct command line examples.\n";
		return -1;
	}
	multimap <int,vector <int> > cliques;

	//Variables to store the number of partities, number of vertices, and edges
	int partites = stoi(argv[2]);
	int glom = stoi(argv[3]);
	int vertices = 0;
	int edges = 0;

	//vectors need for the enumerate subroutine
	vector < vector <int>> matrix;
	vector <int> partiteSets;
	vector <int> P;
	vector <int> R;
	vector < int> X;

	//loop to read in partite set boundaries
	for (int i = 0; i < partites; i++)
	{
		string l = argv[i+4];
		stringstream ss(l);

		int min, max;
		char trash;

		ss>>min>>trash>>max;

		partiteSets.push_back(min);

	}
	

	//opening input file and error checking
	ifstream fin;
	fin.open(argv[1]);
	if(!fin)
	{
		cerr<<"File "<<argv[1]<<" does not  exist. Exiting now.\n";
		return -1;
	}

	string line;
	
	//read in vertices and edges
	while(getline(fin, line)){
		stringstream ss(line);
		if(vertices == 0)
		{
			ss>>vertices>>edges;
			matrix.resize(vertices);
			P.resize(vertices);
			for(int i = 0; i < vertices; i++)
				matrix[i].resize(vertices, 0);
			for(int i = 0; i < P.size(); i++)
				P[i] = i;
		}
		else
		{
			int node1, node2;
			ss>>node1>>node2;

			matrix[node1][node2] = 1;
			matrix[node2][node1] = 1;

		}

	}

	//add intrapartite edges to adjacency matrix
	addIntrapartiteEdges(matrix,  partiteSets);

	//call enumerate subroutine
	enumerate(matrix, R, P, X, partiteSets, cliques);
	

	vector <int> paraclique;
	int maxcliquesize = cliques.rbegin()->first;

	resetIntrapartiteEdges(matrix);

	//opening output file
	string outname = argv[1];
	ofstream fout;
	outname = outname.substr(0, outname.size()-4);
        outname += "_paraclique.txt";
	fout.open(outname);
	
	multimap <int, vector <int > >::iterator it;
	it = cliques.begin();
	
	//for all maximal cliques, compute the paraclique with a glom factor,  print all of them
	for(it = cliques.begin(); it != cliques.end(); it++)
	{
		if(it->first >= maxcliquesize)
		{
			paraclique = it->second;
			fout<<"Paraclique before imputed edges:\n";
			for(int i = 0; i < paraclique.size(); i++)
				fout<<paraclique[i]<<" ";
			fout<<'\n';
			computeParaclique(glom, paraclique, matrix);

			printParacliqueandImputed(paraclique, matrix, fout);
			fout<<endl<<endl;
		}
	}
	
	
	fout.close();
	cout<<"Maximum paraclique and Imputed edges in "<<outname<<'\n';
}

