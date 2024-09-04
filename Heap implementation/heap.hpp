#pragma once

#include <algorithm>
#include <iostream>

template <typename T>
class BinaryHeap {
private:
  int capacity_=10;
  int size_;
  T* heap_;

  void realoc() {
    capacity_ = 2 * capacity_;
    T* temp = new T[capacity_];
    std::move(heap_, heap_ + capacity_, temp);
    delete[] heap_;
    heap_ = temp;
  }

  int parent(int index) const {
    return (index - 1) / 2;
  }

  static int leftChild(int index) {
    return 2 * index + 1;
  }

  static int rightChild(int index) {
    return 2 * index + 2;
  }

  void maxHeapify(int currentIndex) {
    int left = leftChild(currentIndex);
    int right = rightChild(currentIndex);

    T largest = currentIndex;

    if ((left <= size_) && (heap_[left] > heap_[largest]))
      largest = left;

    if ((right <= size_) && (heap_[right] > heap_[largest]))
      largest = right;

    if (largest != currentIndex) {
      std::swap(heap_[currentIndex], heap_[largest]);
      maxHeapify(largest);
    }
  }

public:
  BinaryHeap() : capacity_(10), size_(0), heap_(new T[capacity_]) {};
  
  BinaryHeap(const BinaryHeap& other){
    size_=other.size_;
    capacity_=other.capacity_;
    heap_=new T[capacity_];
    std::copy(other.heap_, other.heap_+size_, heap_);
  };

  BinaryHeap(BinaryHeap&& other){
    size_=other.size_;
    capacity_=other.capacity_;
    heap_=other.heap_;

    other.heap_=nullptr;
    other.size_=other.capacity_=0;
  };

  BinaryHeap& operator=(const BinaryHeap& other){
    if(this!=&other){
    delete [] heap_;
    size_=other.size_;
    capacity_=other.capacity_;
    heap_=new T[capacity_];
    std::copy(other.heap_, other.heap_+size_, heap_);
    }
    return *this;
  };

  BinaryHeap& operator=(BinaryHeap&& other){
    if(this!=&other){
    delete [] heap_;
    size_=other.size_;
    capacity_=other.capacity_;
    heap_=other.heap_;

    other.heap_=nullptr;
    other.size_=other.capacity_=0;
    }
    return *this;
  };

  ~BinaryHeap() {
    clear();
  }

  int size() const {
    return size_;
  }
  bool empty() const {
    return size_ == 0;
  }
  int capacity() const {
    return capacity_;
  }

  void insert(T data) {
    if (size() == capacity()) {
      realoc();
    }

    heap_[size_++] = data;
    int i = size() - 1;
    while ((i != 0) && heap_[parent(i)] < heap_[i]) {
      std::swap(heap_[parent(i)], heap_[i]);
      i = parent(i);
    }
  }

  void print() const {
    if (empty()) {
      std::cout << "Prazan heap!" << std::endl;
      return;
    }
    for (int i = 0; i < size(); i++) {
      std::cout << heap_[i] << " ";
    }
    std::cout << std::endl;
  }

  const T& max() const {
    if (empty()) {
      throw std::out_of_range("Prazan heap!");
    }
    return heap_[0];
  }

  T& max() {
    if (empty()) {
      throw std::out_of_range("Prazan heap!");
    }
    return heap_[0];
  }

  T popMax() {
    if (empty()) {
      throw std::out_of_range("Prazan heap!");
    }
    T maxItem = heap_[0];
    heap_[0] = heap_[--size_];
    maxHeapify(0);
    return maxItem;
  }

  void clear() {
    delete[] heap_;
    heap_ = nullptr;
    capacity_ = 0;
    size_ = 0;
  }
};
