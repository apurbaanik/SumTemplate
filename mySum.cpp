/*
Title: Homework 5.1 A mySum template function with a specialization
Author: Anik Barua
Version: 1.0
Date: 05-27-2021

Description: This C++ program uses mySum template function which, if passed with a container of int or double (these two only), 
returns the sum; but when passed with a vector of std::string (this only), returns the total number of characters of all elements.
*/

#include <iostream>
#include <vector>
#include <list>
using namespace std;

//SameType type function
template<typename X, typename Y>
struct SameType{
    enum {result = false};
};

template<typename T>
struct SameType<T, T>{
    enum { result = true };
};

//A type function, is_addable, which will be true ONLY when the type argument is either int or double
template<typename T>
struct is_addable{
    enum {result = SameType<T, int>::result || SameType<T, double>::result};
};

//Two type parameters, one for the iterator type of the container, and one for the value type of the container.
template<typename X, typename Y>
//Three arguments, first and last of the iterator to mark the range of the container, as well as the initial value of the sum. It returns the summed result.
Y mySum(X iterBegin, X iterEnd, Y value){
    typename iterator_traits<X>::value_type val = value; //Getting the value type
    static_assert(is_addable<Y>::result && SameType<typename iterator_traits<X>::value_type, Y>::result, 
    "Only containers of int or double are supported and initial value of the sum must match the value type of the container.");
    Y sum = value;
    for(auto itr = iterBegin; itr != iterEnd; itr++){
        sum = sum + *itr; //returns the sum
    }
    return sum;
}

//Define a specialization of mySum, which will only be called when a vector of std::string, and an int for 
//initial sum are passed. This version of mySum returns the total number of characters contained in the string vector's elements
template<>
int mySum(vector<string>::iterator iterBegin, vector<string>::iterator iterEnd, int value){
    int count = 0;
    for (vector<string>::iterator itr = iterBegin ; itr != iterEnd; itr++){
        string s = *itr;
        count = count + s.length();
    }
    return count; //returns the total number of characters of all elements
}

int main(){
    vector<int> v1 = {1, 2, 3, 4};
    list<double> v2 = {1.1, 2.2, 3.3, 4.4};
    vector<std::string> v3 = {"Hello", "world", "Yes", "No"};
    int sum1 = 1; // the initial sum for v1 - just some value for testing
    double sum2 = 1.2; // the initial sum for v2
    int sum3 = 0; // the initial sum for v3

    cout << "Sum of v1: " << mySum(v1.begin(), v1.end(), sum1) << endl;
    cout << "Sum of v2: " << mySum(v2.begin(), v2.end(), sum2) << endl;
    cout << "Sum of v3: " << mySum(v3.begin(), v3.end(), sum3) << endl;

    /*
    list<std::string> v4 = {"Yes", "No"};
    float wrong_init = 0.0;
    cout << mySum(v4.begin(), v4.end(), 0) << endl; // should trigger compile error due to elements not being int/double, and not specialization.
    cout << mySum(v1.begin(), v1.end(), wrong_init) << endl; // should trigger compile error due to wrong type of initial sum
    */

    return 0;
}