#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Struct untuk menu makanan dan minuman
typedef struct menuStruct
{
    char name[100];
    int harga;
    struct menuStruct *next;
} menuStruct;

typedef struct Node {
    char namaPesanan[100];
    struct Node* next;
} Node;
// Menampilkan bentuk pizza
void pizzaForm() 
{
    printf("\n           /\\               /\\               /\\      \n");
    printf("          /  \\             /  \\             /  \\       \n");
    printf("         /    \\           /    \\           /    \\      \n");
    printf("        /      \\         /      \\         /      \\     \n");
    printf("       /  (o)   \\       /(o)     \\       /     (o)\\    \n");
    printf("      /    (o)   \\     /      (o) \\     /   (o)    \\   \n");
    printf("     /    (o)  (o)\\   /  (o) (o)   \\   /  (o) (o)   \\  \n");
    printf("    /______________\\ /______________\\ /______________\\ \n");
}
// Menginisialisasi menu makanan dan minuman dengan file processing
void menuMakanan(menuStruct makanan[], menuStruct minuman[], menuStruct topping[])
{
    // Inisialisasi menu makanan
    int counter = 0;
    FILE *fp = fopen("menuMakanan.txt", "r");
    if (!fp)
    {
        printf("Error: Tidak bisa membuka file menuMakanan.txt\n");
        return;
    }
    while (counter < 40 && (fscanf(fp, "%[^#]#%d\n", makanan[counter].name, &makanan[counter].harga)) == 2)
    {
        counter++;
    }
    fclose(fp);

    // Inisialisasi menu minuman
    counter = 0;
    fp = fopen("menuMinuman.txt", "r");
    if (!fp)
    {
        printf("Error: Tidak bisa membuka file menuMinuman.txt\n");
        return;
    }
    while (counter < 15 && (fscanf(fp, "%[^#]#%d\n", minuman[counter].name, &minuman[counter].harga)) == 2)
    {
        counter++;
    }
    fclose(fp);

    //inisialisasi menu untuk topping
    counter = 0;
    fp = fopen("topping.txt", "r");
    if (!fp)
    {
        printf("Error: Tidak bisa membuka file topping.txt\n");
        return;
    }
    while (counter < 20 && (fscanf(fp, "%[^#]#%d\n", topping[counter].name, &topping[counter].harga)) == 2)
    {
        counter++;
    }
    fclose(fp);
}

// Menampilkan menu makanan dan minuman dalam tabel
void tampilkanMenu(menuStruct makanan[], menuStruct minuman[])
{
    printf("\nMenampilkan Menu Makanan\t\t\t\t       Menampilkan Menu Minuman\n");
    printf("============================================================   ============================================================\n");
    printf("|ID| %27s%13s | %7s%3s |   |ID| %27s%13s | %7s%3s |\n", "Nama Makanan", "", "Harga", "", "Nama Minuman", "", "Harga", "");
    printf("============================================================   ============================================================\n");

    for (int i = 0; i < 40; i++)
    {
        if (i < 15)
        {
            printf("|%-2d| %-40s | Rp. %-6d |   |%-2d| %-40s | Rp. %-6d |\n", i + 1, makanan[i].name, makanan[i].harga, i + 1, minuman[i].name, minuman[i].harga);
        }
        else if (i == 15)
        {
            printf("|%-2d| %-40s | Rp. %-6d |   ============================================================\n", i + 1, makanan[i].name, makanan[i].harga);
        }
        else
        {
            printf("|%-2d| %-40s | Rp. %-6d |\n", i + 1, makanan[i].name, makanan[i].harga);
        }
    }
    printf("============================================================\n\n");
}
void tambahtopping(menuStruct topping[], menuStruct *node){
    int temp;
    printf("Apakah anda ingin menambahkan topping?\n");
    printf("[0] Tidak\n");
    printf("[1] Ya\n");
    printf("Masukkan pilihan: ");
    scanf("%d",&temp);
    if (temp == 0){
        return;
    }
    else if (temp > 1 || temp < 0){
        return;
    }

    printf("============================================================\n");
    printf("|ID| %27s%12s  | %7s    |\n", "Nama Topping", "", "Harga");
    printf("============================================================\n");
    for (int i = 0; i < 20; i++) {
        printf("|%-2d| %-40s | Rp. %-6d |\n", i + 1, topping[i].name, topping[i].harga);
    }
    printf("============================================================\n");
hm:
    printf("Pilih topping no : ");
    scanf("%d",&temp);
    getchar();
    if(temp < 1 || temp > 20){
        printf("Input invalid please try again\n");
        goto hm;
    }
    char top [40] = " + ";
    strcat(top, topping[temp - 1].name);
    strcat(node->name, top);
    node->harga = node->harga + topping[temp-1].harga;
    printf("Topping ditambahkan!\n");
}

