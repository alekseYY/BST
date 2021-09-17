/*
  tc0003.cpp
  ------------------------------------------------------------------------------
  Binary Search Tree Test #2 - Move Constructor and Assignment
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
  // ------ move constructor
  BST<int> t1;
  t1.insert(50);
  t1.insert(40);
  t1.insert(60);
  cout << "Before move constructor 'BST<int> t2(std::move(t1))':" << endl;
  cout << "t1: " << t1 << endl;
  BST<int> t2(std::move(t1));
  cout << "After  move constructor 'BST<int> t2(std::move(t1))':" << endl;
  cout << "t1: " << t1 << endl;
  cout << "t2: " << t2 << endl;
  // ------ move assignment
  t1 = std::move(t2);
  cout << "After  move assignment 't1 = std::move(t2)':" << endl;
  cout << "t1: " << t1 << endl;
  cout << "t2: " << t2 << endl;
}
