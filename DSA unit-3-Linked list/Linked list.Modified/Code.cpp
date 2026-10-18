// Contact Management System
// Data structures: Circular (doubly) linked list + Array + Queue
//   - Circular doubly linked list : contact records (add, delete, search, forward/backward display)
//   - Array                       : contact slots (slot allocation)
//   - Queue (circular array)      : deleted contacts (FIFO delete history, restore oldest)
 
#include <iostream>
#include <cstring>
using namespace std;
 
const int MAX_SLOTS = 10;
const int QSIZE = 5;   // queue capacity (small so overflow handling is easy to demo)
 
struct Contact {
    int id;
    char name[30];
    char phone[15];
    char email[30];
    int slot;          // allotted slot number (1..MAX_SLOTS)
};
 
struct Node {
    Contact data;
    Node *next;
    Node *prev;
};
 
// ---------- Globals ----------
Node *head = NULL;            // circular list: tail = head->prev, tail->next = head
int slots[MAX_SLOTS];         // 0 = free, 1 = occupied
int contactCount = 0;
 
Contact dq[QSIZE];            // circular queue of deleted contacts
int qFront = 0, qRear = -1, qCount = 0;
 
// ---------- Queue operations ----------
bool queueEmpty() { return qCount == 0; }
bool queueFull()  { return qCount == QSIZE; }
 
void enqueue(Contact c) {
    qRear = (qRear + 1) % QSIZE;
    dq[qRear] = c;
    qCount++;
}
 
Contact dequeue() {
    Contact c = dq[qFront];
    qFront = (qFront + 1) % QSIZE;
    qCount--;
    return c;
}
 
// ---------- Slot array operations ----------
int findFreeSlot() {
    for (int i = 0; i < MAX_SLOTS; i++)
        if (slots[i] == 0) return i;
    return -1;
}
 
// ---------- Circular linked list operations ----------
Node *findContact(int id) {
    if (head == NULL) return NULL;
    Node *cur = head;
    do {
        if (cur->data.id == id) return cur;
        cur = cur->next;
    } while (cur != head);
    return NULL;
}
 
void insertEnd(Contact c) {
    Node *n = new Node;
    n->data = c;
    if (head == NULL) {
        n->next = n;
        n->prev = n;
        head = n;
    } else {
        Node *tail = head->prev;
        tail->next = n;
        n->prev = tail;
        n->next = head;
        head->prev = n;
    }
    contactCount++;
}
 
void deleteNode(Node *n) {
    if (n->next == n) {            // only node in the list
        head = NULL;
    } else {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        if (n == head) head = n->next;
    }
    delete n;
    contactCount--;
}
 
void printContact(const Contact &c) {
    cout << "  ID: " << c.id << " | Name: " << c.name << " | Phone: " << c.phone
         << " | Email: " << c.email << " | Slot: " << c.slot << endl;
}
 
// ---------- Menu functions ----------
void addContact() {
    int s = findFreeSlot();
    if (s == -1) {
        cout << "No slots available.\n";
        return;
    }
    Contact c;
    cout << "Enter contact ID: ";
    cin >> c.id;
    if (findContact(c.id) != NULL) {
        cout << "Contact ID already exists.\n";
        return;
    }
    cin.ignore(1000, '\n');
    cout << "Enter name: ";
    cin.getline(c.name, 30);
    cout << "Enter phone: ";
    cin.getline(c.phone, 15);
    cout << "Enter email: ";
    cin.getline(c.email, 30);
 
    c.slot = s + 1;
    slots[s] = 1;
    insertEnd(c);
    cout << "Contact added. Slot number " << c.slot << " allotted.\n";
}
 
