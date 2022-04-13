#include <iostream>

#include "branched-linked-list.hpp"


int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');
  first->PushBack('!');
  first->PushBack('!');
  first->PushBack('!');
  first->PushBack('!');

  std::cout << "First Head is: " << first->head_->data_ << std::endl;
  std::cout << first->ToString() << std::endl; // hi
  std::cout << first->Size() << std::endl; // 2

  std::cout << "/////////////////////////////////////"<< std::endl;

  BLL* second = new BLL();
  second->PushBack('y');
  second->PushBack('#');
  second->PushBack('@');

  Node* temp = second->head_;
  while (temp->next_node_ != nullptr) {
    temp = temp->next_node_;
  }
  temp->next_node_ = first->head_;

  std::cout << "Second Head is: " << second->head_->data_ << std::endl;
  std::cout << second->ToString() << std::endl; // i!@
  std::cout << second->Size() << std::endl; // 3

  std::cout << "/////////////////////////////////////"<< std::endl;

  // BLL* third = new BLL();
  // third->PushBack('y');
  // third->PushBack('#');
  // third->PushBack('@');

  // first->Join(3, third);
  // std::cout << "First Head is: " << first->head_->data_ << std::endl;
  // // std::cout << "First bll is: " << first->head_->next_bll_->head_->data_ << std::endl;
  // std::cout << first->ToString() << std::endl; // hii!@
  // std::cout << first->Size() << std::endl;
  // std::cout << "/////////////////////////////////////"<< std::endl;


  first->Join(0, second);

  std::cout << "First Head is: " << first->head_->data_ << std::endl;
  // std::cout << "First bll is: " << first->head_->next_bll_->head_->data_ << std::endl;
  std::cout << first->ToString() << std::endl; // hii!@
  std::cout << first->Size() << std::endl;
  // first->SetAt(4, '!');
  // std::cout << "First Head is: " << first->head_->data_ << std::endl;
  // std::cout << first->ToString() << std::endl; // hii!@!
  // std::cout << first->Size() << std::endl; // 5

  // second->SetAt(2, '!');
  // std::cout << second->ToString() << std::endl; // i!@
  // std::cout << second->Size() << std::endl; // 3

  std::cout << "/////////////////////////////////////"<< std::endl;

  // // BLL* third = new BLL();
  // BLL* first_clone = first;
  

  // std::cout << "First_clone Head is: " << first_clone->head_->data_ << std::endl;
  // std::cout << first_clone->ToString() << std::endl; // hii!@
  // std::cout << first_clone->Size() << std::endl; // 5

  // std::cout << "/////////////////////////////////////"<< std::endl;

  // BLL* third = new BLL();
  // third->PushBack('H');
  // third->PushBack('e');
  // third->PushBack('l');
  // third->PushBack('l');
  // third->PushBack('o');

  // std::cout << "Third head is: " << third->head_->data_ << std::endl;
  // //  std::cout << "Third head next bll is: " << third->head_->next_bll_->head_->data_ << std::endl;
  // std::cout << third->ToString() << std::endl; // hii!@
  // std::cout << third->Size() << std::endl; // 5
  // std::cout << "/////////////////////////////////////"<< std::endl;

  
  // first->Join(2, third);
  // // std::cout << second->ToString() << std::endl; 
  // // std::cout << second->Size() << std::endl; 

  // std::cout << "First Head is: " << first->head_->data_ << std::endl;
  // std::cout << "First bll is: " << first->head_->next_bll_->head_->data_ << std::endl;
  // std::cout << first->ToString() << std::endl; // hii!@
  // std::cout << first->Size() << std::endl;


  // // BLL* fourth = first;
  // BLL* fourth = first;
  // std::cout << "fourth head is: " << fourth->head_->data_ << std::endl;
  // std::cout << fourth->ToString() << std::endl;
  // std::cout << fourth->Size() << std::endl;


  first->~BLL();
  delete first;
  // second->~BLL();
  // delete second;
  // delete third;
  // fourth->~BLL();
  // delete fourth;
  // first_clone->~BLL();
  // delete first_clone;

  return 0;
}
