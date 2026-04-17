#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
using namespace std;

// Constants
const int MAX_SUBJECTS = 6;
const char* FILE_NAME = "students.dat";

// Subject structure
struct Subject {
    char name[30];
    float marks;
    char grade;
};

// Class definition
class Student {
private:
    int rollNo;
    char name[50];
    char department[30];
    int subjectCount;
    Subject subjects[MAX_SUBJECTS];
    float totalMarks;
    float percentage;
    char overallGrade;

public:
    // Constructor
    Student() {
        rollNo = 0;
        strcpy(name, "");
        strcpy(department, "");
        subjectCount = 0;
        totalMarks = 0;
        percentage = 0;
        overallGrade = 'F';
    }

    // Calculate grade for a subject
    char calculateGrade(float marks) {
        if (marks >= 90) return 'A';
        else if (marks >= 80) return 'B';
        else if (marks >= 70) return 'C';
        else if (marks >= 60) return 'D';
        else if (marks >= 50) return 'E';
        else return 'F';
    }

    // Calculate overall percentage and grade
    void calculateOverall() {
        totalMarks = 0;
        for (int i = 0; i < subjectCount; i++) {
            totalMarks += subjects[i].marks;
        }
        percentage = (totalMarks / (subjectCount * 100)) * 100;
        
        if (percentage >= 90) overallGrade = 'A';
        else if (percentage >= 80) overallGrade = 'B';
        else if (percentage >= 70) overallGrade = 'C';
        else if (percentage >= 60) overallGrade = 'D';
        else if (percentage >= 50) overallGrade = 'E';
        else overallGrade = 'F';
    }

    // Input student details with subjects
    void input() {
        cout << "\n┌─────────────────────────────────────────────────┐";
        cout << "\n│         ENTER STUDENT DETAILS                   │";
        cout << "\n└─────────────────────────────────────────────────┘\n";
        
        cout << "Roll Number: ";
        cin >> rollNo;
        cin.ignore();
        
        cout << "Name: ";
        cin.getline(name, 50);
        
        cout << "Department: ";
        cin.getline(department, 30);
        
        cout << "\nNumber of Subjects (max " << MAX_SUBJECTS << "): ";
        cin >> subjectCount;
        
        while (subjectCount <= 0 || subjectCount > MAX_SUBJECTS) {
            cout << "Invalid! Enter between 1 and " << MAX_SUBJECTS << ": ";
            cin >> subjectCount;
        }
        
        cin.ignore();
        
        cout << "\n┌─────────────── SUBJECT DETAILS ───────────────┐\n";
        for (int i = 0; i < subjectCount; i++) {
            cout << "\nSubject " << (i + 1) << ":\n";
            cout << "  Name: ";
            cin.getline(subjects[i].name, 30);
            cout << "  Marks (out of 100): ";
            cin >> subjects[i].marks;
            cin.ignore();
            
            while (subjects[i].marks < 0 || subjects[i].marks > 100) {
                cout << "  Invalid! Enter marks (0-100): ";
                cin >> subjects[i].marks;
                cin.ignore();
            }
            
            subjects[i].grade = calculateGrade(subjects[i].marks);
        }
        
        calculateOverall();
    }
    
    // Display student summary (one line)
    void displaySummary() const {
        cout << "│ " << left << setw(10) << rollNo
             << "│ " << setw(20) << name
             << "│ " << setw(15) << department
             << "│ " << setw(8) << fixed << setprecision(2) << percentage
             << "│ " << setw(6) << overallGrade << "│\n";
    }
    
