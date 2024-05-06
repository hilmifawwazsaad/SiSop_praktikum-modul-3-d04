// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <string.h>
// #define MAX 1000

// char message[MAX][MAX]; // array untuk menyimpan kata-kata
// int message_length = 0; // panjang pesan

// void *write(void *filename) {
//     FILE *file = fopen(filename, "w");
//     if (file == NULL) {
//         perror("Gagal membuka file untuk menulis");
//         pthread_exit(NULL);
//     }
//     // menulis setiap kata ke dalam file
//     for (int i = 0; i < message_length; i++) {
//         fprintf(file, "%s ", message[i]);
//     }

//     fclose(file);
//     printf("Pesan berhasil ditulis ke dalam file '%s'.\n", (char *)filename);
//     pthread_exit(NULL);
// }

// void *read(void *filename) {
//     FILE *file = fopen(filename, "r");
//     if (file == NULL) {
//         perror("Gagal membuka file untuk dibaca");
//         pthread_exit(NULL);
//     }

//     char word[MAX];
//     printf("Pesan yang ditulis:\n");
//     while (fscanf(file, "%s", word) != EOF) {
//         printf("%s ", word); // membaca kata-kata dari file
//     }
//     printf("\n");

//     fclose(file);
//     pthread_exit(NULL);
// }

// int main(int argc, char *argv[]) {
//     pthread_t write_thread, read_thread;

//     if (argc < 2) {
//         printf("Usage:\n");
//         printf("To write: ./chat write <message> <filename>\n");
//         printf("To read: ./chat read <filename>\n");
//         return 1;
//     } else if (strcmp(argv[1], "write") == 0) {
//         // menyalin argumen ke dalam pesan
//         for (int i = 2; i < argc - 1; i++) {
//             strcpy(message[message_length], argv[i]);
//             message_length++;
//         }
//         if (pthread_create(&write_thread, NULL, write, (void *)argv[argc - 1])) {
//             perror("Gagal membuat thread");
//             return 1;
//         }
//         pthread_join(write_thread, NULL); // menunggu thread selesai
//     } else if (strcmp(argv[1], "read") == 0) {
//         if (pthread_create(&read_thread, NULL, read, (void *)argv[2])) {
//             perror("Gagal membuat thread");
//             return 1;
//         }
//         pthread_join(read_thread, NULL); // menunggu thread selesai
//     } else {
//         printf("Invalid argumen\n");
//         return 1;
//     }

//     return 0;
// }

// POIN C DAN D
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

// Struktur untuk data yang dibutuhkan setiap thread
typedef struct {
    char *word;  // Kata untuk ditulis
    FILE *fp;    // File pointer untuk file output
    int position; // Posisi kata dalam argumen
} ThreadData;

// Fungsi yang akan dijalankan oleh setiap thread untuk menulis kata
void *write_word(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    fprintf(data->fp, "%s ", data->word);  // Tulis kata ke file
    return NULL;
}

// Fungsi untuk menulis pesan ke dalam file dengan menggunakan multiple threads
void write_message(char **words, int count, char *filename) {
    pthread_t threads[count];
    ThreadData thread_data[count];
    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < count; i++) {
        thread_data[i].word = words[i];
        thread_data[i].fp = fp;
        thread_data[i].position = i;
        pthread_create(&threads[i], NULL, write_word, &thread_data[i]);
        sleep(1);  // Tunggu 1 detik sebelum membuat thread baru
    }

    // Tunggu semua thread selesai
    for (int i = 0; i < count; i++) {
        pthread_join(threads[i], NULL);
    }

    fclose(fp);
}

// Fungsi untuk membaca pesan dari file
void read_message(char *filename) {
    char buffer[1024];
    FILE *fp = fopen(filename, "r");
    
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <write/read> [<message>] [<target_container>]\n", argv[0]);
        return 1;
    }
    FILE *fp;

    if (strcmp(argv[1], "write") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s write <message> <target_container>\n", argv[0]);
            return 1;
        }
        char *words[argc - 3];
        int word_count = argc - 3;
        for (int i = 0; i < word_count; i++) {
            words[i] = argv[i + 2];
        }

        // Membuat nama file dari nama kontainer tujuan
        char filename[100];
        snprintf(filename, sizeof(filename), "%s_messagebox.txt", argv[argc - 1]);
        //printf("nama file : %s\n", filename);
        write_message(words, word_count, filename);
        //printf("nama file : %s\n", filename);
        fp = fopen(filename, "a");
        if (fp == NULL) {
            perror("Error opening file");
            return 1;
        }
        //printf("nama file : %s\n", filename);
        
        fprintf(fp, "from %s\n", getenv("SENDER")); 
        //printf("nama file : %s\n", filename);
        printf("Pesan berhasil ditulis ke %s\n", argv[argc - 1]);
        //printf("nama file : %s\n", filename);
    } else if (strcmp(argv[1], "read") == 0) {
        char filename[100];
        snprintf(filename, sizeof(filename), "%s_messagebox.txt", getenv("SENDER"));
        read_message(filename);
    } else {
        fprintf(stderr, "Invalid command\n");
        return 1;
    }

    return 0;
}
