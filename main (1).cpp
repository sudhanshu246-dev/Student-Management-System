#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

class Student {
public:
    int roll;
    string name;
    vector<int> marks;

    float getTotal() const {
        float total = 0;
        for (int m : marks)
            total += m;
        return total;
    }

    float getPercentage() const {
        if (marks.size() == 0) return 0;
        return getTotal() / marks.size();
    }

    char getGrade() const {
        float per = getPercentage();
        if (per >= 90) return 'A';
        else if (per >= 75) return 'B';
        else if (per >= 60) return 'C';
        else if (per >= 50) return 'D';
        else return 'F';
    }
};

vector<Student> students;

// ================= FILE SAVE =================
void saveToFile() {
    ofstream file("students.txt");
    for (const Student &s : students) {
        file << s.roll << endl;
        file << s.name << endl;
        file << s.marks.size() << endl;
        for (int m : s.marks)
            file << m << " ";
        file << endl;
    }
    file.close();
}

// ================= FILE LOAD =================
void loadFromFile() {
    students.clear();
    ifstream file("students.txt");
    if (!file) return;

    while (true) {
        Student s;
        int subjectCount;

        if (!(file >> s.roll))
            break;

        file.ignore();
        getline(file, s.name);
        file >> subjectCount;

        s.marks.clear();
        for (int i = 0; i < subjectCount; i++) {
            int m;
            file >> m;
            s.marks.push_back(m);
        }

        students.push_back(s);
    }

    file.close();
}

// ================= ADD STUDENT =================
void addStudent() {
    Student s;

    cout << "\nEnter Roll No: ";
    cin >> s.roll;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, s.name);

    int subjects;
    cout << "Enter number of subjects: ";
    cin >> subjects;

    for (int i = 0; i < subjects; i++) {
        int m;
        cout << "Enter marks for Subject " << i + 1 << ": ";
        cin >> m;
        s.marks.push_back(m);
    }

    students.push_back(s);
    saveToFile();

    cout << "\nStudent Added Successfully!\n";
}

// ================= DISPLAY STUDENT =================
void displayStudent(const Student &s) {
    cout << "\n----------------------------------";
    cout << "\nRoll No: " << s.roll;
    cout << "\nName: " << s.name;

    cout << "\nMarks: ";
    for (int m : s.marks)
        cout << m << " ";

    cout << "\nTotal: " << s.getTotal();
    cout << "\nPercentage: " << fixed << setprecision(2)
         << s.getPercentage() << "%";
    cout << "\nGrade: " << s.getGrade();
    cout << "\n----------------------------------\n";
}

// ================= DISPLAY ALL =================
void displayAll() {
    if (students.empty()) {
        cout << "\nNo records found!\n";
        return;
    }

    for (const Student &s : students)
        displayStudent(s);
}

// ================= SEARCH =================
void searchStudent() {
    int roll;
    cout << "\nEnter Roll No to Search: ";
    cin >> roll;

    for (const Student &s : students) {
        if (s.roll == roll) {
            displayStudent(s);
            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

// ================= UPDATE =================
void updateStudent() {
    int roll;
    cout << "\nEnter Roll No to Update: ";
    cin >> roll;

    for (Student &s : students) {
        if (s.roll == roll) {
            cin.ignore();
            cout << "Enter New Name: ";
            getline(cin, s.name);

            int subjects;
            cout << "Enter new number of subjects: ";
            cin >> subjects;

            s.marks.clear();
            for (int i = 0; i < subjects; i++) {
                int m;
                cout << "Enter marks for Subject " << i + 1 << ": ";
                cin >> m;
                s.marks.push_back(m);
            }

            saveToFile();
            cout << "\nRecord Updated Successfully!\n";
            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

// ================= DELETE =================
void deleteStudent() {
    int roll;
    cout << "\nEnter Roll No to Delete: ";
    cin >> roll;

    for (int i = 0; i < students.size(); i++) {
        if (students[i].roll == roll) {
            students.erase(students.begin() + i);
            saveToFile();
            cout << "\nRecord Deleted Successfully!\n";
            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

// ================= STATISTICS =================
void showStatistics() {
    if (students.empty()) {
        cout << "\nNo records found!\n";
        return;
    }

    float sum = 0;
    float highest = students[0].getPercentage();
    float lowest = students[0].getPercentage();

    for (const Student &s : students) {
        float per = s.getPercentage();
        sum += per;

        if (per > highest) highest = per;
        if (per < lowest) lowest = per;
    }

    cout << "\nClass Average: "
         << fixed << setprecision(2)
         << sum / students.size() << "%";

    cout << "\nHighest Percentage: " << highest << "%";
    cout << "\nLowest Percentage: " << lowest << "%\n";
}

// ================= TOPPER =================
void showTopper() {
    if (students.empty()) {
        cout << "\nNo records found!\n";
        return;
    }

    Student topper = students[0];

    for (const Student &s : students) {
        if (s.getPercentage() > topper.getPercentage())
            topper = s;
    }

    cout << "\n===== CLASS TOPPER =====\n";
    displayStudent(topper);
}

// ================= MAIN =================
int main() {
    loadFromFile();

    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Show Statistics";
        cout << "\n7. Show Topper";
        cout << "\n8. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: showStatistics(); break;
            case 7: showTopper(); break;
            case 8: cout << "\nExiting Program...\n"; break;
            default: cout << "\nInvalid Choice!\n";
        }

    } while (choice != 8);

    return 0;
}