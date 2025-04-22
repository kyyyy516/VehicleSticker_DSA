#include <iostream>
#include <fstream>
using namespace std;

class StudentNode
{
    public:
        string matricNumber;
        string password;
        StudentNode *next;
        StudentNode (string m, string p)
        {
            matricNumber = m;
            password = p;
            next = NULL;
        }
};

class RegistrationNode
{
    public:
        string matricNumber;
        string vehicleOwner;
        string icNumber;
        string vehicleType;
        string plateNumber;
        string engineNumber;
        string licenseNumber;
        string licenseExpiryDate;
        string insuranceCompany;
        string policyNumber;
        string insuranceExpiryDate;
        string status;
        string stickerExpiryDate;
        string reasonForRejection;
        RegistrationNode *next;
        bool isHandled;
        RegistrationNode ()
        {
            next = NULL;
            status = "processing";
            stickerExpiryDate = "Registration in process";
            isHandled = false;
        }
};

class List
{
    private:
        StudentNode *headNode;
    
    public:
        List() {headNode = NULL;}
        void addStudent (string, string);
        bool isValid(string, string);
};

void List::addStudent(string m, string p)
{
    StudentNode *node = new StudentNode(m, p);
    if(headNode == NULL)
    {
        headNode = node;
    }
    else
    {
        StudentNode *temp = headNode;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
}

bool List::isValid(string m, string p)
{
    StudentNode *temp = headNode;
    while(temp != NULL)
    {
        if(temp->matricNumber == m && temp->password == p)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

class Queue
{
    private:
        RegistrationNode *frontPtr, *backPtr;
    
    public:
        Queue() {frontPtr = NULL; backPtr = NULL;}
        void enQueue(RegistrationNode*);
        void deQueue();
        bool isEmpty();
        RegistrationNode* getFront();
        RegistrationNode* getRear();
};

void Queue::enQueue(RegistrationNode* node)
{
    if(frontPtr == NULL)
    {
        frontPtr = backPtr = node;
    }
    else
    {
        backPtr->next = node;
        backPtr = node;
    }
}

void Queue::deQueue()
{
    if(frontPtr != NULL)
    {
        RegistrationNode* temp = frontPtr;
        frontPtr = frontPtr->next;

        if(frontPtr == NULL)
        {
            backPtr = NULL;
        }
    }
}

bool Queue::isEmpty()
{
    return frontPtr == NULL && backPtr == NULL;
}

RegistrationNode* Queue::getFront()
{
    return frontPtr;
}

RegistrationNode* Queue::getRear()
{
    return backPtr;
}

// Function to get user input for various attributes
template <typename T>
T getUserInput(const string& prompt)
{
    T value;
    cout << prompt;
    cin >> value;
    return value;
}

// Function to get string input with getline
string getStringInput(const string& prompt)
{
    string value;
    cout << prompt;
    cin.ignore();
    getline(cin, value);
    return value;
}

// Function to get information from the user for a new registration
void getRegistrationInfo(RegistrationNode* registration)
{
    cout << "Please enter the vehicle owner's name: ";
    registration->vehicleOwner = getStringInput("");

    cout << "Please enter the IC number: ";
    registration->icNumber = getUserInput<string>("");

    cout << "Please enter the vehicle type: ";
    registration->vehicleType = getStringInput("");

    cout << "Please enter the plate number: ";
    registration->plateNumber = getUserInput<string>("");

    cout << "Please enter the engine number: ";
    registration->engineNumber = getUserInput<string>("");

    cout << "Please enter the license number: ";
    registration->licenseNumber = getUserInput<string>("");

    cout << "Please enter the license expiry date: ";
    registration->licenseExpiryDate = getUserInput<string>("");

    cout << "Please enter the insurance company: ";
    registration->insuranceCompany = getStringInput("");

    cout << "Please enter the policy number: ";
    registration->policyNumber = getUserInput<string>("");

    cout << "Please enter the insurance expiry date: ";
    registration->insuranceExpiryDate = getUserInput<string>("");

    // Set default values for other attributes
    registration->status = "processing";
    registration->stickerExpiryDate = "Registration in process";
}

// Function to print registration information
void printRegistrationInfo(RegistrationNode* registration)
{
    cout << "Vehicle Owner        : " << registration->vehicleOwner << endl;
    cout << "IC Number            : " << registration->icNumber << endl;
    cout << "Vehicle Type         : " << registration->vehicleType << endl;
    cout << "Plate Number         : " << registration->plateNumber << endl;
    cout << "Engine Number        : " << registration->engineNumber << endl;
    cout << "License Number       : " << registration->licenseNumber << endl;
    cout << "License Expiry Date  : " << registration->licenseExpiryDate << endl;
    cout << "Insurance Company    : " << registration->insuranceCompany << endl;
    cout << "Policy Number        : " << registration->policyNumber << endl;
    cout << "Insurance Expiry Date: " << registration->insuranceExpiryDate << endl;
    cout << "Registration Status  : " << registration->status << endl;
    if (registration->status == "rejected")
    {
        cout << "Reason for Rejection : " << registration->reasonForRejection << endl;
    }
    cout << "Sticker Expiry Date  : " << registration->stickerExpiryDate << endl;
}

class Student;

class User
{
    public:
        string userID;
        string password;
        virtual bool isValid() = 0;
};

class Admin : public User
{
    private:
        Queue processingQueue;
        string reasonForRejection;

    public:
        Admin() : processingQueue() {}
        void handleRegistration(Student* student);
        void writeToFile(const string& file);
        void readFromFile(const string& file) ;
        Queue* getProcessingQueue() 
        { 
            return &processingQueue;
        }
        bool isValid() override
        {
            return (userID == "admin001" && password == "tiffany123");
        }
};

class Student : public User
{
    private:
        List studentRecords;
        Queue allRegistrations;

    public:
        Student() : studentRecords() {}
        void applyForSticker(Admin& admin);
        void checkStatus(string m);
        void renewSticker(Admin& admin);
        void writeToFile(const string& file);
        void readFromFile(const string& file);
        bool isValid() override
        {
            return studentRecords.isValid(userID, password);
        }
        void addRecord(string m, string p)
        {
            studentRecords.addStudent(m, p);
        }
        Queue* getAllRegistrations()
        {
            return &allRegistrations;
        }
};

void Admin::handleRegistration(Student* student)
{
    while(!processingQueue.isEmpty())
    {
        RegistrationNode* registration = processingQueue.getFront();
        cout << "\nRegistration Information: " << endl;
        cout << "Matric Number        : " << registration->matricNumber << endl;
        printRegistrationInfo(registration);

        int choice;
        string reasonForRejection;
        cout << "\n1. Approve" << endl;
        cout << "2. Reject" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
                registration->status = "approved";
                registration->stickerExpiryDate = "2024-12-31";
                cout << "Registration approved." << endl;
                break;
            case 2:
                cout << "Enter reason for rejection: ";
                cin.ignore();
                getline(cin, reasonForRejection);
                registration->status = "rejected";
                registration->reasonForRejection = reasonForRejection;
                registration->stickerExpiryDate = "Registration is rejected";
                cout << "Registration rejected." << endl;
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        registration->isHandled = true;
        processingQueue.deQueue();
    } 
     
    student->writeToFile("registrationFile.txt");
    writeToFile("processingQueue.txt");
    cout << "No registrations to process." << endl;
}

void Admin::writeToFile(const string& processingFile)
{
    ofstream outfile(processingFile);
    if(!outfile)
    {
        cout << "Unable to open processing file for writing." << endl;
        return;
    }

    RegistrationNode* current = processingQueue.getFront();
    while (current != NULL)
    {
        outfile << current->matricNumber << endl;
        outfile << current->vehicleOwner << endl;
        outfile << current->icNumber << endl;
        outfile << current->vehicleType << endl;
        outfile << current->plateNumber << endl;
        outfile << current->engineNumber << endl;
        outfile << current->licenseNumber << endl;
        outfile << current->licenseExpiryDate << endl;
        outfile << current->insuranceCompany << endl;
        outfile << current->policyNumber << endl;
        outfile << current->insuranceExpiryDate << endl;
        outfile << current->status << endl;
        if(current->status == "rejected")
        {
            outfile << current->reasonForRejection << endl;
        }
        outfile << current->stickerExpiryDate << endl;

        current = current->next;
    }

    outfile.close();
}

void Admin::readFromFile(const string& processingFile)
{
    ifstream infile(processingFile);
    if (!infile)
    {
        cout << "Unable to open processing file for reading." << endl;
        return;
    }

    string line;
    while (getline(infile, line))
    {
        RegistrationNode* newRegistration = new RegistrationNode();
        newRegistration->matricNumber = line;

        getline(infile, line);
        newRegistration->vehicleOwner = line;

        getline(infile, line);
        newRegistration->icNumber = line;

        getline(infile, line);
        newRegistration->vehicleType = line;
        
        getline(infile, line);
        newRegistration->plateNumber = line;
        
        getline(infile, line);
        newRegistration->engineNumber = line;
        
        getline(infile, line);
        newRegistration->licenseNumber = line;
        
        getline(infile, line);
        newRegistration->licenseExpiryDate = line;

        getline(infile, line);
        newRegistration->insuranceCompany = line;
        
        getline(infile, line);
        newRegistration->policyNumber = line;
        
        getline(infile, line);
        newRegistration->insuranceExpiryDate = line;
        
        getline(infile, line);
        newRegistration->status = line;
        
        if(newRegistration->status == "rejected")
        {
            getline(infile, line);
            newRegistration->reasonForRejection = line;
        }
        
        getline(infile, line);
        newRegistration->stickerExpiryDate = line;

        processingQueue.enQueue(newRegistration);
    }

    infile.close();
}

void Student::applyForSticker(Admin& admin)
{
    RegistrationNode *current = allRegistrations.getFront();
    RegistrationNode *latestRegistration = NULL;
    while(current != NULL)
    {
        if(current->matricNumber == this->userID)
        {
            latestRegistration = current;
        }
        current = current->next;
    }
    if(latestRegistration != NULL)
    {
        if(latestRegistration->status != "rejected")
        {
            //if student already have a registration and is not rejected, cannot apply again
            cout << "You already have a registration record. You cannot apply for a new sticker." << endl;
            return;
        }
        else
        {
            //If student's registration is rejected, can apply again
            RegistrationNode* newRegistration = new RegistrationNode();
            newRegistration->matricNumber = this->userID;
                
            cout << "Your previous registration was rejected. Please fill in the information again. " << endl;
            getRegistrationInfo(newRegistration);
                
            allRegistrations.enQueue(newRegistration);
            admin.getProcessingQueue()->enQueue(newRegistration);
            cout << "Sticker application submitted successfully." << endl;

            writeToFile("registrationFile.txt");
            admin.writeToFile("processingQueue.txt");
            return;
        }
    }

    //If no existing registration, create a new one
    RegistrationNode* newRegistration = new RegistrationNode();
    newRegistration->matricNumber = this->userID;

    getRegistrationInfo(newRegistration);
    allRegistrations.enQueue(newRegistration);
    admin.getProcessingQueue()->enQueue(newRegistration);

    cout << "Sticker application submitted successfully." << endl;

    writeToFile("registrationFile.txt");
    admin.writeToFile("processingQueue.txt");
}

void Student::checkStatus(string matricNumber)
{
    if(allRegistrations.isEmpty())
    {
        cout << "No record." << endl;
    }
    else
    {
        //Find the latest record of student's registration to display latest status
        RegistrationNode *current = allRegistrations.getFront();
        RegistrationNode *latestRegistration = NULL;
        while(current != NULL)
        {
            if(current->matricNumber == matricNumber)
            {
                latestRegistration = current;
            }
            current = current->next;
        }

        if(latestRegistration != NULL)
        {
            cout << endl;
            printRegistrationInfo(latestRegistration);
        }
        else
        {
            cout << "No record." << endl;
        }
    }
}

void Student::renewSticker(Admin& admin)
{
    if(allRegistrations.isEmpty())
    {
        cout << "No record." << endl;
    }
    else
    {
        //Find the latest record of student's registration to check whether the sticker is expired
    	RegistrationNode *current = allRegistrations.getFront();
        RegistrationNode *latestRegistration = NULL;
        while(current != NULL)
        {
            if(current->matricNumber == this->userID)
            {
                latestRegistration = current;
            }
            current = current->next;
        }
        if(latestRegistration != NULL)
        {
            if(latestRegistration->stickerExpiryDate < "2024-01-01" && latestRegistration->status != "processing" )
            {
                RegistrationNode* newRegistration = new RegistrationNode();
				newRegistration->matricNumber = this->userID;
					
                cout << "\nSticker is expired. Please fill in the information again." << endl;
                getRegistrationInfo(newRegistration);
					
				allRegistrations.enQueue(newRegistration);
				admin.getProcessingQueue()->enQueue(newRegistration);
                cout << "Sticker renewal request submitted successfully." << endl;

                writeToFile("registrationFile.txt");
                admin.writeToFile("processingQueue.txt");
            }
            else if(latestRegistration->status == "processing")
            {
                cout << "Registration is processing." << endl;
            }
            else
            {
                cout << "Sticker is not expired." << endl;
            }
            return;
        }
        else
        {
        	cout << "No record." << endl;
		}
    }
}

void  Student::writeToFile(const string& registrationFile)
{
    ofstream outfile(registrationFile);
    if(!outfile)
    {
        cout << "Unable to open registration file for writing." << endl;
        return;
    }

    RegistrationNode* current = allRegistrations.getFront();
    while (current != NULL)
    {
        outfile << current->matricNumber << endl;
        outfile << current->vehicleOwner << endl;
        outfile << current->icNumber << endl;
        outfile << current->vehicleType << endl;
        outfile << current->plateNumber << endl;
        outfile << current->engineNumber << endl;
        outfile << current->licenseNumber << endl;
        outfile << current->licenseExpiryDate << endl;
        outfile << current->insuranceCompany << endl;
        outfile << current->policyNumber << endl;
        outfile << current->insuranceExpiryDate << endl;
        outfile << current->status << endl;
        if(current->status == "rejected")
        {
            outfile << current->reasonForRejection << endl;
        }
        outfile << current->stickerExpiryDate << endl;

        current = current->next;
    }

    outfile.close();
}

void Student::readFromFile(const string& registrationFile)
{
    ifstream infile(registrationFile);
    if (!infile)
    {
        cout << "Unable to open registration file for reading." << endl;
        return;
    }

    string line;
    while (getline(infile, line))
    {
        RegistrationNode* newRegistration = new RegistrationNode();
        newRegistration->matricNumber = line;

        getline(infile, line);
        newRegistration->vehicleOwner = line;

        getline(infile, line);
        newRegistration->icNumber = line;

        getline(infile, line);
        newRegistration->vehicleType = line;
        
        getline(infile, line);
        newRegistration->plateNumber = line;
        
        getline(infile, line);
        newRegistration->engineNumber = line;
        
        getline(infile, line);
        newRegistration->licenseNumber = line;
        
        getline(infile, line);
        newRegistration->licenseExpiryDate = line;

        getline(infile, line);
        newRegistration->insuranceCompany = line;
        
        getline(infile, line);
        newRegistration->policyNumber = line;
        
        getline(infile, line);
        newRegistration->insuranceExpiryDate = line;
        
        getline(infile, line);
        newRegistration->status = line;
        
        if(newRegistration->status == "rejected")
        {
            getline(infile, line);
            newRegistration->reasonForRejection = line;
        }
        
        getline(infile, line);
        newRegistration->stickerExpiryDate = line;

        allRegistrations.enQueue(newRegistration);
    }

    infile.close();
}

void studentMenu(Student& student, string matricNumber, Admin& admin)
{
    int choice;

    while (true)
    {
        cout << "\n== Student Menu ==" << endl;
        cout << "1. Apply for sticker" << endl;
        cout << "2. Check status" << endl;
        cout << "3. Renew sticker" << endl;
        cout << "4. Logout" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                student.applyForSticker(admin);
                break;
            case 2:
                student.checkStatus(matricNumber);
                break;
            case 3:
                student.renewSticker(admin);
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void studentLoginMenu(Student& student, Admin& admin)
{
    string matricNumber, password;

    cout << "\n== Student Login Menu ==" << endl;
    cout << "Please enter your matric number: ";
    cin >> matricNumber;
    cout << "Please enter your password: ";
    cin >> password;

    student.userID = matricNumber;
    student.password = password;

    if (student.isValid())
    {
        cout << "Login successful." << endl;
        studentMenu(student, matricNumber, admin);
    }
    else 
    {
        cout << "Login failed." << endl;
    }
}

void adminMenu(Admin& admin, Student& student)
{
    int choice;

    while (true)
    {
        cout << "\n== Admin Menu ==" << endl;
        cout << "1. Handle registration" << endl;
        cout << "2. Logout" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                admin.handleRegistration(&student);
                break;
            case 2:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void adminLoginMenu(Admin& admin, Student& student)
{
    string adminID, password;

    cout << "\n== Admin Login Menu ==" << endl;
    cout << "Please enter your admin ID: ";
    cin >> adminID;
    cout << "Please enter your password: ";
    cin >> password;

    admin.userID = adminID;
    admin.password = password;

    if (admin.isValid())
    {
        cout << "Login successful." << endl;
        adminMenu(admin, student);
    }
    else
    {
        cout << "Login failed." << endl;
    }
}

void mainMenu(Student& student, Admin& admin)
{
    int choice;

    while (true)
    {
        cout << "\nWelcome to the Vehicle Registration System!" << endl << endl;
        cout << "1. Student" << endl;
        cout << "2. Admin" << endl;
        cout << "3. Exit" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                studentLoginMenu(student, admin);
                break;
            case 2:
                adminLoginMenu(admin, student);
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main()
{
    Admin admin;
    admin.userID = "admin001";
    admin.password = "tiffany123";

    admin.readFromFile("processingQueue.txt");

    // Create a Student object with the student records
    Student inputStudent;
    inputStudent.addRecord("A22EC0025", "lim0406");
    inputStudent.addRecord("A22EC0047", "wong0516");
    inputStudent.readFromFile("registrationFile.txt");

    RegistrationNode* oldRegistration = new RegistrationNode();
    oldRegistration->matricNumber = "A22EC0025";
    oldRegistration->vehicleOwner = "Lim Ah Meng";
    oldRegistration->icNumber = "123456017899";
    oldRegistration->vehicleType = "Myvi";
    oldRegistration->plateNumber = "2345";
    oldRegistration->engineNumber = "6G72-MIVEC";
    oldRegistration->licenseNumber = "B1234567";
    oldRegistration->licenseExpiryDate = "2027-12-31";
    oldRegistration->insuranceCompany = "Allianz";
    oldRegistration->policyNumber = "AXA-1234567";
    oldRegistration->insuranceExpiryDate = "2029-12-31";
    oldRegistration->status = "approved";
    oldRegistration->stickerExpiryDate = "2023-12-31"; 

    ifstream infile("registrationFile.txt");
    string line;
    if (!getline(infile, line)) 
    {
        inputStudent.getAllRegistrations()->enQueue(oldRegistration);
    }
    infile.close();

    inputStudent.writeToFile("registrationFile.txt");
    admin.writeToFile("processingQueue.txt");

    mainMenu(inputStudent, admin);

    return 0;
}
