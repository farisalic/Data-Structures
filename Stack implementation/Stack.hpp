#pragma once
#include <algorithm>
#include <stddef.h>
#include <stdexcept>

template <typename T> class Stack {
public:
  Stack();
  Stack(const Stack &);
  Stack(Stack &&);
  Stack &operator=(const Stack &);
  Stack &operator=(Stack &&);
  T pop();
  T &top() const;
  // Savrseno proslijedjivane (forward referenca)
  template <typename U> Stack<T> &push(U && element){
    if(full()) realoc();
    *(arr_+size_)=std::forward<U>(element);
    size_++;
    return *this;
  };
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  bool full() const;
  ~Stack();
  void clear();
  void resize(size_t newSize);
  bool operator==(const Stack &);
  bool operator!=(const Stack &);

private:
  void realoc();
  size_t capacity_{0};
  size_t size_{0};
  T *arr_{nullptr};
};

template<typename T>
void Stack<T>::clear(){
  size_=0;
};

template<typename T>
void Stack<T>::realoc(){
  capacity_=2*capacity_;
  T* temp=new T[capacity_];
  std::copy(arr_, arr_+size_-1, temp);
  delete [] arr_;
};

template<typename T>
void Stack<T>::resize(size_t newSize){
  if(newSize<=size_) size_=newSize;
  else{
    if(newSize>=capacity_) realoc();
    for(auto i=size_; i<newSize; i++){
      push(0);
    }}
  size_=newSize;
};

template<typename T>
Stack<T>::Stack(): capacity_{10}, size_{0}, arr_{new T[capacity_]} {};

template<typename T>
Stack<T>::Stack(const Stack& other){
  capacity_=other.capacity_;
  size_=other.size_;
  arr_=other.arr_;
  std::copy(other.arr_, other.arr_+size_, arr_);
};

template<typename T>
Stack<T>::Stack(Stack&& other){
  capacity_=other.capacity_;
  size_=other.size_;
  arr_=other.arr_;
  other.arr_=nullptr;
  other.capacity_=other.size_=0;
};

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other){
  if(this!=&other){
    delete [] arr_;
    capacity_=other.capacity_;
    size_=other.size_;
    arr_=new T[capacity_];
    std::copy(other.arr_, other.arr_+size_, arr_);
  }
  return *this;
};

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& other){
  if(this!=&other){
    delete [] arr_;
    capacity_=other.capacity_;
    size_=other.size_;
    arr_=other.arr_;

    other.capacity_=other.size_=0;
    other.arr_=nullptr;
  }
  return *this;
};

template<typename T>
T Stack<T>::pop(){
  if(size_==0) throw std::out_of_range("Prazan stack");
  auto temp=std::move(*(arr_+size_-1));
  size_--;
  return temp;
};

template<typename T>
T& Stack<T>::top() const{
  if(size_==0) throw std::out_of_range("Prazan stack");
  return *(arr_+size_-1);
};

template<typename T>
size_t Stack<T>::size() const{
  return this->size_;
};

template<typename T>
size_t Stack<T>::capacity() const{
  return this->capacity_;
};

template<typename T>
bool Stack<T>::empty() const{
  return size_==0;
};

template<typename T>
bool Stack<T>::full() const{
  return size_>=capacity_;
};

template<typename T>
Stack<T>::~Stack(){
  delete [] arr_;
  size_=capacity_=0;
};

template<typename T>
bool Stack<T>::operator==(const Stack& other){
  if(other.size_!=size_) return false;
  for(auto i=0; i!=size_; i++){
    if((*(arr_+i))!=(*(other.arr_+i))) return false;
  }
  return true;
};

template<typename T>
bool Stack<T>::operator!=(const Stack& other){
  if(size_!=other.size_) return true;
  for(auto i=0; i!=size_; i++){
    if((*(arr_+i))!=(*(other.arr_+i))) return true;
  }
  return false;
};

