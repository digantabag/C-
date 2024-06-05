#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Zodiac {
    string name;
    string startDate;
    string endDate;
    string description;
};

vector<Zodiac> zodiacSigns = {
    {"Aries", "03-21", "04-19", "Adventurous and energetic"},
    {"Taurus", "04-20", "05-20", "Patient and reliable"},
    {"Gemini", "05-21", "06-20", "Adaptable and versatile"},
    {"Cancer", "06-21", "07-22", "Emotional and loving"},
    {"Leo", "07-23", "08-22", "Generous and warmhearted"},
    {"Virgo", "08-23", "09-22", "Meticulous and reliable"},
    {"Libra", "09-23", "10-22", "Diplomatic and charming"},
    {"Scorpio", "10-23", "11-21", "Determined and forceful"},
    {"Sagittarius", "11-22", "12-21", "Optimistic and freedom-loving"},
    {"Capricorn", "12-22", "01-19", "Practical and prudent"},
    {"Aquarius", "01-20", "02-18", "Friendly and humanitarian"},
    {"Pisces", "02-19", "03-20", "Imaginative and sensitive"}
};

int compatibilityMatrix[12][12] = {
    // Aries, Taurus, Gemini, Cancer, Leo, Virgo, Libra, Scorpio, Sagittarius, Capricorn, Aquarius, Pisces
    {80, 50, 70, 40, 90, 60, 70, 50, 85, 55, 65, 45}, // Aries
    {50, 75, 60, 80, 40, 85, 55, 75, 50, 85, 60, 80}, // Taurus
    {70, 60, 85, 50, 80, 70, 90, 60, 85, 55, 70, 65}, // Gemini
    {40, 80, 50, 85, 60, 70, 55, 90, 65, 75, 55, 85}, // Cancer
    {90, 40, 80, 60, 95, 55, 75, 65, 90, 50, 80, 60}, // Leo
    {60, 85, 70, 70, 55, 90, 65, 80, 55, 85, 60, 75}, // Virgo
    {70, 55, 90, 55, 75, 65, 85, 60, 80, 60, 85, 70}, // Libra
    {50, 75, 60, 90, 65, 80, 60, 85, 55, 75, 70, 80}, // Scorpio
    {85, 50, 85, 65, 90, 55, 80, 55, 95, 60, 80, 65}, // Sagittarius
    {55, 85, 55, 75, 50, 85, 60, 75, 60, 85, 55, 80}, // Capricorn
    {65, 60, 70, 55, 80, 60, 85, 70, 80, 55, 90, 70}, // Aquarius
    {45, 80, 65, 85, 60, 75, 70, 80, 65, 80, 70, 85}  // Pisces
};

string findZodiacSign(int month, int day) {
    for (const auto& zodiac : zodiacSigns) {
        int startMonth = stoi(zodiac.startDate.substr(0, 2));
        int startDay = stoi(zodiac.startDate.substr(3, 2));
        int endMonth = stoi(zodiac.endDate.substr(0, 2));
        int endDay = stoi(zodiac.endDate.substr(3, 2));

        if ((month == startMonth && day >= startDay) || (month == endMonth && day <= endDay) ||
            (month > startMonth && month < endMonth) ||
            (startMonth > endMonth && ((month > startMonth && month <= 12) || (month >= 1 && month < endMonth)))) {
            return zodiac.name + ": " + zodiac.description;
        }
    }
    return "Invalid date!";
}

int findCompatibility(const string& sign1, const string& sign2) {
    int index1 = -1, index2 = -1;
    for (int i = 0; i < zodiacSigns.size(); i++) {
        if (zodiacSigns[i].name == sign1) index1 = i;
        if (zodiacSigns[i].name == sign2) index2 = i;
    }
    if (index1 == -1 || index2 == -1) return -1;
    return compatibilityMatrix[index1][index2];
}

int main() {
    int choice;
    while (true) {
        cout << "1. Zodiac Check" << endl;
        cout << "2. Zodiac Match" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int day, month;
            cout << "Enter your birth date (MM DD): ";
            cin >> month >> day;
            string zodiac = findZodiacSign(month, day);
            cout << "Your Zodiac Sign: " << zodiac << endl;
        } else if (choice == 2) {
            int day1, month1, day2, month2;
            cout << "Enter the first birth date (MM DD): ";
            cin >> month1 >> day1;
            cout << "Enter the second birth date (MM DD): ";
            cin >> month2 >> day2;

            string sign1 = findZodiacSign(month1, day1);
            string sign2 = findZodiacSign(month2, day2);

            size_t colonPos1 = sign1.find(":");
            size_t colonPos2 = sign2.find(":");

            if (colonPos1 != string::npos) sign1 = sign1.substr(0, colonPos1);
            if (colonPos2 != string::npos) sign2 = sign2.substr(0, colonPos2);

            int compatibility = findCompatibility(sign1, sign2);
            if (compatibility != -1) {
                cout << "Compatibility between " << sign1 << " and " << sign2 << " is: " << compatibility << "%" << endl;
            } else {
                cout << "Invalid Zodiac Signs!" << endl;
            }
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
