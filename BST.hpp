/*
  BST.hpp
  ------------------------------------------------------------------------------
  Binary Search Tree
  ------------------------------------------------------------------------------
  Ver  1.00 Initial version                                         September 21
  Ver  2.00 Add copy/move constructors/assignment operators         September 21
  Ver  3.00 Make the 'Node' a private nested class in the 'BST'     September 21
  Ver  4.00 Replace 'ptr != nullptr' checks by simpler ones         September 21
  Ver  5.00 Use in-class member initializers                        September 21
  Ver  6.00 Use 'std::unique_ptr' to point to nodes                 September 21
  ------------------------------------------------------------------------------
  Copyright (c) 2021 A.Yakovlev
*/

#pragma once

#include <cstdlib>
#include <ctime>

#include <iostream>
#include <memory>
#include <utility>

template <class KEY>
struct BST
{

  BST()
  {
    std::srand(std::time(nullptr));
  }

  BST(BST const& T)
  {
    Copy(&_rootPtr, T._rootPtr);
  }

  BST(BST&& T)
  {
    std::swap(_rootPtr, T._rootPtr);
  }

  BST& operator=(BST const& T)
  {
    if (this != &T)
    {
      _rootPtr.reset();
      Copy(&_rootPtr, T._rootPtr);
    }
    return *this;
  }

  BST& operator=(BST&& T)
  {
    if (this != &T)
    {
      std::swap(_rootPtr, T._rootPtr);
      T._rootPtr.reset();
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
    return Find(K, const_cast<Node::NodePtr*>(&_rootPtr)).second;
  }

  void insert(KEY const& K)
  {
    const auto res = Find(K, &_rootPtr);
    if (not res.second) *res.first = std::make_unique<Node>(K);
  }

  void erase(KEY const& K) noexcept
  {
    const auto res = Find(K, &_rootPtr);
    if (res.second) Erase(res.first);
  }

  void clear() noexcept
  {
    _rootPtr.reset();
  }

private:

  struct Node
  {

    // ------ smart pointer to point to nodes
    using NodePtr = std::unique_ptr<Node>;
  
    // ------ default constructor (deleted)
    Node() = delete;

    // ------ constructor with the key argument
    explicit Node(KEY const& K): _key{K} {}

    // ------ in the subtree with the root N:
    // ------ recursively traverse this subtree with inorder keys output
    friend std::ostream& operator<<(std::ostream& S, NodePtr const& N)
    {
      if (N) S << '(' << N->_lPtr << N->_key << N->_rPtr << ')';
      return S;
    }

    // ------ in the subtree with the root *P:
    // ------ if the node with the key K exists, return pointer to pointer to it and the flag 'true',
    // ------ otherwise return pointer to pointer, where the new node should be linked, and the flag 'false'
    friend std::pair<NodePtr*, bool> Find(KEY const& K, NodePtr* const P)
    {
      const auto nodePtr = P->get();
      if (nodePtr)
      {
        if (K < nodePtr->_key)
        {
          // ------ search in the left subtree
          return Find(K, &nodePtr->_lPtr);
        }
        else if (K > nodePtr->_key)
        {
          // ------ search in the right subtree
          return Find(K, &nodePtr->_rPtr);
        }
        else
        {
          // ------ the node is found: return pointer to it
          return std::make_pair(P, true);
        }
      }
      else
      {
        // ------ the node isn't found
        return std::make_pair(P, false);
      }
    }

    // ------ in the subtree with the root *P:
    // ------ return pointer to pointer to the node with a minimal key
    friend NodePtr* FindMin(NodePtr* const P)
    {
      const auto nodePtr = P->get();
      return (nodePtr->_lPtr) ? FindMin(&nodePtr->_lPtr) : P;
    }

    // ------ in the subtree with the root *P:
    // ------ return pointer to pointer to the node with a maximal key
    friend NodePtr* FindMax(NodePtr* const P)
    {
      const auto nodePtr = P->get();
      return (nodePtr->_rPtr) ? FindMax(&nodePtr->_rPtr) : P;
    }

    // ------ in the subtree with the root *P:
    // ------ recursively erase its root
    friend void Erase(NodePtr* const P)
    {
      const auto nodePtr = P->get();
      if (nodePtr->_lPtr && nodePtr->_rPtr)
      {
        // ------ the node has two children: find the closest node, copy its key and erase it;
        // ------ closest left or right nodes are chosen randomly for symmetry
        const auto closestPtr = (std::rand() % 2 == 0) ? FindMax(&nodePtr->_lPtr) : FindMin(&nodePtr->_rPtr);
        nodePtr->_key = (*closestPtr)->_key;
        Erase(closestPtr);
      }
      else if (nodePtr->_lPtr)
      {
        // ------ the node has only the left child
        *P = std::move(nodePtr->_lPtr);
      }
      else if (nodePtr->_rPtr)
      {
        // ------ the node has only the right child
        *P = std::move(nodePtr->_rPtr);
      }
      else
      {
        // ------ the node doesn't have children
        *P = nullptr;
      }
    }

    // ------ recursively copy the subtree with the root N
    // ------ to the subtree with the root *P
    friend void Copy(NodePtr* const P, NodePtr const& N)
    {
      if (N)
      {
        auto nodePtr = std::make_unique<Node>(N->_key);
        Copy(&nodePtr->_lPtr, N->_lPtr);
        Copy(&nodePtr->_rPtr, N->_rPtr);
        *P = std::move(nodePtr);
      }
    }

    NodePtr _lPtr = nullptr;
    NodePtr _rPtr = nullptr;
    KEY _key;

  };

  Node::NodePtr _rootPtr = nullptr;

};
