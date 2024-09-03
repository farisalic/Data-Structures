#pragma once
#include <initializer_list>
#include <iterator>

template <typename T>
class MojVektor {
  public:
  class Iterator;
  MojVektor();
  MojVektor(const std::initializer_list<T>&);
  MojVektor(const MojVektor&);
  MojVektor& operator=(const MojVektor&);
  MojVektor(MojVektor&&);
  MojVektor& operator=(MojVektor&&);
  ~MojVektor();
  MojVektor& push_back(const T&);
  MojVektor& push_front(const T&);
  MojVektor& push_back(T&&);
  MojVektor& push_front(T&&);
  size_t size() const;
  T& at(size_t) const;
  T& operator[](size_t) const;
  void clear();
  void resize(size_t newSize, const T& difference_value);
  MojVektor& pop_back();
  MojVektor& pop_front();
  T& back() const;
  T& front() const;
  bool empty() const;
  size_t capacity() const;
  bool operator==(const MojVektor&) const;
  bool operator!=(const MojVektor&) const;
  bool full() const;
  MojVektor subvector(Iterator begin, Iterator end);

  Iterator begin() const{
    return Iterator(arr_);
  };

  Iterator end() const{
    return Iterator(arr_+size_);
  };

  Iterator find(const T& element) const{
    for(auto i=0; i<size_; i++){
      if(arr_[i]==element) return Iterator(arr_+i);
    }
    return end();
  };

  Iterator erase(Iterator pos);
  Iterator insert(Iterator, const T&);
  Iterator insert(Iterator, T&&);
  
  Iterator rbegin() const{
    return Iterator(arr_+size_-1);
  };

  Iterator rend() const{
    return Iterator(arr_-1);
  };

  Iterator erase(Iterator beginIt, Iterator endIt);
  void rotate();

  void rotate(Iterator beginIt, Iterator endIt);

  T* data();

  private:
  void realoc();
  size_t capacity_;
  size_t size_;
  T* arr_;
};

// Implementacija ovdje
template<typename T>
T* MojVektor<T>::data(){
  return arr_;
};

template<typename T>
MojVektor<T>::MojVektor(): capacity_{10}, size_{0}, arr_{new T[capacity_]}{};

template<typename T>
MojVektor<T>::MojVektor(const std::initializer_list<T>& temp): capacity_{temp.size()}, size_{temp.size()}, arr_{new T[capacity_]}{
  std::copy(temp.begin(), temp.end(), arr_);
};

template<typename T>
MojVektor<T>& MojVektor<T>::operator=(const MojVektor& other){
  if(this!=&other){
  delete [] arr_;
  capacity_= other.capacity_;
  size_= other.size_;
  arr_=new T[capacity_];
  std::copy(other.arr_, other.arr_+size_,arr_);
  }
  return *this;
};

template<typename T>
MojVektor<T>::MojVektor(const MojVektor& other): capacity_{other.capacity_}, size_{other.size_}, arr_{new T[capacity_]}{
  std::copy(other.arr_, other.arr_+size_, arr_);
};

template<typename T>
MojVektor<T>::MojVektor(MojVektor&& other){
  capacity_=other.capacity_;
  size_=other.size_;
  arr_=other.arr_;

  other.arr_=nullptr;
  other.size_=other.capacity_=0;
};

template<typename T>
MojVektor<T>& MojVektor<T>::operator=(MojVektor&& other){
  if(this!=&other){
  delete [] arr_;
  capacity_=other.capacity_;
  size_=other.size_;
  arr_=other.arr_;

  other.arr_=nullptr;
  other.size_=other.capacity_=0;
  }
  return *this;
};

template<typename T>
MojVektor<T>::~MojVektor(){
  delete [] arr_;
  capacity_=size_=0;
};

template<typename T>
MojVektor<T>& MojVektor<T>::push_back(const T& value){
  if(full()) realoc();
  arr_[size_++]=value;
  return *this;
};

template<typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& value){
  if(full()) realoc();
  arr_[size_++]=std::move(value);

  return *this;
};

template<typename T>
bool MojVektor<T>::empty() const{
  if(size_==0) return true;
  else return false;
};

template<typename T>
bool MojVektor<T>::full() const{
  if(size_==capacity_) return true;
    else return false;
};

template<typename T>
size_t MojVektor<T>::capacity() const{
  return capacity_;
};

template<typename T>
size_t MojVektor<T>::size() const{
  return size_;
};

template<typename T>
void MojVektor<T>::realoc(){
  capacity_=2*capacity_;
  T* temp=new T[capacity_];
  *temp = std::move(*arr_);
};

template<typename T>
T& MojVektor<T>::back() const{
  if(empty()) throw std::out_of_range("Prazan vektor");
  return arr_[size_-1];
};

template<typename T>
T& MojVektor<T>::front() const{
  if(empty()) throw std::out_of_range("Prazan vektor");
  return arr_[0];
};


template<typename T>
void MojVektor<T>::clear(){
  *this=MojVektor<T>();
  arr_=nullptr;
};

template<typename T>
T& MojVektor<T>::at(size_t index) const{
  if(index>size_ || index<0) throw std::out_of_range("Nevalidna vrijednost");
  return arr_[index];
};

template<typename T>
T& MojVektor<T>::operator[](size_t index) const{
  return arr_[index];
};

template<typename T>
MojVektor<T>& MojVektor<T>::pop_back(){
  if(empty()) throw std::out_of_range("Prazan vektor");
  auto temp = std::move(arr_[size_-1]);
  size_--;
  return *this;
};

