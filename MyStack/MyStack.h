#pragma once

#include <iostream>

template<typename INF, typename FRIEND>
class ListNode {
 private:
    INF data;
    ListNode* next;
    friend FRIEND;

 public:
    ListNode() { next = nullptr; }
    ListNode(INF data) : data(data), next(nullptr) {}
    ListNode(const ListNode& object) : data(object.data), next(object.next) {}

    void setData(INF data);
    void setNext(ListNode* next);

    INF getData();
    ListNode* getNext();

    ListNode& operator=(const ListNode& object);
};

template<typename INF, typename FRIEND>
void ListNode<INF, FRIEND>::setData(INF data) {
    this->data = data;
}

template<typename INF, typename FRIEND>
void ListNode<INF, FRIEND>::setNext(ListNode* next) {
    this->next = next;
}

template<typename INF, typename FRIEND>
INF ListNode<INF, FRIEND>::getData() {
    return data;
}

template<typename INF, typename FRIEND>
ListNode<INF, FRIEND>* ListNode<INF, FRIEND>::getNext() {
    return next;
}

template<typename INF, typename FRIEND>
ListNode<INF, FRIEND>& ListNode<INF, FRIEND>::operator=(const ListNode<INF, FRIEND>& object) {
    data = object.data;
    next = object.next;
    return *this;
}

template<typename INF>
class MyStack {
 private:
    using Node = ListNode<INF, MyStack<INF>>;
    Node* top;

 public:
    MyStack() { top = nullptr; }
    MyStack(Node* top) { this->top = top; }
    MyStack(const MyStack<INF>& object);

    ~MyStack();

    Node* getTop() const { return top; }

    bool empty() const { return top == nullptr; }
    bool push(INF object);
    bool pop();
    void reverse();
    INF top_inf() { return top->data; }

    MyStack& operator=(const MyStack& object);

    friend std::ostream& operator<<(std::ostream& out, const MyStack<INF>& object);
};

template<class INF>
MyStack<INF>::MyStack(const MyStack<INF>& object) {
    top = nullptr;

    if (object.empty()) {
        return;
    }

    MyStack<INF> temporaryStack;
    Node* temp = object.top;

    while (temp) {
        temporaryStack.push(temp->data);
        temp = temp->next;
    }

    temp = temporaryStack.top;

    while (temp) {
        push(temp->data);
        temp = temp->next;
    }
}

template<class INF>
MyStack<INF>::~MyStack() {
    if (!top) {
        return;
    }

    while (top) {
        pop();
    }
}

template<class INF>
bool MyStack<INF>::push(INF object) {
    Node* node = new Node;
    node->data = object;
    node->next = top;
    top = node;
    return true;
}

template<class INF>
bool MyStack<INF>::pop() {
    if (!top) {
        return true;
    }

    if (!top->next) {
        delete top;
        top = nullptr;
        return true;
    }

    Node* temp = top->next;

    if (top) {
        delete top;
    }
    
    top = temp;
    return true;
}

template<class INF>
void MyStack<INF>::reverse() {
    MyStack<INF> reversedStack;

    Node* temp = top;

    while (temp) {
        reversedStack.push(temp->data);
        temp = temp->next;
    }

    *this = reversedStack;
}

template<class INF>
MyStack<INF>& MyStack<INF>::operator=(const MyStack<INF>& object) {
    while (top) {
        pop();
    }

    if (object.empty()) {
        return *this;
    }

    MyStack<INF> temporaryStack;
    Node* temp = object.top;

    while (temp) {
        temporaryStack.push(temp->data);
        temp = temp->next;
    }

    temp = temporaryStack.top;

    while (temp) {
        push(temp->data);
        temp = temp->next;
    }

    return *this;
}

template<class INF>
std::ostream& operator<<(std::ostream& out, const MyStack<INF>& object) {
    if (!object.top) {
        return out;
    }

    ListNode<INF, MyStack<INF>>* temp = object.getTop();
    out << temp->data;
    temp = temp->next;

    while (temp) {
        out << ' ' << temp->data;
        temp = temp->next;
    }
    return out;
}
