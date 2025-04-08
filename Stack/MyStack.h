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

    ListNode& operator=(const ListNode& object) {
        data = object.data;
        next = object.next;
        return *this;
    }
};

template<typename INF>
class MyStack {
 private:
    using Node = ListNode<INF, MyStack<INF>>;
    Node* top;

    Node* getTop() const { return top; }

 public:
    MyStack() { top = nullptr; }
    MyStack(Node* top) { this->top = top; }

    MyStack(const MyStack<INF>& object) {
        top = nullptr;

        if (object.empty()) {
            return;
        }

        MyStack temporaryStack;
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

    ~MyStack() {
        if (!top) {
            return;
        }

        while (top) {
            pop();
        }
    }

    bool empty() const { return (top == nullptr); }

    bool push(INF object) {
        Node* node = new Node;
        node->data = object;
        node->next = top;
        top = node;
        return true;
    }

    bool pop() {
        if (!top) {
            return true;
        }

        if (!top->next) {
            delete top;
            top = nullptr;
            return true;
        }

        Node* temp = top->next;
        delete top;
        top = temp;
        return true;
    }

    void reverse() {
        MyStack<INF> reversedStack;

        Node* temp = top;

        while (temp) {
            reversedStack.push(temp->data);
            temp = temp->next;
        }

        *this = reversedStack;
    }

    INF top_inf() { return top->data; }

    MyStack& operator=(const MyStack& object) {
        while (top) {
            pop();
        }

        if (object.empty()) {
            return *this;
        }

        MyStack temporaryStack;
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

    friend std::ostream& operator<<(std::ostream& out, const MyStack<INF>& object) {
        if (!object.top) {
            return out;
        }

        Node* temp = object.getTop();
        out << temp->data << ' ';
        temp = temp->next;

        while (temp) {
            out << "* " << temp->data << ' ';
            temp = temp->next;
        }
        return out;
    }
};
