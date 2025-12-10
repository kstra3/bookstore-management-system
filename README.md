# 📚 UTHLIBRARY - University Bookstore Management System

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Status](https://img.shields.io/badge/Status-Complete-success.svg)

## 📖 Overview

A comprehensive bookstore management system developed in C, featuring two implementations showcasing different data structures and algorithms.

**Project Name**: THE OPEN BOOK - University Library  
**Institution**: University of Thessaly

---

## 🎯 Features

### Core Functionality
- ✅ **Author Management**: Insert, search, and delete author records
- ✅ **Book Management**: Insert, search, and delete book records  
- ✅ **Relationship Tracking**: Many-to-many author-book relationships
- ✅ **Data Persistence**: File-based storage with automatic save/load
- ✅ **Sorted Data**: Automatic sorting for efficient operations
- ✅ **Binary Search**: O(log n) lookup performance (Question 1)
- ✅ **Dynamic Memory**: Efficient malloc/realloc/free management
- ✅ **Input Validation**: Year range (1000-2100), price validation, confirmations

---

## 📁 Project Structure

```
Ergasia_1/
├── Question_1/
│   └── bookstore_ask_1.c          # Dynamic Arrays Implementation
├── Question_2/
│   └── bookstore_ask_2.c          # Linked Lists Implementation
├── data/
│   ├── books.txt                  # Book records
│   ├── authors.txt                # Author records
│   └── writes.txt                 # Author-Book relationships
└── docs/
    └── README.md                  # Detailed documentation
```

---

## 🚀 How to Compile & Run

### Question 1 (Array-based)
```bash
cd Question_1
gcc bookstore_ask_1.c -o bookstore_ask_1
./bookstore_ask_1
```

### Question 2 (Linked List-based)
```bash
cd Question_2
gcc bookstore_ask_2.c -o bookstore_ask_2
./bookstore_ask_2
```

### Windows (PowerShell)
```powershell
cd Question_1
gcc bookstore_ask_1.c -o bookstore_ask_1
.\bookstore_ask_1.exe
```

---

## 📊 Implementation Comparison

| Feature | Question 1 (Arrays) | Question 2 (Linked Lists) |
|---------|-------------------|-------------------------|
| **Data Structure** | Dynamic arrays with `realloc` | Linked lists with nodes |
| **Search** | Binary search O(log n) | Linear search O(n) |
| **Sort** | `qsort` with comparators | Sorted insertion |
| **Memory** | Contiguous, resizable | Scattered, node-based |
| **Insertion** | O(n) with realloc | O(n) sorted insert |
| **Deletion** | O(n) shift elements | O(n) unlink node |

---

## 💾 Data Format

### authors.txt
```
3
1 John Doe
2 Jane Smith
3 Bob Johnson
```

### books.txt
```
2
101 Introduction to C 2020 45.99
102 Data Structures 2021 59.99
```

### writes.txt
```
3
1 101
2 102
1 102
```

---

## ✨ Key Features Implemented

### Security & Validation
- ✅ Memory leak prevention on cancelled operations
- ✅ NULL pointer checks for all malloc/realloc
- ✅ Input validation (year: 1000-2100, price ≥ 0.01)
- ✅ Deletion confirmations ("Are you sure?")
- ✅ Buffer overflow protection

### User Experience
- ✅ Clear error messages with symbols (✓, ✗, ⚠️)
- ✅ Informative "no books found" messages
- ✅ Cross-platform support (Windows/Linux)
- ✅ Clean ASCII art menu interface

---

## 🛠️ Technical Details

### Algorithms Used
- **Binary Search**: O(log n) for sorted arrays (Q1)
- **Quick Sort**: O(n log n) via `qsort` (Q1)
- **Linear Search**: O(n) for linked lists (Q2)
- **Sorted Insertion**: O(n) for maintaining order (Q2)

### Memory Management
- Dynamic allocation with `malloc`/`realloc`
- Proper cleanup with `free` before exit
- Error handling for allocation failures
- Prevention of memory leaks on user cancel

---

## 📝 Assignment Requirements

✅ **Question 1**: Dynamic array implementation with binary search  
✅ **Question 2**: Linked list implementation with sorted insertion  
✅ All 6 operations implemented in both versions  
✅ File I/O for data persistence  
✅ Proper sorting and searching algorithms  
✅ Complete memory management

---

## 👨‍💻 Author

**University of Thessaly**  
Data Structures Course Project

---

## 📄 License

This project is part of academic coursework at the University of Thessaly.
