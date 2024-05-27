#include "ariq.h"
#include "roy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

addressRoot buatRoot ()
{
	// Deklarasi variabel
	addressRoot P;

	// Alokasi memori untuk node Root
	P = (addressRoot) malloc (sizeof(Root));

	// Cek apakah alokasi memori berhasil
	if (P == NULL)
	{
		system("cls");
		printf("Alokasi memori gagal.\n\n");
		exit(1);
	}
	else
	{
		// Inisialisasi node Root
		strcpy(P->info, "Data Pengunjung Konser");
		P->down = NULL;
	}
	
	// Mengembalikan pointer ke node Root yang baru dibuat
	return P;
}

addressKonser buatNodeKonser(int nomorKonser, infotype namaKonser, int maxVIP, int maxREG)
{
	// Deklarasi variabel
	addressKonser P;
	
	// Alokasi memori untuk node list konser
	P = (addressKonser) malloc (sizeof(listKonser));

	// Cek apakah alokasi memori berhasil
	if (P == NULL)
	{
		system("cls");
		printf("Alokasi memori gagal.\n\n");
		exit(1);
	}
	else
	{
		// Inisialisasi node list konser
		P->nomorKonser = nomorKonser;
		strcpy(P->info, namaKonser);
	    P->VIP = buatListUser(maxVIP);
	    P->REG = buatListUser(maxREG);
		P->next = NULL;
	}
	
	// Mengembalikan pointer ke node list konser yang baru dibuat
	return P;
}

addressNode buatNodeUser(int id, char *username, int jumlah)
{
	// Deklarasi variabel
	addressNode P;
	
	// Alokasi memori untuk node User
	P = (addressNode) malloc (sizeof(Node));

	// Cek apakah alokasi memori berhasil
	if (P == NULL)
	{
		system("cls");
		printf("Alokasi memori gagal.\n\n");
		exit(1);
	}
	else
	{
		// Inisialisasi node User
		P->idUser = id;
		strcpy(P->nama, username);
		P->frekuensi = jumlah;
		P->next = NULL;
	}
	
	// Mengembalikan pointer ke node User yang baru dibuat
	return P;
}

addressUser buatListUser(int maxList)
{
	// Deklarasi variabel
	addressUser P;

	// Alokasi memori untuk list User
	P = (addressUser) malloc (sizeof(listUser));

	// Cek apakah alokasi memori berhasil
	if (P == NULL)
	{
		system("cls");
		printf("Alokasi memori gagal.\n\n");
		exit(1);
	}
	else
	{
		// Inisialisasi list User
		P->front = NULL;
		P->rear = NULL;
		P->jumlah = 0;
		P->kapasitas = maxList;
	}
	
	// Mengembalikan pointer ke list User yang baru dibuat
	return P;
}

addressKonser cariKonserById(addressKonser first, int idKonser)
{
    // Deklarasi variabel
    addressKonser trav;
    
    // Inisialisasi variabel
    trav = first;
    
    // Loop untuk traversal list sampai akhir atau sampai konser ditemukan
    while (trav != NULL)
    {
        // Cek apakah nomor konser dari node saat ini sesuai dengan idKonser yang dicari
        if (trav->nomorKonser == idKonser)
        {
            // Jika cocok, kembalikan node saat ini
            return trav;
        }
        
        // Pindah ke node berikutnya dalam list
        trav = trav->next;
    }
    
    // Jika konser dengan id konser tidak ditemukan, kembalikan NULL
    return NULL;
}

int cariKonserByNama(addressRoot root, char *namaKonser) 
{
    // Deklarasi variabel
    addressKonser trav;
    int idKonser;
    
    // Inisialisasi variabel
    trav = root->down;
    
    // Loop untuk traversal list sampai akhir atau sampai konser ditemukan
    while (trav != NULL) 
    {
        // Cek apakah info nama konser dari node saat ini sesuai dengan nama konser yang dicari
        if (strcmp(trav->info, namaKonser) == 0) 
        {
            // Jika cocok, simpan nomor konser dalam idKonser
            idKonser = trav->nomorKonser;
            break;
        }
        
        // Pindah ke node berikutnya dalam list
        trav = trav->next;
    }

    // Kembalikan id konser jika tidak ditemukan, id konser akan mengembalikan nilai terakhir yang dipegang
    return idKonser;
}

