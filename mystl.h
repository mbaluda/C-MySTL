///\file mystl.h
///\brief Unifies all the library headers.
///
///This is the only header you need to include in your code to use the whole MySTL library in your project

#ifndef MYSTL
#define MYSTL

#include "mylist.h"
#include "myvector.h"
#include "myalgorithms.h"

#endif

/**\mainpage MySTL Project

\author Mauro Baluda (matr.038208)\n mauro@bglug.it
 
\section intro_sec 1 Introduction
 
This project is meant as an exercise in C++ template programming.\n
My goal was to mimic a little part of the Standard Template Library [1] duplicating the behavior of some of it's containers, iterators and generic algorithms.
 
\section implementation_sec 2 Implementation
The code of a template-based program must be included in the header files because the compiler needs to know some implementation details to manage the parametric types.\n
I created a file named mystl.h that aggregates all the header files, it can be included in an end-user program to obtain all the necessary declarations at once.

\subsection containers 2.1 Containers
I decided to recreate two of the most used containers: vector and list. Their peculiar functions and behavior where implemented following the Standard specification as found in [2]. The standard also contains some performance requirements to which I adhered.

related files: mylist.h, myvector.h
 
\subsection iterators 2.2 Iterators
I implemented direct and reverse iterators for the two containers (bidirectional for lists, random access for vectors) together with most of the required functions and operators.
I decided to design them as inner classes, I avoided to inherit from common virtual classes thus reducing the performance payoff caused by virtual function calls. Interesting considerations about different possible options in iterators design can be found in [2] cap.16.2.

related files: mylist.h, myvector.h

\subsection algorithms 2.3 Algorithms
I implemented a basic version of 4 functions included with the Standard Library: length(), find(), equal() and search(). They operate on iterators thus beeing completely independent from the actual container chosen to store the data.
 
To give a "real world" example of the powerfulness of this generic programming approach, I included a simple version of an algorithm called "Levenshtein distance" which is used, for example, in bioinformatics to compare couples of biological sequences.\n 
In the past I took part in a project called ALiBio implementing a much more sophisticated variant of this distance algorithm, that time I used a c-style approach which lead me to a less generic implementation.

related files: myalgorithms.h

A simple example program combining some of the above algorithms is given in mystl_example.cpp

\section testing_sec 3 Testing
\subsection unit 3.1 Unit tests
Every single component implemented in this project have been tested extensively using a free software tool named cppunit [3].

To compile and execute the tests you need to use the command 'make test'

related files: mystl_test.h, mystl_test.cpp
 
\subsection memory 3.2 Memory management tests
To avoid memory management problems that can arise using a language as powerfull as c++ is, I used a memory analysis tool called Valgrind [4] which proved to be very useful in the debugging phase.

To execute the memory tests you need to use the command 'make memtest'
 
\section documentation_sec 4 Documentation
The project and the code documentation was written using doxygen [5] a multi-language documentation system.

To generate the documentation you need to use the command 'make doc'

\section links 5 Resources
[1] Standard Templete Library 
http://en.wikipedia.org/wiki/Standard_Template_Library

[2] The C++ Programming Language/Bjarne Stroustrup - 3rd Edition 
http://www.research.att.com/~bs/3rd.html

[3] CppUnit unit testing framework
http://cppunit.sourceforge.net/

[4] Valgrind debugging and profiling tools
http://valgrind.org/

[5] Doxygen multilanguage documentation system
http://www.stack.nl/~dimitri/doxygen/
*/