void deleteContact() {
    if (head == NULL) {
        cout << "No contacts in the contact book.\n";
        return;
    }
    int id;
    cout << "Enter contact ID to delete: ";
    cin >> id;
    Node *n = findContact(id);
    if (n == NULL) {
        cout << "Contact not found.\n";
        return;
    }
    if (queueFull()) {
        Contact old = dequeue();   // oldest record leaves the history to make room
        cout << "(History full: oldest record of " << old.name << " removed from queue.)\n";
    }
    enqueue(n->data);
    slots[n->data.slot - 1] = 0;
    cout << n->data.name << " deleted. Slot " << n->data.slot << " is now free.\n";
    deleteNode(n);
}
 
void searchContact() {
    if (head == NULL) {
        cout << "No contacts in the contact book.\n";
        return;
    }
    int id;
    cout << "Enter contact ID to search: ";
    cin >> id;
    Node *n = findContact(id);
    if (n == NULL) cout << "Contact not found.\n";
    else {
        cout << "Contact found:\n";
        printContact(n->data);
    }
}
 
void displayForward() {
    if (head == NULL) {
        cout << "No contact records.\n";
        return;
    }
    cout << "Contacts (forward, head to tail):\n";
    Node *cur = head;
    do {
        printContact(cur->data);
        cur = cur->next;
    } while (cur != head);
    cout << "Total contacts: " << contactCount << endl;
}
 
void displayBackward() {
    if (head == NULL) {
        cout << "No contact records.\n";
        return;
    }
    cout << "Contacts (backward, tail to head):\n";
    Node *tail = head->prev;
    Node *cur = tail;
    do {
        printContact(cur->data);
        cur = cur->prev;
    } while (cur != tail);
    cout << "Total contacts: " << contactCount << endl;
}
 
void slotStatus() {
    int freeCount = 0;
    for (int i = 0; i < MAX_SLOTS; i++) {
        cout << "  Slot " << i + 1 << ": " << (slots[i] ? "Occupied" : "Free") << endl;
        if (!slots[i]) freeCount++;
    }
    cout << "Free slots: " << freeCount << " / " << MAX_SLOTS << endl;
}
 
// Undo with a queue: the OLDEST deleted contact (front) is restored (FIFO).
void undoDelete() {
    if (queueEmpty()) {
        cout << "No deleted contacts to restore.\n";
        return;
    }
    Contact c = dq[qFront];        // peek, do not remove until we know it can be restored
    if (findContact(c.id) != NULL) {
        cout << "Cannot restore: contact ID " << c.id << " is already in use.\n";
        return;
    }
    int s = findFreeSlot();
    if (s == -1) {
        cout << "No slots available to restore.\n";
        return;
    }
    dequeue();
    c.slot = s + 1;
    slots[s] = 1;
    insertEnd(c);
    cout << c.name << " restored to slot " << c.slot << ".\n";
}
 
void deleteHistory() {
    if (queueEmpty()) {
        cout << "Delete history is empty.\n";
        return;
    }
    cout << "Delete history (oldest first, front to rear):\n";
    for (int i = 0, idx = qFront; i < qCount; i++, idx = (idx + 1) % QSIZE)
        printContact(dq[idx]);
}
 
void freeMemory() {
    while (head != NULL) deleteNode(head);
}
 
int main() {
    int choice;
    for (int i = 0; i < MAX_SLOTS; i++) slots[i] = 0;
 
    do {
        cout << "\n===== CONTACT MANAGEMENT SYSTEM =====\n"
             << "1. Add contact\n"
             << "2. Delete contact\n"
             << "3. Search contact\n"
             << "4. Display forward\n"
             << "5. Display backward\n"
             << "6. Slot status\n"
             << "7. Undo delete (restore oldest deleted)\n"
             << "8. Delete history\n"
             << "0. Exit\n"
             << "Enter choice: ";
        if (!(cin >> choice)) break;
 
        switch (choice) {
            case 1: addContact();     break;
            case 2: deleteContact();  break;
            case 3: searchContact();  break;
            case 4: displayForward(); break;
            case 5: displayBackward();break;
            case 6: slotStatus();     break;
            case 7: undoDelete();     break;
            case 8: deleteHistory();  break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
 
    freeMemory();
    return 0;
}
 
