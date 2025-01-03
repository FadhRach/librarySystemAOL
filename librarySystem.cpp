#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <ctype.h>

#if _WIN32 || _WIN64
    #include <windows.h>
    #include <conio.h>
    #define CLEAR_SCREEN "cls"
#else
#include <unistd.h>
#include <termios.h>
//dari https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux
static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}
#define CLEAR_SCREEN "clear"
#endif
void disableCursor() {
     printf("\033[?25l");
}
void enableCursor() {
    printf("\033[?25h");
}

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

typedef struct {
    char nim[20];
    char idBuku[10];
    int status; // 0 = belum dipinjam, 1 = dipinjam
} Peminjaman;



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
        fprintf(f, "\n%s#%s#%s\n", users[i].nim, users[i].nama, users[i].password);
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
        } else if (key == '\n' || key == '\r') {
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
        } else if (key == '\n' || key == '\r') {
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

void pinjamBuku() {
    clearScreen();
    headingLibrary();
    enableCursor();

    Buku buku[100];
    FILE *file = fopen("buku.txt", "r");
    if (!file) {
        printf("File buku.txt tidak ditemukan!\n");
        return;
    }

    int count = 0;
    while (fscanf(file, "%[^#]#%[^#]#%[^#]#%d\n", buku[count].idBuku, buku[count].judul, buku[count].jenis, &buku[count].thnTerbit) != EOF) {
        if (count >= 100) { 
            printf("Data buku kebanyakan\n");
            fclose(file);
            return;
        }
        count++;
    }
    fclose(file);

    SortingDescendingBuku(buku, count);
    ReadAllBuku(buku, count);

    char nim[20], idBuku[10];
    printf("\nMasukkan NIM Anda: ");
    scanf("%8s", nim); getchar();

    printf("Masukkan ID Buku yang ingin dipinjam: ");
    scanf("%s", idBuku); getchar();

    int foundBook = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(buku[i].idBuku, idBuku) == 0) {
            foundBook = 1;
            break;
        }
    }

    if (!foundBook) {
        printf("Buku dengan ID %s tidak ditemukan.\n", idBuku);
        return;
    }

    Peminjaman peminjaman;
    file = fopen("peminjaman.txt", "r");
    if (file) {
        while (fscanf(file, "%[^#]#%[^#]#%d\n", peminjaman.nim, peminjaman.idBuku, &peminjaman.status) != EOF) {
            if (strcmp(peminjaman.idBuku, idBuku) == 0 && peminjaman.status == 1) {
                printf("Maaf, buku sudah dipinjam.\n");
                fclose(file);
                return;
            }
        }
        fclose(file);
    }

    file = fopen("peminjaman.txt", "a");
    if (!file) {
        printf("Gagal membuka file peminjaman.txt untuk menambahkan data.\n");
        return;
    }

    fprintf(file, "%s#%s#%d\n", nim, idBuku, 1);  
    fclose(file);
    printf("Buku berhasil dipinjam!\n");

    printf("Tekan Enter untuk kembali ke menu utama...");
    getch();
    disableCursor();
}


void lihatPeminjamanBuku() {
    enableCursor();
    clearScreen();
    headingLibrary();

    FILE *file = fopen("peminjaman.txt", "r");
    if (!file) {
        printf("data peminjaman tidak bisa diakses\n");
        sleep(2);
        return;
    }

    Peminjaman peminjaman[100];
    int count = 0;

    while (fscanf(file, "%[^#]#%[^#]#%d\n", peminjaman[count].nim, peminjaman[count].idBuku, &peminjaman[count].status) != EOF) {
        count++;
    }
    fclose(file);

    char nim[20];
    printf("Masukkan NIM Anda: ");
    scanf("%s", nim); getchar();

    int found = 0;
    printf("\n+------------+------------------------------------------+------------------------------+\n");
    printf("| ID Buku    | Judul                                    | Status                       |\n");
    printf("+------------+------------------------------------------+------------------------------+\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(peminjaman[i].nim, nim) == 0 && peminjaman[i].status == 1) {
            Buku buku;
            FILE *bookFile = fopen("buku.txt", "r");
            if (bookFile) {
                while (fscanf(bookFile, "%[^#]#%[^#]#%[^#]#%d\n", buku.idBuku, buku.judul, buku.jenis, &buku.thnTerbit) != EOF) {
                    if (strcmp(buku.idBuku, peminjaman[i].idBuku) == 0) {
                        printf("| %-10s | %-40s | %-28s |\n", buku.idBuku, buku.judul, peminjaman[i].status == 1 ? "Dipinjam" : "Tersedia");
                        found = 1;
                        break;
                    }
                }
                fclose(bookFile);
            }
        }
    }

    if (!found) {
        printf("| %-90s |\n", "Tidak ada buku yang dipinjam.");
    }

    printf("+------------+------------------------------------------+------------------------------+\n");
    printf("Tekan Enter untuk kembali ke menu utama...");
    getch();

    disableCursor();
}

