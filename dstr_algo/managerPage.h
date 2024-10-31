#pragma once
#include <iostream>
#include <functional>

using namespace std;

void managerPage(string username, function<void()> mainPageFunc)
{
    Tenant tenant;
    Property property;
    Manager manager;
    Favorite fav;
    Rent rent;
    string searchValue;

    while (true)
    {
        int choice;
        
        cout << "\n ====== Welcome Manager : " << username << " ======" << endl;
        cout << "1.Display Registered Tenant Details" << endl;
        cout << "2.Search Tenant Details" << endl;
        cout << "3.Delete Inactive Tenant Account" << endl;
        cout << "4.Top 10 Property Favorite List" << endl;
        cout << "5.Manage Tenancy Process (renting req)" << endl;
        cout << "6.Manage Payment Of Confirmed Tenancy" << endl;
        cout << "0.Logout " << endl;
        cout << "Enter your option: ";
        cin >> choice;

        if (cin.fail())
        {
            // Clear the error state of cin and ignore invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.\n"
                 << endl;
            continue;
        }

        switch (choice)
        {
        case 0:
            mainPageFunc();
            break;

        case 1:
            cout << "=== Display Registered Tenant Details ===" << endl;
            tenant.viewTenant(3);
            break;

        case 2:
            cout << "=== Search Tenant Details ===" << endl;
            cout << "Enter the city you want to search for: ";
            cin >> searchValue;
            for (char& s : searchValue) {
                s = toupper(s);
            }

            tenant.searchTenant("city", searchValue);
            break;

        case 3:
            cout << "=== Delete Inactive Tenant Account ===" << endl;
            int daysOfInactivity;
            cout << "Enter the number of days of inactivity to use as a threshold for deletion: ";
            cin >> daysOfInactivity;
            manager.deleteInactiveTenants(daysOfInactivity);
            cout << "Inactive tenants have been deleted." << endl;
            break;

        case 4:
            cout << "=== Top 10 Property Favorite List ===" << endl;
            fav.top10Report();
            break;

        case 5:
            cout << "=== Manage Tenancy Process Upon Renting Request ===" << endl;
            char choice;
            bool approve;

            do
            {
                // Show the rent request queue to the manager
                cout << "--- Rent Request Queue ---" << endl;
                rent.showRentRequestQueue();


                // Ask for manager's decision
                cout << "\nDo you want to (A)pprove or (R)eject the rent request? (Q)uit: ";
                cin >> choice;

                // Convert choice to uppercase for case-insensitivity
                choice = toupper(choice);

                if (choice == 'A')
                {
                    approve = true;
                }
                else if (choice == 'R')
                {
                    approve = false;
                }
                else if (choice == 'Q')
                {
                    cout << "Returning to main menu." << endl;
                    break;
                }
                else
                {
                    cout << "Invalid choice. Please enter A, R, or Q." << endl;
                    continue;
                }

                // Process the rent request based on manager's decision
                rent.processRentRequests(approve);

            } while (true);
            break;

        case 6:
            cout << "=== Manage Payment Of Confirmed Tenancy ===" << endl;
            rent.paymentStatus();

            break;

        default:
            cout << "Invalid input. Please try again.\n"
                 << endl;
            break;
        }
    }
}