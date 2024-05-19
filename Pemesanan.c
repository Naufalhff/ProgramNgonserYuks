#include "ariq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "naufal.h"

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

void pesan(addressRoot root) {
    Pemesanan *pemesanan = malloc(sizeof(Pemesanan)); // Alokasi memori untuk pemesanan
    int userID = generateUser();
    struct Konser konser;
    int konserID;

    printf("Masukkan nama: ");
    scanf("%s", pemesanan->nama);
    printf("Masukkan no telp: ");
    scanf("%d", &pemesanan->notelp);

    do {
        printf("Masukkan ID Konser yang Dipilih: ");
        scanf("%d", &konserID);
        searchkonser(&konser, konserID, pemesanan);
    } while (konser.id != konserID);

    printf("Masukkan jumlah tiket: ");
    scanf("%d", &pemesanan->jumlah);
    printf("Masukkan jenis tiket (VIP/REG): ");
    scanf("%s", pemesanan->jenis);

    // Memastikan input jenis tiket adalah valid
    if (strcasecmp(pemesanan->jenis, "VIP") != 0 && strcasecmp(pemesanan->jenis, "REG") != 0) {
        printf("Jenis tiket tidak valid. Silakan masukkan 'VIP' atau 'REG'.\n");
        free(pemesanan);
        return;
    }

    // Masukkan pemesanan ke dalam antrian
    float total = TotalBayar(pemesanan->jenis, pemesanan->jumlah, konser);
    if (total == -1) {
        free(pemesanan); // Bebaskan memori yang dialokasikan sebelumnya sebelum kembali
        return;
    }

    printf("Total Bayar: %.2f\n", total);
    printf("Apakah yakin ingin memesan? (Y/N): ");
    char data;
    while (getchar() != '\n'); // Mengosongkan buffer input
    scanf(" %c", &data); // Tambahkan spasi sebelum %c untuk mengonsumsi spasi

    if (data == 'Y' || data == 'y') {
        // Memeriksa ketersediaan slot tiket sebelum melakukan penyimpanan
        if ((strcasecmp(pemesanan->jenis, "VIP") == 0 && konser.jumlah_tiket_vip < pemesanan->jumlah) ||
            (strcasecmp(pemesanan->jenis, "REG") == 0 && konser.jumlah_tiket_regular < pemesanan->jumlah)) {
            printf("Maaf, slot tiket untuk jenis %s habis atau tidak mencukupi. Pesanan tidak dapat diproses.\n", pemesanan->jenis);
        } else {
            // Perbarui jumlah tiket yang tersedia
            if (strcasecmp(pemesanan->jenis, "VIP") == 0) {
                konser.jumlah_tiket_vip -= pemesanan->jumlah;
            } else {
                konser.jumlah_tiket_regular -= pemesanan->jumlah;
            }

            enqueue(root->down, konserID, pemesanan->jenis, userID, pemesanan->nama, pemesanan->jumlah);
            FILE *fp = fopen("datauser.txt", "a");
            if (fp != NULL) {
                enkripsi(pemesanan->nama, 5);
                enkripsiInt(&pemesanan->notelp, 5);
                enkripsiFloat(&total, 5);
                fprintf(fp, "%d %s %d %s %d %s %.2f %.2f %d\n", userID, pemesanan->nama, pemesanan->notelp, pemesanan->konserNama, pemesanan->jumlah, pemesanan->jenis, total, 0, 1);
                printf("ID User: %d berhasil dipesan!\n", userID);
            } else {
                printf("Gagal menyimpan pemesanan.\n");
            }
            fclose(fp);
        }
    } else {
        printf("Kembali ke menu utama!\n");
    }

    free(pemesanan);
}



void enkripsi(char *text, int shift) {
    int i;
    for(i = 0; i < strlen(text); i++) {
        if(text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = ((text[i] - 'A' + shift) % 26) + 'A';
        } else if(text[i] >= 'a' && text[i] <= 'z') {
            text[i] = ((text[i] - 'a' + shift) % 26) + 'a';
        } else if(text[i] >= '0' && text[i] <= '9') {
            text[i] = ((text[i] - '0' + shift) % 10) + '0';
        }
    }
}
void dekripsi(char *text, int shift) {
    int i;
    for(i = 0; i < strlen(text); i++) {
        if(text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = ((text[i] - 'A' - shift + 26) % 26) + 'A';
        } else if(text[i] >= 'a' && text[i] <= 'z') {
            text[i] = ((text[i] - 'a' - shift + 26) % 26) + 'a';
        } else if(text[i] >= '0' && text[i] <= '9') {
            text[i] = ((text[i] - '0' - shift + 10) % 10) + '0';
        }
    }
}

void enkripsiFloat(float *num, int shift) {
    // Konversi float menjadi string
    char str[20];
    snprintf(str, sizeof(str), "%.2f", *num);

    // Enkripsi string
    enkripsi(str, shift);

    // Konversi kembali string ke float
    sscanf(str, "%f", num);
}

void dekripsiFloat(float *num, int shift) {
    // Konversi float menjadi string
    char str[20];
    snprintf(str, sizeof(str), "%.2f", *num);

    // Enkripsi string
    dekripsi(str, shift);

    // Konversi kembali string ke float
    sscanf(str, "%f", num);
}


void enkripsiInt(int *num, int shift) {
    *num = (*num + shift) % 10000; 
}

void dekripsiInt(int *num, int shift) {
    *num = (*num - shift + 10000) % 10000;
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
//                lihatKonser();
                break;
            case 2:{
			    char *fileKonser = "Konser.txt";
			    char *fileUser = "datauser.txt";
			    addressRoot root = buatRoot();
			    if (root != NULL) {
			        root->down = enqueueKonserFromFile(fileKonser, root->down);
			        enqueueFromFile(fileUser, root->down, root);
			    }
			    pesan(root);
			    break;
			}

            case 3:
                // Deklarasi
			    muatPromoDariFile();
			    int idNow = 1070;
			
			    // Algoritma
			    pembayaranUser(idNow);
                break;
            case 4:
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
