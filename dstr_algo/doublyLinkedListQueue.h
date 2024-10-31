#pragma once
#include "doublyLinkedList.h"

template <typename T>
class DoublyLinkedListQueue {
public:
    DoublyLinkedListQueue() : head(nullptr), tail(nullptr) {}

    bool isEmpty() const {
        return head == nullptr;
    }

    void enqueue(const T& data) {
        if (isEmpty()) {
            head = tail = new DoublyNode<T>(data);
        } else {
            tail->next = new DoublyNode<T>(data, nullptr, tail);
            tail = tail->next;
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            DoublyNode<T>* temp = head;
            head = head->next;
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete temp;
        }
    }

    T front() const {
        if (!isEmpty()) {
            return head->data;
        }
        return T();
    }

    bool isEmpty() {
        return head == nullptr;
    }

    int getSize() {
        int count = 0;
        DoublyNode<T>* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    DoublyNode<T>* getHead() const {
        return head;
    }

    ~DoublyLinkedListQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

private:
    DoublyNode<T>* head;
    DoublyNode<T>* tail;
};
