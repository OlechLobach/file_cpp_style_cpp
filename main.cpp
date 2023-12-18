#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 

using namespace std;


struct Employee {
    string lastName;
    string firstName;
    int age;
    

    void displayInfo() {
        cout << "Last Name: " << lastName << endl;
        cout << "First Name: " << firstName << endl;
        cout << "Age: " << age << endl;
        
    }
};

struct Node {
    Employee emp;
    Node* next;
};

class EmployeeList
{
private:
    Node* head;
public:
    EmployeeList() {
        head = nullptr;
    }

    void addEmployee(const Employee& newEmployee) {
        Node* newNode = new Node;
        newNode->emp = newEmployee;
        newNode->next = head;
        head = newNode;
        cout << "Employee added successfully." << endl;
    }

    void displayEmployeesByAge(int targetAge) {
        Node* current = head;
        while (current != nullptr) {
            if (current->emp.age == targetAge) {
                current->emp.displayInfo();
            }
            current = current->next;
        }
    }

    void displayEmployeesByLetter(char targetLetter) {
        Node* current = head;
        while (current != nullptr) {
            if (current->emp.lastName[0] == targetLetter) {
                current->emp.displayInfo();
            }
            current = current->next;
        }
    }

    void searchByLastName(const string& lastName) {
        Node* current = head;
        while (current != nullptr) {
            if (current->emp.lastName == lastName) {
                current->emp.displayInfo();
            }
            current = current->next;
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            Node* current = head;
            while (current != nullptr) {
                file << current->emp.lastName << " " << current->emp.firstName << " " << current->emp.age << endl;
                current = current->next;
            }
            file.close();
            cout << "Data saved to file: " << filename << endl;
        }
        else {
            cerr << "Unable to open file: " << filename << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string lastName, firstName;
            int age;
            while (file >> lastName >> firstName >> age) {
                Employee newEmployee;
                newEmployee.lastName = lastName;
                newEmployee.firstName = firstName;
                newEmployee.age = age;
                addEmployee(newEmployee);
            }
            file.close();
            cout << "Data loaded from file: " << filename << endl;
        }
        else {
            cerr << "Unable to open file: " << filename << endl;
        }
    }

    void displayAllEmployees() {
        Node* current = head;
        while (current != nullptr) {
            current->emp.displayInfo();
            current = current->next;
        }
    }

    ~EmployeeList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
};
void saveDataOnExit(EmployeeList& employees, const string& filename) {
    employees.saveToFile(filename);
}

void onExit() {

    static EmployeeList employees;
    static string filename = "employees.txt"; 
    saveDataOnExit(employees, filename);
}

int main() {
    EmployeeList employees;
    string filename = "employees.txt"; 

    employees.loadFromFile(filename);
    int choice;
    do {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. Search Employee by Last Name\n";
        cout << "3. Display Employees by Age\n";
        cout << "4. Display Employees by First Letter of Last Name\n";
        cout << "5. Save Data to File\n";
        cout << "6. Exit\n";
        cout << "7. Display All Employees\n"; 
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Employee newEmployee;
            cout << "Enter Last Name: ";
            cin >> newEmployee.lastName;
            cout << "Enter First Name: ";
            cin >> newEmployee.firstName;
            cout << "Enter Age: ";
            cin >> newEmployee.age;
            employees.addEmployee(newEmployee);
            break;
        }
        case 2: {
            string searchLastName;
            cout << "Enter Last Name to search: ";
            cin >> searchLastName;
            employees.searchByLastName(searchLastName);
            break;
        }
        case 3: {
            int searchAge;
            cout << "Enter Age to search: ";
            cin >> searchAge;
            employees.displayEmployeesByAge(searchAge);
            break;
        }
        case 4: {
            char searchLetter;
            cout << "Enter First Letter of Last Name to search: ";
            cin >> searchLetter;
            employees.displayEmployeesByLetter(searchLetter);
            break;
        }
        case 5:
            employees.saveToFile(filename);
            break;
        case 6:
            cout << "Exiting... Saving data to file." << endl;
            employees.saveToFile(filename);
            break;
        case 7: 
            employees.displayAllEmployees();
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 6);
    atexit(onExit);
    return 0;
}