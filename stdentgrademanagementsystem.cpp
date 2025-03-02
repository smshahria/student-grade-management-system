#include <iostream>
#include <vector>
#include <algorithm>  // For max_element and min_element
#include <limits>     // For numeric_limits
using namespace std;

// Step 1: Define a structure to hold student information
struct Student {
    string name;
    string id;
    vector<int> grades;
};

// Step 2: Declare functions
void addStudent(vector<Student>& students);
void viewStudents(const vector<Student>& students);
double calculateAverage(const vector<int>& grades);
void findHighestGrade(const vector<Student>& students);
void findLowestGrade(const vector<Student>& students);
void updateGrades(vector<Student>& students);

int main() {
    vector<Student> students;  // Vector to store students
    int choice;

    // Menu loop
    while (true) {
        cout << "\nStudent Grades Management System\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Calculate Average Grade\n";
        cout << "4. Find Highest Grade\n";
        cout << "5. Find Lowest Grade\n";
        cout << "6. Update Grades\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                viewStudents(students);
                break;
            case 3: {
                string studentId;
                cout << "Enter student ID to calculate average: ";
                cin >> studentId;
                bool found = false;
                for (const auto& student : students) {
                    if (student.id == studentId) {
                        cout << "Average grade for " << student.name << ": " << calculateAverage(student.grades) << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Student not found.\n";
                }
                break;
            }
            case 4:
                findHighestGrade(students);
                break;
            case 5:
                findLowestGrade(students);
                break;
            case 6:
                updateGrades(students);
                break;
            case 7:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

// Step 3: Function implementations

// Function to add a student
void addStudent(vector<Student>& students) {
    Student newStudent;
    cout << "Enter student name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore any leftover newline character from previous input
    getline(cin, newStudent.name);  // Reading the full name (including spaces)

    cout << "Enter student ID: ";
    cin >> newStudent.id;

    int numGrades;
    cout << "Enter number of grades: ";
    cin >> numGrades;

    newStudent.grades.resize(numGrades);
    cout << "Enter grades: ";
    for (int i = 0; i < numGrades; ++i) {
        while (true) {
            cin >> newStudent.grades[i];
            if (cin.fail() || newStudent.grades[i] < 0) {
                cout << "Invalid input! Please enter a valid grade (positive integer): ";
                cin.clear();  // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            } else {
                break;
            }
        }
    }

    students.push_back(newStudent);  // Add new student to the list
    cout << "Student added successfully.\n";
}

// Function to view all students
void viewStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students in the system.\n";
    } else {
        for (const auto& student : students) {
            cout << "ID: " << student.id << ", Name: " << student.name << ", Grades: ";
            for (int grade : student.grades) {
                cout << grade << " ";
            }
            cout << endl;
        }
    }
}

// Function to calculate the average grade for a student
double calculateAverage(const vector<int>& grades) {
    if (grades.empty()) return 0;  // Handle the case of no grades
    double sum = 0;
    for (int grade : grades) {
        sum += grade;
    }
    return sum / grades.size();
}

// Function to find the highest grade
void findHighestGrade(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students in the system.\n";
        return;
    }

    int highestGrade = -1;
    string highestStudent;

    for (const auto& student : students) {
        for (int grade : student.grades) {
            if (grade > highestGrade) {
                highestGrade = grade;
                highestStudent = student.name;
            }
        }
    }

    cout << "Highest grade is " << highestGrade << " by " << highestStudent << endl;
}

// Function to find the lowest grade
void findLowestGrade(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students in the system.\n";
        return;
    }

    int lowestGrade = 101;  // As grades are usually between 0 and 100
    string lowestStudent;

    for (const auto& student : students) {
        for (int grade : student.grades) {
            if (grade < lowestGrade) {
                lowestGrade = grade;
                lowestStudent = student.name;
            }
        }
    }

    cout << "Lowest grade is " << lowestGrade << " by " << lowestStudent << endl;
}

// Function to update grades for a student
void updateGrades(vector<Student>& students) {
    string studentId;
    cout << "Enter student ID to update grades: ";
    cin >> studentId;

    bool found = false;
    for (auto& student : students) {
        if (student.id == studentId) {
            found = true;
            int numGrades;
            cout << "Enter the number of new grades: ";
            cin >> numGrades;
            student.grades.resize(numGrades);
            cout << "Enter new grades: ";
            for (int i = 0; i < numGrades; ++i) {
                while (true) {
                    cin >> student.grades[i];
                    if (cin.fail() || student.grades[i] < 0) {
                        cout << "Invalid input! Please enter a valid grade (positive integer): ";
                        cin.clear();  // Clear the error state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                    } else {
                        break;
                    }
                }
            }
            cout << "Grades updated successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "Student not found.\n";
    }
}
