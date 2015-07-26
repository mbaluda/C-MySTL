///\file mystl_test.h
///\brief Contains test declarations for cppunit

#ifndef MYSTLTEST
#define MYSTLTEST

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <fstream>
#include <string>

#include "mystl.h"

///\class mylisttest
///\brief Tests MyList class
class mylisttest : public CPPUNIT_NS :: TestFixture {
    CPPUNIT_TEST_SUITE (mylisttest);
    CPPUNIT_TEST (constructorTest);
    CPPUNIT_TEST (assignTest);
    CPPUNIT_TEST (emptyTest);
    CPPUNIT_TEST (sizeTest);
    CPPUNIT_TEST (ppfTest);
    CPPUNIT_TEST (ppbTest);
    CPPUNIT_TEST (iteratorTest);
    CPPUNIT_TEST (reverse_iteratorTest);
    CPPUNIT_TEST (exceptionTest);
    CPPUNIT_TEST_SUITE_END ();

public:
    ///Prepares the test environment
    void setUp (void);
    ///Cleanes the test environment
    void tearDown (void);

protected:
    ///Tests the copy constructor
    void constructorTest (void);
    ///Tests the operator =
    void assignTest (void);
    ///Tests empty() and clear() methods
    void emptyTest (void);
    ///Tests size() method
    void sizeTest (void);
    ///Tests push_front() pop_front() and front() methods
    void ppfTest (void);
    ///Tests push_back() pop_back() and back() methods
    void ppbTest (void);
    ///Tests iterator class
    void iteratorTest (void);
    ///Tests reverse_iterator class
    void reverse_iteratorTest (void);
    ///Test exceptional behaviour
    void exceptionTest (void);

private:
    mystl::MyList<std::string> l;
    mystl::MyList<std::string> inv_l;
    mystl::MyList<std::string> emptyl;
};

///\class myvectortest
///\brief Tests MyVector class
class myvectortest : public CPPUNIT_NS :: TestFixture {
    CPPUNIT_TEST_SUITE (myvectortest);
    CPPUNIT_TEST (constructorTest);
    CPPUNIT_TEST (assignTest);
    CPPUNIT_TEST (emptyTest);
    CPPUNIT_TEST (sizeTest);
    CPPUNIT_TEST (ppfTest);
    CPPUNIT_TEST (ppbTest);
    CPPUNIT_TEST (iteratorTest);
    CPPUNIT_TEST (reverse_iteratorTest);
    CPPUNIT_TEST (exceptionTest);
    CPPUNIT_TEST_SUITE_END ();

public:
    ///Prepares the test environment
    void setUp (void);
    ///Cleanes the test environment
    void tearDown (void);

protected:
    ///Tests the constructors
    void constructorTest (void);
    ///Tests the operator =
    void assignTest (void);
    ///Tests empty() and clear() methods
    void emptyTest (void);
    ///Tests size() resize() and capacity() methods
    void sizeTest (void);
    ///Tests push_front() pop_front() and front() methods
    void ppfTest (void);
    ///Tests push_back() pop_back() and back() methods
    void ppbTest (void);
    ///Tests iterator class
    void iteratorTest (void);
    ///Tests reverse_iterator class
    void reverse_iteratorTest (void);
    ///Test exceptional behaviour
    void exceptionTest (void);

private:
    mystl::MyVector<std::string> v;
    mystl::MyVector<std::string> emptyv;
};

///\class myalgorithmstest
///\brief Tests MySTL algorithms
class myalgorithmstest : public CPPUNIT_NS :: TestFixture {
    CPPUNIT_TEST_SUITE (myalgorithmstest);
    CPPUNIT_TEST (myfindTest);
    CPPUNIT_TEST (myequalTest);
    CPPUNIT_TEST (mysearchTest);
    CPPUNIT_TEST (myldistTest);
    CPPUNIT_TEST_SUITE_END ();

public:
    ///Prepares the test environment */
    void setUp (void);
    ///Cleanes the test environment */
    void tearDown (void);

protected:
    ///Tests myfind() method
    void myfindTest (void);
    ///Tests myequal() method
    void myequalTest (void);
    ///Tests mysearch() method
    void mysearchTest (void);
    ///Tests myldist() method
    void myldistTest (void);

private:
    mystl::MyVector<std::string> v;
    mystl::MyVector<std::string> emptyv;
    mystl::MyList<std::string> l;
    mystl::MyList<std::string> emptyl;
};

#endif
