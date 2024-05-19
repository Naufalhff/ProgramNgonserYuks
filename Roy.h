#ifndef ROY_H
#define ROY_H

typedef struct User {
    int id;
    char name[50];
    long phone;
    char event[50];
    int quantity;
    char category[10];
    double price;
    double paid;
    int validation;
    struct User* next;
} User;

typedef struct Tree {
    User* vip;
    User* reguler;
} Tree;

User* createUser(int id, char* name, long phone, char* event, int quantity, char* category, double price, double paid, int validation);

void initTree(Tree* tree);
void addUserToTree(Tree* tree, User* user);
void readAndValidateData(const char* filename, Tree* tree);
void writeValidatedData(const char* filename, Tree* tree);
void printVIPQueue(Tree* tree);
void printRegulerQueue(Tree* tree);


#endif
