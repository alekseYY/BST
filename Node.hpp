/*
  Node.hpp
  ------------------------------------------------------------------------------
  Binary Search Tree Node Definition
  ------------------------------------------------------------------------------
  Ver  1.00 Initial version                                         September 21
  ------------------------------------------------------------------------------
  (C) A.Yakovlev, 2021
*/

#pragma once

#include <iostream>
#include <utility>

template <class KEY>
struct Node
{

  // ------ default constructor (deleted)
  Node() = delete;

  // ------ constructor with the key argument
  Node(KEY const& K): _lPtr(nullptr), _rPtr(nullptr), _key(K) {}

  // ------ in the subtree with the root N:
  // ------ recursively traverse this subtree with inorder keys output
  friend std::ostream& operator<<(std::ostream& S, const Node* const N)
  {
    if (N != nullptr) S << '(' << N->_lPtr << N->_key << N->_rPtr << ')';
    return S;
  }

  // ------ in the subtree with the root *P:
  // ------ if the node with the key K exists, return pointer to pointer to it and the flag 'true',
  // ------ otherwise return pointer to pointer, where the new node should be linked, and the flag 'false'
  friend std::pair<Node**, bool> Find(KEY const& K, Node** const P)
  {
    const auto nodePtr = *P;
    if (nodePtr != nullptr)
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
  // ------ recursively erase its root
  friend void Erase(Node** const P)
  {
    const auto nodePtr = *P;
    if (nodePtr->_lPtr != nullptr && nodePtr->_rPtr != nullptr)
    {
      // ------ the node has two children: find the closest node, copy its key and erase it;
      // ------ closest left or right nodes are chosen randomly for symmetry
      const auto closestPtr = (std::rand() % 2 == 0) ? FindMax(&nodePtr->_lPtr) : FindMin(&nodePtr->_rPtr);
      nodePtr->_key = (*closestPtr)->_key;
      Erase(closestPtr);
    }
    else if (nodePtr->_lPtr != nullptr)
    {
      // ------ the node has only the left child
      *P = nodePtr->_lPtr;
      delete nodePtr;
    }
    else if (nodePtr->_rPtr != nullptr)
    {
      // ------ the node has only the right child
      *P = nodePtr->_rPtr;
      delete nodePtr;
    }
    else
    {
      // ------ the node doesn't have children
      *P = nullptr;
      delete nodePtr;
    }
  }

  // ------ recursively copy the subtree with the root N
  // ------ to the subtree with the root *P
  friend void Copy(Node** const P, Node* const N)
  {
    if (N != nullptr)
    {
      const auto nodePtr = new Node(N->_key);
      Copy(&nodePtr->_lPtr, N->_lPtr);
      Copy(&nodePtr->_rPtr, N->_rPtr);
      *P = nodePtr;
    }
  }
  
  // ------ in the subtree with the root N:
  // ------ recursively erase all this subtree
  friend void Clear(const Node* const N)
  {
    if (N != nullptr)
    {
      Clear(N->_lPtr);
      Clear(N->_rPtr);
      delete N;
    }
  }

private:

  // ------ in the subtree with the root *P:
  // ------ return pointer to pointer to the node with a minimal key
  friend Node** FindMin(Node** const P)
  {
    const auto nodePtr = *P;
    return (nodePtr->_lPtr != nullptr) ? FindMin(&nodePtr->_lPtr) : P;
  }

  // ------ in the subtree with the root *P:
  // ------ return pointer to pointer to the node with a maximal key
  friend Node** FindMax(Node** const P)
  {
    const auto nodePtr = *P;
    return (nodePtr->_rPtr != nullptr) ? FindMax(&nodePtr->_rPtr) : P;
  }

  Node* _lPtr;
  Node* _rPtr;
  KEY _key;

};