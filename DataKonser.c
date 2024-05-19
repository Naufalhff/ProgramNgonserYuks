#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Naomi.h"
#include "Ariq.h
#include "Naufal.h
#include "Rasyid.h
#include "Yudhis.h
#include "Naufal.h

struct Konser daftarKonser[MAX_KONSER];
int jumlahKonser = 0;

void lihatDetailKonser(int id) {
    FILE *file = fopen("Konser.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file!");
        return;
    }
    printf("\nDetail Konser %d:\n", id);
    while (fscanf(file, "%d|%[^|]|%d-%d-%d|%[^|]|%[^|]|%d|%f|%d|%f\n", &daftarKonser[jumlahKonser].id, daftarKonser[jumlahKonser].nama, &daftarKonser[jumlahKonser].tanggal.tm_mday, &daftarKonser[jumlahKonser].tanggal.tm_mon, &daftarKonser[jumlahKonser].tanggal.tm_year, daftarKonser[jumlahKonser].tempat, daftarKonser[jumlahKonser].bintang_tamu, &daftarKonser[jumlahKonser].jumlah_tiket_vip, &daftarKonser[jumlahKonser].harga_tiket_vip, &daftarKonser[jumlahKonser].jumlah_tiket_regular, &daftarKonser[jumlahKonser].harga_tiket_regular) != EOF) {
        if (daftarKonser[jumlahKonser].id == id) {
            printf("Nama Konser: %s\n", daftarKonser[jumlahKonser].nama);
            printf("Tanggal Konser: %02d-%02d-%04d\n", daftarKonser[jumlahKonser].tanggal.tm_mday, daftarKonser[jumlahKonser].tanggal.tm_mon + 1, daftarKonser[jumlahKonser].tanggal.tm_year + 1900);
            printf("Tempat Konser: %s\n", daftarKonser[jumlahKonser].tempat);
            printf("Bintang Tamu: %s\n", daftarKonser[jumlahKonser].bintang_tamu);
            printf("Jumlah Tiket VIP: %d\n", daftarKonser[jumlahKonser].jumlah_tiket_vip);
            printf("Harga Tiket VIP: %.2f\n", daftarKonser[jumlahKonser].harga_tiket_vip);
            printf("Jumlah Tiket Regular: %d\n", daftarKonser[jumlahKonser].jumlah_tiket_regular);
            printf("Harga Tiket Regular: %.2f\n", daftarKonser[jumlahKonser].harga_tiket_regular);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("Konser dengan ID %d tidak ditemukan.\n", id);
}

void tambahKonser(struct Konser konser) {
    FILE *file = fopen("Konser.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file!");
        return;
    }
    konser.id = jumlahKonser + 1;
    fprintf(file, "%d|%s|%02d-%02d-%04d|%s|%s|%d|%.2f|%d|%.2f\n", konser.id, konser.nama, konser.tanggal.tm_mday, konser.tanggal.tm_mon + 1, konser.tanggal.tm_year + 1900, konser.tempat, konser.bintang_tamu, konser.jumlah_tiket_vip, konser.harga_tiket_vip, konser.jumlah_tiket_regular, konser.harga_tiket_regular);
    fclose(file);

    daftarKonser[jumlahKonser++] = konser;
}

void tampilkanDaftarKonser() {
    printf("\nDaftar Konser:\n");
    printf("ID  | Nama Konser\n");
    printf("----|-------------------\n");
    int i = 0;
    while (i < jumlahKonser) {
        printf("%-4d| %s\n", daftarKonser[i].id, daftarKonser[i].nama);
        i++;
    }
}

void hapusKonser(int id) {
    int i = 0;
    while (i < jumlahKonser) {
        if (daftarKonser[i].id == id) {
            int j = i;
            while (j < jumlahKonser - 1) {
                daftarKonser[j] = daftarKonser[j + 1];
                j++;
            }
            jumlahKonser--;
            printf("Konser dengan ID %d telah dihapus.\n", id);

            FILE *file = fopen("Konser.txt", "w");
            if (file == NULL) {
                printf("Gagal membuka file!");
                return;
            }
            int k = 0;
            while (k < jumlahKonser) {
                fprintf(file, "%d|%s|%02d-%02d-%04d|%s|%s|%d|%.2f|%d|%.2f\n", daftarKonser[k].id, daftarKonser[k].nama, daftarKonser[k].tanggal.tm_mday, daftarKonser[k].tanggal.tm_mon + 1, daftarKonser[k].tanggal.tm_year + 1900, daftarKonser[k].tempat, daftarKonser[k].bintang_tamu, daftarKonser[k].jumlah_tiket_vip, daftarKonser[k].harga_tiket_vip, daftarKonser[k].jumlah_tiket_regular, daftarKonser[k].harga_tiket_regular);
                k++;
            }
            fclose(file);
            return;
        }
        i++;
    }
    printf("Konser dengan ID %d tidak ditemukan.\n", id);
}

void tampilkanMenu() {
    printf("\nMenu:\n");
    printf("1. Lihat Konser\n");
    printf("2. Tambah Konser\n");
    printf("3. Edit Konser\n");
    printf("4. Hapus Konser\n");
    printf("5. Keluar\n");
    printf("Pilih menu: ");
}