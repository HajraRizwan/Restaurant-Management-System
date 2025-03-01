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

// Order Class (Now only responsible for storing order data)
class Order {
public:
    vector<Meal> selectedMeals;
    double totalPrice = 0;
    bool dineIn = false;

    void addMeal(Meal meal) {
        selectedMeals.push_back(meal);
        totalPrice += meal.price;
    }
};

// OrderProcessor Class (Handles order placement separately)
class OrderProcessor {
public:
    void placeOrder(Menu &menu, Order &order) {
        menu.displayMeals();
        cout << "Select meals by number (0 to stop): ";
        int choice;
        while (true) {
            cin >> choice;
            if (choice == 0) break;
            if (choice >= 1 && choice <= (int)menu.meals.size()) {
                order.addMeal(menu.meals[choice - 1]);
            } else {
                cout << "Invalid choice, try again." << endl;
            }
        }

        cout << "Dine-in? (1 for yes, 0 for no): ";
        cin >> order.dineIn;
    }
};

// Tax Strategy Interface
class TaxStrategy {
public:
    virtual double calculateTax(double amount) = 0;
    virtual ~TaxStrategy() = default;
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

// Billing Class (Only applies tax)
class Billing {
public:
    static double applyTax(Order &order) {
        TaxStrategy* taxStrategy = order.dineIn ? static_cast<TaxStrategy*>(new DineInTax()) : static_cast<TaxStrategy*>(new NoTax());
        double totalWithTax = taxStrategy->calculateTax(order.totalPrice);
        delete taxStrategy;
        return totalWithTax;
    }
};

// Discount Class (Handles promo codes separately)
class Discount {
public:
    static double applyDiscount(double price) {
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

// Employee Abstract Class
class Employee {
public:
    string name, role, shiftTime;
    double salary;

    Employee(string n, string r, double s, string shift) : name(n), role(r), salary(s), shiftTime(shift) {}
    virtual void displayInfo() = 0;
    virtual ~Employee() = default;
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

// Staff Management Class (Only for displaying staff)
class StaffManagement {
    vector<Employee*> staffList;
public:
    StaffManagement() {
        staffList.push_back(new Manager("Ahmed", 50000));
        staffList.push_back(new Chef("Ali", 30000));
    }

    void displayStaff() {
        for (auto s : staffList) {
            s->displayInfo();
        }
    }
};

// Hiring Manager Class (Handles new hiring separately)
class HiringManager {
public:
    static Employee* hireStaff() {
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
            return new Manager(name, salary);
        else if (role == "Chef")
            return new Chef(name, salary);
        else {
            cout << "Invalid role. Only Managers and Chefs can be hired.\n";
            return nullptr;
        }
    }
};

// Feedback Repository (Handles storage separately)
class FeedbackRepository {
public:
    static vector<string> feedbackList;

    static void addFeedback(const string& feedback) {
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

// FeedbackManager Class
class FeedbackManager {
public:
    void giveFeedback() {
        string feedback;
        cout << "Please provide your feedback: ";
        cin.ignore();
        getline(cin, feedback);
        FeedbackRepository::addFeedback(feedback);
        cout << "Thank you for your feedback!\n";
    }
};

// Main
int main() {
    Menu menu;
    StaffManagement staffManager;

    while (true) {
        int choice;
        cout << "1) Place Order\n2) Staff Management\n3) Feedback\n4) View Feedbacks\n5) Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            CustomerDetails customer;
            customer.inputDetails();

            Order order;
            OrderProcessor orderProcessor;
            orderProcessor.placeOrder(menu, order);

            double total = Billing::applyTax(order);
            total = Discount::applyDiscount(total);

            cout << "Total Price: Rs" << total << endl;
            Payment payment;
            payment.processPayment(total);
        } else if (choice == 2) {
            staffManager.displayStaff();
        } else if (choice == 3) {
            FeedbackManager feedback;
            feedback.giveFeedback();
        } else if (choice == 4) {
            FeedbackRepository::displayFeedbacks();
        } else {
            cout << "Exiting...";
            break;
        }
    }
    return 0;
}
