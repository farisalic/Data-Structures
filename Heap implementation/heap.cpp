#include"heap.hpp"
#include<iostream>

int main(int argc, char *argv[])
{
  BinaryHeap<int> heap;

  heap.insert(10);
  heap.insert(20);
  heap.insert(8);
  heap.insert(3);
  heap.insert(12);

  std::cout << "Heap prije bilo kakvih izmjena: " << std::endl;
  heap.print();

  std::cout << "Copy konstruktor: " << std::endl;
  BinaryHeap<int> heap1(heap);
  heap1.print();

  std::cout << "Testiranje move konstruktora: " << std::endl;
  BinaryHeap<int> heap2(std::move(heap1));
  heap2.print();
  std::cout << "Heap1 nakon move-a: " << std::endl;
  heap1.print();

  std::cout << "Testiranje copy=: " << std::endl;
  BinaryHeap<int> heap3 = heap;
  heap3.print();

  std::cout << "////////////////////////////" << std::endl;
  std::cout << "Testiranje max metoda i re-heapa: " << std::endl;
  auto maks=heap.max();
  std::cout << maks << std::endl;
  heap.popMax();
  heap.print();
  std::cout << "////////////////////////////" << std::endl;

  std::cout << "Metod clear" << std::endl;
  heap.clear();
  heap.print();
  return 0;
}
