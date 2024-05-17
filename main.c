#include <stdio.h>
#include "header.h"

int main() {
    int pilihan;
    struct Konser konser;

    do {
        tampilkanMenu();
        scanf("%d", &pilihan);
        fflush(stdin);

        switch (pilihan) {
            case 1:
                if (jumlahKonser == 0) {
                    printf("Tidak ada konser yang tersedia untuk dilihat.\n");
                    break;
                }
                tampilkanDaftarKonser();
                printf("Pilih ID konser untuk melihat detail: ");
                int idLihat;
                scanf("%d", &idLihat);
                fflush(stdin);
                lihatDetailKonser(idLihat);
                break;
            case 2:
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

                tambahKonser(konser);
                printf("Data konser telah ditambahkan.\n");
                break;
            case 3:
                if (jumlahKonser == 0) {
                    printf("Tidak ada konser yang tersedia untuk diedit.\n");
                    break;
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
                            return 1;
                        }
                        int j = 0;
                        while (j < jumlahKonser) {
                            fprintf(file, "%d|%s|%02d-%02d-%04d|%s|%s|%d|%.2f|%d|%.2f\n", daftarKonser[j].id, daftarKonser[j].nama, daftarKonser[j].tanggal.tm_mday, daftarKonser[j].tanggal.tm_mon + 1, daftarKonser[j].tanggal.tm_year + 1900, daftarKonser[j].tempat, daftarKonser[j].bintang_tamu, daftarKonser[j].jumlah_tiket_vip, daftarKonser[j].harga_tiket_vip, daftarKonser[j].jumlah_tiket_regular, daftarKonser[j].harga_tiket_regular);
                            j++;
                        }
                        fclose(file);
                        break;
                    }
                    i++;
                }
                if (i == jumlahKonser) {
                    printf("Konser dengan ID %d tidak ditemukan.\n", idEdit);
                }
                break;
            case 4:
                if (jumlahKonser == 0) {
                    printf("Tidak ada konser yang tersedia untuk dihapus.\n");
                    break;
                }
                tampilkanDaftarKonser();
                printf("Pilih ID konser yang akan dihapus: ");
                int idHapus;
                scanf("%d", &idHapus);
                fflush(stdin);
                hapusKonser(idHapus);
                break;
            case 5:
                printf("Keluar dari program. Sampai jumpa!\n");
                break;
            default:
                printf("Menu tidak valid.\n");
        }
    } while (pilihan != 5);

    return 0;
}
