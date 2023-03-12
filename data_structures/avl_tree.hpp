#pragma once
#include <iostream>
#include "TTable.h"

class AVLTree {
private:

  struct TreeNode {
    std::shared_ptr<PolinomObj> data;
    TreeNode* pLeft;
    TreeNode* pRight;
    int bal; // balance value

    TreeNode(std::shared_ptr<PolinomObj> _data = {}) : data(_data) {
      pLeft = pRight = nullptr;
      bal = 0;
    }

    ~TreeNode() {
      data = nullptr;
      pLeft = pRight = nullptr;
    }
  };

  TreeNode* pRoot = nullptr;
  int indInPrint = 0;

  AVLTree(const AVLTree& obj) = delete; // Запрещено копирование

  AVLTree operator=(const AVLTree& obj) = delete; // Запрещено присваивать

  int heightTreeNode(TreeNode* node) {
    if (node == nullptr)
      return 0;
    int heightLeft = heightTreeNode(node->pLeft);
    int heightRight = heightTreeNode(node->pRight);
    if (heightLeft > heightRight)
      return heightLeft + 1;
    else
      return heightRight + 1;
  }

  int balanceNode(TreeNode*& node) {
    if (node != nullptr) {
      node->bal = heightTreeNode(node->pRight) - heightTreeNode(node->pLeft);
      return node->bal;
    }
    return 0;
  }

  void rightRotation(TreeNode*& node) {
    TreeNode* pLeft = node->pLeft;              /*                        Right Rotation                      */
    TreeNode* pLeftRight = node->pLeft->pRight; /*                 node                     pLeft             */
    pLeft->pRight = node;                       /*                /    \                   /     \            */
    node->pLeft = pLeftRight;                   /*           pLeft      pRight -> pLeftLeft       node        */
    node = pLeft;                               /*          /     \                              /    \       */
    balanceNode(node->pRight);                  /* pLeftLeft       pLeftRight          pLeftRight      pRight */
    balanceNode(node);
  }

  void leftRotation(TreeNode*& node) {
    TreeNode* pRight = node->pRight;            /*                          Left Rotation                         */
    TreeNode* pRightLeft = node->pRight->pLeft; /*       node                                  pRight             */
    pRight->pLeft = node;                       /*      /    \                                /      \            */
    node->pRight = pRightLeft;                  /* pLeft      pRight             ->       node        pRightRight */
    node = pRight;                              /*           /      \                    /    \                   */
    balanceNode(node->pLeft);                   /* pRightLeft        pRightRight    pLeft      pRightLeft         */
    balanceNode(node);
  }

  void balanceTree(TreeNode*& node) {
    balanceNode(node);
    if (node->bal == -2) {
      if (balanceNode(node->pLeft) > 0)
        leftRotation(node->pLeft);
      rightRotation(node);
    }
    if (node->bal == 2) {
      if (balanceNode(node->pRight) < 0)
        rightRotation(node->pRight);
      leftRotation(node);
    }
  }

  void Insert(std::shared_ptr<PolinomObj>& _data, TreeNode*& node) {
    if (node == nullptr) {
      node = new TreeNode(_data);
      return;
    }
    if (_data->getName() < node->data->getName())
      Insert(_data, node->pLeft);
    else if (_data->getName() > node->data->getName())
      Insert(_data, node->pRight);
    balanceTree(node);
  }

  TreeNode* FindNode(std::string name, TreeNode* node) {
    if (node == nullptr)
      return nullptr;
    if (node->data->getName() == name)
      return node;
    if (name < node->data->getName())
      return FindNode(name, node->pLeft);
    if (name > node->data->getName())
      return FindNode(name, node->pRight);
    return nullptr; // when something goes wrong
  }

  std::shared_ptr<PolinomObj>* Find(std::string name, TreeNode* node) {
    return &FindNode(name, node)->data;
  }

  TreeNode* findMinNode(TreeNode*& node) {
    if (node->pLeft != nullptr)
      return findMinNode(node->pLeft);
    return node;
  }

  TreeNode* deleteMinNode(TreeNode*& node) {
    if (node->pLeft == nullptr)
      return node->pRight;
    node->pLeft = deleteMinNode(node->pLeft);
    return node;
  }

  void Delete(std::string name, TreeNode*& node) {
    if (node == nullptr)
      return;
    if (name < node->data->getName()) {
      Delete(name, node->pLeft);
    }
    if (name > node->data->getName()) {
      Delete(name, node->pRight);
    }
    if (name == node->data->getName()) {
      TreeNode* pLeft = node->pLeft;
      TreeNode* pRight = node->pRight;
      delete node;
      if (pRight == nullptr) {
        node = pLeft;
      }
      else {
        TreeNode* tmp = findMinNode(pRight);
        tmp->pRight = deleteMinNode(pRight);
        tmp->pLeft = pLeft;
        node = tmp;
      }
    }
    if (node != nullptr)
      balanceTree(node);
  }

  void clear(TreeNode*& node) {
    if (node == nullptr)
      return;
    clear(node->pLeft);
    clear(node->pRight);
    delete node;
    node = nullptr;
  }

  void PrintNode(TreeNode* node) {
    if (node == nullptr)
      return;
    PrintNode(node->pLeft);
    std::cout << ++indInPrint << ") " << node->data << '\n';
    PrintNode(node->pRight);
  }

  int getSize(TreeNode* node) {
    if (node == nullptr)
      return 0;
    return getSize(node->pRight) + getSize(node->pLeft) + 1;
  }

public:

  AVLTree() { }

  int getSize() { return getSize(pRoot); }

  void Insert(std::shared_ptr<PolinomObj> _data) { Insert(_data, pRoot); }

  std::shared_ptr<PolinomObj>* Find(std::string name) { return Find(name, pRoot); }

  void Delete(std::string name) { Delete(name, pRoot); }

  void Print() {
    indInPrint = 0;
    PrintNode(pRoot);
  }

  ~AVLTree() { clear(pRoot); }

};
