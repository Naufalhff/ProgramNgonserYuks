#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Pemesanan {
    char nama[100];
    int jumlah;
    char jenis[50];
    long int notelp;
    char konserNama[50];
} Pemesanan;

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

typedef struct {
    char info[50];
    int left, right;
} tiketTree;

typedef tiketTree Isi_Tree[101];

int generateuser() {
    srand(time(NULL));
    return rand() % 9000 + 1000;
}

void createTree(Isi_Tree X) {
    strcpy(X[1].info, "jenis tiket");
    X[1].left = -1;
    X[1].right = -1;

    int index = 2;
    strcpy(X[index].info, "VIP");
    X[index].left = -1;
    X[index].right = -1;
    X[1].left = index;

    index++;
    strcpy(X[index].info, "REG");
    X[index].left = -1;
    X[index].right = -1;
    X[1].right = index;
}

void printTree(Isi_Tree X, int node_index, int level) {
    if (node_index != -1) {
        int i;
        for (i = 0; i < level; i++) {
            printf("\t");
        }
        printf("Node: %s\n", X[node_index].info);
        printf("\n");

        // Cetak child kiri
        if (X[node_index].left != -1) {
            printf("Kiri: ");
            printTree(X, X[node_index].left, level + 1);
        }

        // Cetak child kanan
        if (X[node_index].right != -1) {
            printf("Kanan: ");
            printTree(X, X[node_index].right, level + 1);
        }
    }
}

float TotalBayar(char jenis[], int jumlah, struct Konser konser) {
    float hargaTiket = 0;
    if (strcmp(jenis, "VIP") == 0) {
        hargaTiket = konser.harga_tiket_vip;
    } else if (strcmp(jenis, "REG") == 0) {
        hargaTiket = konser.harga_tiket_regular;
    } else {
        printf("Jenis tiket tidak valid.\n");
        return -1;
    }
    return jumlah * hargaTiket;
}

void searchkonser(struct Konser *konser, int konserID, Pemesanan *pemesanan) {
    FILE *file = fopen("konser.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file konser.txt!\n");
        return;
    }
    int konserDitemukan = 0;
    while (fscanf(file, "%d|%[^|]|%d-%d-%d|%[^|]|%[^|]|%d|%f|%d|%f\n", &konser->id, konser->nama, &konser->tanggal.tm_mday, &konser->tanggal.tm_mon, &konser->tanggal.tm_year, konser->tempat, konser->bintang_tamu, &konser->jumlah_tiket_vip, &konser->harga_tiket_vip, &konser->jumlah_tiket_regular, &konser->harga_tiket_regular) != EOF) {
        if (konser->id == konserID) {
            konserDitemukan = 1;
            strcpy(pemesanan->konserNama, konser->nama);
            break;
        }
    }
    fclose(file);
    if (!konserDitemukan) {
        printf("Konser dengan ID tersebut tidak ditemukan.\n");
        return;
    }
}

void pesan(Pemesanan *pemesanan) {
    int userID = generateuser();
    struct Konser konser;
    int konserID;

    printf("Masukkan nama : ");
    scanf("%s", pemesanan->nama);
    printf("Masukkan no telp : ");
    scanf("%ld", &pemesanan->notelp);
    
    do {
        printf("Masukkan ID Konser yang Dipilih: ");
        scanf("%d", &konserID);
        searchkonser(&konser, konserID, pemesanan);
    } while (konser.id != konserID);

    
    searchkonser(&konser, konserID, pemesanan);
    
    printf("Masukkan jumlah tiket : ");
    scanf("%d", &pemesanan->jumlah);
    printf("Masukkan jenis tiket (VIP/REG): ");
    scanf("%s", pemesanan->jenis);

    float total = TotalBayar(pemesanan->jenis, pemesanan->jumlah, konser);
    if (total == -1) {
        return;
    }
    
    char data;
    printf("Total Bayar : %.2f\n", total);
    printf("Apakah yakin ingin memesan?(Y/N) :");
    while (getchar() != '\n');
    scanf("%c", &data);
    
    if ( data == 'Y' || 'y'){
    	FILE *fp = fopen("datauser.txt", "a");
	    if (fp != NULL) {
	        fprintf(fp, "%d %s %ld %s %d %s %.2f\n", userID, pemesanan->nama, pemesanan->notelp, pemesanan->konserNama, pemesanan->jumlah, pemesanan->jenis, total);;
	        printf("ID User : %d berhasil dipesan!", userID);
	    } else {
	        printf("Gagal menyimpan pemesanan.\n");
	    }
	    fclose(fp);
	}else{
		printf("kembali ke menu utama!");
	}
}


int main() {
    Pemesanan pemesanan;
    Isi_Tree tree;
    createTree(tree); 
    printf("Tree:\n");
    printTree(tree, 1, 0);
    pesan(&pemesanan);

    return 0;
}
