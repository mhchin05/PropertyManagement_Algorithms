#pragma once
#include <iostream>
#include <functional>
#include "property.h"
#include "manager.h"

using namespace std;


void newManager(); // add new manager


void adminPage(string username, function<void()> mainPageFunc, DoublyLinkedList<Property>& myList)
{
    Property property;
    Tenant tenant;
    Manager manager; 

    while (true)
    {
        int choice;
        string filterValue;
        int filterChoice;
        int filterProp;
        string managerUsername;
        bool newStatus;

        cout << "\n ====== Welcome Admin ======" << endl;
        cout << "1.Add New Manager" << endl;
        cout << "2.Modify Manager Status (active/inactive)" << endl;
        cout << "3.Display All Tenant (with filtering)" << endl;
        cout << "4.Display Property Information (with filtering)" << endl;
        cout << "0.Logout " << endl;
        cout << "Enter your option: ";
        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the error state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining characters in the input buffer
            continue; // Restart the loop
        }

        switch (choice)
        {
            case 0:
                mainPageFunc();
                break;

            case 1:
                cout << "\n=== Add New Manager ===" << endl;
                newManager();

                break;

            case 2:
                cout << "\n=== Modify Manager Status ===" << endl;
                cout << "Enter the username of the manager: ";
                cin >> managerUsername;
                cout << "Enter new status (1 for active, 0 for inactive): ";
                cin >> newStatus;
                manager.modifyManagerStatus(managerUsername, newStatus);
                manager.viewManager();
                break;

            case 3:
                //filter name and city
                cout << "\n=== Display All Tenant (with filtering) ===" << endl;
                cout << "1. Filter by Name" << endl;
                cout << "2. Filter by City" << endl;
                cout << "Enter your choice: ";
                cin >> filterChoice;

                if (filterChoice == 1)
                {
                    cout << "Enter letter to filter name: ";
                    cin >> filterValue;

                    for (char& c : filterValue) {
                        c = tolower(c);
                    }
                }
                else if (filterChoice == 2)
                {
                    cout << "Enter letter to filter city: ";
                    cin >> filterValue;

                    for (char& c : filterValue) {
                        c = toupper(c);
                    }
                }
                else
                {
                    cout << "Invalid option. Please try again.\n" << endl;
                    break; 
                }

                tenant.viewTenant(filterChoice, filterValue); // Filter with username or city
                break; 

            case 4:
                //filter furnished and property type 
                cout << "\n=== Display Property Information (with filtering) ===" << endl;
                cout << "1.By Property Type - Condominium(C)/Apartment(A)/Service Residence(S)/Flat(F)" << endl;
                cout << "2.By Furnished - Fully(F)/Partially(P)/Not(N)" << endl;
                cout << "Enter your choice: ";
                cin >> filterProp;

                if (filterProp == 1)
                {
                    cout << "Enter letter of Property Type: ";
                    cin >> filterValue;

                    // Convert filterValue to uppercase
                    for (char& c : filterValue) {
                        c = toupper(c);
                    }
                }
                else if (filterProp == 2)
                {
                    cout << "Enter letter of Furnished Status: ";
                    cin >> filterValue;

                    for (char& c : filterValue) {
                        c = toupper(c);
                    }
                }
                else
                {
                    cout << "Invalid option. Please try again.\n" << endl;
                    break; 
                }

                property.filterProperties(filterProp, filterValue, myList);
                break; 
                
            default:
                cout << "Invalid input. Please try again.\n" << endl;
                break;
        }
    }
}