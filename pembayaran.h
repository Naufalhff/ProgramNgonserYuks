#ifndef pembayaran_h
#define pembayaran_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Promo {
    char kode[20];
    float diskon;
    bool digunakan;
    struct Promo* next;
} Promo;

Promo* head = NULL;

void muatPromoDariFile();
void simpanPromoKeFile();
float aplikasiPromo(float total, char kode[]);
void hapusPromo(char kode[]);
void tambahPromo(char kode[], float diskon);
void cetakPromo();
void tambahPromoModul();
void hapusPromoModul();
void pembayaranUser(int idNow);
int menuPembayaran();
void opsiBayar(char *fileName, int idNow);
void statusPembayaran(char *fileName, int idNow);
void cetakTiket(char *fileName, int idNow);

#endif