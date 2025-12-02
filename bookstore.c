// Βιβλιοθήκη για εισόδου/εξόδου (printf, scanf, fopen, κλπ)
#include <stdio.h>
// Βιβλιοθήκη για δυναμική διαχείριση μνήμης (malloc, realloc, free)
#include <stdlib.h>
// Βιβλιοθήκη για χειρισμό strings (strcmp, strcpy, strlen, κλπ)
#include <string.h>

// Ορίζουμε το μέγιστο μέγεθος γραμμής για ανάγνωση από αρχεία
#define MAX_LINE 256

// Δομή για την αποθήκευση πληροφοριών βιβλίου
typedef struct book {
    char *title;          // Δείκτης σε string για τον τίτλο του βιβλίου
    int release_date;     // Ακέραιος για το έτος έκδοσης
    float price;          // Δεκαδικός αριθμός για την τιμή
} book;

// Δομή για την αποθήκευση πληροφοριών συγγραφέα
typedef struct author {
    int writer_id;        // Μοναδικός κωδικός συγγραφέα
    char *surname;        // Δείκτης σε string για το επώνυμο
    char *name;           // Δείκτης σε string για το όνομα
    int num_of_books;     // Πλήθος βιβλίων που έχει γράψει
} author;

// Δομή για τη σχέση συγγραφέα-βιβλίου (πίνακας writes)
typedef struct writes {
    char *title;          // Δείκτης σε string για τον τίτλο βιβλίου
    int writer_id;        // Κωδικός συγγραφέα που έγραψε το βιβλίο
} writes;

// Καθολικοί δυναμικοί πίνακες που κρατούν τα δεδομένα στη μνήμη
book *book_arr = NULL;       // Δυναμικός πίνακας για βιβλία (αρχικά κενός)
author *author_arr = NULL;   // Δυναμικός πίνακας για συγγραφείς (αρχικά κενός)
writes *writes_arr = NULL;   // Δυναμικός πίνακας για σχέσεις συγγραφέα-βιβλίου (αρχικά κενός)

// Καθολικοί μετρητές που κρατούν το πλήθος των εγγραφών
int book_count = 0;          // Πλήθος βιβλίων στον πίνακα
int author_count = 0;        // Πλήθος συγγραφέων στον πίνακα
int writes_count = 0;        // Πλήθος εγγραφών στον πίνακα writes

// Δηλώσεις συναρτήσεων (function prototypes) - επιτρέπουν χρήση συναρτήσεων πριν τον ορισμό τους
void load_data();                                      // Φόρτωση δεδομένων από αρχεία
void save_data();                                      // Αποθήκευση δεδομένων σε αρχεία
void insert_author();                                  // Εισαγωγή νέου συγγραφέα
void insert_book();                                    // Εισαγωγή νέου βιβλίου
void search_author();                                  // Αναζήτηση συγγραφέα
void search_book();                                    // Αναζήτηση βιβλίου
void delete_author();                                  // Διαγραφή συγγραφέα
void delete_book();                                    // Διαγραφή βιβλίου
void display_menu();                                   // Εμφάνιση μενού επιλογών
int binary_search_book(char *title);                   // Δυαδική αναζήτηση βιβλίου με τίτλο
int binary_search_author_by_id(int id);                // Δυαδική αναζήτηση συγγραφέα με ID
int binary_search_author_by_surname(char *surname);    // Αναζήτηση συγγραφέα με επώνυμο
int binary_search_writes(int writer_id, char *title);  // Δυαδική αναζήτηση στον πίνακα writes
void sort_books();                                     // Ταξινόμηση πίνακα βιβλίων
void sort_authors();                                   // Ταξινόμηση πίνακα συγγραφέων
void sort_writes();                                    // Ταξινόμηση πίνακα writes
void free_memory();                                    // Απελευθέρωση δυναμικής μνήμης
char* read_string(FILE *fp);                           // Ανάγνωση string από αρχείο
void insert_sorted_book(book new_book);                // Εισαγωγή βιβλίου με ταξινόμηση
void insert_sorted_author(author new_author);          // Εισαγωγή συγγραφέα με ταξινόμηση
void insert_sorted_writes(writes new_write);           // Εισαγωγή εγγραφής writes με ταξινόμηση

// Κύρια συνάρτηση του προγράμματος
int main() {
    int choice; // Μεταβλητή για την επιλογή του χρήστη από το μενού
    
    load_data(); // Φορτώνουμε τα δεδομένα από τα αρχεία κατά την εκκίνηση
    
    // Ατέρμονος βρόχος για το μενού - τερματίζει μόνο όταν ο χρήστης επιλέξει έξοδο
    while (1) {
        display_menu(); // Εμφανίζουμε το μενού στην οθόνη
        printf("Enter your choice: "); // Ζητάμε από τον χρήστη να επιλέξει
        scanf("%d", &choice); // Διαβάζουμε την επιλογή
        getchar(); // Καταναλώνουμε το newline character που μένει στο buffer
        
        // Ελέγχουμε την επιλογή του χρήστη με switch-case
        switch (choice) {
            case 1: // Αν επέλεξε 1
                insert_author(); // Καλούμε τη συνάρτηση εισαγωγής συγγραφέα
                break; // Βγαίνουμε από το switch
            case 2: // Αν επέλεξε 2
                insert_book(); // Καλούμε τη συνάρτηση εισαγωγής βιβλίου
                break;
            case 3: // Αν επέλεξε 3
                search_author(); // Καλούμε τη συνάρτηση αναζήτησης συγγραφέα
                break;
            case 4: // Αν επέλεξε 4
                search_book(); // Καλούμε τη συνάρτηση αναζήτησης βιβλίου
                break;
            case 5: // Αν επέλεξε 5
                delete_author(); // Καλούμε τη συνάρτηση διαγραφής συγγραφέα
                break;
            case 6: // Αν επέλεξε 6
                delete_book(); // Καλούμε τη συνάρτηση διαγραφής βιβλίου
                break;
            case 7: // Αν επέλεξε 7 (έξοδος)
                save_data(); // Αποθηκεύουμε τα δεδομένα στα αρχεία
                free_memory(); // Απελευθερώνουμε τη δυναμική μνήμη
                printf("Exiting program. Data saved.\n"); // Μήνυμα επιβεβαίωσης
                return 0; // Τερματίζουμε το πρόγραμμα με επιτυχία
            default: // Αν επέλεξε κάτι άλλο (μη έγκυρο)
                printf("Invalid choice. Please try again.\n"); // Μήνυμα λάθους
        }
    }
    
    return 0; // Επιστροφή επιτυχίας (δεν θα φτάσουμε ποτέ εδώ λόγω του while(1))
}

