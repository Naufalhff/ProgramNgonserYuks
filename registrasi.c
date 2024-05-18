#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NAOMI.h"

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(Queue* q) {
    return (q->front == NULL);
}

void enqueue(Queue* q, Person p) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->info = p;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void encryptDecrypt(char *input, char *output) {
    int i;
    char key = 'K'; // Key untuk enkripsi/dekripsi sederhana
    for (i = 0; input[i] != '\0'; i++) {
        output[i] = input[i] ^ key;
    }
    output[i] = '\0';
}

Person dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty, cannot dequeue.\n");
        exit(EXIT_FAILURE);
    }
    QueueNode* temp = q->front;
    Person p = temp->info;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return p;
}

void registrasi(Queue* q) {
    Person newPerson;
    char encryptedPassword[100];

    printf("Masukkan Username: ");
    scanf("%s", newPerson.username);
    printf("Masukkan Password: ");
    scanf("%s", newPerson.password);

    // Enkripsi password sebelum disimpan
    encryptDecrypt(newPerson.password, encryptedPassword);
    strcpy(newPerson.password, encryptedPassword);

    enqueue(q, newPerson);
}

void simpanDataRegistrasi(Queue* q) {
    FILE *file = fopen("registrasi.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
    QueueNode* temp = q->front;
    while (temp != NULL) {
        fprintf(file, "%s %s\n", temp->info.username, temp->info.password);
        temp = temp->next;
    }
    fclose(file);
}

void bacaDataRegistrasi(Queue* q) {
    FILE *file = fopen("registrasi.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
    Person tempPerson;
    while (fscanf(file, "%s %s", tempPerson.username, tempPerson.password) != EOF) {
        enqueue(q, tempPerson);
    }
    fclose(file);
}

void displayQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    QueueNode* temp = q->front;
    while (temp != NULL) {
        printf("Username: %s\n", temp->info.username);
        temp = temp->next;
    }
}

// Fungsi untuk membersihkan input buffer
void clearInputBuffer() {
    while (getchar() != '\n');
}

// Fungsi untuk menampilkan halaman khusus registrasi
void tampilan_halaman_registrasi() {
    printf("Halaman Registrasi:\n");
    // Tampilkan informasi atau instruksi untuk registrasi di sini
}

