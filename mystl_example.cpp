///\file mystl_example.cpp
///\brief Contains a simple example program that tells if a string is a postfix of 
///another one combining three simpler algorithms from MySTL library
#include <iostream>
#include <iterator>
#include "mystl.h"

int main () {
	//space for a string
	std::string word;

	std::cout<<std::endl<<"Insert 2 string sequnces, I'll check if 2 if postfix of 1"<<std::endl;
	std::cout<<"Seq 1: separate strings with ENTER (end with STOP)"<<std::endl;
	//creating a list l and reading the content from stdin
	mystl::MyVector<std::string> v;
	while (std::cin >> word && word!="STOP") {
		v.push_back(word);
    }

	std::cout<<"Seq 2: separate strings with ENTER (end with STOP)"<<std::endl;
	//creating a vector v containing abcdef as separated chars
	mystl::MyList<std::string> l;
	while (std::cin >> word && word!="STOP") {
        l.push_back(word);
    }
	
	//looking for l inside v
	mystl::MyVector<std::string>::iterator position=mysearch(v.begin(), v.end(), l.begin(), l.end());

	if (position!=v.end()){//l was found
		//tell if the terminal substrings are equal in length
		if(mylength (position, v.end())==mylength (l.begin(), l.end())){
			//tell if the terminal substrings are equal in content
			if(myequal(position, v.end(), l.begin())){
				std::cout<<"Sequence 2 is a postfix of 1"<<std::endl;
				return 0;
			}
		}
	}
	std::cout<<"Sequence 2 is NOT a postfix of 1"<<std::endl;
}