// Συνάρτηση εμφάνισης του μενού επιλογών
void display_menu() {
    printf("\n========== BOOKSTORE MANAGEMENT SYSTEM ==========\n"); // Τίτλος
    printf("1. Insert new writer record\n");   // Επιλογή 1: Εισαγωγή συγγραφέα
    printf("2. Insert new book record\n");     // Επιλογή 2: Εισαγωγή βιβλίου
    printf("3. Search a writer record\n");     // Επιλογή 3: Αναζήτηση συγγραφέα
    printf("4. Search a book record\n");       // Επιλογή 4: Αναζήτηση βιβλίου
    printf("5. Delete a writer record\n");     // Επιλογή 5: Διαγραφή συγγραφέα
    printf("6. Delete a book record\n");       // Επιλογή 6: Διαγραφή βιβλίου
    printf("7. Exit\n");                       // Επιλογή 7: Έξοδος
    printf("=================================================\n"); // Διαχωριστική γραμμή
}

// Συνάρτηση για ανάγνωση string από αρχείο
char* read_string(FILE *fp) {
    char buffer[MAX_LINE]; // Προσωρινός buffer για ανάγνωση
    // Διαβάζουμε μια γραμμή από το αρχείο - αν αποτύχει επιστρέφουμε NULL
    if (fgets(buffer, MAX_LINE, fp) == NULL) {
        return NULL; // Αποτυχία ανάγνωσης
    }
    buffer[strcspn(buffer, "\n")] = '\0'; // Αφαιρούμε το newline character από το τέλος
    char *str = (char*)malloc(strlen(buffer) + 1); // Δεσμεύουμε μνήμη για το string (+1 για το '\0')
    strcpy(str, buffer); // Αντιγράφουμε το περιεχόμενο από το buffer στη δυναμική μνήμη
    return str; // Επιστρέφουμε τον δείκτη στο string
}

// Συνάρτηση φόρτωσης δεδομένων από τα αρχεία κατά την εκκίνηση
void load_data() {
    FILE *fp; // Δείκτης αρχείου για ανάγνωση
    
    // === ΦΟΡΤΩΣΗ ΒΙΒΛΙΩΝ ===
    fp = fopen("books.txt", "r"); // Ανοίγουμε το αρχείο books.txt για ανάγνωση
    if (fp != NULL) { // Αν το αρχείο ανοίχτηκε επιτυχώς
        fscanf(fp, "%d\n", &book_count); // Διαβάζουμε το πλήθος βιβλίων από την πρώτη γραμμή
        if (book_count > 0) { // Αν υπάρχουν βιβλία
            // Δεσμεύουμε μνήμη για τον πίνακα βιβλίων (book_count * μέγεθος της δομής book)
            book_arr = (book*)malloc(book_count * sizeof(book));
            // Διαβάζουμε κάθε βιβλίο από το αρχείο
            for (int i = 0; i < book_count; i++) {
                book_arr[i].title = read_string(fp);        // Διαβάζουμε τον τίτλο
                fscanf(fp, "%d\n", &book_arr[i].release_date); // Διαβάζουμε το έτος έκδοσης
                fscanf(fp, "%f\n", &book_arr[i].price);        // Διαβάζουμε την τιμή
            }
        }
        fclose(fp); // Κλείνουμε το αρχείο
    } else { // Αν το αρχείο δεν υπάρχει
        printf("No existing books.txt file. Starting fresh.\n"); // Μήνυμα στον χρήστη
        book_count = 0; // Αρχικοποιούμε το πλήθος στο 0
    }
    
    // === ΦΟΡΤΩΣΗ ΣΥΓΓΡΑΦΕΩΝ ===
    fp = fopen("authors.txt", "r"); // Ανοίγουμε το αρχείο authors.txt για ανάγνωση
    if (fp != NULL) { // Αν το αρχείο ανοίχτηκε επιτυχώς
        fscanf(fp, "%d\n", &author_count); // Διαβάζουμε το πλήθος συγγραφέων
        if (author_count > 0) { // Αν υπάρχουν συγγραφείς
            // Δεσμεύουμε μνήμη για τον πίνακα συγγραφέων
            author_arr = (author*)malloc(author_count * sizeof(author));
            // Διαβάζουμε κάθε συγγραφέα από το αρχείο
            for (int i = 0; i < author_count; i++) {
                fscanf(fp, "%d\n", &author_arr[i].writer_id);  // Διαβάζουμε το ID
                author_arr[i].surname = read_string(fp);        // Διαβάζουμε το επώνυμο
                author_arr[i].name = read_string(fp);           // Διαβάζουμε το όνομα
                fscanf(fp, "%d\n", &author_arr[i].num_of_books); // Διαβάζουμε το πλήθος βιβλίων
            }
        }
        fclose(fp); // Κλείνουμε το αρχείο
    } else { // Αν το αρχείο δεν υπάρχει
        printf("No existing authors.txt file. Starting fresh.\n"); // Μήνυμα στον χρήστη
        author_count = 0; // Αρχικοποιούμε το πλήθος στο 0
    }
    
    // === ΦΟΡΤΩΣΗ ΣΧΕΣΕΩΝ ΣΥΓΓΡΑΦΕΑ-ΒΙΒΛΙΟΥ ===
    fp = fopen("writes.txt", "r"); // Ανοίγουμε το αρχείο writes.txt για ανάγνωση
    if (fp != NULL) { // Αν το αρχείο ανοίχτηκε επιτυχώς
        fscanf(fp, "%d\n", &writes_count); // Διαβάζουμε το πλήθος εγγραφών
        if (writes_count > 0) { // Αν υπάρχουν εγγραφές
            // Δεσμεύουμε μνήμη για τον πίνακα writes
            writes_arr = (writes*)malloc(writes_count * sizeof(writes));
            // Διαβάζουμε κάθε εγγραφή από το αρχείο
            for (int i = 0; i < writes_count; i++) {
                writes_arr[i].title = read_string(fp);          // Διαβάζουμε τον τίτλο βιβλίου
                fscanf(fp, "%d\n", &writes_arr[i].writer_id);   // Διαβάζουμε το ID συγγραφέα
            }
        }
        fclose(fp); // Κλείνουμε το αρχείο
    } else { // Αν το αρχείο δεν υπάρχει
        printf("No existing writes.txt file. Starting fresh.\n"); // Μήνυμα στον χρήστη
        writes_count = 0; // Αρχικοποιούμε το πλήθος στο 0
    }
}

