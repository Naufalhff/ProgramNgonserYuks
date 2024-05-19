#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NAOMI.h""

// Fungsi untuk melakukan login admin
int loginAdmin() {
    char username[100];
    char password[100];

    // Meminta pengguna untuk memasukkan informasi login admin
    printf("Masukkan Username Admin: ");
    scanf("%s", username);

    printf("Masukkan Password Admin: ");
    scanf("%s", password);

    // Verifikasi username dan password admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpassword") == 0) {
        return 1; // Return 1 jika login admin berhasil
    } else {
        return 0; // Return 0 jika login admin gagal
    }
}

// Modifikasi fungsi login() untuk mendukung login admin
int login() {
    char username[100];
    char password[100];
    char encryptedPassword[100];

    // Meminta pengguna untuk memasukkan informasi login
    printf("Masukkan Username: ");
    scanf("%s", username);

    printf("Masukkan Password: ");
    scanf("%s", password);

    // Verifikasi apakah yang login adalah admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpassword") == 0) {
        printf("Anda telah berhasil login sebagai admin.\n");
        return 1; // Return 1 jika login admin berhasil
    }

    // Enkripsi password yang dimasukkan untuk verifikasi
    encryptDecrypt(password, encryptedPassword);

    // Buka file untuk membaca data registrasi
    FILE *file = fopen("registrasi.txt", "r");
    if (file == NULL) {
        printf("Error: Gagal membuka file.\n");
        return 0;
    }

    // Membaca data registrasi dari file dan membandingkannya dengan data yang dimasukkan
    char buffer[255];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char stored_username[100], stored_password[100];
        sscanf(buffer, "%s %s", stored_username, stored_password);
        if (strcmp(username, stored_username) == 0 && strcmp(encryptedPassword, stored_password) == 0) {
            fclose(file);
            return 1; // Return 1 jika login berhasil
        }
    }

    // Menutup file
    fclose(file);

    printf("Login gagal. Silakan coba lagi.\n");
    return 0; // Return 0 jika login gagal
}
