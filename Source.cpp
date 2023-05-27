#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct Resident {
    string name;
    int age;
};

struct Flat {
    int id;
    int floor;
    int type;
    Resident* resident;
};

struct House {
    Flat* flats;
    int numFlats;
};

void addFlat(House& house, int id, int floor, int type);
void deleteFlat(House& house, int id);
void addResident(House& house, int flatId, string name, int age);
void removeResident(House& house, int flatId);
void displayAllResidents(const House& house);
void displayAllFlats(const House& house);
void displayFlat(const House& house, int id);
void displayFlatsOnFloor(const House& house, int floor);
void displayFlatsByType(const House& house, int type);
void saveHouseToFile(const House& house, const string& filename);
bool loadHouseFromFile(House& house, const string& filename);
void animateText(const string& text);



void main() {
    setlocale(LC_ALL, "Russian");

    House house;
    house.numFlats = 0;
    house.flats = nullptr;
  
    int choice, flatId, id, floor, age, type;
    string name;
    bool exit = false;

    string filename = "house_data.txt";

    bool loadSuccess = loadHouseFromFile(house, filename);
    if (!loadSuccess) {
        /*    cout << "Failed to load house data from file." << endl;*/
    }

    string greeting = "Hello, welcome to the ""Housing Management"" program";
    animateText(greeting);

    while (!exit) {
        cout << "---------------------------------------------" << endl;
        cout << "1. Add apartment" << endl;
        cout << "2. Delete apartment" << endl;
        cout << "3. Add tenant" << endl;
        cout << "4. Delete tenant" << endl;
        cout << "5. Show all tenants" << endl;
        cout << "6. Show all apartments" << endl;
        cout << "7. Show information about the apartment" << endl;
        cout << "8. Show information about apartments per floor" << endl;
        cout << "9. Show information about apartments of a certain type" << endl;
        cout << "0. Exit the program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            cout << "Enter apartment number: ";
            cin >> id;
            cout << "Enter floor: ";
            cin >> floor;
            cout << "Enter apartment type: ";
            cin >> type;
            addFlat(house, id, floor, type);
            saveHouseToFile(house, filename);
            break;

        case 2:
            system("cls");
            cout << "Enter apartment number: ";
            cin >> id;
            deleteFlat(house, id);
            saveHouseToFile(house, filename);
            break;

        case 3:
            system("cls");
            cout << "Enter apartment number: ";
            cin >> flatId;
            cout << "Enter tenant name: ";
            cin >> name;
            cout << "Enter the tenant's age: ";
            cin >> age;
            addResident(house, flatId, name, age);
            saveHouseToFile(house, filename);
            break;

        case 4:
            system("cls");
            cout << "Enter apartment number: ";
            cin >> flatId;
            removeResident(house, flatId);
            saveHouseToFile(house, filename);
            break;

        case 5:
            system("cls");
            displayAllResidents(house);
            break;

        case 6:
            system("cls");
            displayAllFlats(house);
            break;

        case 7:
            system("cls");
            cout << "Enter apartment number: ";
            cin >> id;
            displayFlat(house, id);
            break;

        case 8:
            system("cls");
            cout << "Enter floor: ";
            cin >> floor;
            displayFlatsOnFloor(house, floor);
            break;

        case 9:
            system("cls");
            cout << "Enter apartment type: ";
            cin >> type;
            displayFlatsByType(house, type);
            break;

        case 0:
            exit = true;
            break;

        default:
            cout << "Wrong choice" << endl;
            break;
        }
    }

    // Зберігаємо дані у файлі перед закриттям програми
    saveHouseToFile(house, filename);

    // Звільняємо пам'ять
    for (int i = 0; i < house.numFlats; i++) {
        delete house.flats[i].resident;
    }
    delete[] house.flats;
    house.flats = nullptr;


}
void animateText(const string& text) {
    for (int i = 0; i < text.length(); i++) {
        system("cls");

        for (int j = 0; j < i; j++) {
            cout << " ";
        }

        cout << text << endl;

        Sleep(100);
    }
}

void addFlat(House& house, int id, int floor, int type) {
    for (int i = 0; i < house.numFlats; i++) {
        if (house.flats[i].id == id) {
            cout << "Apartment with the same number already exists." << endl;
            return;
        }
    }

    Flat* newFlat = new Flat;
    newFlat->id = id;
    newFlat->floor = floor;
    newFlat->type = type;
    newFlat->resident = nullptr;

    int numFlats = house.numFlats;
    Flat* flats = new Flat[numFlats + 1];
    for (int i = 0; i < numFlats; i++) {
        flats[i] = house.flats[i];
    }
    flats[numFlats] = *newFlat;
    delete[] house.flats;
    house.flats = flats;
    house.numFlats++;
}