// Συνάρτηση αποθήκευσης δεδομένων στα αρχεία κατά την έξοδο
void save_data() {
    FILE *fp; // Δείκτης αρχείου για εγγραφή
    
    // === ΑΠΟΘΗΚΕΥΣΗ ΒΙΒΛΙΩΝ ===
    fp = fopen("books.txt", "w"); // Ανοίγουμε το αρχείο books.txt για εγγραφή (mode "w" = write)
    fprintf(fp, "%d\n", book_count); // Γράφουμε πρώτα το πλήθος βιβλίων
    // Επαναλαμβάνουμε για κάθε βιβλίο στον πίνακα
    for (int i = 0; i < book_count; i++) {
        fprintf(fp, "%s\n", book_arr[i].title);              // Γράφουμε τον τίτλο
        fprintf(fp, "%d\n", book_arr[i].release_date);       // Γράφουμε το έτος έκδοσης
        fprintf(fp, "%.2f\n", book_arr[i].price);            // Γράφουμε την τιμή με 2 δεκαδικά
    }
    fclose(fp); // Κλείνουμε το αρχείο
    
    // === ΑΠΟΘΗΚΕΥΣΗ ΣΥΓΓΡΑΦΕΩΝ ===
    fp = fopen("authors.txt", "w"); // Ανοίγουμε το αρχείο authors.txt για εγγραφή
    fprintf(fp, "%d\n", author_count); // Γράφουμε το πλήθος συγγραφέων
    // Επαναλαμβάνουμε για κάθε συγγραφέα στον πίνακα
    for (int i = 0; i < author_count; i++) {
        fprintf(fp, "%d\n", author_arr[i].writer_id);        // Γράφουμε το ID
        fprintf(fp, "%s\n", author_arr[i].surname);          // Γράφουμε το επώνυμο
        fprintf(fp, "%s\n", author_arr[i].name);             // Γράφουμε το όνομα
        fprintf(fp, "%d\n", author_arr[i].num_of_books);     // Γράφουμε το πλήθος βιβλίων
    }
    fclose(fp); // Κλείνουμε το αρχείο
    
    // === ΑΠΟΘΗΚΕΥΣΗ ΣΧΕΣΕΩΝ ΣΥΓΓΡΑΦΕΑ-ΒΙΒΛΙΟΥ ===
    fp = fopen("writes.txt", "w"); // Ανοίγουμε το αρχείο writes.txt για εγγραφή
    fprintf(fp, "%d\n", writes_count); // Γράφουμε το πλήθος εγγραφών
    // Επαναλαμβάνουμε για κάθε εγγραφή στον πίνακα
    for (int i = 0; i < writes_count; i++) {
        fprintf(fp, "%s\n", writes_arr[i].title);            // Γράφουμε τον τίτλο βιβλίου
        fprintf(fp, "%d\n", writes_arr[i].writer_id);        // Γράφουμε το ID συγγραφέα
    }
    fclose(fp); // Κλείνουμε το αρχείο
}

// Συνάρτηση ταξινόμησης του πίνακα βιβλίων (αλφαβητικά με τον τίτλο)
// Χρησιμοποιεί Bubble Sort αλγόριθμο
void sort_books() {
    // Εξωτερικός βρόχος - περνάει book_count-1 φορές
    for (int i = 0; i < book_count - 1; i++) {
        // Εσωτερικός βρόχος - συγκρίνει γειτονικά στοιχεία
        for (int j = 0; j < book_count - i - 1; j++) {
            // Συγκρίνουμε τους τίτλους των βιβλίων j και j+1
            if (strcmp(book_arr[j].title, book_arr[j + 1].title) > 0) {
                // Αν το j βιβλίο έχει μεγαλύτερο τίτλο (αλφαβητικά), τα ανταλλάσσουμε
                book temp = book_arr[j];          // Προσωρινή αποθήκευση του j
                book_arr[j] = book_arr[j + 1];    // Μετακίνηση του j+1 στη θέση j
                book_arr[j + 1] = temp;           // Τοποθέτηση του temp στη θέση j+1
            }
        }
    }
}

