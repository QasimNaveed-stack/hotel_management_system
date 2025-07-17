#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int ROOM_NUM = 10;

void displayMenu();
void validateInput();
void viewRoomStatus();
void viewAllRooms();
void bookRoom();
void checkoutRoom();
void searchBookingInfo();

struct Room {
    bool isBooked = false;
    string customerName = "";
};

Room rooms[ROOM_NUM];

int main() {
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                viewRoomStatus();
                break;
            case 2:
                viewAllRooms();
                break;
            case 3:
                bookRoom();
                break;
            case 4:
                checkoutRoom();
                break;
            case 5:
                searchBookingInfo();
                break;
            case 6:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

        cout << "\n=======================\n";

    } while (choice != 6);

    return 0;
}

void validateInput() {
    cin.clear();
    cin.ignore(100, '\n');
}

void displayMenu() {
    cout << " ________________________________________\n";
    cout << "|   10 Rooms Hotel Management System     |\n";
    cout << "|________________________________________|\n\n";
    cout << "1. View Room Status\n";
    cout << "2. View All Rooms Status\n";
    cout << "3. Book a Room\n";
    cout << "4. Check Out\n";
    cout << "5. Search Booking Information\n";
    cout << "6. Exit\n\n";
    cout << "Enter your choice: ";
}

void viewRoomStatus() {
    int room;
    cout << "Enter room number (1-10): ";
    cin >> room;

    while (room < 1 || room > 10) {
        validateInput();
        cout << "Invalid room number! Enter again (1-10): ";
        cin >> room;
    }

    if (rooms[room - 1].isBooked) {
        cout << "Room " << room << " is booked by " << rooms[room - 1].customerName << ".\n";
    } else {
        cout << "Room " << room << " is available.\n";
    }
}

void viewAllRooms() {
    for (int i = 0; i < ROOM_NUM; ++i) {
        cout << "Room " << (i + 1) << ": ";
        if (rooms[i].isBooked) {
            cout << "Booked by " << rooms[i].customerName << "\n";
        } else {
            cout << "Available\n";
        }
    }
}

void bookRoom() {
    int room;
    string name;

    cout << "Enter room number (1-10): ";
    cin >> room;

    while (room < 1 || room > 10) {
        validateInput();
        cout << "Invalid room number! Enter again (1-10): ";
        cin >> room;
    }

    if (rooms[room - 1].isBooked) {
        cout << "Room " << room << " is already booked by " << rooms[room - 1].customerName << ".\n";
    } else {
        cout << "Enter customer name: ";
        getline(cin >> ws, name);

        rooms[room - 1].isBooked = true;
        rooms[room - 1].customerName = name;

        ofstream outFile("bookings.txt", ios::app);
        outFile << "Room " << room << " is booked by "<< name << "."<< endl;
        outFile.close();

        cout << "Room " << room << " booked successfully for " << name << ".\n";
    }
}

void checkoutRoom() {
    int room, days;
    double amountPaid;
    int ratePerDay;

    cout << "Enter room number (1-10): ";
    cin >> room;

    while (room < 1 || room > 10) {
        validateInput();
        cout << "Invalid room number! Enter again (1-10): ";
        cin >> room;
    }

    if (!rooms[room - 1].isBooked) {
        cout << "Room is not currently booked.\n";
        return;
    }

    cout << "Enter number of days stayed: ";
    cin >> days;

    cout << "Enter daily room rate: ";
    cin >> ratePerDay;

    double totalBill = ratePerDay * days;
    cout << "Total bill: " << totalBill << "\n";

    cout << "Enter amount paid: ";
    cin >> amountPaid;

    double balance = amountPaid - totalBill;
    if (balance < 0) {
        cout << "Remaining balance: " << -balance << "\n";
    } else {
        cout << "Change to return: " << balance << "\n";
    }

    ofstream outFile("checkout.txt", ios::app);
    outFile << "Room " << room << ", Customer: " << rooms[room - 1].customerName
            << ", Days: " << days << ", Bill: " << totalBill
            << ", Paid: " << amountPaid << "\n\n";
    outFile.close();

    rooms[room - 1].isBooked = false;
    rooms[room - 1].customerName = "";

    cout << "Checkout completed for Room " << room << ".\n";
}

void searchBookingInfo() {
    int room;
    cout << "Enter room number (1-10): ";
    cin >> room;

    while (room < 1 || room > 10) {
        validateInput();
        cout << "Invalid room number! Enter again (1-10): ";
        cin >> room;
    }

    if (rooms[room - 1].isBooked) {
        cout << "Room " << room << " is booked by " << rooms[room - 1].customerName << ".\n";
    } else {
        cout << "Room is available.\n";
    }
}
