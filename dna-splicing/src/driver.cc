#include <iostream>

#include "dna_strand.hpp"
using namespace std;

int main() {
    DNAstrand dna1;
    string s1 = "gtctgaagtcgccgaacttgavttcgccgaactcgccgaacttgpattcgccgaagtcgggaacrttaactgatc";
    // string s1 = "ctatat";
    for (char c : s1) {
        Node* temp = new Node(c);
        if (dna1.head_ == nullptr) {                   //  Add head
             dna1.tail_ = dna1.head_ = temp;
             continue;
        }
        dna1.tail_->next = temp;
        dna1.tail_ = temp;
    }

    Node* curr = dna1.head_;
    cout << '\n';
    while(curr != nullptr) {
        if (curr->next == nullptr) {
            cout << curr->data;
        } else {
            cout << curr->data << "->";
        }
        curr = curr->next;
    }
    cout << endl;
    cout << "Above is DNA1 unchanged" << endl;
    cout << "Head before change: " << dna1.head_->data << endl;
    cout << "tail before change: " << dna1.tail_->data << endl;

    DNAstrand dna2;
    string c1 = "tgatc";
    for (char c : c1) {
        Node* temp = new Node(c);
        if (dna2.head_ == nullptr) {                   //  Add head
             dna2.tail_ = dna2.head_ = temp;
             continue;
        }
        dna2.tail_->next = temp;
        dna2.tail_ = temp;
    }

    cout << endl;
    Node* cur = dna2.head_;
    while(cur != nullptr) {
        if (cur->next == nullptr) {
            cout << cur->data;
        } else {
            cout << cur->data << "->";
        }
        cur = cur->next;
    }
    cout << '\n';
    cout << "Above is DNA2" << endl;


    string s2 = "tga";
    const char *c2 = s2.c_str();
    cout << endl;
    cout << c2 << endl;
    cout << "Above is char*" << endl;

    cout << endl;
    dna1.SpliceIn(c2, dna2);
    Node* curr2 = dna1.head_;
    while(curr2 != nullptr) {
        if (curr2->next == nullptr) {
            cout << curr2->data;
        } else {
            cout << curr2->data << "->";
        }
        curr2 = curr2->next;
    }
    cout << endl;
    cout << "Above is DNA1 changed" << endl;
    cout << "Head after change: " << dna1.head_->data << endl;
    cout << "tail after change: " << dna1.tail_->data << endl;
    cout << endl;
}