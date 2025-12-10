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
typedef struct book {
    char *title;
    int release_date;
    float price;
} book;
typedef struct author {
    int writer_id;
    char *surname;
    char *name;
    int num_of_books;
} author;
typedef struct writes {
    char *title;
    int writer_id;
} writes;
book *book_arr = NULL;
author *author_arr = NULL;
writes *writes_arr = NULL;
int book_count = 0;
int author_count = 0;
int writes_count = 0;
void load_data();
void save_data();
void insert_author();
void insert_book();
void search_author();
void search_book();
void delete_author();
void delete_book();
void display_menu();
int binary_search_book(char *title);
int binary_search_author_by_id(int id);
int binary_search_author_by_surname(char *surname);
int binary_search_writes(int writer_id, char *title);
void sort_books();
void sort_authors();
void sort_writes();
void free_memory();
char* read_string(FILE *fp);
void insert_sorted_book(book new_book);
void insert_sorted_author(author new_author);
void insert_sorted_writes(writes new_write);
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
            printf("Invalid choice. Please enter a number.\n");
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
                printf("Exiting program. Data saved.\n");
                return 0;
            default:
                clear_screen();
                printf("Invalid choice. Please try again.\n");
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
    printf("  |         ##  ##  ########  ##  ##  ##        ####  ######            |\n");
    printf("  |         ##  ##     ##     ##  ##  ##         ##   ##   ##           |\n");
    printf("  |         ##  ##     ##     ######  ##         ##   ######            |\n");
    printf("  |         ##  ##     ##     ##  ##  ##         ##   ##   ##           |\n");
    printf("  |          ####      ##     ##  ##  ######    ####  ######            |\n");
    printf("  |                                                                     |\n");
    printf("  |                  ===================================                |\n");
    printf("  |                   THE OPEN BOOK - UNIVERSITY LIBRARY                |\n");
    printf("  |                   Digital Management System v1.0                    |\n");
    printf("  |                      Question 1 - Array Based                       |\n");
    printf("  |                  ===================================                |\n");
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
    strcpy(str, buffer);
    return str;
}
void load_data() {
    FILE *fp;
    fp = fopen("../data/books.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%d\n", &book_count);
        if (book_count > 0) {
            book_arr = (book*)malloc(book_count * sizeof(book));
            for (int i = 0; i < book_count; i++) {
                book_arr[i].title = read_string(fp);
                fscanf(fp, "%d\n", &book_arr[i].release_date);
                fscanf(fp, "%f\n", &book_arr[i].price);
            }
        }
        fclose(fp);
    } else {
        printf("No existing books.txt file. Starting fresh.\n");
        book_count = 0;
    }
    fp = fopen("../data/authors.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%d\n", &author_count);
        if (author_count > 0) {
            author_arr = (author*)malloc(author_count * sizeof(author));
            for (int i = 0; i < author_count; i++) {
                fscanf(fp, "%d\n", &author_arr[i].writer_id);
                author_arr[i].surname = read_string(fp);
                author_arr[i].name = read_string(fp);
                fscanf(fp, "%d\n", &author_arr[i].num_of_books);
            }
        }
        fclose(fp);
    } else {
        printf("No existing authors.txt file. Starting fresh.\n");
        author_count = 0;
    }
    fp = fopen("../data/writes.txt", "r");
    if (fp != NULL) {
        int unique_count;
        fscanf(fp, "%d\n", &unique_count);
        
        // Temporary storage - we'll expand as we parse
        writes_count = 0;
        writes_arr = NULL;
        
        for (int i = 0; i < unique_count; i++) {
            char *title = read_string(fp);
            char author_ids_line[MAX_LINE];
            if (fgets(author_ids_line, MAX_LINE, fp) == NULL) break;
            
            // Parse author IDs separated by " & "
            char *token = strtok(author_ids_line, " &\n");
            while (token != NULL) {
                int author_id = atoi(token);
                
                // Add new entry to writes_arr
                writes_arr = (writes*)realloc(writes_arr, (writes_count + 1) * sizeof(writes));
                writes_arr[writes_count].title = (char*)malloc(strlen(title) + 1);
                strcpy(writes_arr[writes_count].title, title);
                writes_arr[writes_count].writer_id = author_id;
                writes_count++;
                
                token = strtok(NULL, " &\n");
            }
            free(title);
        }
        fclose(fp);
    } else {
        printf("No existing writes.txt file. Starting fresh.\n");
        writes_count = 0;
    }
}
void renumber_author_ids() {
    // Create a mapping from old IDs to new IDs
    for (int i = 0; i < author_count; i++) {
        int old_id = author_arr[i].writer_id;
        int new_id = i + 1;
        
        // Update the author's ID
        author_arr[i].writer_id = new_id;
        
        // Update all references in writes_arr
        if (old_id != new_id) {
            for (int j = 0; j < writes_count; j++) {
                if (writes_arr[j].writer_id == old_id) {
                    writes_arr[j].writer_id = new_id;
                }
            }
        }
    }
    // Re-sort writes array after ID changes
    sort_writes();
}
void save_data() {
    // Renumber author IDs to be sequential before saving
    renumber_author_ids();
    
    FILE *fp;
    fp = fopen("../data/books.txt", "w");
    fprintf(fp, "%d\n", book_count);
    for (int i = 0; i < book_count; i++) {
        fprintf(fp, "%s\n", book_arr[i].title);
        fprintf(fp, "%d\n", book_arr[i].release_date);
        fprintf(fp, "%.2f\n", book_arr[i].price);
    }
    fclose(fp);
    fp = fopen("../data/authors.txt", "w");
    fprintf(fp, "%d\n", author_count);
    for (int i = 0; i < author_count; i++) {
        fprintf(fp, "%d\n", author_arr[i].writer_id);
        fprintf(fp, "%s\n", author_arr[i].surname);
        fprintf(fp, "%s\n", author_arr[i].name);
        fprintf(fp, "%d\n", author_arr[i].num_of_books);
    }
    fclose(fp);
    fp = fopen("../data/writes.txt", "w");
    
    // Count unique book titles in writes array
    int unique_count = 0;
    for (int i = 0; i < writes_count; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(writes_arr[i].title, writes_arr[j].title) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) unique_count++;
    }
    
    fprintf(fp, "%d\n", unique_count);
    
    // Write each unique book with all its authors on one line
    for (int i = 0; i < writes_count; i++) {
        // Check if we already wrote this title
        int already_written = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(writes_arr[i].title, writes_arr[j].title) == 0) {
                already_written = 1;
                break;
            }
        }
        if (already_written) continue;
        
        // Write the title
        fprintf(fp, "%s\n", writes_arr[i].title);
        
        // Collect all author IDs for this title
        int first = 1;
        for (int j = i; j < writes_count; j++) {
            if (strcmp(writes_arr[i].title, writes_arr[j].title) == 0) {
                if (!first) fprintf(fp, " & ");
                fprintf(fp, "%d", writes_arr[j].writer_id);
                first = 0;
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}
void sort_books() {
    for (int i = 0; i < book_count - 1; i++) {
        for (int j = 0; j < book_count - i - 1; j++) {
            if (strcmp(book_arr[j].title, book_arr[j + 1].title) > 0) {
                book temp = book_arr[j];
                book_arr[j] = book_arr[j + 1];
                book_arr[j + 1] = temp;
            }
        }
    }
}
void sort_authors() {
    for (int i = 0; i < author_count - 1; i++) {
        for (int j = 0; j < author_count - i - 1; j++) {
            if (author_arr[j].writer_id > author_arr[j + 1].writer_id) {
                author temp = author_arr[j];
                author_arr[j] = author_arr[j + 1];
                author_arr[j + 1] = temp;
            }
        }
    }
}
void sort_writes() {
    for (int i = 0; i < writes_count - 1; i++) {
        for (int j = 0; j < writes_count - i - 1; j++) {
            int cmp = (writes_arr[j].writer_id - writes_arr[j + 1].writer_id);
            if (cmp > 0 || (cmp == 0 && strcmp(writes_arr[j].title, writes_arr[j + 1].title) > 0)) {
                writes temp = writes_arr[j];
                writes_arr[j] = writes_arr[j + 1];
                writes_arr[j + 1] = temp;
            }
        }
    }
}
int binary_search_book(char *title) {
    int left = 0;
    int right = book_count - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(book_arr[mid].title, title);
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
int binary_search_author_by_id(int id) {
    int left = 0;
    int right = author_count - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (author_arr[mid].writer_id == id) return mid;
        if (author_arr[mid].writer_id < id) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
int binary_search_author_by_surname(char *surname) {
    for (int i = 0; i < author_count; i++) {
        if (strcmp(author_arr[i].surname, surname) == 0) {
            return i;
        }
    }
    return -1;
}
int binary_search_writes(int writer_id, char *title) {
    int left = 0;
    int right = writes_count - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (writes_arr[mid].writer_id == writer_id) {
            int cmp = strcmp(writes_arr[mid].title, title);
            if (cmp == 0) return mid;
            int i = mid;
            while (i >= 0 && writes_arr[i].writer_id == writer_id) {
                if (strcmp(writes_arr[i].title, title) == 0) return i;
                i--;
            }
            i = mid + 1;
            while (i < writes_count && writes_arr[i].writer_id == writer_id) {
                if (strcmp(writes_arr[i].title, title) == 0) return i;
                i++;
            }
            return -1;
        }
        if (writes_arr[mid].writer_id < writer_id) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
void insert_sorted_book(book new_book) {
    book_arr = (book*)realloc(book_arr, (book_count + 1) * sizeof(book));
    book_arr[book_count] = new_book;
    book_count++;
    sort_books();
}
void insert_sorted_author(author new_author) {
    author_arr = (author*)realloc(author_arr, (author_count + 1) * sizeof(author));
    author_arr[author_count] = new_author;
    author_count++;
    sort_authors();
}
void insert_sorted_writes(writes new_write) {
    writes_arr = (writes*)realloc(writes_arr, (writes_count + 1) * sizeof(writes));
    writes_arr[writes_count] = new_write;
    writes_count++;
    sort_writes();
}
void insert_author() {
    author new_author;
    char buffer[MAX_LINE];
    printf("Enter author surname (or '0' to cancel): ");
    fgets(buffer, MAX_LINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
        printf("Operation cancelled.\n");
        return;
    }
    new_author.surname = (char*)malloc(strlen(buffer) + 1);
    strcpy(new_author.surname, buffer);
    printf("Enter author name (or '0' to cancel): ");
    fgets(buffer, MAX_LINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
        printf("Operation cancelled.\n");
        free(new_author.surname);
        return;
    }
    new_author.name = (char*)malloc(strlen(buffer) + 1);
    strcpy(new_author.name, buffer);
    int max_id = 0;
    for (int i = 0; i < author_count; i++) {
        if (author_arr[i].writer_id > max_id) {
            max_id = author_arr[i].writer_id;
        }
    }
    new_author.writer_id = max_id + 1;
    new_author.num_of_books = 0;
    insert_sorted_author(new_author);
    printf("Author inserted successfully with ID: %d\n", new_author.writer_id);
}
void insert_book() {
    book new_book;
    char buffer[MAX_LINE];
    printf("Enter book title (or '0' to cancel): ");
    fgets(buffer, MAX_LINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) == 0 || strcmp(buffer, "0") == 0) {
        printf("Operation cancelled.\n");
        return;
    }
    new_book.title = (char*)malloc(strlen(buffer) + 1);
    strcpy(new_book.title, buffer);
    printf("Enter release date (year): ");
    scanf("%d", &new_book.release_date);
    printf("Enter price: ");
    scanf("%f", &new_book.price);
    getchar();
    if (binary_search_book(new_book.title) != -1) {
        printf("Book already exists!\n");
        free(new_book.title);
        return;
    }
    insert_sorted_book(new_book);
    printf("Enter number of authors: ");
    int num_authors;
    scanf("%d", &num_authors);
    getchar();
    for (int i = 0; i < num_authors; i++) {
        printf("Enter author surname #%d: ", i + 1);
        fgets(buffer, MAX_LINE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        int author_idx = binary_search_author_by_surname(buffer);
        int author_id;
        if (author_idx == -1) {
            author new_author;
            new_author.surname = (char*)malloc(strlen(buffer) + 1);
            strcpy(new_author.surname, buffer);
            printf("Author not found. Enter author name: ");
            fgets(buffer, MAX_LINE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            new_author.name = (char*)malloc(strlen(buffer) + 1);
            strcpy(new_author.name, buffer);
            int max_id = 0;
            for (int j = 0; j < author_count; j++) {
                if (author_arr[j].writer_id > max_id) {
                    max_id = author_arr[j].writer_id;
                }
            }
            new_author.writer_id = max_id + 1;
            new_author.num_of_books = 1;
            insert_sorted_author(new_author);
            author_id = new_author.writer_id;
            printf("New author created with ID: %d\n", author_id);
        } else {
            author_id = author_arr[author_idx].writer_id;
            author_arr[author_idx].num_of_books++;
        }
        writes new_write;
        new_write.title = (char*)malloc(strlen(new_book.title) + 1);
        strcpy(new_write.title, new_book.title);
        new_write.writer_id = author_id;
        insert_sorted_writes(new_write);
    }
    printf("Book inserted successfully!\n");
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
    for (int i = 0; i < author_count; i++) {
        if (strcmp(author_arr[i].surname, buffer) == 0) {
            found = 1;
            printf("\n--- Author Information ---\n");
            printf("ID: %d\n", author_arr[i].writer_id);
            printf("Name: %s %s\n", author_arr[i].name, author_arr[i].surname);
            printf("Number of books: %d\n", author_arr[i].num_of_books);
            printf("Books:\n");
            for (int j = 0; j < writes_count; j++) {
                if (writes_arr[j].writer_id == author_arr[i].writer_id) {
                    int book_idx = binary_search_book(writes_arr[j].title);
                    if (book_idx != -1) {
                        printf("  - %s (%d) - %.2f EUR\n",
                                book_arr[book_idx].title,
                                book_arr[book_idx].release_date,
                                book_arr[book_idx].price);
                    }
                }
            }
            printf("\n");
        }
    }
    if (!found) {
        printf("No author found with surname: %s\n", buffer);
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
    int idx = binary_search_book(buffer);
    if (idx == -1) {
        printf("Book not found: %s\n", buffer);
        return;
    }
    printf("\n--- Book Information ---\n");
    printf("Title: %s\n", book_arr[idx].title);
    printf("Release Date: %d\n", book_arr[idx].release_date);
    printf("Price: %.2f EUR\n", book_arr[idx].price);
    printf("Authors:\n");
    for (int i = 0; i < writes_count; i++) {
        if (strcmp(writes_arr[i].title, buffer) == 0) {
            int author_idx = binary_search_author_by_id(writes_arr[i].writer_id);
            if (author_idx != -1) {
                printf("  - %s %s (ID: %d)\n",
                       author_arr[author_idx].name,
                       author_arr[author_idx].surname,
                       author_arr[author_idx].writer_id);
            }
        }
    }
    printf("\n");
}
void delete_author() {
    int id;
    char buffer[MAX_LINE];
    printf("Enter author ID to delete (or '0' to cancel): ");
    fgets(buffer, MAX_LINE, stdin);
    if (sscanf(buffer, "%d", &id) != 1 || id == 0) {
        printf("Operation cancelled.\n");
        return;
    }
    int idx = binary_search_author_by_id(id);
    if (idx == -1) {
        printf("Author with ID %d not found.\n", id);
        return;
    }
    int i = 0;
    while (i < writes_count) {
        if (writes_arr[i].writer_id == id) {
            char *title = writes_arr[i].title;
            int author_count_for_book = 0;
            for (int j = 0; j < writes_count; j++) {
                if (strcmp(writes_arr[j].title, title) == 0) {
                    author_count_for_book++;
                }
            }
            if (author_count_for_book == 1) {
                int book_idx = binary_search_book(title);
                if (book_idx != -1) {
                    free(book_arr[book_idx].title);
                    for (int k = book_idx; k < book_count - 1; k++) {
                        book_arr[k] = book_arr[k + 1];
                    }
                    book_count--;
                    book_arr = (book*)realloc(book_arr, book_count * sizeof(book));
                }
            }
            free(writes_arr[i].title);
            for (int k = i; k < writes_count - 1; k++) {
                writes_arr[k] = writes_arr[k + 1];
            }
            writes_count--;
            writes_arr = (writes*)realloc(writes_arr, writes_count * sizeof(writes));
        } else {
            i++;
        }
    }
    free(author_arr[idx].surname);
    free(author_arr[idx].name);
    for (int i = idx; i < author_count - 1; i++) {
        author_arr[i] = author_arr[i + 1];
    }
    author_count--;
    author_arr = (author*)realloc(author_arr, author_count * sizeof(author));
    printf("Author deleted successfully.\n");
    save_data();
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
    int idx = binary_search_book(buffer);
    if (idx == -1) {
        printf("Book not found: %s\n", buffer);
        return;
    }
    int i = 0;
    while (i < writes_count) {
        if (strcmp(writes_arr[i].title, buffer) == 0) {
            int author_idx = binary_search_author_by_id(writes_arr[i].writer_id);
            if (author_idx != -1) {
                author_arr[author_idx].num_of_books--;
            }
            free(writes_arr[i].title);
            for (int k = i; k < writes_count - 1; k++) {
                writes_arr[k] = writes_arr[k + 1];
            }
            writes_count--;
            writes_arr = (writes*)realloc(writes_arr, writes_count * sizeof(writes));
        } else {
            i++;
        }
    }
    free(book_arr[idx].title);
    for (int i = idx; i < book_count - 1; i++) {
        book_arr[i] = book_arr[i + 1];
    }
    book_count--;
    book_arr = (book*)realloc(book_arr, book_count * sizeof(book));
    printf("Book deleted successfully.\n");
    save_data();
}
void free_memory() {
    for (int i = 0; i < book_count; i++) {
        free(book_arr[i].title);
    }
    free(book_arr);
    for (int i = 0; i < author_count; i++) {
        free(author_arr[i].surname);
        free(author_arr[i].name);
    }
    free(author_arr);
    for (int i = 0; i < writes_count; i++) {
        free(writes_arr[i].title);
    }
    free(writes_arr);
}
