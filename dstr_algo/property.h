#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <string>
#include "doublyLinkedList.h"
#include "doublyLinkedListQueue.h"
#include <chrono> //execution time
#include <map>

using namespace std;

class Property
{
private:
    string adsId;
    string propName;
    int completionYear;
    int monthlyRent;
    string propLocation;
    string propType;
    string rooms;
    int parking;
    int bathroom;
    int propSize;
    string propFurnished;
    string propFacilities;
    string additionalFacilities;
    string propRegion;

    Property *next;
    Property *prev;

public:
    Property(string id, string name, int year, int rent, string location, string type,
             string numRoom, int numParking, int numBathroom, int size,
             string furnished, string facilities, string addFacilities, string region)
        : adsId(id), propName(name), completionYear(year), monthlyRent(rent),
          propLocation(location), propType(type), rooms(numRoom), parking(numParking), bathroom(numBathroom),
          propSize(size), propFurnished(furnished), propFacilities(facilities), additionalFacilities(addFacilities),
          propRegion(region)
    {
    }

    Property()
        : adsId(""), propName(""), completionYear(0), monthlyRent(0), propLocation(""), propType(""),
          rooms(""), parking(0), bathroom(0), propSize(0), propFurnished(""), propFacilities(""),
          additionalFacilities(""), propRegion("")
    {
    }

    // Getters and Setters for each variable
    string getAdsId() const
    {
        return adsId;
    }

    void setAdsId(string id)
    {
        adsId = id;
    }

    string getPropName()
    {
        return propName;
    }

    void setPropName(string name)
    {
        propName = name;
    }

    int getCompletionYear()
    {
        return completionYear;
    }

    void setCompletionYear(int year)
    {
        completionYear = year;
    }

    int getMonthlyRent() const
    { // Add 'const' here
        return monthlyRent;
    }

    void setMonthlyRent(int rent)
    {
        monthlyRent = rent;
    }

    string getPropLocation() const
    {
        return propLocation;
    }

    void setLocation(string location)
    {
        propLocation = location;
    }

    string getPropType()
    {
        return propType;
    }

    void setPropertyType(string type)
    {
        propType = type;
    }

    string getRooms()
    {
        return rooms;
    }

    void setRooms(string numRoom)
    {
        rooms = numRoom;
    }

    int getParking()
    {
        return parking;
    }

    void setParking(int numParking)
    {
        parking = numParking;
    }

    int getBathroom()
    {
        return bathroom;
    }

    void setBathroom(int numBathroom)
    {
        bathroom = numBathroom;
    }

    int getPropSize() const
    {
        return propSize;
    }

    void setSize(int size)
    {
        propSize = size;
    }

    string getPropFurnished()
    {
        return propFurnished;
    }

    void setFurnished(string furnished)
    {
        propFurnished = furnished;
    }

    string getPropFacilities()
    {
        return propFacilities;
    }

    void setFacilities(string facilities)
    {
        propFacilities = facilities;
    }

    string getAdditionalFacilities() const
    {
        return additionalFacilities;
    }

    void setAdditionalFacilities(string addFacilities)
    {
        additionalFacilities = addFacilities;
    }

    string getPropRegion() const
    {
        return propRegion;
    }

    void setRegion(string region)
    {
        propRegion = region;
    }

    DoublyLinkedList<Property> readCSV();

    void filterProperties(int filterProp, const string &filterValue, const DoublyLinkedList<Property> &myList);

    static void viewProperties(string tenant, int method, const DoublyLinkedList<Property> &sortedList);

    static bool compareByMonthlyRent(const Property &prop1, const Property &prop2)
    {
        return prop1.monthlyRent < prop2.monthlyRent;
    }

    static bool compareByLocation(const Property &prop1, const Property &prop2)
    {
        return prop1.propLocation < prop2.propLocation;
    }

    static bool compareBySize(const Property &prop1, const Property &prop2)
    {
        return prop1.propSize < prop2.propSize;
    }

    void sortPropertiesByRent(int sort);
    void sortPropertiesByLocation(int sort);
    void sortPropertiesBySize(int sort);
    void insertionSortPropertiesByRent();
    void insertionSortPropertiesByLocation();
    void insertionSortPropertiesBySize();
    void searchPropertyByID(string id);
    Property searchByID(string id);
    void searchPropIDLinear(string id);
    void guestViewAllProp();

    friend ostream &operator<<(ostream &os, const Property &property)
    {
        os
            << "Property ID          : " << property.adsId << " \n"
            << "Property Name        : " << property.propName << " \n"
            << "Completion Year      : " << property.completionYear << " \n"
            << "Monthly Rent         : RM " << property.monthlyRent << " \n"
            << "Location             : " << property.propLocation << " \n"
            << "Property Type        : " << property.propType << " \n"
            << "Number of Rooms      : " << property.rooms << " \n"
            << "Parking Spaces       : " << property.parking << " \n"
            << "Number of Bathrooms  : " << property.bathroom << " \n"
            << "Size                 : " << property.propSize << " sq.ft. \n"
            << "Furnished            : " << property.propFurnished << " \n"
            << "Facilities           : " << property.propFacilities << " \n"
            << "Additional Facilities: " << property.additionalFacilities << " \n"
            << "Region               : " << property.propRegion << " \n"
            << endl;

        return os;
    }
};

