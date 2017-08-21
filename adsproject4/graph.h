/////////////////////////////////////////////////////////////////////////
// Maingraph.h - it contains all the operations of the graph           //
//                                                                     //
// Language:    Visual C++ 2012                                        //
// Platform:    Lenova ThinkPad E420s, Windows 7                       //
// Application: File dependency graph Analyzer - ADS, Pr#4, Spring 2017//
// Author:       repaka ramateja,            Syracuse University       //
//              (315) 395-9575, rrepaka@syr.edu                        //
// Source: geeks for geeks                                             //
/////////////////////////////////////////////////////////////////////////

/*
Package Operations:
==================
this package defines all the operations that are used for:
creating a graph
storing a graph info
finding the strong components
finding the transpose of a graph
creating the stack to maintains the vertex

Public Interface:
=================
Graph g(n) ---creates a graph for n vertices
g.addedge(value1,value2)---- for creating a edge
g.printSCCs(); -- for displaying the strong components


Build Process:
==============
Required files
Maingraph.cpp,executivegraph.cpp

Build commands (either one)
- devenv maingraph.sln

Maintenance History:
====================
ver 1.0 : 13th march 2017
-first release



*/
#pragma once
#include <iostream>
#include <list>
#include <stack>
#include<unordered_map>
#include<string>
using namespace std;

class Graph
{
	int V;    // No. of vertices
	list<int> *adj;    // An array of adjacency lists
	
public:

	std::vector<std::string> vertexlist;//conatins all vertex list obtaining by doing dfs


	Graph(int V)
	{
		this->V = V;
		adj = new list<int>[V];
	}

	// A recursive function to print DFS starting from v
	void DFSUtil(int v, bool visited[], std::unordered_map<std::string, int> map)
	{
		// Mark the current node as visited and print it
		visited[v] = true;
		
		for (auto it = map.begin(); it != map.end(); ++it)
		{
			if (it->second == v)
			{
				std::cout << it->first << "  ";
				
				
			}
		}

		// Recur for all the vertices adjacent to this vertex
		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i)
			if (!visited[*i])
				DFSUtil(*i, visited, map);
	}

	// function which is useful to get the transpose of a graph
	Graph getTranspose()
	{
		Graph g(V);
		for (int v = 0; v < V; v++)
		{
			// Recur for all the vertices adjacent to this vertex
			list<int>::iterator i;
			for (i = adj[v].begin(); i != adj[v].end(); ++i)
			{
				g.adj[*i].push_back(v);
			}
		}
		return g;
	}

	//function which is useful for adding the edge to a given vertices
	void addEdge(int v, int w)
	{
		adj[v].push_back(w); // Add w to v’s list.
	}

	// used for creating a stack which contains all the vertices it is a recursive function
	void fillOrder(int v, bool visited[], stack<int> &Stack)
	{
		// Mark the current node as visited and print it
		visited[v] = true;

		// Recur for all the vertices adjacent to this vertex
		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i)
			if (!visited[*i])
				fillOrder(*i, visited, Stack);

		// All vertices reachable from v are processed by now, push v 
		Stack.push(v);
	}

	// function that is responsible for finding the strong components inside a graph
	void printSCCs(std::unordered_map<std::string, int> map)
	{
		std::cout << "\n";
		std::cout << "\nthe strong components from the above dependency analysis are:\n";
		stack<int> Stack;
		bool *visited = new bool[V];
		for (int i = 0; i < V; i++)
			visited[i] = false;

		for (int i = 0; i < V; i++)
			if (visited[i] == false)
				fillOrder(i, visited, Stack);

		Graph gr = getTranspose();

		for (int i = 0; i < V; i++)
			visited[i] = false;

		while (Stack.empty() == false)
		{
			int v = Stack.top();
			Stack.pop();
			if (visited[v] == false)
			{
				gr.DFSUtil(v, visited, map);
				
				cout << endl;
			}
		}
	}

	// utility function useful for doing topological sort called inside topological sort
	void topologicalSortUtil(int v, bool visited[],
		stack<int> &Stack)
	{
		visited[v] = true;
		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i)
			if (!visited[*i])
				topologicalSortUtil(*i, visited, Stack);

		Stack.push(v);
	}

	// function mainly useful for doing topological sort
	void topologicalSort(std::unordered_map<std::string, int> map)
	{
		stack<int> Stack;
		bool *visited = new bool[V];
		for (int i = 0; i < V; i++)
			visited[i] = false;

		
		for (int i = 0; i < V; i++)
			if (visited[i] == false)
				topologicalSortUtil(i, visited, Stack);
		while (Stack.empty() == false)
		{
			int v = Stack.top();
			for (auto it = map.begin(); it != map.end(); ++it)
			{
				if (it->second == v)
				{
					std::cout << it->first << "  ";
				}
			}
			Stack.pop();
		}
	}

	void displayDFSUtil(int v, bool visited[], std::unordered_map<std::string, int> map)
	{
		
		visited[v] = true;

		for (auto it = map.begin(); it != map.end(); ++it)
		{
			if (it->second == v)
			{
				std::cout << it->first << "  ";


			}
		}

	}

	// function that is useful for doing dfs for printing the vertices
	void DFS(std::unordered_map<std::string, int> map)
	{
		bool *visited = new bool[V];
		for (int i = 0; i < V; i++)
			visited[i] = false;
		for(int v=0;v<V;v++)
			displayDFSUtil(v, visited,map);
	}

	//utility function useful for detecting a cycle
	bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
	{
		if (visited[v] == false)
		{
			
			visited[v] = true;
			recStack[v] = true;

			
			list<int>::iterator i;
			for (i = adj[v].begin(); i != adj[v].end(); ++i)
			{
				if (!visited[*i] && isCyclicUtil(*i, visited, recStack))
					return true;
				else if (recStack[*i])
					return true;
			}

		}
		recStack[v] = false;  
		return false;
	}

	//function that uses iscyclic util and it is the main function for detecting a cycle
	bool Graph::isCyclic()
	{
		// Mark all the vertices as not visited and not part of recursion
		// stack
		bool *visited = new bool[V];
		bool *recStack = new bool[V];
		for (int i = 0; i < V; i++)
		{
			visited[i] = false;
			recStack[i] = false;
		}

		// Call the recursive helper function to detect cycle in different
		// DFS trees
		for (int i = 0; i < V; i++)
			if (isCyclicUtil(i, visited, recStack))
				return true;

		return false;
	}

}; 
