#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 256

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Linked list node structures
typedef struct book_node {
    char *title;
    int release_date;
    float price;
    struct book_node *next;
} book_node;

typedef struct author_node {
    int writer_id;
    char *surname;
    char *name;
    int num_of_books;
    struct author_node *next;
} author_node;

typedef struct writes_node {
    char *title;
    int writer_id;
    struct writes_node *next;
} writes_node;

// Head pointers for the three linked lists
book_node *book_head = NULL;
author_node *author_head = NULL;
writes_node *writes_head = NULL;

// Function prototypes
void load_data();
void save_data();
void insert_author();
void insert_book();
void search_author();
void search_book();
void delete_author();
void delete_book();
void display_menu();
book_node* search_book_by_title(char *title);
author_node* search_author_by_id(int id);
author_node* search_author_by_surname(char *surname);
void insert_sorted_book(char *title, int release_date, float price);
void insert_sorted_author(int writer_id, char *surname, char *name, int num_of_books);
void insert_sorted_writes(char *title, int writer_id);
void free_memory();
char* read_string(FILE *fp);
void renumber_author_ids();
int count_books();
int count_authors();
int count_writes();

int main() {
    int choice;
    char input[MAX_LINE];
    load_data();
    clear_screen();
    while (1) {
        display_menu();
        if (fgets(input, MAX_LINE, stdin) == NULL) {
            continue;
        }
        if (sscanf(input, "%d", &choice) != 1) {
            clear_screen();
            printf("Error: '%s' is not a valid number. Please enter a number between 1-7.\n", input);
            printf("\nPress Enter to continue...");
            getchar();
            clear_screen();
            continue;
        }
        switch (choice) {
            case 1:
                insert_author();
                printf("\nPress Enter to continue...");
                getchar();
                clear_screen();
                break;
            case 2:
                insert_book();
                printf("\nPress Enter to continue...");
                getchar();
                clear_screen();
                break;
            case 3:
                search_author();
                printf("\nPress Enter to continue...");
                getchar();
                clear_screen();
                break;
            case 4:
                search_book();
                printf("\nPress Enter to continue...");
                getchar();
                clear_screen();
                break;
            case 5:
                delete_author();
                printf("\nPress Enter to continue...");
                getchar();
                clear_screen();
                break;
            case 6:
                delete_book();
                printf("\nPress Enter to continue...");
                getchar();
                clear_screen();
                break;
            case 7:
                save_data();
                free_memory();
                printf("\n===============================================\n");
                printf("  All changes saved successfully!\n");
                printf("  Thank you for using The Open Book!\n");
                printf("  See you next time!\n");
                printf("=================================================\n");
                return 0;
            default:
                clear_screen();
                printf("Error: Choice %d is out of range. Please select 1-7.\n", choice);
                printf("\nPress Enter to continue...");
                getchar();
                clear_screen();
        }
    }
    return 0;
}

