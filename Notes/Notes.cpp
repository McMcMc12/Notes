#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <ctime>
#include <string>

// Function to check if a date is valid
bool isValidDate(int year, int month, int day) {
    time_t t = time(nullptr);
    tm now;
    localtime_s(&now, &t);
    int currentYear = now.tm_year + 1900;
    int currentMonth = now.tm_mon + 1;
    int currentDay = now.tm_mday;

    if (year < currentYear)
        return false;
    if (year == currentYear && month < currentMonth)
        return false;
    if (year == currentYear && month == currentMonth && day < currentDay)
        return false;

    return true;
}

// Function to write a reminder to a file
void writeReminder(const std::string& fileName, int year, int month, int day, const std::string& activity) {
    std::ifstream fileIn(fileName);
    std::vector<std::string> lines;

    if (fileIn) {
        std::string line;
        while (std::getline(fileIn, line)) {
            lines.push_back(line);
        }
        fileIn.close();
    }

    std::ofstream fileOut(fileName, std::ios::trunc);
    if (fileOut) {
        bool foundDate = false;
        std::string dateStr = std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);

        for (const std::string& line : lines) {
            if (line.substr(0, dateStr.size()) == dateStr) {
                fileOut << line << " | " << activity << std::endl;
                foundDate = true;
            }
            else {
                fileOut << line << std::endl;
            }
        }

        if (!foundDate) {
            fileOut << dateStr << " | " << activity << std::endl;
        }

        std::cout << "Reminder added successfully!" << std::endl;
    }
    else {
        std::cout << "Unable to open file: " << fileName << std::endl;
    }
}

// Function to read and display the contents of a file
void readReminders(const std::string& fileName) {
    std::ifstream file(fileName);
    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
    }
    else {
        std::cout << "Unable to open file: " << fileName << std::endl;
    }
}

int main() {
    std::string fileName = "reminders.txt";
    std::cout << "Welcome to Reminder App!" << std::endl;

    int year, month, day;
    std::cout << "Enter the date (DD/MM/YYYY): ";
    std::cin >> day;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '/');
    std::cin >> month;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '/');
    std::cin >> year;

    if (!isValidDate(year, month, day)) {
        std::cout << "Invalid date!" << std::endl;
        // Date validation checks...
        return 0;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string activity;
    std::cout << "Enter the activity: ";
    std::getline(std::cin, activity);

    writeReminder(fileName, year, month, day, activity);

    char choice;
    std::cout << "Do you want to open the reminders file? (Y/N): ";
    std::cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        readReminders(fileName);
    }

    char addAnother;
    std::cout << "Do you want to add another reminder? (Y/N): ";
    std::cin >> addAnother;

    if (addAnother == 'Y' || addAnother == 'y') {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        main();
    }
    else {
        std::cout << "Exiting Reminder App. Goodbye!" << std::endl;
    }

    return 0;
}
