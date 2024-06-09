#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <windows.h>
using namespace std;

// Define the Workshop struct
struct Workshop {
    string name;
    string startDate;
};

// Define the Club class
class Club {
public:
    string name;
    string contactNo;
    vector<Workshop> workshops;

    Club(string name, string contactNo, vector<Workshop> workshops) 
        : name(name), contactNo(contactNo), workshops(workshops) {}
};

// Function to read clubs from a file
vector<Club> readClubsFromFile(const string& filename) {
    vector<Club> clubs;
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    string line, clubName, contactNo;
    while (getline(file, line)) {
        if (line.empty()) continue;
        clubName = line;
        
        getline(file, contactNo);
        
        vector<Workshop> workshops;
        while (getline(file, line) && !line.empty()) {
            stringstream ss(line);
            string workshopName, startDate;
            getline(ss, workshopName, ',');
            getline(ss, startDate);
            workshops.push_back({workshopName, startDate});
        }
        
        clubs.push_back(Club(clubName, contactNo, workshops));
    }

    file.close();
    return clubs;
}

// Function to write clubs to a file
void writeClubsToFile(const string& filename, const vector<Club>& clubs) {
    ofstream file(filename);

    if (!file) {
        cerr << "Error opening file for writing: " << filename << endl;
        exit(1);
    }

    for (const auto& club : clubs) {
        file << club.name << endl;
        file << club.contactNo << endl;
        for (const auto& workshop : club.workshops) {
            file << workshop.name << "," << workshop.startDate << endl;
        }
        file << endl; // Separate clubs with an empty line
    }

    file.close();
}

// Function to display all clubs
void displayAllClubs(const vector<Club>& clubs) {
    cout << left << setw(15) << "Clubs" 
         << left << setw(30) << "Workshop 1" 
         << left << setw(30) << "Workshop 2" 
         << left << setw(15) << "Contact" << endl;
    cout << string(90, '-') << endl;

    for (const auto& club : clubs) {
        cout << left << setw(15) << club.name 
             << left << setw(30) << club.workshops[0].name + " [" + club.workshops[0].startDate + "]" 
             << left << setw(30) << club.workshops[1].name + " [" + club.workshops[1].startDate + "]"
             << left << setw(15) << club.contactNo << endl;
    }
}

