#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "doublyLinkedList.h"

using namespace std;

class Admin
{
public:
    string username;
    string password;
    Admin *next;
    Admin *prev;

    string getUsername() const
    {
        return username;
    }

    void setUsername(string username)
    {
        this->username = username;
    }

    string getPassword() const
    {
        return password;
    }

    void setPassword(string username)
    {
        this->password = password;
    }

    Admin *getNext() const
    {
        return next;
    }

    void setNext(Admin *next)
    {
        this->next = next;
    }

    Admin *getPrev() const
    {
        return prev;
    }

    void setPrev(Admin *prev)
    {
        this->prev = prev;
    }

    void addAdmin(string username, string password);
    void viewAdmin();
    bool adminLoginV(string username, string password);
};


struct Admin *adminhead = NULL;
struct Admin *admintail = NULL;
struct Admin *admintemp;

void Admin::addAdmin(string username, string password)
{
    Admin *newNode = new Admin;
    newNode->username = username;
    newNode->password = password;

    newNode->next = NULL;
    newNode->prev = admintail;
    admintail = newNode;
    if (adminhead == NULL)
    {
        adminhead = newNode;
    }
    else
    {
        newNode->prev->next = newNode;
    }
}

void Admin::viewAdmin()
{
    admintemp = adminhead;
    cout << endl
         << left << setw(20) << "Username" << left << setw(20)
         << "|Password" << left << setw(20) << endl;
        cout
         << string(90, '-') << endl;

    if ((adminhead == NULL) && (admintemp == NULL))
    {
        cout << string(10, ' ') << "     User List is Empty   " << endl;
        return;
    }
    while (admintemp != NULL)
    {
        cout << left << setw(20) << admintemp->username << setw(1) << "|" << left
             << setw(19) << admintemp->password << endl;
        admintemp = admintemp->next;
    }
}

bool Admin::adminLoginV(string username, string password)
{
    admintemp = admintail;
    while (admintemp != nullptr)
    {
        if (admintemp->username == username && admintemp->password == password)
        {
            return true;
        }
        admintemp = admintemp->prev;
    }
    return false;
}
