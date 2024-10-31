#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include "property.h"
#include "doublyLinkedList.h"
#include <chrono> // Include the header for std::chrono

using namespace std;

void viewTenant(int filterChoice, const string &filterValue);

class Tenant
{
private:
    DoublyLinkedList<Tenant> tenantlist;

public:
    string username;
    string password;
    string fullname;
    string contact;
    string city;
    Tenant *next;
    Tenant *prev;
    time_t lastLoginDate;

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

    string getFullname() const
    {
        return fullname;
    }

    void setFullname(string fullname)
    {
        this->fullname = fullname;
    }

    string getContact() const
    {
        return contact;
    }

    void setContact(string contact)
    {
        this->contact = contact;
    }

    string getCity() const
    {
        return city;
    }

    void setCity(string city)
    {
        this->city = city;
    }

    Tenant *getNext() const
    {
        return next;
    }

    void setNext(Tenant *next)
    {
        this->next = next;
    }

    Tenant *getPrev() const
    {
        return prev;
    }

    void setPrev(Tenant *prev)
    {
        this->prev = prev;
    }

    void updateLastLogin(Tenant *tenant)
    {
        auto currentTime = std::chrono::system_clock::now();
        tenant->lastLoginDate = std::chrono::system_clock::to_time_t(currentTime);
    }

    void addTenant(string username, string password, string fullname, string contact, string city);
    void viewTenant(int filterChoice, const string &filterValue = ""); // test tenant is in the linked list.
    bool tenantLogin(string username, string password);
    bool usernameValidation(string username);
    void searchTenant(const string &searchCriteria, const string &searchValue);
    void getTenantByUsername(string username);
};

struct Tenant *head = NULL;
struct Tenant *tail = NULL;
struct Tenant *temp;

void Tenant::getTenantByUsername(string username)
{

    Tenant *currentTenant = head; // Assuming "head" is the pointer to the first tenant in the list
    bool usernameFound = false;   // Flag to track if the username is found

    while (currentTenant != nullptr)
    {
        if (currentTenant->getUsername() == username)
        {
            // Update last login date for the found tenant
            updateLastLogin(currentTenant);
            usernameFound = true; // Set the flag to true
            break;                // Exit the loop after updating last login
        }
        currentTenant = currentTenant->next;
    }

    if (!usernameFound)
    {
        cout << "Username not found." << endl;
    }
}

void Tenant::addTenant(string username, string password, string fullname, string contact, string city)
{
    Tenant *newNode = new Tenant;
    newNode->username = username;
    newNode->password = password;
    newNode->fullname = fullname;
    newNode->contact = contact;
    newNode->city = city;
    newNode->next = NULL;
    newNode->prev = tail;
    tail = newNode;
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        newNode->prev->next = newNode;
    }
}

// view selection
void Tenant::viewTenant(int filterChoice, const string &filterValue)
{
    temp = head;
    cout << endl
         << left << setw(20) << "Username" << left << setw(20)
         << "|Password" << left << setw(20)
         << "|Full Name" << left << setw(20)
         << "|Contact" << left << setw(20)
         << "|City";

    if (filterChoice == 3) // Only display "|Last Login Date" for filterChoice 3
    {
        cout << left << setw(20) << "|Last Login Date";
    }

    cout << endl
         << string(130, '-') << endl;

    if ((head == NULL) && (temp == NULL))
    {
        cout << string(10, ' ') << "     User List is Empty    " << endl;
        return;
    }
    while (temp != NULL)
    {
        switch (filterChoice)
        {
        case 1:
            if (filterChoice == 1 && temp->fullname[0] == filterValue[0])
            {
                cout << left << setw(20) << temp->username << setw(1) << left
                     << setw(20) << temp->password
                     << setw(20) << temp->fullname
                     << setw(20) << temp->contact
                     << setw(20) << temp->city
                     << endl;
            }
            break;

        case 2:
            if (filterChoice == 2 && temp->city[0] == filterValue[0])
            {
                cout << left << setw(20) << temp->username << setw(1) << left
                     << setw(20) << temp->password
                     << setw(20) << temp->fullname
                     << setw(20) << temp->contact
                     << setw(20) << temp->city
                     << endl;
            }
            break;

        case 3:
            if (filterChoice == 3)
            {
                cout << left << setw(20) << temp->username << setw(1) << left
                     << setw(20) << temp->password
                     << setw(20) << temp->fullname
                     << setw(20) << temp->contact
                     << setw(20) << temp->city;
                // Convert lastLoginDate to string format for display
                struct tm *timeinfo;
                timeinfo = localtime(&(temp->lastLoginDate));
                char buffer[80];
                strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
                cout << buffer << endl;
            }
            break;

        default:
            // Handle the default case here, if necessary.
            cout << "Invalid input. Please try again.\n"
                 << endl;
            break;
        }
        temp = temp->next;
    }
}

bool Tenant::tenantLogin(string username, string pass)
{
    temp = tail;
    while (temp != nullptr)
    {
        if (temp->username == username && temp->password == pass)
        {
            temp = temp->prev;
            return true;
        }
        temp = temp->prev;
    }
    return false;
}

bool Tenant::usernameValidation(string username)
{
    temp = tail;
    while (temp != nullptr)
    {
        if (temp->username == username)
        {
            return true;
        }
        temp = temp->prev;
    }
    return false;
}

// search by City
void Tenant::searchTenant(const string &searchCriteria, const string &searchValue)
{
    if (searchCriteria == "city")

    {
        temp = head;
        bool found = false;

        cout << endl
             << left << setw(20) << "Username" << left << setw(20)
             << "|Password" << left << setw(20)
             << "|Full Name" << left << setw(20)
             << "|Contact" << left << setw(20)
             << "|City" << endl;
        cout << string(95, '-') << endl;

        while (temp != NULL)
        {
            if (temp->city == searchValue)
            {
                cout << left << setw(20) << temp->username << setw(1) << left
                     << setw(20) << temp->password
                     << setw(20) << temp->fullname
                     << setw(20) << temp->contact
                     << setw(20) << temp->city
                     << endl;
                found = true;
            }
            temp = temp->next;
        }

        if (!found)
        {
            cout << "\nNo tenants found in the city: " << searchValue << endl;
        }
    }
}
