//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdbool.h>
//#include "YUDHIS.h"
//
//Promo* head = NULL;
//
//// Fungsi untuk menambah promo baru
//void tambahPromo(char kode[], float diskon) {
//    Promo* newPromo = (Promo*)malloc(sizeof(Promo));
//    strcpy(newPromo->kode, kode);
//    newPromo->diskon = diskon;
//    newPromo->digunakan = false;
//    newPromo->next = NULL;
//
//    // Cek apakah promo sudah ada sebelumnya
//    Promo* current = head;
//    while (current != NULL) {
//        if (strcmp(current->kode, kode) == 0) {
//            printf("Promo dengan kode %s sudah ada.\n", kode);
//            free(newPromo);
//            return;
//        }
//        current = current->next;
//    }
//
//    // Tambahkan promo ke linked list
//    if (head == NULL) {
//        head = newPromo;
//    } else {
//        current = head;
//        while (current->next != NULL) {
//            current = current->next;
//        }
//        current->next = newPromo;
//    }
//    printf("Promo dengan kode %s berhasil ditambahkan.\n\n", kode);
//    simpanPromoKeFile();
//}
//
//// Fungsi untuk menghapus promo berdasarkan kode promo
//void hapusPromo(char kode[]) {
//    Promo *temp = head, *prev;
//
//    // Cek apakah promo pertama yang akan dihapus
//    if (temp != NULL && strcmp(temp->kode, kode) == 0) {
//        head = temp->next;
//        free(temp);
//        printf("Promo dengan kode %s berhasil dihapus.\n", kode);
//        return;
//    }
//
//    // Cari promo yang akan dihapus
//    while (temp != NULL && strcmp(temp->kode, kode) != 0) {
//        prev = temp;
//        temp = temp->next;
//    }
//
//    // Jika promo tidak ditemukan
//    if (temp == NULL) {
//        printf("Promo dengan kode %s tidak ditemukan.\n", kode);
//        return;
//    }
//
//    // Hapus promo dari linked list
//    prev->next = temp->next;
//    free(temp);
//    printf("Promo dengan kode %s berhasil dihapus.\n", kode);
//}
//
//// Fungsi untuk menerapkan promo pada pembayaran
//float aplikasiPromo(float total, char kode[]) {
//    Promo* current = head;
//    while (current != NULL) {
//        if (strcmp(current->kode, kode) == 0 && !current->digunakan) {
//            total -= total * current->diskon;
//            current->digunakan = true;
//            printf("Promo dengan kode %s berhasil digunakan.\n", kode);
//            return total;
//        }
//        current = current->next;
//    }
//    printf("Promo dengan kode %s tidak valid atau sudah digunakan.\n", kode);
//    return total;
//}
//
//// Fungsi untuk mencetak semua promo yang tersedia
//void cetakPromo() {
//    printf("Daftar Promo:\n");
//    Promo* current = head;
//    while (current != NULL) {
//        printf("Kode Promo: %s | Diskon: %.2f | Digunakan: %s\n", current->kode, current->diskon, current->digunakan ? "Ya" : "Tidak");
//        current = current->next;
//    }
//}
//
//// Modul untuk menambah promo baru
//void tambahPromoModul() {
//    char kode[20];
//    float diskon;
//    printf("\nMasukkan kode promo: ");
//    scanf("%s", kode);
//    printf("Masukkan diskon (dalam desimal, contoh: 0.2 untuk 20%%): ");
//    scanf("%f", &diskon);
//    tambahPromo(kode, diskon);
//    simpanPromoKeFile();
//}
//
//// Modul untuk menghapus promo berdasarkan kode
//void hapusPromoModul() {
//    char kode[20];
//    printf("Masukkan kode promo yang akan dihapus: ");
//    scanf("%s", kode);
//    hapusPromo(kode);
//}
//
//// Fungsi untuk menyimpan semua promo ke dalam file promo.txt
//void simpanPromoKeFile() {
//    FILE* file = fopen("promo.txt", "w");
//    if (file == NULL) {
//        printf("Gagal membuka file promo.txt untuk ditulis.\n");
//        return;
//    }
//
//    Promo* current = head;
//    while (current != NULL) {
//        fprintf(file, "%s %.2f %d\n", current->kode, current->diskon, current->digunakan);
//        current = current->next;
//    }
//
//    fclose(file);
//    printf("Semua promo berhasil disimpan ke dalam file promo.txt.\n");
//}
//
//void muatPromoDariFile() {
//    FILE* file = fopen("promo.txt", "r");
//    if (file == NULL) {
//        printf("Gagal membuka file promo.txt untuk dibaca.\n");
//        return;
//    }
//
//    char kode[20];
//    float diskon;
//    int digunakan;
//    while (fscanf(file, "%s %f %d\n", kode, &diskon, &digunakan) != EOF) {
//        tambahPromo(kode, diskon);
//        head->digunakan = digunakan;
//    }
//
//    fclose(file);
//    printf("Promo berhasil dimuat dari file promo.txt.\n");
//}
//
//
//// Fungsi untuk memuat promo dari file promo.txt saat aplikasi dimulai
//
////int main() {
////    // Memuat promo dari file saat aplikasi dimulai
////    muatPromoDariFile();
////
////    int pilihan;
////    do {
////        printf("\nMenu:\n");
////        printf("1. Tambah Promo\n");
////        printf("2. Hapus Promo\n");
////        printf("3. Lihat Promo\n");
////        printf("4. Simpan Promo ke File\n");
////        printf("5. Keluar\n");
////        printf("Pilih: ");
////        scanf("%d", &pilihan);
////        switch (pilihan) {
////            case 1:
////                tambahPromoModul();
////                break;
////            case 2:
////                hapusPromoModul();
////                break;
////            case 3:
////                cetakPromo();
////                break;
////            case 4:
////                printf("Keluar dari program.\n");
////                break;
////            default:
////                printf("Pilihan tidak valid.\n");
////        }
////    } while (pilihan != 4);
////
////    return 0;
////}