    // Display complete student details with all subjects
    void displayFull() const {
        cout << "\n╔══════════════════════════════════════════════════════════════╗\n";
        cout << "║                    STUDENT INFORMATION                        ║\n";
        cout << "╚══════════════════════════════════════════════════════════════╝\n";
        cout << "╔══════════════════════════════════════════════════════════════╗\n";
        cout << "║ Roll Number    : " << left << setw(41) << rollNo << "║\n";
        cout << "║ Name           : " << setw(41) << name << "║\n";
        cout << "║ Department     : " << setw(41) << department << "║\n";
        cout << "║ Total Subjects : " << setw(41) << subjectCount << "║\n";
        cout << "╠══════════════════════════════════════════════════════════════╣\n";
        cout << "║                    SUBJECT-WISE MARKS                        ║\n";
        cout << "╠══════════════════════════════════════════════════════════════╣\n";
        cout << "║ " << left << setw(25) << "Subject Name"
             << "║ " << setw(10) << "Marks"
             << "║ " << setw(8) << "Grade" << " ║\n";
        cout << "╠══════════════════════════════════════════════════════════════╣\n";
        
        for (int i = 0; i < subjectCount; i++) {
            cout << "║ " << left << setw(25) << subjects[i].name
                 << "║ " << setw(10) << subjects[i].marks
                 << "║ " << setw(8) << subjects[i].grade << " ║\n";
        }
        
        cout << "╠══════════════════════════════════════════════════════════════╣\n";
        cout << "║ Total Marks    : " << setw(41) << totalMarks << "║\n";
        cout << "║ Percentage     : " << setw(41) << fixed << setprecision(2) << percentage << "%║\n";
        cout << "║ Overall Grade  : " << setw(41) << overallGrade << "║\n";
        
        // Performance message
        cout << "║ Performance    : ";
        if (percentage >= 90)
            cout << left << setw(41) << "Excellent! Outstanding performance!" << "║\n";
        else if (percentage >= 75)
            cout << left << setw(41) << "Very Good! Keep it up!" << "║\n";
        else if (percentage >= 60)
            cout << left << setw(41) << "Good! Can do better!" << "║\n";
        else if (percentage >= 50)
            cout << left << setw(41) << "Satisfactory! Need improvement!" << "║\n";
        else
            cout << left << setw(41) << "Needs hard work! Please focus!" << "║\n";
        
        cout << "╚══════════════════════════════════════════════════════════════╝\n";
    }
    
    // Getters
    int getRollNo() const { return rollNo; }
    float getPercentage() const { return percentage; }
    char getOverallGrade() const { return overallGrade; }
    const char* getName() const { return name; }
    const char* getDepartment() const { return department; }
    
    // File I/O
    void writeToFile(ofstream &out) const {
        out.write((char*)this, sizeof(*this));
    }
    
    void readFromFile(ifstream &in) {
        in.read((char*)this, sizeof(*this));
    }
    
    // Update student
    void update() {
        cout << "\n📝 Enter New Information (leave blank to keep current):\n";
        cin.ignore();
        
        char newName[50];
        cout << "Name [" << name << "]: ";
        cin.getline(newName, 50);
        if (strlen(newName) > 0) strcpy(name, newName);
        
        char newDept[30];
        cout << "Department [" << department << "]: ";
        cin.getline(newDept, 30);
        if (strlen(newDept) > 0) strcpy(department, newDept);
        
        char updateSubjects;
        cout << "\nUpdate subjects? (y/n): ";
        cin >> updateSubjects;
        
        if (updateSubjects == 'y' || updateSubjects == 'Y') {
            cout << "\nEnter new subject details:\n";
            cout << "Number of Subjects (max " << MAX_SUBJECTS << "): ";
            cin >> subjectCount;
            cin.ignore();
            
            for (int i = 0; i < subjectCount; i++) {
                cout << "\nSubject " << (i + 1) << ":\n";
                cout << "  Name: ";
                cin.getline(subjects[i].name, 30);
                cout << "  Marks (0-100): ";
                cin >> subjects[i].marks;
                cin.ignore();
                subjects[i].grade = calculateGrade(subjects[i].marks);
            }
            calculateOverall();
        }
    }
};

// Function declarations
void displayMenu();
void addStudent();
void displayAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void generateReportCard();
void showStatistics();
void showToppers();
void clearScreen();
void pressAnyKey();

// ==================== MAIN FUNCTION ====================
int main() {
    int choice;
    
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║                                                              ║\n";
    cout << "║     ADVANCED STUDENT MANAGEMENT SYSTEM WITH SUBJECTS         ║\n";
    cout << "║                                                              ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
    
    do {
        displayMenu();
        cout << "\nEnter your choice (1-9): ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                generateReportCard();
                break;
            case 7:
                showStatistics();
                break;
            case 8:
                showToppers();
                break;
            case 9:
                cout << "\n╔════════════════════════════════════════════╗\n";
                cout << "║    Thank you for using the system!       ║\n";
                cout << "║           Goodbye!                       ║\n";
                cout << "╚════════════════════════════════════════════╝\n";
                break;
            default:
                cout << "\n❌ Invalid choice! Please enter 1-9.\n";
                pressAnyKey();
        }
    } while(choice != 9);
    
    return 0;
}

