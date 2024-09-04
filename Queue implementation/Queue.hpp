#pragma once
#include <algorithm>
#include <stddef.h>
#include <stdexcept>

template <typename T> class Queue {
public:
  Queue();
  Queue(const Queue &);
  Queue(Queue &&);
  Queue &operator=(const Queue &);
  Queue &operator=(Queue &&);
  ~Queue();
  
  template <typename U> Queue &push(U&& element){
    if(full()) realoc();
    //back_=(back_+1)&capacity_;
    arr_[back_]=std::forward<U>(element);
    size_++;
    back_++;
  };


  T pop();
  T &front();
  size_t size() const;
  size_t capacity() const;
  bool empty() const;
  bool full() const;
  void clear(); 
  void realoc();

private:
  void copyQueue(const Queue &);
  size_t capacity_{0};
  size_t size_{0};
  T *arr_{nullptr};
  size_t back_{0};
  size_t front_{0};
};

template<typename T>
void Queue<T>::realoc(){
  capacity_=2*capacity_;
  auto temp=new T[capacity_];
  std::copy(arr_, arr_+size_-1, temp);
  delete [] arr_;
};

template<typename T>
Queue<T>::Queue(): capacity_{10}, size_{0}, arr_{new T[capacity_]} {};

template<typename T>
Queue<T>::Queue(const Queue& other){
  capacity_=other.capacity_;
  size_=other.size_;
  front_=other.front_;
  back_=other.back_;
  arr_=new T[capacity_];
  std::copy(other.arr_, other.arr_+size_, arr_);
};

template<typename T>
Queue<T>::Queue(Queue&& other){
  capacity_=other.capacity_;
  size_=other.size_;
  arr_=other.arr_;
  front_=other.front_;
  back_=other.back_;

  other.arr_=nullptr;
  other.front_=0;
  other.back_=0;
  other.capacity_=0;
  other.size_=0;
};

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other){
  if(this!=&other){
    delete [] arr_;
    capacity_=other.capacity_;
    size_=other.size_;
    back_=other.back_;
    front_=other.front_;
    arr_=new T[capacity_];
    std::copy(other.arr_, other.arr_+size_, arr_);
  }
  return *this;
}; 

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& other){
  delete [] arr_;
  capacity_=other.capacity_;
  size_=other.size_;
  front_=other.front_;
  back_=other.back_;
  arr_=other.arr_;

  other.arr_=nullptr;
  other.size_=other.capacity_=0;

  return *this;
};

template<typename T>
Queue<T>::~Queue(){
  delete [] arr_;
  size_=capacity_=0;
};

template<typename T>
T& Queue<T>::front(){
  if(empty()) throw std::out_of_range("Prazan red");
  return arr_[front_];
};

template<typename T>
T Queue<T>::pop(){
  if(empty()) throw std::out_of_range("Prazan red"); 
  auto temp=std::move(arr_[front_]);
  front_=(front_+1)%capacity_;
  size_--;
  return temp;
};

template<typename T>
size_t Queue<T>::size() const{
  return size_;
};

template<typename T>
size_t Queue<T>::capacity() const{
  return capacity_;
};

template<typename T>
bool Queue<T>::full() const{
  return size_==capacity_;  
};

template<typename T>
bool Queue<T>::empty() const{
  return size_==0;
};

template<typename T>
void Queue<T>::clear(){
  size_=0;
};
