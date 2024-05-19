#ifndef NAUFAL_H
#define NAUFAL_H

#include <time.h>
#include "ARIQ.h"


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


int generateUser();
float TotalBayar(char jenis[], int jumlah, struct Konser konser) ;
void searchkonser(struct Konser *konser, int konserID, Pemesanan *pemesanan);
void pesan(addressRoot root);
void menuUser();

void enkripsi(char *text, int shift);
void dekripsi(char *text, int shift);
void enkripsiFloat(float *num, int shift);
void dekripsiFloat(float *num, int shift);
void enkripsiInt(int *num, int shift);
void dekripsiInt(int *num, int shift);
void muatPromoDariFile();

#endif
