///\file myalgorithms.h
///\brief Contains some generic algorithms using sequences
///
///Implementation of the standard algorithms length(), find(), equal() and search(). 
///They operate on iterators thus beeing completely independent from the actual container chosen to store the data.

#ifndef MYSTL_MYALGORITHMS_H
#define MYSTL_MYALGORITHMS_H

///Isolates MySTL Classes and functions names
namespace mystl {

///\brief Returns the length of a generic sequence
template<class In>
int mylength (In first, In last) {
    int lnt=0;
    while (first!=last) {
        ++first;
        ++lnt;
    }
    return lnt;
}

///\brief Returns the position of the element in T in the container
///If the element is not present it returns last
template<class In, class T>
In myfind (In first, In last, const T& val) {
    while (first!=last && *first!=val)
        ++first;
    return first;
}

///\brief Returns true if the sequences are equal
///the second sequence must be long at least as the first
template<class In, class In2>
bool myequal (In first, In last, In2 first2) {
    while (first!=last && *first==*first2) {
        ++first;
        ++first2;
    }
    return first==last;
}

///\brief Returns the position of the element in the first sequence where the second begins as a subsequence,
///if doesn't exists returns the end of the first sequence
template<class For, class For2>
For mysearch(For first, For last, For2 first2, For2 last2) {
    while (first!=last) {
        For tmp_it=first;//temporary iterator for the internal loop
        while (tmp_it!=last && first2!=last2 && *tmp_it==*first2) {
            ++tmp_it;
            ++first2;
        }
        if (first2==last2)
            return first;//end of the second sequence
        ++first;
    }
    return first;
}

///\brief Compute the Levenshtein distance between two sequences
///
///The algorithms is explained at http://www.merriampark.com/ld.htm and is based on dynamic programming.
///The implementation is adapted from the one at http://www.merriampark.com/ldcpp.htm
///
///It is a simplified version of the alignment algorithms I developed in my degree thesis
///which contributed to the bioinformatics project named ALiBio http://www.alibio.org/
template<class For, class For2>
int myldist(For first, For last, For2 first2, For2 last2) {

    const int n = mylength(first,last);
    const int m = mylength(first2,last2);
    if (n == 0) {
        return m;
    }
    if (m == 0) {
        return n;
    }

    typedef MyVector<MyVector<int> > Tmatrix;

    Tmatrix matrix(n+1);

    // Size the vectors in the 2.nd dimension. Unfortunately C++ doesn't
    // allow for allocation on declaration of 2.nd dimension of vec of vec
    for (int i = 0; i <= n; ++i) {
        matrix[i].reserve(m+1);
    }

    // Step 2
    for (int i = 0; i <= n; ++i) {
        matrix[i][0]=i;
    }
    for (int j = 0; j <= m; ++j) {
        matrix[0][j]=j;
    }

    // Step 3
    for (int i = 1; (i <= n)&&(first!=last) ; ++i, ++first) {
        // Step 4
        For2 tmp_it=first2;//temporary iterator for the internal loop
        for (int j = 1; (j <= m)&&(tmp_it!=last2); ++j, ++tmp_it) {

            // Step 5
            int cost=0;
            if (!(*first == *tmp_it))
                cost = 1;

            // Step 6
            const int above = matrix[i-1][j];
            const int left = matrix[i][j-1];
            const int diag = matrix[i-1][j-1];
            const int cell = std::min(above+1, std::min(left+1, diag+cost));
            matrix[i][j]=cell;
        }
    }

    // Step 7
    return matrix[n][m];
}

}
#endif