// ==================== MENU DISPLAY ====================
void displayMenu() {
    cout << "\n┌─────────────────────────────────────────────────┐\n";
    cout << "│                 MAIN MENU                       │\n";
    cout << "├─────────────────────────────────────────────────┤\n";
    cout << "│  1. Add New Student (with subjects)             │\n";
    cout << "│  2. Display All Students Summary                │\n";
    cout << "│  3. Search Student                              │\n";
    cout << "│  4. Update Student Information                  │\n";
    cout << "│  5. Delete Student Record                       │\n";
    cout << "│  6. Generate Detailed Report Card               │\n";
    cout << "│  7. View Class Statistics                       │\n";
    cout << "│  8. Show Toppers List                           │\n";
    cout << "│  9. Exit                                        │\n";
    cout << "└─────────────────────────────────────────────────┘\n";
}

// ==================== ADD STUDENT ====================
void addStudent() {
    Student s;
    ofstream file(FILE_NAME, ios::binary | ios::app);
    
    if (!file) {
        cout << "\n❌ Error opening file!\n";
        return;
    }
    
    s.input();
    s.writeToFile(file);
    file.close();
    
    cout << "\n✅ Student added successfully!\n";
    pressAnyKey();
}

// ==================== DISPLAY ALL STUDENTS ====================
void displayAllStudents() {
    ifstream file(FILE_NAME, ios::binary);
    Student s;
    int count = 0;
    
    if (!file) {
        cout << "\n❌ No records found! Please add students first.\n";
        pressAnyKey();
        return;
    }
    
    cout << "\n┌────────────┬──────────────────────┬─────────────────┬──────────┬────────┐\n";
    cout << "│ Roll No    │ Name                 │ Department      │ Percent  │ Grade  │\n";
    cout << "├────────────┼──────────────────────┼─────────────────┼──────────┼────────┤\n";
    
    while (file.read((char*)&s, sizeof(s))) {
        s.displaySummary();
        count++;
    }
    
    if (count == 0) {
        cout << "│                    No records to display                          │\n";
    } else {
        cout << "└────────────┴──────────────────────┴─────────────────┴──────────┴────────┘\n";
        cout << "\n📊 Total Students: " << count << endl;
    }
    
    file.close();
    pressAnyKey();
}

// ==================== SEARCH STUDENT ====================
void searchStudent() {
    int roll, found = 0;
    Student s;
    
    cout << "\n🔍 Enter Roll Number to search: ";
    cin >> roll;
    
    ifstream file(FILE_NAME, ios::binary);
    
    if (!file) {
        cout << "\n❌ No records found!\n";
        pressAnyKey();
        return;
    }
    
    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == roll) {
            cout << "\n✅ Student Found!\n";
            s.displayFull();
            found = 1;
            break;
        }
    }
    
    if (!found) {
        cout << "\n❌ Student with Roll Number " << roll << " not found!\n";
    }
    
    file.close();
    pressAnyKey();
}

// ==================== UPDATE STUDENT ====================
void updateStudent() {
    int roll, found = 0;
    Student s;
    
    cout << "\n✏️ Enter Roll Number to update: ";
    cin >> roll;
    
    fstream file(FILE_NAME, ios::binary | ios::in | ios::out);
    
    if (!file) {
        cout << "\n❌ Error opening file!\n";
        pressAnyKey();
        return;
    }
    
    streampos position;
    
    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == roll) {
            found = 1;
            // Fix: Cast to streamoff to avoid ambiguous overload
            position = file.tellg() - static_cast<streamoff>(sizeof(s));
            
            cout << "\n📋 Current Information:\n";
            s.displayFull();
            
            s.update();
            
            file.seekp(position);
            file.write((char*)&s, sizeof(s));
            
            cout << "\n✅ Student record updated successfully!\n";
            break;
        }
    }
    
    if (!found) {
        cout << "\n❌ Student with Roll Number " << roll << " not found!\n";
    }
    
    file.close();
    pressAnyKey();
}

// ==================== DELETE STUDENT ====================
void deleteStudent() {
    int roll, found = 0;
    Student s;
    
    cout << "\n🗑️ Enter Roll Number to delete: ";
    cin >> roll;
    
    ifstream inFile(FILE_NAME, ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    
    if (!inFile) {
        cout << "\n❌ No records found!\n";
        pressAnyKey();
        return;
    }
    
    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == roll) {
            found = 1;
            cout << "\n✅ Student \"" << s.getName() << "\" (Roll: " << roll << ") deleted!\n";
            continue;
        }
        outFile.write((char*)&s, sizeof(s));
    }
    
    inFile.close();
    outFile.close();
    
    if (found) {
        remove(FILE_NAME);
        rename("temp.dat", FILE_NAME);
    } else {
        remove("temp.dat");
        cout << "\n❌ Student with Roll Number " << roll << " not found!\n";
    }
    
    pressAnyKey();
}