void display_menu() {
    printf("\n\n");
    printf("  +=====================================================================+\n");
    printf("  |                                                                     |\n");
    printf("  |         ##  ##  ########  ##  ##    ##      ####  ######            |\n");
    printf("  |         ##  ##     ##     ##  ##    ##       ##   ##   ##           |\n");
    printf("  |         ##  ##     ##     ######    ##       ##   ######            |\n");
    printf("  |         ##  ##     ##     ##  ##    ##       ##   ##   ##           |\n");
    printf("  |          ####      ##     ##  ##    ######  ####  ######            |\n");
    printf("  |                                                                     |\n");
    printf("  |                  ====================================               |\n");
    printf("  |                   THE OPEN BOOK - UNIVERSITY LIBRARY                |\n");
    printf("  |                   Digital Management System v1.0                    |\n");
    printf("  |                   Question 2 - Linked List Based                    |\n");
    printf("  |                  ====================================               |\n");
    printf("  |                                                                     |\n");
    printf("  +=====================================================================+\n");
    printf("  |                       MAIN MENU OPTIONS                             |\n");
    printf("  +=====================================================================+\n");
    printf("  |                                                                     |\n");
    printf("  |       +------------------------------------------------------+      |\n");
    printf("  |       |                                                      |      |\n");
    printf("  |       |   [1] >> Insert New Writer Record                    |      |\n");
    printf("  |       |         Add a new author to the database             |      |\n");
    printf("  |       |                                                      |      |\n");
    printf("  |       |   [2] >> Insert New Book Record                      |      |\n");
    printf("  |       |         Add a new book with author information       |      |\n");
    printf("  |       |                                                      |      |\n");
    printf("  |       |   [3] >> Search Writer Record                        |      |\n");
    printf("  |       |         Find author by surname and view details      |      |\n");
    printf("  |       |                                                      |      |\n");
    printf("  |       |   [4] >> Search Book Record                          |      |\n");
    printf("  |       |         Find book by title and view information      |      |\n");
    printf("  |       |                                                      |      |\n");
    printf("  |       |   [5] >> Delete Writer Record                        |      |\n");
    printf("  |       |         Remove author and associated books           |      |\n");
    printf("  |       |                                                      |      |\n");
    printf("  |       |   [6] >> Delete Book Record                          |      |\n");
    printf("  |       |         Remove book from the database                |      |\n");
    printf("  |       |                                                      |      |\n");
    printf("  |       |   [7] >> Exit System                                 |      |\n");
    printf("  |       |         Save all changes and quit                    |      |\n");
    printf("  |       |                                                      |      |\n");
    printf("  |       +------------------------------------------------------+      |\n");
    printf("  |                                                                     |\n");
    printf("  +=====================================================================+\n");
    printf("  |  TIP: Enter '0' or press ENTER without input to cancel operation    |\n");
    printf("  +=====================================================================+\n");
    printf("\n  +---------------------------------------------------------------------+\n");
    printf("  |  >>  Enter your choice: ");
}

