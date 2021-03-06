/*
  tc0002.cpp
  ------------------------------------------------------------------------------
  Binary Search Tree Test #2 - Copy Constructor and Assignment
  ------------------------------------------------------------------------------
  Ver  1.00 Initial version                                         September 21
  ------------------------------------------------------------------------------
  Copyright (c) 2021 A.Yakovlev
*/

#include <iostream>

#include "BST.hpp"

using std::cout;
using std::endl;

int main()
{
  // ------ copy constructor
  BST<int> t1;
  t1.insert(50);
  t1.insert(40);
  t1.insert(60);
  cout << "Before copy constructor 'BST<int> t2(t1)':" << endl;
  cout << "t1: " << t1 << endl;
  BST<int> t2(t1);
  cout << "After  copy constructor 'BST<int> t2(t1)':" << endl;
  cout << "t1: " << t1 << endl;
  cout << "t2: " << t2 << endl;
  // ------ copy assignment
  BST<int> t3;
  t3.insert(150);
  t3.insert(100);
  t3.insert(125);
  cout << "Before copy assignment 't1 = t3':" << endl;
  cout << "t3: " << t3 << endl;
  t1 = t3;
  cout << "After  copy assignment 't1 = t3':" << endl;
  cout << "t1: " << t1 << endl;
  cout << "t3: " << t3 << endl;
}