// Συνάρτηση ταξινόμησης του πίνακα συγγραφέων (με βάση το ID)
// Χρησιμοποιεί Bubble Sort αλγόριθμο
void sort_authors() {
    // Εξωτερικός βρόχος - περνάει author_count-1 φορές
    for (int i = 0; i < author_count - 1; i++) {
        // Εσωτερικός βρόχος - συγκρίνει γειτονικά στοιχεία
        for (int j = 0; j < author_count - i - 1; j++) {
            // Συγκρίνουμε τα IDs των συγγραφέων j και j+1
            if (author_arr[j].writer_id > author_arr[j + 1].writer_id) {
                // Αν το ID του j είναι μεγαλύτερο, τα ανταλλάσσουμε
                author temp = author_arr[j];      // Προσωρινή αποθήκευση του j
                author_arr[j] = author_arr[j + 1]; // Μετακίνηση του j+1 στη θέση j
                author_arr[j + 1] = temp;         // Τοποθέτηση του temp στη θέση j+1
            }
        }
    }
}

// Συνάρτηση ταξινόμησης του πίνακα writes (πρώτα με writer_id, μετά με τίτλο)
// Χρησιμοποιεί Bubble Sort αλγόριθμο
void sort_writes() {
    // Εξωτερικός βρόχος - περνάει writes_count-1 φορές
    for (int i = 0; i < writes_count - 1; i++) {
        // Εσωτερικός βρόχος - συγκρίνει γειτονικά στοιχεία
        for (int j = 0; j < writes_count - i - 1; j++) {
            // Υπολογίζουμε τη διαφορά των writer_id
            int cmp = (writes_arr[j].writer_id - writes_arr[j + 1].writer_id);
            // Αν το writer_id του j είναι μεγαλύτερο ΄Η ίσο αλλά ο τίτλος είναι μεγαλύτερος
            if (cmp > 0 || (cmp == 0 && strcmp(writes_arr[j].title, writes_arr[j + 1].title) > 0)) {
                // Ανταλλάσσουμε τα στοιχεία
                writes temp = writes_arr[j];      // Προσωρινή αποθήκευση του j
                writes_arr[j] = writes_arr[j + 1]; // Μετακίνηση του j+1 στη θέση j
                writes_arr[j + 1] = temp;         // Τοποθέτηση του temp στη θέση j+1
            }
        }
    }
}

// Δυαδική αναζήτηση (Binary Search) για βιβλίο με βάση τον τίτλο
// Επιστρέφει το index του βιβλίου αν βρεθεί, αλλιώς -1
int binary_search_book(char *title) {
    int left = 0;                    // Αριστερό άκρο του εύρους αναζήτησης
    int right = book_count - 1;      // Δεξί άκρο του εύρους αναζήτησης
    // Όσο το αριστερό άκρο είναι μικρότερο ή ίσο του δεξιού
    while (left <= right) {
        int mid = left + (right - left) / 2; // Υπολογίζουμε το μεσαίο στοιχείο
        int cmp = strcmp(book_arr[mid].title, title); // Συγκρίνουμε τους τίτλους
        if (cmp == 0) return mid;    // Αν είναι ίσοι, βρήκαμε το βιβλίο - επιστρέφουμε το index
        if (cmp < 0) left = mid + 1; // Αν ο μεσαίος είναι μικρότερος, ψάχνουμε στο δεξί μισό
        else right = mid - 1;        // Αν ο μεσαίος είναι μεγαλύτερος, ψάχνουμε στο αριστερό μισό
    }
    return -1; // Δεν βρέθηκε το βιβλίο
}

// Δυαδική αναζήτηση (Binary Search) για συγγραφέα με βάση το ID
// Επιστρέφει το index του συγγραφέα αν βρεθεί, αλλιώς -1
int binary_search_author_by_id(int id) {
    int left = 0;                    // Αριστερό άκρο του εύρους αναζήτησης
    int right = author_count - 1;    // Δεξί άκρο του εύρους αναζήτησης
    // Όσο το αριστερό άκρο είναι μικρότερο ή ίσο του δεξιού
    while (left <= right) {
        int mid = left + (right - left) / 2; // Υπολογίζουμε το μεσαίο στοιχείο
        if (author_arr[mid].writer_id == id) return mid; // Αν βρέθηκε, επιστρέφουμε το index
        if (author_arr[mid].writer_id < id) left = mid + 1; // Ψάχνουμε στο δεξί μισό
        else right = mid - 1;        // Ψάχνουμε στο αριστερό μισό
    }
    return -1; // Δεν βρέθηκε ο συγγραφέας
}

// Γραμμική αναζήτηση (Linear Search) για συγγραφέα με βάση το επώνυμο
// Επιστρέφει το index του πρώτου συγγραφέα που βρέθηκε, αλλιώς -1
// Σημείωση: Χρησιμοποιούμε γραμμική αναζήτηση γιατί μπορεί να υπάρχουν πολλοί με το ίδιο επώνυμο
int binary_search_author_by_surname(char *surname) {
    // Επαναλαμβάνουμε για κάθε συγγραφέα στον πίνακα
    for (int i = 0; i < author_count; i++) {
        // Συγκρίνουμε το επώνυμο
        if (strcmp(author_arr[i].surname, surname) == 0) {
            return i; // Βρέθηκε - επιστρέφουμε το index
        }
    }
    return -1; // Δεν βρέθηκε συγγραφέας με αυτό το επώνυμο
}

