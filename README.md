# **Restaurant Management System**

A simple **C++** console-based restaurant management system that allows customers to place orders, manage staff, apply discounts, process payments, and collect feedback.

## **Features**  

✔️ **Menu Display** – View available meals and prices.  
✔️ **Order System** – Customers can select meals and choose dine-in or takeaway.  
✔️ **Billing System** – Calculates total price with tax and discounts.  
✔️ **Payment Processing** – Simulates payment confirmation.  
✔️ **Staff Management** – View and hire staff (Managers & Chefs).  
✔️ **Feedback System** – Customers can provide feedback, which can be reviewed later.  

## **Technologies Used**  

🖥️ **C++ (Object-Oriented Programming)**  

## **How to Run**  

Clone the repository:  
```sh
git clone https://github.com/HajraRizwan/Restaurant-Management-System.git

# SOLID Principles Applied

A collection of five design principles known as **SOLID** aids programmers in creating code that is clear, scalable, and maintainable. SOLID ensures that new features can be introduced without interfering with existing functionality by reducing complexity, increasing flexibility, simplifying debugging, and improving collaboration.

## Team Members
- **Aleeha Akhlaq**
- **Azka Humayon**
- **Mahnoor Asif**
- **Hajra Rizwan**
- **Ifrah Irshad Malik**

## 1. Single Responsibility Principle (SRP)
A class should only do one job and have one reason to change.

### ✅ Refactoring Changes:
- **Order Class:** Separated customer details handling into its own step.
- **Billing Class:** Separated tax calculation from order processing.
- **Staff Management:** Split hiring logic into a separate `HiringManager` class.
- **FeedbackManager:** Moved storage to `FeedbackRepository`.

## 2. Open-Closed Principle (OCP)
A class should be open for extension but closed for modification.

### ✅ Refactoring Changes:
- **Tax Strategy:** Introduced `TaxStrategyFactory` for dynamic tax application.
- **Discount Strategy:** Introduced `DiscountStrategy` interface for easier new discount additions.
- **Order Processing:** Introduced `OrderProcessor` to apply tax and discounts dynamically.
- **Staff Management:** Introduced `RoleManager` to handle different employee roles.
- **Feedback Management:** Separated feedback storage into `FeedbackRepository`.

## 3. Liskov Substitution Principle (LSP)
Subclasses should be replaceable without breaking the program.

### ✅ Refactoring Changes:
- **Employee Class:** Introduced `displayInfo()` function to enforce proper overrides.
- **Tax Strategy:** Created an abstract `TaxStrategy` class with a `calculateTax()` method.
- **Discount Strategy:** Enforced `applyDiscount()` method in `DiscountStrategy`.
- **Staff Management:** Introduced `HiringManager` to ensure `Employee` subclasses remain interchangeable.

## 4. Interface Segregation Principle (ISP)
A class should not be forced to implement interfaces it does not use.

### ✅ Refactoring Changes:
- **Employee Class:** Split into separate interfaces:
  - `ICookingStaff` → `Chef` implements only `cookFood()`.
  - `IManagementStaff` → `Manager` implements only `manageAccounts()`.

## 5. Dependency Inversion Principle (DIP)
High-level modules should not depend on low-level modules. Both should depend on abstractions.

### ✅ Refactoring Changes:
- **Order Class:** Introduced `IMenuProvider` interface.
- **Billing Class:** Introduced `ITaxCalculator` interface for tax calculation.
- **Discount Strategy:** Implemented a `DiscountStrategy` interface for dynamic discount handling.

## Justification
The refactored design improves **maintainability, flexibility, and scalability** by following SOLID principles. Each component now has a distinct role, reducing complexity and making the system adaptable for future enhancements. The restructuring ensures:

- **SRP:** Easier updates and debugging.
- **OCP:** New features like tax rules and discounts can be added without modifying existing code.
- **LSP:** Subclasses remain interchangeable.
- **ISP:** Avoids unnecessary dependencies, improving readability and scalability.
- **DIP:** Enhances modularity and flexibility.

This restructuring ensures that the system can grow with business needs without adding complexity or technical debt.
