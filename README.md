# Card Reader Simulation (C)

This project is a simple card reader / access control simulation written in C.
It was created as a learning project to practice structured C programming,
memory management, and file handling.

The program simulates a basic access-controlled door system.

---

## Features

- Register cards with:
  - Card number
  - Access permission (on / off)
  - Registration date
- Enable or disable access for existing cards
- Simulate opening a door with a green lamp
- Simulate scanning a card:
  - Green: access granted
  - Red: access denied
  - Off: card not registered
- Persistent storage using files
- Safe user input handling
- Modular design using header files

---

## Program Structure

├── main.c // Menu and program control

├── cardhandling.c // Card logic and file handling

├── cardhandling.h

├── inputhandling.c // Safe input handling

├── inputhandling.h

├── cardlist.dat // Saved card data (generated at runtime)

└── README.md


---

## How It Works

- Card data is stored in a dynamically allocated list (`AccessList`)
- Each card is represented by a struct containing:
  - Card number
  - Access flag
  - Registration date
- When the program exits, all card data is saved to a file
- When the program starts, the file is loaded automatically

This allows the system to keep its data between restarts.

---

## Technologies and Concepts

- Language: C (C11)
- Dynamic memory allocation (`malloc`, `free`)
- File I/O (binary read/write)
- Structs and pointers
- Input validation (`fgets` + `sscanf`)
- Modular programming with `.c` and `.h` files

---

## Why I Built This

I built this project to practice:

- Writing safer C code
- Managing memory manually
- Separating logic into multiple source files
- Handling user input robustly
- Persisting data using files

This project helped me understand how a simple access control system could be implemented in C.

---

## Possible Improvements

- Delete cards completely from the system
- Improve the user interface
- Connecting to a real card reader


