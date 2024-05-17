#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct Pemesanan {
    int idUser;
    char nama[100];
    int jumlah;
    char jenis[50];
    int notelp;
    char konserNama[50];
} Pemesanan;

typedef struct Konser {
    int id;
    char nama[50];
    struct tm tanggal;
    char tempat[50];
    char bintang_tamu[50];
    int jumlah_tiket_vip;
    float harga_tiket_vip;
    int jumlah_tiket_regular;
    float harga_tiket_regular;
} Konser;

typedef struct Node {
    int idUser;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

//protep
bool listEmpty(Queue* q);
void createQueue(Queue* q);
void insertAkhir(Queue* q, int idUser);
void insertMultipleAkhir(Queue* q, int idUserStart, int jumlah);
int generateUser();
float TotalBayar(char jenis[], int jumlah, Konser konser);
int loadKonserFromFile(Konser konserList[], int maxKonser);
void saveKonserToFile(Konser konserList[], int konserCount);
void searchKonser(Konser konserList[], int konserCount, int konserID, Konser* konser, Pemesanan* pemesanan);
void saveQueueToFile(Queue* q, const char* filename);
void loadQueueFromFile(Queue* q, const char* filename);
void pesan(Queue* vipQueue, Queue* regQueue);
void printQueue(Queue* q);

bool listEmpty(Queue* q) {
    return (q->front == NULL);
}

void createQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

void insertAkhir(Queue* q, int idUser) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Alokasi memori gagal!\n");
        return;
    }
    newNode->idUser = idUser;
    newNode->next = NULL;

    if (q->rear) {
        q->rear->next = newNode;
    } else {
        q->front = newNode;
    }
    q->rear = newNode;
}

void insertMultipleAkhir(Queue* q, int idUserStart, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        insertAkhir(q, idUserStart + i);
    }
}

int generateUser() {
    srand(time(NULL));
    return rand() % 9000 + 1000;
}

float TotalBayar(char jenis[], int jumlah, Konser konser) {
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

int loadKonserFromFile(Konser konserList[], int maxKonser) {
    FILE* file = fopen("konser.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file konser.txt!\n");
        return 0;
    }
    int count = 0;
    while (count < maxKonser && fscanf(file, "%d|%[^|]|%d-%d-%d|%[^|]|%[^|]|%d|%f|%d|%f\n",
                                       &konserList[count].id, konserList[count].nama, &konserList[count].tanggal.tm_mday,
                                       &konserList[count].tanggal.tm_mon, &konserList[count].tanggal.tm_year,
                                       konserList[count].tempat, konserList[count].bintang_tamu, &konserList[count].jumlah_tiket_vip,
                                       &konserList[count].harga_tiket_vip, &konserList[count].jumlah_tiket_regular,
                                       &konserList[count].harga_tiket_regular) != EOF) {
        konserList[count].tanggal.tm_mon--; 
        konserList[count].tanggal.tm_year -= 1900;
        count++;
    }
    fclose(file);
    return count;
}

void saveKonserToFile(Konser konserList[], int konserCount) {
    FILE* file = fopen("konser.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file konser.txt untuk menulis!\n");
        return;
    }
    for (int i = 0; i < konserCount; i++) {
        fprintf(file, "%d|%s|%d-%d-%d|%s|%s|%d|%f|%d|%f\n", konserList[i].id, konserList[i].nama,
                konserList[i].tanggal.tm_mday, konserList[i].tanggal.tm_mon + 1, konserList[i].tanggal.tm_year + 1900,
                konserList[i].tempat, konserList[i].bintang_tamu, konserList[i].jumlah_tiket_vip, konserList[i].harga_tiket_vip,
                konserList[i].jumlah_tiket_regular, konserList[i].harga_tiket_regular);
    }
    fclose(file);
}

void searchKonser(Konser konserList[], int konserCount, int konserID, Konser* konser, Pemesanan* pemesanan) {
    int konserDitemukan = 0;
    for (int i = 0; i < konserCount; i++) {
        if (konserList[i].id == konserID) {
            *konser = konserList[i];
            strcpy(pemesanan->konserNama, konserList[i].nama);
            konserDitemukan = 1;
            break;
        }
    }
    if (!konserDitemukan) {
        printf("Konser dengan ID tersebut tidak ditemukan.\n");
    }
}

void saveQueueToFile(Queue* q, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file %s untuk menulis!\n", filename);
        return;
    }
    Node* current = q->front;
    while (current != NULL) {
        fprintf(file, "%d\n", current->idUser);
        current = current->next;
    }
    fclose(file);
}

void loadQueueFromFile(Queue* q, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file %s untuk membaca!\n", filename);
        return;
    }
    int idUser;
    while (fscanf(file, "%d\n", &idUser) != EOF) {
        insertAkhir(q, idUser);
    }
    fclose(file);
}

