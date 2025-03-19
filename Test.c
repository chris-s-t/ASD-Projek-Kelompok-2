#include <stdio.h>
#include <stdlib.h>
// typedef struct pizza{

// }pizza;
void tampilmenu(){

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
int main(){
    int choice = 0, i=0;
    while(1){
        printf("\nWelcome To Pizza Hut (Food And Drinks Ordering)\n");
        printf("1. Tampilkan Menu\n");
        printf("2. Tambahkan Dana\n");
        printf("3. Tambah Pesanan\n");
        printf("4. Hapus Pesanan\n");
        printf("5. Total Harga\n");
        printf("6. Jenis Pembayaran\n");
        printf("7. Dine in/Take away\n");
        printf("8. Check History Pesanan\n");
        printf("9. Keluar\n\n");
        printf("pilihan anda : ");
        scanf("%d",&choice);
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