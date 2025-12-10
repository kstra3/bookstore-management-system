# 📚 UTHLIBRARY - University Bookstore Management System

![C](https://img.shields.io/badge/Language-C-blue.svg)
![Status](https://img.shields.io/badge/Status-Complete-success.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

## 📖 Overview

A comprehensive bookstore management system developed in C, featuring three different implementations showcasing various data structures and algorithms. This project demonstrates fundamental concepts in data structures, file I/O, memory management, and algorithm design.

**Project Name**: THE OPEN BOOK - University Library  
**Institution**: University of Thessaly  
**Version**: 1.0

---

## 🎯 Features

### Core Functionality
- ✅ **Author Management**: Insert, search, and delete author records
- ✅ **Book Management**: Insert, search, and delete book records  
- ✅ **Relationship Tracking**: Many-to-many author-book relationships
- ✅ **Data Persistence**: File-based storage with automatic save/load
- ✅ **Sorted Data**: Automatic sorting for efficient operations
- ✅ **Binary Search**: O(log n) lookup performance
- ✅ **Dynamic Memory**: Efficient malloc/realloc/free management
- ✅ **Beautiful UI**: Enhanced ASCII art menu interface

---

## 📁 Project Structure

```
Ergasia_1/
├── src/
│   ├── bookstore_ask_1.c          # Question 1 - Dynamic Arrays
│   ├── bookstore_bonus.c          # Bonus - Generic Structures
│   ├── generic_array.c/.h         # Generic dynamic array implementation
│   └── generic_list.c/.h          # Generic linked list implementation
├── Question_2/
│   └── bookstore_ask_2.c          # Question 2 - Linked Lists
├── data/
│   ├── books.txt                  # Book records
│   ├── authors.txt                # Author records
│   └── writes.txt                 # Author-Book relationships
├── docs/
│   ├── README.md                  # Detailed documentation
│   └── BOOKSTORE_BONUS_README.md  # Generic implementation docs
└── README.md                      # This file
```

---

## 🚀 Quick Start

### Prerequisites
- GCC compiler (MinGW for Windows)
- C standard library

### Compilation

#### Question 1 - Array Based Implementation
```bash
cd "C:\Users\strat\OneDrive - ΠΑΝΕΠΙΣΤΗΜΙΟ ΘΕΣΣΑΛΙΑΣ\Επιφάνεια εργασίας\xaker\Ergasia_1"
gcc src\bookstore_ask_1.c -o bookstore_ask_1.exe
```

#### Question 2 - Linked List Implementation
```bash
cd "C:\Users\strat\OneDrive - ΠΑΝΕΠΙΣΤΗΜΙΟ ΘΕΣΣΑΛΙΑΣ\Επιφάνεια εργασίας\xaker\Ergasia_1\Question_2"
gcc bookstore_ask_2.c -o bookstore_ask_2.exe
```

#### Bonus - Generic Structures
```bash
cd "C:\Users\strat\OneDrive - ΠΑΝΕΠΙΣΤΗΜΙΟ ΘΕΣΣΑΛΙΑΣ\Επιφάνεια εργασίας\xaker\Ergasia_1\src"
gcc bookstore_bonus.c generic_array.c generic_list.c -o bookstore_bonus.exe
```

### Execution
```bash
# Run from project root directory
.\bookstore_ask_1.exe
.\bookstore_ask_2.exe
.\bookstore_bonus.exe
```

---

## 💻 Implementations

### Question 1: Dynamic Arrays
- **Data Structures**: Dynamic arrays with realloc
- **Sorting**: Bubble sort (O(n²))
- **Search**: Binary search (O(log n))
- **File**: `src/bookstore_ask_1.c`

### Question 2: Linked Lists  
- **Data Structures**: Singly linked lists
- **Sorting**: Custom sorting algorithms
- **Search**: Linear search (O(n))
- **File**: `Question_2/bookstore_ask_2.c`

### Bonus: Generic Structures
- **Data Structures**: Generic arrays + generic linked lists
- **Sorting**: qsort for arrays, merge sort for lists
- **Search**: Binary search with function pointers
- **Features**: Type-safe generics with void pointers
- **Files**: `src/bookstore_bonus.c`, `generic_array.c/h`, `generic_list.c/h`

---

## 📊 Data File Format

### books.txt
```
<book_count>
<title_1>
<release_year>
<price>
<title_2>
...
```

### authors.txt
```
<author_count>
<writer_id>
<surname>
<name>
<num_of_books>
...
```

### writes.txt
```
<unique_book_count>
<book_title_1>
<author_id_1> & <author_id_2> & ...
<book_title_2>
...
```

---

## 🎨 User Interface

All implementations feature an enhanced ASCII art menu:

```
  +=====================================================================+
  |                                                                     |
  |         ##  ##  ########  ##  ##  ##        ####  ######            |
  |         ##  ##     ##     ##  ##  ##         ##   ##   ##           |
  |         ##  ##     ##     ######  ##         ##   ######            |
  |         ##  ##     ##     ##  ##  ##         ##   ##   ##           |
  |          ####      ##     ##  ##  ######    ####  ######            |
  |                                                                     |
  |         ######     #####     #####     ######      ##  ##           |
  |         ##   ##   ##   ##   ##   ##    ##  ##      ##  ##           |
  |         ######    #######   #######    ######       ####            |
  |         ##   ##   ##   ##   ##   ##    ##  ##        ##             |
  |         ######    ##   ##   ##   ##    ##   ##       ##             |
  |                                                                     |
  |                  =======================================             |
  |                   THE OPEN BOOK - UNIVERSITY LIBRARY                |
  |                   Digital Management System v1.0                    |
  +=====================================================================+
```

---

## 🔧 Operations

### 1. Insert Writer Record
Add new author with auto-generated ID

### 2. Insert Book Record
Add book with multiple authors, creates new authors if needed

### 3. Search Writer Record
Find author by surname, displays all books

### 4. Search Book Record
Find book by title, displays all authors

### 5. Delete Writer Record
Remove author and optionally cascade delete single-author books

### 6. Delete Book Record
Remove book and update author book counts

### 7. Exit
Save all changes and quit

**Note**: Type '0' or press ENTER to cancel any operation

---

## ⚙️ Algorithm Complexity

| Operation | Array (Q1) | Linked List (Q2) | Generic (Bonus) |
|-----------|------------|------------------|-----------------|
| Insert | O(n²) | O(n) | O(n log n) |
| Delete | O(n) | O(n) | O(n) |
| Search | O(log n) | O(n) | O(log n) |
| Sort | O(n²) | O(n²) | O(n log n) |

---

## 🧪 Testing

Create sample data files in the `data/` folder to test:

```bash
mkdir data
# Add sample books.txt, authors.txt, writes.txt
```

Example test data provided in repository.

---

## 📝 Key Concepts Demonstrated

- **Data Structures**: Arrays, Linked Lists, Generic Structures
- **Algorithms**: Sorting, Binary Search, Memory Management
- **File I/O**: Text file parsing and writing
- **Memory Management**: malloc, realloc, free
- **Function Pointers**: Generic comparison and display functions
- **Modular Design**: Separation of concerns
- **User Experience**: Interactive menu system

---

## 🐛 Known Limitations

### Question 1 (Arrays)
- Bubble sort is inefficient for large datasets
- Binary search requires sorted arrays
- Array reallocations can be costly

### Question 2 (Linked Lists)
- Linear search is O(n)
- More memory overhead per node
- No random access

### Bonus (Generic)
- More complex implementation
- Type safety relies on proper usage

---

## 🚧 Future Improvements

- [ ] Add input validation and error handling
- [ ] Implement update operations
- [ ] Add transaction support
- [ ] Create unit tests
- [ ] Optimize sorting algorithms
- [ ] Add search by multiple criteria
- [ ] Implement undo/redo functionality
- [ ] Add export to CSV/JSON

---

## 👨‍💻 Author

**University of Thessaly Student**  
Computer Science Department

---

## 📄 License

This project is licensed under the MIT License - feel free to use for educational purposes.

---

## 🙏 Acknowledgments

- University of Thessaly - Data Structures Course
- C Programming Language - Dennis Ritchie & Brian Kernighan
- Open source community for inspiration

---

## 📞 Contact & Support

For questions or issues:
- Create an issue in the repository
- Contact through university email

---

**Made with ❤️ for Data Structures Course**
