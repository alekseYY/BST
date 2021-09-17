/*
  tc0001.cpp
  ------------------------------------------------------------------------------
  Binary Search Tree Test #1 - Insertion and Erasure
  ------------------------------------------------------------------------------
  Ver  1.00 Initial version                                         September 21
  ------------------------------------------------------------------------------
  Copyright (c) 2021 A.Yakovlev
*/

#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "BST.hpp"

using std::cout;
using std::endl;

int main()
{
  // ------ generate randomly ordered vector
  std::vector<int> v(10);
  std::iota(v.begin(), v.end(), 0);
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(v.begin(), v.end(), g);
  // ------ insert the vector into a BST
  BST<int> t;
  for (const auto& e: v) t.insert(e);
  cout << "initial : " << t << endl;
  // ------ erase BST keys one by one
  for (const auto& e: v)
  {
    t.erase(e);
    cout << "erase(" << e << "): " << t << endl;
  }
}
