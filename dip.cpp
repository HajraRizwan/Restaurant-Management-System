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

// Abstract Interface for Tax Calculation (DIP Applied)
class ITaxCalculator {
public:
    virtual double calculateTax(double amount) = 0;
    virtual ~ITaxCalculator() = default;
};

// Dine-in Tax Strategy (5% Tax)
class DineInTax : public ITaxCalculator {
public:
    double calculateTax(double amount) override {
        return amount * 1.05;  // 5% tax
    }
};

// No Tax Strategy for Takeaway
class NoTax : public ITaxCalculator {
public:
    double calculateTax(double amount) override {
        return amount;  // No tax applied
    }
};

// Discount Strategy Interface
class IDiscountStrategy {
public:
    virtual double applyDiscount(double price) = 0;
    virtual ~IDiscountStrategy() = default;
};

// No Discount Applied
class NoDiscount : public IDiscountStrategy {
public:
    double applyDiscount(double price) override {
        return price;
    }
};

// Percentage Discount (10%)
class PercentageDiscount : public IDiscountStrategy {
public:
    double applyDiscount(double price) override {
        return price * 0.9; // 10% discount
    }
};

// Billing Class (DIP: Depends on ITaxCalculator and IDiscountStrategy)
class Billing {
public:
    double calculateTotal(Order &order, ITaxCalculator* taxCalculator, IDiscountStrategy* discountStrategy) {
        double taxedPrice = taxCalculator->calculateTax(order.totalPrice);
        return discountStrategy->applyDiscount(taxedPrice);
    }
};

// Payment Class
class Payment {
public:
    void processPayment(double amount) {
        cout << "Processing payment of Rs" << amount << "... Payment successful!\n";
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

// Staff Management (Applying ISP)
class Employee {
public:
    string name;
    double salary;
    Employee(string n, double s) : name(n), salary(s) {}
    virtual void displayInfo() = 0;
    virtual ~Employee() = default;
};

// Interfaces for ISP
class ICookingStaff {
public:
    virtual void cookFood() = 0;
};

class IManagementStaff {
public:
    virtual void manageAccounts() = 0;
};

class Manager : public Employee, public IManagementStaff {
public:
    Manager(string n, double s) : Employee(n, s) {}
    void displayInfo() override {
        cout << name << " - Manager, Salary: Rs" << salary << " (Oversees operations)\n";
    }
    void manageAccounts() override {
        cout << name << " is managing accounts.\n";
    }
};

class Chef : public Employee, public ICookingStaff {
public:
    Chef(string n, double s) : Employee(n, s) {}
    void displayInfo() override {
        cout << name << " - Chef, Salary: Rs" << salary << " (Prepares meals)\n";
    }
    void cookFood() override {
        cout << name << " is cooking meals.\n";
    }
};

class StaffManagement {
    vector<Employee*> staffList;
public:
    StaffManagement() {
        staffList.push_back(new Manager("Ahmed", 50000));
        staffList.push_back(new Chef("Ali", 30000));
    }
    void displayStaff() {
        cout << "\nStaff Members:\n";
        for (auto s : staffList) {
            s->displayInfo();
        }
    }
    ~StaffManagement() {
        for (auto s : staffList) delete s;
    }
};

// Main function
int main() {
    Menu menu;
    Order order;
    order.placeOrder(menu);

    // Apply tax using DIP
    ITaxCalculator* taxCalculator = order.dineIn ? static_cast<ITaxCalculator*>(new DineInTax()) : static_cast<ITaxCalculator*>(new NoTax());

    // Apply discount (no discount for now)
    IDiscountStrategy* discountStrategy = new NoDiscount();

    // Calculate total price
    Billing billing;
    double totalAmount = billing.calculateTotal(order, taxCalculator, discountStrategy);
    cout << "Total Amount (after tax & discount): Rs" << totalAmount << endl;

    // Process payment
    Payment payment;
    payment.processPayment(totalAmount);

    // Feedback
    FeedbackManager feedbackManager;
    feedbackManager.giveFeedback();
    FeedbackManager::displayFeedbacks();

    // Display staff information
    StaffManagement staffManagement;
    staffManagement.displayStaff();

    // Clean up memory
    delete taxCalculator;
    delete discountStrategy;

    return 0;
}