// struct Property *prophead = NULL;
// struct Property *proptail = NULL;
// struct Property *proptemp;

class Rent
{
public:
    string prop;
    string tenant;
    string startdate;
    string enddate;
    double monthlyRent;
    double deposit;
    double totalPaid;
    string status;
    time_t requestedDate;
    static DoublyLinkedListQueue<Rent> rentRequestQueue;       // Static member for rent requests queue
    static DoublyLinkedList<Rent> rentHistoryDoublyLinkedList; // Static member for storing approved/rejected rent history

    Rent(string prop, string tenant, string startdate, string enddate,
         double monthlyRent, double deposit, double totalPaid, string status, time_t requestedDate)
        : prop(prop), tenant(tenant), startdate(startdate), enddate(enddate),
          monthlyRent(monthlyRent), deposit(deposit), totalPaid(totalPaid), status(status),
          requestedDate(requestedDate)
    {
    }

    Rent()
        : prop(""), tenant(""), startdate(""), enddate(""),
          monthlyRent(0), deposit(0), totalPaid(0), status(""), requestedDate(0)
    {
    }

    string getEnddate() const
    {
        return enddate;
    }

    void setEnddate(string enddate)
    {
        this->enddate = enddate;
    }

    string getProp() const
    {
        return prop;
    }

    void setProp(string prop)
    {
        this->prop = prop;
    }

    string getStartdate() const
    {
        return startdate;
    }

    void setStartdate(string startdate)
    {
        this->startdate = startdate;
    }

    double getMonthlyRent() const
    {
        return monthlyRent;
    }

    void setMonthlyRent(double monthlyRent)
    {
        this->monthlyRent = monthlyRent;
    }

    double getDeposit() const
    {
        return deposit;
    }

    void setDeposit(double deposit)
    {
        this->deposit = deposit;
    }

    double getTotalPaid() const
    {
        return totalPaid;
    }

    void setTotalPaid(double totalPaid)
    {
        this->totalPaid = totalPaid;
    }

    string getStatus() const
    {
        return status;
    }

    void setStatus(string status)
    {
        this->status = status;
    }

    string getTenant() const
    {
        return tenant;
    }

    void setTenant(string newTenant)
    {
        tenant = newTenant;
    }

    // Getter method for requestedDate
    time_t getRequestedDate() const
    {
        return requestedDate;
    }

    // Setter method for requestedDate
    void setRequestedDate(time_t newRequestedDate)
    {
        requestedDate = newRequestedDate;
    }

    void requestedTime()
    {
        auto currentTime = std::chrono::system_clock::now();
        requestedDate = std::chrono::system_clock::to_time_t(currentTime);
    }

    // Function to add rent request to the queue
    void addRentRequest(string prop, string tenant, string startdate, string enddate, string status);

    // Function to process (approve / reject) rent requests in FCFS order
    void processRentRequests(bool approve);

    void showRentRequestQueue();

    void viewRentingHistory(string tenant);
    bool checkIfInFavorites(string prop, string tenant);
    void viewPendingRequest(string tenant);

    bool isPropertyInPendingQueue(string propID);
    bool isPropertyInRentHistory(string propID);

    bool insertPayment(string tenant, string propID, double money);
    bool hasApprovedRentingHistory(string tenant, string propID);
    void paymentStatus();
};

class Favorite
{
public:
    string prop;
    string tenant;
    static DoublyLinkedList<Favorite> favDoublyLinkedList; // Static member for rent requests

    Favorite(string prop, string tenant)
        : prop(prop), tenant(tenant)
    {
    }

    Favorite()
        : prop(""), tenant("")
    {
    }

    string getProp() const{
        return prop;
    }

    void setProp(string prop){
        this->prop = prop;
    }

    string getTenant() const{
        return tenant;
    }

    void setTenant(string tenant){
        this->tenant = tenant;
    }

    void addFavoriteProperty(string tenant, string prop);
    void viewFavoriteProperties(string tenant);
    bool checkIfExist(string tenant, string prop);
    void top10Report();
};

DoublyLinkedListQueue<Rent> Rent::rentRequestQueue;

DoublyLinkedList<Rent> Rent::rentHistoryDoublyLinkedList;

DoublyLinkedList<Favorite> Favorite::favDoublyLinkedList;

