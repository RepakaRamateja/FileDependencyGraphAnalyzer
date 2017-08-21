//////////////////////////////////////////////////////////////////////////////////////////
// executive.cpp -  used for demonstration of output for dependency based graph analyzer//
// this package contains all the operations for the creation of html files              //
//--------------------------------------------------------------------------------------//
//                                                                                      //
//--------------------------------------------------------------------------------------//
// Language:    C++, Visual Studio 2015                                                 //
// Platform:    Dell XPS 8900, Windows 7                                                //
// Application: Project #4, ADS - Advanced Data structures, S2017                       //
// Author:      ramteja repaka, Syracuse University                                     //
//              rrepaka@syr.edu                                                         //
//////////////////////////////////////////////////////////////////////////////////////////


#include<iostream>
#include<vector>
#include<string>
#include"direct.h"
#include"DependencyAnalyzer.h"
#include"Strongcomponents.h"


	// this logic we are using to read all the files in the given directory
	std::vector<std::string> open(std::string path) {
		DIR*    dir;
		dirent* pdir;
		std::vector<std::string> files;
		dir = opendir(path.c_str());

		while (pdir = readdir(dir)) {

			files.push_back(pdir->d_name);
		}
		return files;
	}


int main()
{

	std::unordered_map <std::string, std::vector<std::string>> store2;

	dependencyanalyzer analyzer2;

	strongcomponent component2;


	std::cout << "<----------File Dependency Graph Analyzer DEMO ----------->"; 

	std::cout << "\nreading the files from the given folder path\n";

	/* Note : Inputs2 folder contain source files 
	please  change the files in the given directory for testing
	
	----below files doesnot contain a cycle so topological sort is possible
	----if you change the source code files that lead to cycle then topological sort is not possible
	    if you want to test that use path as ../Inputs/

	*/

	
	std::string path2 = "../Inputs/";

	std::vector<std::string> dummy2 = open(path2);

	dummy2.erase(dummy2.begin());
	dummy2.erase(dummy2.begin());

	analyzer2.setfileset(dummy2);

	analyzer2.printall();

	//passing the path variable as input
	analyzer2.finddependencies(path2);

	analyzer2.displaydependencies();

	store2 = analyzer2.getmap();

	component2.setunorderedmap(store2);

	component2.initializegraph();

    return 0;
}