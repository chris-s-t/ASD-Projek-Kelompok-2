#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct menuStruct{
    char name[50];
    int harga;
    struct menuStruct *next;
}menuStruct;

// Menginisialisasi menu makanan dan minuman dengan file processing
void menuMakanan(menuStruct makanan[], menuStruct minuman[]) {
    // Inisialisasi menu makanan
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

    // Inisialisasi menu minuman
    counter = 0;
    fp = fopen("menuMinuman.txt", "r");
    if (!fp) {
        printf("Error: Tidak bisa membuka file menuMinuman.txt\n");
        return;
    }
    while (counter < 15 && (fscanf(fp, "%[^#]#%d\n",minuman[counter].name,&minuman[counter].harga)) == 2){
        counter++;
    }
    fclose(fp);
}

// Menampilkan menu makanan dan minuman dalam tabel
void tampilkanMenu(menuStruct makanan[], menuStruct minuman[]) {
    printf("Menampilkan Menu Makanan\n");
    printf("============================================================   ============================================================\n");
    printf("|ID| %27s%13s | %7s%3s |   |ID| %27s%13s | %7s%3s |\n", "Nama Makanan", "", "Harga", "", "Nama Minuman", "", "Harga", "");
    printf("============================================================   ============================================================\n");

    for(int i = 0; i < 40 ; i++){
        if (i < 15){
            printf("|%-2d| %-40s | Rp. %-6d |   |%-2d| %-40s | Rp. %-6d |\n", i+1, makanan[i].name, makanan[i].harga, i+1, minuman[i].name, minuman[i].harga);
        }
        else if ( i == 15){
            printf("|%-2d| %-40s | Rp. %-6d |   ============================================================\n",i, makanan[i].name, makanan[i].harga);
        }
        else{
            printf("|%-2d| %-40s | Rp. %-6d |\n",i+1, makanan[i].name, makanan[i].harga);
        }
    }
    printf("============================================================\n");
}

// Menambahkan pesanan ke keranjang
void tambahpesanan(menuStruct **head, menuStruct **tail, menuStruct makanan[], menuStruct minuman[]){
    int choice, pilih, harga;
    char temp[50];
    printf("mau (1)makanan atau (2)minuman : "); 
    scanf("%d",&choice);
    getchar();
    if(choice == 1){
        printf("masukan makanan pilihan anda : ");
        scanf("%d",&pilih);
        getchar();
        if (pilih > 40 || pilih < 1){
            printf("masukan pilihan yang benar!");
            return;
        }
        strcpy(temp, makanan[pilih-1].name);
        harga = makanan[pilih-1].harga;
    }else if (choice == 2){
        printf("masukan minuman pilihan anda : ");
        scanf("%d",&pilih);
        getchar();
        if (pilih > 15 || pilih < 1){
            printf("masukan pilihan yang benar!");
            return;
        }
        strcpy(temp, minuman[pilih-1].name);
        harga = minuman[pilih-1].harga;
    }else{
        printf("masukan pilihan yang benar!");
        return;
    }
    menuStruct *node;
    node = (menuStruct *) malloc(sizeof(menuStruct));
    if (!node) {
        printf("Gagal mengalokasikan memori!\n");
        return;
    }
    strcpy(node->name, temp);
    node->harga = harga;
    node->next = NULL;

    if ((*head) == NULL){
        (*head) = (*tail) = node;
    }else{
        (*tail)->next = node;
        (*tail) = node;
    }
}
void tambahdana(){

}
void hapuspesanan(){

}
void totalharga(){

}
void metodepembayaran(){

}

// Menampilkan isi keranjang
void tampilkeranjang(menuStruct **head){
    menuStruct *temp = *head;
    int i = 1;
    printf("keranjang anda :\n");
    while(temp != NULL){
        printf("%d. %s\n", i, temp->name);
        temp = temp->next;
        i++;
    }
    printf("\n\n");
}
void checkhistory(){

}

// Menampilkan menu utama
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

    for (i = 0; i < 7; i++) {
        printf("%d. %s\n", i+1, menu[i]);
    }

    printf("Masukkan pilihan anda : ");
    scanf("%d", &choice);
    getchar();

    return choice;
}

// Main
int main(){
    menuStruct makanan[40], minuman[40], *head, *tail;
    head = tail = NULL;
    menuMakanan(makanan, minuman);
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
                tambahpesanan(&head, &tail, makanan, minuman);
                break;
            }
            case 3:{
                hapuspesanan();
                break;
            }
            case 4:{
                totalharga();
                break;
            }
            case 5:{
                metodepembayaran();
                break;
            }
            case 6:{
                checkhistory();
                break;
            }
            case 7:{
                tampilkeranjang(&head);
                break;
            }
            case 8:{
                printf("Terima kasih telah menggunakan aplikasi kami!!!");
                return 0;
            }
            default :{
                printf ("Masukkan pilihan yang benar!\n\n");
            }
        }
    }
}