// Δυαδική αναζήτηση στον πίνακα writes με βάση το writer_id και τον τίτλο
// Επιστρέφει το index της εγγραφής αν βρεθεί, αλλιώς -1
int binary_search_writes(int writer_id, char *title) {
    int left = 0;                    // Αριστερό άκρο του εύρους αναζήτησης
    int right = writes_count - 1;    // Δεξί άκρο του εύρους αναζήτησης
    // Όσο το αριστερό άκρο είναι μικρότερο ή ίσο του δεξιού
    while (left <= right) {
        int mid = left + (right - left) / 2; // Υπολογίζουμε το μεσαίο στοιχείο
        if (writes_arr[mid].writer_id == writer_id) { // Αν το writer_id ταιριάζει
            int cmp = strcmp(writes_arr[mid].title, title); // Συγκρίνουμε τους τίτλους
            if (cmp == 0) return mid; // Αν και ο τίτλος ταιριάζει, βρέθηκε
            // Γραμμική αναζήτηση γύρω από αυτό το σημείο για ακριβές ταίριασμα
            int i = mid;
            // Ψάχνουμε προς τα αριστερά
            while (i >= 0 && writes_arr[i].writer_id == writer_id) {
                if (strcmp(writes_arr[i].title, title) == 0) return i; // Βρέθηκε
                i--; // Μειώνουμε το index
            }
            i = mid + 1; // Ξεκινάμε από την επόμενη θέση
            // Ψάχνουμε προς τα δεξιά
            while (i < writes_count && writes_arr[i].writer_id == writer_id) {
                if (strcmp(writes_arr[i].title, title) == 0) return i; // Βρέθηκε
                i++; // Αυξάνουμε το index
            }
            return -1; // Δεν βρέθηκε με αυτό το συνδυασμό
        }
        // Συνεχίζουμε τη δυαδική αναζήτηση με βάση το writer_id
        if (writes_arr[mid].writer_id < writer_id) left = mid + 1; // Ψάχνουμε δεξιά
        else right = mid - 1; // Ψάχνουμε αριστερά
    }
    return -1; // Δεν βρέθηκε
}

// Συνάρτηση εισαγωγής βιβλίου με διατήρηση ταξινόμησης
void insert_sorted_book(book new_book) {
    // Επαναδέσμευση μνήμης για να χωρέσει ένα ακόμη βιβλίο
    // realloc αλλάζει το μέγεθος του πίνακα διατηρώντας τα υπάρχοντα δεδομένα
    book_arr = (book*)realloc(book_arr, (book_count + 1) * sizeof(book));
    book_arr[book_count] = new_book; // Τοποθετούμε το νέο βιβλίο στο τέλος
    book_count++;                    // Αυξάνουμε το πλήθος βιβλίων
    sort_books();                    // Ταξινομούμε τον πίνακα για να παραμείνει σε σειρά
}

// Συνάρτηση εισαγωγής συγγραφέα με διατήρηση ταξινόμησης
void insert_sorted_author(author new_author) {
    // Επαναδέσμευση μνήμης για να χωρέσει ένας ακόμη συγγραφέας
    author_arr = (author*)realloc(author_arr, (author_count + 1) * sizeof(author));
    author_arr[author_count] = new_author; // Τοποθετούμε τον νέο συγγραφέα στο τέλος
    author_count++;                        // Αυξάνουμε το πλήθος συγγραφέων
    sort_authors();                        // Ταξινομούμε τον πίνακα για να παραμείνει σε σειρά
}

// Συνάρτηση εισαγωγής εγγραφής writes με διατήρηση ταξινόμησης
void insert_sorted_writes(writes new_write) {
    // Επαναδέσμευση μνήμης για να χωρέσει μία ακόμη εγγραφή
    writes_arr = (writes*)realloc(writes_arr, (writes_count + 1) * sizeof(writes));
    writes_arr[writes_count] = new_write; // Τοποθετούμε τη νέα εγγραφή στο τέλος
    writes_count++;                       // Αυξάνουμε το πλήθος εγγραφών
    sort_writes();                        // Ταξινομούμε τον πίνακα για να παραμείνει σε σειρά
}

// Συνάρτηση εισαγωγής νέου συγγραφέα από τον χρήστη
void insert_author() {
    author new_author;       // Δημιουργούμε μια νέα δομή author
    char buffer[MAX_LINE];   // Buffer για ανάγνωση εισόδου
    
    // Ζητάμε το επώνυμο του συγγραφέα
    printf("Enter author surname: ");
    fgets(buffer, MAX_LINE, stdin);        // Διαβάζουμε τη γραμμή από το stdin
    buffer[strcspn(buffer, "\n")] = '\0';  // Αφαιρούμε το newline character
    // Δεσμεύουμε μνήμη για το επώνυμο και το αποθηκεύουμε
    new_author.surname = (char*)malloc(strlen(buffer) + 1);
    strcpy(new_author.surname, buffer);    // Αντιγράφουμε το string στη δυναμική μνήμη
    
    // Ζητάμε το όνομα του συγγραφέα
    printf("Enter author name: ");
    fgets(buffer, MAX_LINE, stdin);        // Διαβάζουμε τη γραμμή από το stdin
    buffer[strcspn(buffer, "\n")] = '\0';  // Αφαιρούμε το newline character
    // Δεσμεύουμε μνήμη για το όνομα και το αποθηκεύουμε
    new_author.name = (char*)malloc(strlen(buffer) + 1);
    strcpy(new_author.name, buffer);       // Αντιγράφουμε το string στη δυναμική μνήμη
    
    // Ανάθεση ID αυτόματα - βρίσκουμε το μέγιστο ID που υπάρχει
    int max_id = 0; // Αρχικοποιούμε το max_id στο 0
    // Επαναλαμβάνουμε σε όλους τους συγγραφείς
    for (int i = 0; i < author_count; i++) {
        // Αν βρούμε μεγαλύτερο ID, το ενημερώνουμε
        if (author_arr[i].writer_id > max_id) {
            max_id = author_arr[i].writer_id;
        }
    }
    new_author.writer_id = max_id + 1;  // Το νέο ID είναι το μέγιστο + 1
    new_author.num_of_books = 0;        // Αρχικά ο συγγραφέας δεν έχει βιβλία
    
    // Εισαγωγή του νέου συγγραφέα στον πίνακα με διατήρηση ταξινόμησης
    insert_sorted_author(new_author);
    // Μήνυμα επιβεβαίωσης στον χρήστη
    printf("Author inserted successfully with ID: %d\n", new_author.writer_id);
}

