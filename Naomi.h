#ifndef NAOMI_H
#define NAOMI_H

#include <time.h>

#define MAX_KONSER 100

int login();
int loginAdmin();

typedef struct Person {
    char username[100];
    char password[100];
} Person;

typedef struct QueueNode {
    Person info;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

void initQueue(Queue* q);
int isEmpty(Queue* q);
void enqueue(Queue* q, Person p);
Person dequeue(Queue* q);
void displayQueue(Queue* q);
void registrasi(Queue* q);
void simpanDataRegistrasi(Queue* q);
void clearInputBuffer();
void encryptDecrypt(char *input, char *output);

//struct Konser {
//    int id;
//    char nama[50];
//    struct tm tanggal;
//    char tempat[50];
//    char bintang_tamu[50];
//    int jumlah_tiket_vip;
//    float harga_tiket_vip;
//    int jumlah_tiket_regular;
//    float harga_tiket_regular;
//};

// struct Konser daftarKonser[MAX_KONSER];
extern int jumlahKonser;

void lihatSemuaKonser();
//void tambahKonser(struct Konser konser);
void tampilkanDaftarKonser();
//void hapusKonser(int id);
void lihatKetersediaanTiket();
int dapatkanIDMaksimum();

#endif
