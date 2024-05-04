#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

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
    int shmid = shmget(key, 5 * sizeof(ClientRequest), 0666|IPC_CREAT);
    ClientRequest *client_requests = (ClientRequest*) shmat(shmid, (void*)0, 0);

    char username[MAX_USERNAME_LENGTH];
    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;

    int client_index = -1;
    for (int i = 0; i < 5; i++) {
        if (client_requests[i].active == 0) {
            client_index = i;
            break;
        }
    }

    if (client_index == -1) {
        printf("Server is busy. Please try again later.\n");
        shmdt(client_requests);
        return 0;
    }

    strcpy(client_requests[client_index].username, username);
    client_requests[client_index].active = 1;

    printf("Welcome, %s! Please provide the service details:\n", username);

    printf("Container Name: ");
    fgets(client_requests[client_index].container_name, MAX_CONTAINER_NAME_LENGTH, stdin);
    client_requests[client_index].container_name[strcspn(client_requests[client_index].container_name, "\n")] = 0;

    printf("Image: ");
    fgets(client_requests[client_index].image, MAX_IMAGE_LENGTH, stdin);
    client_requests[client_index].image[strcspn(client_requests[client_index].image, "\n")] = 0;

    printf("Command: ");
    fgets(client_requests[client_index].command, MAX_COMMAND_LENGTH, stdin);
    client_requests[client_index].command[strcspn(client_requests[client_index].command, "\n")] = 0;

    printf("Volume: ");
    fgets(client_requests[client_index].volume, MAX_VOLUME_LENGTH, stdin);
    client_requests[client_index].volume[strcspn(client_requests[client_index].volume, "\n")] = 0;

    shmdt(client_requests);
    return 0;
}
