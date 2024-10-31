#pragma once
#include <iostream>

using namespace std;

template <class T>

class DoublyNode
{
public:
    T data;
    DoublyNode<T> *prev;
    DoublyNode<T> *next;

    // Constructors
    DoublyNode() : prev(nullptr), next(nullptr) {}
    DoublyNode(const T &data) : data(data), prev(nullptr), next(nullptr) {}
    DoublyNode(const T &data, DoublyNode<T> *next, DoublyNode<T> *prev)
        : data(data), next(next), prev(prev) {}
};

template <class T>

class DoublyLinkedList
{
public:
    DoublyNode<T> *head;
    DoublyNode<T> *tail;

    int size;

    DoublyLinkedList()
    {
        //        cout << "--- Constructing the Doubly LinkedList object ---" << endl;
        this->size = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    void insertAtbeginning(T elem)
    {
        DoublyNode<T> *newNode = new DoublyNode<T>;
        newNode->data = elem;
        newNode->prev = nullptr;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            // If the list is empty, the new node will be both the head and the tail
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void insertAtEnd(T elem)
    {

        DoublyNode<T> *newNode = new DoublyNode<T>;
        newNode->data = elem;
        newNode->next = nullptr;
        newNode->prev = tail; // update prev of newNode to point to current lastNode
        tail = newNode;       // update tail to point to newNode = lastNode

        if (head == nullptr)
        {
            head = newNode; // if the 1st is empty, head and tail point the newNode
        }
        else
        {
            newNode->prev->next = newNode; // update the 2nd lastNode to point to newNode
        }

        size++;
    }
    void insert(const T *data)
    {
        DoublyNode<T> *newNode = new DoublyNode<T>;
        newNode->data = *data; // Dereference the pointer to get the actual data
        newNode->next = nullptr;
        newNode->prev = tail;

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            tail->next = newNode;
        }

        tail = newNode;
        size++;
    }

    int getSize() const
    {
        return size;
    }
    
    void insertItemAt(T elem, int index)
    {
        if (index <= size)
        {
            if (index == 0)
            {
                insertAtbeginning(elem);
            }
            else if (index == size)
            {
                insertAtEnd(elem);
            }
            else
            {

                DoublyNode<T> newNode = new DoublyNode<T>;
                newNode->data = elem;
                DoublyNode<T> before = head;

                for (int i = 0; i < index; i++)
                {
                    before = before->next;
                }

                newNode->next = before;
                newNode->prev = before->prev;
                before->prev = newNode;
                newNode->prev->next = newNode;

                size++;
            }
        }
    }

    void showAll()
    {
        DoublyNode<T> *curr = head;
        cout << "\n--- ALL = " << size << " elements ---" << endl;

        while (curr != nullptr)
        {
            cout << curr->data << endl;
            curr = curr->next;
        }
    }

    void deleteAtEnd()
    {

        if (tail == nullptr)
        {
            cout << "Linked list is empty. Cannot delete from end." << endl;
            return;
        }

        cout << "Deleting from the end" << endl;

        DoublyNode<T> *temp = tail;
        tail = tail->prev;

        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }

        delete temp;

        size--;
    }


    bool isEmpty()
    {
        return head == nullptr;
    };

    // quick sort
    void quickSort(bool (*compareFunc)(const T &, const T &))
    {
        quickSortRec(head, tail, compareFunc);
    }

    // insertion sort
    void insertionSort(bool (*compareFunc)(const T &, const T &))
    {
        if (head == nullptr || head->next == nullptr)
        {
            // The list is empty or contains only one element, already sorted.
            return;
        }

        DoublyNode<T> *current = head->next; // Pointer to the current unsorted element

        while (current != nullptr)
        {
            DoublyNode<T> *prevNode = current->prev; // Store the previous node

            while (prevNode != nullptr && compareFunc(prevNode->data, current->data))
            {
                prevNode = prevNode->prev; // Move to the previous node
            }

            // Remove current node from its position
            current->prev->next = current->next;
            if (current->next != nullptr)
            {
                current->next->prev = current->prev;
            }

            if (prevNode == nullptr)
            {
                // Insert the current node at the beginning of the sorted list
                current->prev = nullptr;
                current->next = head;
                head->prev = current;
                head = current;
            }
            else
            {
                // Insert the current node after the prevNode
                current->prev = prevNode;
                current->next = prevNode->next;
                prevNode->next = current;
                if (current->next != nullptr)
                {
                    current->next->prev = current;
                }
                else
                {
                    // Update the tail pointer if current becomes the last node
                    tail = current;
                }
            }

            // Move to the next unsorted element
            current = current->next;
        }
    }

    // binary search
    DoublyNode<T> *binarySearch(const string &propertyId) const
    {
        DoublyNode<T> *left = head;
        DoublyNode<T> *right = tail;

        while (left && right && left != right->next)
        {
            DoublyNode<T> *mid = left;
            int count = 0;
            while (mid != right && count < 2)
            {
                mid = mid->next;
                count++;
            }

            if (mid->data.getAdsId() == propertyId)
            {
                return mid;
            }
            else if (mid->data.getAdsId() < propertyId)
            {
                left = mid->next;
            }
            else
            {
                right = mid->prev;
            }
        }

        return nullptr; // Property ID not found in the list
    }

    // linear search
    template <typename F>
    DoublyNode<T> *linearSearch(F func) const
    {
        DoublyNode<T> *currentNode = head;
        while (currentNode != nullptr)
        {
            if (func(currentNode->data))
            {
                return currentNode; // Found the node matching the condition
            }
            currentNode = currentNode->next;
        }

        return nullptr; // Element not found in the list
    }

private:
    // quick sort
    DoublyNode<T> *partition(DoublyNode<T> *low, DoublyNode<T> *high, bool (*compareFunc)(const T &, const T &))
    {
        T pivot = high->data;
        DoublyNode<T> *i = low->prev;

        for (DoublyNode<T> *j = low; j != high; j = j->next)
        {
            if (compareFunc(j->data, pivot))
            {
                i = (i == nullptr) ? low : i->next;
                swap(i->data, j->data);
            }
        }

        i = (i == nullptr) ? low : i->next;
        swap(i->data, high->data);
        return i;
    }

    // recursive quick sort
    void quickSortRec(DoublyNode<T> *low, DoublyNode<T> *high, bool (*compareFunc)(const T &, const T &))
    {
        if (high != nullptr && low != high && low != high->next)
        {
            DoublyNode<T> *pivot = partition(low, high, compareFunc);
            quickSortRec(low, pivot->prev, compareFunc);
            quickSortRec(pivot->next, high, compareFunc);
        }
    }
};
