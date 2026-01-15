# Bank System – Console Application (C++)

An educational console-based bank management system built during my first month of learning C++.  
The project focuses on programming fundamentals, logical flow, and basic system design concepts.

---

## 🔹 Features

### Client Management
- Add new clients
- Update client information
- Delete clients
- Find clients by account number
- Display all clients

### Transactions
- Deposit
- Withdraw
- Display total balances

### User Management
- User login system
- Add, update, delete, and find users
- Permission-based access control

---

## 🔹 Permission System

The system uses numeric permission flags to control access:

- `1`  → Show clients list  
- `2`  → Add new client  
- `4`  → Delete client  
- `8`  → Update client  
- `16` → Find client  
- `32` → Transactions  
- `64` → Manage users  
- `-1` → Full access (Admin)

---

## 🔹 Data Storage

- Data is stored using text files:
  - `Clients.txt`
  - `Users.txt`
- This approach was chosen for simplicity and learning purposes.

---

## 🔹 Project Scope & Notes

- This is an **educational project**, not a production system.
- Built early in my learning journey to practice:
  - File handling
  - Functions & structures
  - Menu-driven programs
  - Basic authentication and authorization logic
- UI, security, and scalability were intentionally kept simple.
