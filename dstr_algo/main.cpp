#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <string>
#include <functional>
#include "tenant.h"
#include "tenantPage.h"
#include "admin.h"
#include "adminPage.h"
#include "manager.h"
#include "managerPage.h"
#include "property.h"

using namespace std;

void newManager();

bool isLoggedIn = false;
string username;


void exitProgram()
{
    cout << "Exiting program...\n"
         << endl;
    exit(0);
}

void adminLogin(function<void()> mainPageFunc, DoublyLinkedList<Property> &myList)
{
    cout << "\n === Admin Login ===";
    Admin admin;
    string username, password;

    cout << "\nEnter Username: ";
    do
    {
        getline(cin, username);

        // Convert the input string to lowercase
        transform(username.begin(), username.end(), username.begin(), ::tolower);

    } while (username == "");

    cout << "Enter Password: ";
    do
    {
        getline(cin, password);
    } while (password == "");

    if (admin.adminLoginV(username, password))
    {
        cout << "Admin Login Success!" << endl
             << endl;

        adminPage(username, mainPageFunc, myList);
    }
    else
    {
        cout << "...Admin Login Fail..." << endl
             << endl;
    }
}
void managerLogin(function<void()> mainPageFunc)
{
    cout << "\n === Manager Login ===";
    Manager manager;
    string username, password;

    cout << "\nEnter Username: ";
    do
    {
        getline(cin, username);

        // Convert the input string to lowercase
        transform(username.begin(), username.end(), username.begin(), ::tolower);

    } while (username == "");

    cout << "Enter Password: ";
    do
    {
        getline(cin, password);
    } while (password == "");

    int loginResult = manager.managerLoginV(username, password);

    switch (loginResult)
    {
    case 0:
        cout << "Incorrect username or password." << endl
             << endl;
        break;
    case 1:
        cout << "Manager account is inactive. Please contact the administrator." << endl
             << endl;
        break;
    case 2:
        cout << "Manager Login Success!" << endl
             << endl;
        managerPage(username, mainPageFunc);
        break;
    }
}

void tenantLogin(function<void()> mainPageFunc, function<void(string)> viewFavProp, function<void(string, string)> addFavProp)
{
    cout << "\n === Tenant Login ===";
    Tenant tenant;
    string username, password;

    cout << "\nEnter Username: ";
    do
    {
        getline(cin, username);

        // Convert the input string to lowercase
        transform(username.begin(), username.end(), username.begin(), ::tolower);

    } while (username == "");

    cout << "Enter Password: ";
    do
    {
        getline(cin, password);
    } while (password == "");

    if (tenant.tenantLogin(username, password))
    {
        // Update last login date for the logged-in tenant
        tenant.getTenantByUsername(username);

        cout << "Tenant Login Success!" << endl
             << endl;
        tenantPage(username, mainPageFunc, viewFavProp, addFavProp);
    }
    else
    {
        cout << "...Tenant Login Fail..." << endl
             << endl;
    }
}

void newTenant()
{
    Tenant tenant;
    string username;
    string password;
    string fullname;
    string contact;
    string city;

    cout << "\nUsername: ";
    do
    {
        getline(cin, username);

        // Convert the input string to lowercase
        transform(username.begin(), username.end(), username.begin(), ::tolower);

    } while (username == "");

    if (tenant.usernameValidation(username))
    {
        cout << "Username already exists. Please choose a different username.\n";
        newTenant(); // re-enter username
        return;      // Return to avoid executing the rest of the function after recursive call
    }
    cout << "Password: ";
    do
    {
        getline(cin, password);
    } while (password == "");

    cout << "Full Name: ";
    do
    {
        getline(cin, fullname);
    } while (fullname == "");

    cout << "Contact: ";
    do
    {
        getline(cin, contact);
    } while (contact == "");

    cout << "City: ";
    do
    {
        getline(cin, city);

        // Convert the input string to uppercase
        transform(city.begin(), city.end(), city.begin(), ::toupper);

    } while (city == "");

    tenant.addTenant(username, password, fullname, contact, city);
    cout << endl
         << "...Tenant added. Please try to login..." << endl
         << endl;

    // tenant.viewTenant();
}

void newManager()
{
    Manager manager;
    string username;
    string password;
    string fullname;
    string contact;

    cout << "\nUsername: ";
    do
    {
        getline(cin, username);

        // Convert the input string to lowercase
        transform(username.begin(), username.end(), username.begin(), ::tolower);

    } while (username == "");

    if (manager.usernameValidation(username))
    {
        cout << "Username already exists. Please choose a different username.\n";
        newManager(); // re-enter username
        return;       // Return to avoid executing the rest of the function after recursive call
    }

    cout << "Password: ";
    do
    {
        getline(cin, password);
    } while (password == "");

    cout << "Full Name: ";
    do
    {
        getline(cin, fullname);
    } while (fullname == "");

    cout << "Contact: ";
    do
    {
        getline(cin, contact);
    } while (contact == "");

    manager.addManager(username, password, fullname, contact, true);
    cout << endl
         << "...Manager added!..." << endl
         << endl;

    // test add function
    manager.viewManager();
}

void newAdmin()
{
    Admin admin;
    string username = "admin";
    string password = "admin123";

    admin.addAdmin(username, password);

    // admin.viewAdmin();
}

void mainPage()
{
    Favorite favorite;
    Property property;
    DoublyLinkedList<Property> myList = property.readCSV();

    while (true)
    {
        int choice;
        cout << "\n====== Asia Pacific Home (APH) ======" << endl;
        cout << "1.Sign Up - Register New Tenant" << endl;
        cout << "2.Login - Tenant" << endl;
        cout << "3.Login - Admin" << endl;
        cout << "4.Login - Manager" << endl;
        cout << "5.View Property Details - Guest" << endl;
        cout << "Insert '0' to exit!" << endl;
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
            exitProgram();
            break;

        case 1:
            newTenant();
            break;

        case 2:
            // functions start to be passed from here
            tenantLogin(mainPage, bind(&Favorite::viewFavoriteProperties, &favorite, placeholders::_1), bind(&Favorite::addFavoriteProperty, &favorite, placeholders::_1, placeholders::_2));
            break;

        case 3:

            adminLogin(mainPage, myList);
            break;

        case 4:
            managerLogin(mainPage);
            break;

        case 5:
            property.guestViewAllProp();
            break;

        default:
            cout << "Invalid input. Please try again.\n"
                 << endl;
            break;
        }
    }
}

int main()
{
    // dummy data: test run purpose
    Property property;
    Tenant tenant;
    Favorite fav;
    Rent rent;
    Manager manager;

    tenant.addTenant("john", "john123", "John Doe", "014666111", "CHERAS");
    tenant.addTenant("lim", "lim123", "Lim Dao-e", "011000555", "CHERAS");
    tenant.addTenant("park", "park123", "John Doe", "011777909", "CHERAS");
    tenant.addTenant("lai", "lai123", "Lai LI", "0148937546", "KL");
    manager.addManager("pop", "pop123", "Pop Lok", "01134745428", true);


    fav.addFavoriteProperty("lim", "100235642");
    fav.addFavoriteProperty("lim", "100732327");
    fav.addFavoriteProperty("lim", "100649739");
    fav.addFavoriteProperty("park", "100649739");

    property.readCSV();
    newAdmin();
    mainPage();
    return 0;
}