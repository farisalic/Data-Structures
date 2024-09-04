#pragma once
#include <iostream>

template <typename K, typename T>
struct Node {
  K key;
  T value;
  Node* left_ = nullptr;
  Node* right_ = nullptr;
  Node(const K& kljuc, const T& vrijednost) :  key{kljuc}, value{vrijednost}, left_{nullptr}, right_{nullptr} {};
};



template <typename K, typename T>
class Tree {
public:
  Tree() : root_{nullptr} {};

  Tree(const Tree& other){
    duplicate(other.root_, root_);
  };
  
  Tree(Tree&& other){
    root_=other.root_;
    size_=other.size_;
    other.root_=nullptr;
    other.size_=0;
  };

  Tree& operator=(const Tree& other){
    if(this!=&other){
        clear();
        duplicate(other.root_, root_);
    }
    return *this;
  };

  Tree& operator=(Tree&& other){
    if(this!=&other){
        if(this!=&other){
            clear();
            root_=other.root_;
            size_=other.size_;
            other.root_=nullptr;
            other.size_=0;
        }
    }
    return *this;
  };

  ~Tree() {
    clear();
  }

  bool size() const {
    return size_;
  }

  bool empty() const {
    return root_ == nullptr;
  }

  void insert(const K& key, T&& value) {
    if(root_==nullptr) return;
    if(key < root_->key) root_->left_=insert(key, value);
    else if (key > root_->key) root_->right_=insert(key, value);
    else root_->value=value;
  }

 
  const T* find(const K& v) const {
    return findNode(const K& v, Node<K, T>* root_);
  }

  T* find(const K& v){
    return findNode(const K& v, Node<K, T>* root_);
  };


  T& at(const K& key){
    auto temp = findNode(key, root_);
    if(temp == nullptr) throw std::out_of_range(" ");
    return temp->value;
  };

  const T& at(const K& key) const{
    auto temp = findNode(key, root_);
    if(temp == nullptr) throw std::out_of_range(" ");
    return temp->value;
  };

  void clear() {
    clear_subtree(root_);
    size_ = 0;
    root_ = nullptr;
  }

  void print() const {
    print_inorder(root_);
    std::cout << std::endl;
  }

  bool erase(const T& v) {
    Node<K, T>* previous = nullptr;
    auto current = root_;
    while (current != nullptr) {
      if (v > current->value) {
        previous = current;
        current = current->right_;
      } else if (v == current->value) {
        if (previous == nullptr) {
          eraseNode(root_);
        } else if (previous->left_->value == v) {
          eraseNode(previous->left_);
          return true;
        } else {
          eraseNode(previous->right_);
          return true;
        }
      } else {
        previous = current;
        current = current->left_;
      }
    }
    return false;
  }

private:
    void duplicate(const Node<K, T>* Node1, Node<K, T>* Node2){
        if(Node1==nullptr) return;
        Node2=new Node<K, T>(Node1->key, Node1->value);
        duplicate(Node1->left_, Node2->left_);
        duplicate(Node1->right_, Node2->right_);
    };

    Node<K, T>* findNode(const K& v, Node<K, T>* root){
        if (root==nullptr || v==root->value)
        {
            return root;
        }
        else if (v < root->value) 
        {
            return findNode(v, root->left);
        }
        else if (v > root->value)
        {
            return findNode(v, root->right_);
        }
        else return nullptr;
    };

  static void print_inorder(const Node<K, T>* root) {
    if (!root)
      return;
    print_inorder(root->left_);
    std::cout << root->value << ' ';
    print_inorder(root->right_);
  }

  void eraseNode(Node<K, T>*& e) {
    if (e == nullptr) {
      return;
    } else if (e->left_ == nullptr && e->right_ == nullptr) {
      delete e;
      e = nullptr;
    } else if (e->right_ == nullptr) {
      auto temp = e;
      e = e->left_;
      delete temp;
    } else if (e->left_ == nullptr) {
      auto temp = e;
      e = e->right_;
      delete temp;
    } else {
      Node<K, T>* previous = nullptr;
      auto current = e->left_;

      while (current->right_ != nullptr) {
        previous = current;
        current = current->right_;
      }
      e->value = current->value;
      if (previous != nullptr) {
        previous->right_ = current->left_;
      } else {
        e->left_ = current->left_;
      }
      delete current;
    }
    size_--;
  }

  static void clear_subtree(Node<K, T>* root) {
    if (!root)
      return;
    clear_subtree(root->left_);
    clear_subtree(root->right_);
    delete root;
  }

  Node<K, T>* root_ = nullptr;
  size_t size_ = 0;
};
