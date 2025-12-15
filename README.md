## Event Registration & Ticketing System (C++)

### Overview

This project is a **console-based Event Registration & Ticketing System** written in C++.  
It allows **admins** to manage events, users, and reports, while **users** can sign up, browse events, and book tickets.  
Data is stored using **parallel arrays** with **CSV file persistence**, making it a good demonstration of core programming and data-handling concepts.

### Problem Statement & Objective

Managing events manually (spreadsheets, paper forms, ad‑hoc lists) is error‑prone and time‑consuming. Organizers need a way to **store events, track seats, manage users, and issue tickets** in a structured way.  
The objective of this project is to build a **modular C++ application** that:

- **Centralizes event data** (name, date, venue, category, price, capacity, availability).
- **Automates user registration and ticket booking** with unique ticket IDs.
- **Persists data** across runs using CSV files instead of a database.
- **Generates basic analytics** such as total revenue, total bookings, and event‑wise statistics.

This project contributes educationally by applying **arrays, file handling, custom string utilities, validation, and simple reporting** in a real‑world style application.

### Users of the Application

- **Admins (Event/System Administrators)**  
  - Manage events: add, view, update, and delete events.  
  - Manage users: view/delete users.  
  - Monitor the system: view all registrations and generate revenue/booking reports.

- **Customers / Event Attendees (Registered Users)**  
  - Sign up and log in.  
  - Browse and search events (by name and category).  
  - Book tickets and view their own bookings or ticket details by ID.

### Core Features

- **Admin Portal**
  - Login with a fixed admin username and password.
  - Add, view, update, and delete events.
  - View all registrations (tickets) for all users.
  - View all users and delete a selected user.
  - Generate sales and booking reports:
    - Total revenue.
    - Total bookings.
    - Per‑event bookings and revenue.

- **User Portal**
  - User signup with unique username and basic email validation.
  - User login with username and password.
  - View all available events.
  - Search events by **name** or **category**.
  - Book tickets for an event (with seat‑availability checks).
  - View **My Bookings** (all tickets associated with the logged‑in user).
  - View **Ticket by ID** to see an “official ticket” printout.

- **Persistence & Utilities**
  - Data stored in three CSV files:
    - `users.csv` – usernames, passwords, emails.
    - `events.csv` – event details and capacities.
    - `tickets.csv` – ticket IDs, user references, event references, quantities, cost, and dates.
  - Custom string and number utility functions instead of relying heavily on the STL.
  - Input validation helpers for integers, doubles, and email format.

### Data Structures – Parallel Arrays

The project is intentionally built using **parallel arrays** (to align with PF/Data‑Structures learning outcomes) instead of classes or STL containers:

- **User Data**
  - Arrays: `usernames[]`, `passwords[]`, `emails[]`  
  - Counter: `userCount`

- **Event Data**
  - Arrays: `eventNames[]`, `eventDates[]`, `eventVenues[]`, `eventCategories[]`,  
    `eventPrices[]`, `eventCapacities[]`, `eventAvailable[]`  
  - Counter: `eventCount`

- **Ticket Data**
  - Arrays: `ticketIDs[]`, `ticketUsernames[]`, `ticketEmails[]`, `ticketEventIDs[]`,  
    `ticketQuantities[]`, `ticketCosts[]`, `ticketDates[]`  
  - Counter: `ticketCount`

These arrays are kept **in sync by index**, e.g., `eventNames[i]`, `eventDates[i]`, and `eventAvailable[i]` represent the same event.

### Function Design & Responsibilities

The project uses many small functions, each with a clear responsibility (supporting the Single Responsibility Principle):

- **Display & Navigation**
  - `clearScreen()`, `displayHeader()`, `displayMainMenu()`, `displayAdminMenu()`, `displayUserMenu()`, `getUserChoice()`, `pauseScreen()`

- **Authentication & Users**
  - `adminLogin()`, `userLogin()`, `userSignup()`
  - `addUser()`, `deleteUser()`, `viewAllUsers()`, `findUserIndex()`, `getUserEmail()`

- **File Handling (CSV)**
  - `loadUsersFromCSV()`, `saveUsersToCSV()`
  - `loadEventsFromCSV()`, `saveEventsToCSV()`
  - `loadTicketsFromCSV()`, `saveTicketsToCSV()`

