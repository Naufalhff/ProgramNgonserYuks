#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_KONSER 100 // Maksimal jumlah konser

// Definisi struktur untuk data konser
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

struct Konser daftarKonser[MAX_KONSER]; // Array untuk menyimpan data konser
int jumlahKonser = 0; // Jumlah konser yang telah ditambahkan

// Fungsi untuk menambahkan data konser ke dalam array dan file
void tambahKonser(struct Konser konser) {
    FILE *file = fopen("Konser.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file!");
        return;
    }
    konser.id = jumlahKonser + 1;
    fprintf(file, "%d|%s|%02d-%02d-%04d|%s|%s|%d|%.2f|%d|%.2f\n", konser.id, konser.nama, konser.tanggal.tm_mday, konser.tanggal.tm_mon + 1, konser.tanggal.tm_year + 1900, konser.tempat, konser.bintang_tamu, konser.jumlah_tiket_vip, konser.harga_tiket_vip, konser.jumlah_tiket_regular, konser.harga_tiket_regular);
    fclose(file);

    // Simpan data ke dalam array
    daftarKonser[jumlahKonser++] = konser;
}

// Fungsi untuk menampilkan daftar konser
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

// Fungsi untuk menghapus konser berdasarkan ID
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

            // Perbarui file Konser.txt
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

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    printf("\nMenu:\n");
    printf("1. Tambah Konser\n");
    printf("2. Edit Konser\n");
    printf("3. Hapus Konser\n");
    printf("4. Keluar\n");
    printf("Pilih menu: ");
}

int main() {
    int pilihan;
    struct Konser konser;

    do {
        tampilkanMenu();
        scanf("%d", &pilihan);
        fflush(stdin); // Membersihkan buffer stdin

        switch (pilihan) {
            case 1:
                printf("\nMasukkan Data Konser Baru:\n");
                printf("Nama Konser: ");
                scanf("%[^\n]", konser.nama);
                fflush(stdin);

                printf("Tanggal Konser (DD-MM-YYYY): ");
                scanf("%d-%d-%d", &konser.tanggal.tm_mday, &konser.tanggal.tm_mon, &konser.tanggal.tm_year);
                konser.tanggal.tm_year -= 1900; // Adjust year to match tm struct format
                konser.tanggal.tm_mon -= 1; // Adjust month to match tm struct format
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
            case 2:
                // Edit Konser
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
                        daftarKonser[i].tanggal.tm_year -= 1900; // Adjust year to match tm struct format
                        daftarKonser[i].tanggal.tm_mon -= 1; // Adjust month to match tm struct format
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

                        // Perbarui file Konser.txt
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
            case 3:
                // Hapus Konser
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
            case 4:
                printf("Keluar dari program. Sampai jumpa!\n");
                break;
            default:
                printf("Menu tidak valid.\n");
        }
    } while (pilihan != 4);

    return 0;
}
