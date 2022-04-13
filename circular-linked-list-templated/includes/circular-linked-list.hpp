#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"


enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
 public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

 private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  if (source.head_ == nullptr) {        // Return when source is NULL
    return;
  }
  node_order_ = source.node_order_;     // Set the order
  Node<T>* trav = source.head_;
  do {                                  // Construct the Linked List
    InsertInOrder(trav->data);          // using do-while loop
    trav = trav->next;
  } while (trav != source.head_);
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  while (head_ != tail_) {              // Traverse until tail_
    Node<T>* temp = head_;              // Cannot traverse until nullptr, 
    head_ = head_->next;                // 'cause you may access a deleted memory (head_)
    delete temp;
  }
  delete tail_;                         // delete tail_ separately
  head_ = nullptr;
  tail_ = nullptr;
  node_order_ = Order::kASC;
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source) {
  if (this == &source) {              // If source has the same memory address as *this
    return *this;
  }
  this->~CircularLinkedList();        // Release the memory of *this
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {      // Return when source is NULL
    return *this;
  }
  Node<T>* trav = source.head_;
  do {                                // Construct the Linked List
    InsertInOrder(trav->data);
    trav = trav->next;
  } while (trav != source.head_);
  return *this;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  Node<T>* trav = head_;
  auto new_node = new Node<T>(data);
  if (head_ == nullptr) {                  // If the linked list is NULL
    head_ = tail_ = new_node;
    tail_->next = head_;
    return;
  }                                        
  if (this->node_order_ == Order::kASC) {  // Ascending order
    do {                                   // Traverse until head_
      if (head_->data > data) {            // If data less than head_
        new_node->next = head_;
        tail_->next = new_node;
        head_ = new_node;
        break;
      } else if (tail_->data <= data) {    // if data greater than or equal to tail_
        new_node->next = head_;
        tail_->next = new_node;
        tail_ = new_node;
        break;
      } else if (trav->data <= data && trav->next->data >= data) {  // Within the Linked List
        new_node->next = trav->next;
        trav->next = new_node;
        break;
      }
      trav = trav->next;
    } while (trav != head_);
  } else {                       // Descending Order
    do {                         // Traverse until head_
      if (head_->data < data) {  // If data greater than head_ less than tail_
        new_node->next = head_;
        tail_->next = new_node;
        head_ = new_node;
        break;
      } else if (tail_->data >= data) {  // If data less than or equal to tail_
        new_node->next = head_;
        tail_->next = new_node;
        tail_ = new_node;
        break;
      } else if (trav->data >= data && trav->next->data <= data) {  // Within the Linked List
        new_node->next = trav->next;
        trav->next = new_node;
        break;
      }
      trav = trav->next;
    } while (trav != head_);
  }
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (head_ == nullptr || head_ == tail_) {     // if *this is NULL or only has one node, 
    if (node_order_ == Order::kASC) {           // just change the order of *this
      node_order_ = Order::kDESC;
    } else {
      node_order_ = Order::kASC;
    }
    return;
  }
  Node<T>* trav = head_;
  Node<T>* pre_trav = tail_;                    // Get the previous node of trav
  head_ = tail_;                                // Reverse head and tail
  tail_ = trav;
  do {                                          // Construct the Linked List
    Node<T>* temp1 = trav;                      // Save the node of trav and pre_trav
    Node<T>* temp2 = pre_trav;
    pre_trav = trav;                            // Increment both pre_trav and trav by one node
    trav = trav->next;
    temp1->next = temp2;                        // Reverse the direction of node->next
  } while (trav != tail_);
  if (node_order_ == Order::kASC) {             // Change the order
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
}

#endif
