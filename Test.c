#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct untuk pesanan
typedef struct pesan{
    char pesanan[50];
    struct pesan *next;
}pesan;

// Struct untuk menu makanan dan minuman
typedef struct{
    char name[50];
    int harga;
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
void tambahpesanan(pesan **head, pesan **tail){
    char temp[50];

    pesan *node;
    node = (pesan *) malloc(sizeof(pesan));

    printf("masukan pesanan : ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    strcpy(node->pesanan, temp);
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
void tampilkeranjang(pesan **head){
    pesan *temp = *head;
    int i = 1;
    printf("keranjang anda :\n");
    while(temp != NULL){
        printf("%d. %s\n", i, temp->pesanan);
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
    menuStruct makanan[40];
    menuStruct minuman[15];
    pesan *head, *tail;
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
                tambahpesanan(&head, &tail);
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
