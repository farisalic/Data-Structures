#pragma once

#include <cstddef>
#include <functional>

template <typename T> 
struct Node {
  Node* prev{nullptr};
  Node* next{nullptr};
  T data;
  Node(const T &element) : data{element}, next{nullptr}, prev{nullptr} {}
};

template <typename T> 
class DoubleLinkedList {
public:
  class Iterator;
  DoubleLinkedList()=default; //ODRADJENO
  DoubleLinkedList(const DoubleLinkedList &); //ODRADJENO
  DoubleLinkedList(DoubleLinkedList &&); //ODRADJENO
  DoubleLinkedList &operator=(const DoubleLinkedList &); //ODRADJENO
  DoubleLinkedList &operator=(DoubleLinkedList &&); //ODRADJENO
  ~DoubleLinkedList(); //ODRADJENO

  DoubleLinkedList& push_back(const T &); //ODRADJENO
  DoubleLinkedList& push_front(const T &); //ODRADJENO
  DoubleLinkedList& push_back(T &&); //ODRADJENO
  DoubleLinkedList& push_front(T &&); //ODRADJENO
  DoubleLinkedList& pop_front(); //ODRADJENO
  DoubleLinkedList& pop_back(); //ODRADJENO
  bool empty() const; //ODRADJENO
  size_t size() const; //ODRADJENO
  T &front(); //ODRADJENO
  T &back(); //ODRADJENO
  Iterator begin() const{ return Iterator(head_); }; //ODRADJENO
  Iterator end() const{ return Iterator(nullptr); }; //ODRADJENO
  const Iterator cbegin() const{ return Iterator(head_); }; //ODRADJENO
  const Iterator cend() const{ return Iterator(nullptr); }; //ODRADJENO
  Iterator rbegin() const{ return Iterator(tail_); }; //ODRADJENO
  Iterator rend() const{ return Iterator(nullptr); }; //ODRADJENO
  const Iterator rcbegin() const{ return Iterator(tail_); }; //ODRADJENO
  const Iterator rcend() const{ return Iterator(nullptr); }; //ODRADJENO
  void clear(); //ODRADJENO
  Iterator insert(Iterator pos, const T &element); //ODRADJENO
  Iterator erase(Iterator pos); //ODRADJENO
  Iterator erase(Iterator beginIt, Iterator endIt); //ODRADJENO
  void remove_if(std::function<bool(const T &)> &&p); //ODRADJENO
  void reverse(); //ODRADJENO
  Iterator find(const T &element) const; //ODRADJENO

private:
  void dealoc();
  Node<T>* head_{nullptr};
  Node<T>* tail_{nullptr};
  size_t size_{0};
};

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& other){
  auto temp=other.head_;
  while(temp->next!=nullptr){
    push_back(temp->data);
    temp=temp->next;
  }
};

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList&& other){
  size_=other.size_;
  head_=other.head_;
  tail_=other.tail_;
  other.tail_=nullptr;
  other.head_=nullptr;
  other.size_=0;
};

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList& other){
  if(this!=&other){
    auto temp=other.head_;
    clear();
    while(temp!=nullptr){
      push_back(temp->data);
      temp=temp->next;
    }
  }
  return *this;
};

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList&& other){
  if(this!=&other){
    size_=other.size_;
    head_=other.head_;
    tail_=other.tail_;
    other.size_=0;
    other.tail_=other.head_=nullptr;
  }
  return *this;
};

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList(){ clear(); };

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(const T& element){
auto temp=new Node<T>(element);
  if(size_==0){
    head_=tail_=temp;
  }
  else{
    tail_->next=temp;
    temp->prev=tail_;
    tail_=temp;
  }
  size_++;
  return *this;
};

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(T&& element){
auto temp=new Node<T>(std::move(element));
  if(size_==0){
    head_=tail_=temp;
  }
  else{
    tail_->next=temp;
    temp->prev=tail_;
    tail_=temp;
  }
  size_++;
  return *this;
};

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(const T& element){
auto temp=new Node<T>(element);
  if(size_==0){
    head_=tail_=temp;
  }
  else{
    temp->next=head_;
    head_->prev=temp;
    head_=temp;
  }
  size_++;
  return *this;
};

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(T&& element){
auto temp=new Node<T>(std::move(element));
  if(size_==0){
    head_=tail_=temp;
  }
  else{
    temp->next=head_;
    head_->prev=temp;
    head_=temp;
  }
  size_++;
  return *this;
};

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_back(){
  if(size_==0) throw std::out_of_range("Prazna lista");
  else if(size_==1) pop_front();
  else{
    auto temp=tail_;
    tail_=tail_->prev;
    tail_->next=nullptr;
    delete temp;
    size_--;
  }
  return *this;
};

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_front(){
  if(size_==0) throw std::out_of_range("Prazna lista");
  if(size_==1){
    delete head_;
    tail_=head_=nullptr;
  }
  else{
    auto temp=head_;
    head_=head_->next;
    delete temp;
  }
  size_--;
  return *this;
};