addressNode cariUserByIndex(addressUser list, int index, addressNode *prev) 
{
	// Deklarasi variabel
    addressNode current;
    int i;

    // Inisialisasi variabel
    current = list->front;
    *prev = NULL;

    // Menelusuri list hingga mencapai index yang diinginkan
    for (i = 0; i < index && current != NULL; ++i) 
	{
        *prev = current;
        current = current->next;
    }

    // Mengembalikan NULL jika index melebihi panjang list
    if (current == NULL) 
	{
        return NULL;
    }

    // Mengembalikan pointer ke node pada index yang diinginkan
    return current;
}

addressKonser pushKonser(addressKonser first, addressKonser nodeBaru)
{
	// Deklarasi variabel
    addressKonser trav;
    
    // Inisialisasi variabel
    trav = first;

    // Jika list konser masih kosong, node baru menjadi node pertama
    if (first == NULL)
    {
        return nodeBaru;
    }
    else
    {
        // Menelusuri list hingga akhir dan menambahkan node baru di sana
        while (trav->next != NULL)
        {
            trav = trav->next;
        }
        trav->next = nodeBaru;
        
        // Mengembalikan pointer ke node pertama
        return first;
    }
}

addressKonser pushKonserFromFile(char *filename, addressKonser first)
{
	// Deklarasi variabel
    FILE *file;
    addressKonser nodeBaru, trav;
    int id, jumlah_tiket_vip, jumlah_tiket_regular;
    char nama[50], tempat[50], bintang_tamu[50];
    struct tm tanggal;
    float harga_tiket_vip, harga_tiket_regular;
    
    // Inisialisasi variabel file
    file = fopen(filename, "r");
    
    // Jika file tidak ditemukan, buat file baru
    if (file == NULL) 
    {
        file = fopen(filename, "w");
        if (file == NULL)
        {
        	system("cls");
        	printf("Gagal membuat file.\n\n");
        	exit(1);
		}
    }

    // Membaca data dari file dan menambahkannya ke list konser
    while (fscanf(file, "%d|%49[^|]|%d-%d-%d|%49[^|]|%49[^|]|%d|%f|%d|%f\n",
                  &id, nama, &tanggal.tm_mday, &tanggal.tm_mon, &tanggal.tm_year,
                  tempat, bintang_tamu, &jumlah_tiket_vip, &harga_tiket_vip,
                  &jumlah_tiket_regular, &harga_tiket_regular) != EOF)
    {
    
        // Membuat node baru untuk setiap baris data yang dibaca
        nodeBaru = buatNodeKonser(id, nama, jumlah_tiket_vip, jumlah_tiket_regular);
        
        // Menambah node baru ke dalam list konser
        first = pushKonser(first, nodeBaru);
    }
    
    // Menutup file setelah selesai membaca
    fclose(file);
    
    // Mengembalikan pointer ke node pertama dalam list konser
    return first;
}

void pushFromFile(char *fileName, addressKonser first, addressRoot root)
{
    // Deklarasi variabel
    int userID, jumlahTiket, statusVerif, idKonser;
    float jumlahBayar, userBayar;
    char username[50], jenisTiket[10], namaKonser[50], email[50];
    FILE *file;

    // Inisialisasi variabel file
    file = fopen(fileName, "r");

    // Cek apakah file berhasil dibuka
    if (file == NULL)
    {
        system("cls");
        printf("Gagal membaca file.\n\n");
        exit(1);
    }

    // Membaca data dari file dan memproses setiap baris
    while (fscanf(file, "%d %s %s %s %d %s %f %f %d", &userID, username, email, namaKonser, &jumlahTiket, jenisTiket, &jumlahBayar, &userBayar, &statusVerif) != EOF)
    {
    	int kunci = 13;
        dekripsi(username, kunci);
        dekripsi(email, kunci);

        // Cari id konser berdasarkan nama konser
        idKonser = cariKonserByNama(root, namaKonser);

        // Tambahkan data user ke dalam list konser yang sesuai
        push(root->down, idKonser, jenisTiket, userID, username, jumlahTiket);
    }

    // Menutup file setelah selesai
    fclose(file);
}

