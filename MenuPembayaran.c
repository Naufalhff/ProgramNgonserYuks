#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Naomi.h"
#include "Ariq.h
#include "Naufal.h
#include "Rasyid.h
#include "Yudhis.h
#include "Naufal.h

void pembayaranUser (int idNow)
{
    // Deklarasi variabel
    char *fileName = "datauser.txt";
    char hasilPilihanMenuPembayaran;
    FILE *file;

    // Algoritma
    do
    {
        system("cls");
        hasilPilihanMenuPembayaran = menuPembayaran(); // Menampilkan menu dan mendapatkan pilihan pengguna
        switch(hasilPilihanMenuPembayaran)
        {
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

int menuPembayaran ()
{
    // Deklarasi variabel
    char pilihanMenuPembayaran;
    
    // Menampilkan opsi menu dan membaca pilihan pengguna
    printf("1. Bayar\n2. Cek status pembayaran\n3. Lihat Tiket\n0. Keluar\nOpsi yang anda inginkan: ");
    fflush(stdin);
    scanf("%c", &pilihanMenuPembayaran);
    
    return pilihanMenuPembayaran;
}

void opsiBayar(char *fileName, int idNow)
{
    // Deklarasi variabel
    int userID, nomorTelepon, jumlahTiket, statusVerif;
    float jumlahBayar, userBayar;
    char username[50], namaKonser[100], jenisTiket[10];
    float tempUserBayar;
    bool isValid = false;
    FILE *file, *fileTemp;

    // Membuka file asli dan file sementara untuk menulis data yang diperbarui
    file = fopen(fileName, "r");
    fileTemp = fopen("temp.txt", "w");

    if (file == NULL)
    {
        printf("\nGagal membaca file.\n");
        return;
    }

    // Membaca data dari file dan memproses pembayaran
    while (fscanf(file, "%d %s %d %s %d %s %f %f %d", &userID, username, &nomorTelepon, namaKonser, &jumlahTiket, jenisTiket, &jumlahBayar, &userBayar, &statusVerif) != EOF)
    {
        if (userID == idNow)
        {
            // Kondisi jika belum melakukan pemesanan tiket
            if (jumlahBayar == 0)
            {
                printf("\nAnda belum melakukan pemesanan tiket.\n");
            }
            // Kondisi jika pembayaran belum diproses oleh admin
            else if (statusVerif == -1)
            {
                printf("\n->Pembayaran untuk %d tiket konser '%s' berjenis '%s' belum diproses oleh Admin.\n", jumlahTiket, namaKonser, jenisTiket);
            }
            // Kondisi jika pembayaran sudah lunas
            else if (statusVerif == 0)
            {
                printf("\n->Pembayaran untuk %d tiket konser '%s' berjenis '%s'.", jumlahTiket, namaKonser, jenisTiket);
                printf("\nPembayaran anda sudah lunas.\n");
            }
            // Proses pembayaran
            else
            {
                do
                {
                    printf("\n->Pembayaran untuk %d tiket konser '%s' berjenis '%s'.", jumlahTiket, namaKonser, jenisTiket);
                    printf("\nJumlah yang harus dibayar: %d\n", (int)jumlahBayar - (int)userBayar);
                    printf("Input pembayaran: ");
                    scanf("%f", &tempUserBayar); // Membaca input pembayaran
                    if (tempUserBayar < 0)
                    {
                        printf("\nInput pembayaran tidak valid.\n");
                    }
                    else if ((tempUserBayar + userBayar) <= jumlahBayar)
                    {
                        printf("\nPembayaran diterima.\n");
                        isValid = true;
                    }
                    else
                    {
                        printf("\nInput anda melebihi jumlah pembayaran.\n");
                    }
                } while (!isValid); // Ulangi sampai input valid
                userBayar += tempUserBayar; // Tambahkan pembayaran pengguna

                if (tempUserBayar != 0)
                {
                    statusVerif = -1; // Set status menjadi belum diproses
                }
            }
        }

        // Menulis data yang diperbarui ke file sementara
        if (!feof(file))
        {
            fprintf(fileTemp, "%d %s %d %s %d %s %.2f %.2f %d\n", userID, username, nomorTelepon, namaKonser, jumlahTiket, jenisTiket, jumlahBayar, userBayar, statusVerif);
        }
    }

    fclose(file);
    fclose(fileTemp);

    // Mengganti file asli dengan file sementara
    remove(fileName);
    rename("temp.txt", fileName);
}

void statusPembayaran(char *fileName, int idNow)
{
    // Deklarasi variabel
    int userID, nomorTelepon, jumlahTiket, statusVerif;
    float jumlahBayar, userBayar;
    char username[50], namaKonser[100], jenisTiket[10];
    FILE *file;
    
    // Membuka file untuk membaca data
    file = fopen(fileName, "r");
    
    if (file == NULL)
    {
        printf("\nGagal membaca file.\n");
        return;
    }
    
    // Membaca data dari file dan menampilkan status pembayaran
    while (fscanf(file, "%d %s %d %s %d %s %f %f %d", &userID, username, &nomorTelepon, namaKonser, &jumlahTiket, jenisTiket, &jumlahBayar, &userBayar, &statusVerif) != EOF)
    {
        if (userID == idNow)
        {
            if (jumlahBayar == 0)
            {
                printf("\nAnda belum melakukan pemesanan tiket.\n");
            }
            else
            {
                if (statusVerif == -1)
                {
                    printf("\n->Pembayaran untuk %d tiket konser '%s' berjenis '%s'.", jumlahTiket, namaKonser, jenisTiket);
                    printf("\nStatus: Pending\n");
                    printf("Pembayaran yang anda lakukan belum diproses oleh admin.\n");
                } 
                else if (statusVerif == 0)
                {
                    printf("\n->Pembayaran untuk %d tiket konser '%s' berjenis '%s'.", jumlahTiket, namaKonser, jenisTiket);
                    printf("\nStatus: Lunas\n");
                    printf("Pembayaran yang anda lakukan sudah lunas, anda bisa melakukan cetak tiket.\n");
                }
                else
                {
                    printf("\n->Pembayaran untuk %d tiket konser '%s' berjenis '%s'.", jumlahTiket, namaKonser, jenisTiket);
                    printf("\nStatus: Belum lunas\n");
                    printf("Pembayaran yang anda lakukan belum lunas, silahkan ada melakukan pembayaran kembali.\n");
                }
            }
        }
    }

    fclose(file);
}

void cetakTiket(char *fileName, int idNow)
{
    // Deklarasi variabel
    int userID, nomorTelepon, jumlahTiket, statusVerif;
    float jumlahBayar, userBayar;
    char username[50], namaKonser[100], jenisTiket[10];
    FILE *file;
    
    // Membuka file untuk membaca data
    file = fopen(fileName, "r");
    
    if (file == NULL)
    {
        printf("\nGagal membaca file\n\n");
        return;
    }
    
    // Membaca data dari file dan mencetak tiket
    while (fscanf(file, "%d %s %d %s %d %s %f %f %d", &userID, username, &nomorTelepon, namaKonser, &jumlahTiket, jenisTiket, &jumlahBayar, &userBayar, &statusVerif) != EOF)
    {
        if (userID == idNow)
        {
            if (jumlahBayar == 0)
            {
                system("cls");
                printf("Anda belum melakukan pemesanan tiket.\n\n");
                system("pause");
            }
            else
            {
                if (statusVerif == -1 || statusVerif == 1)
                {
                    system("cls");
                    printf("->Lihat tiket untuk %d tiket konser '%s' berjenis '%s'.", jumlahTiket, namaKonser, jenisTiket);
                    printf("\nAnda belum bisa menggunakan fitur ini.\n\n");
                    system("pause");
                } 
                else
                {
                    system("cls");
                    printf("Gunakan fitur screenshoot pada device anda untuk mencetak tiket ini dalam bentuk fisik.\n\n");
                    printf("=====================================\n");
                    printf("|            TIKET KONSER           |\n");
                    printf("=====================================\n");
                    printf("| ID           : %-19d|\n", userID);
                    printf("=====================================\n");
                    printf("| Atas Nama    : %-19s|\n", username);
                    printf("| Nama Konser  : %-19s|\n", namaKonser);
                    printf("| Jenis Tiket  : %-19s|\n", jenisTiket);
                    printf("| Jumlah Tiket : %-19d|\n", jumlahTiket);
                    printf("=====================================\n\n");
                    system("pause");
                }
            }
        }
    }

    fclose(file);
}
