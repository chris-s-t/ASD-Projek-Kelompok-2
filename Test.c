#include <stdio.h>
#include <stdlib.h>
// typedef struct pizza{

// }pizza;

void tampilmenu(){
    printf("Menu ditampilkan");
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

int printMenu(int *choice) {
    int i;
    char menu[100][100] = {"Tampilkan Menu Makanan",
        "Tampilkan Menu Minuman",
        "Tambahkan Dana",
        "Tambah Pesanan",
        "Hapus Pesanan",
        "Total Harga",
        "Jenis Pembayaran",
        "Check History Pesanan",
    };

    printf("\nWelcome To Pizza Hut (Food And Drinks Ordering)\n");

    for (i = 0; i < 10; i++) {
        printf("%d. %s\n", i+1, menu[i]);
    }

    printf("Masukkan pilihan anda : ");
    scanf("%d",&choice);
}

int main(){
    int choice = 0, i=0;

    while(1){
        choice = printMenu(choice);

        switch (choice){
            case 1:{
                tampilmenu();
                break;
            }
            case 2:{
                tambahdana();
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