void hapusFilePop(addressKonser konser, addressNode data)
{
    // Deklarasi variabel
    int userID, jumlahTiket, statusVerif;
    float jumlahBayar, userBayar;
    char username[50], namaKonser[100], jenisTiket[10], email[50];
    FILE *file, *fileTemp;

    // Inisialisasi variabel file dan fileTemp
    file = fopen("datauser.txt", "r");
    fileTemp = fopen("temp1.txt", "w");

    // Cek apakah file berhasil dibuka
    if (file == NULL)
    {
    	system("cls");
        printf("Gagal membaca file.\n\n");
        exit(1);
    }
    
    // Cek apakah fileTemp berhasil dibuat
    if (fileTemp == NULL)
    {
    	system("cls");
        printf("Gagal membuat file.\n\n");
        exit(1);
	}

    // Membaca data dari file dan menulis ke file sementara jika data tidak cocok dengan yang akan dihapus
    while (fscanf(file, "%d %s %s %s %d %s %f %f %d", &userID, username, email, namaKonser, &jumlahTiket, jenisTiket, &jumlahBayar, &userBayar, &statusVerif) != EOF)
    {
		int kunci = 13;
        dekripsi(username, kunci);
        dekripsi(email, kunci);
	    
        // Memeriksa apakah data cocok dengan yang akan dihapus
        if (userID != data->idUser && strcmp(username, data->nama) != 0 && strcmp(namaKonser, konser->info) != 0 && jumlahTiket != data->frekuensi)
        {
            // Menulis data yang tidak cocok ke file sementara
            fprintf(fileTemp, "%d %s %s %s %d %s %.2f %.2f %d\n", userID, username, email, namaKonser, jumlahTiket, jenisTiket, jumlahBayar, userBayar, statusVerif);
        }
    }

    // Menutup file setelah selesai
    fclose(file);
    fclose(fileTemp);

    // Menghapus file asli dan menggantinya dengan file sementara
    remove("datauser.txt");
    rename("temp1.txt", "datauser.txt");
}

void pop(addressKonser konser, addressUser list, int index) 
{
    // Deklarasi variabel
    addressNode prev;
    addressNode current;

    // Cek apakah indeks valid
    if (index < 0 || index >= list->jumlah) 
	{
        printf("Indeks tidak valid.\n");
        return;
    }

    // Inisialisasi variabel
    prev = NULL;
    current = cariUserByIndex(list, index, &prev);

    // Cek apakah current valid
    if (current == NULL) 
	{
        printf("Indeks tidak valid.\n");
        return;
    }

    // Menghapus node dari list
    if (prev == NULL) // Jika node yang dihapus adalah node pertama
	{
        list->front = current->next; // Atur front ke node berikutnya
    } 
	else // Jika node yang dihapus bukan node pertama
	{
        prev->next = current->next; // Atur next dari node sebelumnya ke node berikutnya
    }

    // Jika node yang dihapus adalah node terakhir
    if (current == list->rear) 
	{
        list->rear = prev; // Atur rear ke node sebelumnya
    }

    // Menghapus data dari file
    hapusFilePop(konser, current);

    // Kurangi jumlah user dalam list
    list->jumlah -= current->frekuensi;

    // Membebaskan memori yang dialokasikan untuk node saat ini
    free(current);

    // Menampilkan pesan sukses
    printf("Data user berhasil dihapus.\n\n");
}

int tampilanULU(addressRoot root)
{
    // Deklarasi variabel
    addressKonser trav;
    int pilihanKonser;

    // Inisialisasi variabel
    trav = root->down;

	// Menampilkan info dalam root
    printf("%s\n", root->info);

    // Menampilkan list konser
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
    // Deklarasi variabel
    int pilihanJT;

    // Menampilkan pilihan jenis tiket
    printf("Jenis Tiket\n1. VIP\n2. REG\n0. Kembali\nJenis tiket yang ingin anda pilih: ");
    scanf("%d", &pilihanJT);

    return pilihanJT;
}

void simpanHistoryKehadiran(int idUser, char *nama, int frekuensi) 
{
    // Deklarasi variabel
    FILE *file;
    
    // Inisialisasi file
    file = fopen("history_kehadiran.bin", "ab");
    
    // Menangani kesalahan jika gagal membuka file
    if (file == NULL) 
	{
		file = fopen("history_kehadiran.bin", "wb");
		if (file == NULL)
		{
			system("cls");
			printf("Gagal membuat file.\n\n");
			exit(1);
		}
    } 
	else 
	{
        // Menulis data ke file
        fwrite(&idUser, sizeof(int), 1, file);
        fwrite(nama, sizeof(char), 50, file);
        fwrite(&frekuensi, sizeof(int), 1, file);
        
        // Menutup file setelah selesai
        fclose(file);
    }
}