void deleteFlat(House& house, int id) {
    int numFlats = house.numFlats;
    int index = -1;
    for (int i = 0; i < numFlats; i++) {
        if (house.flats[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Apartment with this number not found" << endl;
        return;
    }


    removeResident(house, id);
    Flat* flats = new Flat[numFlats - 1];
    int j = 0;
    for (int i = 0; i < numFlats; i++) {
        if (i != index) {
            flats[j] = house.flats[i];
            j++;
        }
    }
    delete[] house.flats;
    house.flats = flats;
    house.numFlats--;
}

void addResident(House& house, int flatId, string name, int age) {
    int numFlats = house.numFlats;
    int index = -1;
    for (int i = 0; i < numFlats; i++) {
        if (house.flats[i].id == flatId) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Apartment with this number not found" << endl;
        return;
    }

    Resident* newResident = new Resident;
    newResident->name = name;
    newResident->age = age;

    if (house.flats[index].resident != nullptr) {
        cout << "Apartment already has a resident" << endl;
        return;
    }

    house.flats[index].resident = newResident;
}

void removeResident(House& house, int flatId) {
    int numFlats = house.numFlats;
    int index = -1;
    for (int i = 0; i < numFlats; i++) {
        if (house.flats[i].id == flatId) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Apartment with this number not found" << endl;
        return;
    }

    if (house.flats[index].resident == nullptr) {
        cout << "No resident in this apartment" << endl;
        return;
    }

    delete house.flats[index].resident;
    house.flats[index].resident = nullptr;
}

void displayAllResidents(const House& house) {
    int numFlats = house.numFlats;
    for (int i = 0; i < numFlats; i++) {
        if (house.flats[i].resident != nullptr) {
            cout << "Apartment: " << house.flats[i].id << endl;
            cout << "Resident name: " << house.flats[i].resident->name << endl;
            cout << "Resident age: " << house.flats[i].resident->age << endl;
            cout << "-----------------------" << endl;
        }
    }
}

void displayAllFlats(const House& house) {
    int numFlats = house.numFlats;
    for (int i = 0; i < numFlats; i++) {
        cout << "Apartment: " << house.flats[i].id << endl;
        cout << "Floor: " << house.flats[i].floor << endl;
        cout << "Type: " << house.flats[i].type << endl;
        if (house.flats[i].resident != nullptr) {
            cout << "Resident name: " << house.flats[i].resident->name << endl;
            cout << "Resident age: " << house.flats[i].resident->age << endl;
        }
        else {
            cout << "No resident" << endl;
        }
        cout << "-----------------------" << endl;
    }
}

void displayFlat(const House& house, int id) {
    int numFlats = house.numFlats;
    for (int i = 0; i < numFlats; i++) {
        if (house.flats[i].id == id) {
            cout << "Apartment: " << house.flats[i].id << endl;
            cout << "Floor: " << house.flats[i].floor << endl;
            cout << "Type: " << house.flats[i].type << endl;
            if (house.flats[i].resident != nullptr) {
                cout << "Resident name: " << house.flats[i].resident->name << endl;
                cout << "Resident age: " << house.flats[i].resident->age << endl;
            }
            else {
                cout << "No resident" << endl;
            }
            return;
        }
    }
    cout << "Apartment with this number not found" << endl;
}

void displayFlatsOnFloor(const House& house, int floor) {
    int numFlats = house.numFlats;
    for (int i = 0; i < numFlats; i++) {
        if (house.flats[i].floor == floor) {
            cout << "Apartment: " << house.flats[i].id << endl;
            cout << "Type: " << house.flats[i].type << endl;
            if (house.flats[i].resident != nullptr) {
                cout << "Resident name: " << house.flats[i].resident->name << endl;
                cout << "Resident age: " << house.flats[i].resident->age << endl;
            }
            else {
                cout << "No resident" << endl;
            }
            cout << "-----------------------" << endl;
        }
    }
}

void displayFlatsByType(const House& house, int type) {
    int numFlats = house.numFlats;
    for (int i = 0; i < numFlats; i++) {
        if (house.flats[i].type == type) {
            cout << "Apartment: " << house.flats[i].id << endl;
            cout << "Floor: " << house.flats[i].floor << endl;
            if (house.flats[i].resident != nullptr) {
                cout << "Resident name: " << house.flats[i].resident->name << endl;
                cout << "Resident age: " << house.flats[i].resident->age << endl;
            }
            else {
                cout << "No resident" << endl;
            }
            cout << "-----------------------" << endl;
        }
    }
}

void saveHouseToFile(const House& house, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << house.numFlats << endl;
        for (int i = 0; i < house.numFlats; i++) {
            file << house.flats[i].id << endl;
            file << house.flats[i].floor << endl;
            file << house.flats[i].type << endl;
            if (house.flats[i].resident != nullptr) {
                file << "1" << endl;  // Є житель
                file << house.flats[i].resident->name << endl;
                file << house.flats[i].resident->age << endl;
            }
            else {
                file << "0" << endl;  // Немає жителя
            }
        }
        file.close();
        /*cout << "Data saved to file." << endl;*/
    }
    else {
        cout << "Unable to open file for writing." << endl;
    }
}

bool loadHouseFromFile(House& house, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> house.numFlats;
        house.flats = new Flat[house.numFlats];
        for (int i = 0; i < house.numFlats; i++) {
            file >> house.flats[i].id;
            file >> house.flats[i].floor;
            file >> house.flats[i].type;
            int hasResident;
            file >> hasResident;
            if (hasResident) {
                house.flats[i].resident = new Resident;
                file >> house.flats[i].resident->name;
                file >> house.flats[i].resident->age;
            }
            else {
                house.flats[i].resident = nullptr;
            }
        }
        file.close();
        cout << "Data loaded from file." << endl;
        return true;
    }
    else {
      /*  cout << "Unable to open file for reading." << endl;*/
        return false;
    }
}

