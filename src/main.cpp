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
#include <sstream>
#include<bits/stdc++.h>
#include "helper.h"
#include "enumerate.h"
#include "inputprep.h"
#include "paraclique.h"

using namespace std;



void split(vector<string>& v, const char* s, char c)
{
  v.clear();
  while (true)
  {
    const char* begin = s;

    while (*s != c && *s) { ++s; }

    v.push_back(string(begin, s));

    if (!*s) break;

    if (!*++s) break;
  }

  if (*--s == c)                            //if last character is c, append another empt$
    v.push_back("");
}



int main(int argc, char* argv[])
{
		//Must have input file name, number of partite sets, and at least one partite set group
	if(argc < 3)
	{
		cerr<<"Invalid number of command line arguments. Please see github documentation\n"<<
		"for correct command line examples.\n";
		return -1;
	}
	multimap <int,vector <int> > cliques;

	//Variables to store the number of partities, number of vertices, and edges
	//int partites = stoi(argv[2]);
	int glom = stoi(argv[2]);
	int vertices = 0;
	int edges = 0;

	//vectors need for the enumerate subroutine
	vector < vector <int>> matrix;
	vector <int> partiteSets;
	vector <int> P;
	vector <int> R;
	vector < int> X;

	
	Graph g;
	//opening input file and error checking
	ifstream fin;
	fin.open(argv[1]);
	if(!fin)
	{
		cerr<<"File "<<argv[1]<<" does not  exist. Exiting now.\n";
		return -1;
	}


	std::vector<string> v;
	string line;
	getline(fin,line);
	split(v,line.c_str(),'\t');
	int num_partite_sets=v.size()-1;
	cout<<"number of partite sets: "<<num_partite_sets<<"\n";
	g.partiteSets.resize(num_partite_sets);
	int numV=0;
	for (int i = 0; i < v.size()-1; ++i)
	{
		numV+=stoi(v[i]);
	}
	vertices=numV;
	cout<<"number of vertices "<<vertices<<"\n";
	edges=stoi(v[v.size()-1]);
	int k=0;
	int v1,v2;
	bool v1_done, v2_done;
	g.matrix.resize(vertices);
	P.resize(vertices);
	for(int i = 0; i < vertices; i++)
		g.matrix[i].resize(vertices, 0);

	for(int i = 0; i < P.size(); i++)
		P[i] = i;
	
	while(getline(fin, line)){
		split(v,line.c_str(),'\t');
		v1_done=v2_done=false;
		for (int i = 0; i < v.size(); ++i)
		{
			//cout<<v[i]<<" ";
			if (v[i]!="" && !v1_done)
			{
				v1=i;
				v1_done=true;
			}
			else if(v[i]!="" && !v2_done)
			{
				v2=i;
				v2_done=true;
			}
		}
		//cout<<"\n";
		//cout<<v1<<" "<<v2<<"\n";
		//cout<<v[v1]<<" "<<v[v2]<<"\n";
		if (g.int_map.find(v[v1])==g.int_map.end())
		{
			g.int_map.insert(make_pair(v[v1],k));
			g.label_map.insert(make_pair(k,v[v1]));
			k++;
		}
		if (g.int_map.find(v[v2])==g.int_map.end())
		{
			g.int_map.insert(make_pair(v[v2],k));
			g.label_map.insert(make_pair(k,v[v2]));
			k++;
		}
		g.partiteSets[v1].insert(g.int_map[v[v1]]);
		g.partiteSets[v2].insert(g.int_map[v[v2]]);
		g.matrix[g.int_map[v[v1]]][g.int_map[v[v2]]]=1;
		g.matrix[g.int_map[v[v2]]][g.int_map[v[v1]]]=1;

	}
	//cout<<"read graph\n";
	//read in vertices and edges
	//printMatrix(g.matrix);
	


	//add intrapartite edges to adjacency matrix
	addIntrapartiteEdges(g.matrix, g.partiteSets);
	//print_matrix_label(g.matrix,g.label_map);
	//cout<<"added intrapartite edges\n";
	//call enumerate subroutine
	enumerate(g.matrix, R, P, X, g.partiteSets, cliques);
	//cout<<"finished enumerating\n";

	vector <int> paraclique;
	int maxcliquesize = cliques.rbegin()->first;
	//cout<<"finished getting maxcliquesize\n";
	//resetIntrapartiteEdges(g.matrix);
	//cout<<"finished reseting inrapartite edges\n";
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
			fout<<num_partite_sets<<"-partite clique before imputed edges:\n";
			for(int i = 0; i < paraclique.size(); i++)
				fout<<g.label_map[paraclique[i]]<<" ";
			fout<<'\n';
			//cout<<"computing paraclique\n";
			computeParaclique(glom, paraclique, g.matrix);
			//cout<<"done computing paraclique\n";
			printParacliqueandImputed(paraclique, g, fout);
			fout<<endl<<endl;
			resetIntrapartiteEdges(g.matrix);
		}
	}
	
	
	fout.close();
	cout<<"Maximum paraclique and Imputed edges in "<<outname<<'\n';
}

