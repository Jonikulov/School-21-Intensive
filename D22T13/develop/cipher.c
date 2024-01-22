#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1024

void read_out_file(char *filepath);
void write_end_file(char *filepath);
void caesar_cipher_files(char *folder, char *file_ext, int key);  // key: 7

int main() {
    int choice, key;
    char file_path[MAX_LEN] = "";

    while (1) {
        if (scanf("%d", &choice) != 1) {
            printf("n/a\n");
            while (getchar() != '\n')
                ;  // Clear the input buffer
            continue;
        }

        switch (choice) {
            case -1:
                return 0;
            case 1:
                scanf("%1023s", file_path);
                read_out_file(file_path);
                break;
            case 2:
                write_end_file(file_path);
                break;
            case 3:
                if (scanf("%d", &key) != 1) {
                    printf("n/a");
                    break;
                }
                caesar_cipher_files("ai_modules", ".c", key);
                break;
            default:
                printf("n/a\n");
                break;
        }
    }

    return 0;
}

void read_out_file(char *filepath) {
    FILE *fp = fopen(filepath, "r");
    // Check if the file exists
    if (fp == NULL) {
        printf("n/a\n");
        return;
    }

    // Check if the file is empty
    int ch = fgetc(fp);
    if (ch == EOF) {
        printf("n/a\n");
        fclose(fp);
        return;
    }

    // Print file content
    while (ch != EOF) {
        putchar(ch);
        ch = fgetc(fp);
    }
    printf("\n");

    fclose(fp);
}

void write_end_file(char *filepath) {
    char add_str[MAX_LEN] = "";
    FILE *fp;
    int ch, idx = 0;

    getchar();  // Skip the initial newline
    while ((ch = getchar()) != '\n') {
        add_str[idx++] = ch;
    }

    // Check if the file exists
    fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("n/a\n");
        return;
    }
    fclose(fp);

    fp = fopen(filepath, "a+");
    fputs(add_str, fp);

    // Print file content
    rewind(fp);  // Move the file pointer to beginning
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    printf("\n");

    fclose(fp);
}

void caesar_cipher_files(char *folder, char *file_ext, int key) {
    DIR *dir = opendir(folder);
    struct dirent *entry;
    FILE *fp;
    char *file_data = NULL, filepath[MAX_LEN], ch;
    int file_size = 0;

    if (dir == NULL) {
        printf("Error opening folder.\n");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char *ext = strrchr(entry->d_name, '.');
        if (strcmp(file_ext, ext) == 0) {
            sprintf(filepath, "%s/%s", folder, entry->d_name);
            fp = fopen(filepath, "r");
            while ((ch = fgetc(fp)) != EOF) {
                file_data = realloc(file_data, file_size + 1);
                file_data[file_size++] = ch;
            }
            file_data = realloc(file_data, file_size + 1);
            file_data[file_size] = '\0';
            fclose(fp);

            fp = fopen(filepath, "w");
            for (int i = 0; file_data[i] != '\0'; i++) {
                // Caesar cipher. ASCII decimal -> [33 - 126], 94 characters
                if ((int)file_data[i] >= 33 && (int)file_data[i] <= 126) {
                    // Encrypt
                    char enc_v = ((int)file_data[i] - 33 + key) % 94 + 33;
                    // Decrypt
                    // char enc_v = ((int) file_data[i] - 33 - key + 94) % 94 + 33;
                    fputc(enc_v, fp);
                } else {
                    fputc(file_data[i], fp);
                }
            }
            fclose(fp);
        }

        file_size = 0;
        free(file_data);
        file_data = NULL;
    }

    free(file_data);
    closedir(dir);
}