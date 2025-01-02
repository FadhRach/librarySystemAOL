#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <windows.h>
#include <time.h>

#if _WIN32
    #include <conio.h>
    #define CLEAR_SCREEN "cls"
#else
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
    char getch() {
        system("stty raw -echo");
        char ch = getchar();
        system("stty cooked echo");
        return ch;
    }
#endif

//MODEL-----------------------------------------------------------------
typedef struct {
    char nim[20];
    char nama[50];
    char password[20];
} User;

typedef struct {
    char idBuku[10];
    char judul[100];
    char jenis[50];
    int thnTerbit;
} Buku;

//COMPONENT-------------------------------------------------------------
void clearScreen() {
    system(CLEAR_SCREEN);
}

void headingLibrary() {
	printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("  ______   ______  __    __  ______  ________   ______         __       ______  _______   _______    ______   _______ __      __\n");
	printf(" /      \\ |      \\|  \\  |  \\|      \\|        \\ /      \\       |  \\     |      \\|       \\ |       \\  /      \\ |       \\  \\    /  \\\n");
	printf("|  $$$$$$\\ \\$$$$$$| $$  | $$ \\$$$$$$| $$$$$$$$|  $$$$$$\\      | $$      \\$$$$$$| $$$$$$$\\| $$$$$$$\\|  $$$$$$\\| $$$$$$$\\$$\\  /  $$\n");
	printf("| $$___\\$$  | $$   \\$$\\/  $$  | $$  | $$__    | $$___\\$$      | $$       | $$  | $$__/ $$| $$__| $$| $$__| $$| $$__| $$\\$$\\/  $$\n");
	printf(" \\$$    \\   | $$    >$$  $$   | $$  | $$  \\    \\$$    \\       | $$       | $$  | $$    $$| $$    $$| $$    $$| $$    $$ \\$$  $$\n");
    printf(" _\\$$$$$$\\  | $$   /  $$$$\\   | $$  | $$$$$    _\\$$$$$$$\\     | $$       | $$  | $$$$$$$\\| $$$$$$$\\| $$$$$$$$| $$$$$$$\\  \\$$$$\n");
	printf("|  \\__| $$ _| $$_ |  $$ \\$$\\ _| $$_ | $$_____ |  \\__| $$      | $$_____ _| $$_ | $$__/ $$| $$  | $$| $$  | $$| $$  | $$  | $$\n");
	printf(" \\$$    $$|   $$ \\| $$  | $$|   $$ \\| $$     \\ \\$$    $$      | $$     \\   $$ \\| $$    $$| $$  | $$| $$  | $$| $$  | $$  | $$\n");
    printf("  \\$$$$$$  \\$$$$$$ \\$$   \\$$ \\$$$$$$ \\$$$$$$$$  \\$$$$$$        \\$$$$$$$$\\$$$$$$ \\$$$$$$$  \\$$   \\$$ \\$$   \\$$ \\$$   \\$$   \\$$\n");
	printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
}

void ReadAllBuku(Buku buku[], int count) {
    printf("\n+------------+------------------------------------------+------------------------------+----------------+\n");
    printf("| ID Buku    | Judul                                    | Jenis                        | Tahun Terbit   |\n");
    printf("+------------+------------------------------------------+------------------------------+----------------+\n");

    for (int i = 0; i < count; i++) {
        printf("| %-10s | %-40s | %-28s | %-14d |\n",
               buku[i].idBuku, buku[i].judul, buku[i].jenis, buku[i].thnTerbit);
    }

    printf("+------------+------------------------------------------+------------------------------+----------------+\n");
}

void SortingAscendingBuku(Buku buku[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcasecmp(buku[j].judul, buku[j + 1].judul) > 0) {
                Buku temp = buku[j];
                buku[j] = buku[j + 1];
                buku[j + 1] = temp;
            }
        }
    }
    printf("\nBuku berhasil diurutkan secara ascending berdasarkan judul (tanpa membedakan case)!\n");
}

void SortingDescendingBuku(Buku buku[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcasecmp(buku[j].judul, buku[j + 1].judul) < 0) {
                Buku temp = buku[j];
                buku[j] = buku[j + 1];
                buku[j + 1] = temp;
            }
        }
    }
    printf("\nBuku berhasil diurutkan secara descending berdasarkan judul (tanpa membedakan case)!\n");
}

