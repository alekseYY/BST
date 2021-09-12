/*
  BST.hpp
  ------------------------------------------------------------------------------
  Binary Search Tree
  ------------------------------------------------------------------------------
  Ver  1.00 Initial version                                         September 21
  Ver  2.00 Add copy/move constructors/assignment operators         September 21
  ------------------------------------------------------------------------------
  (C) A.Yakovlev, 2021
*/

#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Node.hpp"

template <class KEY>
struct BST
{

  BST(): _rootPtr(nullptr)
  {
    std::srand(std::time(nullptr));
  }

  BST(BST const& T): _rootPtr(nullptr)
  {
    Copy(&_rootPtr, T._rootPtr);
  }

  BST(BST&& T): _rootPtr(nullptr)
  {
    std::swap(_rootPtr, T._rootPtr);
  }

  BST& operator=(BST const& T)
  {
    if (this != &T)
    {
      const auto ptr = _rootPtr;
      Copy(&_rootPtr, T._rootPtr);
      Clear(ptr);
    }
    return *this;
  }

  BST& operator=(BST&& T)
  {
    if (this != &T)
    {
      std::swap(_rootPtr, T._rootPtr);
      Clear(T._rootPtr);
      T._rootPtr = nullptr;
    }
    return *this;
  }

  virtual ~BST()
  {
    this->clear();
  }

  friend std::ostream& operator<<(std::ostream& S, BST const& T)
  {
    return S << T._rootPtr;
  }

  bool contains(KEY const& K) const noexcept
  {
    return Find(K, const_cast<Node<KEY>**>(&_rootPtr)).second;
  }

  void insert(KEY const& K)
  {
    const auto res = Find(K, &_rootPtr);
    if (not res.second) *res.first = new Node(K);
  }

  void erase(KEY const& K) noexcept
  {
    const auto res = Find(K, &_rootPtr);
    if (res.second) Erase(res.first);
  }

  void clear() noexcept
  {
    Clear(_rootPtr);
    _rootPtr = nullptr;
  }

private:

  Node<KEY>* _rootPtr;

};
