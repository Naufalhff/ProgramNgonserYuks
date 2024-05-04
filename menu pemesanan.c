#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//tahap proses, belum kepikiran tree nya

typedef struct{
	char nama[100];
	int jumlah;
	char jenis[50];
	long int notelp;
}Pemesanan;

typedef struct{
	
};

int generateuser(){
	srand(time(NULL));
	
	return rand() % (9999 - 1000 + 1) + 100;
}

void pesan(){
	Pemesanan pemesanan;
	int userID = generateuser();

	printf("Masukkan nama : ");
	scanf("%s", pemesanan.nama);
	printf("Masukkan no telp : ");
	scanf("%ld", &pemesanan.notelp);	
	printf("Masukkan jumlah tiket : ");
	scanf("%d", &pemesanan.jumlah);
	printf("Masukkan jenis tiket (VIP/REG): ");
	scanf("%s", pemesanan.jenis);
	
	printf("id user : %d\n", userID);
	printf("total tiket yang harus dibayar : \n");
	
	
	
	enkripsi(&pemesanan.notelp, 5);
	FILE *fp = fopen("datauser.txt", "a");
	if (fp != NULL){
		fprintf(fp, "%d %s %ld %d %s\n", userID,pemesanan.nama, pemesanan.notelp,pemesanan.jumlah, pemesanan.jenis);
		printf("akun berhasil didaftarkan!");
	}else{
		printf("akun gagal didaftarkan");
	}
	fclose(fp);
}

void enkripsi(int *no, int kunci) {
    int i;
    for (i = 0; no[i] != '\0'; i++) {
        if (no[i] >= '0' && no[i] <= '11') {
            no[i] = '0' + (no[i] - '0' + kunci) % 12;
        }
    }
}

int main(){
	pesan();
	return 0;
}