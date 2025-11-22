#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Structure for TimeSlot
struct TimeSlot {
    string time;
    string status;
};

// Function to read available/not available slots from file
vector<TimeSlot> readRoomAvailability(const string &roomFile) {
    vector<TimeSlot> slots;
    ifstream fin(roomFile);
    if (!fin) {
        cout << "Cannot open file: " << roomFile << endl;
        return slots;
    }

    string time, status;
    while (getline(fin, time, ',')) {   // assuming each line format: "8:00-9:15,Available"
        getline(fin, status);
        TimeSlot t;
        t.time = time;
        t.status = status;
        slots.push_back(t);
    }

    fin.close();
    return slots;
}

// Function to show available rooms
void showAvailableRooms() {
    int buildingChoice, roomTypeChoice;

    cout << "Select your Building ?\n";
    cout << "1) Building 1\n2) Building 2\n3) Building 3\n4) Back\n";
    cout << "Enter your choice: ";
    cin >> buildingChoice;

    if (buildingChoice == 4) return;

    cout << "Select your Room type ?\n";
    cout << "1) Classroom\n2) Labroom\n3) Back\n";
    cout << "Enter your choice: ";
    cin >> roomTypeChoice;

    if (roomTypeChoice == 3) return;

    // For demonstration, we assume 2 rooms
    vector<string> rooms;
    if (buildingChoice == 2 && roomTypeChoice == 1) {  // Building 2, Classroom
        rooms.push_back("401");
        rooms.push_back("403");
    }

    cout << "\nAvailable Rooms:\n";
    for (auto &room : rooms) {
        string filename = "RoomAvailablesornotinfo/" + room + "available.txt";
        vector<TimeSlot> slots = readRoomAvailability(filename);
        cout << "Room " << room << ":\n";
        for (auto &s : slots) {
            cout << s.time << " -> " << s.status << "\n";
        }
        cout << "--------------------------\n";
    }
}

int main() {
    cout << "===== Room Booking System =====\n";
    showAvailableRooms();
    return 0;
}   
