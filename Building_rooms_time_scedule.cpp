#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for system()
using namespace std;

/*
Function to show room list 
-> // Display the list of rooms for a specific building from the file
*/
void showRoomList(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'!" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;  // Show every room no.
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
        cout << "\n\tWhich building's schedule do you want to see?\n";
        cout << "\t1) Building 1\n";
        cout << "\t2) Building 2\n";
        cout << "\t3) Building 3\n";
        cout << "\t4) Back\n";
        cout << "\n\tEnter your choice: ";
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
            cout << "\t\tBuilding " << buildingChoice << ": Which type of room do you want to see?\n";
            cout << "\t\t1) Classroom\n";
            cout << "\t\t2) Lab Room\n";
            cout << "\t\t3) Back\n";
            cout << "\n\t\tEnter your choice: ";
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
                    cout << "Invalid input! Returning to building menu.\n";
                    system("pause");
                    goto BuildingMenu;
                }
            } // end room selection loop
        } // end room type loop
    } // end building selection loop
}


// Main Function
int main() {
    int mainChoice;
    while (true) {
        system("CLS");
        cout << "\t\t\t~Welcome to our Room Management Program~\n";
        cout << "\n\t\t========== Room Management Menu ==========\n";
        cout << "\t\t1) View Time Schedule\n";
        cout << "\t\t2) Exit\n";
        cout << "\n\t\tEnter your choice: ";
        cin >> mainChoice;
        system("CLS");

        switch (mainChoice) {
            case 1:
                viewTimeScheduleMenu();  // Info of Time schedule
                break;
            case 2:
                cout << "Exiting program......\n";
                cout << "\nThank you ";
                return 0;
            default:
                cout << "Invalid option! Press any key to try again...\n";
                system("pause");
        }
    }
}
