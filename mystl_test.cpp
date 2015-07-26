///\file mystl_test.cpp
///\brief Contains test implementations for cppunit

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

#include "mystl_test.h"

using namespace mystl;
///\brief Running the test suites
int main () {
    // informs test-listener about testresults
    CPPUNIT_NS :: TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS :: TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS :: TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS :: TestFactoryRegistry :: getRegistry ().makeTest ());
    testrunner.run (testresult);

    // output results in compiler-format
    CPPUNIT_NS :: CompilerOutputter compileroutputter (&collectedresults, std::cerr);
    compileroutputter.write ();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful () ? 0 : 1;
}

///\brief Testing MyList implementation
CPPUNIT_TEST_SUITE_REGISTRATION (mylisttest);

///Prepares the test environment
void mylisttest :: setUp (void) {
    const std::string fileName("numeri.txt");
    std::fstream f(fileName.c_str());
    if (!f.is_open()) {
        std::cerr << "Il file " << fileName << " non esiste\n";
        return;
    }
    std::string word;
    while (f >> word) { //operator>> si ferma al primo spazio
        l.push_back(word);
        inv_l.push_front(word);
    }
}

///Cleanes the test environment
void mylisttest :: tearDown (void) {
    // no need to delete anything
}

///Tests the constructors
void mylisttest :: constructorTest (void) {
    mystl::MyList<std::string> newl;
    CPPUNIT_ASSERT (newl.empty());

    mystl::MyList<std::string> copyl(l);

    //tests for same content in different objects
    MyList<std::string>::iterator it1 = l.begin();
    MyList<std::string>::iterator it2 = copyl.begin();
    while (it1++ != l.end() && it2++ != copyl.end()) {
        CPPUNIT_ASSERT_EQUAL (*it1, *it2);
        CPPUNIT_ASSERT (it1 != it2);
    }
}

///Tests the operator =
void mylisttest :: assignTest (void) {
    mystl::MyList<std::string> copyl;
    copyl.push_back("element to be erased");

    copyl=l;

    //tests for same content in different objects
    MyList<std::string>::iterator it1 = l.begin();
    MyList<std::string>::iterator it2 = copyl.begin();
    while (it1++ != l.end() && it2++ != copyl.end()) {
        CPPUNIT_ASSERT_EQUAL (*it1, *it2);
        CPPUNIT_ASSERT (it1 != it2);
    }
}

///Tests empty() and clear() methods
void mylisttest :: emptyTest (void) {
    CPPUNIT_ASSERT (emptyl.empty());
    CPPUNIT_ASSERT (!l.empty());
    l.clear();
    CPPUNIT_ASSERT (l.empty());
}

///Tests size() method
void mylisttest :: sizeTest (void) {
    CPPUNIT_ASSERT_EQUAL (l.size(), 11);
    l.push_back("undici");
    CPPUNIT_ASSERT_EQUAL (l.size(), 12);
    l.pop_front();
    CPPUNIT_ASSERT_EQUAL (l.size(), 11);
}

///Tests push_front() pop_front() and front() methods
void mylisttest :: ppfTest (void) {
    std::string orig_value=l.front();
    l.push_front("menouno");
    CPPUNIT_ASSERT_EQUAL (l.front(), std::string("menouno"));
    l.pop_front();
    CPPUNIT_ASSERT_EQUAL (l.front(), orig_value);
}

///Tests push_back pop_back and back methods
void mylisttest :: ppbTest (void) {
    std::string orig_value=l.back();
    l.push_back("undici");
    CPPUNIT_ASSERT_EQUAL (l.back(), std::string("undici"));
    l.pop_back();
    CPPUNIT_ASSERT_EQUAL (l.back(), orig_value);
}

///Tests iterator class
void mylisttest :: iteratorTest (void) {
    std::string str;
    for (MyList<std::string>::iterator it = l.begin(); it != l.end(); ++it) {
        str.append(*it);
        str.append(" ");
    }
    CPPUNIT_ASSERT_EQUAL (str, std::string("zero uno due tre quattro cinque sei sette otto nove dieci "));

    std::string inv_str;
    for (MyList<std::string>::iterator it = inv_l.begin(); it != inv_l.end(); ++it) {
        inv_str.append(*it);
        inv_str.append(" ");
    }
    CPPUNIT_ASSERT_EQUAL (inv_str, std::string("dieci nove otto sette sei cinque quattro tre due uno zero "));
}

