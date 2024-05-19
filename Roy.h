#ifndef ROY_H
#define ROY_H

// Struktur untuk menyimpan data pengguna
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


void readAndValidateData(const char* filename);
void enqueue(addressKonser first, int idKonser, char *category, int id, char *name, int quantity);

#endif
