#ifndef RASYID_H
#define RASYID_H

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

void muatDataKonser();
void lihatDetailKonser(int id);
void tambahKonser(struct Konser konser);
void tampilkanDaftarKonser();
void hapusKonser(int id);
void tampilkanMenu();
void prosesLihatKonser();
void prosesTambahKonser();
void prosesEditKonser();
void prosesHapusKonser();

#endif