template<typename T>
MojVektor<T>& MojVektor<T>::pop_front(){
  if(empty()) throw std::out_of_range("Prazan vektor");
  for(auto i=0; i<size_-1; i++){
    arr_[i]=arr_[i+1];
  };
  size_--;
  return *this;
};

template<typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& element){
  if(full()) realoc();
  for(auto i=size_; i>0; i--) arr_[i]=arr_[i-1];
  arr_[0]=element;
  size_++;
  return *this;
};

template<typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& element){
  if(full()) realoc();
  if(size_==0){
    arr_[0]=std::move(element);}
  else{
  for(auto i=size_; i>0; i--) arr_[i]=arr_[i-1];
  arr_[0]=std::move(element);
  }
  size_++;
  return *this;
};

template<typename T>
void MojVektor<T>::resize(size_t newSize, const T& difference_value){
  if(newSize<=size_){
    size_=newSize;
  }
  else{
    if(newSize>=capacity_) realoc();
    for(auto i=size_; i<newSize; i++){
      arr_[i]=difference_value;
    }
  size_=newSize;
  }
};

template<typename T>
bool MojVektor<T>::operator==(const MojVektor<T>& other) const{
  if(size_!=other.size_) return false;
  for(auto i=0; i<size_; i++){
    if(arr_[i]!=other.arr_[i]) return false;
  }
  return true;
};

template<typename T>
bool MojVektor<T>::operator!=(const MojVektor<T>& other) const{
  if(size_!=other.size_) return true;
  for(auto i=0; i<size_; i++){
    if(arr_[i]!=other.arr_[i]) return true;
  }
  return false;
};

template<typename T>
void MojVektor<T>::rotate(){
  for(size_t i=0, j=size_-1; i<j; i++,j--){
    std::swap(arr_[i], arr_[j]);
  }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const MojVektor<T>& vec){
  out<<"{";
  if(!vec.empty()){
    for(size_t i=0; i<vec.size()-1; i++) out<<vec[i]<<", ";
    out<<vec[vec.size()-1];
  }
  out<<"}";
  return out;
};

//IMPLEMENTACIJA SUBKLASE ITERATOR I NJENIH OSNOVNIH OSOBINA.
template<typename T>
class MojVektor<T>::Iterator : public std::iterator<std::random_access_iterator_tag, T> {
  private:
    T* ptr_;
  public:
    Iterator(): ptr_{nullptr}{};

    Iterator(T* iter): ptr_{iter}{};

    Iterator(const Iterator& other){
      ptr_=other.ptr_;
    };

    Iterator(Iterator&& other){
      ptr_=other.ptr_;
      other.ptr_=nullptr;
    };

    Iterator& operator=(const Iterator& other){
      this->ptr_=other.ptr_;
      return *this;
    };

    Iterator operator[](const int index) const{
      return Iterator(ptr_+index);
    };

    Iterator& operator=(Iterator&& other){
      this->ptr_=other.ptr_;
      other.ptr_=nullptr;
      return *this;
    };
    
    Iterator& operator++(){
      ++ptr_;
      return *this;
    };

    Iterator operator++(int){
      return Iterator{ptr_++};
    };

    Iterator& operator--(){
      --ptr_;
      return *this;
    };

    Iterator operator--(int){
      return Iterator{ptr_--};
    };

    bool operator!=(const Iterator& other) const{
      return ptr_!=other.ptr_;
    };

    bool operator==(const Iterator& other) const{
      return ptr_==other.ptr_;
    };

    T& operator*(){
      return *ptr_;
    };

    T* operator->(){
      return ptr_;
    };

    size_t operator-(const Iterator& other) const{
      return ptr_-other.ptr_;
    };

    Iterator operator+(int n) const{
      return ptr_+n;
    };

    Iterator operator-(int n) const{
      return ptr_-n;
    };

    bool operator<(const Iterator& other) const{
      return ptr_<other.ptr_;
    };
};

template<typename T>
void MojVektor<T>::rotate(Iterator beginIt, Iterator endIt){
  for(Iterator it1=beginIt, it2=endIt-1; it1<it2; it1++, it2--){
    std::swap(*it1, *it2);
  }
};

template<typename T>
MojVektor<T> MojVektor<T>::subvector(Iterator begin, Iterator end){
  MojVektor<T> temp;
  for(Iterator it=begin; it!=end; it++) temp.push_back(*it);
  temp.size_=end-begin;
  return temp;
};

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator beginIt, Iterator endIt){
  size_t broj_obrisanih=endIt-beginIt;
  for(Iterator it=endIt; it!=end(); it++) *(it-broj_obrisanih)=*(it);
  size_-=broj_obrisanih;
  return Iterator(beginIt);
};

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator pos){
  if(pos!=end()){
  for(Iterator it=pos; it!=end()-1; it++) *(it)=*(it+1);
  size_--;}
  return Iterator(pos);
};

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator it, const T& element){
  size_t temp=it-begin();
  if(size_==capacity_) realoc();
  if(it==end()) throw std::out_of_range("Izvan dometa");
  for(size_t i=size_; i>temp; i--) arr_[i]=arr_[i-1];
  arr_[temp]=element;
  size_++;
  return Iterator(begin()+temp);
};

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator it, T&& element){
  size_t temp=it-begin();
  if(size_==capacity_) realoc();
  if(it==end()) throw std::out_of_range("Izvan dometa");
  for(size_t i=size_; i>temp; i--) arr_[i]=arr_[i-1];
  arr_[temp]=std::move(element);
  size_++;
  return Iterator(begin()+temp);
};
