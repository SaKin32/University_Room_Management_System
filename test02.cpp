#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include <vector>
#include <cstdlib> // for system()
#include <map>    // Global map to store booked slots for each room+day
#include <set>   // Global map to store booked slots for each room+day

using namespace std;


// Global booking data
map<string, set<int>> bookedSlots;
set<string> bookedIDs;  // store full ID


// Global Flags
bool backToPreviousMenu = false;
bool backToMainMenu = false;

// Function to create a folder if it doesn't exist
void createFolder(const string &folderName) {
#ifdef _WIN32
    system(("if not exist " + folderName + " mkdir " + folderName).c_str());
#else
    system(("mkdir -p " + folderName).c_str());
#endif
}

/* 
Function to show info from a file.
-> To read data line by line from any file and display it on the screen.
*/
void showInfoFromFile(string filename) {
    ifstream file(filename);  // File open
    if (!file.is_open()) {   // if file doesn't open then it pass error messege
        cout << "Error: Could not open file '" << filename << "'!" << endl;
        cout << "\n";
        return;
    }
    string line;

    // Display each line of the file on the screen
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}


/* 
Function to show room schedule
-> Show the schedule for a specific room and day by searching from the file.
*/
void showRoomSchedule(string filename, string roomNo, string day) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'!" << endl;
        cout << "\n";
        return;
    }

    string line;
    bool found = false;

    //Header print
    cout << "\n---------------------------------------------\n";
    cout << "Building : " << filename.substr(filename.find("B") + 1, 1) << "\n";
    cout << "Room     : " << roomNo << "\n";
    cout << "Day      : " << day << "\n";
    cout << "---------------------------------------------\n\n";
    cout << "   ============ Time Schedule ============\n";

    // Search for a line in the file matching the room number and day
    while (getline(file, line)) {
        //Check in this line if room and day both are found. That means this line might contain the schedule we need
        if (line.find(roomNo) != string::npos && line.find(day) != string::npos) {
            size_t pos = line.find(day); // Finds the starting position of the word "day" in that line.
            /* 
            line.substr(pos + day.length()) means it extracts the part of the line that comes after the word day.
            For example : 
            if the line is - 
                   "503 Sunday 9:00AM - 10:00AM CSE Class" 
            this code will extract:  
                    "9:00AM - 10:00AM CSE Class"
            */
            string schedulePart = line.substr(pos + day.length());
            cout << schedulePart << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No schedule found for room " << roomNo << " on " << day << "!\n";
        cout << "\n";
    }

    file.close();
}


