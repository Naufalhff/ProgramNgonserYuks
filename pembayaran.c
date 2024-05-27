#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ARIQ.h"
#include "NAUFAL.h"
#include "YUDHIS.h"

Promo* head;

void pembayaranUser(int idNow) {
    // Deklarasi variabel
    char *fileName = "datauser.txt";
    char hasilPilihanMenuPembayaran;
    FILE *file;

    // Algoritma
    do {
        system("cls");
        hasilPilihanMenuPembayaran = menuPembayaran(); // Menampilkan menu dan mendapatkan pilihan pengguna
        switch(hasilPilihanMenuPembayaran) {
            case '0':
                break; // Keluar dari loop
            case '1':
                opsiBayar(fileName, idNow); // Memproses opsi bayar
                printf("\n");
                system("pause");
                break;
            case '2':
                statusPembayaran(fileName, idNow); // Memeriksa status pembayaran
                printf("\n");
                system("pause");
                break;
            case '3':
                cetakTiket(fileName, idNow); // Mencetak tiket
                printf("\n");
                system("pause");
                break;
            default:
                printf("\nMohon maaf, pilihan anda tidak valid.\n\n"); // Menampilkan pesan error
                system("pause");
        }
    } while (hasilPilihanMenuPembayaran != '0'); // Ulangi sampai pengguna memilih '0' untuk keluar
}

int menuPembayaran() {
    // Deklarasi variabel
    char pilihanMenuPembayaran;

    // Menampilkan opsi menu dan membaca pilihan pengguna
    printf("1. Bayar\n2. Cek status pembayaran\n3. Lihat Tiket\n0. Keluar\nOpsi yang anda inginkan: ");
    fflush(stdin);
    scanf("%c", &pilihanMenuPembayaran);

    return pilihanMenuPembayaran;
}

void opsiBayar(char *fileName, int idNow) {
    // Deklarasi variabel
    int userID,jumlahTiket, statusVerif;
    float jumlahBayar, userBayar, tempUserBayar;
    char username[50], namaKonser[100], jenisTiket[10], email[50];
    bool isValid = false;
    FILE *file, *fileTemp;
    float total; // Inisialisasi total bayar sebagai float

    // Membuka file asli dan file sementara untuk menulis data yang diperbarui
    file = fopen(fileName, "r");
    fileTemp = fopen("temp.txt", "w");

    if (file == NULL) {
        printf("\nGagal membaca file.\n");
        return;
    }

    // Membaca data dari file dan memproses pembayaran
    while (fscanf(file, "%d %s %s %s %d %s %f %f %d", &userID, username, email, namaKonser, &jumlahTiket, jenisTiket, &jumlahBayar, &userBayar, &statusVerif) != EOF) {
    	int kunci = 13;
    	dekripsi(username, kunci);
		dekripsi(email, kunci);
        
        if (userID == idNow) {
            // Kondisi jika belum melakukan pemesanan tiket
            if (jumlahBayar == 0) {
                printf("\nAnda belum melakukan pemesanan tiket.\n");
            } else if (statusVerif == -1) {
                printf("\n->Pembayaran untuk %d tiket konser '%s' berjenis '%s' belum diproses oleh Admin.\n", jumlahTiket, namaKonser, jenisTiket);
            } else if (statusVerif == 0) {
                printf("\n->Pembayaran untuk %d tiket konser '%s' berjenis '%s'.", jumlahTiket, namaKonser, jenisTiket);
                printf("\nPembayaran anda sudah lunas.\n");
            } else {
                total = jumlahBayar; // Inisialisasi total dengan jumlahBayar

                do {
                    printf("\n->Pembayaran untuk %d tiket konser '%s' berjenis '%s'.", jumlahTiket, namaKonser, jenisTiket);
                    printf("\nJumlah yang harus dibayar: %.2f\n", jumlahBayar - userBayar);
                    printf("Apakah anda ingin memasukkan kode promo? (Y/T): ");
                    char input;
                    scanf(" %c", &input);
                    if (input == 'Y' || input == 'y') {
                        char kode[20];
                        printf("Masukkan kode promo: ");
                        scanf("%s", kode);
                        total = aplikasiPromo(total, kode);
                        if (total == -1) {
                            printf("Promo tidak valid.\n");
                            continue;
                        }
                        printf("Total Bayar setelah promo: %.2f\n", total);
                    }

                    printf("Apakah yakin ingin memesan?(Y/N): ");
                    while (getchar() != '\n'); // Membersihkan buffer stdin
                    scanf("%c", &input);

                    if (input == 'Y' || input == 'y') {
                        // Melakukan pemesanan sesuai dengan langkah sebelumnya
                        // ...
                    } else {
                        printf("Kembali ke menu utama!\n");
                        return; // Keluar dari fungsi jika pengguna tidak ingin memesan
                    }

                    do {
                        printf("Input pembayaran: ");
                        scanf("%f", &tempUserBayar); // Membaca input pembayaran
                        if (tempUserBayar < 0) {
                            printf("\nInput pembayaran tidak valid.\n");
                        } else if ((tempUserBayar + userBayar) == total) {
                            printf("\nPembayaran diterima.\n");
                            isValid = true;
                        } else {
                            printf("\nInput anda tidak sesuai dengan jumlah yang harus dibayar.\n");
                        }
                    } while (!isValid); // Ulangi sampai input valid
                    userBayar += tempUserBayar; // Tambahkan pembayaran pengguna

                    if (tempUserBayar != 0) {
                        statusVerif = -1; // Set status menjadi belum diproses
                    }
                } while (!isValid);
            }
        }
	    enkripsi(username, kunci);
		enkripsi(email, kunci);
        fprintf(fileTemp, "%d %s %s %s %d %s %.2f %.2f %d\n", userID, username, email, namaKonser, jumlahTiket, jenisTiket, jumlahBayar, userBayar, statusVerif);
    }

    fclose(file);
    fclose(fileTemp);

    // Mengganti file asli dengan file sementara
    remove(fileName);
    rename("temp.txt", fileName);
}