///Tests reverse_iterator class
void mylisttest :: reverse_iteratorTest (void) {
    std::string str;
    for (MyList<std::string>::reverse_iterator it = l.rbegin(); it != l.rend(); ++it) {
        str.append(*it);
        str.append(" ");
    }
    CPPUNIT_ASSERT_EQUAL (str, std::string("dieci nove otto sette sei cinque quattro tre due uno zero "));

    std::string inv_str;
    for (MyList<std::string>::reverse_iterator it = inv_l.rbegin(); it != inv_l.rend(); ++it) {
        inv_str.append(*it);
        inv_str.append(" ");
    }
    CPPUNIT_ASSERT_EQUAL (inv_str, std::string("zero uno due tre quattro cinque sei sette otto nove dieci "));
}

///Test exceptional behaviour
void mylisttest :: exceptionTest (void) {
    CPPUNIT_ASSERT_THROW (emptyl.front(), std::out_of_range);
    CPPUNIT_ASSERT_THROW (emptyl.back(), std::out_of_range);
}

///brief Testing MyVector implementation
CPPUNIT_TEST_SUITE_REGISTRATION (myvectortest);

///Prepares the test environment
void myvectortest :: setUp (void) {
    const std::string fileName("numeri.txt");
    std::fstream f(fileName.c_str());
    if (!f.is_open()) {
        std::cerr << "Il file " << fileName << " non esiste\n";
        return;
    }
    std::string word;
    while (f >> word) {
        v.push_back(word);
    }
}

///Cleanes the test environment
void myvectortest :: tearDown (void) {
    // no need to delete anything
}

///Tests the constructors
void myvectortest :: constructorTest (void) {
    mystl::MyVector<std::string> newv;
    CPPUNIT_ASSERT (newv.empty());

    mystl::MyVector<std::string> copyv(v);

    //tests for same content in different objects
    MyVector<std::string>::iterator it1 = v.begin();
    MyVector<std::string>::iterator it2 = copyv.begin();
    while (it1++ != v.end() && it2++ != copyv.end()) {
        CPPUNIT_ASSERT_EQUAL (*it1, *it2);
        CPPUNIT_ASSERT (it1 != it2);
    }
}

///Tests the operator =
void myvectortest :: assignTest (void) {
    mystl::MyVector<std::string> copyv;
    copyv.push_back("element to be erased");

    copyv=v;

    //tests for same content in different objects
    MyVector<std::string>::iterator it1 = v.begin();
    MyVector<std::string>::iterator it2 = copyv.begin();
    while (it1++ != v.end() && it2++ != copyv.end()) {
        CPPUNIT_ASSERT_EQUAL (*it1, *it2);
        CPPUNIT_ASSERT (it1 != it2);
    }
}

///Tests empty() and clear() methods
void myvectortest :: emptyTest (void) {
    CPPUNIT_ASSERT (emptyv.empty());
    CPPUNIT_ASSERT (!v.empty());
    v.clear();
    CPPUNIT_ASSERT (v.empty());
}

///Tests size() reserve() and capacity() methods
void myvectortest :: sizeTest (void) {
    CPPUNIT_ASSERT_EQUAL (v.size(), 11);
    v.push_back("undici");
    CPPUNIT_ASSERT_EQUAL (v.size(), 12);
    CPPUNIT_ASSERT (v.capacity()>=v.size());
    v.reserve(30);
    CPPUNIT_ASSERT (v.capacity()>=30);
}

///Tests front() method ad operator[]
void myvectortest :: ppfTest (void) {
    CPPUNIT_ASSERT_EQUAL (v.front(), std::string("zero"));
    CPPUNIT_ASSERT_EQUAL (v[0], std::string("zero"));
    v[5]=std::string("modificato");
    CPPUNIT_ASSERT_EQUAL (v[5], std::string("modificato"));
}

///Tests push_back pop_back and back methods
void myvectortest :: ppbTest (void) {
    std::string orig_value=v.back();
    v.push_back("undici");
    CPPUNIT_ASSERT_EQUAL (v.back(), std::string("undici"));
    v.pop_back();
    CPPUNIT_ASSERT_EQUAL (v.back(), orig_value);
}

///Tests iterator class
void myvectortest :: iteratorTest (void) {
    std::string str;
    for (MyVector<std::string>::iterator it = v.begin(); it != v.end(); ++it) {
        str.append(*it);
        str.append(" ");
    }
    CPPUNIT_ASSERT_EQUAL (str, std::string("zero uno due tre quattro cinque sei sette otto nove dieci "));
}

///Tests reverse_iterator class
void myvectortest :: reverse_iteratorTest (void) {
    std::string str;
    for (MyVector<std::string>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
        str.append(*it);
        str.append(" ");
    }
    CPPUNIT_ASSERT_EQUAL (str, std::string("dieci nove otto sette sei cinque quattro tre due uno zero "));
}

