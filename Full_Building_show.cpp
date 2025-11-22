#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for system()
using namespace std;

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

// View Info Menu : Full details / Classrooms / LabRooms 
void viewInfoMenu() {

    selectBuilding:; // label for goto if needed

    //info choice loop
    while(true) {
        system("CLS");  //screen clear
        int buildingChoice;

        cout << "\n";
        cout << "\tSelect Building to View info :\n";
        cout << "\t1) Building 1\n";
        cout << "\t2) Building 2\n";
        cout << "\t3) Building 3\n";
        cout << "\t4) Back\n";
        cout << "\n\tEnter your choice: ";
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
        cout << "\t\t======== Building " << buildingChoice << " Info ========\n\n";
        cout << "\t1) Full Details\n";
        cout << "\t2) Classrooms Only\n";
        cout << "\t3) Lab Rooms Only\n";
        cout << "\t4) Back\n";
        cout << "\n\tEnter your choice: ";
        cin >> infoChoice;
        system("CLS");

        //Display file content based on the user's choice.
        switch (infoChoice) {
            case 1:
                cout << "---------------------------------------------\n";
                cout << "Building " << buildingChoice << " Full Details\n";
                cout << "---------------------------------------------\n\n";
                showInfoFromFile(buildingFile);
                break;
            case 2:
                cout << "---------------------------------------------\n";
                cout << "Building " << buildingChoice << " Classrooms\n";
                cout << "---------------------------------------------\n\n";
                showInfoFromFile(classFile);
                break;
            case 3:
                cout << "---------------------------------------------\n";
                cout << "Building " << buildingChoice << " Lab Rooms\n";
                cout << "---------------------------------------------\n\n";
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
            cout << "\n\n\nDo you want to see another building info? (Y/N) ";
            cout << "\nPress 0 to go back";
            cout << "\n\n: ";
            cin >> actionChoice;

            if (actionChoice == '0') {
                continue; // Repeat info menu for same building
            } else if (actionChoice == 'Y' || actionChoice == 'y') {
                break; // Break current info loop and select new building
            } else if (actionChoice == 'N' || actionChoice == 'n') {
                cout << "\nPress Enter to return to main menu...\n";
                cin.ignore(); // Ignore leftover newline
                cin.get();    // Wait for Enter
                return;       // Back to main menu
            } else {
                cout << "Invalid input! Returning to building menu.\n";
                system("pause");
                break; // Back to building selection
            }
        } // End of infoChoice loop
    } // End of selectBuilding while loop
}

// Main Function
/*
main() → case 1 → viewInfoMenu() → showInfoFromFile(filename)
*/
int main() {
    int mainChoice;
    while (true) {
        system("CLS");
        cout << "\t\t\t~Welcome to our Room Management Program~\n";
        cout << "\n\t\t========== Room Management Menu ==========\n";
        cout << "\t\t1) View Info\n";
        cout << "\t\t2) Exit\n";
        cout << "\n\t\tEnter your choice: ";
        cin >> mainChoice;
        system("CLS");

        switch (mainChoice) {
            case 1:
                viewInfoMenu();  // Info of Buildings
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