void statusPembayaran(char *fileName, int idNow) {
    // Deklarasi variabel
    int userID, jumlahTiket, statusVerif;
    float jumlahBayar, userBayar;
    char username[50], namaKonser[100], jenisTiket[10], email[50];
    FILE *file;

    // Membuka file untuk membaca data
    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("\nGagal membaca file.\n");
        return;
    }

    // Membaca data dari file dan menampilkan status pembayaran
    while (fscanf(file, "%d %s %s %s %d %s %f %f %d", &userID, username, email, namaKonser, &jumlahTiket, jenisTiket, &jumlahBayar, &userBayar, &statusVerif) != EOF) {
    	int kunci = 13;
        dekripsi(username, kunci);
        dekripsi(email, kunci);
        if (userID == idNow) {
            if (jumlahBayar == 0) {
                printf("\nAnda belum melakukan pemesanan tiket.\n");
            } else {
                if (statusVerif == -1) {
                    printf("\n->Pembayaran untuk %d tiket konser '%s' berjenis '%s'.", jumlahTiket, namaKonser, jenisTiket);
                    printf("\nStatus: Pending\n");
                    printf("Pembayaran yang anda lakukan belum diproses oleh admin.\n");
                } else if (statusVerif == 0) {
                    printf("\n->Pembayaran untuk %d tiket konser '%s' berjenis '%s'.", jumlahTiket, namaKonser, jenisTiket);
                    printf("\nStatus: Lunas\n");
                    printf("Pembayaran yang anda lakukan sudah lunas, anda bisa melakukan cetak tiket.\n");
                } else {
                    printf("\n->Pembayaran untuk %d tiket konser '%s' berjenis '%s'.", jumlahTiket, namaKonser, jenisTiket);
                    printf("\nStatus: Belum Lunas\n");
                    printf("Jumlah yang sudah dibayar: %.2f\n", userBayar);
                    printf("Sisa yang harus dibayar: %.2f\n", jumlahBayar - userBayar);
                }
            }
        }
    }

    fclose(file);
}