///Test exceptional behaviour
void myvectortest :: exceptionTest (void) {
    CPPUNIT_ASSERT_THROW (emptyv.front(), std::out_of_range);
    CPPUNIT_ASSERT_THROW (emptyv.back(), std::out_of_range);
    CPPUNIT_ASSERT_THROW (emptyv.pop_back(), std::out_of_range);
}

///\brief Testing MySTL algorithms
CPPUNIT_TEST_SUITE_REGISTRATION (myalgorithmstest);

///Prepares the test environment
void myalgorithmstest :: setUp (void) {
    const std::string fileName("numeri.txt");
    std::fstream f(fileName.c_str());
    if (!f.is_open()) {
        std::cerr << "Il file " << fileName << " non esiste\n";
        return;
    }
    std::string word;
    while (f >> word) {
        v.push_back(word);
        l.push_front(word);
    }
}

///Cleanes the test environment
void myalgorithmstest :: tearDown (void) {
    // no need to delete anything
}

///Tests myfind() method
///using direct and reverse iterators on MyList and MyVector
///considering found and not-found results
void myalgorithmstest :: myfindTest (void) {
    MyVector<std::string>::iterator it;
    it = myfind(v.begin(), v.end(), std::string("due"));
    CPPUNIT_ASSERT_EQUAL(*it,v[2]);
    it = myfind(v.begin(), v.end(), std::string("sei"));
    CPPUNIT_ASSERT_EQUAL(*it,v[6]);
    it = myfind(v.begin(), v.end(), std::string("undici"));
    CPPUNIT_ASSERT (it==v.end());

    MyVector<std::string>::reverse_iterator rit;
    rit = myfind(v.rbegin(), v.rend(), std::string("due"));
    CPPUNIT_ASSERT_EQUAL(*rit,v[2]);

    MyList<std::string>::iterator it2;
    it2= myfind(l.begin(), l.end(), std::string("dieci"));
    CPPUNIT_ASSERT_EQUAL(*it2,l.front());
    it2 = myfind(l.begin(), l.end(), std::string("zero"));
    CPPUNIT_ASSERT_EQUAL(*it2,l.back());

    MyList<std::string>::reverse_iterator rit2;
    rit2= myfind(l.rbegin(), l.rend(), std::string("dieci"));
    CPPUNIT_ASSERT_EQUAL(*rit2,l.front());
}

///Tests myequal() method
void myalgorithmstest :: myequalTest (void) {
    ///Test on an empty container
    CPPUNIT_ASSERT(myequal(emptyv.begin(), emptyv.end(), emptyl.begin()));

    ///Test on a single type of container
    CPPUNIT_ASSERT(myequal(l.begin(), l.end(), l.begin()));

    mystl::MyList<std::string> l1;
    l1.push_back(std::string("zero"));
    l1.push_back(std::string("uno"));
    l1.push_back(std::string("due"));

    ///Test on different kind of container
    CPPUNIT_ASSERT(myequal(l1.begin(), l1.end(), v.begin()));

    ///Test for disequality
    l1.push_back(std::string("sei"));
    CPPUNIT_ASSERT(!myequal(l1.begin(), l1.end(), v.begin()));
}

///Tests mysearch() method
///with different containers and iterators
void myalgorithmstest :: mysearchTest (void) {
    mystl::MyList<std::string> l1;
    l1.push_back(std::string("sei"));
    l1.push_back(std::string("sette"));
    l1.push_back(std::string("otto"));

    ///Positive searches
    CPPUNIT_ASSERT(mysearch(v.begin(), v.end(), l1.begin(), l1.end())==&v[6]);
    CPPUNIT_ASSERT(mysearch(v.rbegin(), v.rend(), l1.rbegin(), l1.rend())==&v[8]);

    l1.push_back(std::string("nove"));
    l1.push_back(std::string("dieci"));
    l1.push_back(std::string("undici"));

    ///Negative searches
    CPPUNIT_ASSERT(mysearch(v.begin(), v.end(), l1.begin(), l1.end())==v.end());
    CPPUNIT_ASSERT(mysearch(v.rbegin(), v.rend(), l1.rbegin(), l1.rend())==v.rend());
}

///Tests myldist() method
void myalgorithmstest :: myldistTest (void) {
    mystl::MyList<char> l;
    l.push_back('G');
    l.push_back('U');
    l.push_back('M');
    l.push_back('B');
    l.push_back('O');

    mystl::MyVector<char> v;
    v.push_back('G');
    v.push_back('A');
    v.push_back('M');
    v.push_back('B');
    v.push_back('O');
    v.push_back('L');

    CPPUNIT_ASSERT_EQUAL(myldist(l.begin(), l.end(), v.begin(), v.end()),2);
}