void cariBuku(Buku buku[], int count) {
    char cariJudul[100];
    int ditemukan = 0;

    printf("\nMasukkan judul buku yang ingin dicari: ");
    scanf(" %[^\n]", cariJudul);

    printf("\n+------------+------------------------------------------+------------------------------+----------------+\n");
    printf("| ID Buku    | Judul                                    | Jenis                        | Tahun Terbit   |\n");
    printf("+------------+------------------------------------------+------------------------------+----------------+\n");

    for (int i = 0; i < count; i++) {
        if (strstr(buku[i].judul, cariJudul)) {
            printf("| %-10s | %-40s | %-28s | %-14d |\n",
                   buku[i].idBuku, buku[i].judul, buku[i].jenis, buku[i].thnTerbit);
            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("| %-90s |\n", "Tidak ada buku dengan judul yang dicari.");
    }

    printf("+------------+------------------------------------------+------------------------------+----------------+\n");
    getchar();
}

int cekIdBuku(const char *idBuku, const char *namaFile) {
    FILE *file = fopen(namaFile, "r");
    if (!file) {
        printf("Gagal membuka file %s!\n", namaFile);
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char existingId[10];
        sscanf(line, "%s", existingId);
        if (strcmp(existingId, idBuku) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0; // ID belum ada di dalam file
}

void generateIdBuku(char *idBuku, const char *namaFile) {
    srand((unsigned int)time(NULL));

    int isUnique = 0;
    while (!isUnique) {
        int randomNum = rand() % 1000;
        sprintf(idBuku, "BK%03d", randomNum);

        if (!cekIdBuku(idBuku, namaFile)) {
            isUnique = 1;
        }
    }
}

void writeUser(User users[], int count) {
    FILE *f = fopen("data.txt", "a");
    if (f == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s#%s#%s\n", users[i].nim, users[i].nama, users[i].password);
    }
    fclose(f);
}

//PAGE------------------------------------------------------------------
void tambahBuku() {
    printf("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
    FILE *file = fopen("buku.txt", "a");
    if (!file) {
        printf("Gagal membuka file buku.txt!\n");
        return;
    }

    char judul[100], jenis[50];
    int thnTerbit;
    char idBuku[10];

    generateIdBuku(idBuku, "buku.txt");

    printf("Tambah Buku Baru\n");
    printf("Judul Buku: ");
    scanf(" %[^\n]", judul);
    printf("Jenis Buku: ");
    scanf(" %[^\n]", jenis);
    printf("Tahun Terbit: ");
    scanf("%d", &thnTerbit);

    fprintf(file, "%s#%s#%s#%d\n", idBuku, judul, jenis, thnTerbit);
    fclose(file);

    printf("Buku berhasil ditambahkan dengan ID %s\n", idBuku);
    printf("Tekan Enter untuk kembali...");
    getchar(); getchar();
}

void lihatBuku() {
    FILE *file = fopen("buku.txt", "r");
    if (!file) {
        printf("Tidak ada data buku tersedia!\n");
        return;
    }

    Buku buku[100];
    int count = 0;

    while (fscanf(file, "%[^#]#%[^#]#%[^#]#%d\n", buku[count].idBuku, buku[count].judul, buku[count].jenis, &buku[count].thnTerbit) != EOF) {
        count++;
    }
    fclose(file);

    int selection = 0;
    char key;

    while (1) {
        clearScreen();
        headingLibrary();
        printf("Lihat Buku:\n");
        printf("%s Urutkan Buku (Ascending)\n", selection == 0 ? "> " : "  ");
        printf("%s Urutkan Buku (Descending)\n", selection == 1 ? "> " : "  ");
        printf("%s Cari Buku Berdasarkan Judul\n", selection == 2 ? "> " : "  ");
        printf("%s Kembali\n", selection == 3 ? "> " : "  ");

        key = getch();

        if (key == 'W' || key == 'w') {
            selection--;
        } else if (key == 'S' || key == 's') {
            selection++;
        } else if (key == 13) {
            break;
        }

        if (selection < 0) selection = 0;
        if (selection > 3) selection = 3;
    }

    switch (selection) {
        case 0:
            SortingAscendingBuku(buku, count);
            ReadAllBuku(buku, count);
            break;

        case 1:
            SortingDescendingBuku(buku, count);
            ReadAllBuku(buku, count);
            break;

        case 2:
            cariBuku(buku, count);
            break;

        case 3:
            return;
    }

    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
    lihatBuku();
}

void editBuku() {
    printf("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
    FILE *file = fopen("buku.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (!file || !tempFile) {
        printf("Gagal membuka file buku.txt!\n");
        return;
    }

    char idBuku[10], judul[100], jenis[50];
    int thnTerbit;
    char targetID[10];
    int found = 0;

    printf("Masukkan ID Buku yang ingin diubah: ");
    scanf("%s", targetID);

    while (fscanf(file, "%[^#]#%[^#]#%[^#]#%d\n", idBuku, judul, jenis, &thnTerbit) != EOF) {
        if (strcmp(idBuku, targetID) == 0) {
            found = 1;
            printf("Judul Buku Baru: ");
            scanf(" %[^\n]", judul);
            printf("Jenis Buku Baru: ");
            scanf(" %[^\n]", jenis);
            printf("Tahun Terbit Baru: ");
            scanf("%d", &thnTerbit);
        }
        fprintf(tempFile, "%s#%s#%s#%d\n", idBuku, judul, jenis, thnTerbit);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("buku.txt");
        rename("temp.txt", "buku.txt");
        printf("Data buku berhasil diubah!\n");
    } else {
        remove("temp.txt");
        printf("Buku dengan ID %s tidak ditemukan!\n", targetID);
    }
    printf("Tekan Enter untuk kembali...");
    getch();
}

void hapusBuku() {
    printf("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
    FILE *file = fopen("buku.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (!file || !tempFile) {
        printf("Gagal membuka file buku.txt!\n");
        return;
    }

    char idBuku[10], judul[100], jenis[50];
    int thnTerbit;
    char targetID[10];
    int found = 0;

    printf("Masukkan ID Buku yang ingin dihapus: ");
    scanf("%s", targetID);

    while (fscanf(file, "%[^#]#%[^#]#%[^#]#%d\n", idBuku, judul, jenis, &thnTerbit) != EOF) {
        if (strcmp(idBuku, targetID) != 0) {
            fprintf(tempFile, "%s#%s#%s#%d\n", idBuku, judul, jenis, thnTerbit);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("buku.txt");
        rename("temp.txt", "buku.txt");
        printf("Buku berhasil dihapus!\n");
    } else {
        remove("temp.txt");
        printf("Buku dengan ID %s tidak ditemukan!\n", targetID);
    }
    printf("Tekan Enter untuk kembali...");
    getch();
}

void checkBuku() {
    int selection = 0;
    char key;

    while (1) {
        clearScreen();
        headingLibrary();
        printf("Cek Buku - Pilih Operasi\n");
        printf("%s Tambah Buku\n", selection == 0 ? "> " : "  ");
        printf("%s Lihat Buku\n", selection == 1 ? "> " : "  ");
        printf("%s Edit Buku\n", selection == 2 ? "> " : "  ");
        printf("%s Hapus Buku\n", selection == 3 ? "> " : "  ");
        printf("%s Kembali\n", selection == 4 ? "> " : "  ");

        key = getch();

        if (key == 'W' || key == 'w') {
            selection--;
        } else if (key == 'S' || key == 's') {
            selection++;
        } else if (key == 13) {
            switch (selection) {
                case 0:
                    tambahBuku();
                    break;
                case 1:
                    lihatBuku();
                    break;
                case 2:
                    editBuku();
                    break;
                case 3:
                    hapusBuku();
                    break;
                case 4:
                    return;
            }
        }

        if (selection < 0) selection = 0;
        if (selection > 4) selection = 4;
    }
}

void mainMenuUser(char *nama) {
    int selection = 0;
    char key;

    while (1) {
        clearScreen();
        headingLibrary();
        printf("Selamat datang \"%s\" di perpustakaan ada yang bisa dibantu?\n", nama);

        printf("%s Lihat Buku\n", selection == 0 ? "> " : "  ");
        printf("%s Lihat Peminjaman Buku\n", selection == 1 ? "> " : "  ");
        printf("%s Meminjam Buku\n", selection == 2 ? "> " : "  ");
        printf("%s Mengembalikan Buku\n", selection == 3 ? "> " : "  ");
        printf("%s Kembali\n", selection == 4 ? "> " : "  ");

        key = getch();

        if (key == 'W' || key == 'w') {
            selection--;
        } else if (key == 'S' || key == 's') {
            selection++;
        } else if (key == 13) {
            break;
        }

        if (selection < 0) selection = 0;
        if (selection > 4) selection = 4;
    }

    switch (selection) {
        case 0:
            lihatBuku();
            break;
        case 1:
            // LihatPinjamBuku();
            break;
        case 2:
            // PinjamBuku();
            break;
        case 3:
            // MengembalikanBuku();
            break;
        case 4:
            return;
    }

    mainMenuUser(nama);
}

void mainMenuAdmin(char *nama) {
    int selection = 0;
    char key;

    while (1) {
        clearScreen();
        headingLibrary();
	    printf("Selamat datang \"%s\" di perpustakaan ada yang bisa dibantu?\n", nama);

        printf("%s Check Buku\n", selection == 0 ? "> " : "  ");
        printf("%s Check Peminjaman Buku\n", selection == 1 ? "> " : "  ");
        printf("%s Check User\n", selection == 2 ? "> " : "  ");
        printf("%s Kembali\n", selection == 3 ? "> " : "  ");

        key = getch();

        if (key == 'W' || key == 'w') {
            selection--;
        } else if (key == 'S' || key == 's') {
            selection++;
        } else if (key == 13) {
            break;
        }

        if (selection < 0) selection = 0;
        if (selection > 3) selection = 3;
    }

    switch (selection) {
        case 0:
            checkBuku();
            break;
        case 1:
            // checkPeminjamanBuku();
            break;
        case 2:
            // checkUser();
            break;
        case 3:
            return;
    }

    mainMenuAdmin(nama);
}

void login() {
    User user;
    char nim[20], password[20];
    int status = 0;

    clearScreen();
    headingLibrary();
    printf("Login Session\n");
    printf("Masukkan NIM: ");
    scanf("%s", nim); getchar();
    printf("Masukkan Password: ");
    scanf("%s", password); getchar();

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

    if (status == 1) {
        if (strcmp(user.nim, "2802123123") == 0 && strcmp(user.password, "admin") == 0) {
            mainMenuAdmin(user.nama);
        } else {
            mainMenuUser(user.nama);
        }
    } else {
        printf("Login gagal! NIM atau password salah.\n");
        printf("Tekan Enter untuk kembali ke menu utama...");
        getch();
    }
}

void registrasi() {
    User newUser;
    printf("\nRegister Session\n");
    printf("Masukkan NIM: "); 
    scanf("%s", newUser.nim); getchar();

    // if (cekNIM(newUser.nim)) {
    //     printf("NIM sudah terdaftar!\n");
    //     return;
    // }

    printf("Masukkan Nama: ");
    scanf("%[^\n]", newUser.nama); getchar();
    printf("Masukkan Password: ");
    scanf("%s", newUser.password); getchar();

    User tempUser[1] = {newUser};
    writeUser(tempUser, 1);
    printf("Registrasi berhasil!\n");
    printf("\n");
    printf("Tekan Enter untuk kembali ke menu utama...");
    getch();
}

void landingPage() {
    int selection = 0;
    char key;

    while (1) {
        clearScreen();
        headingLibrary();
        
        printf("Halo Selamat Datang, silahkan memilih menggunakan w/s dan tekan 'enter' jika sudah\n");

        printf("%s Login\n", selection == 0 ? "> " : "  ");
        printf("%s Register\n", selection == 1 ? "> " : "  ");
        printf("%s Exit\n", selection == 2 ? "> " : "  ");

        key = getch();

        if (key == 'W' || key == 'w') {
            selection--;
        } else if (key == 'S' || key == 's') {
            selection++;
        } else if (key == 13) {
            break;
        }

        if (selection < 0) selection = 0;
        if (selection > 2) selection = 2;
    }

    switch (selection) {
        case 0:
            login();
            landingPage();
            break;
        case 1:
            registrasi();
            landingPage();
            break;
        case 2:
            printf("Selamat Tinggal Byeee...\n");
            return;
    }
}


int main() {
    // Masuk ke fullscreen mode (Windows only)
    // keybd_event(VK_F11, 0, 0, 0);
    keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);

    landingPage();

    return 0;
}
