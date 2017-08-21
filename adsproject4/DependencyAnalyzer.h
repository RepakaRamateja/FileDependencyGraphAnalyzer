/////////////////////////////////////////////////////////////////////////
// Dependency Analyzer.h - it contains all the operations of the graph //
//                                                                     //
// Language:    Visual C++ 2012                                        //
// Platform:    Lenova ThinkPad E420s, Windows 7                       //
// Application:  Dependency Analysis - Ads, Pr#4, Spring 2017          //
// Author:       repaka ramateja,            Syracuse University       //
//              (315) 395-9575, rrepaka@syr.edu                        //
//                                                                     //
/////////////////////////////////////////////////////////////////////////
#pragma once
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<fstream>

class dependencyanalyzer
{

	std::vector<std::string> fileset;
	std::vector<std::string> packages;
	std::unordered_map <std::string, std::vector<std::string>> store;
	
public:
	
	//<---used to return the unordered map which contain the dependencies------>
	std::unordered_map<std::string, std::vector<std::string>> getmap()
	{
		return store;
	}

	//<----sets the given fileset to the instance variable------------>
	void setfileset(std::vector<std::string> files)
	{
		fileset = files;
		packages = files;
		
	}

	//<--------- used for printing the fileset------------------------>
	void printall()
	{
		std::cout << "\nthe files are \n";
		for (size_t i = 0; i < fileset.size(); i++)
		{
			std::cout << fileset[i];
			std::cout << "\n";
		}

	}

	// -----< replace with old content with the replace content in the given string file_contents >------------
	void replacestring(std::string old, std::string rep, std::string &file_contents)
	{
		for (int pos = 0;
			(pos = file_contents.find(old, pos)) != std::string::npos;
			pos += rep.length())
		{
			file_contents.replace(pos, old.length(), rep);
		}
	}
	
	//<----------- used for inserting a dependency---------------------------------->
	void insertdependency(std::string packagename, std::vector<std::string> listofpackages)
	{
		std::unordered_map<std::string, std::vector<std::string>>::const_iterator got = store.find(packagename);
		if (got == store.end())
		{
			store[packagename] = listofpackages;
		}
		else
		{
			std::vector<std::string> childlist = store[packagename];

			for (size_t i = 0; i < listofpackages.size(); i++)
			{
				std::vector<std::string>::iterator it;
				it = find(childlist.begin(), childlist.end(), listofpackages[i]);
				if (it == childlist.end())
				{
					childlist.push_back(listofpackages[i]);
				}

			}

			store[packagename] = childlist;
		}
	}

	//<--------- get the packagename from the given filename--------------->
	std::string getpackagename(std::string filename)
	{
       
		std::size_t foundh = filename.find(".h");
		std::size_t foundcpp = filename.find(".cpp");

		if (foundh != std::string::npos)
		{
			replacestring(".h", "", filename);
		}

		if (foundcpp != std::string::npos)
		{
			replacestring(".cpp", "", filename);
		}

		return filename;
	}

	//<--------------- used for finding the dependencies------------------------>
	void finddependencies(std::string foldername)
	{
		for (size_t i = 0; i < fileset.size(); ++i)
		{
			std::vector<std::string> childlist;
			std::string packagename = getpackagename(fileset[i]);
			std::string mainpath= foldername +fileset[i];
			std::ifstream in(mainpath);
			if (in)
			{

			}
			else
			{
				std::cout << "\nnot able to open file\n";
			}

			std::string file_contents;
			std::string str;
			while (std::getline(in, str))
			{
				std::size_t found = str.find("#");

				if (found != std::string::npos)
				{
					file_contents += str;
					file_contents.push_back('\n');
				}
			}

			for (size_t i = 0; i < packages.size(); ++i)
			{
				std::size_t found = file_contents.find(packages[i]);
				if (found != std::string::npos)
				{
					std::vector<std::string>::iterator it;
					it = find(childlist.begin(), childlist.end(), packages[i]);
					if (it == childlist.end())
					{
						std::string childpackagename = getpackagename(packages[i]);
						if(childpackagename!=packagename)
						childlist.push_back(childpackagename);
					}

				}

			}

			insertdependency(packagename, childlist);
		}

	}


	//<------------ used for displaying the dependencies------------------->
	void displaydependencies()
	{

		std::cout << "\n the package dependencies identified are\n";
		std::cout << "\n";

		for (std::unordered_map <std::string, std::vector<std::string>>::const_iterator iter = store.begin(); iter != store.end(); ++iter)
		{

			std::cout << iter->first <<"-->"<< "\t";

			for (std::vector<std::string>::size_type i = 0; i < iter->second.size(); i++)
			{
				std::cout << (iter->second)[i]<<"\t";
				
			}
			std::cout << "\n";


		}
	}
};
