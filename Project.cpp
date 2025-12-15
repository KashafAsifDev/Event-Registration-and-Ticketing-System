/*
 * Event Registration and Ticketing System
 * A comprehensive C++ console application for event management
 * 
 * Features:
 * - Admin portal: Manage events, users, view reports
 * - User portal: Browse events, book tickets, view bookings
 * - File persistence using CSV format
 * - Ticket system with unique IDs
 * - Revenue analytics and reporting
 */

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "termcolor/include/termcolor/termcolor.hpp"
using namespace std;
using namespace termcolor;

// Constants
const int MAX_USERS = 100;
const int MAX_EVENTS = 100;
const int MAX_TICKETS = 500;
const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

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

// Function Prototypes - File Handling (CSV Format)
void loadUsersFromCSV(string usernames[], string passwords[], string emails[], int& userCount);
void saveUsersToCSV(string usernames[], string passwords[], string emails[], int userCount);
void loadEventsFromCSV(string eventNames[], string eventDates[], string eventVenues[], 
                       string eventCategories[], double eventPrices[], int eventCapacities[], 
                       int eventAvailable[], int& eventCount);
void saveEventsToCSV(string eventNames[], string eventDates[], string eventVenues[], 
                     string eventCategories[], double eventPrices[], int eventCapacities[], 
                     int eventAvailable[], int eventCount);
void loadTicketsFromCSV(int ticketIDs[], string ticketUsernames[], string ticketEmails[], 
                        int ticketEventIDs[], int ticketQuantities[], double ticketCosts[], 
                        string ticketDates[], int& ticketCount);
void saveTicketsToCSV(int ticketIDs[], string ticketUsernames[], string ticketEmails[], 
                      int ticketEventIDs[], int ticketQuantities[], double ticketCosts[], 
                      string ticketDates[], int ticketCount);

// Function Prototypes - Validation Functions
bool isUsernameUnique(string username, string usernames[], int userCount);
bool isValidEmail(string email);
bool isValidNumber(string input);
int getValidInteger(string prompt);
double getValidDouble(string prompt);
void clearInputBuffer();