/*
Function to show room list 
-> // Display the list of rooms for a specific building from the file
*/
void showRoomList(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'!" << endl;
        cout << "\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}
 

// View Info Menu : Full details / Classrooms / LabRooms 
void viewInfoMenu() {

    selectBuilding:; // label for goto if needed

    //info choice loop
    while(true) {
        system("CLS");  //screen clear
        int buildingChoice;

        cout << "\n\n";
        cout << "\t Select Building : \n\n";
        cout << "\t 1) Building 1 \n";
        cout << "\t 2) Building 2 \n";
        cout << "\t 3) Building 3 \n";
        cout << "\t 4) Back \n";
        cout << "\n\t Enter your choice : ";
        cin >> buildingChoice;

        if (buildingChoice == 4)
            return; // Back to return main menu
        if (buildingChoice < 1 || buildingChoice > 4) {
            cout << "Invalid choice! Press try again\n";
            system("pause");
            cout << "\n";
            continue;
        }    

        //Here File name are make by dynamic method    
        string buildingFile = "Buildingsinfo/building" + to_string(buildingChoice) + ".txt";
        string classFile    = "Classroomsinfo/classroomsB" + to_string(buildingChoice) + ".txt";
        string labFile      = "Labroomsinfo/labroomsB" + to_string(buildingChoice) + ".txt";
        
        // info choice loop
        while(true){
        system("CLS");
        int infoChoice;
        cout <<"\n\n";
        cout << "\t ======== Building " << buildingChoice << " Info ======== \n\n";
        cout << "\t 1) Full Details \n";
        cout << "\t 2) Classrooms Only\n";
        cout << "\t 3) Lab Rooms Only\n";
        cout << "\t 4) Back\n\n";
        cout << "\n\t Enter your choice : ";
        cin >> infoChoice;
        system("CLS");

        //Display file content based on the user's choice.
        switch (infoChoice) {
            case 1:
                cout << "\t --------------------------------------------- \n";
                cout << "\t   Building " << buildingChoice << " Full Details \n";
                cout << "\t --------------------------------------------- \n\n";
                showInfoFromFile(buildingFile);
                break;
            case 2:
                cout << "\t --------------------------------------------- \n";
                cout << "\t   Building " << buildingChoice << " Classrooms \n";
                cout << "\t --------------------------------------------- \n\n";
                showInfoFromFile(classFile);
                break;
            case 3:
                cout << "\t --------------------------------------------- \n";
                cout << "\t   Building " << buildingChoice << " Lab Rooms \n";
                cout << "\t --------------------------------------------- \n\n";
                showInfoFromFile(labFile);
                break;
            case 4:
                goto selectBuilding; // Go back to building selection
            default:
                cout << "Invalid choice!\n";
                system("pause");
                cout << "\n";
                continue;
        }

        char actionChoice;
        while(true){
            cout << "\n\n\n Do you want to see another building info? (Y/N) ";
            cout << "\n Press 0 to go back";
            cout << "\n\n : ";
            cin >> actionChoice;

            if (actionChoice == '0') {
                break; // Repeat info menu for same building
            } else if (actionChoice == 'Y' || actionChoice == 'y') {
                goto selectBuilding; // Break current info loop and select new building
            } else if (actionChoice == 'N' || actionChoice == 'n') {
                cout << "\nPress Enter to return to main menu...\n";
                cin.ignore(); // Ignore leftover newline
                cin.get();    // Wait for Enter
                return;       // Back to main menu
            } else {
               cout << "Invalid input!Press valid option";
             }
          } // End of infoChoice loop
       } // End of selectBuilding while loop
   }
}


// RAM-only booking with clean updated schedule on new page
// Function to show & book room schedule (only selected day)


// Function prototypes
void roomBookingSystemMenu();
void viewRoomBookingMenu();
void showRoomScheduleWithBooking(string filename, string roomNo, string day);

void showRoomScheduleWithBooking(string filename, string roomNo, string day) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'!" << endl;
        system("pause");
        return;
    }

    vector<string> fullLines;
    string line;

    while (getline(file, line))
        fullLines.push_back(line);
    file.close();

    vector<string> scheduleLines;
    
    for (auto &curr : fullLines) {
        if (curr.find(day) != string::npos)
            scheduleLines.push_back(curr);
    }

    if (scheduleLines.empty()) {
        cout << "No schedule found for " << day << "!\n";
        system("pause");
        return;
    }

    createFolder("RoomBookings");

    while (true) {
        system("CLS");
        cout << "---------------------------------------------\n";
        cout << "Room     : " << roomNo << "\n";
        cout << "Day      : " << day << "\n";
        cout << "---------------------------------------------\n";
        cout << "      You can book only available rooms!\n";
        cout << "      =================================\n\n";

        // Show schedule
        int slotNum = 1;

        for (auto &curr : scheduleLines) {
            size_t posArrow = curr.find("->");
            string status = "Not Available";
            string timePart = "";

            if (posArrow != string::npos) {
                string afterArrow = curr.substr(posArrow + 2);

                if (afterArrow.find("-") != string::npos)
                    status = "Available";

                size_t posDay = curr.find(day);
                timePart = curr.substr(posDay + day.length(), posArrow - (posDay + day.length()));

                while (!timePart.empty() && timePart[0] == ' ') 
                     timePart.erase(0,1);
                while (!timePart.empty() && timePart.back() == ' ') 
                     timePart.pop_back();
            }

            string key = roomNo + day;
            if (bookedSlots[key].count(slotNum))
                status = "Booked";

            printf("%d. %-17s   |  %s\n", slotNum, timePart.c_str(), status.c_str());
            slotNum++;
        }

        // Ask for timeslot
        int choice;
        cout << "\nEnter your Timeslot to book or 0 to go back: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            system("pause");
            continue;
        }

        // **CORRECTED: 0 returns to Available Rooms list**
        if (choice == 0) {
            return;  // no flags, just return to caller to show room list
        }

        if (choice < 1 || choice > scheduleLines.size()) {
            cout << "Invalid number! Please input valid number.\n";
            system("pause");
            continue;
        }

        string key = roomNo + day;
        if (bookedSlots[key].count(choice)) {
            cout << "\nThis timeslot is already booked!\n";
            system("pause");
            continue;
        }

        size_t posArrow = scheduleLines[choice - 1].find("->");
        string afterArrow = scheduleLines[choice - 1].substr(posArrow + 2);
        if (afterArrow.find("-") == string::npos) {
            cout << "\nThis timeslot is not available!\n";
            system("pause");
            continue;
        }

        // Book in RAM and file
        bookedSlots[key].insert(choice);
        string bookingID = roomNo + day.substr(0,3) + to_string(choice);
        bookedIDs.insert(bookingID);

        string bookingFile = "RoomBookings/" + roomNo + ".txt";
        ofstream bookingOut(bookingFile, ios::app);
        bookingOut << "BookingID: " << bookingID
                   << " | Day: " << day
                   << " | Slot: " << choice
                   << " | Time: " << afterArrow << "\n";
        bookingOut.close();

        system("CLS");
        cout << "\nThank you for booking this room!\n";
        cout << "Your Booking ID is: " << bookingID << "\n\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << " Press Enter to to return main menu ";
        cin.get();

        backToMainMenu = true;  // set flag to indicate we want main menu
        return;  // exit current function and go back to main menu
    }
}



