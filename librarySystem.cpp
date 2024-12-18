#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
//----------------------------------------------------------------------

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
	printf("---------------------------------==----------------------------------------------------------------------------------------------------\n");
}

void mainMenu() {
    int selection = 0;
    char key;

    while (1) {
        clearScreen();
        
	    printf("Selamat datang [namaPanjang] di perpustakaan ada yang bisa dibantu?\n");

        printf("%s Meminjam Buku\n", selection == 0 ? "> " : "  ");
        printf("%s Jadwal Peminjaman Buku\n", selection == 1 ? "> " : "  ");
        printf("%s Pengembalian Buku\n", selection == 2 ? "> " : "  ");

        key = getch();

        if (key == 'W' || key == 'w') {
            selection--;
        } else if (key == 'S' || key == 's') {
            selection++;
        } else if (key == ' ') {
            break;
        }

        if (selection < 0) selection = 0;
        if (selection > 2) selection = 2;
    }

    clearScreen();
    switch (selection) {
        case 0:
            printf("Anda memilih: Meminjam Buku\n");
            break;
        case 1:
            printf("Anda memilih: Jadwal Peminjaman Buku\n");
            break;
        case 2:
            printf("Anda memilih: Pengembalian Buku\n");
            break;
    }
}

int main() {
    int choice;
    // Masuk ke fullscreen mode (Windows only)
    keybd_event(VK_F11, 0, 0, 0);
    keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);

    headingLibrary();

    printf("  __    __       __      _____  ___    _______   ___      ___       __      _____  ___        _______       __       ___      ___   _______     \n");
    printf(" /\" |  | \"\\     /\"\"\\    (\\\"   \\|\"  \\  /\" _   \"| |\"  \\    /\"  |     /\"\"\\    (\\\"   \\|\"  \\      /\" _   \"|     /\"\"\\     |\"  \\    /\"  | /\"     \"|    \n");
    printf("(:  (__)  :)   /    \\   |.\\\\   \\    |(: ( \\___)  \\   \\  //   |    /    \\   |.\\\\   \\    |    (: ( \\___)    /    \\     \\   \\  //   |(: ______)    \n");
    printf(" \\/      \\/   /' /\\  \\  |: \\.   \\\\  | \\/ \\       /\\\\  \\/.    |   /' /\\  \\  |: \\.   \\\\  |     \\/ \\        /' /\\  \\    /\\\\  \\/.    | \\/    |      \n");
    printf(" //  __  \\\\  //  __'  \\ |.  \\    \\. | //  \\ ___ |: \\.        |  //  __'  \\ |.  \\    \\. |     //  \\ ___  //  __'  \\  |: \\.        | // ___)_     \n");
    printf("(:  (  )  :)/   /  \\\\  \\|    \\    \\ |(:   _(  _||.  \\    /:  | /   /  \\\\  \\|    \\    \\ |    (:   _(  _|/   /  \\\\  \\ |.  \\    /:  |(:      \"|    \n");
    printf(" \\__|  |__/(___/    \\___)\\___|\\____\\) \\_______) |___|\\__/|___|(___/    \\___)\\___|\\____\\)     \\_______)(___/    \\___)|___|\\__/|___| \\_______)    \n");
    printf("                                                                                                                                              \n");

    
    

    

    return 0;
}
