🏧 ATM Banking System (C++ Console Application - Procedural)
===========================================================

A colorful and interactive console-based ATM Banking System built with C++, designed to simulate real-world ATM operations such as withdrawals, deposits, balance checking, and transaction history.

This project is ideal for practicing file handling, structs, enums, time handling, and menu-driven console applications in C++.

📌 Project Idea
---------------
The idea of this project is to create a simple ATM system that allows a bank client to log in using an account number and PIN code, then perform common ATM operations through a clear and user-friendly console interface.

All client data and transaction history are stored in text files, ensuring data persistence even after closing the program.

👤 What Can the Client Do?
-------------------------
After logging in, the client can:

- 💸 Quick Withdraw (predefined amounts)
- 💰 Normal Withdraw (custom amount)
- ➕ Deposit money
- 📊 Check account balance
- 🔐 Change PIN code
- 👤 View personal account details
- 📜 View transaction history
- 🚪 Log out securely

⚙️ Features
------------
- 🗂 File-based data storage using text files
- 🔐 Secure login using Account Number & PIN
- 🎨 Colored console output using ANSI escape codes
- 📑 Clean and intuitive menu-driven interface
- 🕒 Transaction history with date & time logging
- 🧱 Structured procedural code using:
  - `struct`
  - `enum`
  - `vector`
- 🔄 Persistent data storage (saved after program exit)

🧠 How the System Works
-----------------------
- The program starts with a login screen
- Client credentials are validated from `Clients.txt`
- Each transaction is recorded in a dedicated history file per client
- Menus guide the user through available ATM operations
- Input validation ensures safe and correct transactions
- Console colors enhance user experience and readability

📁 Files Used in the Project
----------------------------
- `Clients.txt`  
  Stores client account data

- `ClientHistory_[AccountNumber].txt`  
  Stores transaction history for each client

▶️ How to Run the Project (Visual Studio)
----------------------------------------
1. Open Visual Studio
2. Click **Create a new project**
3. Choose **Console App**
4. Select **C++**
5. Click **Next**
6. Name the project (e.g. `ATM-System`)
7. Replace the auto-generated `.cpp` file with the project code
8. Make sure this file exists in the same directory:
   - `Clients.txt`
9. Click **Run ▶️** or press **Ctrl + F5**

🛠 Requirements
----------------
**💻 Operating System**
- Windows 10 or later

**🧰 IDE**
- Visual Studio 2019 / 2022 (Recommended)

**⚙️ Compiler**
- MSVC (Visual Studio C++ Compiler)

⚠️ Notes & Warnings
--------------------
- 📁 `Clients.txt` must exist before running the program
- 🧾 File data format must not be changed
- 💡 This is a console-based application (no GUI)
- 🎨 Console colors may vary depending on terminal support

🎓 Educational Value
--------------------
This project helps you practice:

- File handling in C++
- Structs and enums
- Vectors and data organization
- Date & time handling
- Input validation
- Procedural programming
- Real-world ATM simulation logic
