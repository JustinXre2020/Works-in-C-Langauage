#include "branched-linked-list.hpp"

BLL::BLL() {
    head_ = nullptr;
}


BLL::BLL(const BLL& to_copy) {
    head_ = nullptr;
    if (to_copy.head_ == nullptr) {
        return;
    }
    Node* trav = to_copy.head_;
    while (trav != nullptr) {
        Node* new_node = this->PushBack(trav->data_);
        if (trav->next_bll_ != nullptr) { // If the current Node has a linked BLL
            new_node->next_bll_ = new BLL(*trav->next_bll_);
        }   
        trav = trav->next_node_;
    }
}


BLL::~BLL() {
    while (head_ != nullptr) {
        Node* temp = head_;
        if (temp->next_bll_ != nullptr) { // If the current Node has a linked BLL
            temp->next_bll_->~BLL();
            delete temp->next_bll_;
        }    
        head_ = head_->next_node_;
        delete temp;
    }
}


BLL& BLL::operator=(const BLL& rhs) {
    if (this == &rhs) {
        return *this;
    }
    this->~BLL();
    if (rhs.head_ == nullptr) {
        head_ = nullptr;
        return *this;
    }
    Node* trav = rhs.head_;
    while (trav != nullptr) {
        Node* node = this->PushBack(trav->data_);
        if (trav->next_bll_ != nullptr) {       // If the current Node has a linked BLL
            node->next_bll_ = new BLL(*trav->next_bll_);
        }   
        trav = trav->next_node_;
    }
    return *this;
}


bool BLL::IsBLLAcyclic() const {
    if (head_ == nullptr) 
        return true;
    Node* node1 = head_;
    Node* node2 = head_->next_node_;
    while (node1 != nullptr && node2 != nullptr) {
        if (node1 == node2)  
            return false;
        node2 = node2->next_bll_ != nullptr ? node2->next_bll_->head_ : node2->next_node_;
        if (node2 == nullptr) 
            break;
        node2 = node2->next_bll_ != nullptr ? node2->next_bll_->head_ : node2->next_node_;
        node1 = node1->next_bll_ != nullptr ? node1->next_bll_->head_ : node1->next_node_;
    }
    return true;
}


Node* BLL::PushBack(char dat) {
    Node* new_node = new Node(dat);
    if (head_ == nullptr) {
        head_ = new_node;
    } else {
        Node* last = head_;
        while (last->next_node_ != nullptr) { // Find the current last node
            last = last->next_node_;
        }
        last->next_node_ = new_node;
    }
    return new_node;
}


char BLL::GetAt(size_t idx) const {
    size_t count = 0;
    Node* trav = head_;
    bool in_linked_bll = false;
    Node* begin_another_bll = nullptr;
    while (trav != nullptr) {
        if (count == idx) {
            return trav->data_;
        }
        count++;
        if (trav->next_bll_ != nullptr) { // If the current Node has a linked BLL
            in_linked_bll = true;
            begin_another_bll = trav;
            trav = trav->next_bll_->head_;
        } else if (in_linked_bll && trav->next_node_ == nullptr) { // If reaches the end of linked BILL
            trav = begin_another_bll->next_node_;
            in_linked_bll = false;
        } else {   // Base case
          trav = trav->next_node_;
        }
    }
    throw std::runtime_error("idx out of bounds!"); // If trav reaches the end, throw exception 
}


void BLL::SetAt(size_t idx, char dat) {
    size_t count = 0;
    Node* trav = head_;
    bool in_linked_bll = false;
    Node* begin_another_bll = nullptr;
    while (count < this->Size() && idx >= 0) {
        if (count == idx) {
            trav->data_ = dat;
            return;
        }
        count++;
        if (trav->next_bll_ != nullptr) { // If the current Node has a linked BLL
            in_linked_bll = true;
            begin_another_bll = trav;
            trav = trav->next_bll_->head_;
        } else if (in_linked_bll && trav->next_node_ == nullptr) { // If reaches the end of linked BILL
            trav = begin_another_bll->next_node_;
            in_linked_bll = false;
        } else {   // Base case
          trav = trav->next_node_;
        }
    }
    throw std::runtime_error("idx out of bounds!"); // If trav reaches the end, throw exception 
}


void BLL::Join(size_t idx, BLL* list) {
    size_t count = 0;
    Node* trav = head_;
    bool in_linked_bll = false;
    Node* begin_another_bll = nullptr;
    if (idx >= Size() || idx < 0) {
        throw std::runtime_error("idx is not within the size of BLL!");
    }
    while (trav != nullptr) {
        if (count == idx) {
            if (trav->next_bll_ != nullptr) {
                throw std::runtime_error("idx cannot insert the list!");
            }
            trav->next_bll_ = list;
            if (!IsBLLAcyclic()) {
                trav->next_bll_ = nullptr;
                throw std::runtime_error("The list now is cyclic!");
            }
            return;
        }
        count++;
        if (trav->next_bll_ != nullptr) { // If the current Node has a linked BLL
            in_linked_bll = true;
            begin_another_bll = trav;
            trav = trav->next_bll_->head_;
        } else if (in_linked_bll && trav->next_node_ == nullptr) { // If reaches the end of linked BILL
            trav = begin_another_bll->next_node_;
            in_linked_bll = false;
        } else {   // Base case
          trav = trav->next_node_;
        }
    }
}


std::string BLL::ToString() const {
    std::string s;
    if (head_ == nullptr) {
        return s;
    }
    Node* trav = head_;
    while (trav != nullptr) {
        s += trav->data_;
        if (trav->next_bll_ != nullptr) { // If the current Node has a linked BLL
            s += trav->next_bll_->ToString();
        }
        trav = trav->next_node_;
    }
    return s;
}

size_t BLL::Size() const {
    size_t count = 0;
    Node* trav = head_;
    while (trav != nullptr) {
        count++;
        if (trav->next_bll_ != nullptr) { // If the current Node has a linked BLL
            count += trav->next_bll_->Size();
        }
        trav = trav->next_node_;
    }
    return count;
}