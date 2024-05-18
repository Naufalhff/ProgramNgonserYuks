#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

struct Konser daftarKonser[MAX_KONSER];
int jumlahKonser = 0;

void lihatSemuaKonser();
void tambahKonser(struct Konser konser);
void tampilkanDaftarKonser();
void hapusKonser(int id);
void tampilkanMenu();
int dapatkanIDMaksimum();

void lihatSemuaKonser() {
    FILE *file = fopen("Konser.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    struct Konser konserTemp;
    printf("\nDaftar Semua Konser:\n");
    while (fscanf(file, "%d|%[^|]|%d-%d-%d|%[^|]|%[^|]|%d|%f|%d|%f\n", 
                  &konserTemp.id, konserTemp.nama, 
                  &konserTemp.tanggal.tm_mday, &konserTemp.tanggal.tm_mon, &konserTemp.tanggal.tm_year, 
                  konserTemp.tempat, konserTemp.bintang_tamu, 
                  &konserTemp.jumlah_tiket_vip, &konserTemp.harga_tiket_vip, 
                  &konserTemp.jumlah_tiket_regular, &konserTemp.harga_tiket_regular) != EOF) {
        printf("\nID: %d\n", konserTemp.id);
        printf("Nama Konser: %s\n", konserTemp.nama);
        printf("Tanggal Konser: %02d-%02d-%04d\n", konserTemp.tanggal.tm_mday, konserTemp.tanggal.tm_mon, konserTemp.tanggal.tm_year);
        printf("Tempat Konser: %s\n", konserTemp.tempat);
        printf("Bintang Tamu: %s\n", konserTemp.bintang_tamu);
        printf("Jumlah Tiket VIP: %d\n", konserTemp.jumlah_tiket_vip);
        printf("Harga Tiket VIP: %.2f\n", konserTemp.harga_tiket_vip);
        printf("Jumlah Tiket Regular: %d\n", konserTemp.jumlah_tiket_regular);
        printf("Harga Tiket Regular: %.2f\n", konserTemp.harga_tiket_regular);
    }
    fclose(file);
}

int dapatkanIDMaksimum() {
    FILE *file = fopen("Konser.txt", "r");
    if (file == NULL) {
        return 0; // Jika file tidak ada, mulai dari ID 1
    }

    int id, maxID = 0;
    struct Konser konserTemp;
    while (fscanf(file, "%d|%[^|]|%d-%d-%d|%[^|]|%[^|]|%d|%f|%d|%f\n", 
                  &konserTemp.id, konserTemp.nama, 
                  &konserTemp.tanggal.tm_mday, &konserTemp.tanggal.tm_mon, &konserTemp.tanggal.tm_year, 
                  konserTemp.tempat, konserTemp.bintang_tamu, 
                  &konserTemp.jumlah_tiket_vip, &konserTemp.harga_tiket_vip, 
                  &konserTemp.jumlah_tiket_regular, &konserTemp.harga_tiket_regular) != EOF) {
        if (konserTemp.id > maxID) {
            maxID = konserTemp.id;
        }
    }
    fclose(file);
    return maxID;
}

void tambahKonser(struct Konser konser) {
    FILE *file = fopen("Konser.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
    konser.id = dapatkanIDMaksimum() + 1;
    fprintf(file, "%d|%s|%02d-%02d-%04d|%s|%s|%d|%.2f|%d|%.2f\n", 
            konser.id, konser.nama, 
            konser.tanggal.tm_mday, konser.tanggal.tm_mon + 1, konser.tanggal.tm_year + 1900, 
            konser.tempat, konser.bintang_tamu, 
            konser.jumlah_tiket_vip, konser.harga_tiket_vip, 
            konser.jumlah_tiket_regular, konser.harga_tiket_regular);
    fclose(file);

    daftarKonser[jumlahKonser++] = konser;
}

void tampilkanDaftarKonser() {
    FILE *file = fopen("Konser.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    jumlahKonser = 0;
    while (fscanf(file, "%d|%[^|]|%d-%d-%d|%[^|]|%[^|]|%d|%f|%d|%f\n", 
                  &daftarKonser[jumlahKonser].id, daftarKonser[jumlahKonser].nama, 
                  &daftarKonser[jumlahKonser].tanggal.tm_mday, &daftarKonser[jumlahKonser].tanggal.tm_mon, &daftarKonser[jumlahKonser].tanggal.tm_year, 
                  daftarKonser[jumlahKonser].tempat, daftarKonser[jumlahKonser].bintang_tamu, 
                  &daftarKonser[jumlahKonser].jumlah_tiket_vip, &daftarKonser[jumlahKonser].harga_tiket_vip, 
                  &daftarKonser[jumlahKonser].jumlah_tiket_regular, &daftarKonser[jumlahKonser].harga_tiket_regular) != EOF) {
        jumlahKonser++;
    }
    fclose(file);

    printf("\nDaftar Konser:\n");
    printf("ID  | Nama Konser\n");
    printf("----|-------------------\n");
    for (int i = 0; i < jumlahKonser; i++) {
        printf("%-4d| %s\n", daftarKonser[i].id, daftarKonser[i].nama);
    }
}

void hapusKonser(int id) {
    FILE *file = fopen("Konser.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    jumlahKonser = 0;
    while (fscanf(file, "%d|%[^|]|%d-%d-%d|%[^|]|%[^|]|%d|%f|%d|%f\n", 
                  &daftarKonser[jumlahKonser].id, daftarKonser[jumlahKonser].nama, 
                  &daftarKonser[jumlahKonser].tanggal.tm_mday, &daftarKonser[jumlahKonser].tanggal.tm_mon, &daftarKonser[jumlahKonser].tanggal.tm_year, 
                  daftarKonser[jumlahKonser].tempat, daftarKonser[jumlahKonser].bintang_tamu, 
                  &daftarKonser[jumlahKonser].jumlah_tiket_vip, &daftarKonser[jumlahKonser].harga_tiket_vip, 
                  &daftarKonser[jumlahKonser].jumlah_tiket_regular, &daftarKonser[jumlahKonser].harga_tiket_regular) != EOF) {
        jumlahKonser++;
    }
    fclose(file);

    int index = -1;
    for (int i = 0; i < jumlahKonser; i++) {
        if (daftarKonser[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Konser dengan ID %d tidak ditemukan.\n", id);
        return;
    }

    for (int i = index; i < jumlahKonser - 1; i++) {
        daftarKonser[i] = daftarKonser[i + 1];
    }
    jumlahKonser--;

    file = fopen("Konser.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
    for (int i = 0; i < jumlahKonser; i++) {
        fprintf(file, "%d|%s|%02d-%02d-%04d|%s|%s|%d|%.2f|%d|%.2f\n", 
                daftarKonser[i].id, daftarKonser[i].nama, 
                daftarKonser[i].tanggal.tm_mday, daftarKonser[i].tanggal.tm_mon + 1, daftarKonser[i].tanggal.tm_year + 1900, 
                daftarKonser[i].tempat, daftarKonser[i].bintang_tamu, 
                daftarKonser[i].jumlah_tiket_vip, daftarKonser[i].harga_tiket_vip, 
                daftarKonser[i].jumlah_tiket_regular, daftarKonser[i].harga_tiket_regular);
    }
    fclose(file);

    printf("Konser dengan ID %d telah dihapus.\n", id);
}

void tampilkanMenu() {
    printf("\nMenu:\n");
    printf("1. Lihat Semua Konser\n");
    printf("2. Tambah Konser\n");
    printf("3. Hapus Konser\n");
    printf("4. Keluar\n");
    printf("Pilih menu: ");
}

int main() {
    int pilihan;
    struct Konser konserBaru;
    int id;

    while (1) {
        tampilkanMenu();
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1:
                lihatSemuaKonser();
                break;
            case 2:
                printf("Masukkan Nama Konser: ");
                scanf(" %[^\n]s", konserBaru.nama);
                printf("Masukkan Tanggal (dd-mm-yyyy): ");
                scanf("%d-%d-%d", &konserBaru.tanggal.tm_mday, &konserBaru.tanggal.tm_mon, &konserBaru.tanggal.tm_year);
                konserBaru.tanggal.tm_mon--; // Karena tm_mon dimulai dari 0
                konserBaru.tanggal.tm_year -= 1900; // Karena tm_year dihitung sejak 1900
                printf("Masukkan Tempat Konser: ");
                scanf(" %[^\n]s", konserBaru.tempat);
                printf("Masukkan Bintang Tamu: ");
                scanf(" %[^\n]s", konserBaru.bintang_tamu);
                printf("Masukkan Jumlah Tiket VIP: ");
                scanf("%d", &konserBaru.jumlah_tiket_vip);
                printf("Masukkan Harga Tiket VIP: ");
                scanf("%f", &konserBaru.harga_tiket_vip);
                printf("Masukkan Jumlah Tiket Regular: ");
                scanf("%d", &konserBaru.jumlah_tiket_regular);
                printf("Masukkan Harga Tiket Regular: ");
                scanf("%f", &konserBaru.harga_tiket_regular);
                tambahKonser(konserBaru);
                break;
            case 3:
                printf("Masukkan ID Konser yang ingin dihapus: ");
                scanf("%d", &id);
                hapusKonser(id);
                break;
            case 4:
                exit(0);
            default:
                printf("Pilihan tidak valid!\n");
        }
    }

    return 0;
}

