#ifndef NAUFAL_H
#define NAUFAL_H

typedef struct Pemesanan {
    int idUser;
    char nama[100];
    int jumlah;
    char jenis[50];
    int notelp;
    char konserNama[50];
} Pemesanan;

typedef struct Konser {
    int id;
    char nama[50];
    struct tm tanggal;
    char tempat[50];
    char bintang_tamu[50];
    int jumlah_tiket_vip;
    float harga_tiket_vip;
    int jumlah_tiket_regular;
    float harga_tiket_regular;
} Konser;

typedef struct Node {
    int idUser;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

bool listEmpty(Queue* q);
void createQueue(Queue* q);
void insertAkhir(Queue* q, int idUser);
void insertMultipleAkhir(Queue* q, int idUserStart, int jumlah);
int generateUser();
float TotalBayar(char jenis[], int jumlah, Konser konser);
int loadKonserFromFile(Konser konserList[], int maxKonser);
void saveKonserToFile(Konser konserList[], int konserCount);
void searchKonser(Konser konserList[], int konserCount, int konserID, Konser* konser, Pemesanan* pemesanan);
void saveQueueToFile(Queue* q, const char* filename);
void loadQueueFromFile(Queue* q, const char* filename);
void pesan(Queue* vipQueue, Queue* regQueue);
void printQueue(Queue* q);

#endif