// Function to display the clubs offering a specific workshop
void displayClubsOfferingWorkshop(const vector<Club>& clubs, const string& workshopName) {
    cout << left << setw(15) << "Clubs" 
         << left << setw(30) << "Workshop" 
         << left << setw(30) << "Date" 
         << left << setw(15) << "Contact" << endl;
    cout << string(90, '-') << endl;

    bool found = false;
    for (const auto& club : clubs) {
        for (const auto& workshop : club.workshops) {
            if (workshop.name == workshopName) {
                cout << left << setw(15) << club.name 
                     << left << setw(30) << workshop.name 
                     << left << setw(30) << workshop.startDate 
                     << left << setw(15) << club.contactNo << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No clubs found offering the " << workshopName << " workshop." << endl;
    }
}

// Function to check if a club name already exists
bool clubExists(const vector<Club>& clubs, const string& clubName) {
    return any_of(clubs.begin(), clubs.end(), [&](const Club& club) {
        return club.name == clubName;
    });
}

// Function to add a new club
void addClub(vector<Club>& clubs, const string& filename) {
    string clubName, contactNo;
    vector<Workshop> workshops;

    while (true) {
        cout << "Enter Club Name: ";
        cin.ignore();
        getline(cin, clubName);
        if (clubExists(clubs, clubName)) {
            cout << "This club name already exists, enter another new club name: ";
        } else {
            break;
        }
    }

    cout << "Choose Your 1st Workshop:\n1. C\n2. C++\n3. Python\n4. Java\n5. Web Development\nEnter your choice: ";
    int choice;
    cin >> choice;
    string workshop1Name;
    switch (choice) {
        case 1: workshop1Name = "C"; break;
        case 2: workshop1Name = "C++"; break;
        case 3: workshop1Name = "Python"; break;
        case 4: workshop1Name = "Java"; break;
        case 5: workshop1Name = "Web Development"; break;
        default: cout << "Invalid choice"; return;
    }
    cout << "Enter your 1st workshop date in dd mm yyyy format (e.g., 01 02 2024): ";
    string date1;
    cin.ignore();
    getline(cin, date1);
    workshops.push_back({workshop1Name, date1});

    cout << "Choose Your 2nd Workshop:\n1. C\n2. C++\n3. Python\n4. Java\n5. Web Development\nEnter your choice: ";
    cin >> choice;
    string workshop2Name;
    switch (choice) {
        case 1: workshop2Name = "C"; break;
        case 2: workshop2Name = "C++"; break;
        case 3: workshop2Name = "Python"; break;
        case 4: workshop2Name = "Java"; break;
        case 5: workshop2Name = "Web Development"; break;
        default: cout << "Invalid choice"; return;
    }
    cout << "Enter your 2nd workshop date in dd mm yyyy format (e.g., 01 02 2024): ";
    string date2;
    cin.ignore();
    getline(cin, date2);
    workshops.push_back({workshop2Name, date2});

    cout << "Enter club contact number: ";
    getline(cin, contactNo);

    clubs.push_back(Club(clubName, contactNo, workshops));

    cout << "Press y or yes or Y to save your new club & press n or no or N to go back to previous menu: ";
    char saveChoice;
    cin >> saveChoice;
    if (saveChoice == 'y' || saveChoice == 'Y') {
        writeClubsToFile(filename, clubs);
        cout << "Club Name Successfully added\n";
    } else {
        cout << "Adding new club cancelled.\n";
    }
}

// Function to delete a club
void deleteClub(vector<Club>& clubs, const string& filename) {
    cout << "No.          Clubs\n";
    cout << string(20, '-') << endl;
    for (size_t i = 0; i < clubs.size(); ++i) {
        cout << i + 1 << setw(14) << right << clubs[i].name << endl;
    }
    cout << "Press the club no. to delete the club: ";
    int deleteIndex;
    cin >> deleteIndex;

    if (deleteIndex < 1 || deleteIndex > clubs.size()) {
        cout << "Invalid club number.\n";
        return;
    }

    const auto& club = clubs[deleteIndex - 1];
    cout << "\nClub Details:\n";
    cout << "Club Name : " << club.name << endl;
    cout << "Workshops 1: " << club.workshops[0].name << " [" << club.workshops[0].startDate << "]" << endl;
    cout << "Workshops 2: " << club.workshops[1].name << " [" << club.workshops[1].startDate << "]" << endl;
    cout << "Contact No.: " << club.contactNo << endl;

    cout << "Do you want to delete (Press y or yes or Y to delete & press n or no or N to go back to previous menu): ";
    char deleteChoice;
    cin >> deleteChoice;
    if (deleteChoice == 'y' || deleteChoice == 'Y') {
        clubs.erase(clubs.begin() + deleteIndex - 1);
        writeClubsToFile(filename, clubs);
        cout << "Club - " << club.name << " is Deleted\n";
    } else {
        cout << "Deletion cancelled.\n";
    }
}

// Function to show the developer menu
void showDeveloperMenu(vector<Club>& clubs, const string& filename) {
    string password;
    int attempts = 0;
    const string correctPassword = "1234567";

    while (attempts < 3) {
        cout << "Enter password: ";
        cin >> password;
        if (password == correctPassword) {
            system("clear");
            break;
        } else {
            cout << "Wrong password. Try again.\n";
            ++attempts;
        }
    }

    if (attempts == 3) {
        cout << "Too many wrong attempts. Exiting...\n";
        return;
    }

    int devChoice;
    do {
        cout << "\nDeveloper Menu:\n";
        cout << "1. Add club\n";
        cout << "2. Delete club\n";
        cout << "3. Go back\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> devChoice;

        switch (devChoice) {
            case 1:
                addClub(clubs, filename);
                break;
            case 2:
                deleteClub(clubs, filename);
                break;
            case 3:
                return;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (devChoice != 3);
}

// Main function
int main() {
    const string filename = "clubs.txt";
    vector<Club> clubs = readClubsFromFile(filename);

    int choice;
    do {
        cout << "\nWhich Workshop You Want To Do:\n";
        cout << "1. C Workshop\n";
        cout << "2. C++ Workshop\n";
        cout << "3. Python Workshop\n";
        cout << "4. Java Workshop\n";
        cout << "5. Web Development Workshop\n";
        cout << "6. Exit\n";
        cout << "7. Developer menu\n";
        cout << "8. Show All Clubs\n";
        cout << "Please Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayClubsOfferingWorkshop(clubs, "C");
                break;
            case 2:
                displayClubsOfferingWorkshop(clubs, "C++");
                break;
            case 3:
                displayClubsOfferingWorkshop(clubs, "Python");
                break;
            case 4:
                displayClubsOfferingWorkshop(clubs, "Java");
                break;
            case 5:
                displayClubsOfferingWorkshop(clubs, "Web Development");
                break;
            case 6:
                exit(0);
            case 7:
                showDeveloperMenu(clubs, filename);
                break;
            case 8:
                displayAllClubs(clubs);
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

        cout << "\nPress 1 to exit, press 2 to go back to the main menu: ";
        int backChoice;
        cin >> backChoice;
        if (backChoice == 1) {
            break;
        }
    } while (true);

    return 0;
}
