#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "NAUFAL.h"
#include "ARIQ.h"
#include "NAOMI.h"
#include "ROY.h"

int generateUser() {
    srand(time(NULL));
    return rand() % 9000 + 1000;
}

float TotalBayar(char jenis[], int jumlah, struct Konser konser) {
    float hargaTiket = 0;
    if (strcmp(jenis, "VIP") == 0) {
        hargaTiket = konser.harga_tiket_vip;
    } else if (strcmp(jenis, "REG") == 0) {
        hargaTiket = konser.harga_tiket_regular;
    } else {
        printf("Jenis tiket tidak valid.\n");
        return -1;
    }
    return jumlah * hargaTiket;
}

void searchkonser(struct Konser *konser, int konserID, Pemesanan *pemesanan) {
    FILE *file = fopen("konser.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file konser.txt!\n");
        return;
    }
    int konserDitemukan = 0;
    while (fscanf(file, "%d|%[^|]|%d-%d-%d|%[^|]|%[^|]|%d|%f|%d|%f\n", &konser->id, konser->nama, &konser->tanggal.tm_mday, &konser->tanggal.tm_mon, &konser->tanggal.tm_year, konser->tempat, konser->bintang_tamu, &konser->jumlah_tiket_vip, &konser->harga_tiket_vip, &konser->jumlah_tiket_regular, &konser->harga_tiket_regular) != EOF) {
        if (konser->id == konserID) {
            konserDitemukan = 1;
            strcpy(pemesanan->konserNama, konser->nama);
            break;
        }
    }
    fclose(file);
    if (!konserDitemukan) {
        printf("Konser dengan ID tersebut tidak ditemukan.\n");
        return;
    }
}

void enkripsi(char *data, int kunci) {
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= kunci;
    }
}

void dekripsi(char *data, int kunci) {
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= kunci;
    }
}

void readKonserFromFile(Konser *konserList, int *konserCount) {
    FILE *file = fopen("konser.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file konser.txt.\n");
        return;
    }
    
    *konserCount = 0;
    while (fscanf(file, "%d|%49[^|]|%d-%d-%d|%49[^|]|%49[^|]|%d|%f|%d|%f\n",
                  &konserList[*konserCount].id,
                  konserList[*konserCount].nama,
                  &konserList[*konserCount].tanggal.tm_mday,
                  &konserList[*konserCount].tanggal.tm_mon,
                  &konserList[*konserCount].tanggal.tm_year,
                  konserList[*konserCount].tempat,
                  konserList[*konserCount].bintang_tamu,
                  &konserList[*konserCount].jumlah_tiket_vip,
                  &konserList[*konserCount].harga_tiket_vip,
                  &konserList[*konserCount].jumlah_tiket_regular,
                  &konserList[*konserCount].harga_tiket_regular) != EOF) {
        (*konserCount)++;
    }
    
    fclose(file);
}

void updateKonserFile(Konser *konserList, int konserCount) {
    FILE *file = fopen("konser.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file konser.txt untuk penulisan.\n");
        return;
    }
    
    for (int i = 0; i < konserCount; i++) {
        fprintf(file, "%d|%s|%d-%d-%d|%s|%s|%d|%.2f|%d|%.2f\n",
                konserList[i].id,
                konserList[i].nama,
                konserList[i].tanggal.tm_mday,
                konserList[i].tanggal.tm_mon,
                konserList[i].tanggal.tm_year,
                konserList[i].tempat,
                konserList[i].bintang_tamu,
                konserList[i].jumlah_tiket_vip,
                konserList[i].harga_tiket_vip,
                konserList[i].jumlah_tiket_regular,
                konserList[i].harga_tiket_regular);
    }
    
    fclose(file);
}