// View Time Schedule Menu : Building, Room Type, Room Number, see day schedule
void viewTimeScheduleMenu() {
    const string validDays[] = {
        "Sunday", 
        "Monday", 
        "Tuesday", 
        "Wednesday", 
        "Thursday", 
        "Friday", 
        "Saturday"
    };

    char nextAction = ' ';  //global inside function

    BuildingMenu:  ;

    // Building selection loop
    while(true) {
        system("CLS");
        int buildingChoice;
        cout << "\t Which building's schedule do you want to see?\n";
        cout << "\t 1) Building 1\n";
        cout << "\t 2) Building 2\n";
        cout << "\t 3) Building 3\n";
        cout << "\t 4) Back\n\n";
        cout << "\n\t Enter your choice : ";
        cin >> buildingChoice;

        if (buildingChoice == 4)
            return;  //Back main menu
        if (buildingChoice < 1 || buildingChoice > 4) {
            cout << "Invalid choice!Press try again\n";
            cout << "\n";
            system("pause");
            continue;
        }

        //paths for classroom and labroom lists
        string classFile = "Classroomsinfo/classroomsB" + to_string(buildingChoice) + ".txt";
        string labFile   = "Labroomsinfo/labroomsB" + to_string(buildingChoice) + ".txt";

        // Room type loop selection
        while (true) {
            system("CLS");
            int roomType;
            cout << "\t Building " << buildingChoice << ": Which type of room do you want to see?\n";
            cout << "\t 1) Classroom\n";
            cout << "\t 2) Lab Room\n";
            cout << "\t 3) Back\n\n";
            cout << "\n\t Enter your choice : ";
            cin >> roomType;

            if (roomType == 3)
                break;  //back to building selection

            if (roomType != 1 && roomType != 2) {
                cout << "Invalid choice! Try again.\n";
                cout << "\n";
                system("pause");
                continue;
            }

            string roomFile = (roomType == 1) ? classFile : labFile;

            //Room selection lopp
            while(true) {
            system("CLS");
            cout << "\nAvailable Rooms:\n";
            cout << "\n";
            showRoomList(roomFile);  //Show Room list

                // Input the room number and days
                string roomNo;
                while(true) {
                cout << "\nEnter the room number or 0 to go back : ";
                cin >> roomNo;

                if (roomNo == "0")
                    break; //back to room type menu

                // Validate room number exists
                ifstream file(roomFile);
                    string line;
                    bool roomFound = false;
                    while(getline(file, line)) {
                        if(line.find(roomNo) != string::npos) {
                            roomFound = true;
                            break;
                        }
                    }
                    file.close();

                    if(!roomFound) {
                        cout << "\n" << roomNo << " class room is not found! Please press a valid classroom from this list.\n";
                        system("pause");
                        continue; // Ask room number again
                    }
                    break; // Valid room number
                }
                if(roomNo == "0") 
                  break;
 

                // day selection
                string dayInput;
                bool validDay = false;

                while (!validDay) {
                    cout << "Enter the day or 0 to go back : ";
                    cin >> dayInput;
                    if (dayInput == "0")
                        break; //back to room selection

                    // Normalize input: first letter uppercase, rest lowercase
                    dayInput[0] = toupper(dayInput[0]);
                    for (int i = 1; i < dayInput.size(); i++)
                        dayInput[i] = tolower(dayInput[i]);

                    for (auto d : validDays) {
                        if (d == dayInput) {
                            validDay = true;
                            break;
                        }
                    }

                    if (!validDay)
                        cout << "Invalid day! Please try again.\n";
                        cout << "\n";
               }

                if (!validDay)
                    continue;  //back pressed

                //Make & show schedule files    
                string scheduleFile = "RoomSchedules/" + roomNo + "B" + to_string(buildingChoice) + "schedule.txt";
                system("CLS");
                showRoomSchedule(scheduleFile, roomNo, dayInput);

               // Ask user what to do next

                while (true) { // input loop
                char actionChoice;
                cout << "\n\n\nDo you want to see another building info? (Y/N) ";
                cout << "\nPress 0 to go back";
                cout << "\n\n: ";
                cin >> actionChoice;

                if(actionChoice == '0') {
                    continue; // Back to room list
                } else if(actionChoice == 'Y' || actionChoice == 'y') {
                    goto BuildingMenu; // Jump to building selection
                } else if(actionChoice == 'N' || actionChoice == 'n') {
                    cout << "Press Enter to return to main menu...\n";
                    cin.ignore();
                    cin.get();
                    return; // Back to main menu
                } else {
                    cout << "Invalid input! Try again (Y/N).\n";
                    system("pause");
                   continue;
                }
            } // end room selection loop
        } // end room type loop
    } // end building selection loop
  }
}