void kembalikanBuku() {
    clearScreen();
    enableCursor();
    headingLibrary();
    char nim[20], idBuku[10];
    int foundBook = 0;
    int hasBorrowedBooks = 0; // Flag to check if books are displayed
    printf("\nMasukkan NIM Anda: ");
    scanf("%s", nim); getchar();

    Peminjaman peminjaman;
    FILE *file = fopen("peminjaman.txt", "r");
    FILE *tempFile = fopen("temp_peminjaman.txt", "w");

    if (!file || !tempFile) {
        printf("Gagal membuka file peminjaman!\n");
        return;
    }

    printf("\n+------------+------------------------------------------+------------------------------+\n");
    printf("| ID Buku    | Judul                                    | Status                       |\n");
    printf("+------------+------------------------------------------+------------------------------+\n");

    while (fscanf(file, "%[^#]#%[^#]#%d\n", peminjaman.nim, peminjaman.idBuku, &peminjaman.status) != EOF) {
        if (peminjaman.status == 0) {
            fprintf(tempFile, "%s#%s#%d\n", peminjaman.nim, peminjaman.idBuku, peminjaman.status);
            continue;
        }

        if (strcmp(peminjaman.nim, nim) == 0) {
            Buku buku;
            FILE *bookFile = fopen("buku.txt", "r");
            if (bookFile) {
                while (fscanf(bookFile, "%[^#]#%[^#]#%[^#]#%d\n", buku.idBuku, buku.judul, buku.jenis, &buku.thnTerbit) != EOF) {
                    if (strcmp(buku.idBuku, peminjaman.idBuku) == 0) {
                        printf("| %-10s | %-40s | %-28s |\n", buku.idBuku, buku.judul, "Dipinjam");
                        hasBorrowedBooks = 1; // Mark that a book has been displayed
                        break;
                    }
                }
                fclose(bookFile);
            }
        }

        fprintf(tempFile, "%s#%s#%d\n", peminjaman.nim, peminjaman.idBuku, peminjaman.status);
    }
    printf("+------------+------------------------------------------+------------------------------+\n");

    fclose(file);
    fclose(tempFile);

    if (!hasBorrowedBooks) {
        printf("Tidak ada buku yang dipinjam.\n");
    } else {
        printf("Masukkan ID Buku yang ingin dikembalikan: ");
        scanf("%s", idBuku); getchar();

        file = fopen("peminjaman.txt", "r");
        tempFile = fopen("temp_peminjaman.txt", "w");
        int found = 0;

        while (fscanf(file, "%[^#]#%[^#]#%d\n", peminjaman.nim, peminjaman.idBuku, &peminjaman.status) != EOF) {
            if (strcmp(peminjaman.nim, nim) == 0 && strcmp(peminjaman.idBuku, idBuku) == 0 && peminjaman.status == 1) {
                found = 1;
                peminjaman.status = 0; 
            }

            fprintf(tempFile, "%s#%s#%d\n", peminjaman.nim, peminjaman.idBuku, peminjaman.status);
        }

        fclose(file);
        fclose(tempFile);

        if (found) {
            remove("peminjaman.txt");
            rename("temp_peminjaman.txt", "peminjaman.txt");
            printf("\nBuku berhasil dikembalikan!\n");
        } else {
            remove("temp_peminjaman.txt");
            printf("\nBuku dengan ID %s tidak ditemukan dalam peminjaman Anda.\n", idBuku);
        }
    }

    disableCursor();
    printf("Tekan Enter untuk kembali ke menu utama...");
    getch();
}





void mainMenuUser(char *nama) {
    disableCursor();
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
        } else if (key == '\n' || key == '\r') {
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
            lihatPeminjamanBuku();
            break;
        case 2:
            pinjamBuku();
            break;
        case 3:
            kembalikanBuku();
            break;
        case 4:
            return;
    }

    mainMenuUser(nama);
}

void mainMenuAdmin(char *nama) {
    int selection = 0;
    char key;
    disableCursor();
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
        } else if (key == '\n' || key == '\r') {
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
    enableCursor();
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
    disableCursor();
}


void registrasi() {
    clearScreen();
    enableCursor();
    headingLibrary();
    User newUser;
    puts("NIM harus terdiri dari 8 digit angka.");
    printf("Masukkan NIM: "); 
    scanf("%s", newUser.nim); getchar();


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
    disableCursor();
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
        } else if (key == '\n' || key == '\r') {
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
    #if _WIN32 || _WIN64
    // Masuk ke fullscreen mode (Windows only)
    // keybd_event(VK_F11, 0, 0, 0);
    keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);
    #endif
    disableCursor();
    landingPage();

    return 0;
}