void pesan(addressRoot root) {;
    Pemesanan *pemesanan = malloc(sizeof(Pemesanan));
    Konser konserList[100];
    int konserCount = 0; 
    struct Konser konser;
    int konserID;
    int userID = generateUser();
    
    system ("cls");
	printf("                                                                              \n");
    printf("                                    _  _   ___   ___   _  _  ___  ___  ___          `__   __ _   _  _  __ ___  ___   _ \n");
    printf("                                   | \\| | / __| / _ \\ | \\| |/ __|| __|| _ \\      \\ \\ / /| | | || |/ // __|/ __| | |\n");
    printf("                                   | .  || (_ || (_) || .  |\\__ \\| _| |   /       \\   / | |_| ||   < \\__ \\\\__ \\ |_|\n");
    printf("                                    |_|\\_| \\___| \\___/ |_|\\_||___/|___||_|_\\        |_|   \\___/ |_|\\_\\|___/|___/ (_)\n");    
    printf("Masukkan nama: ");
    scanf("%s", pemesanan->nama);
    printf("Masukkan email: ");
    scanf("%s", pemesanan->email);
    
    readKonserFromFile(konserList, &konserCount);
    
    do {
        printf("Masukkan ID Konser yang Dipilih: ");
        scanf("%d", &konserID);
        searchkonser(&konser, konserID, pemesanan);
    } while (konser.id != konserID);

    printf("Masukkan jumlah tiket: ");
    scanf("%d", &pemesanan->jumlah);
    do {
        printf("Masukkan jenis tiket (VIP/REG): ");
        scanf("%s", pemesanan->jenis);
        if (strcasecmp(pemesanan->jenis, "VIP") != 0 && strcasecmp(pemesanan->jenis, "REG") != 0) {
            printf("Jenis tiket tidak valid. Silakan masukkan 'VIP' atau 'REG'.\n");
        }
    } while (strcasecmp(pemesanan->jenis, "VIP") != 0 && strcasecmp(pemesanan->jenis, "REG") != 0);

    if ((strcasecmp(pemesanan->jenis, "VIP") == 0 && konser.jumlah_tiket_vip < pemesanan->jumlah) ||
        (strcasecmp(pemesanan->jenis, "REG") == 0 && konser.jumlah_tiket_regular < pemesanan->jumlah)) {
        printf("Maaf, slot tiket untuk jenis %s habis atau tidak mencukupi.\n", pemesanan->jenis);
        printf("Sisa tiket REG %d, sisa tiket VIP %d. Pesanan tidak dapat diproses.\n", konser.jumlah_tiket_regular, konser.jumlah_tiket_vip);
        free(pemesanan);
        return;
    }

    if (strcasecmp(pemesanan->jenis, "VIP") == 0) {
        konser.jumlah_tiket_vip -= pemesanan->jumlah;
    } else {
        konser.jumlah_tiket_regular -= pemesanan->jumlah;
    }
    
    for (int i = 0; i < konserCount; i++) {
        if (konserList[i].id == konserID) {
            konserList[i] = konser;
            break;
        }
    }


    float total = TotalBayar(pemesanan->jenis, pemesanan->jumlah, konser);
    if (total == -1) {
        free(pemesanan);
        return;
    }

    printf("Total Bayar: %.2f\n", total);
    printf("Apakah yakin ingin memesan? (Y/N): ");
    char data;
    while (getchar() != '\n');
    scanf(" %c", &data);
    if (data != 'Y' && data != 'y') {
        printf("Pemesanan dibatalkan.\n");
        free(pemesanan);
        return;
    }
   
    int kunci = 13; 
    enkripsi(pemesanan->nama, kunci);
	enkripsi(pemesanan->email, kunci);

    push(root->down, konserID, pemesanan->jenis, userID, pemesanan->nama, pemesanan->jumlah);

    FILE *fp = fopen("datauser.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%d %s %s %s %d %s %.2f %.2f %d\n", userID, pemesanan->nama, pemesanan->email, pemesanan->konserNama, pemesanan->jumlah, pemesanan->jenis, total, 0, 1);
        printf("Tiket berhasil dipesan!\n");
    } else {
        printf("Gagal menyimpan pemesanan.\n");
    }
    fclose(fp);

	dekripsi(pemesanan->nama, kunci);
    dekripsi(pemesanan->email, kunci);

    updateKonserFile(konserList, konserCount);


    free(pemesanan);
}

void menuUser() {
    int choice;

    do {
        printf("\n===== Menu User =====\n");
        printf("1. Lihat Konser\n");
        printf("2. Pemesanan\n");
        printf("3. Pembayaran\n");
        printf("4. Lihat Promo\n");
        printf("5. Keluar\n");
        printf("Pilih menu (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                lihatKetersediaanTiket();
                break;
            case 2: {
                char *fileKonser = "Konser.txt";
                char *fileUser = "datauser.txt";
                addressRoot root = buatRoot();
                if (root != NULL) {
                    root->down = pushKonserFromFile(fileKonser, root->down);
                    pushFromFile(fileUser, root->down, root);
                }
                pesan(root);
                break;
            }
            case 3: {
                // Deklarasi
                muatPromoDariFile();
                int idNow = 8666;

                // Algoritma
                pembayaranUser(idNow);
                break;
            }
            case 4:
                muatPromoDariFile();
                cetakPromo();
                break;
            case 5: 	
                printf("Terima kasih! Keluar dari menu.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 5);
}