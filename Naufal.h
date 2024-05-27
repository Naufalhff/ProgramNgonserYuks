#ifndef NAUFAL_H
#define NAUFAL_H

#include <time.h>
#include "ARIQ.h"


typedef struct Pemesanan {
    int idUser;
    char nama[100];
    int jumlah;
    char jenis[50];
    char email[50];
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


int generateUser();
float TotalBayar(char jenis[], int jumlah, struct Konser konser) ;
void searchkonser(struct Konser *konser, int konserID, Pemesanan *pemesanan);
void pesan(addressRoot root);
void menuUser();
void readKonserFromFile(Konser *konserList, int *konserCount);
void updateKonserFile(Konser *konserList, int konserCount);
void enkripsi(char *text, int shift);
void dekripsi(char *text, int shift);


void muatPromoDariFile();

#endif