// Function prototype
void viewRoomBookingMenu();



void cancelBookingRoom() {
    if (bookedIDs.empty()) {
        cout << "\nNo bookings available to cancel!\n";
        system("pause");
        return;
    }

    system("CLS");
    cout << "\n===== Cancel Booking by Booking ID =====\n\n";

    while (true) {
        string bookingID;
        cout << "Enter Booking ID to cancel or 0 to go back: ";
        cin >> bookingID;

        if (bookingID == "0") return;

        auto it = bookedIDs.find(bookingID);
        if (it != bookedIDs.end()) {
            bookedIDs.erase(it); // remove from bookedIDs

            // ALSO remove from bookedSlots
            // Booking ID format: roomNo + dayShort + slotNum
            string roomNo = bookingID.substr(0, bookingID.size()-4); // e.g. 203
            string dayShort = bookingID.substr(bookingID.size()-4, 3); // Sun
            int slotNum = stoi(bookingID.substr(bookingID.size()-1,1)); // 4

            // Build key for bookedSlots map
            // dayShort = "Sun" → need full day name to match key? assume key=roomNo+fullDay
            // To simplify, just loop and erase slot
            for (auto &pair : bookedSlots) {
                set<int> &slots = pair.second;

                if (slots.count(slotNum)) {
                    slots.erase(slotNum);
                    break;
                }
            }

            cout << "\nBooking ID " << bookingID << " cancelled successfully!\n";
            system("pause");
            return;
        } else {
            cout << "\nInvalid Booking ID! Try again.\n";
            system("pause");
        }
    }
}



void roomBookingSystemMenu() {
    int choice;
    while(true) {
        system("CLS");
        cout << "\t ===== Room Booking System ===== \n\n";
        cout << "\t 1) Confirm to booking room \n";
        cout << "\t 2) Cancel to booking room \n";
        cout << "\t 3) Back \n";
        cout << "\n\t Enter your choice : ";
        cin >> choice;

        switch(choice) {
            case 1:
                viewRoomBookingMenu();

                if (backToMainMenu) 
                return; // go to main menu
                break;
            case 2:
                cancelBookingRoom();
                break;
            case 3:
                return; // Back to main menu
            default:
                cout << "Invalid choice! Please try again.\n";
                system("pause");
        }
    }
}




