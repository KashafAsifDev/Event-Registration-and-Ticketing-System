/*
 * Event Registration and Ticketing System
 * A comprehensive C++ console application for event management
 * 
 * Features:
 * - Admin portal: Manage events, users, view reports
 * - User portal: Browse events, book tickets, view bookings
 * - File persistence using TXT format
 * - Ticket system with unique IDs
 * - Revenue analytics and reporting
 */

 #include <iostream>
 #include <fstream>
 #include <string>
 #include <limits>  //for input buffer
   //These are the settings of windows to use term colors library else compile give us error.
  // needed so COMMON_LVB_UNDERSCORE is defined
 #ifdef _WIN32
 #ifndef COMMON_LVB_UNDERSCORE
 #define COMMON_LVB_UNDERSCORE 0x8000
 #endif
 #endif
 #include "termcolor/include/termcolor/termcolor.hpp"
 using namespace std;
 using namespace termcolor;
 
 // Function Prototypes - Constants (Replaced global variables with functions)
 const int getMaxUsers();
 const int getMaxEvents();
 const int getMaxTickets();
 string getAdminUsername();
 string getAdminPassword();
 
 // Function Prototypes - Display Functions
 void clearScreen();
 void displayHeader();
 void displayMainMenu();
 void displayAdminMenu();
 void displayUserMenu();
 string getUserChoice();
 void pauseScreen();
 
 // Function Prototypes - Authentication
 bool adminLogin();
 string userLogin(string usernames[], string passwords[], int userCount);
 bool userSignup(string usernames[], string passwords[], string emails[], int& userCount);
 
 // Function Prototypes - File Handling (TXT Format)
 void loadUsersFromTXT(string usernames[], string passwords[], string emails[], int& userCount);
 void saveUsersToTXT(string usernames[], string passwords[], string emails[], int userCount);
 void loadEventsFromTXT(string eventNames[], string eventDates[], string eventVenues[], 
                        string eventCategories[], double eventPrices[], int eventCapacities[], 
                        int eventAvailable[], int& eventCount);
 void saveEventsToTXT(string eventNames[], string eventDates[], string eventVenues[], 
                      string eventCategories[], double eventPrices[], int eventCapacities[], 
                      int eventAvailable[], int eventCount);
 void loadTicketsFromTXT(int ticketIDs[], string ticketUsernames[], string ticketEmails[], 
                         int ticketEventIDs[], int ticketQuantities[], double ticketCosts[], 
                         string ticketDates[], int& ticketCount);
 void saveTicketsToTXT(int ticketIDs[], string ticketUsernames[], string ticketEmails[], 
                       int ticketEventIDs[], int ticketQuantities[], double ticketCosts[], 
                       string ticketDates[], int ticketCount);
 
 // Function Prototypes - Validation Functions
 bool isUsernameUnique(string username, string usernames[], int userCount);
 bool isValidEmail(string email);
 bool isValidNumber(string input);
 int getValidInteger(string prompt);
 double getValidDouble(string prompt);
 void clearInputBuffer();
 
 // Function Prototypes - Utility Functions
 string getCurrentDate();
 
 // Function Prototypes - Event Management Functions
 string addEvent(string name, string date, string venue, string category, double price, 
                 int capacity, string eventNames[], string eventDates[], string eventVenues[], 
                 string eventCategories[], double eventPrices[], int eventCapacities[], 
                 int eventAvailable[], int& eventCount);
 string updateEvent(int index, string name, string date, string venue, string category, 
                    double price, int capacity, int available, string eventNames[], 
                    string eventDates[], string eventVenues[], string eventCategories[], 
                    double eventPrices[], int eventCapacities[], int eventAvailable[]);
 string deleteEvent(int index, string eventNames[], string eventDates[], string eventVenues[], 
                    string eventCategories[], double eventPrices[], int eventCapacities[], 
                    int eventAvailable[], int& eventCount);
 string viewAllEvents(string eventNames[], string eventDates[], string eventVenues[], 
                      string eventCategories[], double eventPrices[], int eventCapacities[], 
                      int eventAvailable[], int eventCount);
 string searchEventByName(string name, string eventNames[], string eventDates[], 
                          string eventVenues[], string eventCategories[], double eventPrices[], 
                          int eventCapacities[], int eventAvailable[], int eventCount);
 string searchEventByCategory(string category, string eventNames[], string eventDates[], 
                              string eventVenues[], string eventCategories[], double eventPrices[], 
                              int eventCapacities[], int eventAvailable[], int eventCount);
 
 // Function Prototypes - User Management Functions
 string addUser(string username, string password, string email, string usernames[], 
                string passwords[], string emails[], int& userCount);
 string deleteUser(int index, string usernames[], string passwords[], string emails[], int& userCount);
 string viewAllUsers(string usernames[], string emails[], int userCount);
 int findUserIndex(string username, string usernames[], int userCount);
 string getUserEmail(string username, string usernames[], string emails[], int userCount);
 
 // Function Prototypes - Ticket Management Functions
 int generateTicketID(int ticketIDs[], int ticketCount);
 string bookTicket(string username, string email, int eventIndex, int quantity, 
                   string eventNames[], double eventPrices[], int eventAvailable[], 
                   int ticketIDs[], string ticketUsernames[], string ticketEmails[], 
                   int ticketEventIDs[], int ticketQuantities[], double ticketCosts[], 
                   string ticketDates[], int& ticketCount);
 string viewUserTickets(string username, int ticketIDs[], string ticketUsernames[], 
                        string ticketEmails[], int ticketEventIDs[], int ticketQuantities[], 
                        double ticketCosts[], string ticketDates[], string eventNames[], 
                        int ticketCount, int eventCount);
 string viewTicketByID(int ticketID, int ticketIDs[], string ticketUsernames[], 
                       string ticketEmails[], int ticketEventIDs[], int ticketQuantities[], 
                       double ticketCosts[], string ticketDates[], string eventNames[], 
                       int ticketCount, int eventCount);
 string viewAllRegistrations(int ticketIDs[], string ticketUsernames[], string ticketEmails[], 
                             int ticketEventIDs[], int ticketQuantities[], double ticketCosts[], 
                             string ticketDates[], string eventNames[], int ticketCount, 
                             int eventCount);
 
 // Function Prototypes - Report Functions
 void generateReports(int ticketIDs[], string ticketUsernames[], int ticketEventIDs[], 
                      int ticketQuantities[], double ticketCosts[], string eventNames[], 
                      double eventPrices[], int ticketCount, int eventCount);
 double calculateTotalRevenue(int ticketIDs[], double ticketCosts[], int ticketCount);
 int calculateTotalBookings(int ticketIDs[], int ticketCount);
 int calculateEventBookings(int eventIndex, int ticketEventIDs[], int ticketCount);
 
 // Main Function
 int main() {
     // Data Arrays - No Global Arrays (Modularity Requirement)
     string usernames[getMaxUsers()];
     string passwords[getMaxUsers()];
     string emails[getMaxUsers()];
     int userCount = 0;
     
     string eventNames[getMaxEvents()];
     string eventDates[getMaxEvents()];
     string eventVenues[getMaxEvents()];
     string eventCategories[getMaxEvents()];
     double eventPrices[getMaxEvents()];
     int eventCapacities[getMaxEvents()];
     int eventAvailable[getMaxEvents()];
     int eventCount = 0;
     
     int ticketIDs[getMaxTickets()];
     string ticketUsernames[getMaxTickets()];
     string ticketEmails[getMaxTickets()];
     int ticketEventIDs[getMaxTickets()];
     int ticketQuantities[getMaxTickets()];
     double ticketCosts[getMaxTickets()];
     string ticketDates[getMaxTickets()];
     int ticketCount = 0;
     
     // Load data from TXT files
     loadUsersFromTXT(usernames, passwords, emails, userCount);
     loadEventsFromTXT(eventNames, eventDates, eventVenues, eventCategories, eventPrices, 
                      eventCapacities, eventAvailable, eventCount);
     loadTicketsFromTXT(ticketIDs, ticketUsernames, ticketEmails, ticketEventIDs, 
                       ticketQuantities, ticketCosts, ticketDates, ticketCount);
     
     clearScreen();
     displayHeader();
     
     bool running = true;
     
     while (running) {
         displayMainMenu();
         string choice = getUserChoice();
         
         if (choice == "1" || choice == "2" || choice == "3" || choice == "4") {
             if (choice == "1") {
             // Admin Login
             bool adminLoggedIn = adminLogin();
             
             if (adminLoggedIn) {
                 clearScreen();
                 cout << "\n" << bright_green << bold << "*** Admin Login Successful! ***\n" << reset;
                 pauseScreen();
                 
                 bool adminSession = true;
                 while (adminSession) {
                     clearScreen();
                     displayAdminMenu();
                     string adminChoice = getUserChoice();
                     
                     if (adminChoice == "1" || adminChoice == "2" || adminChoice == "3" || adminChoice == "4" || 
                         adminChoice == "5" || adminChoice == "6" || adminChoice == "7" || adminChoice == "8" || adminChoice == "9") {
                         if (adminChoice == "1") {
                         // Add Event
                         clearScreen();
                         cout << "\n" << bright_cyan << bold << "========== ADD NEW EVENT ==========\n" << reset;
                         string name, date, venue, category;
                         double price;
                         int capacity;
                         
                         cin.ignore();
                         cout << bright_yellow << "Enter Event Name: " << reset;
                         getline(cin, name);
                         while ((int)name.length() == 0) {
                             cout << bright_red << "Event name cannot be empty! Enter again: " << reset;
                             getline(cin, name);
                         }
                         cout << bright_yellow << "Enter Event Date (DD-MM-YYYY): " << reset;
                         getline(cin, date);
                         while ((int)date.length() == 0) {
                             cout << bright_red << "Date cannot be empty! Enter again: " << reset;
                             getline(cin, date);
                         }
                         cout << bright_yellow << "Enter Event Venue: " << reset;
                         getline(cin, venue);
                         while ((int)venue.length() == 0) {
                             cout << bright_red << "Venue cannot be empty! Enter again: " << reset;
                             getline(cin, venue);
                         }
                         cout << bright_yellow << "Enter Event Category (Music/Conference/Sports/Other): " << reset;
                         getline(cin, category);
                         while ((int)category.length() == 0) {
                             cout << bright_red << "Category cannot be empty! Enter again: " << reset;
                             getline(cin, category);
                         }
                         price = getValidDouble("Enter Ticket Price: $");
                         while (price < 0) {
                             cout << bright_red << "Price cannot be negative! Enter again: " << reset;
                             price = getValidDouble("Enter Ticket Price: $");
                         }
                         capacity = getValidInteger("Enter Event Capacity: ");
                         while (capacity <= 0) {
                             cout << bright_red << "Capacity must be greater than 0! Enter again: " << reset;
                             capacity = getValidInteger("Enter Event Capacity: ");
                         }
                         
                         string result = addEvent(name, date, venue, category, price, capacity, 
                                                 eventNames, eventDates, eventVenues, 
                                                 eventCategories, eventPrices, eventCapacities, 
                                                 eventAvailable, eventCount);
                         cout << "\n" << bright_green << result << reset << endl;
                         saveEventsToTXT(eventNames, eventDates, eventVenues, eventCategories, 
                                        eventPrices, eventCapacities, eventAvailable, eventCount);
                         pauseScreen();
                         
                         } else if (adminChoice == "2") {
                         // View All Events
                         clearScreen();
                         string events = viewAllEvents(eventNames, eventDates, eventVenues, 
                                                      eventCategories, eventPrices, 
                                                      eventCapacities, eventAvailable, eventCount);
                         // Print with colors
                         cout << bright_cyan << bold << "\n========== ALL EVENTS ==========\n" << reset;
                         if (eventCount == 0) {
                             cout << bright_red << "No events available!" << reset << endl;
                         } else {
                             for (int i = 0; i < eventCount; i++) {
                                 cout << "\n" << bright_yellow << "Event #" << (i + 1) << reset << endl;
                                 cout << cyan << "Name: " << reset << bright_white << eventNames[i] << reset << endl;
                                 cout << cyan << "Date: " << reset << eventDates[i] << endl;
                                 cout << cyan << "Venue: " << reset << eventVenues[i] << endl;
                                 cout << cyan << "Category: " << reset << bright_magenta << eventCategories[i] << reset << endl;
                                 cout << cyan << "Price: " << reset << bright_green << "$" << to_string(eventPrices[i]) << reset << endl;
                                 cout << cyan << "Capacity: " << reset << to_string(eventCapacities[i]) << endl;
                                 cout << cyan << "Available: " << reset << bright_yellow << to_string(eventAvailable[i]) << reset << endl;
                                 cout << grey << "--------------------------------" << reset << endl;
                             }
                         }
                         pauseScreen();
                         
                         } else if (adminChoice == "3") {
                         // Update Event
                         clearScreen();
                         // Print with colors
                         cout << bright_cyan << bold << "\n========== ALL EVENTS ==========\n" << reset;
                         if (eventCount == 0) {
                             cout << bright_red << "No events available!" << reset << endl;
                         } else {
                             for (int i = 0; i < eventCount; i++) {
                                 cout << "\n" << bright_yellow << "Event #" << (i + 1) << reset << endl;
                                 cout << cyan << "Name: " << reset << bright_white << eventNames[i] << reset << endl;
                                 cout << cyan << "Date: " << reset << eventDates[i] << endl;
                                 cout << cyan << "Venue: " << reset << eventVenues[i] << endl;
                                 cout << cyan << "Category: " << reset << bright_magenta << eventCategories[i] << reset << endl;
                                 cout << cyan << "Price: " << reset << bright_green << "$" << to_string(eventPrices[i]) << reset << endl;
                                 cout << cyan << "Capacity: " << reset << to_string(eventCapacities[i]) << endl;
                                 cout << cyan << "Available: " << reset << bright_yellow << to_string(eventAvailable[i]) << reset << endl;
                                 cout << grey << "--------------------------------" << reset << endl;
                             }
                         }
                         
                         if (eventCount > 0) {
                             int index = getValidInteger("\nEnter Event Number to Update (0 to cancel): ");
                             while (index < 0 || index > eventCount) {
                                 cout << bright_red << "Invalid event number! Enter between 0 and " << eventCount << ": " << reset;
                                 index = getValidInteger("Enter Event Number: ");
                             }
                             
                             if (index > 0 && index <= eventCount) {
                                 string name, date, venue, category;
                                 double price;
                                 int capacity, available;
                                 
                                 cin.ignore();
                                 cout << bright_yellow << "Enter New Event Name: " << reset;
                                 getline(cin, name);
                                 while ((int)name.length() == 0) {
                                     cout << bright_red << "Event name cannot be empty! Enter again: " << reset;
                                     getline(cin, name);
                                 }
                                 cout << bright_yellow << "Enter New Event Date (DD-MM-YYYY): " << reset;
                                 getline(cin, date);
                                 while ((int)date.length() == 0) {
                                     cout << bright_red << "Date cannot be empty! Enter again: " << reset;
                                     getline(cin, date);
                                 }
                                 cout << bright_yellow << "Enter New Event Venue: " << reset;
                                 getline(cin, venue);
                                 while ((int)venue.length() == 0) {
                                     cout << bright_red << "Venue cannot be empty! Enter again: " << reset;
                                     getline(cin, venue);
                                 }
                                 cout << bright_yellow << "Enter New Event Category (Music/Conference/Sports/Other): " << reset;
                                 getline(cin, category);
                                 while ((int)category.length() == 0) {
                                     cout << bright_red << "Category cannot be empty! Enter again: " << reset;
                                     getline(cin, category);
                                 }
                                 price = getValidDouble("Enter New Ticket Price: $");
                                 while (price < 0) {
                                     cout << bright_red << "Price cannot be negative! Enter again: " << reset;
                                     price = getValidDouble("Enter New Ticket Price: $");
                                 }
                                 capacity = getValidInteger("Enter New Event Capacity: ");
                                 while (capacity <= 0) {
                                     cout << bright_red << "Capacity must be greater than 0! Enter again: " << reset;
                                     capacity = getValidInteger("Enter New Event Capacity: ");
                                 }
                                 available = getValidInteger("Enter Available Seats: ");
                                 while (available < 0 || available > capacity) {
                                     cout << bright_red << "Available seats must be between 0 and " << capacity << "! Enter again: " << reset;
                                     available = getValidInteger("Enter Available Seats: ");
                                 }
                                 
                                 string result = updateEvent(index - 1, name, date, venue, category, 
                                                             price, capacity, available, eventNames, 
                                                             eventDates, eventVenues, eventCategories, 
                                                             eventPrices, eventCapacities, eventAvailable);
                                 cout << "\n" << bright_green << result << reset << endl;
                                 saveEventsToTXT(eventNames, eventDates, eventVenues, eventCategories, 
                                                eventPrices, eventCapacities, eventAvailable, eventCount);
                             }
                         }
                         pauseScreen();
                         
                         } else if (adminChoice == "4") {
                         // Delete Event
                         clearScreen();
                         // Print with colors
                         cout << bright_cyan << bold << "\n========== ALL EVENTS ==========\n" << reset;
                         if (eventCount == 0) {
                             cout << bright_red << "No events available!" << reset << endl;
                         } else {
                             for (int i = 0; i < eventCount; i++) {
                                 cout << "\n" << bright_yellow << "Event #" << (i + 1) << reset << endl;
                                 cout << cyan << "Name: " << reset << bright_white << eventNames[i] << reset << endl;
                                 cout << cyan << "Date: " << reset << eventDates[i] << endl;
                                 cout << cyan << "Venue: " << reset << eventVenues[i] << endl;
                                 cout << cyan << "Category: " << reset << bright_magenta << eventCategories[i] << reset << endl;
                                 cout << cyan << "Price: " << reset << bright_green << "$" << to_string(eventPrices[i]) << reset << endl;
                                 cout << cyan << "Capacity: " << reset << to_string(eventCapacities[i]) << endl;
                                 cout << cyan << "Available: " << reset << bright_yellow << to_string(eventAvailable[i]) << reset << endl;
                                 cout << grey << "--------------------------------" << reset << endl;
                             }
                         }
                         
                         if (eventCount > 0) {
                             int index = getValidInteger("\nEnter Event Number to Delete (0 to cancel): ");
                             while (index < 0 || index > eventCount) {
                                 cout << bright_red << "Invalid event number! Enter between 0 and " << eventCount << ": " << reset;
                                 index = getValidInteger("Enter Event Number: ");
                             }
                             
                             if (index > 0 && index <= eventCount) {
                                 string result = deleteEvent(index - 1, eventNames, eventDates, 
                                                            eventVenues, eventCategories, eventPrices, 
                                                            eventCapacities, eventAvailable, eventCount);
                                 cout << "\n" << bright_red << result << reset << endl;
                                 saveEventsToTXT(eventNames, eventDates, eventVenues, eventCategories, 
                                                eventPrices, eventCapacities, eventAvailable, eventCount);
                             }
                         }
                         pauseScreen();
                         
                         } else if (adminChoice == "5") {
                         // View All Registrations
                         clearScreen();
                         string registrations = viewAllRegistrations(ticketIDs, ticketUsernames, 
                                                                     ticketEmails, ticketEventIDs, 
                                                                     ticketQuantities, ticketCosts, 
                                                                     ticketDates, eventNames, 
                                                                     ticketCount, eventCount);
                         if (registrations != "") {
                             cout << bright_red << registrations << reset << endl;
                         }
                         pauseScreen();
                         
                         } else if (adminChoice == "6") {
                         // Generate Reports
                         clearScreen();
                         generateReports(ticketIDs, ticketUsernames, ticketEventIDs, ticketQuantities, 
                                       ticketCosts, eventNames, eventPrices, ticketCount, eventCount);
                         pauseScreen();
                         
                         } else if (adminChoice == "7") {
                         // View All Users
                         clearScreen();
                         cout << bright_cyan << bold << "\n========== ALL USERS ==========\n" << reset;
                         if (userCount == 0) {
                             cout << bright_red << "No users registered!" << reset << endl;
                         } else {
                             for (int i = 0; i < userCount; i++) {
                                 cout << "\n" << bright_yellow << "User #" << (i + 1) << reset << endl;
                                 cout << cyan << "Username: " << reset << bright_white << usernames[i] << reset << endl;
                                 cout << cyan << "Email: " << reset << emails[i] << endl;
                                 cout << grey << "--------------------------------" << reset << endl;
                             }
                         }
                         pauseScreen();
                         
                         } else if (adminChoice == "8") {
                         // Delete User
                         clearScreen();
                         cout << bright_cyan << bold << "\n========== ALL USERS ==========\n" << reset;
                         if (userCount == 0) {
                             cout << bright_red << "No users registered!" << reset << endl;
                         } else {
                             for (int i = 0; i < userCount; i++) {
                                 cout << "\n" << bright_yellow << "User #" << (i + 1) << reset << endl;
                                 cout << cyan << "Username: " << reset << bright_white << usernames[i] << reset << endl;
                                 cout << cyan << "Email: " << reset << emails[i] << endl;
                                 cout << grey << "--------------------------------" << reset << endl;
                             }
                         }
                         
                         if (userCount > 0) {
                             int index = getValidInteger("\nEnter User Number to Delete (0 to cancel): ");
                             while (index < 0 || index > userCount) {
                                 cout << bright_red << "Invalid user number! Enter between 0 and " << userCount << ": " << reset;
                                 index = getValidInteger("Enter User Number: ");
                             }
                             
                             if (index > 0 && index <= userCount) {
                                 string result = deleteUser(index - 1, usernames, passwords, emails, userCount);
                                 cout << "\n" << result << endl;
                                 saveUsersToTXT(usernames, passwords, emails, userCount);
                             }
                         }
                         pauseScreen();
                         
                         } else if (adminChoice == "9") {
                             // Logout
                             clearScreen();
                             cout << "\n" << bright_yellow << "*** Admin Logged Out ***\n" << reset;
                             pauseScreen();
                             adminSession = false;
                         }
                     } else {
                         cout << "\n" << bright_red << "Invalid option! Please try again.\n" << reset;
                         pauseScreen();
                     }
                 }
             } else {
                 clearScreen();
                 cout << "\n" << bright_red << bold << "*** Admin Login Failed! ***\n" << reset;
                 pauseScreen();
             }
             
         } else if (choice == "2") {
             // User Login
             clearScreen();
             cout << "\n" << bright_cyan << bold << "========== USER LOGIN ==========\n" << reset;
             string loggedInUser = userLogin(usernames, passwords, userCount);
             
             if (loggedInUser != "") {
                 clearScreen();
                 cout << "\n" << bright_green << bold << "*** Welcome " << bright_yellow << loggedInUser << bright_green << "! ***\n" << reset;
                 pauseScreen();
                 
                 string userEmail = getUserEmail(loggedInUser, usernames, emails, userCount);
                 
                 bool userSession = true;
                 while (userSession) {
                     clearScreen();
                     displayUserMenu();
                     string userChoice = getUserChoice();
                     
                     if (userChoice == "1" || userChoice == "2" || userChoice == "3" || userChoice == "4" || 
                         userChoice == "5" || userChoice == "6" || userChoice == "7") {
                         if (userChoice == "1") {
                         // View All Events
                         clearScreen();
                         // Print with colors
                         cout << bright_cyan << bold << "\n========== ALL EVENTS ==========\n" << reset;
                         if (eventCount == 0) {
                             cout << bright_red << "No events available!" << reset << endl;
                         } else {
                             for (int i = 0; i < eventCount; i++) {
                                 cout << "\n" << bright_yellow << "Event #" << (i + 1) << reset << endl;
                                 cout << cyan << "Name: " << reset << bright_white << eventNames[i] << reset << endl;
                                 cout << cyan << "Date: " << reset << eventDates[i] << endl;
                                 cout << cyan << "Venue: " << reset << eventVenues[i] << endl;
                                 cout << cyan << "Category: " << reset << bright_magenta << eventCategories[i] << reset << endl;
                                 cout << cyan << "Price: " << reset << bright_green << "$" << to_string(eventPrices[i]) << reset << endl;
                                 cout << cyan << "Capacity: " << reset << to_string(eventCapacities[i]) << endl;
                                 cout << cyan << "Available: " << reset << bright_yellow << to_string(eventAvailable[i]) << reset << endl;
                                 cout << grey << "--------------------------------" << reset << endl;
                             }
                         }
                         pauseScreen();
                         
                         } else if (userChoice == "2") {
                         // Search Event by Name
                         clearScreen();
                         cout << "\n" << bright_cyan << bold << "========== SEARCH EVENT ==========\n" << reset;
                         cin.ignore();
                         string searchName;
                         cout << bright_yellow << "Enter Event Name to Search: " << reset;
                         getline(cin, searchName);
                         while ((int)searchName.length() == 0) {
                             cout << bright_red << "Search name cannot be empty! Enter again: " << reset;
                             getline(cin, searchName);
                         }
                         
                         string result = searchEventByName(searchName, eventNames, eventDates, 
                                                           eventVenues, eventCategories, eventPrices, 
                                                           eventCapacities, eventAvailable, eventCount);
                         if ((int)result.find("No events found") != -1) {
                             cout << bright_red << result << reset << endl;
                         } else {
                             cout << bright_cyan << bold << "\n========== SEARCH RESULTS ==========\n" << reset;
                             // Parse and print with colors
                             cout << result << endl;
                         }
                         pauseScreen();
                         
                         } else if (userChoice == "3") {
                         // Search Event by Category
                         clearScreen();
                         cout << "\n" << bright_cyan << bold << "========== SEARCH BY CATEGORY ==========\n" << reset;
                         cin.ignore();
                         string category;
                         cout << bright_yellow << "Enter Category (Music/Conference/Sports/Other): " << reset;
                         getline(cin, category);
                         while ((int)category.length() == 0) {
                             cout << bright_red << "Category cannot be empty! Enter again: " << reset;
                             getline(cin, category);
                         }
                         
                         string result = searchEventByCategory(category, eventNames, eventDates, 
                                                               eventVenues, eventCategories, eventPrices, 
                                                               eventCapacities, eventAvailable, eventCount);
                         if ((int)result.find("No events found") != -1) {
                             cout << bright_red << result << reset << endl;
                         } else {
                             cout << bright_cyan << bold << "\n========== SEARCH RESULTS ==========\n" << reset;
                             cout << result << endl;
                         }
                         pauseScreen();
                         
                         } else if (userChoice == "4") {
                         // Register for Event (Book Tickets)
                         clearScreen();
                         // Print with colors
                         cout << bright_cyan << bold << "\n========== ALL EVENTS ==========\n" << reset;
                         if (eventCount == 0) {
                             cout << bright_red << "No events available!" << reset << endl;
                         } else {
                             for (int i = 0; i < eventCount; i++) {
                                 cout << "\n" << bright_yellow << "Event #" << (i + 1) << reset << endl;
                                 cout << cyan << "Name: " << reset << bright_white << eventNames[i] << reset << endl;
                                 cout << cyan << "Date: " << reset << eventDates[i] << endl;
                                 cout << cyan << "Venue: " << reset << eventVenues[i] << endl;
                                 cout << cyan << "Category: " << reset << bright_magenta << eventCategories[i] << reset << endl;
                                 cout << cyan << "Price: " << reset << bright_green << "$" << to_string(eventPrices[i]) << reset << endl;
                                 cout << cyan << "Capacity: " << reset << to_string(eventCapacities[i]) << endl;
                                 cout << cyan << "Available: " << reset << bright_yellow << to_string(eventAvailable[i]) << reset << endl;
                                 cout << grey << "--------------------------------" << reset << endl;
                             }
                         }
                         
                         if (eventCount > 0) {
                             int eventIndex = getValidInteger("\nEnter Event Number to Book (0 to cancel): ");
                             while (eventIndex < 0 || eventIndex > eventCount) {
                                 cout << bright_red << "Invalid event number! Enter between 0 and " << eventCount << ": " << reset;
                                 eventIndex = getValidInteger("Enter Event Number: ");
                             }
                             
                             if (eventIndex > 0 && eventIndex <= eventCount) {
                                 int quantity = getValidInteger("Enter Number of Tickets: ");
                                 while (quantity <= 0) {
                                     cout << bright_red << "Quantity must be greater than 0! Enter again: " << reset;
                                     quantity = getValidInteger("Enter Number of Tickets: ");
                                 }
                                 while (quantity > eventAvailable[eventIndex - 1]) {
                                     cout << bright_red << "Not enough tickets! Only " << eventAvailable[eventIndex - 1] << " available. Enter again: " << reset;
                                     quantity = getValidInteger("Enter Number of Tickets: ");
                                 }
                                 
                                 string result = bookTicket(loggedInUser, userEmail, eventIndex - 1, quantity, 
                                                           eventNames, eventPrices, eventAvailable, 
                                                           ticketIDs, ticketUsernames, ticketEmails, 
                                                           ticketEventIDs, ticketQuantities, ticketCosts, 
                                                           ticketDates, ticketCount);
                                 cout << "\n" << bright_green << result << reset << endl;
                                 saveTicketsToTXT(ticketIDs, ticketUsernames, ticketEmails, 
                                                 ticketEventIDs, ticketQuantities, ticketCosts, 
                                                 ticketDates, ticketCount);
                                 saveEventsToTXT(eventNames, eventDates, eventVenues, eventCategories, 
                                                eventPrices, eventCapacities, eventAvailable, eventCount);
                             }
                         }
                         pauseScreen();
                         
                         } else if (userChoice == "5") {
                         // My Bookings
                         clearScreen();
                         string bookings = viewUserTickets(loggedInUser, ticketIDs, ticketUsernames, 
                                                          ticketEmails, ticketEventIDs, ticketQuantities, 
                                                          ticketCosts, ticketDates, eventNames, 
                                                          ticketCount, eventCount);
                         if (bookings != "") {
                             cout << bright_red << bookings << reset << endl;
                         }
                         pauseScreen();
                         
                             } else if (userChoice == "6") {
                             // View Ticket by ID
                             clearScreen();
                             if (ticketCount == 0) {
                                 cout << bright_red << "No tickets available!" << reset << endl;
                             } else {
                                 int ticketID = getValidInteger("Enter Ticket ID to View: ");
                                 bool found = false;
                                 for (int i = 0; i < ticketCount; i++) {
                                     if (ticketIDs[i] == ticketID) {
                                         found = true;
                                         break;
                                     }
                                 }
                                 while (!found) {
                                     cout << bright_red << "Ticket ID not found! Enter a valid ticket ID: " << reset;
                                     ticketID = getValidInteger("Enter Ticket ID: ");
                                     found = false;
                                     for (int i = 0; i < ticketCount; i++) {
                                         if (ticketIDs[i] == ticketID) {
                                             found = true;
                                             break;
                                         }
                                     }
                                 }
                                 string ticket = viewTicketByID(ticketID, ticketIDs, ticketUsernames, 
                                                                ticketEmails, ticketEventIDs, ticketQuantities, 
                                                                ticketCosts, ticketDates, eventNames, 
                                                                ticketCount, eventCount);
                                 if (ticket != "") {
                                     cout << bright_red << ticket << reset << endl;
                                 }
                             }
                         pauseScreen();
                         
                         } else if (userChoice == "7") {
                             // Logout
                             clearScreen();
                             cout << "\n" << bright_yellow << "*** User Logged Out ***\n" << reset;
                             pauseScreen();
                             userSession = false;
                         }
                     } else {
                         cout << "\n" << bright_red << "Invalid option! Please try again.\n" << reset;
                         pauseScreen();
                     }
                 }
             } else {
                 clearScreen();
                 cout << "\n" << bright_red << bold << "*** Login Failed! ***\n" << reset;
                 pauseScreen();
             }
             
         } else if (choice == "3") {
             // User Signup
             clearScreen();
             cout << "\n" << bright_cyan << bold << "========== USER SIGNUP ==========\n" << reset;
             bool signupSuccess = userSignup(usernames, passwords, emails, userCount);
             
             if (signupSuccess) {
                 cout << "\n" << bright_green << bold << "*** Signup Successful! You can now login. ***\n" << reset;
                 saveUsersToTXT(usernames, passwords, emails, userCount);
             } else {
                 cout << "\n" << bright_red << "*** Signup Failed! ***\n" << reset;
             }
             pauseScreen();
             
         } else if (choice == "4") {
             // Exit
             clearScreen();
             cout << "\n" << bright_magenta << bold << "*** Thank you for using Event Management System! ***\n" << reset;
             running = false;
             
         } else {
             cout << "\n" << bright_red << "Invalid option! Please try again.\n" << reset;
             pauseScreen();
         }
     }
     
     return 0;
 }
 }
 
 // Display Functions
 void clearScreen() {
     // Clear screen by printing newlines (simple approach)
     for (int i = 0; i < 2; i++) {
         cout << endl;
     }
 }
 
 void displayHeader() {
     cout << bright_cyan << bold << "================================================\n";
     cout << "    EVENT REGISTRATION & TICKETING SYSTEM\n";
     cout << "    Comprehensive Event Management Solution\n";
     cout << "================================================\n" << reset;
 }
 
 void displayMainMenu() {
     cout << bright_blue << bold << "========== MAIN MENU ==========\n" << reset;
     cout << bright_yellow << "1. " << reset << cyan << "Admin Portal\n" << reset;
     cout << bright_yellow << "2. " << reset << cyan << "User Portal\n" << reset;
     cout << bright_yellow << "3. " << reset << cyan << "User Signup\n" << reset;
     cout << bright_yellow << "4. " << reset << red << "Exit\n" << reset;
     cout << bright_blue << "===============================\n" << reset;
     cout << bright_green << "Enter your choice: " << reset;
 }
 
 void displayAdminMenu() {
     cout << bright_magenta << bold << "========== ADMIN DASHBOARD ==========\n" << reset;
     cout << bright_yellow << "1. " << reset << cyan << "Add Event\n" << reset;
     cout << bright_yellow << "2. " << reset << cyan << "View All Events\n" << reset;
     cout << bright_yellow << "3. " << reset << cyan << "Update Event\n" << reset;
     cout << bright_yellow << "4. " << reset << cyan << "Delete Event\n" << reset;
     cout << bright_yellow << "5. " << reset << cyan << "View All Registrations\n" << reset;
     cout << bright_yellow << "6. " << reset << cyan << "Generate Reports\n" << reset;
     cout << bright_yellow << "7. " << reset << cyan << "View All Users\n" << reset;
     cout << bright_yellow << "8. " << reset << cyan << "Delete User\n" << reset;
     cout << bright_yellow << "9. " << reset << red << "Logout\n" << reset;
     cout << bright_magenta << "=====================================\n" << reset;
     cout << bright_green << "Enter your choice: " << reset;
 }
 
 void displayUserMenu() {
     cout << bright_cyan << bold << "========== USER DASHBOARD ==========\n" << reset;
     cout << bright_yellow << "1. " << reset << cyan << "View All Events\n" << reset;
     cout << bright_yellow << "2. " << reset << cyan << "Search Event by Name\n" << reset;
     cout << bright_yellow << "3. " << reset << cyan << "Search Event by Category\n" << reset;
     cout << bright_yellow << "4. " << reset << cyan << "Register & Book Tickets\n" << reset;
     cout << bright_yellow << "5. " << reset << cyan << "My Bookings\n" << reset;
     cout << bright_yellow << "6. " << reset << cyan << "View Ticket by ID\n" << reset;
     cout << bright_yellow << "7. " << reset << red << "Logout\n" << reset;
     cout << bright_cyan << "====================================\n" << reset;
     cout << bright_green << "Enter your choice: " << reset;
 }
 
 string getUserChoice() {
     string choice;
     cin >> choice;
     clearInputBuffer();
     return choice;
 }
 
 void pauseScreen() {
     cout << "\n" << bright_cyan << "Press Enter to continue..." << reset;
     cin.ignore();
     cin.get();
 }
 
 // Authentication Functions
 bool adminLogin() {
     string username, password;
     
     cin.ignore();
     cout << "\n" << bright_magenta << bold << "========== ADMIN LOGIN ==========\n" << reset;
     cout << bright_yellow << "Enter Admin Username: " << reset;
     getline(cin, username);
     while ((int)username.length() == 0) {
         cout << bright_red << "Username cannot be empty! Enter again: " << reset;
         getline(cin, username);
     }
     cout << bright_yellow << "Enter Admin Password: " << reset;
     getline(cin, password);
     while ((int)password.length() == 0) {
         cout << bright_red << "Password cannot be empty! Enter again: " << reset;
         getline(cin, password);
     }
     
     if (username == getAdminUsername() && password == getAdminPassword()) {
         return true;
     }
     return false;
 }
 
 string userLogin(string usernames[], string passwords[], int userCount) {
     string username, password;
     
     cin.ignore();
     cout << bright_yellow << "Enter Username: " << reset;
     getline(cin, username);
     while ((int)username.length() == 0) {
         cout << bright_red << "Username cannot be empty! Enter again: " << reset;
         getline(cin, username);
     }
     cout << bright_yellow << "Enter Password: " << reset;
     getline(cin, password);
     while ((int)password.length() == 0) {
         cout << bright_red << "Password cannot be empty! Enter again: " << reset;
         getline(cin, password);
     }
     
     for (int i = 0; i < userCount; i++) {
         if (usernames[i] == username && passwords[i] == password) {
             return username;
         }
     }
     return "";
 }
 
 bool userSignup(string usernames[], string passwords[], string emails[], int& userCount) {
     if (userCount >= getMaxUsers()) {
         cout << "User limit reached!\n";
         return false;
     }
     
     string username, password, email;
     
     cin.ignore();
     cout << bright_yellow << "Enter Username: " << reset;
     getline(cin, username);
     while ((int)username.length() == 0) {
         cout << bright_red << "Username cannot be empty! Enter again: " << reset;
         getline(cin, username);
     }
     
     if ((int)username.length() < 3) {
         cout << bright_red << "Username must be at least 3 characters!\n" << reset;
         return false;
     }
     
     if (!isUsernameUnique(username, usernames, userCount)) {
         cout << bright_red << "Username already exists!\n" << reset;
         return false;
     }
     
     cout << bright_yellow << "Enter Password: " << reset;
     getline(cin, password);
     while ((int)password.length() == 0) {
         cout << bright_red << "Password cannot be empty! Enter again: " << reset;
         getline(cin, password);
     }
     
     if ((int)password.length() < 4) {
         cout << bright_red << "Password must be at least 4 characters!\n" << reset;
         return false;
     }
     
     cout << bright_yellow << "Enter Email: " << reset;
     getline(cin, email);
     while ((int)email.length() == 0) {
         cout << bright_red << "Email cannot be empty! Enter again: " << reset;
         getline(cin, email);
     }
     
     if (!isValidEmail(email)) {
         cout << bright_red << "Invalid email format!\n" << reset;
         return false;
     }
     
     string result = addUser(username, password, email, usernames, passwords, emails, userCount);
     return true;
 }
 
 // File Handling Functions (TXT Format)
 void loadUsersFromTXT(string usernames[], string passwords[], string emails[], int& userCount) {
     ifstream file("users.txt");
     
     if (!file.is_open()) {
         return;
     }
     
     userCount = 0;
     string line;
     while (userCount < getMaxUsers() && getline(file, line)) {
         // Parse TXT line: username|password|email
         int pipe1 = (int)line.find("|");
         int pipe2 = -1;
         
         if (pipe1 != -1) {
             usernames[userCount] = "";
             for (int i = 0; i < pipe1; i++) {
                 usernames[userCount] += line[i];
             }
             
             for (int i = pipe1 + 1; i < (int)line.length(); i++) {
                 if (line[i] == '|') {
                     pipe2 = i;
                     break;
                 }
             }
             
             if (pipe2 != -1) {
                 passwords[userCount] = "";
                 for (int i = pipe1 + 1; i < pipe2; i++) {
                     passwords[userCount] += line[i];
                 }
                 
                 emails[userCount] = "";
                 for (int i = pipe2 + 1; i < (int)line.length(); i++) {
                     emails[userCount] += line[i];
                 }
                 userCount++;
             }
         }
     }
     
     file.close();
 }
 
 void saveUsersToTXT(string usernames[], string passwords[], string emails[], int userCount) {
     ofstream file("users.txt");
     
     for (int i = 0; i < userCount; i++) {
         file << usernames[i] << "|" << passwords[i] << "|" << emails[i] << endl;
     }
     
     file.close();
 }
 
 void loadEventsFromTXT(string eventNames[], string eventDates[], string eventVenues[], 
                        string eventCategories[], double eventPrices[], int eventCapacities[], 
                        int eventAvailable[], int& eventCount) {
     ifstream file("events.txt");
     
     if (!file.is_open()) {
         return;
     }
     
     eventCount = 0;
     string line;
     while (eventCount < getMaxEvents() && getline(file, line)) {
         // Parse TXT: name|date|venue|category|price|capacity|available
         int pipes[6];
         int pipeIndex = 0;
         
         for (int i = 0; i < (int)line.length() && pipeIndex < 6; i++) {
             if (line[i] == '|') {
                 pipes[pipeIndex] = i;
                 pipeIndex++;
             }
         }
         
         if (pipeIndex == 6) {
             // Extract name
             eventNames[eventCount] = "";
             for (int i = 0; i < pipes[0]; i++) {
                 eventNames[eventCount] += line[i];
             }
             
             // Extract date
             eventDates[eventCount] = "";
             for (int i = pipes[0] + 1; i < pipes[1]; i++) {
                 eventDates[eventCount] += line[i];
             }
             
             // Extract venue
             eventVenues[eventCount] = "";
             for (int i = pipes[1] + 1; i < pipes[2]; i++) {
                 eventVenues[eventCount] += line[i];
             }
             
             // Extract category
             eventCategories[eventCount] = "";
             for (int i = pipes[2] + 1; i < pipes[3]; i++) {
                 eventCategories[eventCount] += line[i];
             }
             
             // Extract price
             string priceStr = "";
             for (int i = pipes[3] + 1; i < pipes[4]; i++) {
                 priceStr += line[i];
             }
             eventPrices[eventCount] = stod(priceStr);
             
             // Extract capacity
             string capStr = "";
             for (int i = pipes[4] + 1; i < pipes[5]; i++) {
                 capStr += line[i];
             }
             eventCapacities[eventCount] = stoi(capStr);
             
             // Extract available
             string availStr = "";
             for (int i = pipes[5] + 1; i < (int)line.length(); i++) {
                 availStr += line[i];
             }
             eventAvailable[eventCount] = stoi(availStr);
             
             eventCount++;
         }
     }
     
     file.close();
 }
 
 void saveEventsToTXT(string eventNames[], string eventDates[], string eventVenues[], 
                      string eventCategories[], double eventPrices[], int eventCapacities[], 
                      int eventAvailable[], int eventCount) {
     ofstream file("events.txt");
     //t0_string is converting event price to string which was in double. When we will read from the file we will use stoi()function to convert from string to integer or stod().
     for (int i = 0; i < eventCount; i++) {
         file << eventNames[i] << "|" << eventDates[i] << "|" << eventVenues[i] << "|"
              << eventCategories[i] << "|" << to_string(eventPrices[i]) << "|"
              << to_string(eventCapacities[i]) << "|" << to_string(eventAvailable[i]) << endl;
     }
     
     file.close();
 }
 
 void loadTicketsFromTXT(int ticketIDs[], string ticketUsernames[], string ticketEmails[], 
                         int ticketEventIDs[], int ticketQuantities[], double ticketCosts[], 
                         string ticketDates[], int& ticketCount) {
     ifstream file("tickets.txt");
     
     if (!file.is_open()) {
         return;
     }
     
     ticketCount = 0;
     string line;
     while (ticketCount < getMaxTickets() && getline(file, line)) {
         // Parse TXT: ticketID|username|email|eventID|quantity|cost|date
         int pipes[6];
         int pipeIndex = 0;
         
         for (int i = 0; i < (int)line.length() && pipeIndex < 6; i++) {
             if (line[i] == '|') {
                 pipes[pipeIndex] = i;
                 pipeIndex++;
             }
         }
         
         if (pipeIndex == 6) {
             // Extract ticketID
             string idStr = "";
             for (int i = 0; i < pipes[0]; i++) {
                 idStr += line[i];
             }
             ticketIDs[ticketCount] = stoi(idStr);
             
             // Extract username
             ticketUsernames[ticketCount] = "";
             for (int i = pipes[0] + 1; i < pipes[1]; i++) {
                 ticketUsernames[ticketCount] += line[i];
             }
             
             // Extract email
             ticketEmails[ticketCount] = "";
             for (int i = pipes[1] + 1; i < pipes[2]; i++) {
                 ticketEmails[ticketCount] += line[i];
             }
             
             // Extract eventID
             string eventIDStr = "";
             for (int i = pipes[2] + 1; i < pipes[3]; i++) {
                 eventIDStr += line[i];
             }
             ticketEventIDs[ticketCount] = stoi(eventIDStr);
             
             // Extract quantity
             string qtyStr = "";
             for (int i = pipes[3] + 1; i < pipes[4]; i++) {
                 qtyStr += line[i];
             }
             ticketQuantities[ticketCount] = stoi(qtyStr);
             
             // Extract cost
             string costStr = "";
             for (int i = pipes[4] + 1; i < pipes[5]; i++) {
                 costStr += line[i];
             }
             ticketCosts[ticketCount] = stod(costStr);
             
             // Extract date
             ticketDates[ticketCount] = "";
             for (int i = pipes[5] + 1; i < (int)line.length(); i++) {
                 ticketDates[ticketCount] += line[i];
             }
             
             ticketCount++;
         }
     }
     
     file.close();
 }
 
 void saveTicketsToTXT(int ticketIDs[], string ticketUsernames[], string ticketEmails[], 
                       int ticketEventIDs[], int ticketQuantities[], double ticketCosts[], 
                       string ticketDates[], int ticketCount) {
     ofstream file("tickets.txt");
     
     for (int i = 0; i < ticketCount; i++) {
         file << to_string(ticketIDs[i]) << "|" << ticketUsernames[i] << "|" 
              << ticketEmails[i] << "|" << to_string(ticketEventIDs[i]) << "|"
              << to_string(ticketQuantities[i]) << "|" << to_string(ticketCosts[i]) 
              << "|" << ticketDates[i] << endl;
     }
     
     file.close();
 }
 
 // Validation Functions
 bool isUsernameUnique(string username, string usernames[], int userCount) {
     for (int i = 0; i < userCount; i++) {
         if (usernames[i] == username) {
             return false;
         }
     }
     return true;
 }
 
 bool isValidEmail(string email) {
     int atPos = -1;
     int dotPos = -1;
     
     for (int i = 0; i < (int)email.length(); i++) {
         if (email[i] == '@') {
             atPos = i;
         }
         if (email[i] == '.' && atPos != -1) {
             dotPos = i;
         }
     }
     
     return (atPos > 0 && dotPos > atPos + 1 && dotPos < (int)email.length() - 1);
 }
 
 bool isValidNumber(string input) {
     if ((int)input.length() == 0) return false;
     
     for (int i = 0; i < (int)input.length(); i++) {
         if (input[i] < '0' || input[i] > '9') {
             if (i == 0 && input[i] == '-') continue;
             if (input[i] == '.' && i > 0) continue;
             return false;
         }
     }
     return true;
 }
 
 int getValidInteger(string prompt) {
     string input;
     int value;
     
     cout << bright_yellow << prompt << reset;
     cin >> input;
     
     while (!isValidNumber(input)) {
         clearInputBuffer();
         cout << bright_red << "Invalid input! Enter a valid number: " << reset;
         cin >> input;
     }
     
     value = stoi(input);
     return value;
 }
 
 double getValidDouble(string prompt) {
     string input;
     double value;
     
     cout << bright_yellow << prompt << reset;
     cin >> input;
     
     bool valid = true;
     int dotCount = 0;
     
     for (int i = 0; i < (int)input.length(); i++) {
         if (input[i] == '.') {
             dotCount++;
             if (dotCount > 1) {
                 valid = false;
                 break;
             }
         } else if (input[i] < '0' || input[i] > '9') {
             if (i == 0 && input[i] == '-') continue;
             valid = false;
             break;
         }
     }
     
     while (!valid) {
         clearInputBuffer();
         cout << bright_red << "Invalid input! Enter a valid number: " << reset;
         cin >> input;
         valid = true;
         dotCount = 0;
         for (int i = 0; i < (int)input.length(); i++) {
             if (input[i] == '.') {
                 dotCount++;
                 if (dotCount > 1) {
                     valid = false;
                     break;
                 }
             } else if (input[i] < '0' || input[i] > '9') {
                 if (i == 0 && input[i] == '-') continue;
                 valid = false;
                 break;
             }
         }
     }
     
     value = stod(input);
     return value;
 }
 
 void clearInputBuffer() {
     cin.clear();
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
 }
 
 // Utility Functions
 string getCurrentDate() {
     // Simple date format - can be enhanced
     return "17-12-2025";
 }
 
 // Constants Functions (Replaced global variables)
 const int getMaxUsers() {
     return 100;
 }
 
 const int getMaxEvents() {
     return 100;
 }
 
 const int getMaxTickets() {
     return 500;
 }
 
 string getAdminUsername() {
     return "admin";
 }
 
 string getAdminPassword() {
     return "admin123";
 }
 
 // Event Management Functions
 string addEvent(string name, string date, string venue, string category, double price, 
                 int capacity, string eventNames[], string eventDates[], string eventVenues[], 
                 string eventCategories[], double eventPrices[], int eventCapacities[], 
                 int eventAvailable[], int& eventCount) {
     if (eventCount >= getMaxEvents()) {
         return "Event limit reached!";
     }
     
     eventNames[eventCount] = name;
     eventDates[eventCount] = date;
     eventVenues[eventCount] = venue;
     eventCategories[eventCount] = category;
     eventPrices[eventCount] = price;
     eventCapacities[eventCount] = capacity;
     eventAvailable[eventCount] = capacity;
     eventCount++;
     
     return "Event added successfully!";
 }
 
 string viewAllEvents(string eventNames[], string eventDates[], string eventVenues[], 
                      string eventCategories[], double eventPrices[], int eventCapacities[], 
                      int eventAvailable[], int eventCount) {
     if (eventCount == 0) {
         return "\nNo events available!";
     }
     
     string result = "\n========== ALL EVENTS ==========\n";
     
     for (int i = 0; i < eventCount; i++) {
         result += "\nEvent #" + to_string(i + 1) + "\n";
         result += "Name: " + eventNames[i] + "\n";
         result += "Date: " + eventDates[i] + "\n";
         result += "Venue: " + eventVenues[i] + "\n";
         result += "Category: " + eventCategories[i] + "\n";
         result += "Price: $" + to_string(eventPrices[i]) + "\n";
         result += "Capacity: " + to_string(eventCapacities[i]) + "\n";
         result += "Available: " + to_string(eventAvailable[i]) + "\n";
         result += "--------------------------------\n";
     }
     
     return result;
 }
 
 string updateEvent(int index, string name, string date, string venue, string category, 
                    double price, int capacity, int available, string eventNames[], 
                    string eventDates[], string eventVenues[], string eventCategories[], 
                    double eventPrices[], int eventCapacities[], int eventAvailable[]) {
     if (index < 0) {
         return "Invalid event index!";
     }
     
     eventNames[index] = name;
     eventDates[index] = date;
     eventVenues[index] = venue;
     eventCategories[index] = category;
     eventPrices[index] = price;
     eventCapacities[index] = capacity;
     eventAvailable[index] = available;
     
     return "Event updated successfully!";
 }
 
 string deleteEvent(int index, string eventNames[], string eventDates[], string eventVenues[], 
                    string eventCategories[], double eventPrices[], int eventCapacities[], 
                    int eventAvailable[], int& eventCount) {
     if (index < 0 || index >= eventCount) {
         return "Invalid event index!";
     }
     
     for (int i = index; i < eventCount - 1; i++) {
         eventNames[i] = eventNames[i + 1];
         eventDates[i] = eventDates[i + 1];
         eventVenues[i] = eventVenues[i + 1];
         eventCategories[i] = eventCategories[i + 1];
         eventPrices[i] = eventPrices[i + 1];
         eventCapacities[i] = eventCapacities[i + 1];
         eventAvailable[i] = eventAvailable[i + 1];
     }
     
     eventCount--;
     return "Event deleted successfully!";
 }
 
 string searchEventByName(string name, string eventNames[], string eventDates[], 
                          string eventVenues[], string eventCategories[], double eventPrices[], 
                          int eventCapacities[], int eventAvailable[], int eventCount) {
     bool found = false;
     string result = "\n========== SEARCH RESULTS ==========\n";
     
     for (int i = 0; i < eventCount; i++) {
         if ((int)eventNames[i].find(name) != -1) {
             found = true;
             result += "\nEvent #" + to_string(i + 1) + "\n";
             result += "Name: " + eventNames[i] + "\n";
             result += "Date: " + eventDates[i] + "\n";
             result += "Venue: " + eventVenues[i] + "\n";
             result += "Category: " + eventCategories[i] + "\n";
             result += "Price: $" + to_string(eventPrices[i]) + "\n";
             result += "Available: " + to_string(eventAvailable[i]) + "/" + to_string(eventCapacities[i]) + "\n";
             result += "--------------------------------\n";
         }
     }
     
     if (!found) {
         return "\nNo events found with that name!";
     }
     
     return result;
 }
 
 string searchEventByCategory(string category, string eventNames[], string eventDates[], 
                              string eventVenues[], string eventCategories[], double eventPrices[], 
                              int eventCapacities[], int eventAvailable[], int eventCount) {
     bool found = false;
     string result = "\n========== SEARCH RESULTS ==========\n";
     
     for (int i = 0; i < eventCount; i++) {
         if ((int)eventCategories[i].find(category) != -1) {
             found = true;
             result += "\nEvent #" + to_string(i + 1) + "\n";
             result += "Name: " + eventNames[i] + "\n";
             result += "Date: " + eventDates[i] + "\n";
             result += "Venue: " + eventVenues[i] + "\n";
             result += "Category: " + eventCategories[i] + "\n";
             result += "Price: $" + to_string(eventPrices[i]) + "\n";
             result += "Available: " + to_string(eventAvailable[i]) + "/" + to_string(eventCapacities[i]) + "\n";
             result += "--------------------------------\n";
         }
     }
     
     if (!found) {
         return "\nNo events found in that category!";
     }
     
     return result;
 }
 
 // User Management Functions
 string addUser(string username, string password, string email, string usernames[], 
                string passwords[], string emails[], int& userCount) {
     if (userCount >= getMaxUsers()) {
         return "User limit reached!";
     }
     
     usernames[userCount] = username;
     passwords[userCount] = password;
     emails[userCount] = email;
     userCount++;
     
     return "User added successfully!";
 }
 
 string deleteUser(int index, string usernames[], string passwords[], string emails[], int& userCount) {
     if (index < 0 || index >= userCount) {
         return "Invalid user index!";
     }
     
     for (int i = index; i < userCount - 1; i++) {
         usernames[i] = usernames[i + 1];
         passwords[i] = passwords[i + 1];
         emails[i] = emails[i + 1];
     }
     
     userCount--;
     return "User deleted successfully!";
 }
 
 string viewAllUsers(string usernames[], string emails[], int userCount) {
     // This function is kept for compatibility but colors are added at call sites
     if (userCount == 0) {
         return "\nNo users registered!";
     }
     
     string result = "\n========== ALL USERS ==========\n";
     
     for (int i = 0; i < userCount; i++) {
         result += "\nUser #" + to_string(i + 1) + "\n";
         result += "Username: " + usernames[i] + "\n";
         result += "Email: " + emails[i] + "\n";
         result += "--------------------------------\n";
     }
     
     return result;
 }
 
 int findUserIndex(string username, string usernames[], int userCount) {
     for (int i = 0; i < userCount; i++) {
         if (usernames[i] == username) {
             return i;
         }
     }
     return -1;
 }
 
 string getUserEmail(string username, string usernames[], string emails[], int userCount) {
     int index = findUserIndex(username, usernames, userCount);
     if (index != -1) {
         return emails[index];
     }
     return "";
 }
 
 // Ticket Management Functions
 int generateTicketID(int ticketIDs[], int ticketCount) {
     int maxID = 1000;
     for (int i = 0; i < ticketCount; i++) {
         if (ticketIDs[i] > maxID) {
             maxID = ticketIDs[i];
         }
     }
     return maxID + 1;
 }
 
 string bookTicket(string username, string email, int eventIndex, int quantity, 
                   string eventNames[], double eventPrices[], int eventAvailable[], 
                   int ticketIDs[], string ticketUsernames[], string ticketEmails[], 
                   int ticketEventIDs[], int ticketQuantities[], double ticketCosts[], 
                   string ticketDates[], int& ticketCount) {
     if (ticketCount >= getMaxTickets()) {
         return "Ticket limit reached!";
     }
     
     if (eventIndex < 0) {
         return "Invalid event index!";
     }
     
     if (quantity <= 0) {
         return "Invalid quantity!";
     }
     
     if (eventAvailable[eventIndex] < quantity) {
         return "Not enough seats available! Available: " + to_string(eventAvailable[eventIndex]);
     }
     
     // Create ticket
     ticketIDs[ticketCount] = generateTicketID(ticketIDs, ticketCount);
     ticketUsernames[ticketCount] = username;
     ticketEmails[ticketCount] = email;
     ticketEventIDs[ticketCount] = eventIndex;
     ticketQuantities[ticketCount] = quantity;
     ticketCosts[ticketCount] = eventPrices[eventIndex] * quantity;
     ticketDates[ticketCount] = getCurrentDate();
     
     // Update available seats
     eventAvailable[eventIndex] -= quantity;
     
     ticketCount++;
     
     string result = "Ticket booked successfully!\n";
     result += "Ticket ID: TKT-" + to_string(ticketIDs[ticketCount - 1]) + "\n";
     result += "Event: " + eventNames[eventIndex] + "\n";
     result += "Quantity: " + to_string(quantity) + "\n";
     result += "Total Cost: $" + to_string(ticketCosts[ticketCount - 1]);
     
     return result;
 }
 
 string viewUserTickets(string username, int ticketIDs[], string ticketUsernames[], 
                        string ticketEmails[], int ticketEventIDs[], int ticketQuantities[], 
                        double ticketCosts[], string ticketDates[], string eventNames[], 
                        int ticketCount, int eventCount) {
     bool found = false;
     
     cout << "\n" << bright_cyan << bold << "========== MY BOOKINGS ==========\n" << reset;
     
     for (int i = 0; i < ticketCount; i++) {
         if (ticketUsernames[i] == username) {
             found = true;
             cout << "\n" << bright_yellow << "Ticket ID: " << reset << bright_cyan << "TKT-" << to_string(ticketIDs[i]) << reset << endl;
             if (ticketEventIDs[i] >= 0 && ticketEventIDs[i] < eventCount) {
                 cout << cyan << "Event: " << reset << bright_white << eventNames[ticketEventIDs[i]] << reset << endl;
             }
             cout << cyan << "Quantity: " << reset << bright_yellow << to_string(ticketQuantities[i]) << reset << endl;
             cout << cyan << "Cost: " << reset << bright_green << "$" << to_string(ticketCosts[i]) << reset << endl;
             cout << cyan << "Booking Date: " << reset << ticketDates[i] << endl;
             cout << grey << "--------------------------------" << reset << endl;
         }
     }
     
     if (!found) {
         return "\nNo bookings found!";
     }
     
     return "";
 }
 
 string viewTicketByID(int ticketID, int ticketIDs[], string ticketUsernames[], 
                       string ticketEmails[], int ticketEventIDs[], int ticketQuantities[], 
                       double ticketCosts[], string ticketDates[], string eventNames[], 
                       int ticketCount, int eventCount) {
     for (int i = 0; i < ticketCount; i++) {
         if (ticketIDs[i] == ticketID) {
             cout << "\n" << bright_green << bold << "========== OFFICIAL TICKET ==========\n" << reset;
             cout << bright_yellow << "Ticket ID: " << reset << bright_cyan << "TKT-" << to_string(ticketIDs[i]) << reset << endl;
             cout << cyan << "Name: " << reset << bright_white << ticketUsernames[i] << reset << endl;
             cout << cyan << "Email: " << reset << ticketEmails[i] << endl;
             if (ticketEventIDs[i] >= 0 && ticketEventIDs[i] < eventCount) {
                 cout << cyan << "Event: " << reset << bright_white << eventNames[ticketEventIDs[i]] << reset << endl;
             }
             cout << cyan << "Quantity: " << reset << bright_yellow << to_string(ticketQuantities[i]) << reset << endl;
             cout << cyan << "Total Cost: " << reset << bright_green << "$" << to_string(ticketCosts[i]) << reset << endl;
             cout << cyan << "Booking Date: " << reset << ticketDates[i] << endl;
             cout << bright_green << "=====================================\n" << reset;
             return "";
         }
     }
     
     return "\nTicket not found!";
 }
 
 string viewAllRegistrations(int ticketIDs[], string ticketUsernames[], string ticketEmails[], 
                             int ticketEventIDs[], int ticketQuantities[], double ticketCosts[], 
                             string ticketDates[], string eventNames[], int ticketCount, 
                             int eventCount) {
     cout << "\n" << bright_magenta << bold << "========== ALL REGISTRATIONS ==========\n" << reset;
     
     if (ticketCount == 0) {
         return "\nNo registrations found!";
     }
     
     for (int i = 0; i < ticketCount; i++) {
         cout << "\n" << bright_yellow << "Registration #" << (i + 1) << reset << endl;
         cout << cyan << "Ticket ID: " << reset << bright_cyan << "TKT-" << to_string(ticketIDs[i]) << reset << endl;
         cout << cyan << "User: " << reset << bright_white << ticketUsernames[i] << reset << endl;
         cout << cyan << "Email: " << reset << ticketEmails[i] << endl;
         if (ticketEventIDs[i] >= 0 && ticketEventIDs[i] < eventCount) {
             cout << cyan << "Event: " << reset << bright_white << eventNames[ticketEventIDs[i]] << reset << endl;
         }
         cout << cyan << "Quantity: " << reset << bright_yellow << to_string(ticketQuantities[i]) << reset << endl;
         cout << cyan << "Cost: " << reset << bright_green << "$" << to_string(ticketCosts[i]) << reset << endl;
         cout << cyan << "Date: " << reset << ticketDates[i] << endl;
         cout << grey << "--------------------------------" << reset << endl;
     }
     
     return "";
 }
 
 // Report Functions
 void generateReports(int ticketIDs[], string ticketUsernames[], int ticketEventIDs[], 
                      int ticketQuantities[], double ticketCosts[], string eventNames[], 
                      double eventPrices[], int ticketCount, int eventCount) {
     cout << "\n" << bright_magenta << bold << "========== SALES REPORTS & ANALYTICS ==========\n" << reset;
     
     double totalRevenue = calculateTotalRevenue(ticketIDs, ticketCosts, ticketCount);
     int totalBookings = calculateTotalBookings(ticketIDs, ticketCount);
     
     cout << "\n" << bright_cyan << bold << "--- Overall Statistics ---\n" << reset;
     cout << cyan << "Total Revenue: " << reset << bright_green << "$" << to_string(totalRevenue) << reset << endl;
     cout << cyan << "Total Bookings: " << reset << bright_yellow << to_string(totalBookings) << reset << endl;
     cout << cyan << "Total Events: " << reset << bright_yellow << to_string(eventCount) << reset << endl;
     
     cout << "\n" << bright_cyan << bold << "--- Event-wise Statistics ---\n" << reset;
     for (int i = 0; i < eventCount; i++) {
         int bookings = calculateEventBookings(i, ticketEventIDs, ticketCount);
         double revenue = 0.0;
         
         for (int j = 0; j < ticketCount; j++) {
             if (ticketEventIDs[j] == i) {
                 revenue += ticketCosts[j];
             }
         }
         
         cout << "\n" << bright_yellow << "Event: " << reset << bright_white << eventNames[i] << reset << endl;
         cout << cyan << "Bookings: " << reset << to_string(bookings) << endl;
         cout << cyan << "Revenue: " << reset << bright_green << "$" << to_string(revenue) << reset << endl;
     }
     
     cout << "\n" << bright_magenta << "==========================================\n" << reset;
 }
 
 double calculateTotalRevenue(int ticketIDs[], double ticketCosts[], int ticketCount) {
     double total = 0.0;
     for (int i = 0; i < ticketCount; i++) {
         total += ticketCosts[i];
     }
     return total;
 }
 
 int calculateTotalBookings(int ticketIDs[], int ticketCount) {
     return ticketCount;
 }
 
 int calculateEventBookings(int eventIndex, int ticketEventIDs[], int ticketCount) {
     int count = 0;
     for (int i = 0; i < ticketCount; i++) {
         if (ticketEventIDs[i] == eventIndex) {
             count++;
         }
     }
     return count;
 }
 
