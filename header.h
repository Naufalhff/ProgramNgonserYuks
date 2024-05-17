#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_KONSER 100

struct Konser {
    int id;
    char nama[50];
    struct tm tanggal;
    char tempat[50];
    char bintang_tamu[50];
    int jumlah_tiket_vip;
    float harga_tiket_vip;
    int jumlah_tiket_regular;
    float harga_tiket_regular;
};

extern struct Konser daftarKonser[MAX_KONSER];
extern int jumlahKonser;

void lihatDetailKonser(int id);
void tambahKonser(struct Konser konser);
void tampilkanDaftarKonser();
void hapusKonser(int id);
void tampilkanMenu();

#endif
