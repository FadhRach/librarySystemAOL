#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

// Typedef untuk struct User
typedef struct {
    char nim[20];
    char nama[50];
    char password[20];
} User;

// Fungsi untuk menulis data user ke file
void writeUser(User users[], int count) {
    FILE *f = fopen("data.txt", "a"); // Append mode
    if (f == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s#%s#%s\n", users[i].nim, users[i].nama, users[i].password);
    }
    fclose(f);
}

// Fungsi untuk membaca semua user dari file
void readUsers() {
    User user;
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        printf("File tidak ditemukan!\n");
        return;
    }
    printf("\n===== Daftar User =====\n");
    while (fscanf(f, "%[^#]#%[^#]#%[^\n]\n", user.nim, user.nama, user.password) != EOF) {
        printf("NIM: %s, Nama: %s, Password: %s\n", user.nim, user.nama, user.password);
    }
    fclose(f);
}

// Fungsi untuk mengecek apakah NIM sudah terdaftar
int cekNIM(char *nim) {
    User user;
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        return 0; // File belum ada, NIM pasti belum terdaftar
    }
    while (fscanf(f, "%[^#]#%[^#]#%[^\n]\n", user.nim, user.nama, user.password) != EOF) {
        if (strcmp(user.nim, nim) == 0) {
            fclose(f);
            return 1; // NIM ditemukan
        }
    }
    fclose(f);
    return 0; // NIM tidak ditemukan
}

// Fungsi untuk registrasi user baru
void registrasi() {
    User newUser;
    printf("\n===== Registrasi =====\n");
    printf("Masukkan NIM: ");
    scanf("%s", newUser.nim);

    // Cek apakah NIM sudah ada
    if (cekNIM(newUser.nim)) {
        printf("NIM sudah terdaftar!\n");
        return;
    }

    printf("Masukkan Nama: ");
    scanf(" %[^\n]", newUser.nama);
    printf("Masukkan Password: ");
    scanf("%s", newUser.password);

    // Simpan data ke file menggunakan writeUser
    User tempUser[1] = {newUser}; // Menyimpan satu user sementara
    writeUser(tempUser, 1);
    printf("Registrasi berhasil!\n");
}

// Fungsi untuk login
void login() {
    User user;
    char nim[20], password[20];
    int status = 0;

    printf("\n===== Login =====\n");
    printf("Masukkan NIM: ");
    scanf("%s", nim);
    printf("Masukkan Password: ");
    scanf("%s", password);

    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        printf("Belum ada data terdaftar!\n");
        return;
    }

    while (fscanf(f, "%[^#]#%[^#]#%[^\n]\n", user.nim, user.nama, user.password) != EOF) {
        if (strcmp(user.nim, nim) == 0 && strcmp(user.password, password) == 0) {
            status = 1;
            break;
        }
    }
    fclose(f);

    if (status) {
        printf("Login berhasil! Selamat datang, %s!\n", user.nama);
    } else {
        printf("Login gagal! NIM atau password salah.\n");
    }
}

int main() {
    int pilihan;
    while (1) {
        printf("\n===== Menu =====\n");
        printf("1. Login\n");
        printf("2. Registrasi\n");
        printf("3. Tampilkan Semua User\n");
        printf("4. Keluar\n");
        printf("Pilih menu (1-4): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                login();
                break;
            case 2:
                registrasi();
                break;
            case 3:
                readUsers();
                break;
            case 4:
                printf("Keluar dari program.\n");
                exit(0);
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
    return 0;
}