bool Favorite::checkIfExist(string tenant, string prop)
{
    DoublyNode<Favorite> *current = favDoublyLinkedList.head;
    while (current != nullptr)
    {
        if (current->data.tenant == tenant && current->data.prop == prop)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

void Favorite::addFavoriteProperty(string username, string propertyID)
{
    Property property;
    DoublyLinkedList<Property> myList = property.readCSV();
    myList.quickSort([](const Property &prop1, const Property &prop2)
                     { return prop1.getAdsId() < prop2.getAdsId(); });

    favDoublyLinkedList.quickSort([](const Favorite &prop1, const Favorite &prop2)
                                  { return prop1.getProp() < prop2.getProp(); });

    DoublyNode<Property> *result = myList.binarySearch(propertyID);

    if (result)
    {
        if (checkIfExist(username, propertyID))
        {
            cout << "This property is in your favorite list." << endl;
        }
        else
        {
            Favorite favo(result->data.getAdsId(), username);
            favDoublyLinkedList.insertAtEnd(favo);
            cout << "Property with ID " << propertyID << " added to favorites." << endl;
        }
    }
    else
    {
        cout << "Property " << propertyID << " Not Found." << endl;
    }

    cout << endl;
}

void Favorite::viewFavoriteProperties(string tenant)
{
    Rent rq;
    Property pp;
    int count = 0;
    DoublyNode<Favorite> *current = favDoublyLinkedList.head;
    cout << "==== Favorite Properties ====" << endl
         << endl;
    if (current == NULL)
    {
        cout << "The list is empty." << endl;
    }
    while (current != NULL)
    {
        if (current->data.tenant == tenant)
        {
            // Display the rent request details for the specific tenant
            cout << "Property ID: " << current->data.prop << endl;
            cout << "Tenant ID: " << current->data.tenant << endl;
            cout << "Property Details: " << endl;
            cout << pp.searchByID(current->data.prop) << endl;
            cout << "-----------------------" << endl;
            count++;
        }
        current = current->next;
    }
    if (count == 0)
    {
        cout << "The list is empty." << endl;
    }
    else
    {
        char opt;
        do
        {
            cout << "N - New Rent Request\n";
            cout << "P - View Pending Request\n";
            cout << "V - View Rent Request\n";
            cout << "Q - Quit\n";
            cout << "Enter your option: ";
            cin >> opt;
            switch (toupper(opt))
            {
            case 'N':
            {
                string propID, startdate, enddate;
                cout << "=== Rent Request ===" << endl;
                cout << "\nEnter Property ID : ";
                do
                {
                    getline(cin, propID);
                } while (propID == "");

                // Check if the property ID is in the pending rent history queue
                bool existsInPendingQueue = rq.isPropertyInPendingQueue(propID);

                // Check if the property ID is in the renting history doubly linked list
                bool existsInRentHistory = rq.isPropertyInRentHistory(propID);

                if (existsInPendingQueue || existsInRentHistory)
                {
                    cout << "This property has already been rented. Please choose another property." << endl;
                }
                else
                {
                    cout << "Enter Start Date : ";
                    do
                    {
                        getline(cin, startdate);
                    } while (startdate == "");
                    cout << "Enter End Date : ";
                    do
                    {
                        getline(cin, enddate);
                    } while (enddate == "");

                    rq.addRentRequest(propID, tenant, startdate, enddate, "pending");
                    cout << "Rent request submitted." << endl
                         << endl;
                }
                break;
            }
            case 'P':
                rq.viewPendingRequest(tenant);
                break;
            case 'V':
                rq.viewRentingHistory(tenant);
                break;
            case 'Q':
                break;
            default:
                cout << "Invalid option. Please try again.\n";
            }
        } while (toupper(opt) != 'Q');
    }
}

void Favorite::top10Report()
{
    if (favDoublyLinkedList.isEmpty())
    {
        cout << "No favorite properties to generate the report." << endl;
        return;
    }

    // Map to store the occurrences of each property
    map<string, int> propertyOccurrences;

    // Count the occurrences of each property in the favorite list
    DoublyNode<Favorite> *current = favDoublyLinkedList.head;
    while (current != nullptr)
    {
        string propertyID = current->data.prop;
        propertyOccurrences[propertyID]++;
        current = current->next;
    }

    if (propertyOccurrences.empty())
    {
        cout << "No favorite properties to generate the report." << endl;
        return;
    }

    // Print the top 10 properties in table format
    cout << "\n" << endl;
    cout << " Top 10 Favorite Properties Report " << endl;
    cout << string(40, '=') << endl;
    cout << left << setw(15) << "Property ID" << setw(15) << "Frequency" << endl;

    for (int i = 0; i < 10; i++)
    {
        int maxOccurrences = 0;
        string mostPopularProperty;

        // Find the most popular property in the map
        for (const auto &property : propertyOccurrences)
        {
            if (property.second > maxOccurrences)
            {
                maxOccurrences = property.second;
                mostPopularProperty = property.first;
            }
        }

        // Print the property information and remove it from the map
        if (!mostPopularProperty.empty())
        {
            cout << left << setw(15) << mostPopularProperty << setw(15) << maxOccurrences << endl;
            propertyOccurrences.erase(mostPopularProperty);
        }
        else
        {
            break; // No more popular properties to display
        }
    }
}

bool Rent::checkIfInFavorites(string prop, string tenant)
{
    DoublyNode<Favorite> *current = Favorite::favDoublyLinkedList.head;
    while (current != nullptr)
    {
        if (current->data.tenant == tenant && current->data.prop == prop)
        {
            return true; // The property is in the favorites list for the tenant
        }
        current = current->next;
    }
    return false; // The property is not in the favorites list for the tenant
}

void Rent::addRentRequest(string prop, string tenant, string startdate, string enddate, string status)
{
    Property property;
    DoublyLinkedList<Property> myList = property.readCSV();
    myList.quickSort([](const Property &prop1, const Property &prop2)
                     { return prop1.getAdsId() < prop2.getAdsId(); });

    DoublyNode<Property> *result = myList.binarySearch(prop);

    if (result)
    {
        if (!checkIfInFavorites(prop, tenant))
        {
            cout << "This property is in not your favorite list." << endl;
        }
        else
        {
            // Calculate monthly rent and deposit based on the property details
            double monthlyRent = result->data.getMonthlyRent();
            double deposit;

            // Check if monthly rent is -1 (NA)
            if (monthlyRent == -1.0)
            {
                deposit = 1000.0; // Set deposit to RM 1000 for NA monthly rent
            }
            else
            {
                deposit = 2.0 * monthlyRent;
            }

            double paid = 0; // init paid amount to 0

            requestedTime();

            Rent newrent(prop, tenant, startdate, enddate, monthlyRent, deposit, paid, status, requestedDate);

            rentRequestQueue.enqueue(newrent); // Enqueue the new rent request
            cout << "Rent request submitted." << endl
                 << endl;
        }
    }
    else
    {
        cout << "This is not a valid property." << endl;
    }
}

// tenant view own pending request
void Rent::viewPendingRequest(string tenant)
{
    Property pp;
    int count = 0;
    DoublyNode<Rent> *current = rentRequestQueue.getHead();

    if (current == NULL)
    {
        cout << "\nThe list is empty." << endl;
    }
    while (current != NULL)
    {
        // Display the rent request details for the specific tenant
        if (current->data.tenant == tenant)
        {
            // Display the rent request details for the specific tenant
            cout << "\nProperty ID  : " << current->data.prop << endl;
            cout << "Tenant ID    : " << current->data.tenant << endl;
            cout << "Start Date   : " << current->data.startdate << endl;
            cout << "End Date     : " << current->data.enddate << endl;

            // Format monthly rent and deposit to two decimal places
            cout << fixed << setprecision(2);
            cout << "\nMonthly Rent   : RM " << current->data.monthlyRent << endl;
            cout << "Deposit          : RM " << current->data.deposit << endl;
            cout << "Total Payment    : RM " << (current->data.monthlyRent + current->data.deposit) << endl;
            cout << "Total Paid Amount: RM " << current->data.totalPaid << endl;

            cout << "\nStatus              : " << current->data.status << endl;

            // Convert date to string format for display
            struct tm *timeinfo;
            timeinfo = localtime(&(current->data.requestedDate)); // Convert time_t to tm struct
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // Format as desired
            cout << "Rent Requested Time : " << buffer << endl;

            cout << "\nProperty Details: " << endl;
            cout << pp.searchByID(current->data.prop) << endl;
            cout << "-----------------------" << endl;
            count++;
        }
        current = current->next;
    }

    if (count == 0)
    {
        cout << "No pending rent requests found for the specified tenant.\n\n"
             << endl;
    }
}

// tenant view renting history (status approved / rejected)
void Rent::viewRentingHistory(string tenant)
{
    Property pp;
    int count = 0;
    DoublyNode<Rent> *current = rentHistoryDoublyLinkedList.head;
    cout << "==== Rent Request ====" << endl
         << endl;
    if (current == NULL)
    {
        cout << "The list is empty." << endl;
    }
    while (current != NULL)
    {
        // Display the rent request details for the specific tenant
        if (current->data.tenant == tenant)
        {
            // Display the rent request details for the specific tenant
            cout << "Property ID  : " << current->data.prop << endl;
            cout << "Tenant ID    : " << current->data.tenant << endl;
            cout << "Start Date   : " << current->data.startdate << endl;
            cout << "End Date     : " << current->data.enddate << endl;

            // Format monthly rent and deposit to two decimal places
            cout << fixed << setprecision(2);
            cout << "\nMonthly Rent     : RM " << current->data.monthlyRent << endl;
            cout << "Deposit          : RM " << current->data.deposit << endl;
            cout << "Total Payment    : RM " << (current->data.monthlyRent + current->data.deposit) << endl;
            cout << "Total Paid Amount: RM " << current->data.totalPaid << endl;

            cout << "\nStatus              : " << current->data.status << endl;

            if (current->data.status == "Rejected")
            {
                cout << "Rejection Reason: Date is invalid. Please try to submit new request again. " << endl;
            }

            struct tm *timeinfo;
            timeinfo = localtime(&(current->data.requestedDate)); // Convert time_t to tm struct
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // Format as desired
            cout << "Rent Requested Time : " << buffer << endl;

            cout << "\nProperty Details: " << endl;
            cout << pp.searchByID(current->data.prop) << endl;
            cout << "-----------------------" << endl;
            count++;
        }
        current = current->next;
    }
    if (count == 0)
    {
        cout << "No renting history found for the specified tenant.\n\n"
             << endl;
    }
}

// M - Displaying pending rent request for manager to approve / reject
void Rent::showRentRequestQueue()
{
    if (!Rent::rentRequestQueue.isEmpty())
    {
        // Get the front rent request from the queue
        Rent rent = Rent::rentRequestQueue.front();
        cout << "Property    : " << rent.getProp() << endl;
        cout << "Tenant      : " << rent.getTenant() << endl;
        cout << "Start Date  : " << rent.getStartdate() << endl;
        cout << "End Date    : " << rent.getEnddate() << endl;

        // Display monthly rent, deposit, and total payment with two decimal places
        cout << fixed << setprecision(2);
        cout << "\nMonthly Rent     : RM" << rent.getMonthlyRent() << endl;
        cout << "Deposit          : RM " << rent.getDeposit() << endl;
        double totalPayment = rent.getMonthlyRent() + rent.getDeposit();
        cout << "Total Payment    : RM " << totalPayment << endl;
        cout << "Total Paid Amount: RM " << rent.getTotalPaid() << endl;

        cout << "\nStatus              : " << rent.getStatus() << endl;

        // Convert requestedDate to string format for display
        struct tm *timeinfo;
        time_t requestedDate = rent.getRequestedDate(); // Get requestedDate from Rent instance
        timeinfo = localtime(&requestedDate); // Convert time_t to tm struct
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // Format as desired

        // Display the requestedDate in string format
        cout << "Rent Requested Time : " << buffer << endl
        << endl;
    }
    else
    {
        cout << "Rent Request Queue is Empty!" << endl;
    }
}

// M - Function to approve or reject tenant rent request
void Rent::processRentRequests(bool approve)
{
    if (!rentRequestQueue.isEmpty())
    {
        Rent rent = rentRequestQueue.front(); // Get the front rent request from the queue

        if (approve)
        {
            rent.setStatus("Approved"); // Update the status to "Approved"

            // Move the approved rent request to the history
            rentHistoryDoublyLinkedList.insertAtEnd(rent);

            cout << "Rent request for Property " << rent.getProp() << " approved.\n\n" << endl;
            rentRequestQueue.dequeue();
        }
        else
        {
            rent.setStatus("Rejected"); // Update the status to "Rejected"

            // Move the rejected rent request to the history
            rentHistoryDoublyLinkedList.insertAtEnd(rent);

            cout << "Rent request for Property " << rent.getProp() << " rejected.\n\n" << endl;
            rentRequestQueue.dequeue();
        }

        // Dequeue the rent request after it has been processed
    }
    else
    {
        cout << "No rent request in the queue to process." << endl;
    }
}

// M - manager manage payment
bool Rent::insertPayment(string tenant, string propID, double money)
{
    bool paymentProcessed = false;

    // Find the rent record for the specified tenant and property
    DoublyNode<Rent> *current = rentHistoryDoublyLinkedList.head;

    while (current != NULL)
    {
        if (current->data.tenant == tenant && current->data.prop == propID && current->data.status == "Approved")
        {
            // Check if the amount received is equal to the remaining amount
            double remainingAmount = current->data.monthlyRent + current->data.deposit - current->data.totalPaid;
            if (money == remainingAmount)
            {
                current->data.totalPaid += money;
                current->data.status = "Confirmed";
                cout << "Payment successful. Rent request is now fully paid." << endl;
            }
            else
            {
                cout << "Payment unsuccessful. Please pay the exact amount." << endl;
            }

            paymentProcessed = true;
            break;
        }
        current = current->next;
    }
    if (!paymentProcessed)
    {
        cout << "No approved renting history found for the specified tenant and property." << endl;
    }
    return paymentProcessed;
}

bool Rent::hasApprovedRentingHistory(string tenant, string propID)
{
    DoublyNode<Rent> *current = Rent::rentHistoryDoublyLinkedList.head;

    while (current != nullptr)
    {
        if (current->data.tenant == tenant && current->data.prop == propID && current->data.status == "Approved")
        {
            return true; // Found approved renting history for the specified tenant and property
        }
        current = current->next;
    }

    return false; // No approved renting history found for the specified tenant and property
}

void Rent::paymentStatus()
{
    cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(14) << left << "Paid Status" << setw(16) << left << "Username" << setw(24) << left << "Total Paid Amount" << setw(26) << left << "Total Payable Amount"
         << setw(17) << left << "Rent Status" << setw(21) << left << "Rent Request Time" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

    DoublyNode<Rent> *current = rentHistoryDoublyLinkedList.head;

    while (current != nullptr)
    {
        double totalAmount = current->data.monthlyRent + current->data.deposit;

        // Calculate the paid status
        string paidStatus = (current->data.status == "Confirmed") ? "Paid" : "Unpaid";

        // Convert requestedDate to string format for display
        struct tm *timeinfo;
        time_t requestedDate = current->data.getRequestedDate(); // Get requestedDate from Rent instance
        timeinfo = localtime(&requestedDate); // Convert time_t to tm struct
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo); // Format as desired

        cout << setw(14) << left << paidStatus;
        cout << setw(16) << left << current->data.tenant;
        cout << setw(24) << left << fixed << setprecision(2) << current->data.totalPaid;
        cout << setw(26) << left << fixed << setprecision(2) << totalAmount;
        cout << setw(17) << left << current->data.status;
        cout << setw(21) << left << buffer << endl;

        current = current->next;
    }

    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}

// Check if the property ID is in the pending rent history queue
bool Rent::isPropertyInPendingQueue(string propID)
{
    DoublyNode<Rent> *current = Rent::rentRequestQueue.getHead();
    while (current != nullptr)
    {
        if (current->data.prop == propID)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Check if the property ID is in the renting history doubly linked list
bool Rent::isPropertyInRentHistory(string propID)
{
    DoublyNode<Rent> *current = Rent::rentHistoryDoublyLinkedList.head;
    while (current != nullptr)
    {
        if (current->data.prop == propID)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

DoublyLinkedList<Property> Property::readCSV()
{
    ifstream file("mudah-apartment-kl-selangor.csv");
    string line;
    DoublyLinkedList<Property> propertyDoublyLinkedList;
    int g = 0;

    while (getline(file, line))
    {
        g++;
        if (g == 1)
            continue; // skip first row
        // line = "100323185,The Hipster @ Taman Desa,2022,RM 4 200 per month,Kuala Lumpur - Taman Desa,Condominium,5,2,6,1842 sq.ft.,Fully Furnished,\"Minimart, Gymnasium, Security, Playground, Swimming Pool, Parking, Lift, Barbeque area, Multipurpose hall, Jogging Track\",\"Air-Cond, Cooking Allowed, Washing Machine\",Kuala Lumpur";
        // cout << "hi" << line << endl;
        istringstream iss(line);
        string item;
        string data[14];

        int n = 0;
        while (getline(iss, item, ','))
        {
            if (item.front() == '"')
            {
                // handle quoted field spanning multiple lines
                string nextitem;

                while (getline(iss, nextitem, ','))
                {
                    item += "," + nextitem;
                    if (nextitem.back() == '"')
                    {
                        break;
                    };
                };
            }
            data[n] = item;
            n++;
        }

        data[0] = (data[0].empty()) ? "NA" : data[0];
        data[1] = (data[1].empty()) ? "NA" : data[1];
        data[2] = (data[2].empty()) ? "-1" : data[2];

        if (data[3].empty())
        {
            data[3] = "-1";
        }
        else
        {
            // Remove spaces from the input string
            data[3].erase(remove(data[3].begin(), data[3].end(), ' '), data[3].end());
            // Extract the numeric part of the string
            size_t start = data[3].find_first_of("0123456789");
            size_t end = data[3].find_first_not_of("0123456789", start);
            string numericPart = data[3].substr(start, end - start);

            // Convert the numeric part to an integer
            data[3] = numericPart;
        }

        data[4] = (data[4].empty()) ? "NA" : data[4];
        data[5] = (data[5].empty()) ? "NA" : data[5];

        if (data[6].empty())
        {
            data[6] = "NA";
        }
        else
        {
            try
            {
                float floatValue = stof(data[6]);
                int intValue = static_cast<int>(floatValue);
                data[6] = to_string(intValue);
            }
            catch (const invalid_argument &e)
            {
                // Not a valid float, treat as string
                // No conversion needed, keep the original value
            }
        }

        data[7] = (data[7].empty()) ? "-1" : data[7];
        data[8] = (data[8].empty()) ? "-1" : data[8];
        if (data[9].empty())
        {
            data[9] = "-1";
        }
        else
        {
            string temp = data[9].substr(0, data[9].length() - 7);

            data[9] = temp;
        }

        data[10] = (data[10].empty()) ? "NA" : data[10];

        data[11] = (data[11].empty()) ? "NA" : data[11];

        data[12] = (data[12].empty()) ? "NA" : data[12];

        data[13] = (data[13].empty()) ? "NA" : data[13];

        Property temp(data[0], data[1], stoi(data[2]), stoi(data[3]), data[4],

                      data[5], data[6], stoi(data[7]), stoi(data[8]), stoi(data[9]),

                      data[10], data[11], data[12], data[13]);

        propertyDoublyLinkedList.insertAtbeginning(temp);

        // break;
    }

    //    propertyDoublyLinkedList.showForward();

    return propertyDoublyLinkedList;
}

void displayPage(const DoublyLinkedList<Property> &sortedList, int startIdx, int pageSize)
{
    DoublyNode<Property> *curr = sortedList.head;

    int count = 0;
    int endIdx = startIdx + pageSize;

    // Traverse the list to the starting index
    while (count < startIdx && curr)
    {
        curr = curr->next;
        count++;
    }

    // Display properties from startIdx to endIdx
    cout << "\n--- All Property Details ---\n";
    while (curr && count < endIdx)
    {
        cout << curr->data << "\n";
        curr = curr->next;
        count++;
    }
}

void Property::viewProperties(string tenant, int method, const DoublyLinkedList<Property> &sortedList)
{
    Rent rq;
    const int pageSize = 10; // Number of properties to display per page
    int currentPage = 1;
    int totalProperties = sortedList.getSize();
    int totalPages = (totalProperties + pageSize - 1) / pageSize;

    char option;
    do
    {
        // Display properties for the current page
        cout << "\n--- Page " << currentPage << "/" << totalPages << " ---\n";
        displayPage(sortedList, (currentPage - 1) * pageSize, pageSize);
        cout << "\n--- Page " << currentPage << "/" << totalPages << " ---\n";
        // Display navigation menu
        cout << "\n--- Navigation ---\n";
        if (method == 1)
        {
            cout << "R - Rent Request\n";
        }
        cout << "P - Previous Page\n";
        cout << "N - Next Page\n";
        cout << "V - View Specific Page\n";
        cout << "Q - Quit\n";
        cout << "Choose an option: ";
        cin >> option;

        // Handle user input for navigation
        switch (toupper(option))
        {
        case 'R':
            if (method == 1)
            {
                string propID, startdate, enddate;
                cout << "=== Rent Request ===" << endl;
                cout << "\nEnter Property ID : ";
                do
                {
                    getline(cin, propID);
                } while (propID == "");

                // Check if the property ID is in the pending rent history queue
                bool existsInPendingQueue = rq.isPropertyInPendingQueue(propID);

                // Check if the property ID is in the renting history doubly linked list
                bool existsInRentHistory = rq.isPropertyInRentHistory(propID);

                if (existsInPendingQueue || existsInRentHistory)
                {
                    cout << "This property has already been rented. Please choose another property." << endl;
                }
                else
                {
                    cout << "Enter Start Date : ";
                    do
                    {
                        getline(cin, startdate);
                    } while (startdate == "");
                    cout << "Enter End Date : ";
                    do
                    {
                        getline(cin, enddate);
                    } while (enddate == "");

                    rq.addRentRequest(propID, tenant, startdate, enddate, "pending");
                    cout << "Rent request submitted." << endl
                         << endl;
                }
                break;
            }
        case 'P':
            if (currentPage > 1)
            {
                currentPage--;
            }
            break;
        case 'N':
            if (currentPage < totalPages)
            {
                currentPage++;
            }
            break;
        case 'V':
            int page;
            cout << "Enter the page number (1 to " << totalPages << "): ";
            cin >> page;
            if (page >= 1 && page <= totalPages)
            {
                currentPage = page;
            }
            else
            {
                cout << "Invalid page number. Please try again.\n";
            }
            break;
        case 'Q':
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (toupper(option) != 'Q');
}

void Property::guestViewAllProp()
{
    DoublyLinkedList<Property> myList = readCSV();
    viewProperties("tenant", 0, myList);
}

void Property::filterProperties(int filterProp, const string &filterValue, const DoublyLinkedList<Property> &myList)
{
    DoublyNode<Property> *proptemp = myList.head;
    int pageSize = 20; // Number of properties to display per page
    int currentPage = 1;
    int propertyCount = 0;

    int totalProperties = 0;
    // Calculate the total number of properties that match the filter
    while (proptemp != nullptr)
    {
        if ((filterProp == 1 && proptemp->data.propType[0] == filterValue[0]) ||
            (filterProp == 2 && proptemp->data.propFurnished[0] == filterValue[0]))
        {
            totalProperties++;
        }
        proptemp = proptemp->next;
    }

    // Reset the proptemp pointer to the beginning of the list
    proptemp = myList.head;

    cout << endl
         << left << setw(15) << "ID" << left << setw(25)
         << "|Property Type" << left << setw(25)
         << "|Furnished" << left << setw(20)
         << "|Region" << left << setw(20)
         << "|Property Name" << endl;

    cout << string(105, '-') << endl;

    if (proptemp == nullptr)
    {
        cout << string(10, ' ') << "     Property List is Empty    " << endl;
        return;
    }

    char choice;
    do
    {
        // Display the page number
        cout << "\n=== " << currentPage << "/" << ((totalProperties + pageSize - 1) / pageSize) << " pages===\n";

        propertyCount = 0;
        while (proptemp != nullptr)
        {
            if ((filterProp == 1 && proptemp->data.getPropType()[0] == filterValue[0]) ||
                (filterProp == 2 && proptemp->data.getPropFurnished()[0] == filterValue[0]))
            {
                cout << left << setw(15) << proptemp->data.getAdsId() << setw(1) << left
                     << setw(25) << proptemp->data.getPropType()
                     << setw(25) << proptemp->data.getPropFurnished()
                     << setw(20) << proptemp->data.getPropRegion()
                     << setw(20) << proptemp->data.getPropName() << endl;

                propertyCount++;
                if (propertyCount % pageSize == 0)
                {
                    // Ask the user to continue to the next page or exit
                    cout << "\nPress 'N' for the Next Page, or any other key to Quit: ";
                    cin >> choice;
                    if (toupper(choice) == 'N')
                    {
                        currentPage++;
                        // Show the incremented page number before displaying the next page
                        cout << "\n=== " << currentPage << "/" << ((totalProperties + pageSize - 1) / pageSize) << " pages===\n";
                    }
                    else
                    {
                        break; // Exit the loop if the user chooses not to continue
                    }
                }
            }

            proptemp = proptemp->next;
        }

        // Check any property left or quit
        if (proptemp == nullptr || (propertyCount % pageSize != 0) || (toupper(choice) != 'N'))
        {
            // exit loop if no more properties left to display
            break;
        }
    } while (true);
}

void Property::sortPropertiesByRent(int sort)
{
    cout << endl
         << "==== Sort Property by Rent ====" << endl;
    DoublyLinkedList<Property> myList = readCSV();

    // Measure execution time
    auto start = chrono::high_resolution_clock::now();

    if (sort == 1)
    {
        myList.quickSort(compareByMonthlyRent);
        cout << "Sorted in ascending order by rent." << endl;
    }
    else if (sort == 2)
    {
        // Implement sorting in descending order by using a custom comparator function
        myList.quickSort([](const Property &prop1, const Property &prop2)
                         { return prop1.getMonthlyRent() > prop2.getMonthlyRent(); });
        cout << "Sorted in descending order by rent." << endl;
    }

    // Measure execution time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nExecution time (Quick Sort): " << duration.count() << " seconds" << endl;

    viewProperties("tenant", 0, myList);
}

void Property::sortPropertiesByLocation(int sort)
{
    cout << endl
         << "==== Sort Property by Location ====" << endl;
    DoublyLinkedList<Property> myList = readCSV();

    // Measure execution time
    auto start = chrono::high_resolution_clock::now();

    if (sort == 1)
    {
        myList.quickSort(compareByLocation);
        cout << "Sorted in ascending order by location." << endl;
    }
    else if (sort == 2)
    {
        // Implement sorting in descending order by using a custom comparator function
        myList.quickSort([](const Property &prop1, const Property &prop2)
                         { return prop1.getPropLocation() > prop2.getPropLocation(); });
        cout << "Sorted in descending order by location." << endl;
    }

    // Measure execution time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nExecution time (Quick Sort): " << duration.count() << " seconds" << endl;

    viewProperties("tenant", 0, myList);
}

void Property::sortPropertiesBySize(int sort)
{
    cout << endl
         << "==== Sort Property by Size ====" << endl;
    DoublyLinkedList<Property> myList = readCSV();

    // Measure execution time
    auto start = chrono::high_resolution_clock::now();

    if (sort == 1)
    {
        myList.quickSort(compareBySize);
        cout << "Sorted in ascending order by size." << endl;
    }
    else if (sort == 2)
    {
        // Implement sorting in descending order by using a custom comparator function
        myList.quickSort([](const Property &prop1, const Property &prop2)
                         { return prop1.getPropSize() > prop2.getPropSize(); });
        cout << "Sorted in descending order by size." << endl;
    }

    // Measure execution time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nExecution time (Quick Sort): " << duration.count() << " seconds" << endl;

    viewProperties("tenant", 0, myList);
}

void Property::insertionSortPropertiesByRent()
{
    cout << endl
         << "==== Sort Property by Monthly Rent ====" << endl;
    DoublyLinkedList<Property> myList = readCSV();

    // Measure execution time
    auto start = chrono::high_resolution_clock::now();

    myList.insertionSort([](const Property &p1, const Property &p2)
                         { return p1.getMonthlyRent() < p2.getMonthlyRent(); });
    cout << "Sorted in descending order by monthly rent." << endl;

    // Measure execution time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nExecution time (Insertion Sort): " << duration.count() << " seconds" << endl;

    viewProperties("tenant", 0, myList);
}

void Property::insertionSortPropertiesByLocation()
{
    cout << endl
         << "==== Sort Property by Location ====" << endl;
    DoublyLinkedList<Property> myList = readCSV();

    // Measure execution time
    auto start = chrono::high_resolution_clock::now();

    myList.insertionSort([](const Property &p1, const Property &p2)
                         { return p1.getPropLocation() < p2.getPropLocation(); });
    cout << "Sorted in descending order by Location." << endl;

    // Measure execution time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nExecution time (Insertion Sort): " << duration.count() << " seconds" << endl;

    viewProperties("tenant", 0, myList);
}

void Property::insertionSortPropertiesBySize()
{
    cout << endl
         << "==== Sort Property by Size ====" << endl;
    DoublyLinkedList<Property> myList = readCSV();

    // Measure execution time
    auto start = chrono::high_resolution_clock::now();

    myList.insertionSort([](const Property &p1, const Property &p2)
                         { return p1.getPropSize() < p2.getPropSize(); });
    cout << "Sorted in descending order by Size." << endl;

    // Measure execution time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nExecution time (Insertion Sort): " << duration.count() << " seconds" << endl;

    viewProperties("tenant", 0, myList);
}

// binary search
void Property::searchPropertyByID(string id)
{
    DoublyLinkedList<Property> myList = readCSV();

    // Measure execution time
    auto start = chrono::high_resolution_clock::now();

    myList.quickSort([](const Property &prop1, const Property &prop2)
                     { return prop1.getAdsId() < prop2.getAdsId(); });

    DoublyNode<Property> *result = myList.binarySearch(id);

    // Measure execution time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nExecution time (Binary Search): " << duration.count() << " seconds" << endl;

    if (result)
    {
        // Property with the given ID found
        cout << "\nProperty ID " << id << " found!" << endl
             << result->data << endl;
    }
    else
    {
        cout << "Property ID " << id << " not found!" << endl;
    }
}

Property Property::searchByID(string id)
{
    DoublyLinkedList<Property> myList = readCSV();
    myList.quickSort([](const Property &prop1, const Property &prop2)
                     { return prop1.getAdsId() < prop2.getAdsId(); });

    DoublyNode<Property> *result = myList.binarySearch(id);

    if (result)
    {
        // Property with the given ID found
        return result->data;
    }
}

// linear search
void Property::searchPropIDLinear(string id)
{
    DoublyLinkedList<Property> myList = readCSV();
    cout << "\nLinear Search Property by ID.... " << endl;

    // Measure execution time
    auto start = chrono::high_resolution_clock::now();
    DoublyNode<Property> *result = myList.linearSearch([&](const Property &property)
                                                       { return property.getAdsId() == id; });

    // Measure execution time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "\nExecution time (Linear Search): " << duration.count() << " secs." << endl;

    if (result)
    {
        // Property with the given ID found
        cout << "\nProperty with ID " << id << " found: " << endl
             << result->data << endl;
    }
    else
    {
        cout << "\nProperty with ID " << id << " not found." << endl;
    }
}
