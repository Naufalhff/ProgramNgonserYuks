#include "ariq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

addressRoot buatRoot ()
{
	addressRoot P;
	
	P = (addressRoot) malloc (sizeof(Root));
	
	if (P == NULL)
	{
		system("cls");
		printf("Alokasi memori gagal.\n\n");
		exit(1);
	}
	else
	{
		strcpy(P->info, "Data Pengunjung Konser");
		P->down = NULL;
	}
	
	return P;
}

addressKonser buatNodeKonser(int nomorKonser, infotype namaKonser, int maxVIP, int maxREG)
{
	addressKonser P;
	
	P = (addressKonser) malloc (sizeof(listKonser));
	
	if (P == NULL)
	{
		system("cls");
		printf("Alokasi memori gagal.\n\n");
		exit(1);
	}
	else
	{
		P->nomorKonser = nomorKonser;
		strcpy(P->info, namaKonser);
	    P->VIP = buatListUser(maxVIP);
	    P->REG = buatListUser(maxREG);
		P->next = NULL;
	}
	
	return P;
}

addressNode buatNodeUser(int id, char *username, int jumlah)
{
	addressNode P;
	
	P = (addressNode) malloc (sizeof(Node));
	
	if (P == NULL)
	{
		system("cls");
		printf("Alokasi memori gagal.\n\n");
		exit(1);
	}
	else
	{
		P->idUser = id;
		strcpy(P->nama, username);
		P->frekuensi = jumlah;
		P->next = NULL;
	}
	
	return P;
}

addressUser buatListUser(int maxList)
{
	addressUser P;
	
	P = (addressUser) malloc (sizeof(listUser));
	
	if (P == NULL)
	{
		system("cls");
		printf("Alokasi memori gagal.\n\n");
		exit(1);
	}
	else
	{
		P->front = NULL;
		P->rear = NULL;
		P->jumlah = 0;
		P->kapasitas = maxList;
	}
	
	return P;
}

addressKonser cariKonserById(addressKonser first, int idKonser)
{
    addressKonser trav;
	trav = first;
    
    while (trav != NULL)
    {
        if (trav->nomorKonser == idKonser)
        {
            return trav;
        }
        
        trav = trav->next;
    }
    
    return NULL;
}

int cariKonserByNama(addressRoot root, char *namaKonser) {
    addressKonser trav;
	int idKonser;
	
    trav = root->down;
    while (trav != NULL) {
        if (strcmp(trav->info, namaKonser) == 0) {
            idKonser = trav->nomorKonser;
            break;
        }
        trav = trav->next;
    }

    return idKonser;
}

addressNode cariUser(addressUser list, int idUser, addressNode *prev)
{
	addressNode trav;
	
    trav = list->front;
    *prev = NULL;
    while (trav != NULL)
    {
        if (trav->idUser == idUser)
        {
            return trav;
        }
        
        *prev = trav;
        trav = trav->next;
    }
    
    return NULL;
}

addressKonser enqueueKonser(addressKonser first, addressKonser nodeBaru)
{
    if (first == NULL)
    {
        return nodeBaru;
    }
    else
    {
        addressKonser trav = first;
        while (trav->next != NULL)
        {
            trav = trav->next;
        }
        trav->next = nodeBaru;
        
        return first;
    }
}

addressKonser enqueueKonserFromFile(char *filename, addressKonser first)
{
    FILE *file;
    addressKonser nodeBaru, trav;
    int id, jumlah_tiket_vip, jumlah_tiket_regular;
    char nama[50], tempat[50], bintang_tamu[50];
    struct tm tanggal;
    float harga_tiket_vip, harga_tiket_regular;
    
    file = fopen(filename, "r");
    
    if (file == NULL) 
    {
        file = fopen(filename, "w");
    }
    
    while (fscanf(file, "%d|%49[^|]|%d-%d-%d|%49[^|]|%49[^|]|%d|%f|%d|%f\n",
                  &id, nama, &tanggal.tm_mday, &tanggal.tm_mon, &tanggal.tm_year,
                  tempat, bintang_tamu, &jumlah_tiket_vip, &harga_tiket_vip,
                  &jumlah_tiket_regular, &harga_tiket_regular) != EOF)
    {
        nodeBaru = buatNodeKonser(id, nama, jumlah_tiket_vip, jumlah_tiket_regular);
        first = enqueueKonser(first, nodeBaru);
    }
    
    fclose(file);
    
    return first;
}

void enqueueFromFile(char *fileName, addressKonser first, addressRoot root)
{
    int userID, nomorTelepon, jumlahTiket, statusVerif, idKonser;
    float jumlahBayar, userBayar;
    char username[50], jenisTiket[10], namaKonser[50];
    
    FILE *file;

    file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("\nGagal membaca file.\n");
        return;
    }

    while (fscanf(file, "%d %s %d %s %d %s %f %f %d", &userID, username, &nomorTelepon, namaKonser, &jumlahTiket, jenisTiket, &jumlahBayar, &userBayar, &statusVerif) != EOF)
    {
        idKonser = cariKonserByNama(root, namaKonser);
        enqueue1(root->down, idKonser, jenisTiket, userID, username, jumlahTiket);
    }

    fclose(file);
}

