#include <stdio.h>
#include <string.h>
#define MAX_ROOMS 20
#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 50
#define MAX_SPECIALTY_LENGTH 50
#define MAX_AMBULANCES 5


//for login
typedef struct User {
    char username[30];
    char password[30];
} User;



// Patient structure
typedef struct {
    int id;
    char name[100];
    char gender[10];
    int age;
    char blood[10];
    char disease[100];
    int roomAssigned;
    float deposit;  // Total deposit amount required for the room
    float amountPaid;  // Amount paid so far by the patient
} Patient;

Patient patients[100];
int patientCount = 0;



typedef struct {
    int id;
    char name[100];
    char role[50];
    char specialty[50];
} Employee;

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;





typedef struct {
    int roomNo;
    char availability[10];
    float roomCost;
    char description[20];
} Room;


typedef struct {
    int id;
    char licensePlate[15];
    char status[20];
} Ambulance;


const char *specialties[] = {
    "General Practitioner",
    "Cardiologist",
    "Dermatologist",
    "Neurologist",
    "Orthopedic",
    "Pediatrician",
    "Psychiatrist",
    "Radiologist",
    "Surgeon"
};



Room rooms[MAX_ROOMS] = {
    {100, "Available", 500, "G Bed 1"},
    {101, "Available", 500, "G Bed 2"},
    {102, "Available", 500, "G Bed 3"},
    {103, "Available", 500, "G Bed 4"},
    {200, "Available", 1500, "Private Room"},
    {201, "Available", 1500, "Private Room"},
    {202, "Available", 1500, "Private Room"},
    {300, "Available", 3500, "ICU Bed 1"},
    {301, "Available", 3500, "ICU Bed 2"},
    {302, "Occupied", 3500, "ICU Bed 3"},
    {303, "Available", 3500, "ICU Bed 4"},
    {304, "Available", 3500, "ICU Bed 5"},
    {305, "Available", 3500, "ICU Bed 6"},
    // Add more rooms as needed
};


int specialtyCount = sizeof(specialties) / sizeof(specialties[0]);

Ambulance ambulances[MAX_AMBULANCES] = {
    {1, "ABC123", "Available"},
    {2, "XYZ456", "Available"},
    {3, "LMN789", "Available"},
    {4, "PQR012", "Available"},
    {5, "STU345", "Available"}
};