template<typename T>
bool DoubleLinkedList<T>::empty() const{ return size_==0; };

template<typename T>
size_t DoubleLinkedList<T>::size() const{ return size_; };

template<typename T>
T& DoubleLinkedList<T>::front(){
  if(size_==0) throw std::out_of_range("Prazna lista");
  return head_->data;
};

template<typename T>
T& DoubleLinkedList<T>::back(){
  if(size_==0) throw std::out_of_range("Prazna lista");
  return tail_->data;
};

template<typename T>
void DoubleLinkedList<T>::clear(){
  while(head_!=nullptr){
    auto temp=head_;
    head_=head_->next;
    delete temp;
  }
  size_=0;
  head_=tail_=nullptr;
};


//ITERATOR IMPLEMENTACIJA
template<typename T>
class DoubleLinkedList<T>::Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  friend class DoubleLinkedList<T>;
  private:
    Node<T>* ptr_=nullptr;
  public:
    Iterator(): ptr_{nullptr} {};
    Iterator(Node<T>* ptr) : ptr_{ptr}{};
    Iterator(const Iterator& other){ ptr_=other.ptr_; };
    
    Iterator(Iterator&& other){
      ptr_=other.ptr_;
      other.ptr_=nullptr;
    };

    ~Iterator(){ ptr_=nullptr; };

    Node<T>* node(){ return ptr_; };

    Iterator& operator=(const Iterator& other){
      if(this!=&other) ptr_=other.ptr_;
      return *this;
    };

    Iterator& operator=(Iterator&& other){
      if(this!=&other){
        ptr_=other.ptr_;
        other.ptr_=nullptr;
      }
      return *this;
    };

    T& operator*(){ return ptr_->data; };
    T* operator->(){ return &(ptr_->data); };
    T* operator->() const { return &(ptr_->data); };

    Iterator& operator++(){
      ptr_=ptr_->next;
      return *this;
    };
//provjeriti da li mozemo ovdje napisati temp=*this;
    Iterator operator++(int){
      auto temp=ptr_;
      ptr_=ptr_->next;
      return temp;
    };

    Iterator& operator--(){
      ptr_=ptr_->prev;
      return *this;
    };

    Iterator operator--(int){
      auto temp=ptr_;
      ptr_=ptr_->prev;
      return temp;
    };

    bool operator==(const Iterator& other){ return other.ptr_==ptr_; };
    bool operator!=(const Iterator& other){ return other.ptr_!=ptr_; };
};

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::insert(Iterator pos, const T& element){
  if(size_==0 || pos==begin()){
    push_front(element);
    return begin();
  }

  auto temp=new Node<T>(element);
  auto prev_node=pos.ptr_->prev;
  prev_node->next=temp;
  temp->prev=prev_node;
  temp->next=pos.ptr_;
  pos.ptr_->prev=temp;
  size_++;
  return Iterator(--pos);
};

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator pos){
  if(pos.ptr_->next==nullptr) pop_back();
  auto temp=pos.ptr_->next;
  pos.ptr_->next=pos.ptr_->next->next;
  delete temp;
  size_--;
  return Iterator(temp);
};

//Iz nekog razloga moram head_ ptr staviti u zasebnu varijablu inace test nece proci
template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::find(const T& element) const{
  auto temp=head_;
  while(temp!=nullptr){
    if(temp->data==element) return Iterator(temp);
    temp=temp->next;
  }
  return Iterator(end());
};

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator beginIt, Iterator endIt){
  while(beginIt!=endIt){
    erase(beginIt);
    beginIt++;
    size_--;
  }
  return Iterator(endIt);
};

//NE RADI (SEG FAULT)
template<typename T>
void DoubleLinkedList<T>::remove_if(std::function<bool(const T&)>&& p){
  for(auto it=begin(); it!=end();){
    if(p(*it)){
      auto brisi=it;
      ++it;
      erase(brisi);
    }
    else{
      ++it;
    }
  }
};

template<typename T>
void DoubleLinkedList<T>::reverse(){
  auto temp1=head_;
  auto temp2=tail_;
  while(temp1!=temp2 && temp1->prev!=temp2){
    std::swap(temp1->data, temp2->data);
    temp1=temp1->next;
    temp2=temp2->prev;
  }
};
