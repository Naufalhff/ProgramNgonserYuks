#include "NAOMI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lihatKetersediaanTiket() {
    FILE *file = fopen("Konser.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    struct Konser konserTemp;
    printf("\nKetersediaan Tiket Konser:\n");
    while (fscanf(file, "%d|%[^|]|%d-%d-%d|%[^|]|%[^|]|%d|%f|%d|%f\n", 
                  &konserTemp.id, konserTemp.nama, 
                  &konserTemp.tanggal.tm_mday, &konserTemp.tanggal.tm_mon, &konserTemp.tanggal.tm_year, 
                  konserTemp.tempat, konserTemp.bintang_tamu, 
                  &konserTemp.jumlah_tiket_vip, &konserTemp.harga_tiket_vip, 
                  &konserTemp.jumlah_tiket_regular, &konserTemp.harga_tiket_regular) != EOF) {
        printf("\nNama Konser: %s\n", konserTemp.nama);
        printf("Tanggal: %02d-%02d-%04d\n", konserTemp.tanggal.tm_mday, konserTemp.tanggal.tm_mon, konserTemp.tanggal.tm_year);
        printf("Tempat: %s\n", konserTemp.tempat);
        printf("Jumlah Tiket VIP Tersedia: %d\n", konserTemp.jumlah_tiket_vip);
        printf("Jumlah Tiket Regular Tersedia: %d\n", konserTemp.jumlah_tiket_regular);
    }
    fclose(file);
}

