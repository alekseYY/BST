/*
  tc0001.cpp
  ------------------------------------------------------------------------------
  Binary Search Tree Test #1
  ------------------------------------------------------------------------------
  Ver  1.00 Initial version                                         September 21
  ------------------------------------------------------------------------------
  (C) A.Yakovlev, 2021
*/

#include <iostream>
#include <random>
#include <vector>

#include "BST.hpp"

using std::cout;
using std::endl;

int main()
{
  // ------ generate randomly ordered vector
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
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
