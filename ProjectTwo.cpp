/*
* CS-300 Project Two
* Author: Pi'ilani Apo
*/


#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

// Define Course structure to hold course information
struct Course {
    // Course number
    std::string number;
    // Course title
    std::string title;
    // List of prerequisite course numbers
    std::vector<std::string> prerequisites;
};

// Function prototypes
void loadCourses(std::unordered_map<std::string, Course>& courses);
void printCourseList(const std::unordered_map<std::string, Course>& courses);
void printCourseInfo(const std::unordered_map<std::string, Course>& courses);
std::string makeUpperCase(const std::string& str);


int main()
{
    // Hash table to store courses
    std::unordered_map<std::string, Course> courses;
    // User menu choice
    int choice;

    std::cout << "Welcome to your course assistant.\n";

    do {
        // Display menu options
        std::cout << "Menu:\n";
        std::cout << "1) Load Courses\n";
        std::cout << "2) Print Course List\n";
        std::cout << "3) Print Course Information\n";
        std::cout << "9) Exit\n";
        std::cout << "Please select an option: ";
        std::cin >> choice;

        // Handle menu choices
        switch (choice) {
            case 1:
                loadCourses(courses);
                break;
            case 2:
                printCourseList(courses);
                break;
            case 3:
                printCourseInfo(courses);
                break;
            case 9:
                std::cout << "Hope you enjoyed our course assistant!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}

// Function to load courses from file
void loadCourses(std::unordered_map<std::string, Course>& courses) {
    std::string filename;
    std::cout << "Enter the course data file name: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string number, title, prereq;
        std::getline(ss, number, ',');
        std::getline(ss, title, ',');

        Course course;
        course.number = number;
        course.title = title;

        while (std::getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses[number] = course;
    }

    std::cout << "Courses loaded successfully.\n";
}

// Function to print sorted list of courses
void printCourseList(const std::unordered_map<std::string, Course>& courses) {
    std::vector<std::string> courseNumbers;

    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }
    std::sort(courseNumbers.begin(), courseNumbers.end());

    for (const std::string& number : courseNumbers) {
        std::cout << number << ", " << courses.at(number).title << std::endl;
    }
}

// Function to print information about a specific course
void printCourseInfo(const std::unordered_map<std::string, Course>& courses) {
    std::string courseNumber;
    std::cout << "What course do you want to look at? ";
    std::cin >> courseNumber;
    courseNumber = makeUpperCase(courseNumber);

    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        std::cout << it->second.number << ", " << it->second.title << std::endl;
        std::cout << "Prerequisites: ";

        for (const std::string& prereq : it->second.prerequisites) {
            std::cout << prereq << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Course not found.\n";
    }
}

// Function to convert string to uppercase
std::string makeUpperCase(const std::string& str) {
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}