#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <forward_list>
#include <algorithm>
#include <ctime>

using namespace std;

class Car {
public:
    string type;
    string brand;
    string model;
    int year;
    bool rented;

    Car(string t, string b, string m, int y) : type(t), brand(b), model(m), year(y), rented(false) {}
};

class Customer {
private:
    struct BookingNode {
        string booking;
        BookingNode* next;

        BookingNode(const string& b, BookingNode* n = nullptr) : booking(b), next(n) {}
    };

    BookingNode* head;

public:
    string name;
    string contact;

    Customer(string n, string c) : name(n), contact(c), head(nullptr) {}

    void addBooking(const string& booking) {
        if (!head) {
            head = new BookingNode(booking);
        } else {
            BookingNode* newNode = new BookingNode(booking, head);
            head = newNode;
        }
    }

    void displayBookingHistory() const {
        cout << "Booking History:" << endl;
        BookingNode* current = head;
        while (current) {
            cout << current->booking << endl;
            current = current->next;
        }
    }
    
    friend ostream& operator<<(ostream& os, const Customer& customer) {
        os << "Customer Name: " << customer.name << ", Contact: " << customer.contact << endl;
        os << "Booking History:" << endl;
        BookingNode* current = customer.head;
        while (current) {
            os << current->booking << endl;
            current = current->next;
        }
        return os;
    }

    ~Customer() {
        while (head) {
            BookingNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};


class EliteDrive {
private:
    forward_list<Car> availableCars;
    forward_list<Customer> customers; 

public:
    EliteDrive() {
        loadCars();
    }

    void loadCars() {
        ifstream file("cars.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                string type, brand, model;
                int year;
                stringstream ss(line);
                getline(ss, type, ',');
                getline(ss, brand, ',');
                getline(ss, model, ',');
                ss >> year;
                availableCars.emplace_front(type, brand, model, year);
            }
            file.close();
        }
        else {
            cerr << "Unable to open cars.txt" << endl;
        }
    }

    void displayMenu() {
        cout << "Welcome to EliteDrive Car Rental System" << endl << endl;
        cout << "1. Display Available Cars" << endl;
        cout << "2. Rent a Car" << endl;
        cout << "3. Return a Car" << endl;
        cout << "4. Display Customer Information and Booking History" << endl;
        cout << "5. Register New Customer" << endl;
        cout << "6. View Customer Accounts and Booking History" << endl;
        cout << "7. Exit" << endl;
    }

    void displayAvailableCars() {
    cout << "Available Cars:" << endl;
    bool firstCar = true; // Flag to skip the first line
    for (const auto& car : availableCars) {
        if (firstCar) {
            firstCar = false; // Skip the first line
            continue;
        }
        if (car.type == "CarType" && car.brand == "Brand" && car.model == "Model" && car.year == 0) {
            // Skip printing the placeholder line
            continue;
        }
        cout << "Type: " << car.type << ", Brand: " << car.brand << ", Model: " << car.model << ", Year: " << car.year;
        cout << ", Rental Status: " << (car.rented ? "Not Available" : "Available") << endl;
    }
	}

    void rentCar(const string& brand, const string& model, const string& customerName) {
    bool carFound = false;
    for (auto& car : availableCars) {
        if (car.brand == brand && car.model == model && !car.rented) {
            car.rented = true;
            updateCustomerBookingHistory(customerName, brand + " " + model);
            cout << "Car rented successfully." << endl;
            carFound = true;
            break;
        }
    }
    if (!carFound) {
        cout << "Car not available for rent." << endl;
    }
	}

    void returnCar(const string& brand, const string& model, const string& customerName) {
        auto it = find_if(availableCars.begin(), availableCars.end(), [&](const Car& car) {
            return car.brand == brand && car.model == model && car.rented;
            });
        if (it != availableCars.end()) {
            it->rented = false;
            cout << "Car returned successfully." << endl;
        }
        else {
            cout << "Car not found or not rented by " << customerName << "." << endl;
        }
    }

    void displayCustomerInfo(const string& customerName) {
        auto it = find_if(customers.begin(), customers.end(), [&](const Customer& customer) {
            return customer.name == customerName;
            });
        if (it != customers.end()) {
            cout << "Customer Name: " << it->name << ", Contact: " << it->contact << endl;
            it->displayBookingHistory();
        }
        else {
            cout << "Customer not found." << endl;
        }
    }

    void registerCustomer(const string& name, const string& contact) {
        customers.emplace_front(name, contact); 
        cout << "Customer registered successfully." << endl;
    }

    void viewCustomerAccounts() {
    cout << "Customer Accounts and Booking History:" << endl;
    for (const auto& customer : customers) {
        cout << "Customer Name: " << customer.name << ", Contact: " << customer.contact << endl;
        customer.displayBookingHistory();
        cout << endl;
    }
}

    void updateCustomerBookingHistory(const string& customerName, const string& bookingDetails) {
    bool customerFound = false;
    for (auto& customer : customers) {
        if (customer.name == customerName) {
            customer.addBooking(bookingDetails);
            customerFound = true;
            break;
        }
    }
    if (!customerFound) {
        cerr << "Customer not found while updating booking history." << endl;
    }
	}

    void run() {
        int choice;
        do {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
            case 1:
                displayAvailableCars();
                break;
            case 2: {
                string brand, model, customerName;
                cout << "Enter brand and model of the car to rent: ";
                cin >> brand >> model;
                cout << "Enter customer name: ";
                cin >> customerName;
                rentCar(brand, model, customerName);
                break;
            }
            case 3: {
                string brand, model, customerName;
                cout << "Enter brand and model of the car to return: ";
                cin >> brand >> model;
                cout << "Enter customer name: ";
                cin >> customerName;
                returnCar(brand, model, customerName);
                break;
            }
            case 4: {
                string customerName;
                cout << "Enter customer name: ";
                cin >> customerName;
                displayCustomerInfo(customerName);
                break;
            }
            case 5: {
                string name, contact;
                cout << "Enter customer name: ";
                cin >> name;
                cout << "Enter contact details: ";
                cin >> contact;
                registerCustomer(name, contact);
                break;
            }
            case 6:
                viewCustomerAccounts();
                break;
            case 7:
                cout << "Exiting application." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 7);
    }
};

int main() {
    EliteDrive app;
    app.run();
    return 0;
}
