#include <stdio.h>
#include <stdlib.h>
#include "NAOMI.h"
#include "RASYID.h"
#include "YUDHIS.h"
#include "ARIQ.h"
#include "ROY.h"
#include "NAUFAL.h"

int main() {
    Queue q;
    initQueue(&q);
    bacaDataRegistrasi(&q);
    char kembali_ke_menu;
    char username[100];
    char password[100];
    char *fileKonser = "Konser.txt";
	char *fileUser = "datauser.txt";
	addressRoot root;
	root = buatRoot();
	root->down = enqueueKonserFromFile(fileKonser, root->down);
	enqueueFromFile(fileUser, root->down, root);
    

    do {
        int pilihan_menu;

        // Menampilkan menu registrasi atau login
        // Menampilkan menu registrasi atau login
		system("cls");
        printf("                                                                              \n");
        printf("                                    _  _   ___   ___   _  _  ___  ___  ___          `__   __ _   _  _  __ ___  ___   _ \n");
        printf("                                   | \\| | / __| / _ \\ | \\| |/ __|| __|| _ \\      \\ \\ / /| | | || |/ // __|/ __| | |\n");
        printf("                                   | .  || (_ || () || .  |\\_ \\| | |   /       \\   / | || ||   < \\__ \\\\__ \\ |_|\n");
        printf("                      \\!!!/        ||\\| \\| \\/ ||\\||/||||\\        ||   \\/ ||\\\\|/|/ (_)\n");
        printf("                      |===|                                                                                              \n");
        printf("                      |!!!|                                                                                             \n");
        printf("                      |!!!|                                                                                             \n");
        printf("                      |!!!|                                                                                             \n");
        printf("                      |!!!|                                                                                             \n");
        printf("                     |!!!|_               1. Registrasi                                                                          \n");
        printf("                   .+=|!!!|--.`.            2. Login                                                                          \n");
        printf("                 .'   |!!!|   `\\            3. Tampilkan Antrian Registrasi                                                       \n");
        printf("                /     !===!     \\           4. Simpan Data Registrasi                                                                          \n");
        printf("               |    /|!!!|\\    ||           5. Keluar                                                                           \n");
        printf("                \\   \\!!!!!/   //                                                                                       \n");
        printf("                 )   `==='   ((                                                                                     \n");
        printf("               .'    !!!!!    `..                                                                                      \n");
        printf("              /      !!!!!      \\                                                                                      \n");
        printf("             |       !!!!!       ||                                                                                    \n");
        printf("             |       !!!!!       ||                                                                                    \n");
        printf("             |       !!!!!       ||                                                                                    \n");
        printf("              \\     =======     //                                                                                     \n");
        printf("                `.    ooooo     '                                                                                      \n");
        printf("                 `-._.-'   															");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan_menu);
        clearInputBuffer();

        switch (pilihan_menu) {
            case 1:
            	system("cls");
                registrasi(&q);
                simpanDataRegistrasi(&q);
                break;
            case 2: {
                system("cls");
                int pilihan_login = menuLogin();
                system("cls");
                switch (pilihan_login) {
                    case 1:
                        if (loginAdmin()) {
						    int admin_choice;
						    system("cls");
                            do {
                                printf("Menu Admin:\n");
                                printf("1. Edit Konser\n");
                                printf("2. Tambah Promo\n");
                                printf("3. Hapus Promo\n");
                                printf("4. Validasi Pembayaran\n");
                                printf("5. Histori Kehadiran\n"); 
                                printf("6. Lihat Data User\n");
								printf("7. Kembali\n");                         
                                printf("Pilih menu: ");
                                scanf("%d", &admin_choice);
                                clearInputBuffer();
                                
                                switch (admin_choice) {
                                    case 1:
                                    	system("cls");
                                        muatDataKonser();
    									int pilihan;
    										do {
        										tampilkanMenu();
        										scanf("%d", &pilihan);
        										fflush(stdin);

        										switch (pilihan) {
            										case 1:
            											system("cls");
                										prosesLihatKonser();
                										break;
            										case 2:
            											system("cls");
                										prosesTambahKonser();
                										break;
            										case 3:
            											system("cls");
                										prosesEditKonser();
                										break;
            										case 4:
            											system("cls");
                										prosesHapusKonser();
                										break;
            										case 5:
                										printf("Keluar dari program. Sampai jumpa!\n");
                										break;
            										default:
                										printf("Menu tidak valid.\n");
        										}
    										} while (pilihan != 5);
                                        break;
                                    case 2:
                                    	system("cls");
                                        muatPromoDariFile();
                                        tambahPromoModul();
                                        break;
                                    case 3:
                                    	system("cls");
                                    	muatPromoDariFile();
                                        hapusPromoModul();
                                        break;
                                    case 4:
                                    	system("cls");
                                       	readAndValidateData("datauser.txt");
                                       	printf("Validasi Data Berhasil.\n\n");
                                        break;
                                    case 5:
	                                   	system("cls");
                                   		menuLihatUser(root);
                                        break;
                                    case 6:
                                   		system("cls");
                                    	menuLihatHistory();
										break;
									case 7:
										break;                                        
                                    default:
                                        printf("Pilihan tidak valid.\n");
                                        break;
                                }
                            } while (admin_choice != 5);
                        }
                        break;
                    case 2:
                        system("cls");
                        if (loginUser()) {
                            menuUser();
                        }
                        break;
                    default:
                        printf("Pilihan tidak valid.\n");
                        break;
                }
                break;
            }
            case 3:
                system("cls");
                printf("Daftar Antrian Registrasi:\n");
                displayQueue(&q);
                break;
            case 4:
                printf("Keluar dari program.\n");
                return 0;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }

        printf("Kembali ke menu awal? (y/n): ");
        scanf(" %c", &kembali_ke_menu);
        clearInputBuffer();
    } while (kembali_ke_menu == 'y' || kembali_ke_menu == 'Y');

    return 0;
}
