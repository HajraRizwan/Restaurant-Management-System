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

// Tax Strategy Factory
class TaxStrategyFactory {
public:
    static TaxStrategy* getTaxStrategy(bool dineIn) {
        return dineIn ? static_cast<TaxStrategy*>(new DineInTax()) : static_cast<TaxStrategy*>(new NoTax());
    }
};

// Discount Strategy Interface
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

// Billing Class
class Billing {
public:
    double calculateTotal(Order &order, TaxStrategy* taxStrategy, DiscountStrategy* discountStrategy) {
        double taxedPrice = taxStrategy->calculateTax(order.totalPrice);
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

// Staff Management
class Employee {
public:
    string name, role;
    double salary;
    Employee(string n, string r, double s) : name(n), role(r), salary(s) {}
    virtual void displayInfo() {
        cout << name << " - " << role << ", Salary: Rs" << salary << endl;
    }
};

class StaffManagement {
    vector<Employee*> staffList;
public:
    StaffManagement() {
        staffList.push_back(new Employee("Ahmed", "Manager", 50000));
        staffList.push_back(new Employee("Ali", "Chef", 30000));
    }
    void displayStaff() {
        cout << "\nStaff Members:\n";
        for (auto s : staffList) {
            s->displayInfo();
        }
    }
};

// Main
int main() {
    Menu menu;
    CustomerDetails customer;
    FeedbackManager feedbackManager;
    StaffManagement staffManager;
    
    while (true) {
        int choice;
        cout << "1) Place Order\n2) Manage Staff\n3) Give Feedback\n4) View Feedbacks\n5) Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            Order order;
            order.placeOrder(menu);
            
            TaxStrategy* taxStrategy = TaxStrategyFactory::getTaxStrategy(order.dineIn);
            DiscountStrategy* discountStrategy;
            
            char promo;
            cout << "Do you have a promo code? (y/n): ";
            cin >> promo;
            discountStrategy = (promo == 'y' || promo == 'Y') ? static_cast<DiscountStrategy*>(new PercentageDiscount()) : static_cast<DiscountStrategy*>(new NoDiscount());
            
            Billing bill;
            double total = bill.calculateTotal(order, taxStrategy, discountStrategy);
            
            cout << "Total Price after discount is: Rs " << total << endl;
            if (order.dineIn) {
                cout << "Your dine-in order is ready. Enjoy your meal!\n";
            }
            
            Payment payment;
            payment.processPayment(total);
            
            delete taxStrategy;
            delete discountStrategy;
        } else if (choice == 2) {
            staffManager.displayStaff();
        } else if (choice == 3) {
            feedbackManager.giveFeedback();
        } else if (choice == 4) {
            FeedbackManager::displayFeedbacks();
        } else {
            break;
        }
    }
    return 0;
}
