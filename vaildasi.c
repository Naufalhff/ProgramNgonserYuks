#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Struktur untuk node VIP dan Reguler
typedef struct Tree {
    User* vip;
    User* reguler;
} Tree;

// Fungsi untuk membuat node user baru
User* createUser(int id, char* name, long phone, char* event, int quantity, char* category, double price, double paid, int validation) {
    User* newUser = (User*)malloc(sizeof(User));
    newUser->id = id;
    strcpy(newUser->name, name);
    newUser->phone = phone;
    strcpy(newUser->event, event);
    newUser->quantity = quantity;
    strcpy(newUser->category, category);
    newUser->price = price;
    newUser->paid = paid;
    newUser->validation = validation;
    newUser->next = NULL;
    return newUser;
}

// Fungsi untuk menambahkan user ke dalam tree
void addUserToTree(Tree* tree, User* user) {
    if (strcmp(user->category, "VIP") == 0) {
        user->next = tree->vip;
        tree->vip = user;
    } else {
        user->next = tree->reguler;
        tree->reguler = user;
    }
}

// Fungsi untuk membaca data dari file dan memvalidasi pembayaran
void readAndValidateData(const char* filename, Tree* tree) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Gagal membuka file");
        return;
    }

    int id, quantity;
    char name[50], event[50], category[10];
    long phone;
    double price, paid;

    while (fscanf(file, "%d %s %ld %s %d %s %lf %lf", &id, name, &phone, event, &quantity, category, &price, &paid) != EOF) {
        int validation = (paid < price) ? -1 : (paid > price) ? 1 : 0;
        User* user = createUser(id, name, phone, event, quantity, category, price, paid, validation);
        addUserToTree(tree, user);
    }

    fclose(file);
}

// Fungsi untuk menulis data yang sudah divalidasi ke dalam file
void writeValidatedData(const char* filename, Tree* tree) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Gagal membuka file");
        return;
    }

    User* current = tree->vip;
    while (current) {
        fprintf(file, "%d %s %ld %s %d %s %lf %lf %d\n", current->id, current->name, current->phone, current->event, current->quantity, current->category, current->price, current->paid, current->validation);
        current = current->next;
    }

    current = tree->reguler;
    while (current) {
        fprintf(file, "%d %s %ld %s %d %s %lf %lf %d\n", current->id, current->name, current->phone, current->event, current->quantity, current->category, current->price, current->paid, current->validation);
        current = current->next;
    }

    fclose(file);
}

// Fungsi untuk menampilkan antrian
void printQueue(User* head) {
    User* current = head;
    while (current) {
        printf("ID: %d, Nama: %s, Telp: %ld, Event: %s, Quantity: %d, Kategori: %s, Harga: %.2f, Dibayar: %.2f, Validasi: %d\n",
               current->id, current->name, current->phone, current->event, current->quantity, current->category, current->price, current->paid, current->validation);
        current = current->next;
    }
}

// Fungsi untuk menampilkan antrian VIP
void printVIPQueue(Tree* tree) {
    printf("Antrian VIP:\n");
    printQueue(tree->vip);
}

// Fungsi untuk menampilkan antrian Reguler
void printRegulerQueue(Tree* tree) {
    printf("Antrian Reguler:\n");
    printQueue(tree->reguler);
}

int main() {
    Tree tree = {NULL, NULL};

    // Baca dan validasi data dari file
    readAndValidateData("datauser.txt", &tree);

    // Tulis data yang sudah divalidasi ke file
    writeValidatedData("validated_data.txt", &tree);

    // Tampilkan antrian VIP
    printVIPQueue(&tree);

    // Tampilkan antrian Reguler
    printRegulerQueue(&tree);

    return 0;
}

