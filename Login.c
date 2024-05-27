#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NAOMI.h"

// Fungsi untuk login admin
int loginAdmin() {
    char username[100];
    char password[100];
	
		printf("                                                                              \n");
    printf("                                    _  _   ___   ___   _  _  ___  ___  ___          `__   __ _   _  _  __ ___  ___   _ \n");
    printf("                                   | \\| | / __| / _ \\ | \\| |/ __|| __|| _ \\      \\ \\ / /| | | || |/ // __|/ __| | |\n");
    printf("                                   | .  || (_ || (_) || .  |\\__ \\| _| |   /       \\   / | |_| ||   < \\__ \\\\__ \\ |_|\n");
    printf("                                    |_|\\_| \\___| \\___/ |_|\\_||___/|___||_|_\\        |_|   \\___/ |_|\\_\\|___/|___/ (_)\n");
    // Meminta pengguna untuk memasukkan informasi login admin
    printf("Masukkan Username Admin: ");
    scanf("%s", username);

    printf("Masukkan Password Admin: ");
    scanf("%s", password);

    // Verifikasi username dan password admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpassword") == 0) {
        printf("Anda telah berhasil login sebagai admin.\n");
        return 1; // Return 1 jika login admin berhasil
    } else {
        printf("Login admin gagal. Silakan coba lagi.\n");
        return 0; // Return 0 jika login admin gagal
    }
}

// Fungsi untuk login user
int loginUser() {
    char username[100];
    char password[100];
    char encryptedPassword[100];
    
    	printf("                                                                              \n");
    printf("                                    _  _   ___   ___   _  _  ___  ___  ___          `__   __ _   _  _  __ ___  ___   _ \n");
    printf("                                   | \\| | / __| / _ \\ | \\| |/ __|| __|| _ \\      \\ \\ / /| | | || |/ // __|/ __| | |\n");
    printf("                                   | .  || (_ || (_) || .  |\\__ \\| _| |   /       \\   / | |_| ||   < \\__ \\\\__ \\ |_|\n");
    printf("                                    |_|\\_| \\___| \\___/ |_|\\_||___/|___||_|_\\        |_|   \\___/ |_|\\_\\|___/|___/ (_)\n");

    // Meminta pengguna untuk memasukkan informasi login user
    printf("Masukkan Username: ");
    scanf("%s", username);

    printf("Masukkan Password: ");
    scanf("%s", password);

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
            printf("Anda telah berhasil login sebagai user.\n");
            return 1; // Return 1 jika login berhasil
        }
    }

    // Menutup file
    fclose(file);

    printf("Login user gagal. Silakan coba lagi.\n");
    return 0; // Return 0 jika login gagal
}

// Fungsi untuk menampilkan pilihan login
int menuLogin() {
    int pilihan;
    
    printf("1. Login Admin\n");
    printf("2. Login User\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &pilihan);
    return pilihan;
}