char* read_string(FILE *fp) {
    char buffer[MAX_LINE];
    if (fgets(buffer, MAX_LINE, fp) == NULL) {
        return NULL;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    char *str = (char*)malloc(strlen(buffer) + 1);
    if (str == NULL) {
        printf("Error: Memory allocation failed in read_string!\n");
        return NULL;
    }
    strcpy(str, buffer);
    return str;
}

int count_books() {
    int count = 0;
    book_node *current = book_head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int count_authors() {
    int count = 0;
    author_node *current = author_head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int count_writes() {
    int count = 0;
    writes_node *current = writes_head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void load_data() {
    FILE *fp;
    
    // Load books
    fp = fopen("../data/books.txt", "r");
    if (fp != NULL) {
        int book_count;
        fscanf(fp, "%d\n", &book_count);
        for (int i = 0; i < book_count; i++) {
            char *title = read_string(fp);
            int release_date;
            float price;
            fscanf(fp, "%d\n", &release_date);
            fscanf(fp, "%f\n", &price);
            insert_sorted_book(title, release_date, price);
            free(title);
        }
        fclose(fp);
    } else {
        printf("No existing books.txt file. Starting fresh.\n");
    }
    
    // Load authors
    fp = fopen("../data/authors.txt", "r");
    if (fp != NULL) {
        int author_count;
        fscanf(fp, "%d\n", &author_count);
        for (int i = 0; i < author_count; i++) {
            int writer_id;
            fscanf(fp, "%d\n", &writer_id);
            char *surname = read_string(fp);
            char *name = read_string(fp);
            int num_of_books;
            fscanf(fp, "%d\n", &num_of_books);
            insert_sorted_author(writer_id, surname, name, num_of_books);
            free(surname);
            free(name);
        }
        fclose(fp);
    } else {
        printf("No existing authors.txt file. Starting fresh.\n");
    }
    
    // Load writes
    fp = fopen("../data/writes.txt", "r");
    if (fp != NULL) {
        int unique_count;
        fscanf(fp, "%d\n", &unique_count);
        
        for (int i = 0; i < unique_count; i++) {
            char *title = read_string(fp);
            char author_ids_line[MAX_LINE];
            if (fgets(author_ids_line, MAX_LINE, fp) == NULL) break;
            
            // Parse author IDs separated by " & "
            char *token = strtok(author_ids_line, " &\n");
            while (token != NULL) {
                int author_id = atoi(token);
                insert_sorted_writes(title, author_id);
                token = strtok(NULL, " &\n");
            }
            free(title);
        }
        fclose(fp);
    } else {
        printf("No existing writes.txt file. Starting fresh.\n");
    }
}

void renumber_author_ids() {
    author_node *current = author_head;
    int new_id = 1;
    
    while (current != NULL) {
        int old_id = current->writer_id;
        current->writer_id = new_id;
        
        // Update all references in writes list
        if (old_id != new_id) {
            writes_node *w = writes_head;
            while (w != NULL) {
                if (w->writer_id == old_id) {
                    w->writer_id = new_id;
                }
                w = w->next;
            }
        }
        new_id++;
        current = current->next;
    }
}

void save_data() {
    renumber_author_ids();
    
    FILE *fp;
    
    // Save books
    fp = fopen("../data/books.txt", "w");
    int book_count = count_books();
    fprintf(fp, "%d\n", book_count);
    book_node *b = book_head;
    while (b != NULL) {
        fprintf(fp, "%s\n", b->title);
        fprintf(fp, "%d\n", b->release_date);
        fprintf(fp, "%.2f\n", b->price);
        b = b->next;
    }
    fclose(fp);
    
    // Save authors
    fp = fopen("../data/authors.txt", "w");
    int author_count = count_authors();
    fprintf(fp, "%d\n", author_count);
    author_node *a = author_head;
    while (a != NULL) {
        fprintf(fp, "%d\n", a->writer_id);
        fprintf(fp, "%s\n", a->surname);
        fprintf(fp, "%s\n", a->name);
        fprintf(fp, "%d\n", a->num_of_books);
        a = a->next;
    }
    fclose(fp);
    
    // Save writes (with grouped authors)
    fp = fopen("../data/writes.txt", "w");
    
    // Count unique book titles
    int unique_count = 0;
    writes_node *w = writes_head;
    while (w != NULL) {
        int is_duplicate = 0;
        writes_node *check = writes_head;
        while (check != w) {
            if (strcmp(check->title, w->title) == 0) {
                is_duplicate = 1;
                break;
            }
            check = check->next;
        }
        if (!is_duplicate) unique_count++;
        w = w->next;
    }
    
    fprintf(fp, "%d\n", unique_count);
    
    // Write each unique book with all its authors
    w = writes_head;
    while (w != NULL) {
        // Check if already written
        int already_written = 0;
        writes_node *check = writes_head;
        while (check != w) {
            if (strcmp(check->title, w->title) == 0) {
                already_written = 1;
                break;
            }
            check = check->next;
        }
        
        if (!already_written) {
            fprintf(fp, "%s\n", w->title);
            
            // Collect all author IDs for this title
            int first = 1;
            writes_node *w2 = writes_head;
            while (w2 != NULL) {
                if (strcmp(w2->title, w->title) == 0) {
                    if (!first) fprintf(fp, " & ");
                    fprintf(fp, "%d", w2->writer_id);
                    first = 0;
                }
                w2 = w2->next;
            }
            fprintf(fp, "\n");
        }
        w = w->next;
    }
    fclose(fp);
}

book_node* search_book_by_title(char *title) {
    book_node *current = book_head;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

author_node* search_author_by_id(int id) {
    author_node *current = author_head;
    while (current != NULL) {
        if (current->writer_id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

author_node* search_author_by_surname(char *surname) {
    author_node *current = author_head;
    while (current != NULL) {
        if (strcmp(current->surname, surname) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void insert_sorted_book(char *title, int release_date, float price) {
    book_node *new_node = (book_node*)malloc(sizeof(book_node));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed for book node!\n");
        return;
    }
    new_node->title = (char*)malloc(strlen(title) + 1);
    if (new_node->title == NULL) {
        printf("Error: Memory allocation failed for book title!\n");
        free(new_node);
        return;
    }
    strcpy(new_node->title, title);
    new_node->release_date = release_date;
    new_node->price = price;
    new_node->next = NULL;
    
    // Insert in sorted order by title
    if (book_head == NULL || strcmp(book_head->title, title) > 0) {
        new_node->next = book_head;
        book_head = new_node;
    } else {
        book_node *current = book_head;
        while (current->next != NULL && strcmp(current->next->title, title) < 0) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void insert_sorted_author(int writer_id, char *surname, char *name, int num_of_books) {
    author_node *new_node = (author_node*)malloc(sizeof(author_node));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed for author node!\n");
        return;
    }
    new_node->writer_id = writer_id;
    new_node->surname = (char*)malloc(strlen(surname) + 1);
    if (new_node->surname == NULL) {
        printf("Error: Memory allocation failed for author surname!\n");
        free(new_node);
        return;
    }
    strcpy(new_node->surname, surname);
    new_node->name = (char*)malloc(strlen(name) + 1);
    if (new_node->name == NULL) {
        printf("Error: Memory allocation failed for author name!\n");
        free(new_node->surname);
        free(new_node);
        return;
    }
    strcpy(new_node->name, name);
    new_node->num_of_books = num_of_books;
    new_node->next = NULL;
    
    // Insert in sorted order by writer_id
    if (author_head == NULL || author_head->writer_id > writer_id) {
        new_node->next = author_head;
        author_head = new_node;
    } else {
        author_node *current = author_head;
        while (current->next != NULL && current->next->writer_id < writer_id) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void insert_sorted_writes(char *title, int writer_id) {
    writes_node *new_node = (writes_node*)malloc(sizeof(writes_node));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed for writes node!\n");
        return;
    }
    new_node->title = (char*)malloc(strlen(title) + 1);
    if (new_node->title == NULL) {
        printf("Error: Memory allocation failed for writes title!\n");
        free(new_node);
        return;
    }
    strcpy(new_node->title, title);
    new_node->writer_id = writer_id;
    new_node->next = NULL;
    
    // Insert in sorted order by writer_id, then by title
    if (writes_head == NULL || writes_head->writer_id > writer_id ||
        (writes_head->writer_id == writer_id && strcmp(writes_head->title, title) > 0)) {
        new_node->next = writes_head;
        writes_head = new_node;
    } else {
        writes_node *current = writes_head;
        while (current->next != NULL &&
               (current->next->writer_id < writer_id ||
                (current->next->writer_id == writer_id && strcmp(current->next->title, title) < 0))) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void insert_author() {
    char buffer[MAX_LINE];
    printf("Enter author surname (or '0' to cancel): ");
    fgets(buffer, MAX_LINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
        printf("Operation cancelled.\n");
        return;
    }
    char *surname = (char*)malloc(strlen(buffer) + 1);
    if (surname == NULL) {
        printf("Error: Memory allocation failed for surname!\n");
        return;
    }
    strcpy(surname, buffer);
    
    printf("Enter author name (or '0' to cancel): ");
    fgets(buffer, MAX_LINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
        printf("Operation cancelled.\n");
        free(surname);
        return;
    }
    char *name = (char*)malloc(strlen(buffer) + 1);
    if (name == NULL) {
        printf("Error: Memory allocation failed for name!\n");
        free(surname);
        return;
    }
    strcpy(name, buffer);
    
    // Find max ID
    int max_id = 0;
    author_node *current = author_head;
    while (current != NULL) {
        if (current->writer_id > max_id) {
            max_id = current->writer_id;
        }
        current = current->next;
    }
    
    int new_id = max_id + 1;
    insert_sorted_author(new_id, surname, name, 0);
    printf(" Success! Author '%s %s' has been added with ID: %d\n", name, surname, new_id);
    
    free(surname);
    free(name);
}

void insert_book() {
    char buffer[MAX_LINE];
    printf("Enter book title (or '0' to cancel): ");
    fgets(buffer, MAX_LINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
        printf("Operation cancelled.\n");
        return;
    }
    char *title = (char*)malloc(strlen(buffer) + 1);
    if (title == NULL) {
        printf("Error: Memory allocation failed for book title!\n");
        return;
    }
    strcpy(title, buffer);
    
    int release_date;
    float price;
    printf("Enter release date (year, 1000-2100): ");
    if (scanf("%d", &release_date) != 1 || release_date < 1000 || release_date > 2100) {
        printf("Error: Invalid year. Please enter a year between 1000 and 2100.\n");
        free(title);
        while (getchar() != '\n');
        return;
    }
    printf("Enter price (minimum 0.01 EUR): ");
    if (scanf("%f", &price) != 1 || price < 0.01) {
        printf("Error: Invalid price. Price must be at least 0.01 EUR.\n");
        free(title);
        while (getchar() != '\n');
        return;
    }
    getchar();
    
    if (search_book_by_title(title) != NULL) {
        printf(" Error: A book with this title already exists!\n");
        free(title);
        return;
    }
    
    insert_sorted_book(title, release_date, price);
    
    printf("Enter number of authors: ");
    int num_authors;
    if (scanf("%d", &num_authors) != 1 || num_authors <= 0) {
        printf("Error: Invalid number of authors. Must be at least 1.\n");
        free(title);
        while (getchar() != '\n');
        return;
    }
    getchar();
    
    for (int i = 0; i < num_authors; i++) {
        printf("Enter author surname #%d: ", i + 1);
        fgets(buffer, MAX_LINE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        
        author_node *author = search_author_by_surname(buffer);
        int author_id;
        
        if (author == NULL) {
            char *surname = (char*)malloc(strlen(buffer) + 1);
            if (surname == NULL) {
                printf("Error: Memory allocation failed!\n");
                continue;
            }
            strcpy(surname, buffer);
            
            printf("Author not found. Enter author name: ");
            fgets(buffer, MAX_LINE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            char *name = (char*)malloc(strlen(buffer) + 1);
            if (name == NULL) {
                printf("Error: Memory allocation failed!\n");
                free(surname);
                continue;
            }
            strcpy(name, buffer);
            
            // Find max ID
            int max_id = 0;
            author_node *current = author_head;
            while (current != NULL) {
                if (current->writer_id > max_id) {
                    max_id = current->writer_id;
                }
                current = current->next;
            }
            
            author_id = max_id + 1;
            insert_sorted_author(author_id, surname, name, 1);
            printf("New author created with ID: %d\n", author_id);
            
            free(surname);
            free(name);
        } else {
            author_id = author->writer_id;
            author->num_of_books++;
        }
        
        insert_sorted_writes(title, author_id);
    }
    
    printf(" Wonderful! The book '%s' is now in our library!\n", title);
    free(title);
}

void search_author() {
    char buffer[MAX_LINE];
    printf("Enter author surname to search (or '0' to cancel): ");
    fgets(buffer, MAX_LINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
        printf("Operation cancelled.\n");
        return;
    }
    
    int found = 0;
    author_node *current = author_head;
    while (current != NULL) {
        if (strcmp(current->surname, buffer) == 0) {
            found = 1;
            printf("\n--- Author Information ---\n");
            printf("ID: %d\n", current->writer_id);
            printf("Name: %s %s\n", current->name, current->surname);
            printf("Number of books: %d\n", current->num_of_books);
            printf("Books:\n");
            
            int has_books = 0;
            writes_node *w = writes_head;
            while (w != NULL) {
                if (w->writer_id == current->writer_id) {
                    book_node *book = search_book_by_title(w->title);
                    if (book != NULL) {
                        printf("  - %s (%d) - %.2f EUR\n",
                               book->title, book->release_date, book->price);
                        has_books = 1;
                    }
                }
                w = w->next;
            }
            if (!has_books) {
                printf("  This author hasn't published a single book yet!\n");
            }
            printf("\n");
        }
        current = current->next;
    }
    
    if (!found) {
        printf(" Sorry, no author found with surname: %s\n", buffer);
    }
}

void search_book() {
    char buffer[MAX_LINE];
    printf("Enter book title to search (or '0' to cancel): ");
    fgets(buffer, MAX_LINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
        printf("Operation cancelled.\n");
        return;
    }
    
    book_node *book = search_book_by_title(buffer);
    if (book == NULL) {
        printf(" Sorry, book not found: %s\n", buffer);
        return;
    }
    
    printf("\n--- Book Information ---\n");
    printf("Title: %s\n", book->title);
    printf("Release Date: %d\n", book->release_date);
    printf("Price: %.2f EUR\n", book->price);
    printf("Authors:\n");
    
    writes_node *w = writes_head;
    while (w != NULL) {
        if (strcmp(w->title, buffer) == 0) {
            author_node *author = search_author_by_id(w->writer_id);
            if (author != NULL) {
                printf("  - %s %s (ID: %d)\n",
                       author->name, author->surname, author->writer_id);
            }
        }
        w = w->next;
    }
    printf("\n");
}

void delete_author() {
    char buffer[MAX_LINE];
    printf("Enter author ID to delete (or '0' to cancel): ");
    fgets(buffer, MAX_LINE, stdin);
    int id;
    if (sscanf(buffer, "%d", &id) != 1 || id == 0) {
        printf("Operation cancelled.\n");
        return;
    }
    
    author_node *author = search_author_by_id(id);
    if (author == NULL) {
        printf("Error: Author with ID %d not found.\n", id);
        return;
    }
    
    printf("\n  WARNING: This will delete author '%s %s' and all related data!\n",
           author->name, author->surname);
    printf("Are you sure? Type 'yes' to confirm: ");
    fgets(buffer, MAX_LINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    
    if (strcmp(buffer, "yes") != 0) {
        printf("Deletion cancelled.\n");
        return;
    }
    
    // Delete all writes entries and possibly books
    writes_node *w = writes_head;
    writes_node *prev_w = NULL;
    
    while (w != NULL) {
        if (w->writer_id == id) {
            char *title = w->title;
            
            // Count authors for this book
            int author_count_for_book = 0;
            writes_node *count_w = writes_head;
            while (count_w != NULL) {
                if (strcmp(count_w->title, title) == 0) {
                    author_count_for_book++;
                }
                count_w = count_w->next;
            }
            
            // If this is the only author, delete the book
            if (author_count_for_book == 1) {
                book_node *book = book_head;
                book_node *prev_book = NULL;
                while (book != NULL) {
                    if (strcmp(book->title, title) == 0) {
                        if (prev_book == NULL) {
                            book_head = book->next;
                        } else {
                            prev_book->next = book->next;
                        }
                        free(book->title);
                        free(book);
                        break;
                    }
                    prev_book = book;
                    book = book->next;
                }
            }
            
            // Remove this writes entry
            writes_node *to_delete = w;
            if (prev_w == NULL) {
                writes_head = w->next;
                w = writes_head;
            } else {
                prev_w->next = w->next;
                w = w->next;
            }
            free(to_delete->title);
            free(to_delete);
        } else {
            prev_w = w;
            w = w->next;
        }
    }
    
    // Delete the author
    author_node *current = author_head;
    author_node *prev = NULL;
    while (current != NULL) {
        if (current->writer_id == id) {
            if (prev == NULL) {
                author_head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->surname);
            free(current->name);
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
    
    printf(" Success! Author has been removed from the system.\n");
}

void delete_book() {
    char buffer[MAX_LINE];
    printf("Enter book title to delete (or '0' to cancel): ");
    fgets(buffer, MAX_LINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
        printf("Operation cancelled.\n");
        return;
    }
    
    book_node *book = search_book_by_title(buffer);
    if (book == NULL) {
        printf(" Sorry, book not found: %s\n", buffer);
        return;
    }
    
    printf("\n  WARNING: This will permanently delete '%s'!\n", buffer);
    printf("Are you sure? Type 'yes' to confirm: ");
    char confirm[MAX_LINE];
    fgets(confirm, MAX_LINE, stdin);
    confirm[strcspn(confirm, "\n")] = '\0';
    
    if (strcmp(confirm, "yes") != 0) {
        printf(" Deletion cancelled. Nothing was changed.\n");
        return;
    }
    
    // Delete all writes entries and update author book counts
    writes_node *w = writes_head;
    writes_node *prev_w = NULL;
    
    while (w != NULL) {
        if (strcmp(w->title, buffer) == 0) {
            author_node *author = search_author_by_id(w->writer_id);
            if (author != NULL) {
                author->num_of_books--;
            }
            
            writes_node *to_delete = w;
            if (prev_w == NULL) {
                writes_head = w->next;
                w = writes_head;
            } else {
                prev_w->next = w->next;
                w = w->next;
            }
            free(to_delete->title);
            free(to_delete);
        } else {
            prev_w = w;
            w = w->next;
        }
    }
    
    // Delete the book
    book_node *current = book_head;
    book_node *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->title, buffer) == 0) {
            if (prev == NULL) {
                book_head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->title);
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
    
    printf(" Success! Book has been removed from the library.\n");
}

void free_memory() {
    // Free books
    book_node *b = book_head;
    while (b != NULL) {
        book_node *temp = b;
        b = b->next;
        free(temp->title);
        free(temp);
    }
    
    // Free authors
    author_node *a = author_head;
    while (a != NULL) {
        author_node *temp = a;
        a = a->next;
        free(temp->surname);
        free(temp->name);
        free(temp);
    }
    
    // Free writes
    writes_node *w = writes_head;
    while (w != NULL) {
        writes_node *temp = w;
        w = w->next;
        free(temp->title);
        free(temp);
    }
}
