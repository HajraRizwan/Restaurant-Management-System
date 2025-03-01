#include <iostream>
#include <vector>
using namespace std;

// Meal Class
class Meal {
public:
    string name;
    double price;
    Meal(string n, double p) : name(n), price(p) {}
};

// Menu Class
class Menu {
public:
    vector<Meal> meals = {
        {"Fries", 5}, {"Burger", 15}, {"Wrap", 25}, {"Pizza", 30},
        {"Pasta", 20}, {"Salad", 10}, {"Nuggets", 12}, {"Sandwich", 18},
        {"Soup", 8}, {"Steak", 40}
    };

    void displayMeals() {
        cout << "Meals Available:\n";
        for (size_t i = 0; i < meals.size(); i++) {
            cout << i + 1 << ") " << meals[i].name << " - Rs" << meals[i].price << endl;
        }
    }
};

// CustomerDetails Class
class CustomerDetails {
public:
    string name, contact;
    
    void inputDetails() {
        cout << "Enter customer name: ";
        cin >> name;
        cout << "Enter contact number: ";
        cin >> contact;
    }
};

// Order Class
class Order {
public:
    CustomerDetails customer;
    vector<Meal> selectedMeals;
    bool dineIn;
    double totalPrice = 0;

    void placeOrder(Menu &menu) {
        customer.inputDetails();
        menu.displayMeals();
        
        cout << "Select meals by number (0 to stop): ";
        int choice;
        while (true) {
            cin >> choice;
            if (choice == 0) break;
            if (choice >= 1 && choice <= (int)menu.meals.size()) {
                selectedMeals.push_back(menu.meals[choice - 1]);
                totalPrice += menu.meals[choice - 1].price;
            } else {
                cout << "Invalid choice, try again." << endl;
            }
        }

        cout << "Dine-in? (1 for yes, 0 for no): ";
        cin >> dineIn;
    }
};

// Tax Strategy Interface
class TaxStrategy {
public:
    virtual double calculateTax(double amount) = 0;
    virtual ~TaxStrategy() = default; // Virtual destructor for proper cleanup
};

// Dine-in Tax
class DineInTax : public TaxStrategy {
public:
    double calculateTax(double amount) override {
        return amount * 1.05;
    }
};

// No Tax
class NoTax : public TaxStrategy {
public:
    double calculateTax(double amount) override {
        return amount;
    }
};

// Billing Class
class Billing {
    TaxStrategy* taxStrategy;
public:
    Billing(TaxStrategy* strategy) : taxStrategy(strategy) {}

    double calculateTotal(Order &order) {
        return taxStrategy->calculateTax(order.totalPrice);
    }
};

// Discount Class
class Discount {
public:
    double applyDiscount(double price) {
        char promo;
        cout << "Do you have a promo code? (y/n): ";
        cin >> promo;
        if (promo == 'y' || promo == 'Y') {
            cout << "10% discount applied!" << endl;
            return price * 0.9;
        }
        return price;
    }
};

// Payment Class
class Payment {
public:
    void processPayment(double amount) {
        cout << "Processing payment of Rs" << amount << "... Payment successful!\n";
    }
};

// Employee Interface (Abstract Class)
class Employee {
public:
    string name, role, shiftTime;
    double salary;

    Employee(string n, string r, double s, string shift) : name(n), role(r), salary(s), shiftTime(shift) {}
    virtual void displayInfo() = 0; // Pure virtual function
    virtual ~Employee() = default;  // Virtual destructor for proper cleanup
};

// Specific Employee Types
class Manager : public Employee {
public:
    Manager(string n, double s) : Employee(n, "Manager", s, "Full Day") {}
    void displayInfo() override {
        cout << name << " - Manager, Salary: Rs" << salary << ", Shift: " << shiftTime << endl;
    }
};

class Chef : public Employee {
public:
    Chef(string n, double s) : Employee(n, "Chef", s, "Morning") {}
    void displayInfo() override {
        cout << name << " - Chef, Salary: Rs" << salary << ", Shift: " << shiftTime << endl;
    }
};

// Staff Management Interface
class IEmployeeManagement {
public:
    virtual void displayStaff() = 0;
    virtual void hireStaff() = 0;
};

// Staff Management Class
class StaffManagement : public IEmployeeManagement {
    vector<Employee*> staffList;
public:
    StaffManagement() {
        staffList.push_back(new Manager("Ahmed", 50000));
        staffList.push_back(new Chef("Ali", 30000));
    }

    void displayStaff() override {
        for (auto s : staffList) {
            s->displayInfo();
        }
    }

    void hireStaff() override {
        string name, role, shift;
        double salary;
        cout << "Enter staff name: ";
        cin >> name;
        cout << "Enter role: ";
        cin >> role;
        cout << "Enter salary: ";
        cin >> salary;
        cout << "Enter shift time: ";
        cin >> shift;

        if (role == "Manager")
            staffList.push_back(new Manager(name, salary));
        else if (role == "Chef")
            staffList.push_back(new Chef(name, salary));
        else
            cout << "Invalid role. Only Managers and Chefs can be hired.\n";
    }
};

// Feedback Manager Class
class FeedbackManager {
public:
    static vector<string> feedbackList;

    void giveFeedback() {
        string feedback;
        cout << "Please provide your feedback: ";
        cin.ignore();
        getline(cin, feedback);
        feedbackList.push_back(feedback);
        cout << "Thank you for your feedback!\n";
    }

    static void displayFeedbacks() {
        cout << "\nCustomer Feedbacks:\n";
        for (const string& f : feedbackList) {
            cout << "- " << f << endl;
        }
    }
};

vector<string> FeedbackManager::feedbackList;

// Main
int main() {
    Menu menu;
    StaffManagement staffManager;
    
    while (true) {
        int choice;
        cout << "1) Place Order\n2) Staff Management\n3) Feedback\n4) View Feedbacks\n5) Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            Order order;
            order.placeOrder(menu);

            TaxStrategy* taxStrategy = (order.dineIn) ? static_cast<TaxStrategy*>(new DineInTax()) : static_cast<TaxStrategy*>(new NoTax());
            Billing bill(taxStrategy);
            double total = bill.calculateTotal(order);
            delete taxStrategy;

            Discount discount;
            total = discount.applyDiscount(total);
            cout << "Total Price: Rs" << total << endl;

            Payment payment;
            payment.processPayment(total);
        } else if (choice == 2) {
            cout << "1) View Employees\n2) Hire New Staff\nChoose an option: ";
            int staffChoice;
            cin >> staffChoice;
            if (staffChoice == 1) {
                staffManager.displayStaff();
            } else if (staffChoice == 2) {
                staffManager.hireStaff();
            }
        } else if (choice == 3) {
            FeedbackManager feedback;
            feedback.giveFeedback();
        } else if (choice == 4) {
            FeedbackManager::displayFeedbacks();
        } else {
            cout << "Exiting...";
            break;
        }
    }
    return 0;
}