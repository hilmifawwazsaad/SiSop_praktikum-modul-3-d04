#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define MAX 1000

char message[MAX][MAX]; // array untuk menyimpan kata-kata
int message_length = 0; // panjang pesan

void *write(void *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Gagal membuka file untuk menulis");
        pthread_exit(NULL);
    }
    // menulis setiap kata ke dalam file
    for (int i = 0; i < message_length; i++) {
        fprintf(file, "%s ", message[i]);
    }

    fclose(file);
    printf("Pesan berhasil ditulis ke dalam file '%s'.\n", (char *)filename);
    pthread_exit(NULL);
}

void *read(void *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Gagal membuka file untuk dibaca");
        pthread_exit(NULL);
    }

    char word[MAX];
    printf("Pesan yang ditulis:\n");
    while (fscanf(file, "%s", word) != EOF) {
        printf("%s ", word); // membaca kata-kata dari file
    }
    printf("\n");

    fclose(file);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t write_thread, read_thread;

    if (argc < 2) {
        printf("Usage:\n");
        printf("To write: ./chat write <message> <filename>\n");
        printf("To read: ./chat read <filename>\n");
        return 1;
    } else if (strcmp(argv[1], "write") == 0) {
        // menyalin argumen ke dalam pesan
        for (int i = 2; i < argc - 1; i++) {
            strcpy(message[message_length], argv[i]);
            message_length++;
        }
        if (pthread_create(&write_thread, NULL, write, (void *)argv[argc - 1])) {
            perror("Gagal membuat thread");
            return 1;
        }
        pthread_join(write_thread, NULL); // menunggu thread selesai
    } else if (strcmp(argv[1], "read") == 0) {
        if (pthread_create(&read_thread, NULL, read, (void *)argv[2])) {
            perror("Gagal membuat thread");
            return 1;
        }
        pthread_join(read_thread, NULL); // menunggu thread selesai
    } else {
        printf("Invalid argumen\n");
        return 1;
    }

    return 0;
}
