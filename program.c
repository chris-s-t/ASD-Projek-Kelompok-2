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

typedef struct BSTNode {
    char name[100];
    int harga;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Struct
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

//ALgoritma Sorting Bubble dan Insertion
void swapStruct(menuStruct *a, menuStruct *b){
    menuStruct temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble sort dari harga terbesar ke terkecil
void bubbleSortMenu(menuStruct arr[], int n){
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = n - 1; j > 0; j--) {
            if (arr[j].harga > arr[j - 1].harga) {
                swapStruct(&arr[j], &arr[j - 1]);
            }
        }
    }
}

// Insertion sort dari harga terkecil ke terbesar
void insertionSortMenu(menuStruct arr[], int n){
    int i, j;
    menuStruct temp;
    for (i = 0; i < n; i++) {
        temp = arr[i];
        for (j = i - 1; j >= 0 && arr[j].harga > temp.harga; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
    }
}

int sortMenu(menuStruct makanan[], menuStruct minuman[]){
    int choice;
    printf("\n=== Menu Sorting ===\n");
    printf("1. Bubble Sort (Descending)\n");
    printf("2. Insertion Sort (Ascending)\n");
    printf("3. Kembali ke menu utama");
    printf("Pilihan Anda: ");
    scanf("%d", &choice);

    switch (choice){
        case 1:
            bubbleSortMenu(makanan, 40);
            bubbleSortMenu(minuman, 15);
            printf("\nMenu diurutkan dari harga tertinggi ke terendah.\n");
            break;
        case 2:
            insertionSortMenu(makanan, 40);
            insertionSortMenu(minuman, 15);
            printf("\nMenu diurutkan dari harga terendah ke tertinggi.\n");
            break;
        case 3:
            printf("Kembali ke menu utama tanpa sorting.\n");
            break;
        default:
            printf("Pilihan tidak valid. Silakan pilih lagi.\n");
            break;
    }

    return choice;
}

//Menampung tampilkanMenu dan sortMenu untuk pilihan user
void tampilkanMenuAwal(menuStruct makanan[], menuStruct minuman[]){
    int sortChoice;
    do{
        tampilkanMenu(makanan, minuman);
        sortChoice = sortMenu(makanan, minuman); 

    }while (sortChoice != 3);
}


BSTNode* insertBST(BSTNode* root, menuStruct data) {
    if (root == NULL) {
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
        strcpy(newNode->name, data.name);
        newNode->harga = data.harga;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (data.harga < root->harga)
        root->left = insertBST(root->left, data);
    else
        root->right = insertBST(root->right, data);

    return root;
}

// Menampilkan menu topping
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
ulang:
    printf("Pilih topping no : ");
    scanf("%d",&temp);
    getchar();
    if(temp < 1 || temp > 20){
        printf("Input invalid please try again\n");
        goto ulang;
    }
    char top [40] = " + ";
    strcat(top, topping[temp - 1].name);
    strcat(node->name, top);
    node->harga = node->harga + topping[temp-1].harga;
    printf("Topping ditambahkan!\n");
}

// Menambahkan pesanan ke keranjang
BSTNode* tambahPesanan(menuStruct makanan[], menuStruct minuman[], menuStruct topping[], BSTNode* root) {
    int kategori, id;
    menuStruct pesanan;

    printf("Pilih kategori:\n");
    printf("[1] Makanan\n[2] Minuman\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &kategori);

    if (kategori == 1) {
        //tampilkanMenuMakanan(makanan); // fungsi tampilkan menu makanan
        printf("Masukkan ID makanan: ");
        scanf("%d", &id);

        if (id < 0 || id >= 40) {
            printf("ID tidak valid!\n");
            return root;
        }

        pesanan = makanan[id];

        // Cek apakah ID termasuk range makanan utama
        if (id >= 0 && id <= 14) {
            tambahtopping(topping, &pesanan);
        }

    } else if (kategori == 2) {
        //tampilkanMenuMinuman(minuman); // fungsi tampilkan menu minuman
        printf("Masukkan ID minuman: ");
        scanf("%d", &id);

        if (id < 0 || id >= 40) {
            printf("ID tidak valid!\n");
            return root;
        }

        pesanan = minuman[id];
    } else {
        printf("Kategori tidak valid.\n");
        return root;
    }

    // Masukkan ke dalam BST keranjang
    root = insertBST(root, pesanan);
    printf("Pesanan berhasil ditambahkan ke keranjang!\n");

    return root;
}


// menghapus pesanan
BSTNode* hapusPesanan(BSTNode* root, int harga) {
    if (root == NULL) {
        printf("Pesanan dengan harga %d tidak ditemukan.\n", harga);
        return NULL;
    }

    if (harga < root->harga) {
        root->left = hapusPesanan(root->left, harga);
    } else if (harga > root->harga) {
        root->right = hapusPesanan(root->right, harga);
    } else {
        // Node ditemukan
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }

        // Dua anak: cari inorder successor
        BSTNode* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;

        strcpy(root->name, temp->name);
        root->harga = temp->harga;
        root->right = hapusPesanan(root->right, temp->harga);
    }

    return root;
}
BSTNode* hapusPesananInput(BSTNode* root) {
    int harga;
    printf("Masukkan harga pesanan yang ingin dihapus: ");
    scanf("%d", &harga);
    root = hapusPesanan(root, harga);
    printf("Pesanan dengan harga %d telah dihapus.\n", harga);
    return root;
}
// Menghitung total harga seluruh pesanan dan jumlahnya di keranjang
int totalHarga(BSTNode* root) {
    if (root == NULL) return 0;
    return root->harga + totalHarga(root->left) + totalHarga(root->right);
}
void tampilTotalHarga(BSTNode* root) {
    int total = totalHarga(root);
    printf("Total harga semua pesanan di keranjang: Rp. %d\n", total);
}

// Menampilkan isi keranjang
void inorderTampil(BSTNode* node) {
        if (node == NULL) return;
        inorderTampil(node->left);
        printf("- %s | Harga: Rp. %d\n", node->name, node->harga);
        inorderTampil(node->right);
}
void tampilKeranjang(BSTNode* root) {
    if (root == NULL) {
        printf("Keranjang masih kosong.\n");
        return;
    }

    printf("=========== Daftar Pesanan di Keranjang ===========\n");
    inorderTampil(root);
    printf("====================================================\n");
}



void freeKeranjang(BSTNode* node) {
    if (node == NULL) return;
    freeKeranjang(node->left);
    freeKeranjang(node->right);
    free(node);
}

void checkout(BSTNode** root) {
    if (*root == NULL) {
        printf("\nKeranjang kosong! Silahkan pesan makanan atau minuman terlebih dahulu.\n");
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

    switch (metode) {
        case 1: strcpy(metodePembayaran, "Tunai"); break;
        case 2: strcpy(metodePembayaran, "Kartu Kredit/Debit"); break;
        case 3: strcpy(metodePembayaran, "E-Wallet"); break;
        default:
            printf("Metode tidak valid!\n");
            return; 
    }
    freeKeranjang(*root);
    *root = NULL;
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
    menuStruct makanan[40], minuman[40], topping[30];
    
    int choice, total = 0;
    BSTNode *keranjang = NULL;

    printf("====== Welcome To Pizza Hut (Food And Drink Ordering) =======\n");
    pizzaForm();
    menuMakanan(makanan, minuman, topping);

    while (1) {
        choice = printMenu();
        switch (choice) {
            case 1:
                tampilkanMenuAwal(makanan, minuman);
                break;

            case 2:
                keranjang = tambahPesanan(makanan, minuman, topping, keranjang);                
                break;

            case 3:
                keranjang = hapusPesananInput(keranjang); // harus kamu implementasikan
                break;

            case 4:
                printf("=== Keranjang Anda ===\n");
                tampilKeranjang(keranjang);  // inorder traversal
                totalHarga(keranjang); 
                break;

            case 5:
                checkout(&keranjang); // tampilkan + simpan ke file + kosongkan BST
                keranjang = NULL;
                break;
            case 6:
                printf("Terima kasih telah menggunakan aplikasi kami!!!\n");
                return 0;

            default:
                printf("Masukkan pilihan yang benar!\n\n");
        }
    }
}
