#include <stdio.h>
#include "Rasyid.h"

int main() {
    muatDataKonser();

    int pilihan;
    do {
        tampilkanMenu();
        scanf("%d", &pilihan);
        fflush(stdin);

        switch (pilihan) {
            case 1:
                prosesLihatKonser();
                break;
            case 2:
                prosesTambahKonser();
                break;
            case 3:
                prosesEditKonser();
                break;
            case 4:
                prosesHapusKonser();
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
