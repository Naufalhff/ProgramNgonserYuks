#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rasyid.h"
#include "ariq.h"

struct Konser daftarKonser[MAX_KONSER];
int jumlahKonser;

void muatDataKonser() {
    FILE *file = fopen("Konser.txt", "r");
    if (file == NULL) {
        return;
    }
    jumlahKonser = 0;
    while (fscanf(file, "%d|%[^|]|%d-%d-%d|%[^|]|%[^|]|%d|%f|%d|%f\n",
                  &daftarKonser[jumlahKonser].id, daftarKonser[jumlahKonser].nama,
                  &daftarKonser[jumlahKonser].tanggal.tm_mday, &daftarKonser[jumlahKonser].tanggal.tm_mon,
                  &daftarKonser[jumlahKonser].tanggal.tm_year, daftarKonser[jumlahKonser].tempat,
                  daftarKonser[jumlahKonser].bintang_tamu, &daftarKonser[jumlahKonser].jumlah_tiket_vip,
                  &daftarKonser[jumlahKonser].harga_tiket_vip, &daftarKonser[jumlahKonser].jumlah_tiket_regular,
                  &daftarKonser[jumlahKonser].harga_tiket_regular) != EOF) {
        daftarKonser[jumlahKonser].tanggal.tm_year -= 1900;
        daftarKonser[jumlahKonser].tanggal.tm_mon -= 1;
        jumlahKonser++;
    }
    fclose(file);
}

void lihatDetailKonser(int id) {
    printf("\nDetail Konser %d:\n", id);
    int i = 0;
    while (i < jumlahKonser) {
        if (daftarKonser[i].id == id) {
            printf("Nama Konser: %s\n", daftarKonser[i].nama);
            printf("Tanggal Konser: %02d-%02d-%04d\n", daftarKonser[i].tanggal.tm_mday,
                   daftarKonser[i].tanggal.tm_mon + 1, daftarKonser[i].tanggal.tm_year + 1900);
            printf("Tempat Konser: %s\n", daftarKonser[i].tempat);
            printf("Bintang Tamu: %s\n", daftarKonser[i].bintang_tamu);
            printf("Jumlah Tiket VIP: %d\n", daftarKonser[i].jumlah_tiket_vip);
            printf("Harga Tiket VIP: %.2f\n", daftarKonser[i].harga_tiket_vip);
            printf("Jumlah Tiket Regular: %d\n", daftarKonser[i].jumlah_tiket_regular);
            printf("Harga Tiket Regular: %.2f\n", daftarKonser[i].harga_tiket_regular);
            return;
        }
        i++;
    }
    printf("Konser dengan ID %d tidak ditemukan.\n", id);
}

void tambahKonser(struct Konser konser, addressKonser first) {
	addressKonser nodeBaru;
	
	char p2[50];
    int p1, p3, p4;
    FILE *file = fopen("Konser.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file!");
        return;
    }
    int lastID = 0;
    if (jumlahKonser > 0) {
        lastID = daftarKonser[jumlahKonser - 1].id;
    }
    konser.id = lastID + 1;
    fprintf(file, "%d|%s|%02d-%02d-%04d|%s|%s|%d|%.2f|%d|%.2f\n",
            konser.id, konser.nama, konser.tanggal.tm_mday, konser.tanggal.tm_mon + 1,
            konser.tanggal.tm_year + 1900, konser.tempat, konser.bintang_tamu,
            konser.jumlah_tiket_vip, konser.harga_tiket_vip, konser.jumlah_tiket_regular, konser.harga_tiket_regular);
    fclose(file);
    
    p1 = konser.id;
    strcpy(p2, konser.nama);
    p3 = konser.jumlah_tiket_vip;
    p4 = konser.jumlah_tiket_regular;
    
    nodeBaru = buatNodeKonser(p1, p2, p3, p4);
    first = pushKonser(first, nodeBaru);
    
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

void hapusKonser(int id, bool *isDelete) { 
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
                fprintf(file, "%d|%s|%02d-%02d-%04d|%s|%s|%d|%.2f|%d|%.2f\n",
                        daftarKonser[k].id, daftarKonser[k].nama, daftarKonser[k].tanggal.tm_mday,
                        daftarKonser[k].tanggal.tm_mon + 1, daftarKonser[k].tanggal.tm_year + 1900,
                        daftarKonser[k].tempat, daftarKonser[k].bintang_tamu, daftarKonser[k].jumlah_tiket_vip,
                        daftarKonser[k].harga_tiket_vip, daftarKonser[k].jumlah_tiket_regular, daftarKonser[k].harga_tiket_regular);
                k++;
            }
            fclose(file);
            *isDelete = true;
            return;
        }
        i++;
    }
    printf("Konser dengan ID %d tidak ditemukan.\n", id);
    *isDelete = false;
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

void prosesLihatKonser() {
    if (jumlahKonser == 0) {
        printf("Tidak ada konser yang tersedia untuk dilihat.\n");
        return;
    }
    tampilkanDaftarKonser();
    printf("Pilih ID konser untuk melihat detail: ");
    int idLihat;
    scanf("%d", &idLihat);
    fflush(stdin);
    lihatDetailKonser(idLihat);
}

