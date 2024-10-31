#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "property.h"
#include "doublyLinkedList.h"
#include "doublyLinkedListQueue.h"

using namespace std;

class Manager
{
public:
    string username;
    string password;
    string fullname;
    string contact;
    bool active;
    Manager *next;
    Manager *prev;

    // Default constructor
    Manager()
        : username(""), password(""), fullname(""), contact(""), active(false), next(nullptr), prev(nullptr) {}

    // Parameterized constructor
    Manager(string un, string pw, string fn, string cn, bool ac)
        : username(un), password(pw), fullname(fn), contact(cn), active(ac), next(nullptr), prev(nullptr) {}

    // Getter and Setter for Username
    string getUsername() const
    {
        return username;
    }

    void setUsername(string un)
    {
        username = un;
    }

    // Getter and Setter for Password
    string getPassword() const
    {
        return password;
    }

    void setPassword(string pw)
    {
        password = pw;
    }

    // Getter and Setter for Fullname
    string getFullname() const
    {
        return fullname;
    }

    void setFullname(string fn)
    {
        fullname = fn;
    }

    // Getter and Setter for Contact
    string getContact() const
    {
        return contact;
    }

    void setContact(string cn)
    {
        contact = cn;
    }

    // Getter and Setter for Active status
    bool getActive() const
    {
        return active;
    }

    void setActive(bool ac)
    {
        active = ac;
    }

    // Getter and Setter for next
    Manager *getNext() const
    {
        return next;
    }

    void setNext(Manager *nxt)
    {
        next = nxt;
    }

    // Getter and Setter for prev
    Manager *getPrev() const
    {
        return prev;
    }

    void setPrev(Manager *prv)
    {
        prev = prv;
    }

    // Other member functions...
    void addManager(string username, string password, string fullname, string contact, bool active);
    void getManagerByUsername(string username);
    void viewManager();
    void modifyManagerStatus(string username, bool newStatus);
    bool usernameValidation(string username);
    void deleteInactiveTenants(int daysOfInactivity);
    int managerLoginV(string inputUsername, string inputPassword);
};

struct Manager *managerhead = NULL;
struct Manager *managertail = NULL;
struct Manager *managertemp;

void Manager::addManager(string username, string password, string fullname, string contact, bool active)
{
    Manager *newNode = new Manager;
    newNode->username = username;
    newNode->password = password;
    newNode->fullname = fullname;
    newNode->contact = contact;
    newNode->active = true;
    newNode->next = NULL;
    newNode->prev = managertail;
    managertail = newNode;
    if (managerhead == NULL)
    {
        managerhead = newNode;
    }
    else
    {
        newNode->prev->next = newNode;
    }
}

void Manager::viewManager()
{
    managertemp = managerhead;
    cout << endl
         << left << setw(20) << "Username" << left << setw(20)
         << "|Password" << left << setw(20)
         << "|Full Name" << left << setw(20)
         << "|Contact" << left << setw(20)
         << "|Status" << endl;
    cout << string(95, '-') << endl;

    if ((managerhead == NULL) && (managertemp == NULL))
    {
        cout << string(10, ' ') << "     User List is Empty   " << endl;
        return;
    }
    while (managertemp != NULL)
    {
        cout << left << setw(20) << managertemp->username << setw(1) << left
             << setw(20) << managertemp->password
             << setw(20) << managertemp->fullname
             << setw(20) << managertemp->contact
             << setw(20) << (managertemp->active ? "Active" : "Inactive") << endl;
        managertemp = managertemp->next;
    }
}

void Manager::modifyManagerStatus(string username, bool newStatus)
{
    managertemp = managerhead;
    while (managertemp != nullptr)
    {
        if (managertemp->username == username)
        {
            managertemp->active = newStatus;
            return;
        }
        managertemp = managertemp->next;
    }
    cout << "Manager not found." << endl;
}

int Manager::managerLoginV(string inputUsername, string inputPassword)
{
    // Iterate through your doubly linked list to find the manager with the provided username
   managertemp = managerhead;// Assuming "head" is the pointer to the first manager in the list

    while (managertemp != nullptr)
    {
        if (managertemp->username == inputUsername)
        {
            if (managertemp->password == inputPassword)
            {
                // Login successful, update active status and return appropriate code
                
                if (managertemp->active == true)
                    return 2; // Active account
                else
                    return 1; // Inactive account
            }
            else
            {
                // Incorrect password
                return 0;
            }
        }
        managertemp = managertemp->next;
    }

    // Manager with the given username not found
    return 0;
}


bool Manager::usernameValidation(string username)
{
    managertemp = managertail;
    while (managertemp != nullptr)
    {
        if (managertemp->username == username)
        {
            return true;
        }
        managertemp = managertemp->prev;
    }
    return false;
}

void Manager::deleteInactiveTenants(int daysOfInactivity)
{
    time_t now = time(0);
    Tenant *prevTenant = nullptr;
    Tenant *temp = head;

    while (temp != nullptr)
    {
        double secondsSinceLastLogin = difftime(now, temp->lastLoginDate);
        double daysSinceLastLogin = secondsSinceLastLogin / (60 * 60 * 24);

        if (daysSinceLastLogin > daysOfInactivity)
        {
            if (prevTenant != nullptr)
            {
                prevTenant->next = temp->next;
            }
            else
            {
                head = temp->next;
            }
            Tenant *tenantToDelete = temp;
            temp = temp->next;
            delete tenantToDelete;
        }
        else
        {
            prevTenant = temp;
            temp = temp->next;
        }
    }
}