// Functions
void signup();
int login();
void addPatient();
void viewPatients();
void updatePatient();
void dischargePatient();
void addEmployee();
void viewEmployees();
void searchPatients();
void sortPatients();
void searchRooms();
void viewAmbulances();
void bookAmbulance();
void completeAmBulanceDuty();
int main() {
    int choice;
    login();
    // Main menu
    while (1) {
        printf("\n1. Add Patient\n2. View Patients\n3. Update Patient\n4. Discharge Patient\n");
        printf("5. Add Employee\n6. View Employees\n");
        printf("7. Search Patients\n8. Sort Patients\n9. Search Rooms\n");
        printf("10. View Ambulances\n11. Book Ambulance\n12. Complete Duty\n");
        printf("13. Logout\n");
        printf("Enter Choice : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: updatePatient(); break;
            case 4: dischargePatient(); break;
            case 5: addEmployee(); break;
            case 6: viewEmployees(); break;
            case 7: searchPatients(); break;
            case 8: sortPatients(); break;
            case 9: searchRooms();break;
            case 10: viewAmbulances();break;
            case 11:bookAmbulance();break;
            case 12: completeAmBulanceDuty();break;
            case 13: return 0;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}


int login() {
    char username[30], password[30];

    while (1) {
        printf("\n=============================\n");
        printf("         LOGIN PANEL         \n");
        printf("=============================\n");

        printf("Enter username: ");
        scanf(" %[^\n]", username);
        printf("Enter password: ");
        scanf(" %[^\n]", password);

        if ((strcmp(username, "admin") == 0)) {
            if (strcmp(password, "admin") == 0) {
                printf("\n=============================\n");
                printf("   Login successful. Welcome! \n");
                printf("=============================\n");
                return 1;
            } else {
                printf("\nInvalid password. Try again.\n");
            }
        } else {
            printf("\nInvalid username. Try again.\n");
        }
    }
}

void displayAvailableRooms() {
    printf("Available Rooms:\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (strcmp(rooms[i].availability, "Available") == 0) {
            printf("Room No: %d, Cost: %.2f, Description: %s\n", rooms[i].roomNo, rooms[i].roomCost, rooms[i].description);
        }
    }
}


void addPatient() {
    Patient newPatient;
    printf("Enter patient ID: ");
    scanf("%d", &newPatient.id);

    getchar();

    printf("Enter name: ");
    scanf(" %[^\n]", newPatient.name);

    printf("Enter gender: ");
    scanf(" %[^\n]", newPatient.gender);

    printf("Enter age: ");
    scanf("%d", &newPatient.age);

    getchar();

    printf("Enter Blood Group: ");
    scanf(" %[^\n]", newPatient.blood);

    printf("Enter disease: ");
    scanf(" %[^\n]", newPatient.disease);

    displayAvailableRooms();

    int selectedRoom;
    int roomFound = 0;

    while (!roomFound) {
        printf("Select Room Number from the available list: ");
        scanf("%d", &selectedRoom);

        // Checking if the selected room is available or nottt
        for (int i = 0; i < MAX_ROOMS; i++) {
            if (rooms[i].roomNo == selectedRoom && strcmp(rooms[i].availability, "Available") == 0) {
                strcpy(rooms[i].availability, "Occupied");
                newPatient.roomAssigned = rooms[i].roomNo;
                roomFound = 1;

                // SeTing thee deposit
                printf("Enter deposit for the room (%.2f required): ", rooms[i].roomCost);
                scanf("%f", &newPatient.amountPaid);

                if (newPatient.deposit < rooms[i].roomCost) {
                    printf("Partial deposit accepted.\nRemaining: %.2f\n", rooms[i].roomCost - newPatient.amountPaid);
                }
                newPatient.deposit = rooms[i].roomCost;
                break;
            }
        }

        if (!roomFound) {
            printf("Invalid room selection or room already occupied. Please try again.\n");
        }
    }

    patients[patientCount++] = newPatient;
    printf("Patient added successfully. Room %d assigned.\n", newPatient.roomAssigned);
}





void updatePatient() {
    int id;
    printf("Enter patient ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            float remainingDeposit = patients[i].deposit - patients[i].amountPaid;
            printf("Remaining deposit to pay: %f\n", remainingDeposit);

            // Updatinggg the deposit amount if there is a remaining balance
            float additionalPayment = 0;
            if (remainingDeposit > 0) {
                printf("Enter amount to pay towards deposit: ");
                scanf("%f", &additionalPayment);
                patients[i].amountPaid += additionalPayment;

                if (patients[i].amountPaid >= patients[i].deposit) {
                    patients[i].deposit=0;
                    printf("Deposit fully paid.\n");
                } else {
                    printf("Remaining balance after payment: %f\n", patients[i].deposit - patients[i].amountPaid);
                }
            } else {
                printf("Deposit has already been fully paid.\n");
            }
        }
    }

    printf("Patient not found.\n");
}



void dischargePatient() {
    int id;
    printf("Enter patient ID to discharge: ");
    scanf("%d", &id);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            // Check if the deposit is fully paid
            if (patients[i].amountPaid < patients[i].deposit) {
                printf("Cannot discharge patient. Remaining deposit not fully paid: %f\n",
                       patients[i].deposit - patients[i].amountPaid);
                return;  // Prevent discharge if deposit isn't fully paid
            }

            // Markinggg the patients room as availab
            for (int j = 0; j < MAX_ROOMS; j++) {
                if (rooms[j].roomNo == patients[i].roomAssigned) {
                    strcpy(rooms[j].availability, "Available");
                    break;
                }
            }

            // Shiftingg remaining patientss in the array to fill the gaps
            for (int j = i; j < patientCount - 1; j++) {
                patients[j] = patients[j + 1];
            }

            patientCount--;
            printf("Patient discharged successfully.\n");
            return;
        }
    }

    printf("Patient not found.\n");
}



