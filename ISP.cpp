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

// Menu Class (SRP Applied)
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

// CustomerDetails Class (SRP Applied)
class CustomerDetails {
public:
    string name, contact;
    void inputDetails() {
        cout << "Enter customer name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter contact number: ";
        cin >> contact;
    }
};

// Order Class (SRP Applied)
class Order {
public:
    vector<Meal> selectedMeals;
    double totalPrice = 0;
    bool dineIn;

    void placeOrder(Menu &menu) {
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

// Tax Strategy (OCP Applied)
class TaxStrategy {
public:
    virtual double calculateTax(double amount) = 0;
    virtual ~TaxStrategy() = default;
};

class DineInTax : public TaxStrategy {
public:
    double calculateTax(double amount) override {
        return amount * 1.05;
    }
};

class NoTax : public TaxStrategy {
public:
    double calculateTax(double amount) override {
        return amount;
    }
};

// Tax Strategy Factory (OCP Applied)
class TaxStrategyFactory {
public:
    static TaxStrategy* getTaxStrategy(bool dineIn) {
        return dineIn ? static_cast<TaxStrategy*>(new DineInTax()) : static_cast<TaxStrategy*>(new NoTax());
    }
};

// Discount Strategy (OCP Applied)
class DiscountStrategy {
public:
    virtual double applyDiscount(double price) = 0;
    virtual ~DiscountStrategy() = default;
};

class NoDiscount : public DiscountStrategy {
public:
    double applyDiscount(double price) override {
        return price;
    }
};

class PercentageDiscount : public DiscountStrategy {
public:
    double applyDiscount(double price) override {
        return price * 0.9; // 10% discount
    }
};

// Billing Class (SRP & OCP Applied)
class Billing {
public:
    double calculateTotal(Order &order, TaxStrategy* taxStrategy, DiscountStrategy* discountStrategy) {
        double taxedPrice = taxStrategy->calculateTax(order.totalPrice);
        return discountStrategy->applyDiscount(taxedPrice);
    }
};

// Payment Class (SRP Applied)
class Payment {
public:
    void processPayment(double amount) {
        cout << "Processing payment of Rs" << amount << "... Payment successful!\n";
    }
};

// Feedback Repository (SRP Applied)
class FeedbackRepository {
public:
    static vector<string> feedbackList;
    static void storeFeedback(const string& feedback) {
        feedbackList.push_back(feedback);
    }
    static void displayFeedbacks() {
        cout << "\nCustomer Feedbacks:\n";
        for (const string& f : feedbackList) {
            cout << "- " << f << endl;
        }
    }
};
vector<string> FeedbackRepository::feedbackList;

// Feedback Manager (SRP Applied)
class FeedbackManager {
public:
    void giveFeedback() {
        string feedback;
        cout << "Please provide your feedback: ";
        cin.ignore();
        getline(cin, feedback);
        FeedbackRepository::storeFeedback(feedback);
        cout << "Thank you for your feedback!\n";
    }
};

// Employee Base Class (LSP Applied)
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

// Main Function
int main() {
    Menu menu;
    Order order;
    CustomerDetails customer;

    cout << "Welcome to the Restaurant Management System!\n";
    customer.inputDetails();
    order.placeOrder(menu);

    TaxStrategy* taxStrategy = TaxStrategyFactory::getTaxStrategy(order.dineIn);
    DiscountStrategy* discountStrategy = new PercentageDiscount();

    Billing billing;
    double totalAmount = billing.calculateTotal(order, taxStrategy, discountStrategy);
    
    Payment payment;
    payment.processPayment(totalAmount);

    // Free allocated memory
    delete taxStrategy;
    delete discountStrategy;

    FeedbackManager feedbackManager;
    feedbackManager.giveFeedback();
    FeedbackRepository::displayFeedbacks();

    StaffManagement staffManagement;
    staffManagement.displayStaff();

    return 0;
}
