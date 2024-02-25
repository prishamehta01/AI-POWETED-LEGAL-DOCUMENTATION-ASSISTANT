#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

// Structure to represent a legal clause
struct clause {
    char text[MAX_LENGTH];
    struct clause* link;
};
typedef struct clause* CLAUSE;

CLAUSE getClause() {
    CLAUSE x = (CLAUSE)malloc(sizeof(struct clause));
    if (x == NULL) {
        printf("Memory not allocated");
        exit(EXIT_FAILURE);
    }
    return x;
}

CLAUSE insert_clause(CLAUSE first) {
    CLAUSE temp, cur;
    temp = getClause();
    printf("Enter the Clause to be added:\n");
    fgets(temp->text, MAX_LENGTH, stdin);
    temp->text[strcspn(temp->text, "\n")] = '\0'; // Remove newline character
    temp->link = NULL;

    if (first == NULL) {
        return temp;
    }

    cur = first;
    while (cur->link != NULL) {
        cur = cur->link;
    }
    cur->link = temp;
    return first;
}

void displayClauses(CLAUSE first) {
    if (first == NULL) {
        printf("No clauses found\n");
        return;
    }
    CLAUSE cur = first;
    printf("List of Clauses:\n");
    while (cur != NULL) {
        printf("%s\n", cur->text);
        cur = cur->link;
    }
}

CLAUSE delete_clause(CLAUSE first, const char* clause_text) {
    if (first == NULL) {
        printf("List is empty\n");
        return NULL;
    }

    CLAUSE prev = NULL;
    CLAUSE current = first;

    while (current != NULL) {
        if (strcmp(current->text, clause_text) == 0) {
            if (prev == NULL) {
                first = current->link; // Update first if deleting the first node
            } else {
                prev->link = current->link; // Remove current node from the list
            }
            free(current); // Free memory
            return first;
        }
        prev = current;
        current = current->link;
    }

    printf("Clause not found\n");
    return first; // Return original list if clause not found
}

int main() {
    CLAUSE first = NULL;
    int ch;
    char clause_text[MAX_LENGTH];

    while (1) {
        printf("Enter the choice:\n1.Insert clause\n2.Display Clause\n3.Delete Clause\n4.Exit\n");
        scanf(" %d", &ch);
        getchar(); // Consume newline character

        switch (ch) {
            case 1:
                first = insert_clause(first);
                break;
            case 2:
                displayClauses(first);
                break;
            case 3:
                printf("Enter the clause to delete:\n ");
                fgets(clause_text, MAX_LENGTH, stdin);
                clause_text[strcspn(clause_text, "\n")] = '\0'; // Remove newline character
                first = delete_clause(first, clause_text);
                break;
            case 4:
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    }
    return 0;
}
