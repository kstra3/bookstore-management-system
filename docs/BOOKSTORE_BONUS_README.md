# Bookstore Management System - Generic Implementation (Bonus)

## Overview
This is an enhanced version of the bookstore management system that uses **generic dynamic arrays** and **generic linked lists** with **generic functions** for all operations.

## Architecture

### Generic Data Structures

#### 1. Generic Dynamic Array (`generic_array.h/c`)
- **Structure**: `GenericArray`
  - Stores elements of any type using `void*` pointers
  - Dynamic resizing with automatic capacity management
  - Maintains sorted order for efficient binary search

- **Generic Operations**:
  - `array_create()` - Create array for any element type
  - `array_insert_sorted()` - Insert maintaining sorted order
  - `array_binary_search()` - O(log n) search using comparator
  - `array_delete()` - Remove element with optional cleanup
  - `array_sort()` - Sort using qsort with custom comparator
  - `array_display()` - Display using custom display function
  - `array_destroy()` - Cleanup with element-specific free function

#### 2. Generic Linked List (`generic_list.h/c`)
- **Structure**: `GenericList`
  - Node-based storage with `void*` data pointers
  - Each node contains element size information
  - Supports sorted insertions

- **Generic Operations**:
  - `list_create()` - Create list for any element type
  - `list_insert_sorted()` - Insert maintaining sorted order
  - `list_search()` - Linear search using comparator
  - `list_delete()` - Remove element with optional cleanup
  - `list_sort()` - Merge sort implementation
  - `list_display()` - Display using custom display function
  - `list_destroy()` - Cleanup with element-specific free function

### Function Pointers for Genericity

#### Comparison Functions (`CompareFunc`)
```c
typedef int (*CompareFunc)(const void*, const void*);
```
Used for:
- Sorting elements
- Binary/linear searching
- Maintaining sorted order during insertion

#### Display Functions (`DisplayFunc`)
```c
typedef void (*DisplayFunc)(const void*);
```
Used for:
- Printing elements in custom formats
- Displaying search results

#### Free Functions
```c
void (*free_element)(void*)
```
Used for:
- Cleaning up dynamically allocated fields
- Preventing memory leaks during deletion

## Implementation Details

### Data Organization

1. **Books**: Stored in `GenericArray`
   - Sorted by title (alphabetically)
   - Binary search for O(log n) lookups
   - Dynamic resizing on insert/delete

2. **Authors**: Stored in `GenericArray`
   - Sorted by writer_id
   - Binary search for O(log n) lookups by ID
   - Linear search available for surname lookups

3. **Writes (Relationships)**: Stored in `GenericList`
   - Many-to-many relationship between books and authors
   - Sorted by writer_id, then title
   - Linked list allows efficient insertions/deletions

### Generic Function Examples

#### Insert Operations
```c
// Generic sorted insertion for books
array_insert_sorted(books_array, &new_book, compare_books);

// Generic sorted insertion for writes relationships
list_insert_sorted(writes_list, &new_writes, compare_writes);
```

#### Search Operations
```c
// Generic binary search for books
int index = array_binary_search(books_array, &key, compare_books);

// Generic linear search in list
void* result = list_search(writes_list, &key, compare_writes);
```

#### Delete Operations
```c
// Generic delete with cleanup
array_delete(books_array, index, free_book);
list_delete(writes_list, &key, compare_writes, free_writes);
```

#### Sort Operations
```c
// Generic sorting with custom comparator
array_sort(books_array, compare_books);
list_sort(writes_list, compare_writes);
```

### Comparator Functions

All comparators follow the standard convention:
- Return negative if first < second
- Return 0 if first == second
- Return positive if first > second

Examples:
- `compare_books()` - Compare by title (string comparison)
- `compare_authors()` - Compare by writer_id (integer comparison)
- `compare_writes()` - Compare by writer_id, then by title

### Memory Management

All dynamic memory is properly managed through generic free functions:
- `free_book()` - Frees book title string
- `free_author()` - Frees surname and name strings
- `free_writes()` - Frees title string in relationship

## Compilation

```bash
gcc -o bookstore_bonus generic_array.c generic_list.c bookstore_bonus.c
```

Or use the Makefile (update as needed):
```makefile
bookstore_bonus: generic_array.o generic_list.o bookstore_bonus.o
	gcc -o bin/bookstore_bonus generic_array.o generic_list.o bookstore_bonus.o

generic_array.o: src/generic_array.c src/generic_array.h
	gcc -c src/generic_array.c

generic_list.o: src/generic_list.c src/generic_list.h
	gcc -c src/generic_list.c

bookstore_bonus.o: src/bookstore_bonus.c src/generic_array.h src/generic_list.h
	gcc -c src/bookstore_bonus.c
```

## Features

All original features are preserved with generic implementations:
1. **Insert author** - Uses generic array with sorted insertion
2. **Insert book** - Uses generic array and list for relationships
3. **Search author** - Generic binary search by ID, linear by surname
4. **Search book** - Generic binary search by title
5. **Delete author** - Generic delete with cascade to books and relationships
6. **Delete book** - Generic delete with relationship cleanup
7. **Save/Load** - Persistence using generic traversal functions

## Advantages of Generic Implementation

1. **Reusability**: Generic containers can be used for any data type
2. **Type Safety**: Compile-time type checking through sizeof()
3. **Performance**: Binary search in arrays, efficient merge sort in lists
4. **Flexibility**: Easy to add new entity types without rewriting container logic
5. **Maintainability**: Separation of container logic from business logic
6. **Extensibility**: New operations can be added through function pointers

## Complexity Analysis

| Operation | Array | List |
|-----------|-------|------|
| Insert (sorted) | O(n) | O(n) |
| Delete | O(n) | O(n) |
| Search | O(log n) binary | O(n) linear |
| Sort | O(n log n) qsort | O(n log n) merge |
| Access by index | O(1) | O(n) |

## Files

- `generic_array.h/c` - Generic dynamic array implementation
- `generic_list.h/c` - Generic linked list implementation
- `bookstore_bonus.c` - Main application using generic structures
- `../data/books.txt` - Book data persistence
- `../data/authors.txt` - Author data persistence
- `../data/writes.txt` - Relationship data persistence