void kehadiranUser(addressUser list, int index, int jumlah) 
{
    // Deklarasi variabel
    addressNode prev, current;

    // Validasi indeks
    if (index < 0 || index >= list->jumlah) 
	{
        printf("Indeks tidak valid.\n");
        return;
    }

    // Inisialisasi variabel
    prev = NULL;
    current = cariUserByIndex(list, index, &prev);

    // Validasi current
    if (current == NULL) 
	{
        printf("Indeks tidak valid.\n");
        return;
    }

    // Simpan kehadiran user
    simpanHistoryKehadiran(current->idUser, current->nama, current->frekuensi);
    printf("Jumlah tiket berhasil dikurangi.\n\n");
}

void printUser(addressNode front)
{
    // Deklarasi variabel
    int i = 0;
    addressNode trav = front;

    // Cek apakah list kosong
    if (trav == NULL) 
	{
        return;
    }

    // Mencetak header tabel
    printf("| %-4s | %-5s | %-30s | %-15s |\n", "No", "ID", "Nama", "Tiket yang dibeli");
    printf("=====================================================================\n");

    // Melakukan iterasi dan mencetak setiap node dalam list
    while (trav != NULL) 
	{
        printf("| %-4d | %-5d | %-30s | %-17d |\n", i + 1, trav->idUser, trav->nama, trav->frekuensi);
        trav = trav->next;
        i++;
    }
    printf("=====================================================================\n");
}

void lihatDetailUser(addressUser list, addressKonser konserPilihan, int JT, int index)
{
    // Deklarasi variabel
    int userID, jumlahTiket, statusVerif;
    float jumlahBayar, userBayar;
    char username[50], namaKonser[100], jenisTiket[10], pJT[4], email[50];
    addressNode prev, current;
    
    // Inisialisasi file
    FILE *file = fopen("datauser.txt", "r");

    // Cek apakah file berhasil dibuka
    if (file == NULL)
    {
        printf("Gagal membaca file.\n");
        return;
    }

    // Validasi indeks
    if (index < 0 || index >= list->jumlah) 
	{
        printf("Indeks tidak valid.\n");
        fclose(file);
        return;
    }

    // Inisialisasi variabel
    prev = NULL;
	current = cariUserByIndex(list, index, &prev);

    // Validasi current
    if (current == NULL) 
	{
        printf("Indeks tidak valid.\n");
        fclose(file);
        return;
    }

    // Menentukan jenis tiket berdasarkan parameter JT
    if (JT == 1)
    {
        strcpy(pJT, "VIP");
    }
    else
    {
        strcpy(pJT, "REG");
    }

    // Mencari data user dalam file
    while (fscanf(file, "%d %s %s %s %d %s %f %f %d", &userID, username, email, namaKonser, &jumlahTiket, jenisTiket, &jumlahBayar, &userBayar, &statusVerif) != EOF)
    {
    	int kunci = 13;
        dekripsi(username, kunci);
        dekripsi(email, kunci);
        // Memeriksa apakah data cocok dengan yang dicari
        if (userID == current->idUser && strcmp(username, current->nama) == 0 && strcmp(namaKonser, konserPilihan->info) == 0 && jumlahTiket == current->frekuensi && strcmp(pJT, jenisTiket) == 0)
        {
            // Mencetak detail user
            printf("\nUser ID: %d\n", userID);
            printf("Username: %s\n", username);
            printf("Email: %s\n", email);
            printf("Konser: %s\n", namaKonser);
            printf("Jumlah Tiket: %d\n", jumlahTiket);
            printf("Jenis Tiket: %s\n", jenisTiket);
            printf("Jumlah yang harus dibayar: %.2f\n", jumlahBayar);
            printf("Jumlah yang terbayar: %.2f\n", userBayar);

            // Mencetak status verifikasi
            if (statusVerif == -1)
            {
                printf("Status Verifikasi: Pending\n\n");
            }
            else if (statusVerif == 0)
            {
                printf("Status Verifikasi: Lunas\n\n");
            }
            else
            {
                printf("Status Verifikasi: Belum Lunas\n\n");
            }
        }
        // Hentikan iterasi setelah data ditemukan
//        break;
    }
    
    // Menutup file setelah selesai
    fclose(file);
}

