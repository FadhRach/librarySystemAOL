#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#if _WIN32
#include <conio.h>
#endif

int selection = 0, valuewhileloop = 1;
char key;

int getKey() {
    #if _WIN32
    return getch();
    #else
    return getchar();
    #endif
}

void clearScreen() {
    #if _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void mainMenu(int selection) {
    clearScreen();

    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("  ______   ______  __    __  ______  ________   ______         __       ______  _______   _______    ______   _______ __      __\n");
    printf(" /      \\ |      \\|  \\  |  \\|      \\|        \\ /      \\       |  \\     |      \\|       \\ |       \\  /      \\ |       \\  \\    /  \\\n");
    printf("|  $$$$$$\\ \\$$$$$$| $$  | $$ \\$$$$$$| $$$$$$$$|  $$$$$$\\      | $$      \\$$$$$$| $$$$$$$\\| $$$$$$$\\|  $$$$$$\\| $$$$$$$\\$$\\  /  $$\n");
    printf("| $$___\\$$  | $$   \\$$\\/  $$  | $$  | $$__    | $$___\\$$      | $$       | $$  | $$__/ $$| $$__| $$| $$__| $$| $$__| $$\\$$\\/  $$\n");
    printf(" \\$$    \\   | $$    >$$  $$   | $$  | $$  \\    \\$$    \\       | $$       | $$  | $$    $$| $$    $$| $$    $$| $$    $$ \\$$  $$\n");
    printf(" _\\$$$$$$\\  | $$   /  $$$$\\   | $$  | $$$$$    _\\$$$$$$$\\      | $$       | $$  | $$$$$$$\\| $$$$$$$\\| $$$$$$$$| $$$$$$$\\  \\$$$$\n");
    printf("|  \\__| $$ _| $$_ |  $$ \\$$\\ _| $$_ | $$_____ |  \\__| $$      | $$_____ _| $$_ | $$__/ $$| $$  | $$| $$  | $$| $$  | $$  | $$\n");
    printf(" \\$$    $$|   $$ \\| $$  | $$|   $$ \\| $$     \\ \\$$    $$      | $$     \\   $$ \\| $$    $$| $$  | $$| $$  | $$| $$  | $$  | $$\n");
    printf("  \\$$$$$$  \\$$$$$$ \\$$   \\$$ \\$$$$$$ \\$$$$$$$$  \\$$$$$$        \\$$$$$$$$\\$$$$$$ \\$$$$$$$  \\$$   \\$$ \\$$   \\$$ \\$$   \\$$   \\$$\n");
    printf("---------------------------------==----------------------------------------------------------------------------------------------------\n");
    printf("Selamat datang [namaPanjang] di perpustakaan ada yang bisa dibantu?\n");
    
    if (selection == 0) {
        printf(">meminjam buku \njadwal peminjaman buku \npengembalian buku \n");
    } else if (selection == 1) {
        printf("meminjam buku \n>jadwal peminjaman buku \npengembalian buku \n");
    } else if (selection == 2) {
        printf("meminjam buku \njadwal peminjaman buku \n>pengembalian buku \n");
    }
}

int main() {
    while(valuewhileloop) {
        mainMenu(selection);
   
        key = getKey();

        if (key == 'W' || key == 'w') {
            selection--;  
        } else if (key == 'S' || key == 's') {
            selection++;  
        } else if (key == ' ') {
            break;  
        }

     
        if (selection < 0) {
            selection = 0;  
        } else if (selection > 2) {
            selection = 2;  
        }
		switch(selection) {
			case 0:
                printf("ke menu meminjam buku");
				break;
			case 1:
				//ke menu jadwal
                printf("jadwal peminjaman buku");
				break;
			case 2:
				//ke menu pengambilan buku	
                printf("pengembalian buku");
				break; 
			default:
				//nanti aja dipikirn
                break;
                }
    }
    return 0;
}
