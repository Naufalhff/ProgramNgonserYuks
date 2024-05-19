#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Naomi.h"
#include "Ariq.h"
#include "Naufal.h"
#include "Rasyid.h"
#include "Yudhis.h"
#include "Roy.h"

void readAndValidateData(const char* filename) {
    FILE* file = fopen(filename, "r");
    FILE* file2 = fopen("temp2.txt", "w");
    if (!file) {
        perror("Gagal membuka file");
        return;
    }

    int id, quantity, validation;
    char name[50], event[50], category[10];
    int phone;
    float price, paid;

    while (fscanf(file, "%d %s %d %s %d %s %f %f %d", &id, name, &phone, event, &quantity, category, &price, &paid, &validation) != EOF) {
        int validation = (paid < price) ? 1 : (paid == price) ? 0 : 0;
        fprintf(file2, "%d %s %d %s %d %s %.2f %.2f %d\n", id, name, phone, event, quantity, category, price, paid, validation);
    }
	
    fclose(file);
    fclose(file2);
    remove(filename);
    rename("temp2.txt", filename);
}


void enqueue(addressKonser first, int idKonser, char *category, int id, char *name, int quantity)
{
    addressKonser trav;
    addressUser jenisList;
    addressNode nodeBaru;
    int i;
    
    trav = cariKonserById(first, idKonser);
    if (trav == NULL)
    {
        printf("Konser dengan ID '%d' tidak ditemukan.\n", idKonser);
        return;
    }
    
    if (strcmp(category, "VIP") == 0)
    {
        jenisList = trav->VIP;
    }
    else if (strcmp(category, "REG") == 0)
    {
        jenisList = trav->REG;
    }
    else
    {
        printf("Jenis tiket '%s' tidak ditemukan.\n", category);
        return;
    }
    
    if (jenisList->jumlah + quantity > jenisList->kapasitas)
    {
        printf("Mohon maaf, untuk tiket '%s' hanya tersisa %d tiket saja.\n", category, (jenisList->kapasitas - jenisList->jumlah));
        return;
    }
    
    nodeBaru = buatNodeUser(id, name, quantity);

    if (jenisList->rear == NULL)
    {
        jenisList->front = nodeBaru;
    }
    else
    {
        jenisList->rear->next = nodeBaru;
    }
    jenisList->rear = nodeBaru;

    for (i = 0; i < quantity; i++)
    {
        jenisList->jumlah++;
    }
}

int main() {
    readAndValidateData("datauser.txt");

    return 0;
}
