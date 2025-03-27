#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for Menu
typedef struct{
    char name[50];
    int harga;
}menuStructmakan;

typedef struct{
    char name[50];
    int harga;
}menuStructminum;

void menuMakanan(menuStructmakan makanan[]) {
    int counter = 0;
    FILE *fp = fopen("menuMakanan.txt", "r");
    if (!fp) {
        printf("Error: Tidak bisa membuka file menuMakanan.txt\n");
        return;
    }
    while (counter < 40 && (fscanf(fp, "%[^#]#%d\n",makanan[counter].name,&makanan[counter].harga)) == 2){
        counter++;
    }
    fclose(fp);
}

void menuMinuman(menuStructminum minuman[]) {
    int counter = 0;
    FILE *fp = fopen("menuMinuman.txt", "r");
    if (!fp) {
        printf("Error: Tidak bisa membuka file menuMinuman.txt\n");
        return;
    }
    while (counter < 15 && (fscanf(fp, "%[^#]#%d\n",minuman[counter].name,&minuman[counter].harga)) == 2){
        counter++;
    }
    fclose(fp);
}

void tampilkanMenu(menuStructmakan makanan[], menuStructminum minuman[]) {
    printf("Menampilkan Menu Makanan\n");
    printf("============================================================   ============================================================\n");
    printf("|ID| %27s%13s | %7s%3s |   |ID| %27s%13s | %7s%3s |\n", "Nama Makanan", "", "Harga", "", "Nama Minuman", "", "Harga", "");
    printf("============================================================   ============================================================\n");
    for(int i = 0; i < 15 ; i++){
        printf("|%-2d| %-40s | Rp. %-6d |   |%-2d| %-40s | Rp. %-6d |\n", i+1, makanan[i].name, makanan[i].harga, i+1, minuman[i].name, minuman[i].harga);
    }
    printf("|%-2d| %-40s | Rp. %-6d |   ============================================================\n",15, makanan[14].name, makanan[14].harga);
    for(int i = 15; i < 40 ; i++){
        printf("|%-2d| %-40s | Rp. %-6d |\n",i+1, makanan[i].name, makanan[i].harga);
    }
    printf("============================================================\n");
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
    menuStructmakan makanan[40];
    menuStructminum minuman[15];
    menuMakanan(makanan);
    menuMinuman(minuman);
    int choice, i=0;
    char orderType[20];

    while(1){
        choice = printMenu();
        switch (choice){
            case 1:{
                tampilkanMenu(makanan, minuman);
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
                printf("Terima kasih telah menggunakan aplikasi kami!!!");
                return 0;
            }
            default :{
                printf ("Masukkan pilihan yang benar!\n\n");
            }
        }
    }

}
