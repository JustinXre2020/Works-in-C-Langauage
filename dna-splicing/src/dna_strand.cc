#include "dna_strand.hpp"
#include <cassert>
#include <stdexcept>

// Delete a DNA strand
DNAstrand::~DNAstrand() {
  while (head_ != nullptr) { 
    Node* curr = head_;
    head_ = head_->next;
    delete curr;
  }
}

// Compare two char* with equal length, true if they are equal, false if there are not
bool DNAstrand::IsEqual(const char* c1, const char* c2, int length) {
  for (int i = 0; i < length; ++i) {
    if (c1[i] != c2[i]) {
      return false;
    }
  }
  return true;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  Node* traverse = head_;                // Set the traverse node
  Node* start = nullptr;                 // The node that we start to delete
  Node* curr = head_;                    // The node that point to "start" node
  int size = 0;                         
  while (pattern[size] != '\0') size++;  // Get the size of pattern
  while (traverse != nullptr) {          // Traverse to find the start node
    char* c1 = new char[size];
    for (int j = 0; j < size; ++j) {     // Initialize the char array (This is mandatory)
      c1[j] = '0';
    }
    if (traverse->data == pattern[0]) {
      Node* temp = traverse;
      for (int j = 0; j < size; ++j) {
        if (temp == nullptr) {           // If temp reaches the end of the DNA strand, break the for loop
          break;
        }
        c1[j] = temp->data;
        temp = temp->next;
      }
    }
    if (IsEqual(c1, pattern, size)) {    // If the char array equals the pattern, then we start here
      start = traverse;
    }
    delete[] c1;                         // Delete the char array every time we create it
    traverse = traverse->next;
  }
  if (start == nullptr) {                // Throw exception when cannot find the pattern
    throw std::runtime_error("Did not find the pattern!"); 
  }
  if (start == head_) {                  // If the pattern starts at head_
    head_ = nullptr;                     // Assign head_ to nullptr if we need to delete from start
    curr = head_;                        // curr should be head_ as well
  } else {                               
    traverse = head_;
    while (traverse != nullptr) {        // traverse to find "curr" that points to "start"
      if (traverse->next == start) {
        curr = traverse;
      }
      traverse = traverse->next;
    }
  }
  for (int i = 0; i < size; ++i) {       // Traverse to delete
    Node* change = start;
    start = start->next;                 // start will reach the DNA node right after the pattern
    delete change;                       // and if could be nullptr 
  }
  if (start == nullptr) {                // If pattern is at the end of DNA
    curr->next = to_splice_in.head_;
    tail_ = to_splice_in.tail_;
  } else if (head_ != nullptr) {         // If pattern is in the middle
    curr->next = to_splice_in.head_;
    to_splice_in.tail_->next = start;
  } else if (head_ == nullptr) {         // If pattern is at the beginning
    head_ = to_splice_in.head_;
    to_splice_in.tail_->next = start;
  }
  to_splice_in.head_ = nullptr;          // Set to splice in DNA strand to nullptr
  to_splice_in.tail_ = nullptr;
}