// Function Prototypes - String Utility Functions
int stringLength(string str);
bool stringCompare(string str1, string str2);
int stringFind(string str, string search);
string intToString(int num);
string doubleToString(double num);
int stringToInt(string str);
double stringToDouble(string str);
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
    string usernames[MAX_USERS];
    string passwords[MAX_USERS];
    string emails[MAX_USERS];
    int userCount = 0;
    
    string eventNames[MAX_EVENTS];
    string eventDates[MAX_EVENTS];
    string eventVenues[MAX_EVENTS];
    string eventCategories[MAX_EVENTS];
    double eventPrices[MAX_EVENTS];
    int eventCapacities[MAX_EVENTS];
    int eventAvailable[MAX_EVENTS];
    int eventCount = 0;
    
    int ticketIDs[MAX_TICKETS];
    string ticketUsernames[MAX_TICKETS];
    string ticketEmails[MAX_TICKETS];
    int ticketEventIDs[MAX_TICKETS];
    int ticketQuantities[MAX_TICKETS];
    double ticketCosts[MAX_TICKETS];
    string ticketDates[MAX_TICKETS];
    int ticketCount = 0;
    
    // Load data from CSV files
    loadUsersFromCSV(usernames, passwords, emails, userCount);
    loadEventsFromCSV(eventNames, eventDates, eventVenues, eventCategories, eventPrices, 
                     eventCapacities, eventAvailable, eventCount);
    loadTicketsFromCSV(ticketIDs, ticketUsernames, ticketEmails, ticketEventIDs, 
                      ticketQuantities, ticketCosts, ticketDates, ticketCount);
    
    clearScreen();
    displayHeader();
    
    bool running = true;
    
    while (running) {
        displayMainMenu();
        string choice = getUserChoice();
        
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
                        cout << bright_yellow << "Enter Event Date (DD-MM-YYYY): " << reset;
                        getline(cin, date);
                        cout << bright_yellow << "Enter Event Venue: " << reset;
                        getline(cin, venue);
                        cout << bright_yellow << "Enter Event Category (Music/Conference/Sports/Other): " << reset;
                        getline(cin, category);
                        price = getValidDouble("Enter Ticket Price: $");
                        capacity = getValidInteger("Enter Event Capacity: ");
                        
                        string result = addEvent(name, date, venue, category, price, capacity, 
                                                eventNames, eventDates, eventVenues, 
                                                eventCategories, eventPrices, eventCapacities, 
                                                eventAvailable, eventCount);
                        cout << "\n" << bright_green << result << reset << endl;
                        saveEventsToCSV(eventNames, eventDates, eventVenues, eventCategories, 
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
                                cout << cyan << "Price: " << reset << bright_green << "$" << doubleToString(eventPrices[i]) << reset << endl;
                                cout << cyan << "Capacity: " << reset << intToString(eventCapacities[i]) << endl;
                                cout << cyan << "Available: " << reset << bright_yellow << intToString(eventAvailable[i]) << reset << endl;
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
                                cout << cyan << "Price: " << reset << bright_green << "$" << doubleToString(eventPrices[i]) << reset << endl;
                                cout << cyan << "Capacity: " << reset << intToString(eventCapacities[i]) << endl;
                                cout << cyan << "Available: " << reset << bright_yellow << intToString(eventAvailable[i]) << reset << endl;
                                cout << grey << "--------------------------------" << reset << endl;
                            }
                        }
                        
                        if (eventCount > 0) {
                            int index = getValidInteger("\nEnter Event Number to Update (0 to cancel): ");
                            
                            if (index > 0 && index <= eventCount) {
                                string name, date, venue, category;
                                double price;
                                int capacity, available;
                                
                                cin.ignore();
                                cout << bright_yellow << "Enter New Event Name: " << reset;
                                getline(cin, name);
                                cout << bright_yellow << "Enter New Event Date: " << reset;
                                getline(cin, date);
                                cout << bright_yellow << "Enter New Event Venue: " << reset;
                                getline(cin, venue);
                                cout << bright_yellow << "Enter New Event Category: " << reset;
                                getline(cin, category);
                                price = getValidDouble("Enter New Ticket Price: $");
                                capacity = getValidInteger("Enter New Event Capacity: ");
                                available = getValidInteger("Enter Available Seats: ");
                                
                                string result = updateEvent(index - 1, name, date, venue, category, 
                                                            price, capacity, available, eventNames, 
                                                            eventDates, eventVenues, eventCategories, 
                                                            eventPrices, eventCapacities, eventAvailable);
                                cout << "\n" << bright_green << result << reset << endl;
                                saveEventsToCSV(eventNames, eventDates, eventVenues, eventCategories, 
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
                                cout << cyan << "Price: " << reset << bright_green << "$" << doubleToString(eventPrices[i]) << reset << endl;
                                cout << cyan << "Capacity: " << reset << intToString(eventCapacities[i]) << endl;
                                cout << cyan << "Available: " << reset << bright_yellow << intToString(eventAvailable[i]) << reset << endl;
                                cout << grey << "--------------------------------" << reset << endl;
                            }
                        }
                        
                        if (eventCount > 0) {
                            int index = getValidInteger("\nEnter Event Number to Delete (0 to cancel): ");
                            
                            if (index > 0 && index <= eventCount) {
                                string result = deleteEvent(index - 1, eventNames, eventDates, 
                                                           eventVenues, eventCategories, eventPrices, 
                                                           eventCapacities, eventAvailable, eventCount);
                                cout << "\n" << bright_red << result << reset << endl;
                                saveEventsToCSV(eventNames, eventDates, eventVenues, eventCategories, 
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
                            
                            if (index > 0 && index <= userCount) {
                                string result = deleteUser(index - 1, usernames, passwords, emails, userCount);
                                cout << "\n" << result << endl;
                                saveUsersToCSV(usernames, passwords, emails, userCount);
                            }
                        }
                        pauseScreen();
                        
                    } else if (adminChoice == "9") {
                        // Logout
                        clearScreen();
                        cout << "\n" << bright_yellow << "*** Admin Logged Out ***\n" << reset;
                        pauseScreen();
                        adminSession = false;
                        
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
                                cout << cyan << "Price: " << reset << bright_green << "$" << doubleToString(eventPrices[i]) << reset << endl;
                                cout << cyan << "Capacity: " << reset << intToString(eventCapacities[i]) << endl;
                                cout << cyan << "Available: " << reset << bright_yellow << intToString(eventAvailable[i]) << reset << endl;
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
                        
                        string result = searchEventByName(searchName, eventNames, eventDates, 
                                                          eventVenues, eventCategories, eventPrices, 
                                                          eventCapacities, eventAvailable, eventCount);
                        if (stringFind(result, "No events found") != -1) {
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
                        
                        string result = searchEventByCategory(category, eventNames, eventDates, 
                                                              eventVenues, eventCategories, eventPrices, 
                                                              eventCapacities, eventAvailable, eventCount);
                        if (stringFind(result, "No events found") != -1) {
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
                                cout << cyan << "Price: " << reset << bright_green << "$" << doubleToString(eventPrices[i]) << reset << endl;
                                cout << cyan << "Capacity: " << reset << intToString(eventCapacities[i]) << endl;
                                cout << cyan << "Available: " << reset << bright_yellow << intToString(eventAvailable[i]) << reset << endl;
                                cout << grey << "--------------------------------" << reset << endl;
                            }
                        }
                        
                        if (eventCount > 0) {
                            int eventIndex = getValidInteger("\nEnter Event Number to Book (0 to cancel): ");
                            
                            if (eventIndex > 0 && eventIndex <= eventCount) {
                                int quantity = getValidInteger("Enter Number of Tickets: ");
                                
                                string result = bookTicket(loggedInUser, userEmail, eventIndex - 1, quantity, 
                                                          eventNames, eventPrices, eventAvailable, 
                                                          ticketIDs, ticketUsernames, ticketEmails, 
                                                          ticketEventIDs, ticketQuantities, ticketCosts, 
                                                          ticketDates, ticketCount);
                                cout << "\n" << bright_green << result << reset << endl;
                                saveTicketsToCSV(ticketIDs, ticketUsernames, ticketEmails, 
                                                ticketEventIDs, ticketQuantities, ticketCosts, 
                                                ticketDates, ticketCount);
                                saveEventsToCSV(eventNames, eventDates, eventVenues, eventCategories, 
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
                        int ticketID = getValidInteger("Enter Ticket ID to View: ");
                        string ticket = viewTicketByID(ticketID, ticketIDs, ticketUsernames, 
                                                       ticketEmails, ticketEventIDs, ticketQuantities, 
                                                       ticketCosts, ticketDates, eventNames, 
                                                       ticketCount, eventCount);
                        if (ticket != "") {
                            cout << bright_red << ticket << reset << endl;
                        }
                        pauseScreen();
                        
                    } else if (userChoice == "7") {
                        // Logout
                        clearScreen();
                        cout << "\n" << bright_yellow << "*** User Logged Out ***\n" << reset;
                        pauseScreen();
                        userSession = false;
                        
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
                saveUsersToCSV(usernames, passwords, emails, userCount);
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
    cout << bright_yellow << "Enter Admin Password: " << reset;
    getline(cin, password);
    
    if (stringCompare(username, ADMIN_USERNAME) && stringCompare(password, ADMIN_PASSWORD)) {
        return true;
    }
    return false;
}

string userLogin(string usernames[], string passwords[], int userCount) {
    string username, password;
    
    cin.ignore();
    cout << bright_yellow << "Enter Username: " << reset;
    getline(cin, username);
    cout << bright_yellow << "Enter Password: " << reset;
    getline(cin, password);
    
    for (int i = 0; i < userCount; i++) {
        if (stringCompare(usernames[i], username) && stringCompare(passwords[i], password)) {
            return username;
        }
    }
    return "";
}

bool userSignup(string usernames[], string passwords[], string emails[], int& userCount) {
    if (userCount >= MAX_USERS) {
        cout << "User limit reached!\n";
        return false;
    }
    
    string username, password, email;
    
    cin.ignore();
    cout << bright_yellow << "Enter Username: " << reset;
    getline(cin, username);
    
    if (!isUsernameUnique(username, usernames, userCount)) {
        cout << bright_red << "Username already exists!\n" << reset;
        return false;
    }
    
    cout << bright_yellow << "Enter Password: " << reset;
    getline(cin, password);
    
    if (stringLength(password) < 4) {
        cout << bright_red << "Password must be at least 4 characters!\n" << reset;
        return false;
    }
    
    cout << bright_yellow << "Enter Email: " << reset;
    getline(cin, email);
    
    if (!isValidEmail(email)) {
        cout << bright_red << "Invalid email format!\n" << reset;
        return false;
    }
    
    string result = addUser(username, password, email, usernames, passwords, emails, userCount);
    return true;
}

// File Handling Functions (CSV Format)
void loadUsersFromCSV(string usernames[], string passwords[], string emails[], int& userCount) {
    ifstream file("users.csv");
    
    if (!file.is_open()) {
        return;
    }
    
    userCount = 0;
    string line;
    while (userCount < MAX_USERS && getline(file, line)) {
        // Parse CSV line: username,password,email
        int comma1 = stringFind(line, ",");
        int comma2 = -1;
        
        if (comma1 != -1) {
            usernames[userCount] = "";
            for (int i = 0; i < comma1; i++) {
                usernames[userCount] += line[i];
            }
            
            for (int i = comma1 + 1; i < stringLength(line); i++) {
                if (line[i] == ',') {
                    comma2 = i;
                    break;
                }
            }
            
            if (comma2 != -1) {
                passwords[userCount] = "";
                for (int i = comma1 + 1; i < comma2; i++) {
                    passwords[userCount] += line[i];
                }
                
                emails[userCount] = "";
                for (int i = comma2 + 1; i < stringLength(line); i++) {
                    emails[userCount] += line[i];
                }
                userCount++;
            }
        }
    }
    
    file.close();
}

void saveUsersToCSV(string usernames[], string passwords[], string emails[], int userCount) {
    ofstream file("users.csv");
    
    for (int i = 0; i < userCount; i++) {
        file << usernames[i] << "," << passwords[i] << "," << emails[i] << endl;
    }
    
    file.close();
}

void loadEventsFromCSV(string eventNames[], string eventDates[], string eventVenues[], 
                       string eventCategories[], double eventPrices[], int eventCapacities[], 
                       int eventAvailable[], int& eventCount) {
    ifstream file("events.csv");
    
    if (!file.is_open()) {
        return;
    }
    
    eventCount = 0;
    string line;
    while (eventCount < MAX_EVENTS && getline(file, line)) {
        // Parse CSV: name,date,venue,category,price,capacity,available
        int commas[6];
        int commaIndex = 0;
        
        for (int i = 0; i < stringLength(line) && commaIndex < 6; i++) {
            if (line[i] == ',') {
                commas[commaIndex] = i;
                commaIndex++;
            }
        }
        
        if (commaIndex == 6) {
            // Extract name
            eventNames[eventCount] = "";
            for (int i = 0; i < commas[0]; i++) {
                eventNames[eventCount] += line[i];
            }
            
            // Extract date
            eventDates[eventCount] = "";
            for (int i = commas[0] + 1; i < commas[1]; i++) {
                eventDates[eventCount] += line[i];
            }
            
            // Extract venue
            eventVenues[eventCount] = "";
            for (int i = commas[1] + 1; i < commas[2]; i++) {
                eventVenues[eventCount] += line[i];
            }
            
            // Extract category
            eventCategories[eventCount] = "";
            for (int i = commas[2] + 1; i < commas[3]; i++) {
                eventCategories[eventCount] += line[i];
            }
            
            // Extract price
            string priceStr = "";
            for (int i = commas[3] + 1; i < commas[4]; i++) {
                priceStr += line[i];
            }
            eventPrices[eventCount] = stringToDouble(priceStr);
            
            // Extract capacity
            string capStr = "";
            for (int i = commas[4] + 1; i < commas[5]; i++) {
                capStr += line[i];
            }
            eventCapacities[eventCount] = stringToInt(capStr);
            
            // Extract available
            string availStr = "";
            for (int i = commas[5] + 1; i < stringLength(line); i++) {
                availStr += line[i];
            }
            eventAvailable[eventCount] = stringToInt(availStr);
            
            eventCount++;
        }
    }
    
    file.close();
}

void saveEventsToCSV(string eventNames[], string eventDates[], string eventVenues[], 
                     string eventCategories[], double eventPrices[], int eventCapacities[], 
                     int eventAvailable[], int eventCount) {
    ofstream file("events.csv");
    
    for (int i = 0; i < eventCount; i++) {
        file << eventNames[i] << "," << eventDates[i] << "," << eventVenues[i] << ","
             << eventCategories[i] << "," << doubleToString(eventPrices[i]) << ","
             << intToString(eventCapacities[i]) << "," << intToString(eventAvailable[i]) << endl;
    }
    
    file.close();
}

void loadTicketsFromCSV(int ticketIDs[], string ticketUsernames[], string ticketEmails[], 
                        int ticketEventIDs[], int ticketQuantities[], double ticketCosts[], 
                        string ticketDates[], int& ticketCount) {
    ifstream file("tickets.csv");
    
    if (!file.is_open()) {
        return;
    }
    
    ticketCount = 0;
    string line;
    while (ticketCount < MAX_TICKETS && getline(file, line)) {
        // Parse CSV: ticketID,username,email,eventID,quantity,cost,date
        int commas[6];
        int commaIndex = 0;
        
        for (int i = 0; i < stringLength(line) && commaIndex < 6; i++) {
            if (line[i] == ',') {
                commas[commaIndex] = i;
                commaIndex++;
            }
        }
        
        if (commaIndex == 6) {
            // Extract ticketID
            string idStr = "";
            for (int i = 0; i < commas[0]; i++) {
                idStr += line[i];
            }
            ticketIDs[ticketCount] = stringToInt(idStr);
            
            // Extract username
            ticketUsernames[ticketCount] = "";
            for (int i = commas[0] + 1; i < commas[1]; i++) {
                ticketUsernames[ticketCount] += line[i];
            }
            
            // Extract email
            ticketEmails[ticketCount] = "";
            for (int i = commas[1] + 1; i < commas[2]; i++) {
                ticketEmails[ticketCount] += line[i];
            }
            
            // Extract eventID
            string eventIDStr = "";
            for (int i = commas[2] + 1; i < commas[3]; i++) {
                eventIDStr += line[i];
            }
            ticketEventIDs[ticketCount] = stringToInt(eventIDStr);
            
            // Extract quantity
            string qtyStr = "";
            for (int i = commas[3] + 1; i < commas[4]; i++) {
                qtyStr += line[i];
            }
            ticketQuantities[ticketCount] = stringToInt(qtyStr);
            
            // Extract cost
            string costStr = "";
            for (int i = commas[4] + 1; i < commas[5]; i++) {
                costStr += line[i];
            }
            ticketCosts[ticketCount] = stringToDouble(costStr);
            
            // Extract date
            ticketDates[ticketCount] = "";
            for (int i = commas[5] + 1; i < stringLength(line); i++) {
                ticketDates[ticketCount] += line[i];
            }
            
            ticketCount++;
        }
    }
    
    file.close();
}

void saveTicketsToCSV(int ticketIDs[], string ticketUsernames[], string ticketEmails[], 
                      int ticketEventIDs[], int ticketQuantities[], double ticketCosts[], 
                      string ticketDates[], int ticketCount) {
    ofstream file("tickets.csv");
    
    for (int i = 0; i < ticketCount; i++) {
        file << intToString(ticketIDs[i]) << "," << ticketUsernames[i] << "," 
             << ticketEmails[i] << "," << intToString(ticketEventIDs[i]) << ","
             << intToString(ticketQuantities[i]) << "," << doubleToString(ticketCosts[i]) 
             << "," << ticketDates[i] << endl;
    }
    
    file.close();
}

// Validation Functions
bool isUsernameUnique(string username, string usernames[], int userCount) {
    for (int i = 0; i < userCount; i++) {
        if (stringCompare(usernames[i], username)) {
            return false;
        }
    }
    return true;
}

bool isValidEmail(string email) {
    int atPos = -1;
    int dotPos = -1;
    
    for (int i = 0; i < stringLength(email); i++) {
        if (email[i] == '@') {
            atPos = i;
        }
        if (email[i] == '.' && atPos != -1) {
            dotPos = i;
        }
    }
    
    return (atPos > 0 && dotPos > atPos + 1 && dotPos < stringLength(email) - 1);
}

bool isValidNumber(string input) {
    if (stringLength(input) == 0) return false;
    
    for (int i = 0; i < stringLength(input); i++) {
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
    
    value = stringToInt(input);
    return value;
}

double getValidDouble(string prompt) {
    string input;
    double value;
    
    cout << bright_yellow << prompt << reset;
    cin >> input;
    
    bool valid = true;
    int dotCount = 0;
    
    for (int i = 0; i < stringLength(input); i++) {
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
        for (int i = 0; i < stringLength(input); i++) {
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
    
    value = stringToDouble(input);
    return value;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// String Utility Functions
int stringLength(string str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

bool stringCompare(string str1, string str2) {
    if (stringLength(str1) != stringLength(str2)) {
        return false;
    }
    
    for (int i = 0; i < stringLength(str1); i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

int stringFind(string str, string search) {
    int strLen = stringLength(str);
    int searchLen = stringLength(search);
    
    for (int i = 0; i <= strLen - searchLen; i++) {
        bool found = true;
        for (int j = 0; j < searchLen; j++) {
            if (str[i + j] != search[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return -1;
}

string intToString(int num) {
    if (num == 0) return "0";
    
    bool negative = false;
    if (num < 0) {
        negative = true;
        num = -num;
    }
    
    string result = "";
    while (num > 0) {
        char digit = '0' + (num % 10);
        result = digit + result;
        num = num / 10;
    }
    
    if (negative) {
        result = "-" + result;
    }
    
    return result;
}

string doubleToString(double num) {
    // Simple conversion for display
    int intPart = (int)num;
    int decimalPart = (int)((num - intPart) * 100);
    
    string result = intToString(intPart);
    if (decimalPart > 0) {
        result += ".";
        if (decimalPart < 10) {
            result += "0";
        }
        result += intToString(decimalPart);
    }
    
    return result;
}

int stringToInt(string str) {
    int result = 0;
    int start = 0;
    bool negative = false;
    
    if (stringLength(str) > 0 && str[0] == '-') {
        negative = true;
        start = 1;
    }
    
    for (int i = start; i < stringLength(str); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    
    if (negative) {
        result = -result;
    }
    
    return result;
}

double stringToDouble(string str) {
    double result = 0.0;
    int start = 0;
    bool negative = false;
    int dotPos = -1;
    
    if (stringLength(str) > 0 && str[0] == '-') {
        negative = true;
        start = 1;
    }
    
    // Find decimal point
    for (int i = start; i < stringLength(str); i++) {
        if (str[i] == '.') {
            dotPos = i;
            break;
        }
    }
    
    // Convert integer part
    int endPos = (dotPos == -1) ? stringLength(str) : dotPos;
    for (int i = start; i < endPos; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    
    // Convert decimal part
    if (dotPos != -1) {
        double decimal = 0.0;
        double divisor = 10.0;
        for (int i = dotPos + 1; i < stringLength(str); i++) {
            if (str[i] >= '0' && str[i] <= '9') {
                decimal += (str[i] - '0') / divisor;
                divisor *= 10.0;
            }
        }
        result += decimal;
    }
    
    if (negative) {
        result = -result;
    }
    
    return result;
}

string getCurrentDate() {
    // Simple date format - can be enhanced
    return "01-01-2025";
}

// Event Management Functions
string addEvent(string name, string date, string venue, string category, double price, 
                int capacity, string eventNames[], string eventDates[], string eventVenues[], 
                string eventCategories[], double eventPrices[], int eventCapacities[], 
                int eventAvailable[], int& eventCount) {
    if (eventCount >= MAX_EVENTS) {
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
        result += "\nEvent #" + intToString(i + 1) + "\n";
        result += "Name: " + eventNames[i] + "\n";
        result += "Date: " + eventDates[i] + "\n";
        result += "Venue: " + eventVenues[i] + "\n";
        result += "Category: " + eventCategories[i] + "\n";
        result += "Price: $" + doubleToString(eventPrices[i]) + "\n";
        result += "Capacity: " + intToString(eventCapacities[i]) + "\n";
        result += "Available: " + intToString(eventAvailable[i]) + "\n";
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
        if (stringFind(eventNames[i], name) != -1) {
            found = true;
            result += "\nEvent #" + intToString(i + 1) + "\n";
            result += "Name: " + eventNames[i] + "\n";
            result += "Date: " + eventDates[i] + "\n";
            result += "Venue: " + eventVenues[i] + "\n";
            result += "Category: " + eventCategories[i] + "\n";
            result += "Price: $" + doubleToString(eventPrices[i]) + "\n";
            result += "Available: " + intToString(eventAvailable[i]) + "/" + intToString(eventCapacities[i]) + "\n";
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
        if (stringFind(eventCategories[i], category) != -1) {
            found = true;
            result += "\nEvent #" + intToString(i + 1) + "\n";
            result += "Name: " + eventNames[i] + "\n";
            result += "Date: " + eventDates[i] + "\n";
            result += "Venue: " + eventVenues[i] + "\n";
            result += "Category: " + eventCategories[i] + "\n";
            result += "Price: $" + doubleToString(eventPrices[i]) + "\n";
            result += "Available: " + intToString(eventAvailable[i]) + "/" + intToString(eventCapacities[i]) + "\n";
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
    if (userCount >= MAX_USERS) {
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
        result += "\nUser #" + intToString(i + 1) + "\n";
        result += "Username: " + usernames[i] + "\n";
        result += "Email: " + emails[i] + "\n";
        result += "--------------------------------\n";
    }
    
    return result;
}

int findUserIndex(string username, string usernames[], int userCount) {
    for (int i = 0; i < userCount; i++) {
        if (stringCompare(usernames[i], username)) {
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
    if (ticketCount >= MAX_TICKETS) {
        return "Ticket limit reached!";
    }
    
    if (eventIndex < 0) {
        return "Invalid event index!";
    }
    
    if (quantity <= 0) {
        return "Invalid quantity!";
    }
    
    if (eventAvailable[eventIndex] < quantity) {
        return "Not enough seats available! Available: " + intToString(eventAvailable[eventIndex]);
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
    result += "Ticket ID: TKT-" + intToString(ticketIDs[ticketCount - 1]) + "\n";
    result += "Event: " + eventNames[eventIndex] + "\n";
    result += "Quantity: " + intToString(quantity) + "\n";
    result += "Total Cost: $" + doubleToString(ticketCosts[ticketCount - 1]);
    
    return result;
}

string viewUserTickets(string username, int ticketIDs[], string ticketUsernames[], 
                       string ticketEmails[], int ticketEventIDs[], int ticketQuantities[], 
                       double ticketCosts[], string ticketDates[], string eventNames[], 
                       int ticketCount, int eventCount) {
    bool found = false;
    
    cout << "\n" << bright_cyan << bold << "========== MY BOOKINGS ==========\n" << reset;
    
    for (int i = 0; i < ticketCount; i++) {
        if (stringCompare(ticketUsernames[i], username)) {
            found = true;
            cout << "\n" << bright_yellow << "Ticket ID: " << reset << bright_cyan << "TKT-" << intToString(ticketIDs[i]) << reset << endl;
            if (ticketEventIDs[i] >= 0 && ticketEventIDs[i] < eventCount) {
                cout << cyan << "Event: " << reset << bright_white << eventNames[ticketEventIDs[i]] << reset << endl;
            }
            cout << cyan << "Quantity: " << reset << bright_yellow << intToString(ticketQuantities[i]) << reset << endl;
            cout << cyan << "Cost: " << reset << bright_green << "$" << doubleToString(ticketCosts[i]) << reset << endl;
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
            cout << bright_yellow << "Ticket ID: " << reset << bright_cyan << "TKT-" << intToString(ticketIDs[i]) << reset << endl;
            cout << cyan << "Name: " << reset << bright_white << ticketUsernames[i] << reset << endl;
            cout << cyan << "Email: " << reset << ticketEmails[i] << endl;
            if (ticketEventIDs[i] >= 0 && ticketEventIDs[i] < eventCount) {
                cout << cyan << "Event: " << reset << bright_white << eventNames[ticketEventIDs[i]] << reset << endl;
            }
            cout << cyan << "Quantity: " << reset << bright_yellow << intToString(ticketQuantities[i]) << reset << endl;
            cout << cyan << "Total Cost: " << reset << bright_green << "$" << doubleToString(ticketCosts[i]) << reset << endl;
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
        cout << cyan << "Ticket ID: " << reset << bright_cyan << "TKT-" << intToString(ticketIDs[i]) << reset << endl;
        cout << cyan << "User: " << reset << bright_white << ticketUsernames[i] << reset << endl;
        cout << cyan << "Email: " << reset << ticketEmails[i] << endl;
        if (ticketEventIDs[i] >= 0 && ticketEventIDs[i] < eventCount) {
            cout << cyan << "Event: " << reset << bright_white << eventNames[ticketEventIDs[i]] << reset << endl;
        }
        cout << cyan << "Quantity: " << reset << bright_yellow << intToString(ticketQuantities[i]) << reset << endl;
        cout << cyan << "Cost: " << reset << bright_green << "$" << doubleToString(ticketCosts[i]) << reset << endl;
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
    cout << cyan << "Total Revenue: " << reset << bright_green << "$" << doubleToString(totalRevenue) << reset << endl;
    cout << cyan << "Total Bookings: " << reset << bright_yellow << intToString(totalBookings) << reset << endl;
    cout << cyan << "Total Events: " << reset << bright_yellow << intToString(eventCount) << reset << endl;
    
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
        cout << cyan << "Bookings: " << reset << intToString(bookings) << endl;
        cout << cyan << "Revenue: " << reset << bright_green << "$" << doubleToString(revenue) << reset << endl;
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