// Room Booking System
void viewRoomBookingMenu() {

    backToPreviousMenu = false;
    backToMainMenu = false;

    const string validDays[] = { 
        "Sunday", 
        "Monday", 
        "Tuesday", 
        "Wednesday", 
        "Thursday", 
        "Friday", 
        "Saturday" 
    };

    while (true) {
        system("CLS");
        int buildingChoice;
          cout << "\t Which building's schedule do you want to see?\n";
          cout << "\t 1) Building 1\n";
          cout << "\t 2) Building 2\n";
          cout << "\t 3) Building 3\n";
          cout << "\t 4) Back\n\n";
          cout << "\n\t Enter your choice : ";
          cin >> buildingChoice;

        if (buildingChoice == 4) 
            return; // back to previous menu

        if (buildingChoice < 1 || buildingChoice > 3) {
            cout << "Invalid building choice! Please try again.\n";
            system("pause");
            continue;
        }

        while (true) { // Room Type Menu
            system("CLS");
             int roomType;
             cout << "\t Building " << buildingChoice << ": Which type of room do you want to see?\n";
             cout << "\t 1) Classroom\n";
             cout << "\t 2) Lab Room\n";
             cout << "\t 3) Back\n\n";
             cout << "\n\t Enter your choice : ";
             cin >> roomType;

            if (roomType == 3) 
                break; // back to building menu
            if (roomType != 1 && roomType != 2) {
                cout << "Invalid option! Please try again.\n";
                system("pause");
                continue;
            }

            string roomFile = (roomType == 1) ? "Classroomsinfo/classroomsB" : "Labroomsinfo/labroomsB";
            roomFile += to_string(buildingChoice) + ".txt";

            bool backToRoomTypeMenu = false;

            while (!backToRoomTypeMenu) {
                system("CLS");
                cout << "\nAvailable Rooms:\n\n";

                ifstream inFile(roomFile);
                if (!inFile.is_open()) {
                    cout << "No rooms available or file not found!\n";
                    system("pause");
                    backToRoomTypeMenu = true;
                    break;
                }

                string roomLine;

                while (getline(inFile, roomLine)) cout << roomLine << "\n";
                inFile.close();

                // Ask for room number
               string roomNo;

               while (true) {
               cout << "\nEnter the room number to book or 0 to go back: ";
               cin >> roomNo;

               if (roomNo == "0") {
                backToRoomTypeMenu = true;
                 break; // back to Room Type menu
                }

               // Validate room number exists in file
               ifstream chk(roomFile);
               string line;
               bool found = false;

               while (getline(chk, line)) {
               // Trim leading spaces
               line.erase(0, line.find_first_not_of(" \t"));
                string first = line.substr(0, line.find(' ')); // first column = room number

                 if (first == roomNo) {
                   found = true;
                     break;
                    }
                   }
               chk.close();

               if (!found) {
                 cout << "\nInvalid room number! Please enter a valid room from the list.\n";
               system("pause");
                continue; // ask again
                 }
                   break; // valid room => move forward
                 }

                  // Ask for day
                  string dayInput;
                  bool validDay = false;

                  while (!validDay) {
                    cout << "\nEnter the day or 0 to go back: ";
                    cin >> dayInput;

                    if (dayInput == "0") 
                      break;

                    dayInput[0] = toupper(dayInput[0]);
                    for (int i = 1; i < dayInput.size(); i++) 
                       dayInput[i] = tolower(dayInput[i]);

                    for (auto d : validDays) if (d == dayInput) 
                      validDay = true;

                    if (!validDay) {
                        cout << "Invalid day! Please enter a valid day.\n";
                        system("pause");
                    }
                  }

                  if (!validDay) 
                   continue;

                // Show booking schedule only if valid room and day
                showRoomScheduleWithBooking(
                    "RoomSchedules/" + roomNo + "B" + to_string(buildingChoice) + "schedule.txt",
                    roomNo, dayInput
                );

                if (backToMainMenu) 
                  return;
                if (backToPreviousMenu) {
                    backToPreviousMenu = false;
                     break;
                }
            }
        }
    }
}


// Main Function
int main() {

    int mainChoice;
    while (true) {
        system("CLS");
        cout << "\t\t\t\t\t  ~ Welcome to our Room Management Program ~ \n";
        cout << "\n\t\t\t\t\t ========== Room Management Menu ========== \n\n";
        cout << "\t\t\t\t 1) View Info\n";
        cout << "\t\t\t\t 2) View Time Schedule\n";
        cout << "\t\t\t\t 3) Room Booked System\n";
        cout << "\t\t\t\t 4) Exit\n\n";
        cout << "\n\t\t\t Enter your choice : ";
        cin >> mainChoice;
        system("CLS");

        switch (mainChoice) {
            case 1:
                viewInfoMenu();  // Info of Buildings
                break;
            case 2:
                viewTimeScheduleMenu();  // Info of Time schedule
                break;
            case 3:
                roomBookingSystemMenu(); // Room Booking
                break;
            case 4:
                cout << "Exiting program......\n";
                cout << "\nThank you ";
                return 0;
            default:
                cout << "Invalid option! Press any key to try again...\n";
                system("pause");
        }
    }
}