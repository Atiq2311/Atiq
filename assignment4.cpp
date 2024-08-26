#include <iostream>
#include <string>

using namespace std;

// Base class for library items
class Item {
protected:
    int itemID;
    string title;
    bool available;

public:
    Item(int id, string t) : itemID(id), title(t), available(true) {}

    virtual void getItemDetails() const = 0;
    virtual bool checkAvailability() const { return available; }
    virtual void checkOut() { available = false; }
    virtual void checkIn() { available = true; }

    virtual ~Item() {}
};

// Derived class for Books
class Book : public Item {
    string author;
    string isbn;

public:
    Book(int id, string t, string a, string i) : Item(id, t), author(a), isbn(i) {}

    void getItemDetails() const override {
        cout << "Book ID: " << itemID << ", Title: " << title << ", Author: " << author << ", ISBN: " << isbn << endl;
    }
};

// Derived class for Journals
class Journal : public Item {
    string publisher;
    int issueNum;

public:
    Journal(int id, string t, string p, int issue) : Item(id, t), publisher(p), issueNum(issue) {}

    void getItemDetails() const override {
        cout << "Journal ID: " << itemID << ", Title: " << title << ", Publisher: " << publisher << ", Issue: " << issueNum << endl;
    }
};

// Class for Members
class Member {
    int memberID;
    string name;
    string contact;
    int loanLimit;
    int loanHistory[10];  // Fixed size array for loan history
    int loanCount;

public:
    Member(int id, string n, string c, int limit) : memberID(id), name(n), contact(c), loanLimit(limit), loanCount(0) {}

    void borrowItem(int itemId) {
        if (loanCount < loanLimit) {
            loanHistory[loanCount++] = itemId;
            cout << "Item borrowed successfully.\n";
        }
        else {
            cout << "Loan limit reached.\n";
        }
    }

    void returnItem(int itemId) {
        for (int i = 0; i < loanCount; ++i) {
            if (loanHistory[i] == itemId) {
                // Shift the remaining items in the array
                for (int j = i; j < loanCount - 1; ++j) {
                    loanHistory[j] = loanHistory[j + 1];
                }
                loanCount--;
                cout << "Item returned successfully.\n";
                return;
            }
        }
        cout << "Item not found in loan history.\n";
    }

    void getLoanHistory() const {
        cout << "Loan History: ";
        for (int i = 0; i < loanCount; ++i) {
            cout << loanHistory[i] << " ";
        }
        cout << endl;
    }
};

// Class for Loans
class Loan {
    int loanID;
    int itemID;
    int memberID;
    string dueDate;
    string returnDate;

public:
    Loan(int lid, int iid, int mid, string due, string ret = "") : loanID(lid), itemID(iid), memberID(mid), dueDate(due), returnDate(ret) {}

    void calculateFine() const {
        if (returnDate > dueDate) {
            cout << "Fine calculated based on overdue days.\n";
        }
        else {
            cout << "No fine.\n";
        }
    }
};

// Main function
int main() {
    // Example usage
    Book book1(1, "C++ Programming", "Bjarne Stroustrup", "1234567890");
    Journal journal1(2, "Science Journal", "Nature Publishing", 100);

    Member member1(101, "Alice", "alice@example.com", 3);

    book1.getItemDetails();
    journal1.getItemDetails();

    member1.borrowItem(1);
    member1.getLoanHistory();
    member1.returnItem(1);
    member1.getLoanHistory();

    Loan loan1(201, 1, 101, "2024-08-30", "2024-09-02");
    loan1.calculateFine();

    return 0;
}
