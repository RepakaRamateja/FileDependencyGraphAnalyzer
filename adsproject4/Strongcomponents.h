/////////////////////////////////////////////////////////////////////////
// Strongcomponents.h - it contains all the operations of the graph    //
//                                                                     //
// Language:    Visual C++ 2012                                        //
// Platform:    Lenova ThinkPad E420s, Windows 7                       //
// Application: File dependency graph Analyzer - ADS, Pr#4, Spring 2017//
// Author:       repaka ramateja,            Syracuse University       //
//              (315) 395-9575, rrepaka@syr.edu                        //
//                                                                      //
/////////////////////////////////////////////////////////////////////////

#pragma once
#include<vector>
#include<string>
#include<unordered_map>
#include<iostream>
#include"graph.h"

class strongcomponent
{
	std::unordered_map <std::string, std::vector<std::string>> store;
	std::unordered_map<std::string, int> map;
	std::vector<std::string> listvector;
public:

	//<--------------sets the given unordered map to the class instance variable----------------->
	void setunorderedmap(std::unordered_map <std::string, std::vector<std::string>> obj)
	{
		store = obj;
		initializevectorlist();
	}

	//<----------initialize of the vector list--------------->
	void initializevectorlist()
	{
		for (std::unordered_map <std::string, std::vector<std::string>>::const_iterator iter = store.begin(); iter != store.end(); ++iter)
		{
			listvector.push_back(iter->first);
		}
    }

	//<--------initialization of the graph------------->
	void initializegraph()
	{
		std::cout << "\ninitialize of graph\n";
		
		for (size_t i = 0; i < listvector.size(); i++)
		{
			map[listvector[i]] = i;
		}

		int k = listvector.size();
		Graph g(k);
		std::vector<std::string> depenlist;
		for (size_t i = 0; i < listvector.size(); i++)
		{
			std::string v = listvector[i];
			int iv = 100;
			std::unordered_map<std::string, int>::const_iterator got = map.find(v);

			if (got == map.end())
			{
				//std::cout << "not found";
			}
			else
			{
				iv = got->second;
			}


			std::unordered_map<std::string, std::vector<std::string>>::const_iterator got2 = store.find(listvector[i]);
			if (got2 == store.end())
			{
				//std::cout << "not found";
			}
			else
			{
				depenlist = got2->second;
			}

			int iv2 = 100;
			for (size_t i = 0; i < depenlist.size(); i++)
			{

				std::unordered_map<std::string, int>::const_iterator got2 = map.find(depenlist[i]);
				if (got2 == map.end())
				{
					//std::cout << "not found";
				}
				else
				{
					iv2 = got2->second;
					g.addEdge(iv, iv2);
				}

			}
		}

		std::cout << "\nthe vertex in the graph  are\n";
		std::cout << "\n";
		g.DFS(map);
		g.printSCCs(map);
		if (g.isCyclic())
		{
			std::cout << "\n graph contains a cycle\n";
			std::cout << "\n so topological sort is not possible\n";
		}
		else
		{
			displaytopologicalsort(g, map);
		}
		
		std::cout << "\n";
	}

	//<-----------used for displaying the topological sort---------------->
	void displaytopologicalsort(Graph g, std::unordered_map<std::string, int> map)
	{
		std::cout << "\nThe vertices are in the below order after doing topological sorting\n";
		g.topologicalSort(map);
		std::cout << "\n";
	}

	


};