void prosesTambahKonser(addressKonser first) {
    struct Konser konser;
    
    printf("\nMasukkan Data Konser Baru:\n");
    printf("Nama Konser: ");
    scanf("%[^\n]", konser.nama);
    fflush(stdin);

    printf("Tanggal Konser (DD-MM-YYYY): ");
    scanf("%d-%d-%d", &konser.tanggal.tm_mday, &konser.tanggal.tm_mon, &konser.tanggal.tm_year);
    konser.tanggal.tm_year -= 1900;
    konser.tanggal.tm_mon -= 1;
    fflush(stdin);

    printf("Tempat Konser: ");
    scanf("%[^\n]", konser.tempat);
    fflush(stdin);

    printf("Bintang Tamu: ");
    scanf("%[^\n]", konser.bintang_tamu);
    fflush(stdin);

    printf("Jumlah Tiket VIP: ");
    scanf("%d", &konser.jumlah_tiket_vip);
    fflush(stdin);

    printf("Harga Tiket VIP: ");
    scanf("%f", &konser.harga_tiket_vip);
    fflush(stdin);

    printf("Jumlah Tiket Regular: ");
    scanf("%d", &konser.jumlah_tiket_regular);
    fflush(stdin);

    printf("Harga Tiket Regular: ");
    scanf("%f", &konser.harga_tiket_regular);
    fflush(stdin);

    tambahKonser(konser, first);
    
    printf("Data konser telah ditambahkan.\n");
}

void prosesEditKonser() {
    if (jumlahKonser == 0) {
        printf("Tidak ada konser yang tersedia untuk diedit.\n");
        return;
    }
    tampilkanDaftarKonser();
    printf("Pilih ID konser yang akan diedit: ");
    int idEdit;
    scanf("%d", &idEdit);
    fflush(stdin);
    int i = 0;
    while (i < jumlahKonser) {
        if (daftarKonser[i].id == idEdit) {
            printf("\nEdit Konser dengan ID %d:\n", idEdit);
            printf("Nama Konser: ");
            scanf("%[^\n]", daftarKonser[i].nama);
            fflush(stdin);

            printf("Tanggal Konser (DD-MM-YYYY): ");
            scanf("%d-%d-%d", &daftarKonser[i].tanggal.tm_mday, &daftarKonser[i].tanggal.tm_mon, &daftarKonser[i].tanggal.tm_year);
            daftarKonser[i].tanggal.tm_year -= 1900;
            daftarKonser[i].tanggal.tm_mon -= 1;
            fflush(stdin);

            printf("Tempat Konser: ");
            scanf("%[^\n]", daftarKonser[i].tempat);
            fflush(stdin);

            printf("Bintang Tamu: ");
            scanf("%[^\n]", daftarKonser[i].bintang_tamu);
            fflush(stdin);

            printf("Jumlah Tiket VIP: ");
            scanf("%d", &daftarKonser[i].jumlah_tiket_vip);
            fflush(stdin);

            printf("Harga Tiket VIP: ");
            scanf("%f", &daftarKonser[i].harga_tiket_vip);
            fflush(stdin);

            printf("Jumlah Tiket Regular: ");
            scanf("%d", &daftarKonser[i].jumlah_tiket_regular);
            fflush(stdin);

            printf("Harga Tiket Regular: ");
            scanf("%f", &daftarKonser[i].harga_tiket_regular);
            fflush(stdin);

            printf("Konser telah berhasil diubah.\n");

            FILE *file = fopen("Konser.txt", "w");
            if (file == NULL) {
                printf("Gagal membuka file!");
                return;
            }
            int j = 0;
            while (j < jumlahKonser) {
                fprintf(file, "%d|%s|%02d-%02d-%04d|%s|%s|%d|%.2f|%d|%.2f\n",
                        daftarKonser[j].id, daftarKonser[j].nama, daftarKonser[j].tanggal.tm_mday,
                        daftarKonser[j].tanggal.tm_mon + 1, daftarKonser[j].tanggal.tm_year + 1900,
                        daftarKonser[j].tempat, daftarKonser[j].bintang_tamu, daftarKonser[j].jumlah_tiket_vip,
                        daftarKonser[j].harga_tiket_vip, daftarKonser[j].jumlah_tiket_regular, daftarKonser[j].harga_tiket_regular);
                j++;
            }
            fclose(file);
            return;
        }
        i++;
    }
    printf("Konser dengan ID %d tidak ditemukan.\n", idEdit);
}

void prosesHapusKonser(int *idHapus, bool *isDelete){
    if (jumlahKonser == 0) {
        printf("Tidak ada konser yang tersedia untuk dihapus.\n");
        return;
    }
    tampilkanDaftarKonser();
    printf("Pilih ID konser yang akan dihapus: ");
    scanf("%d", idHapus);
    fflush(stdin);
    hapusKonser(*idHapus, isDelete);
}
