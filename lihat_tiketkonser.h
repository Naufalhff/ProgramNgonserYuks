#ifndef LIHAT_TIKETKONSER_H
#define LIHAT_TIKETKONSER_H

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

void lihatSemuaKonser();
void tambahKonser(struct Konser konser);
void tampilkanDaftarKonser();
void hapusKonser(int id);
void lihatKetersediaanTiket();
int dapatkanIDMaksimum();

#endif