// Συνάρτηση εισαγωγής νέου βιβλίου από τον χρήστη
void insert_book() {
    book new_book;           // Δημιουργούμε μια νέα δομή book
    char buffer[MAX_LINE];   // Buffer για ανάγνωση εισόδου
    
    // Ζητάμε τον τίτλο του βιβλίου
    printf("Enter book title: ");
    fgets(buffer, MAX_LINE, stdin);        // Διαβάζουμε τη γραμμή
    buffer[strcspn(buffer, "\n")] = '\0';  // Αφαιρούμε το newline
    // Δεσμεύουμε μνήμη για τον τίτλο
    new_book.title = (char*)malloc(strlen(buffer) + 1);
    strcpy(new_book.title, buffer);        // Αντιγράφουμε τον τίτλο
    
    // Ζητάμε το έτος έκδοσης
    printf("Enter release date (year): ");
    scanf("%d", &new_book.release_date);   // Διαβάζουμε ακέραιο
    
    // Ζητάμε την τιμή
    printf("Enter price: ");
    scanf("%f", &new_book.price);          // Διαβάζουμε δεκαδικό
    getchar(); // Καταναλώνουμε το newline που έμεινε από το scanf
    
    // Ελέγχουμε αν το βιβλίο υπάρχει ήδη
    if (binary_search_book(new_book.title) != -1) {
        printf("Book already exists!\n");  // Μήνυμα λάθους
        free(new_book.title);              // Απελευθερώνουμε τη μνήμη που δεσμεύσαμε
        return;                            // Τερματίζουμε τη συνάρτηση
    }
    
    // Εισαγωγή του βιβλίου στον πίνακα
    insert_sorted_book(new_book);
    
    // Ζητάμε το πλήθος των συγγραφέων
    printf("Enter number of authors: ");
    int num_authors;                       // Μεταβλητή για το πλήθος συγγραφέων
    scanf("%d", &num_authors);             // Διαβάζουμε το πλήθος
    getchar();                             // Καταναλώνουμε το newline
    
    // Επαναλαμβάνουμε για κάθε συγγραφέα
    for (int i = 0; i < num_authors; i++) {
        printf("Enter author surname #%d: ", i + 1); // Μήνυμα με αύξοντα αριθμό
        fgets(buffer, MAX_LINE, stdin);    // Διαβάζουμε το επώνυμο
        buffer[strcspn(buffer, "\n")] = '\0'; // Αφαιρούμε το newline
        
        // Αναζητούμε τον συγγραφέα με βάση το επώνυμο
        int author_idx = binary_search_author_by_surname(buffer);
        int author_id;                     // Μεταβλητή για το ID του συγγραφέα
        
        // Αν ο συγγραφέας δεν βρέθηκε
        if (author_idx == -1) {
            // Δημιουργούμε νέο συγγραφέα
            author new_author;
            // Δεσμεύουμε μνήμη για το επώνυμο
            new_author.surname = (char*)malloc(strlen(buffer) + 1);
            strcpy(new_author.surname, buffer); // Αντιγράφουμε το επώνυμο
            
            // Ζητάμε το όνομα του συγγραφέα
            printf("Author not found. Enter author name: ");
            fgets(buffer, MAX_LINE, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            // Δεσμεύουμε μνήμη για το όνομα
            new_author.name = (char*)malloc(strlen(buffer) + 1);
            strcpy(new_author.name, buffer);
            
            // Βρίσκουμε το μέγιστο ID για να αναθέσουμε νέο
            int max_id = 0;
            for (int j = 0; j < author_count; j++) {
                if (author_arr[j].writer_id > max_id) {
                    max_id = author_arr[j].writer_id;
                }
            }
            new_author.writer_id = max_id + 1; // Νέο ID
            new_author.num_of_books = 1;       // Έχει γράψει 1 βιβλίο (το τρέχον)
            
            // Εισαγωγή του νέου συγγραφέα
            insert_sorted_author(new_author);
            author_id = new_author.writer_id;  // Κρατάμε το ID
            printf("New author created with ID: %d\n", author_id);
        } else {
            // Ο συγγραφέας υπάρχει - παίρνουμε το ID του
            author_id = author_arr[author_idx].writer_id;
            // Αυξάνουμε το πλήθος βιβλίων του
            author_arr[author_idx].num_of_books++;
        }
        
        // Προσθήκη στον πίνακα writes (σχέση συγγραφέα-βιβλίου)
        writes new_write;
        // Δεσμεύουμε μνήμη για τον τίτλο του βιβλίου
        new_write.title = (char*)malloc(strlen(new_book.title) + 1);
        strcpy(new_write.title, new_book.title); // Αντιγράφουμε τον τίτλο
        new_write.writer_id = author_id;         // Αναθέτουμε το ID του συγγραφέα
        insert_sorted_writes(new_write);         // Εισαγωγή στον πίνακα writes
    }
    
    printf("Book inserted successfully!\n"); // Μήνυμα επιτυχίας
}

// Συνάρτηση αναζήτησης συγγραφέα με βάση το επώνυμο
void search_author() {
    char buffer[MAX_LINE];   // Buffer για το επώνυμο προς αναζήτηση
    // Ζητάμε από τον χρήστη το επώνυμο
    printf("Enter author surname to search: ");
    fgets(buffer, MAX_LINE, stdin);        // Διαβάζουμε τη γραμμή
    buffer[strcspn(buffer, "\n")] = '\0';  // Αφαιρούμε το newline
    
    int found = 0; // Flag για να δούμε αν βρέθηκαν αποτελέσματα
    // Επαναλαμβάνουμε σε όλους τους συγγραφείς
    for (int i = 0; i < author_count; i++) {
        // Συγκρίνουμε το επώνυμο
        if (strcmp(author_arr[i].surname, buffer) == 0) {
            found = 1; // Βρέθηκε τουλάχιστον ένας συγγραφέας
            // Εμφάνιση πληροφοριών συγγραφέα
            printf("\n--- Author Information ---\n");
            printf("ID: %d\n", author_arr[i].writer_id);
            printf("Name: %s %s\n", author_arr[i].name, author_arr[i].surname);
            printf("Number of books: %d\n", author_arr[i].num_of_books);
            printf("Books:\n"); // Τίτλος λίστας βιβλίων
            
            // Βρίσκουμε όλα τα βιβλία αυτού του συγγραφέα
            for (int j = 0; j < writes_count; j++) {
                // Αν το writer_id ταιριάζει
                if (writes_arr[j].writer_id == author_arr[i].writer_id) {
                    // Βρίσκουμε τις λεπτομέρειες του βιβλίου
                    int book_idx = binary_search_book(writes_arr[j].title);
                    if (book_idx != -1) { // Αν βρέθηκε το βιβλίο
                        // Εμφανίζουμε τίτλο, έτος, τιμή
                        printf("  - %s (%d) - %.2f EUR\n", 
                               book_arr[book_idx].title, 
                               book_arr[book_idx].release_date, 
                               book_arr[book_idx].price);
                    }
                }
            }
            printf("\n"); // Κενή γραμμή για διαχωρισμό
        }
    }
    
    // Αν δεν βρέθηκε κανένας συγγραφέας
    if (!found) {
        printf("No author found with surname: %s\n", buffer);
    }
}

// Συνάρτηση αναζήτησης βιβλίου με βάση τον τίτλο
void search_book() {
    char buffer[MAX_LINE];   // Buffer για τον τίτλο προς αναζήτηση
    // Ζητάμε από τον χρήστη τον τίτλο
    printf("Enter book title to search: ");
    fgets(buffer, MAX_LINE, stdin);        // Διαβάζουμε τη γραμμή
    buffer[strcspn(buffer, "\n")] = '\0';  // Αφαιρούμε το newline
    
    // Χρησιμοποιούμε δυαδική αναζήτηση για να βρούμε το βιβλίο
    int idx = binary_search_book(buffer);
    if (idx == -1) { // Αν δεν βρέθηκε (επιστρέφει -1)
        printf("Book not found: %s\n", buffer); // Μήνυμα λάθους
        return; // Τερματίζουμε τη συνάρτηση
    }
    
    // Εμφάνιση πληροφοριών βιβλίου
    printf("\n--- Book Information ---\n");
    printf("Title: %s\n", book_arr[idx].title);           // Τίτλος
    printf("Release Date: %d\n", book_arr[idx].release_date); // Έτος έκδοσης
    printf("Price: %.2f EUR\n", book_arr[idx].price);     // Τιμή
    printf("Authors:\n"); // Τίτλος λίστας συγγραφέων
    
    // Βρίσκουμε όλους τους συγγραφείς του βιβλίου
    for (int i = 0; i < writes_count; i++) {
        // Αν ο τίτλος ταιριάζει
        if (strcmp(writes_arr[i].title, buffer) == 0) {
            // Βρίσκουμε τις λεπτομέρειες του συγγραφέα με το ID
            int author_idx = binary_search_author_by_id(writes_arr[i].writer_id);
            if (author_idx != -1) { // Αν βρέθηκε ο συγγραφέας
                // Εμφανίζουμε όνομα, επώνυμο, ID
                printf("  - %s %s (ID: %d)\n", 
                       author_arr[author_idx].name, 
                       author_arr[author_idx].surname, 
                       author_arr[author_idx].writer_id);
            }
        }
    }
    printf("\n"); // Κενή γραμμή για διαχωρισμό
}

// Συνάρτηση διαγραφής συγγραφέα με βάση το ID
void delete_author() {
    int id; // Μεταβλητή για το ID προς διαγραφή
    // Ζητάμε από τον χρήστη το ID
    printf("Enter author ID to delete: ");
    scanf("%d", &id);        // Διαβάζουμε το ID
    getchar();               // Καταναλώνουμε το newline
    
    // Αναζητούμε τον συγγραφέα με δυαδική αναζήτηση
    int idx = binary_search_author_by_id(id);
    if (idx == -1) { // Αν δεν βρέθηκε
        printf("Author with ID %d not found.\n", id); // Μήνυμα λάθους
        return; // Τερματίζουμε
    }
    
    // Βρίσκουμε και διαγράφουμε όλα τα βιβλία του συγγραφέα
    int i = 0; // Δείκτης για τον πίνακα writes
    // Επαναλαμβάνουμε όσο υπάρχουν εγγραφές
    while (i < writes_count) {
        // Αν η εγγραφή αντιστοιχεί στον συγγραφέα προς διαγραφή
        if (writes_arr[i].writer_id == id) {
            char *title = writes_arr[i].title; // Κρατάμε τον τίτλο του βιβλίου
            
            // Μετράμε πόσοι συγγραφείς έχουν γράψει αυτό το βιβλίο
            int author_count_for_book = 0;
            for (int j = 0; j < writes_count; j++) {
                // Αν ο τίτλος ταιριάζει, αυξάνουμε τον μετρητή
                if (strcmp(writes_arr[j].title, title) == 0) {
                    author_count_for_book++;
                }
            }
            
            // Αν το βιβλίο είναι μονογραφία (1 συγγραφέας), το διαγράφουμε
            if (author_count_for_book == 1) {
                int book_idx = binary_search_book(title); // Βρίσκουμε το βιβλίο
                if (book_idx != -1) { // Αν βρέθηκε
                    free(book_arr[book_idx].title); // Απελευθερώνουμε τη μνήμη του τίτλου
                    // Μετακινούμε όλα τα επόμενα στοιχεία μία θέση αριστερά
                    for (int k = book_idx; k < book_count - 1; k++) {
                        book_arr[k] = book_arr[k + 1];
                    }
                    book_count--; // Μειώνουμε το πλήθος βιβλίων
                    // Επαναδεσμεύουμε μνήμη με το νέο μέγεθος
                    book_arr = (book*)realloc(book_arr, book_count * sizeof(book));
                }
            }
            
            // Διαγραφή από τον πίνακα writes
            free(writes_arr[i].title); // Απελευθερώνουμε τη μνήμη του τίτλου
            // Μετακινούμε όλα τα επόμενα στοιχεία μία θέση αριστερά
            for (int k = i; k < writes_count - 1; k++) {
                writes_arr[k] = writes_arr[k + 1];
            }
            writes_count--; // Μειώνουμε το πλήθος εγγραφών
            // Επαναδεσμεύουμε μνήμη με το νέο μέγεθος
            writes_arr = (writes*)realloc(writes_arr, writes_count * sizeof(writes));
        } else {
            i++; // Προχωράμε στην επόμενη εγγραφή μόνο αν δεν διαγράψαμε
        }
    }
    
    // Διαγραφή του συγγραφέα από τον πίνακα
    free(author_arr[idx].surname); // Απελευθερώνουμε το επώνυμο
    free(author_arr[idx].name);    // Απελευθερώνουμε το όνομα
    // Μετακινούμε όλα τα επόμενα στοιχεία μία θέση αριστερά
    for (int i = idx; i < author_count - 1; i++) {
        author_arr[i] = author_arr[i + 1];
    }
    author_count--; // Μειώνουμε το πλήθος συγγραφέων
    // Επαναδεσμεύουμε μνήμη με το νέο μέγεθος
    author_arr = (author*)realloc(author_arr, author_count * sizeof(author));
    
    printf("Author deleted successfully.\n"); // Μήνυμα επιτυχίας
}

// Συνάρτηση διαγραφής βιβλίου με βάση τον τίτλο
void delete_book() {
    char buffer[MAX_LINE];   // Buffer για τον τίτλο προς διαγραφή
    // Ζητάμε από τον χρήστη τον τίτλο
    printf("Enter book title to delete: ");
    fgets(buffer, MAX_LINE, stdin);        // Διαβάζουμε τη γραμμή
    buffer[strcspn(buffer, "\n")] = '\0';  // Αφαιρούμε το newline
    
    // Αναζητούμε το βιβλίο με δυαδική αναζήτηση
    int idx = binary_search_book(buffer);
    if (idx == -1) { // Αν δεν βρέθηκε
        printf("Book not found: %s\n", buffer); // Μήνυμα λάθους
        return; // Τερματίζουμε
    }
    
    // Διαγραφή από τον πίνακα writes και ενημέρωση πλήθους βιβλίων συγγραφέων
    int i = 0; // Δείκτης για τον πίνακα writes
    // Επαναλαμβάνουμε όσο υπάρχουν εγγραφές
    while (i < writes_count) {
        // Αν ο τίτλος ταιριάζει με το βιβλίο προς διαγραφή
        if (strcmp(writes_arr[i].title, buffer) == 0) {
            // Βρίσκουμε τον συγγραφέα για να ενημερώσουμε το πλήθος βιβλίων του
            int author_idx = binary_search_author_by_id(writes_arr[i].writer_id);
            if (author_idx != -1) { // Αν βρέθηκε ο συγγραφέας
                author_arr[author_idx].num_of_books--; // Μειώνουμε το πλήθος βιβλίων
            }
            
            // Διαγραφή της εγγραφής από τον πίνακα writes
            free(writes_arr[i].title); // Απελευθερώνουμε τη μνήμη του τίτλου
            // Μετακινούμε όλα τα επόμενα στοιχεία μία θέση αριστερά
            for (int k = i; k < writes_count - 1; k++) {
                writes_arr[k] = writes_arr[k + 1];
            }
            writes_count--; // Μειώνουμε το πλήθος εγγραφών
            // Επαναδεσμεύουμε μνήμη με το νέο μέγεθος
            writes_arr = (writes*)realloc(writes_arr, writes_count * sizeof(writes));
        } else {
            i++; // Προχωράμε στην επόμενη εγγραφή μόνο αν δεν διαγράψαμε
        }
    }
    
    // Διαγραφή του βιβλίου από τον πίνακα βιβλίων
    free(book_arr[idx].title); // Απελευθερώνουμε τη μνήμη του τίτλου
    // Μετακινούμε όλα τα επόμενα στοιχεία μία θέση αριστερά
    for (int i = idx; i < book_count - 1; i++) {
        book_arr[i] = book_arr[i + 1];
    }
    book_count--; // Μειώνουμε το πλήθος βιβλίων
    // Επαναδεσμεύουμε μνήμη με το νέο μέγεθος
    book_arr = (book*)realloc(book_arr, book_count * sizeof(book));
    
    printf("Book deleted successfully.\n"); // Μήνυμα επιτυχίας
}

// Συνάρτηση απελευθέρωσης όλης της δυναμικής μνήμης πριν το τέλος του προγράμματος
void free_memory() {
    // Απελευθέρωση μνήμης για βιβλία
    for (int i = 0; i < book_count; i++) {
        free(book_arr[i].title); // Απελευθερώνουμε κάθε τίτλο βιβλίου
    }
    free(book_arr); // Απελευθερώνουμε τον πίνακα βιβλίων
    
    // Απελευθέρωση μνήμης για συγγραφείς
    for (int i = 0; i < author_count; i++) {
        free(author_arr[i].surname); // Απελευθερώνουμε κάθε επώνυμο
        free(author_arr[i].name);    // Απελευθερώνουμε κάθε όνομα
    }
    free(author_arr); // Απελευθερώνουμε τον πίνακα συγγραφέων
    
    // Απελευθέρωση μνήμης για εγγραφές writes
    for (int i = 0; i < writes_count; i++) {
        free(writes_arr[i].title); // Απελευθερώνουμε κάθε τίτλο
    }
    free(writes_arr); // Απελευθερώνουμε τον πίνακα writes
}
