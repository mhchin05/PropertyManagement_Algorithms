#include <iostream>
#include "property.h"

using namespace std;

void tenantPage(string username, function<void()> mainPageFunc, function<void(string)> viewFavProp, function<void(string, string)> addFavProp)
{
    Property property;
    Rent rq;
    bool hasApprovedRentingHistory = false; // Declare the variable here
    while (true)
    {
        int choice;
        int sort;
        string propid;

        cout << "\n ====== Welcome Tenant : " << username << " ======" << endl;
        cout << "1.Quick Sort - Monthly Rent" << endl;
        cout << "2.Quick Sort - Location" << endl;
        cout << "3.Quick Sort - Size (per sq.ft.)" << endl;
        cout << "4.Insertion Sort - Monthly Rent" << endl;
        cout << "5.Insertion Sort - Location" << endl;
        cout << "6.Insertion Sort - Size (per sq.ft.)" << endl;
        cout << "7.Linear Search - Property ID" << endl;
        cout << "8.Binary Search - Property ID" << endl;
        cout << "9.Save Favorite Property" << endl;
        cout << "10.Place rent request from favorite list" << endl;
        cout << "11.View pending rent request" << endl;
        cout << "12.Payment & Display property renting history" << endl;
        cout << "0. Logout " << endl;
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
            cout << "=== Quick Sort ===" << endl;
            cout << "Sort by: " << endl
                 << "1. Ascending" << endl
                 << "2. Descending" << endl
                 << "0. Back" << endl;
            cout << "Enter your option: ";
            cin >> sort;
            if (sort == 1 || sort == 2)
            {
                property.sortPropertiesByRent(sort);
            }
            else
            {
                cout << endl
                     << "Back" << endl;
            }
            break;

        case 2:
            cout << "=== Quick Sort ===" << endl;
            cout << "Sort by: " << endl
                 << "1. Ascending" << endl
                 << "2. Descending" << endl
                 << "0. Back" << endl;
            cout << "Enter your option: " << endl;
            cin >> sort;
            if (sort == 1 || sort == 2)
            {
                property.sortPropertiesByLocation(sort);
            }
            else
            {
                cout << endl
                     << "Back" << endl;
            }
            break;

        case 3:
            cout << "=== Quick Sort ===" << endl;
            cout << "Sort by: " << endl
                 << "1. Ascending" << endl
                 << "2. Descending" << endl
                 << "0. Back" << endl;
            cout << "Enter your option: " << endl;
            cin >> sort;
            if (sort == 1 || sort == 2)
            {
                property.sortPropertiesBySize(sort);
            }
            else
            {
                cout << endl
                     << "Back" << endl;
            }
            break;

        case 4:
            // insertion - monthly rent
            cout << "=== Insertion Sort ===" << endl;
            property.insertionSortPropertiesByRent();
            break;

        case 5:
            // insertion - location
            cout << "=== Insertion Sort ===" << endl;
            property.insertionSortPropertiesByLocation();
            break;

        case 6:
            // insertion - size
            cout << "=== Insertion Sort ===" << endl;
            property.insertionSortPropertiesBySize();
            break;

        case 7:
            // linear search
            cout << "=== Linear Search Property ID ===" << endl;
            cout << "Enter property ID: " << endl;
            cin >> propid;
            property.searchPropIDLinear(propid);
            break;

        case 8:
            // binary search
            cout << "=== Binary Search Property ID ===" << endl;
            cout << "Enter property ID: " << endl;
            cin >> propid;
            property.searchPropertyByID(propid);
            break;

        case 9:
        {
            cout << "=== Add Favorite Property ===" << endl;
            cout << "Enter property ID to add to favorites: ";
            cin.ignore(); // Ignore any newline character in the buffer
            getline(cin, propid);
            addFavProp(username, propid); // Call the provided function to add the property to favorites
            break;
        }
        case 10:
            cout << "=== Your Favorite Property ===" << endl;
            viewFavProp(username);
            break;

        case 11:
            cout << "=== Your Pending Rent Request ===" << endl;
            rq.viewPendingRequest(username);
            break;

        case 12:
            char opt;
            do
            {
                cout << "=== Your Renting History ===" << endl;
                rq.viewRentingHistory(username);
                cout << "P - Payment" << endl;
                cout << "Q - Back to Main Menu" << endl;
                cout << "\nEnter your choice : ";
                cin >> opt;

                if (toupper(opt) == 'P')
                {
                    cout << "Enter property ID: ";
                    cin >> propid;

                    bool checkRentRequestExist = rq.hasApprovedRentingHistory(username, propid);
                    if (checkRentRequestExist)
                    {
                        cout << "Enter Payment Amount (RM): ";
                        double money;
                        cin >> money;

                        // Validate if the input is a valid double
                        if (cin.fail())
                        {
                            cout << "Invalid input. Please enter a valid number." << endl;
                            cin.clear();                                         // Clear the error flags
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any remaining characters in the input buffer
                            continue;
                        }

                        rq.insertPayment(username, propid, money);
                    }
                    else
                    {
                        cout << "\nNo payment needed for the given property ID." << endl;
                        break;
                    }
                }
                else if (toupper(opt) == 'Q')
                {
                    cout << endl
                         << "Returning to the Main Menu." << endl;
                    break;
                }
                else
                {
                    cout << "Invalid input. Please enter 'P' or 'Q' only." << endl;
                    cin.clear();                                         // Clear the error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any remaining characters in the input buffer
                }
            } while (toupper(opt) != 'Q');
            break;

        default:
            cout << "Invalid input. Please try again.\n"
                 << endl;
            break;
        }
    }
}
