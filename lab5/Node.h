// Node.h
#pragma once
#include <string>
#include <iostream>
using namespace std;

class Node {
public:
    string data;
    Node* next;

    Node() : next(nullptr) {}
    Node(const string &na) : data(na), next(nullptr) {}

    void print() const {
        cout << data << "->";
    }
    friend ostream& operator<<(ostream & out, const Node & obj);
};

ostream& operator<<(ostream& out, const Node& obj) {
    out << obj.data << "->";
    return out;
}