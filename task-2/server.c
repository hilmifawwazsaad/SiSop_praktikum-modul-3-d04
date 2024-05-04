#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define MAX_CLIENTS 5
#define MAX_USERNAME_LENGTH 50
#define MAX_CONTAINER_NAME_LENGTH 50
#define MAX_IMAGE_LENGTH 100
#define MAX_COMMAND_LENGTH 100
#define MAX_VOLUME_LENGTH 100

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char container_name[MAX_CONTAINER_NAME_LENGTH];
    char image[MAX_IMAGE_LENGTH];
    char command[MAX_COMMAND_LENGTH];
    char volume[MAX_VOLUME_LENGTH];
    int active;
} ClientRequest;

int main() {
    key_t key = ftok("server", 65);
    int shmid = shmget(key, MAX_CLIENTS * sizeof(ClientRequest), 0666|IPC_CREAT);
    ClientRequest *client_requests = (ClientRequest*) shmat(shmid, (void*)0, 0);

    printf("Server is running...\n");

    int num_clients = 0;
    while (num_clients < MAX_CLIENTS) {
        printf("Waiting for clients to connect...\n");

        while (num_clients == 0) {
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_requests[i].active == 1) {
                    num_clients++;
                }
            }
        }

        printf("All clients connected.\n");

        // Wait for all clients to send their requests
        int all_requests_received = 0;
        while (!all_requests_received) {
            all_requests_received = 1;
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_requests[i].active == 1) {
                    if (client_requests[i].container_name[0] == '\0') {
                        all_requests_received = 0;
                        break;
                    }
                }
            }
        }

        printf("All requests received. Generating docker-compose file...\n");

        // Generate docker-compose file
        FILE *compose_file = fopen("docker-compose.yml", "w");
        fprintf(compose_file, "version: '3'\nservices:\n");

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_requests[i].active == 1) {
                fprintf(compose_file, "  %s:\n", client_requests[i].container_name);
                fprintf(compose_file, "    image: %s\n", client_requests[i].image);
                fprintf(compose_file, "    command: %s\n", client_requests[i].command);
                fprintf(compose_file, "    volumes:\n");
                fprintf(compose_file, "      - %s\n", client_requests[i].volume);
            }
        }

        fclose(compose_file);

        printf("Docker-compose file generated.\n");

        // Run docker-compose
        system("docker-compose up -d");

        printf("All services are running.\n");

        // Wait for all clients to send new requests
        printf("Waiting for new requests...\n");
        int all_requests_reset = 0;
        while (!all_requests_reset) {
            all_requests_reset = 1;
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_requests[i].active == 1) {
                    memset(&client_requests[i], 0, sizeof(ClientRequest));
                    all_requests_reset = 0;
                }
            }
        }

        printf("All requests reset.\n");
        num_clients = 0;
    }

    shmdt(client_requests);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
