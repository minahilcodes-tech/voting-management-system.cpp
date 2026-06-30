#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function declarations
bool isIDUsed(int ID);//bool contain two values 'true'/'false'
void recordID(int ID);
void castVote();
void showResults();

int main() {
    string name;
    int ID, age;
    cout << "\t\t\t\t--------------------------";
    cout << "\n\t\t\t\tVoting Management System\n";
    cout << "\t\t\t\t--------------------------";
    // Taking user's details
    cout << "\nEnter your name: ";
    cin.ignore();    //is use to clear the buffer
    getline(cin, name);
    cout << "Enter your ID (unique): ";
    cin >> ID;
    // Check if ID is already used
    if (isIDUsed(ID)) {
        cout << "\nError: This ID has already been used to vote!\n";
        return 0;
    }
    cout << "Enter your age: ";
    cin >> age;
    // Check age eligibility
    if (age < 18) {
        cout << "\nError: You must be 18 or older to vote!\n";
        return 0;
    }
    // Record ID and allow user to vote
    recordID(ID);
    castVote();
    showResults();

    return 0;
}

// Function to check if the ID has already been used
bool isIDUsed(int ID) {
    fstream file("IDs.txt", ios::in);
    if (!file.is_open()) {
        return false; // File doesn't exist yet, 
    }

    int existingID;
    while (file >> existingID) {
        if (existingID == ID) {
            //   file.close();
            return true; // ID already used
        }
    }
    file.close();
    return false;
}

// Function to record a used ID
void recordID(int ID) {
    fstream file("IDs.txt", ios::app);
    if (file.is_open()) {
        file << ID << endl;
        file.close();
    }
    else {
        cout << "\nError: Unable to record ID.\n";
    }
}

// Function to cast a vote
void castVote() {
    int partyChoice;
    string parties[] = { "PTI", "PMLN", "PPP" };
    int voteCounts[3] = { 0, 0, 0 };

    cout << "\nChoose a party to cast your vote:\n";
    cout << "1 - PTI\n";
    cout << "2 - PMLN\n";
    cout << "3 - PPP\n";
    cout << "Enter your choice: ";
    cin >> partyChoice;

    if (partyChoice < 1 || partyChoice > 3) {
        cout << "\nInvalid choice! Your vote is wasted.\n";
        return;
    }

    // Read current vote counts
    fstream file("Votes.txt", ios::in);
    if (file.is_open()) {
        for (int i = 0; i < 3; i++) {
            file >> voteCounts[i];
        }
        file.close();
    }

    // Increment the selected party's vote count
    voteCounts[partyChoice - 1]++;

    // Write updated vote counts back to the file
    file.open("Votes.txt", ios::out);
    if (file.is_open()) {
        for (int i = 0; i < 3; i++) {
            file << voteCounts[i] << endl;
        }
        file.close();
        cout << "\nYour vote has been successfully cast for " << parties[partyChoice - 1] << "!\n";
    }
    else {
        cout << "\nError: Unable to record vote.\n";
    }
}

// Function to display results
void showResults() {
    char show;
    int voteCounts[3] = { 0, 0, 0 };
    string parties[] = { "PTI", "PMLN", "PPP" };

    cout << "\nDo you want to see the voting results? (y/n): ";
    cin >> show;

    if (show == 'y' || show == 'n') {
        fstream file("Votes.txt", ios::in);
        if (file.is_open()) {
            for (int i = 0; i < 3; i++) {
                file >> voteCounts[i];
            }
            file.close();

            // Display results
            cout << "\n--- Voting Results ---\n";
            for (int i = 0; i < 3; i++) {
                cout << parties[i] << " = " << voteCounts[i] << " votes\n";
            }
        }
        else {
            cout << "\nNo votes have been recorded yet.\n";
        }
    }
    else {
        cout << "\nThank you for participating in the voting process!\n";
    }
}
