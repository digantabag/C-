#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

string getComputerChoice() {
    string choices[] = {"Rock", "Paper", "Scissors"};
    int randomIndex = rand() % 3; // Random index between 0 and 2
    return choices[randomIndex];
}

string getUserChoice() {
    int choice;
    cout << "Enter your choice: 1. Rock  2. Paper  3. Scissors: ";
    cin >> choice;

    while (choice < 1 || choice > 3) {
        cout << "Invalid choice! Please enter 1 for Rock, 2 for Paper, or 3 for Scissors: ";
        cin >> choice;
    }

    switch (choice) {
        case 1:
            return "Rock";
        case 2:
            return "Paper";
        case 3:
            return "Scissors";
        default:
            return "";
    }
}

string determineWinner(string userChoice, string computerChoice) {
    if (userChoice == computerChoice) {
        return "It's a tie!";
    } else if ((userChoice == "Rock" && computerChoice == "Scissors") ||
               (userChoice == "Paper" && computerChoice == "Rock") ||
               (userChoice == "Scissors" && computerChoice == "Paper")) {
        return "You win!";
    } else {
        return "Computer wins!";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    char playAgain;
    do {
        string userChoice = getUserChoice();
        string computerChoice = getComputerChoice();

        cout << "You chose: " << userChoice << endl;
        cout << "Computer chose: " << computerChoice << endl;

        string result = determineWinner(userChoice, computerChoice);
        cout << result << endl;

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!" << endl;

    return 0;
}