// ==================== GENERATE REPORT CARD ====================
void generateReportCard() {
    int roll, found = 0;
    Student s;
    
    cout << "\n📄 Enter Roll Number for Report Card: ";
    cin >> roll;
    
    ifstream file(FILE_NAME, ios::binary);
    
    if (!file) {
        cout << "\n❌ No records found!\n";
        pressAnyKey();
        return;
    }
    
    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == roll) {
            found = 1;
            s.displayFull();
            break;
        }
    }
    
    if (!found) {
        cout << "\n❌ Student with Roll Number " << roll << " not found!\n";
    }
    
    file.close();
    pressAnyKey();
}

// ==================== SHOW STATISTICS ====================
void showStatistics() {
    ifstream file(FILE_NAME, ios::binary);
    Student s;
    int count = 0;
    float totalPercentage = 0, highest = 0, lowest = 100;
    int gradeCount[6] = {0}; // A,B,C,D,E,F
    
    if (!file) {
        cout << "\n❌ No records found!\n";
        pressAnyKey();
        return;
    }
    
    while (file.read((char*)&s, sizeof(s))) {
        count++;
        float percent = s.getPercentage();
        totalPercentage += percent;
        
        if (percent > highest) highest = percent;
        if (percent < lowest) lowest = percent;
        
        switch(s.getOverallGrade()) {
            case 'A': gradeCount[0]++; break;
            case 'B': gradeCount[1]++; break;
            case 'C': gradeCount[2]++; break;
            case 'D': gradeCount[3]++; break;
            case 'E': gradeCount[4]++; break;
            case 'F': gradeCount[5]++; break;
        }
    }
    
    file.close();
    
    if (count == 0) {
        cout << "\n❌ No students in database!\n";
        pressAnyKey();
        return;
    }
    
    cout << "\n╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║                   CLASS STATISTICS                            ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║ Total Students        : " << setw(37) << count << "║\n";
    cout << "║ Average Percentage    : " << setw(37) << fixed << setprecision(2) << (totalPercentage/count) << "%║\n";
    cout << "║ Highest Percentage    : " << setw(37) << highest << "%║\n";
    cout << "║ Lowest Percentage     : " << setw(37) << lowest << "%║\n";
    cout << "║                                                              ║\n";
    cout << "║ Grade Distribution:                                          ║\n";
    cout << "║   A Grade (90%+)      : " << setw(37) << gradeCount[0] << "║\n";
    cout << "║   B Grade (80-89%)    : " << setw(37) << gradeCount[1] << "║\n";
    cout << "║   C Grade (70-79%)    : " << setw(37) << gradeCount[2] << "║\n";
    cout << "║   D Grade (60-69%)    : " << setw(37) << gradeCount[3] << "║\n";
    cout << "║   E Grade (50-59%)    : " << setw(37) << gradeCount[4] << "║\n";
    cout << "║   F Grade (<50%)      : " << setw(37) << gradeCount[5] << "║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
    
    pressAnyKey();
}

// ==================== SHOW TOPPERS ====================
void showToppers() {
    ifstream file(FILE_NAME, ios::binary);
    Student students[100];
    int count = 0;
    
    if (!file) {
        cout << "\n❌ No records found!\n";
        pressAnyKey();
        return;
    }
    
    // Read all students
    while (file.read((char*)&students[count], sizeof(Student)) && count < 100) {
        count++;
    }
    file.close();
    
    if (count == 0) {
        cout << "\n❌ No students in database!\n";
        pressAnyKey();
        return;
    }
    
    // Sort by percentage (bubble sort)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].getPercentage() < students[j + 1].getPercentage()) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    
    cout << "\n╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║                     TOP PERFORMERS                            ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
    cout << "\n┌────────────┬──────────────────────┬─────────────────┬──────────┬────────┐\n";
    cout << "│ Rank       │ Name                 │ Department      │ Percent  │ Grade  │\n";
    cout << "├────────────┼──────────────────────┼─────────────────┼──────────┼────────┤\n";
    
    int toppersCount = (count < 5) ? count : 5;
    for (int i = 0; i < toppersCount; i++) {
        cout << "│ " << left << setw(10) << (i + 1)
             << "│ " << setw(20) << students[i].getName()
             << "│ " << setw(15) << students[i].getDepartment()
             << "│ " << setw(8) << fixed << setprecision(2) << students[i].getPercentage()
             << "│ " << setw(6) << students[i].getOverallGrade() << "│\n";
    }
    
    cout << "└────────────┴──────────────────────┴─────────────────┴──────────┴────────┘\n";
    
    pressAnyKey();
}

// ==================== UTILITY FUNCTIONS ====================
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressAnyKey() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    clearScreen();
}