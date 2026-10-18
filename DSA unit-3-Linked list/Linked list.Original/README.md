📇 Contact Management System Using Doubly Linked List, Stack and Array
📌 Project Overview

The Contact Management System is a C++ mini-project that manages contact records using three data structures working together. Contact details are stored in a Doubly Linked List, contact slots are managed using an Array, and deleted contacts are saved in a Stack so that the last delete can be undone.

The project is written using structures only (no classes) and has a menu-driven interface.

🎯 Objectives
To manage contact records efficiently.
To implement a Doubly Linked List, a Stack and an Array in C++.
To perform add, delete, searching and display operations.
To allocate and free contact slots automatically.
To understand dynamic memory allocation and pointer manipulation.
✨ Features
Add a new contact and allot a free slot automatically.
Delete a contact and free the slot.
Search a contact by ID.
Display all contact records in forward and backward order.
Show the status of all contact slots.
Undo the last delete.
View delete history (latest delete first).
Duplicate ID checking and slot availability checking.
Menu-driven user interface.
🛠️ Technologies Used
Programming Language: C++
Data Structures: Doubly Linked List, Stack (array based), Array
Concepts: Structures, Pointers, Dynamic Memory Allocation, Functions and Loops
Platform: Visual Studio Code / Code::Blocks / any compatible C++ compiler
⚙️ How It Works
The user selects an operation from the menu.
While adding, the system finds the first free slot in the slot array.
Contact details are entered and stored as a new node at the end of the doubly linked list.
While deleting, the contact record is pushed onto the stack, the slot is freed and the node is removed from the list.
Undo pops the last record from the stack and inserts the contact back into the list.
🧩 Data Structures Used
Data Structure	Used For
Doubly Linked List	Stores contact records (forward and backward traversal)
Array (10 slots)	Slot allocation and availability
Stack (20 records)	Delete history and undo last delete
Node Structure

Each node of the linked list contains:

Contact ID
Contact Name
Phone Number
Allotted Slot Number
Previous pointer
Next pointer
▶️ How to Run the Project
Clone or download this repository.
Open the project folder in your preferred C++ IDE.
Compile the source code using a C++ compiler.
bash
g++ Contact_Management_DLL_Stack_Array.cpp -o contact
Run the program.

Windows:

bash
contact.exe

Linux/macOS:

bash
./contact
📋 Menu Options
Choice	Operation
1	Add new contact
2	Delete contact
3	Search contact
4	Display all contacts (forward)
5	Display all contacts (backward)
6	Show slot status
7	Undo last delete
8	Show delete history
9	Exit
📚 Data Structure Operations
Operation	Description	Time Complexity
Add	Adds a contact at the end of the list and occupies a slot	O(n)
Delete	Pushes record to stack, frees slot, removes node	O(n)
Searching	Finds a contact by ID	O(n)
Forward Traversal	Displays records from first to last	O(n)
Backward Traversal	Displays records from last to first	O(n)
Slot Status	Scans the slot array	O(1)
Undo Delete	Pops stack and re-adds the contact	O(n)
Delete History	Prints stack from top to bottom	O(1)
✅ Advantages
Supports traversal in both directions.
Allows dynamic addition and removal of records.
Deletion is efficient once the node is found, since both neighbours are linked.
Undo feature is simple and quick using a stack.
Slots are allocated and freed automatically.
Demonstrates practical use of three data structures in a contact book scenario.
⚠️ Limitations
Records are lost when the program terminates, as file storage is not implemented.
The contact book has a fixed number of slots (10) and delete history is limited to 20 records.
Searching for a contact requires linear traversal.
A restored contact is added at the end of the list and may get a different slot number.
The project is intended for educational purposes and is not a production-ready contact application.
🔮 Future Enhancements
Add file handling or database integration for permanent storage.
Add an option to update contact details.
Implement search by name and contact categories (family, friends, work).
Add sorting of contacts in alphabetical order.
Add favourite contacts and call history.
🎓 Learning Outcomes
Understand the working of a Doubly Linked List, Stack and Array.
Develop practical C++ programming skills.
Learn dynamic memory management and pointer operations.
Apply data structures to a real-world inspired problem.
👨‍💻 Author

Student Mini-Project — Data Structures and Algorithms (DSA)

📄 License

This project is intended for educational and academic purposes.