void cetakTiket(char *fileName, int idNow) {
    // Deklarasi variabel
    int userID, jumlahTiket, statusVerif;
    float jumlahBayar, userBayar;
    char username[50], namaKonser[100], jenisTiket[10], email[50];
    FILE *file;

    // Membuka file untuk membaca data
    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("\nGagal membaca file.\n");
        return;
    }

    // Membaca data dari file dan mencetak tiket jika pembayaran sudah lunas
    while (fscanf(file, "%d %s %s %s %d %s %f %f %d", &userID, username, email, namaKonser, &jumlahTiket, jenisTiket, &jumlahBayar, &userBayar, &statusVerif) != EOF) {
    	int kunci = 13;
        dekripsi(username, kunci);
        dekripsi(email, kunci);
        if (userID == idNow) {
            if (jumlahBayar == 0) {
                printf("\nAnda belum melakukan pemesanan tiket.\n");
            } else if (statusVerif != 0) {
                printf("\nPembayaran anda belum lunas.\n");
            } else {
                printf("\n->Tiket konser '%s' berjenis '%s'.", namaKonser, jenisTiket);
                printf("\nNama Pemesan: %s", username);
                printf("\nEmail: %s", email);
                printf("\nJumlah Tiket: %d", jumlahTiket);
                printf("\nTotal Bayar: %.2f\n", jumlahBayar);
            }
        }
    }

    fclose(file);
}

void muatPromoDariFile() {
    FILE* file = fopen("promo.txt", "r");
    if (file == NULL) {
        return;
    }

    char kode[20];
    float diskon;
    while (fscanf(file, "%s %f", kode, &diskon) == 2) {
        tambahPromo(kode, diskon);
    }

    fclose(file);
}

void simpanPromoKeFile() {
    FILE* file = fopen("promo.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data promo.\n");
        return;
    }

    Promo* current = head;
    while (current != NULL) {
        if (!current->digunakan) {
            fprintf(file, "%s %.2f\n", current->kode, current->diskon);
        }
        current = current->next;
    }

    fclose(file);
}

float aplikasiPromo(float total, char kode[]) {
    Promo* current = head;
    while (current != NULL) {
        if (strcmp(current->kode, kode) == 0 && !current->digunakan) {
            current->digunakan = true;
            return total - (total * current->diskon / 100);
        }
        current = current->next;
    }
    return -1; // Promo tidak valid
}

void hapusPromo(char kode[]) {
    Promo* current = head;
    Promo* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->kode, kode) == 0) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            simpanPromoKeFile();
            return;
        }
        prev = current;
        current = current->next;
    }
}

void tambahPromo(char kode[], float diskon) {
    Promo* newPromo = (Promo*)malloc(sizeof(Promo));
    strcpy(newPromo->kode, kode);
    newPromo->diskon = diskon;
    newPromo->digunakan = false;
    newPromo->next = head;
    head = newPromo;
}


void cetakPromo() {
	
	FILE* file = fopen("promo.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data promo.\n");
        return;
    }

	printf("Daftar Promo:\n");

    char kode[50];
    double diskon;
    while (fscanf(file, "%s %lf", kode, &diskon) == 2) {
        printf("Kode Promo: %s | Diskon: %.2f\n", kode, diskon);
    }

    fclose(file);
}

void tambahPromoModul() {
    char kode[20];
    float diskon;
    printf("Masukkan kode promo: ");
    scanf("%s", kode);
    printf("Masukkan diskon: ");
    scanf("%f", &diskon);
    tambahPromo(kode, diskon);
    simpanPromoKeFile();
}

void hapusPromoModul() {
    char kode[20];
    printf("Masukkan kode promo yang ingin dihapus: ");
    scanf("%s", kode);
    hapusPromo(kode);
    simpanPromoKeFile();
}
