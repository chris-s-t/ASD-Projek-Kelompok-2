#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// typedef struct pizza{

// }pizza;

void menuMakanan() {
    int counter;
    menuMakan Makanan;
    FILE *menu = fopen("menuMakanan.txt", "r");
    while (!feof(menu)) {
        fscanf(menu, "%[^#]#%d\n",
                   menu.Nama,
                   &menu.Harga);
    }
}
}
void tampilkanMenu(char Tipe[]) {
    printf("Menampilkan Menu Makanan\n");

}

void tambahdana(){

}
void tambahpesanan(){

}
void hapuspesanan(){

}
void totalharga(){

}
void metodepembayaran(){

}
void dineortake(){

}
void checkhistory(){

}

int printMenu() {
    int i, choice;
    char menu[][25] = {"Tampilkan Menu",
        "Tambah Pesanan",
        "Hapus Pesanan",
        "Total Harga",
        "Jenis Pembayaran",
        "Check History Pesanan",
        "Cek Keranjang"
    };

    printf("Welcome To Pizza Hut (Food And Drinks Ordering)\n");

    for (i = 0; i < 8; i++) {
        printf("%d. %s\n", i+1, menu[i]);
    }

    printf("Masukkan pilihan anda : ");
    scanf("%d", &choice);

    return choice;
}
int main(){
    char namaMakanan[100][100];
    char hargaMakanan[100][100];

    namaMakanan = menuMakanan(namaMakanan);
    int choice, i=0;
    char orderType[20];

    while(1){
        choice = printMenu();
        switch (choice){
            case 1:{
                tampilkanMenu();
                break;
            }
            case 2:{
                tambahpesanan();
                break;
            }
            case 3:{
                tambahpesanan();
                break;
            }
            case 4:{
                hapuspesanan();
                break;
            }
            case 5:{
                totalharga();
                break;
            }
            case 6:{
                metodepembayaran();
                break;
            }
            case 7:{
                dineortake();
                break;
            }
            case 8:{
                checkhistory();
                break;
            }
            case 9:{
                printf("terima kasih telah menggunakan aplikasi kami!!!");
                return 0;
            }
            default :{
                printf ("masukan pilihan yang benar!\n\n");
            }
        }
    }

}