void menuLihatUser(addressRoot root) 
{
    // Deklarasi variabel
    addressKonser konserPilihan;
    addressUser jenisTiketList;
    int hasilPilihan, hasilJT, pilihan;
    int indeks, jumlahKurang;
    char jenisTiketStr[10];

    // Proses menu untuk melihat user
    do
	{
        // Tampilkan daftar konser
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
            // Cari konser sesuai dengan ID yang dipilih
            konserPilihan = cariKonserById(root->down, hasilPilihan);
            if (konserPilihan == NULL) 
			{
                system("cls");
                printf("Mohon maaf, konser dengan ID '%d' tidak ditemukan.\n\n", hasilPilihan);
            }
			else
			{
                // Pilih jenis tiket untuk ditampilkan (VIP atau REG)
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
                        printf("=====================================================================\n");
                        printUser(jenisTiketList->front);
                    }
					else if (hasilJT == 2)
					{
                        jenisTiketList = konserPilihan->REG;
                        strcpy(jenisTiketStr, "REG");
                        system("cls");
                        printf("=====================================================================\n");
                        printf("|                          List User REG                            |\n");
                        printf("=====================================================================\n");
                        printUser(jenisTiketList->front);
                    }
					else
					{
                        system("cls");
                    }
                    // Jika jenis tiket telah dipilih
                    if (hasilJT == 1 || hasilJT == 2) 
					{
                        // Jika ada user dalam jenis tiket tersebut
                        if (jenisTiketList->front != NULL) 
						{
                            // Tampilkan opsi untuk melakukan tindakan pada user
                            printf("\n1. Lihat Detail User\n2. Hapus User\n3. Kehadiran User (Ketika konser berjalan)\n0. Kembali\nPilihan: ");
                            scanf("%d", &pilihan);
                            switch (pilihan)
							{
                                case 1:
                                    // Menampilkan detail user berdasarkan indeks
                                    printf("\nIndeks User yang akan dicari: ");
                                    scanf("%d", &indeks);
                                    lihatDetailUser(jenisTiketList, konserPilihan, hasilJT, indeks - 1);
                                    break;
                                case 2:
                                    // Menghapus user berdasarkan indeks
                                    printf("\nIndeks User yang akan dihapus: ");
                                    scanf("%d", &indeks);
                                    pop(konserPilihan, jenisTiketList, indeks - 1);
                                    break;
                                case 3:
                                    // Mengurangi kehadiran user ketika konser berjalan
                                    printf("\nIndeks User yang akan dikurangi: ");
                                    scanf("%d", &indeks);
                                    printf("Jumlah pengurangan: ");
                                    scanf("%d", &jumlahKurang);
                                    kehadiranUser(jenisTiketList, indeks - 1, jumlahKurang);
                                    break;
                                case 0:
                                    // Kembali ke menu sebelumnya
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
                            // Jika tidak ada user dalam jenis tiket tersebut
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
    // Deklarasi variabel
    FILE *file;
    int idUser, frekuensi;
    char nama[50];

    // Inisialisasi file
    file = fopen("history_kehadiran.bin", "rb");
    
    // Cek apakah file sudah terbuat
    if (file == NULL) 
	{
        printf("Belum ada history kehadiran.\n");
        return;
    }

    // Tampilkan history kehadiran
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

    // Tutup file
    fclose(file);

    printf("\n");
    system("pause");
    system("cls");
}

void rekursifHapusUser(addressNode *node) 
{
    // Awal rekursi
    if (*node == NULL)
        return;

    // Rekursif untuk hapus node berikutnya
    rekursifHapusUser(&(*node)->next);

    // Hapus node saat ini
    free(*node);
    *node = NULL;
}

void popKonserById(addressRoot root, int idKonser) 
{
    // Deklarasi variabel
    addressKonser prev, curr;

    // Inisialisasi variabel
    prev = NULL;
    curr = root->down;

    // Cari konser dengan id konser yang diberikan
    while (curr != NULL && curr->nomorKonser != idKonser) 
	{
        prev = curr; // Konser saat ini menjadi konser sebelumnya
        curr = curr->next; // Lanjut ke konser selanjutnya dalam linked list
    }

    // Jika konser dengan id yang diberikan ditemukan
    if (curr != NULL) 
	{
        // Hapus semua user dalam daftar VIP dan REG pada konser saat ini
        rekursifHapusUser(&curr->VIP->front);
        rekursifHapusUser(&curr->REG->front);

        // Hapus konser dari struktur root
        if (prev == NULL) // Jika konser yang dihapus adalah konser pertama dalam root
		{
            root->down = curr->next; // Atur list konser pertama ke konser berikutnya
        } 
		else 
		{
            prev->next = curr->next; // Hapus konser saat ini dari konser sebelumnya
        }

        // Bebaskan memori yang dialokasikan untuk konser saat ini
        free(curr);
        curr = NULL;
    }
}