void viewPatients() {
    if (patientCount == 0) {
        printf("No patients are currently added.\n");
        return;
    }

    printf("==================================================================================================\n");
    printf("| %-3s | %-15s | %-6s | %-3s | %-10s | %-12s | %-7s | %-8s | %-7s |\n",
           "ID", "Name", "Gender", "Age", "Blood", "Disease", "Room", "Deposit", "Paid");
    printf("===================================================================================================\n");

    for (int i = 0; i < patientCount; i++) {
        float roomCost = 0.0;

        // Finding t the room cost based on the assigned rooms
        for (int j = 0; j < MAX_ROOMS; j++) {
            if (rooms[j].roomNo == patients[i].roomAssigned) {
                roomCost = rooms[j].roomCost;
                break;
            }
        }

        printf("| %-3d | %-15s | %-6s | %-3d | %-10s | %-12s | %-7d | %-8.2f | %-7.2f |\n",
               patients[i].id,
               patients[i].name,
               patients[i].gender,
               patients[i].age,
               patients[i].blood,
               patients[i].disease,
               patients[i].roomAssigned,
               roomCost,    // Total deposit required for the room
               patients[i].amountPaid);  // Amount paid by the patient
    }

    printf("===================================================================================================\n");
}








void displaySpecialties() {
    printf("Available Specialties:\n");
    for (int i = 0; i < specialtyCount; i++) {
        printf("%d. %s\n", i + 1, specialties[i]);
    }
}

void addEmployee() {
    Employee newEmployee;
    printf("Enter employee ID: ");
    scanf("%d", &newEmployee.id);

    getchar();
    printf("Enter employee name: ");
    scanf(" %[^\n]", newEmployee.name);

    int roleChoice;
    while (1) {
        printf("Select role:\n1. Doctor\n2. Nurse\n3. Other\n");
        scanf("%d", &roleChoice);
        if (roleChoice == 1) {
            strcpy(newEmployee.role, "Doctor");
            int specialtyChoice;
            while (1) {
                displaySpecialties();
                printf("Select specialty by number: ");
                scanf("%d", &specialtyChoice);
                if (specialtyChoice > 0 && specialtyChoice <= specialtyCount) {
                    strcpy(newEmployee.specialty, specialties[specialtyChoice - 1]);
                    break;
                } else {
                    printf("Invalid specialty choice. Please try again.\n");
                }
            }
            break;
        } else if (roleChoice == 2) {
            strcpy(newEmployee.role, "Nurse");
            break;
        } else if (roleChoice == 3) {
            strcpy(newEmployee.role, "Other");
            break;
        } else {
            printf("Invalid role choice. Please try again.\n");
        }
    }

    employees[employeeCount++] = newEmployee;
    printf("Employee added successfully.\n");
}


void viewEmployees() {
    printf("\nList of Employees:\n");
    printf("----------------------------\n");
    for (int i = 0; i < employeeCount; i++) {
        printf("ID: %d\n", employees[i].id);
        printf("Name: %s\n", employees[i].name);
        printf("Role: %s\n", employees[i].role);
        if (strcmp(employees[i].role, "Doctor") == 0) {
            printf("Specialty: %s\n", employees[i].specialty);
        }
        printf("----------------------------\n");
    }
}



void searchPatients() {
    int choice;

    while (1) {
        printf("Search by:\n1. ID\n2. Name\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // Search by ID
            int searchID;
            printf("Enter patient ID to search: ");
            scanf("%d", &searchID);
            int found = 0;

            for (int i = 0; i < patientCount; i++) {
                if (patients[i].id == searchID) {
                    found = 1;
                    // Display patient details
                    printf("Patient Found:\n");
                    printf("ID: %d\n", patients[i].id);
                    printf("Name: %s\n", patients[i].name);
                    printf("Age: %d\n", patients[i].age);
                    printf("Gender: %s\n", patients[i].gender);
                    printf("Blood Group: %s\n", patients[i].blood);
                    printf("Disease: %s\n", patients[i].disease);
                    printf("Room Assigned: %d\n", patients[i].roomAssigned);
                    printf("Deposit Required: %.2f\n", patients[i].deposit);
                    printf("Amount Paid: %.2f\n", patients[i].amountPaid);

                    if (patients[i].amountPaid < patients[i].deposit) {
                        printf("Remaining Deposit: %.2f\n", patients[i].deposit - patients[i].amountPaid);
                    }
                    break;
                }
            }
            if (!found) {
                printf("Patient with ID %d not found.\n", searchID);
            }
            break;

        } else if (choice == 2) {
            // Search by Name
            char searchName[30];
            printf("Enter patient name to search: ");
            scanf(" %[^\n]", searchName);
            int found = 0;

            for (int i = 0; i < patientCount; i++) {
                if (strcmp(patients[i].name, searchName) == 0) {
                    found = 1;
                    // Display patient details
                    printf("Patient Found:\n");
                    printf("ID: %d\n", patients[i].id);
                    printf("Name: %s\n", patients[i].name);
                    printf("Age: %d\n", patients[i].age);
                    printf("Gender: %s\n", patients[i].gender);
                    printf("Blood Group: %s\n", patients[i].blood);
                    printf("Disease: %s\n", patients[i].disease);
                    printf("Room Assigned: %d\n", patients[i].roomAssigned);
                    printf("Deposit Required: %.2f\n", patients[i].deposit);
                    printf("Amount Paid: %.2f\n", patients[i].amountPaid);

                    if (patients[i].amountPaid < patients[i].deposit) {
                        printf("Remaining Deposit: %.2f\n", patients[i].deposit - patients[i].amountPaid);
                    }
                    break;
                }
            }
            if (!found) {
                printf("Patient with name '%s' not found.\n", searchName);
            }
            break;

        } else {
            printf("Invalid choice. Please enter 1 or 2.\n");
        }
    }
}