void hapusFileDequeue(addressKonser konser, addressNode data)
{
    // Deklarasi variabel
    int userID, nomorTelepon, jumlahTiket, statusVerif;
    float jumlahBayar, userBayar;
    char username[50], namaKonser[100], jenisTiket[10];
    FILE *file, *fileTemp;

    file = fopen("datauser.txt", "r");
    fileTemp = fopen("temp1.txt", "w");

    if (file == NULL)
    {
        printf("\nGagal membaca file.\n");
        return;
    }

    while (fscanf(file, "%d %s %d %s %d %s %f %f %d", &userID, username, &nomorTelepon, namaKonser, &jumlahTiket, jenisTiket, &jumlahBayar, &userBayar, &statusVerif) != EOF)
    {
        if (userID != data->idUser && username != data->nama && namaKonser != konser->info && jumlahTiket != data->frekuensi)
        {
            fprintf(fileTemp, "%d %s %d %s %d %s %.2f %.2f %d\n", userID, username, nomorTelepon, namaKonser, jumlahTiket, jenisTiket, jumlahBayar, userBayar, statusVerif);
        }
    }

    fclose(file);
    fclose(fileTemp);

    remove("datauser.txt");
    rename("temp1.txt", "datauser.txt");
}

void dequeue1(addressKonser konser, addressUser list, int index)
{
    if (index < 0 || index >= list->jumlah) {
        printf("Indeks tidak valid.\n");
        return;
    }

    addressNode prev = NULL, current = list->front;
    for (int i = 0; i < index && current != NULL; ++i) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Indeks tidak valid.\n");
        return;
    }

    if (prev == NULL) {
        list->front = current->next;
    } else {
        prev->next = current->next;
    }

    if (current == list->rear) {
        list->rear = prev;
    }
    
	hapusFileDequeue(konser, current);
    list->jumlah -= current->frekuensi;
    
    free(current);
    printf("Data user berhasil dihapus.\n\n");
}

int tampilanULU(addressRoot root)
{
	addressKonser trav;
	int pilihanKonser;
	
	printf("%s\n", root->info);
		
	trav = root->down;
	while (trav != NULL)
	{
		printf("%d. %s (%d/%d)\n", trav->nomorKonser, trav->info, (trav->REG->jumlah + trav->VIP->jumlah), (trav->REG->kapasitas + trav->VIP->kapasitas));
		trav = trav->next;
	}
	printf("0. Keluar\n");
	printf("Konser yang ingin anda pilih: ");
	scanf("%d", &pilihanKonser);
	
	return pilihanKonser;
}

int VipOrReg ()
{
	int pilihanJT;
	
	printf("Jenis Tiket\n1. VIP\n2. REG\n0. Kembali\nJenis tiket yang ingin anda pilih: ");
	scanf("%d", &pilihanJT);
	
	return pilihanJT;
}

void simpanHistoryKehadiran(int idUser, char *nama, int frekuensi) 
{
    FILE *file = fopen("history_kehadiran.bin", "ab");
    if (file == NULL) 
	{
		FILE *file = fopen("history_kehadiran.bin", "wb");
		if (file == NULL)
		{
			printf("Gagal membuat file.\n");
			system("pause");
			exit(1);
		}
    } 
	else 
	{
        fwrite(&idUser, sizeof(int), 1, file);
        fwrite(nama, sizeof(char), 50, file);
        fwrite(&frekuensi, sizeof(int), 1, file);
        fclose(file);
    }
}

void kehadiranUser(addressUser list, int index, int jumlah)
{
    if (index < 0 || index >= list->jumlah) 
	{
        printf("Indeks tidak valid.\n");
        return;
    }

    addressNode current = list->front;
    for (int i = 0; i < index && current != NULL; ++i) 
	{
        current = current->next;
    }

    if (current == NULL) 
	{
        printf("Indeks tidak valid.\n");
        return;
    }
	
    simpanHistoryKehadiran(current->idUser, current->nama, current->frekuensi);
    printf("Jumlah tiket berhasil dikurangi.\n\n");
}

void printUser(addressNode front)
{
    int i = 0;
    addressNode trav = front;

    if (trav == NULL) 
	{
        return;
    }

    printf("=====================================================================\n");
    printf("| %-4s | %-5s | %-30s | %-15s |\n", "No", "ID", "Nama", "Tiket yang dibeli");
    printf("=====================================================================\n");
    while (trav != NULL) {
        printf("| %-4d | %-5d | %-30s | %-17d |\n", i + 1, trav->idUser, trav->nama, trav->frekuensi);
        trav = trav->next;
        i++;
    }
    printf("=====================================================================\n");
}