void pesan(Queue* vipQueue, Queue* regQueue) {
    Pemesanan pemesanan;
    pemesanan.idUser = generateUser();
    Konser konserList[100];
    Konser konser;
    int konserCount = loadKonserFromFile(konserList, 100);
    int konserID;

    printf("Masukkan nama: ");
    scanf("%s", pemesanan.nama);
    printf("Masukkan no telp: ");
    scanf("%d", &pemesanan.notelp);

    do {
        printf("Masukkan ID Konser yang Dipilih: ");
        scanf("%d", &konserID);
        searchKonser(konserList, konserCount, konserID, &konser, &pemesanan);
    } while (konser.id != konserID);

    printf("Masukkan jumlah tiket: ");
    scanf("%d", &pemesanan.jumlah);

    int tiketCukup = 0;

    while (!tiketCukup) {
        printf("Masukkan jenis tiket (VIP/REG): ");
        scanf("%s", pemesanan.jenis);

        if (strcmp(pemesanan.jenis, "VIP") == 0) {
	    if (konser.jumlah_tiket_vip >= pemesanan.jumlah) {
	        konser.jumlah_tiket_vip -= pemesanan.jumlah;
	        tiketCukup = 1;
	    } else {
	        printf("Tiket VIP tidak cukup tersedia! Sisa tiket VIP: %d\n", konser.jumlah_tiket_vip);
	        if (konser.jumlah_tiket_regular >= pemesanan.jumlah) {
	            printf("Silakan pilih tiket REG. Sisa tiket REG: %d\n", konser.jumlah_tiket_regular);
	        } else {
	            printf("Maaf, tiket REG tidak cukup tersedia juga.\n");
	            return;
	        }
	    }
		} else if (strcmp(pemesanan.jenis, "REG") == 0) {
		    if (konser.jumlah_tiket_regular >= pemesanan.jumlah) {
		        konser.jumlah_tiket_regular -= pemesanan.jumlah;
		        tiketCukup = 1;
		    } else {
		        printf("Tiket Regular tidak cukup tersedia! Sisa tiket REG: %d\n", konser.jumlah_tiket_regular);
		        if (konser.jumlah_tiket_vip >= pemesanan.jumlah) {
		            printf("Silakan pilih tiket VIP. Sisa tiket VIP: %d\n", konser.jumlah_tiket_vip);
		        } else {
		            printf("Maaf, tiket VIP tidak cukup tersedia juga.\n");
		            return;
		        }
		    }
		} else {
		    printf("Jenis tiket tidak valid. Silakan pilih VIP atau REG.\n");
		    return;
		}

    }
    if (konser.jumlah_tiket_vip < pemesanan.jumlah && konser.jumlah_tiket_regular < pemesanan.jumlah) {
            printf("Maaf, konser ini telah sold out.\n");
            return;
        }

    float total = TotalBayar(pemesanan.jenis, pemesanan.jumlah, konser);
    if (total == -1) {
        return;
    }

    char data;
    printf("Total Bayar: %.2f\n", total);
    printf("Apakah yakin ingin memesan?(Y/N): ");
    while (getchar() != '\n');
    scanf("%c", &data);

    if (data == 'Y' || data == 'y') {
        FILE* fp = fopen("datauser.txt", "a");
        if (fp != NULL) {
            fprintf(fp, "%d %s %d %s %d %s %.2f %d %d\n", pemesanan.idUser, pemesanan.nama, pemesanan.notelp, pemesanan.konserNama, pemesanan.jumlah, pemesanan.jenis, total, 0, -1);
            printf("ID User: %d berhasil dipesan!\n", pemesanan.idUser);
            fclose(fp);

            if (strcmp(pemesanan.jenis, "VIP") == 0) {
                insertMultipleAkhir(vipQueue, pemesanan.idUser, pemesanan.jumlah);
                saveQueueToFile(vipQueue, "vipQueue.txt");
            } else if (strcmp(pemesanan.jenis, "REG") == 0) {
                insertMultipleAkhir(regQueue, pemesanan.idUser, pemesanan.jumlah);
                saveQueueToFile(regQueue, "regQueue.txt");
            }

            // Update konser list and save back to file
            for (int i = 0; i < konserCount; i++) {
                if (konserList[i].id == konser.id) {
                    konserList[i] = konser;
                    break;
                }
            }
            saveKonserToFile(konserList, konserCount);
        } else {
            printf("Gagal menyimpan pemesanan.\n");
        }
    } else {
        printf("Kembali ke menu utama!\n");
    }
}

void printQueue(Queue* q) {
    Node* current = q->front;
    while (current != NULL) {
        printf("%d ", current->idUser);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Queue vipQueue, regQueue;
    createQueue(&vipQueue);
    createQueue(&regQueue);

    loadQueueFromFile(&vipQueue, "vipQueue.txt");
    loadQueueFromFile(&regQueue, "regQueue.txt");

    pesan(&vipQueue, &regQueue);

    printf("Antrian VIP:\n");
    printQueue(&vipQueue);
    printf("\nAntrian REG:\n");
    printQueue(&regQueue);

    return 0;
}
