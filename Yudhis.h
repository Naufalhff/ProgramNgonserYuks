#ifndef YUDHIS_H
#define YUDHIS_H

#include <stdbool.h>

// Struktur data untuk promo
typedef struct Promo {
    char kode[20];
    float diskon;
    bool digunakan;
    struct Promo* next;
} Promo;

// Linked list untuk menyimpan promo


void tambahPromo(char kode[], float diskon);
void hapusPromo(char kode[]);
float aplikasiPromo(float total, char kode[]);
void cetakPromo();
void tambahPromoModul();
void hapusPromoModul();
void simpanPromoKeFile();
void muatPromoDariFile();

#endif // YUDHIS_H