void menuLihatUser(addressRoot root)
{
    addressKonser konserPilihan;
    addressUser jenisTiketList;
    int hasilPilihan, hasilJT, pilihan;
    int idUser, jumlahTiket, indeks, jumlahKurang;
    char namaUser[50];
    char jenisTiketStr[10];

    do
    {
        hasilPilihan = tampilanULU(root);
        if (hasilPilihan < 0)
        {
            system("cls");
            printf("Pilihan anda tidak valid.\n\n");
        }
        else if (hasilPilihan == 0)
        {
            break;
        }
        else
        {
            konserPilihan = cariKonserById(root->down, hasilPilihan);
            if (konserPilihan == NULL)
            {
                system("cls");
                printf("Mohon maaf, konser dengan ID '%d' tidak ditemukan.\n\n", hasilPilihan);
            }
            else
            {
                system("cls");
                do
                {
                    hasilJT = VipOrReg();
                    if (hasilJT < 0 || hasilJT > 2)
                    {
                        system("cls");
                        printf("Pilihan anda tidak valid.\n\n");
                    }
                    else if (hasilJT == 1)
                    {
                        jenisTiketList = konserPilihan->VIP;
                        strcpy(jenisTiketStr, "VIP");
                        system("cls");
                        printf("=====================================================================\n");
                        printf("|                          List User VIP                            |\n");
                        printUser(jenisTiketList->front);
                    }
                    else if (hasilJT == 2)
                    {
                        jenisTiketList = konserPilihan->REG;
                        strcpy(jenisTiketStr, "REG");
                        system("cls");
                        printf("=====================================================================\n");
                        printf("|                          List User REG                            |\n");
                        printUser(jenisTiketList->front);
                    }
                    else
                    {
                        system("cls");
                    }
                    if (hasilJT == 1 || hasilJT == 2)
                    {
                        if (jenisTiketList->front != NULL)
                        {
                            printf("\n1. Hapus User\n2. Kehadiran User (Ketika konser berjalan)\n0. Kembali\nPilihan: ");
                            scanf("%d", &pilihan);

                            switch (pilihan)
                            {
                                case 1:
                                    printf("\nIndeks User yang akan dihapus: ");
                                    scanf("%d", &indeks);
                                    dequeue(konserPilihan, jenisTiketList, indeks - 1);
                                    break;
                                case 2:
                                    printf("\nIndeks User yang akan dikurangi: ");
                                    scanf("%d", &indeks);
                                    printf("Jumlah pengurangan: ");
                                    scanf("%d", &jumlahKurang);
                                    kehadiranUser(jenisTiketList, indeks - 1, jumlahKurang);
                                    break;
                                case 0:
                                	break;
                                default:
                                    printf("Pilihan tidak valid.\n");
                                    break;
                            }
                            system("pause");
                            system("cls");
                        }
                        else
                        {
                            printf("\nBelum ada user yang memesan tiket.\n\n");
                            system("pause");
                            system("cls");
                        }
                    }
                } while (hasilJT != 0);
            }
        }
    } while (hasilPilihan != 0);
}

void menuLihatHistory() 
{
    FILE *file = fopen("history_kehadiran.bin", "rb");
    if (file == NULL) 
	{
        printf("Belum ada history kehadiran.\n");
        return;
    }

    int idUser;
    char nama[50];
    int frekuensi;

    printf("=====================================================================\n");
    printf("|                          History Kehadiran                        |\n");
    printf("=====================================================================\n");
    printf("| %-5s | %-30s | %-24s |\n", "ID", "Nama", "Jumlah Tiket");
    printf("=====================================================================\n");
    while (fread(&idUser, sizeof(int), 1, file) == 1) 
	{
        fread(nama, sizeof(char), 50, file);
        fread(&frekuensi, sizeof(int), 1, file);
        printf("| %-5d | %-30s | %-24d |\n", idUser, nama, frekuensi);
    }
    printf("=====================================================================\n");

    fclose(file);

    printf("\n");
    system("pause");
    system("cls");
}

void rekursifHapusUser(addressNode *node) 
{
    if (*node == NULL)
        return;

    rekursifHapusUser(&(*node)->next);

    free(*node);
    *node = NULL;
}

void hapusKonserById(addressRoot root, int idKonser) 
{
    addressKonser prev;
    addressKonser curr;
	
	prev = NULL;
	curr = root->down;
	
    while (curr != NULL && curr->nomorKonser != idKonser) 
	{
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) 
	{
        return;
    }

    rekursifHapusUser(&curr->VIP->front);

    rekursifHapusUser(&curr->REG->front);

    if (prev == NULL) 
	{
        root->down = curr->next;
    }
	else 
	{
        prev->next = curr->next;
    }

    free(curr);
    curr = NULL;
}

