#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  CircularLinkedList<int> cll;
  cll.InsertInOrder(12);
  cll.InsertInOrder(12);
  cll.InsertInOrder(12);
  cll.InsertInOrder(12);
  cll.InsertInOrder(12);
  cll.InsertInOrder(13);
  cll.InsertInOrder(6);
  cll.InsertInOrder(6);
  cll.InsertInOrder(3);
  cll.InsertInOrder(3);
  cll.InsertInOrder(3);
  cll.InsertInOrder(1);
  cll.InsertInOrder(4);
  cll.InsertInOrder(4);
  cll.InsertInOrder(2);
  cll.InsertInOrder(5);
  std::cout << cll << std::endl;
  std::cout << "Head: " << cll.tail_->next->data << std::endl;
  std::cout << "Tail:" << cll.tail_->data << std::endl;


  CircularLinkedList<int> cll5;
  cll5.InsertInOrder(12);
  cll5.InsertInOrder(6);
  cll5.InsertInOrder(1);
  cll5.InsertInOrder(4);
  cll5.InsertInOrder(2);
  cll5.InsertInOrder(5);
  std::cout << cll5 << std::endl;
  std::cout << "Head: " << cll5.tail_->next->data << std::endl;
  std::cout << "Tail:" << cll5.tail_->data << std::endl;

  CircularLinkedList<int> cll2 = CircularLinkedList<int>(cll);
  CircularLinkedList<int> cll3;
  cll3 = cll2 = cll5;

  std::cout << cll2 << std::endl;
  std::cout << "Head: " << cll2.tail_->next->data << std::endl;
  std::cout << "Tail:" << cll2.tail_->data << std::endl;

  std::cout << cll3 << std::endl;
  std::cout << "Head: " << cll3.tail_->next->data << std::endl;
  std::cout << "Tail:" << cll3.tail_->data << std::endl;

  cll.Reverse();
  cll.InsertInOrder(22);
  cll.InsertInOrder(20);
  cll.InsertInOrder(23);
  cll.InsertInOrder(21);
  cll.InsertInOrder(12);
  std::cout << cll << std::endl;
  std::cout << "Head: " << cll.tail_->next->data << std::endl;
  std::cout << "Tail:" << cll.tail_->data << std::endl;
}