// Menambahkan pesanan ke keranjang
void tambahPesanan(menuStruct **head, menuStruct **tail, menuStruct makanan[], menuStruct minuman[], menuStruct topping[])
{
    int choice, pilih;
    menuStruct *node;
    node = (menuStruct *)malloc(sizeof(menuStruct));
    if (!node)
    {
        printf("Gagal mengalokasikan memori!\n");
        return;
    }
    printf("\n========================= Jenis Menu ========================\n");
    printf("[1] Makanan\n");
    printf("[2] Minuman\n");
    printf("=============================================================\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &choice);
    getchar();
    if (choice == 1)
    {
        printf("Masukkan ID makanan pilihan anda : ");
        scanf("%d", &pilih);
        getchar();
        if (pilih > 40 || pilih < 1)
        {
            printf("Masukkan pilihan yang benar!");
            return;
        }
        strcpy(node->name, makanan[pilih - 1].name);
        node->harga = makanan[pilih - 1].harga;
        if(pilih <= 15){
            tambahtopping(topping,node);
        }
    }
    else if (choice == 2)
    {
        printf("Masukkan ID minuman pilihan anda : ");
        scanf("%d", &pilih);
        getchar();
        if (pilih > 15 || pilih < 1)
        {
            printf("Masukkan pilihan yang benar!");
            return;
        }
        strcpy(node->name, minuman[pilih - 1].name);
        node->harga = minuman[pilih - 1].harga;
    }
    else
    {
        printf("Masukkan pilihan yang benar!");
        return;
    }
    node->next = NULL;
    if ((*head) == NULL)
    {
        (*head) = (*tail) = node;
    }
    else
    {
        (*tail)->next = node;
        (*tail) = node;
    }
}
void hapusPesanan(menuStruct **head, menuStruct **tail)
{
    if (*head == NULL)
    {
        printf("\nBelum ada pesanan yang terisi\n");
        return;
    }
    menuStruct *temp = *head;
    int i = 1, del;
    printf("\nMenampilkan keranjang\n");
    printf("============================================================\n");
    printf("|No| %27s%13s | %7s%4s|\n", "Nama", "", "Harga ", "");
    printf("============================================================\n");
    while (temp != NULL)
    {
        printf("|%-2d| %-40s |  Rp. %-5d |\n", i, temp->name, temp->harga);
        temp = temp->next;
        i++;
    }
    printf("============================================================\n");
    printf("Hapus pesanan No: ");
    scanf("%d", &del);
    if (del < 1 || del >= i)
    {
        printf("Nomor pesanan tidak valid!\n");
        return;
    }
    temp = *head;
    if (del == 1)
    {
        *head = (*head)->next;
        free(temp);
        if (*head == NULL)
            *tail = NULL;
        return;
    }
    for (int j = 1; j < del - 1; j++)
    {
        temp = temp->next;
    }
    menuStruct *deleteNode = temp->next;
    temp->next = deleteNode->next;
    if (deleteNode == *tail)
    {
        *tail = temp;
    }
    free(deleteNode);
    printf("Pesanan nomor %d berhasil dihapus.\n", del);
}

void totalHarga(menuStruct **head, int *total)
{
    menuStruct *temp = *head;
    *total = 0;
    int i = 1;
    while (temp != NULL)
    {
        *total += temp->harga;
        temp = temp->next;
        i++;
    }
    printf("Total harga : Rp. %d\n", *total);
}

// Menampilkan isi keranjang
void tampilKeranjang(menuStruct **head){
    if(*head==NULL){
        printf("\nKeranjang kosong! Silahkan pesan makanan atau minuman terlebih dahulu.\n");
        return;
    }
    menuStruct *temp = *head;
    int i = 1, totalHarga = 0;

    printf("\nMenampilkan keranjang\n");
    printf("=============================================================\n");
    printf("|No| %19s%s%19s | %2s%s%2s |\n", "", "Nama", "", "", "Harga", "");
    printf("=============================================================\n");
    while (temp != NULL)
    {
        printf("|%-2d| %-42s | Rp.%-6d |\n", i, temp->name, temp->harga);
        totalHarga += temp->harga;
        temp = temp->next;
        i++;
    }
    printf("=============================================================\n");
    printf("|%16s%s%19s | Rp.%-6d |\n", "", "Total Harga", "", totalHarga);
    printf("=============================================================\n");
    printf("\n");
}

// Menampilkan history atau menghapus history dalam history.txt
void historyManager(char Type[]){
    char line[100];
    FILE *fp = fopen("history.txt", "r");

    if (!fp || !fgets(line, sizeof(line), fp))
    {
        printf("\nBelum ada riwayat pesanan.\n");
        fclose(fp);
        return;
    }
    if (strcmp("View", Type) == 0) {
        printf("\n===================== Riwayat Pesanan =====================\n");
        while (fgets(line, sizeof(line), fp))
        {
            printf("%s", line);
        }
        printf("=============================================================\n");
        fclose(fp);
    }
    else if (strcmp("Delete", Type) == 0) {
        fclose(fp);
        FILE *fp = fopen("history.txt", "w");
        printf("\nHistory telah dihapus\n");
        fclose(fp);
    }
}

void dequeueAll(Node **front, Node **rear) {
    printf("\n=== Status Pesanan Sedang Diproses ===\n");
    while (*front != NULL) {
        Node* temp = *front;
        printf("sedang proses pesanan: %s\n", temp->namaPesanan);
        *front = (*front)->next;
        free(temp);
        Sleep(5000);
    }
    *rear = NULL;
    printf("Semua pesanan telah selesai dimasak.\n");
}
void enqueue(Node **front, Node **rear, char *namaPesanan) {
    Node* baru = (Node*)malloc(sizeof(Node));
    strcpy(baru->namaPesanan, namaPesanan);
    baru->next = NULL;

    if (*rear == NULL) {
        *front = *rear = baru;
    } else {
        (*rear)->next = baru;
        *rear = baru;
    }
}
void cekStatusPesanan(menuStruct **head, menuStruct **tail) {
    Node* front = NULL;
    Node* rear = NULL;
    menuStruct *temp = *head;
    while (temp != NULL){
        enqueue(&front, &rear, temp->name);
        temp = temp->next;
    }
    dequeueAll(&front, &rear);
}


void checkout(menuStruct **head, menuStruct **tail)
{
    FILE *fp = fopen("history.txt", "a");

    if (!fp)
    {
        printf("\nGagal membuka history.txt untuk checkout!\n");
        return;
    }

    if (*head == NULL)
    {
        printf("\nKeranjang kosong! Silahkan pesan makanan atau minuman terlebih dahulu.\n");
        fclose(fp);
        return;
    }

    int metode, totalHarga = 0;
    char metodePembayaran[50];

    printf("\n=== Pilih Metode Pembayaran ===\n");
    printf("1. Tunai\n");
    printf("2. Kartu Kredit/Debit\n");
    printf("3. E-Wallet\n");
    printf("Pilihan: ");
    scanf("%d", &metode);
    getchar();

    switch (metode)
    {
    case 1:
        strcpy(metodePembayaran, "Tunai");
        break;
    case 2:
        strcpy(metodePembayaran, "Kartu Kredit/Debit");
        break;
    case 3:
        strcpy(metodePembayaran, "E-Wallet");
        break;
    default:
        printf("Metode tidak valid!\n");
        fclose(fp);
        return;
    }

    fprintf(fp, "\n===== History =====\n");
    fprintf(fp, "Metode Pembayaran: %s\n", metodePembayaran);
    fprintf(fp, "Daftar Pesanan:\n");

    menuStruct *current = *head;
    while (current)
    {
        fprintf(fp, "- %s \t(Rp. %d)\n", current->name, current->harga);
        totalHarga += current->harga;
        current = current->next;
    }

    fprintf(fp, "\nTotal Harga: Rp. %d\n", totalHarga);
    fclose(fp);

    

    printf("\nCheckout berhasil!\n");
    printf("Total: Rp. %d\n", totalHarga);
    printf("Metode: %s\n", metodePembayaran);
    printf("apakah ingin melihat status pesanan anda?\n");
    int choice;
    printf("Yes[1]\n");
    printf("No [0]\n");
    scanf("%d",&choice);
    if(choice == 1){
        cekStatusPesanan(head, tail);
    }
    
    while (*head)
    {
        menuStruct *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *tail = NULL;
}
// Menampilkan menu utama
int printMenu()
{
    int i, choice;
    char menu[][25] = {"Tampilkan Menu",
                       "Tambah Pesanan",
                       "Hapus Pesanan",
                       "Tampilkan Keranjang",
                       "Check Out",
                       "Cek Riwayat Pesanan",
                       "Hapus Riwayat Pesanan",
                       "Keluar"};
    printf("\n==================== Pizza Hut Main Menu ====================\n");
    for (i = 0; i < 8; i++)
    {
        printf("%d. %s\n", i + 1, menu[i]);
    }
    printf("=============================================================\n");
    printf("Masukkan pilihan anda : ");
    scanf("%d", &choice);
    getchar();
    return choice;
}

// Main
int main() {
    menuStruct makanan[40], minuman[40], topping[30], *head, *tail;
    head = tail = NULL;

    int choice, i = 0, dana = 0, total = 0;
    char orderType[20];

    printf("====== Welcome To Pizza Hut (Food And Drink Ordering) =======");
    pizzaForm();
    menuMakanan(makanan, minuman, topping);
    while (1)
    {
        choice = printMenu();
        switch (choice){
            case 1:
            {
                tampilkanMenu(makanan, minuman);
                break;
            }
            case 2:
            {
                tambahPesanan(&head, &tail, makanan, minuman, topping);
                break;
            }
            case 3:
            {
                hapusPesanan(&head, &tail);
                break;
            }
            case 4:
            {
                tampilKeranjang(&head);
                totalHarga(&head, &total);
                break;
            }
            case 5:
            {
                checkout(&head, &tail);
                break;
            }
            case 6:
            {
                historyManager("View");
                break;
            }
            case 7:
            {
                historyManager("Delete");
                break;
            }
            case 8:
            {
                printf("Terima kasih telah menggunakan aplikasi kami!!!");
                return 0;
            }
            default:
            {
                printf("Masukkan pilihan yang benar!\n\n");
            }
        }
    }
}