void sortPatients() {
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (patients[j].id > patients[j + 1].id) {
                Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }

    printf("Patients sorted by name.\n");

    printf("Sorted List of Patients:\n");
    for (int i = 0; i < patientCount; i++) {
        printf("ID: %d, Name: %s, Age: %d, Gender: %s, Disease: %s, Room No: %d, Deposit: %.2f, Paid: %.2f\n",
               patients[i].id,
               patients[i].name,
               patients[i].age,
               patients[i].gender,
               patients[i].disease,
               patients[i].roomAssigned,
               patients[i].deposit,
               patients[i].amountPaid);
    }
}

void searchRooms() {
    int choice;
    printf("Search for rooms:\n");
    printf("1. Available Rooms\n");
    printf("2. Occupied Rooms\n");
    printf("Select option (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Display Available Rooms
        printf("\nAvailable Rooms:\n");
        for (int i = 0; i < MAX_ROOMS; i++) {
            if (strcmp(rooms[i].availability, "Available") == 0) {
                printf("Room No: %d, Cost: %.2f, Description: %s\n", rooms[i].roomNo, rooms[i].roomCost, rooms[i].description);
            }
        }
    } else if (choice == 2) {
        // Display Occupied Rooms
        printf("\nOccupied Rooms:\n");
        for (int i = 0; i < MAX_ROOMS; i++) {
            if (strcmp(rooms[i].availability, "Occupied") == 0) {
                printf("Room No: %d, Cost: %.2f, Description: %s\n", rooms[i].roomNo, rooms[i].roomCost, rooms[i].description);
            }
        }
    } else {
        printf("Invalid choice. Please select either 1 or 2.\n");
    }
}


void viewAmbulances() {
    printf("Ambulance List:\n");
    for (int i = 0; i < MAX_AMBULANCES; i++) {
        printf("ID: %d, License Plate: %s, Status: %s\n",
                ambulances[i].id,
                ambulances[i].licensePlate,
                ambulances[i].status);
    }
}

void bookAmbulance() {
    viewAmbulances();

    int selectedID;
    printf("Enter the ID of the ambulance you want to book: ");
    scanf("%d", &selectedID);

    for (int i = 0; i < MAX_AMBULANCES; i++) {
        if (ambulances[i].id == selectedID) {
            if (strcmp(ambulances[i].status, "Available") == 0) {
                strcpy(ambulances[i].status, "On Duty");
                printf("Ambulance %s booked successfully.\n", ambulances[i].licensePlate);
                return;
            } else {
                printf("Ambulance %s is already on duty.\n", ambulances[i].licensePlate);
                return;
            }
        }
    }
    printf("Ambulance with ID %d not found.\n", selectedID);
}

void completeAmBulanceDuty(){

    viewAmbulances();

    int selectedID;
    printf("Enter the ID of the ambulance you want to mark as available: ");
    scanf("%d", &selectedID);

    for (int i = 0; i < MAX_AMBULANCES; i++) {
        if (ambulances[i].id == selectedID) {
            if (strcmp(ambulances[i].status, "On Duty") == 0) {
                strcpy(ambulances[i].status, "Available");
                printf("Ambulance %s is now available again.\n", ambulances[i].licensePlate);
                return;
            } else {
                printf("Ambulance %s is already available.\n", ambulances[i].licensePlate);
                return;
            }
        }
    }
    printf("Ambulance with ID %d not found.\n", selectedID);
}