- **Validation & String Utilities**
  - `isUsernameUnique()`, `isValidEmail()`, `isValidNumber()`
  - `getValidInteger()`, `getValidDouble()`, `clearInputBuffer()`
  - `stringLength()`, `stringCompare()`, `stringFind()`
  - `intToString()`, `doubleToString()`, `stringToInt()`, `stringToDouble()`
  - `getCurrentDate()`

- **Events & Tickets**
  - `addEvent()`, `updateEvent()`, `deleteEvent()`, `viewAllEvents()`
  - `searchEventByName()`, `searchEventByCategory()`
  - `generateTicketID()`, `bookTicket()`
  - `viewUserTickets()`, `viewTicketByID()`, `viewAllRegistrations()`

- **Reports**
  - `generateReports()`
  - `calculateTotalRevenue()`, `calculateTotalBookings()`, `calculateEventBookings()`

### Function Flow (High-Level)

Below is a **simplified Mermaid diagram** of the function call flow:

```mermaid
flowchart TD
    main[main()] --> loadUsersFromCSV()
    main --> loadEventsFromCSV()
    main --> loadTicketsFromCSV()
    main --> displayHeader()
    main --> mainMenu[displayMainMenu() / getUserChoice()]

    mainMenu --> adminLogin[adminLogin()]
    mainMenu --> userLogin[userLogin()]
    mainMenu --> userSignup[userSignup()]

    adminLogin --> adminMenu[displayAdminMenu() / getUserChoice()]
    adminMenu --> addEvent()
    adminMenu --> viewAllEvents()
    adminMenu --> updateEvent()
    adminMenu --> deleteEvent()
    adminMenu --> viewAllRegistrations()
    adminMenu --> generateReports()
    adminMenu --> viewAllUsers()
    adminMenu --> deleteUser()

    userLogin --> userMenu[displayUserMenu() / getUserChoice()]
    userMenu --> viewAllEventsUser[viewAllEvents()]
    userMenu --> searchEventByName()
    userMenu --> searchEventByCategory()
    userMenu --> bookTicket()
    userMenu --> viewUserTickets()
    userMenu --> viewTicketByID()
```

### Functional Requirements (User Stories)

**Admin**
- Log in to the admin portal to manage the system.  
- Add, view, update, and delete events.  
- View all registrations and all users.  
- Delete users when necessary.  
- Generate sales and booking reports.

**User**
- Sign up with a unique username, password, and email.  
- Log in to access personal features.  
- View all events and search by name or category.  
- Book tickets for events and receive a unique ticket ID.  
- View all personal bookings and look up a ticket by ID.

### How to Build & Run

**Requirements**
- A C++ compiler (e.g., `g++` from MinGW or similar)  
- Windows terminal / PowerShell / CMD

**Compile**

```bash
g++ -std=c++11 Project.cpp -o EventSystem
```

**Run**

```bash
./EventSystem
```

On first run, CSV files (`users.csv`, `events.csv`, `tickets.csv`) may not exist; they will be created as you start adding data.

### Weaknesses / Limitations

- Console‑based and **single‑machine**, with no real concurrency support.  
- Uses **CSV files** instead of a real database (no transactions, no indexing, easier to corrupt).  
- Passwords are stored in **plain text**; there is no encryption or advanced security.  
- Fixed maximum sizes for users, events, and tickets due to static arrays.  
- No integration with payment gateways, email/SMS notifications, or network access.

### Future Directions

In a future semester, this project can evolve by:

- Migrating to a **GUI or web‑based interface** for better usability.  
- Replacing CSV files with a **relational database** (MySQL, PostgreSQL, etc.).  
- Implementing **secure password hashing**, stronger authentication, and role‑based access control.  
- Adding **online payments**, automated email confirmations, and richer reporting dashboards.  
- Refactoring data storage to use **structs/classes and STL containers** (e.g., `vector`, `map`) for better scalability and maintainability.

### Credits

This project was created as a **Programming Fundamentals / Data Structures** term project to practice:

- Procedural program design  
- Parallel arrays and manual string manipulation  
- File I/O with CSV formats  
- Basic analytics and report generation for a realistic business scenario  

Feel free to extend, refactor, or modernize this system into a full‑featured event management platform.
