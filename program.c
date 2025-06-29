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

typedef struct HeapNode{
    char name[100];
    int harga;
} HeapNode;

typedef struct Heap{
    HeapNode data[100];
    int size;
} Heap;

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
void menuMakanan(menuStruct makanan[], menuStruct minuman[])
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

int binarySearch(menuStruct arr[], int n, int target, int isAscending) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid].harga == target)
            return mid;
        if (isAscending) {
            if (arr[mid].harga < target)
                left = mid + 1;
            else
                right = mid - 1;
        } else {
            if (arr[mid].harga > target)
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    return -1;
}


int sortMenu(menuStruct makanan[], menuStruct minuman[], int *sortedFlag){
    int choice;
    printf("\n=== Menu Sorting dan Searching ===\n");
    printf("1. Bubble Sort (Descending)\n");
    printf("2. Insertion Sort (Ascending)\n");
	printf("3. Binary Search (berdasarkan harga)\n"); // Hanya bisa setelah melakukan bubble atau insertion
    printf("4. Kembali ke menu utama\n");
    printf("Pilihan Anda: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            bubbleSortMenu(makanan, 40);
            bubbleSortMenu(minuman, 15);
            printf("\nMenu diurutkan dari harga tertinggi ke terendah.\n");
            *sortedFlag = 1;
            break;
        case 2:
            insertionSortMenu(makanan, 40);
            insertionSortMenu(minuman, 15);
            printf("\nMenu diurutkan dari harga terendah ke tertinggi.\n");
            *sortedFlag = 2;
            break;
        case 3:
            if (*sortedFlag == 0) {
                printf("Anda harus melakukan sorting terlebih dahulu!\n");
            } else {
                int kategori, harga, index;
                printf("Pilih kategori: Makanan (1) atau Minuman (2)\nMasukkan pilihan anda: ");
                scanf("%d", &kategori);
                printf("Masukkan harga yang ingin dicari: ");
                scanf("%d", &harga);

                if (kategori == 1) {
                    index = binarySearch(makanan, 40, harga, *sortedFlag == 2);
                    if (index != -1)
                        printf("Ditemukan:[%d] %s | Harga: Rp. %d\n", index+1, makanan[index].name, makanan[index].harga);
                    else
                        printf("Tidak ditemukan makanan dengan harga Rp. %d\n", harga);
                } else if (kategori == 2) {
                    index = binarySearch(minuman, 15, harga, *sortedFlag == 2);
                    if (index != -1)
                        printf("Ditemukan:[%d] %s | Harga: Rp. %d\n", index+1, minuman[index].name, minuman[index].harga);
                    else
                        printf("Tidak ditemukan minuman dengan harga Rp. %d\n", harga);
                } else {
                    printf("Kategori tidak valid.\n");
                }
            }
            break;
        case 4:
            printf("Kembali ke menu utama tanpa aksi lebih lanjut.\n");
            break;
        default:
            printf("Pilihan tidak valid. Silakan pilih lagi.\n");
            break;
    }
    return choice;
}

//Menampung tampilkanMenu dan sortMenu untuk pilihan user
void tampilkanMenuAwal(menuStruct makanan[], menuStruct minuman[], int *sortedFlag){
    int sortChoice;
    do{
        tampilkanMenu(makanan, minuman);
        sortChoice = sortMenu(makanan, minuman, sortedFlag);

    }while (sortChoice != 4);
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

// Menambahkan pesanan ke keranjang
BSTNode* tambahPesananbst(menuStruct makanan[], menuStruct minuman[], BSTNode* root) {
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

        if (id <= 0 || id > 40) {
            printf("ID tidak valid!\n");
            return root;
        }

        pesanan = makanan[id - 1];

    } else if (kategori == 2) {
        //tampilkanMenuMinuman(minuman); // fungsi tampilkan menu minuman
        printf("Masukkan ID minuman: ");
        scanf("%d", &id);

        if (id <= 0 || id > 40) {
            printf("ID tidak valid!\n");
            return root;
        }

        pesanan = minuman[id - 1];
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
void caripesanan(BSTNode* root, int harga, char daftar[][50], int* count) {
    if (root == NULL) return;

    caripesanan(root->left, harga, daftar, count);
    if (root->harga == harga) {
        strcpy(daftar[*count], root->name);
        (*count)++;
    }
    caripesanan(root->right, harga, daftar, count);
}
BSTNode* hapusPesananbst(BSTNode* root, int harga, char* name) {
    if (root == NULL) return NULL;

    if (harga < root->harga) {
        root->left = hapusPesananbst(root->left, harga, name);
    } else if (harga > root->harga) {
        root->right = hapusPesananbst(root->right, harga, name);
    } else {
        int cmp = strcmp(root->name, name);
        if (cmp > 0) {
            root->left = hapusPesananbst(root->left, harga, name);
        } else if (cmp < 0) {
            root->right = hapusPesananbst(root->right, harga, name);
        } else {
            if (root->left == NULL) {
                BSTNode* temp = root->right;
                free(root);
                return temp;
            } else if (root->right == NULL) {
                BSTNode* temp = root->left;
                free(root);
                return temp;
            }

            BSTNode* temp = root->right;
            while (temp->left != NULL) temp = temp->left;

            strcpy(root->name, temp->name);
            root->harga = temp->harga;
            root->right = hapusPesananbst(root->right, temp->harga, temp->name);
        }
    }

    return root;
}
BSTNode* hapusPesananInputbst(BSTNode* root) {
    int harga;
    printf("Masukkan harga pesanan yang ingin dihapus: ");
    scanf("%d", &harga);

    char daftar[100][50];
    int count = 0;
    caripesanan(root, harga, daftar, &count);

    if (count == 0) {
        printf("Tidak ditemukan pesanan dengan harga tersebut.\n");
        return root;
    }

    char name[50];

    if (count == 1) {
        strcpy(name, daftar[0]);
        printf("Pesanan ditemukan: %s | Harga: %d. Menghapus langsung...\n", name, harga);
    } else {
        printf("Ditemukan %d pesanan dengan harga %d:\n", count, harga);
        for (int i = 0; i < count; i++) {
            printf("%d. %s\n", i + 1, daftar[i]);
        }

        int pilihan;
        do {
            printf("Pilih nomor pesanan yang ingin dihapus: ");
            scanf("%d", &pilihan);
        } while (pilihan < 1 || pilihan > count);

        strcpy(name, daftar[pilihan - 1]);
    }

    root = hapusPesananbst(root, harga, name);
    printf("Pesanan '%s' dengan harga %d telah dihapus.\n", name, harga);
    return root;
}
// Menghitung total harga seluruh pesanan dan jumlahnya di keranjang
int totalHargabst(BSTNode* root) {
    if (root == NULL) return 0;
    return root->harga + totalHargabst(root->left) + totalHargabst(root->right);
}
void tampilTotalHargabst(BSTNode* root) {
    int total = totalHargabst(root);
    printf("Total harga semua pesanan di keranjang: Rp. %d\n", total);
}

// Menampilkan isi keranjang
void inorderTampil(BSTNode* node) {
        if (node == NULL) return;
        inorderTampil(node->left);
        printf("- %s | Harga: Rp. %d\n", node->name, node->harga);
        inorderTampil(node->right);
}
void tampilKeranjangbst(BSTNode* root) {
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

void checkoutbst(BSTNode** root) {
    if (*root == NULL) {
        printf("\nKeranjang kosong! Silahkan pesan makanan atau minuman terlebih dahulu.\n");
        return;
    }

    int metode, totalHargabst = 0;
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
//--------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------pembatas heap dengan bst-------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------

void insertHeap(Heap* h, menuStruct item) {
    if (h->size >= 100) {
        printf("Keranjang penuh!\n");
        return;
    }

    int i = h->size++;
    while (i > 0 && item.harga > h->data[(i - 1) / 2].harga) {
        h->data[i] = h->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    strcpy(h->data[i].name, item.name);
    h->data[i].harga = item.harga;
}

void tambahPesananheap(menuStruct makanan[], menuStruct minuman[], Heap* h) {
    int kategori, id;
    printf("Pilih kategori:\n[1] Makanan\n[2] Minuman\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &kategori);

    if (kategori == 1) {
        printf("Masukkan ID makanan: ");
        scanf("%d", &id);
        if (id <= 0 || id > 40) return;
        insertHeap(h, makanan[id - 1]);
    } else if (kategori == 2) {
        printf("Masukkan ID minuman: ");
        scanf("%d", &id);
        if (id <= 0 || id > 15) return;
        insertHeap(h, minuman[id - 1]);
    } else {
        printf("Kategori tidak valid.\n");
    }
}

void hapusPesananHeap(Heap* h) {
    if (h->size == 0) {
        printf("Keranjang kosong!\n");
        return;
    }

    int harga;
    printf("Masukkan harga pesanan yang ingin dihapus: ");
    scanf("%d", &harga);

    char daftar[100][50];
    int indeks[100], count = 0;

    for (int i = 0; i < h->size; i++) {
        if (h->data[i].harga == harga) {
            strcpy(daftar[count], h->data[i].name);
            indeks[count] = i;
            count++;
        }
    }

    if (count == 0) {
        printf("Tidak ditemukan pesanan dengan harga tersebut.\n");
        return;
    }

    int number;

    if (count == 1) {
        number = indeks[0];
        printf("Pesanan ditemukan: %s | Harga: %d. Menghapus langsung...\n", h->data[number].name, harga);
    } else {
        printf("Ditemukan %d pesanan dengan harga %d:\n", count, harga);
        for (int i = 0; i < count; i++) {
            printf("%d. %s\n", i + 1, daftar[i]);
        }

        int pilihan;
        do {
            printf("Pilih nomor pesanan yang ingin dihapus: ");
            scanf("%d", &pilihan);
        } while (pilihan < 1 || pilihan > count);

        number = indeks[pilihan - 1];
    }

    printf("Menghapus pesanan: %s | Harga: Rp. %d\n", h->data[number].name, h->data[number].harga);
    h->data[number] = h->data[--h->size];

    int i = number;
    while (1) {
        int left = 2 * i + 1, right = 2 * i + 2, largest = i;
        if (left < h->size && h->data[left].harga > h->data[largest].harga) largest = left;
        if (right < h->size && h->data[right].harga > h->data[largest].harga) largest = right;
        if (largest == i) break;

        HeapNode temp = h->data[i];
        h->data[i] = h->data[largest];
        h->data[largest] = temp;
        i = largest;
    }
}

void tampilKeranjangheap(Heap* h) {
    if (h->size == 0) {
        printf("Keranjang kosong.\n");
        return;
    }

    printf("=========== Daftar Pesanan (Heap) ===========\n");
    for (int i = 0; i < h->size; i++) {
        printf("- %s | Harga: Rp. %d\n", h->data[i].name, h->data[i].harga);
    }
    printf("=============================================\n");
}

void totalHargaheap(Heap* h) {
    int total = 0;
    for (int i = 0; i < h->size; i++) {
        total += h->data[i].harga;
    }
    printf("Total harga: Rp. %d\n", total);
}
void checkoutheap(Heap* h) {
    if (h->size == 0) {
        printf("Keranjang kosong!\n");
        return;
    }

    int metode;
    char metodePembayaran[50];

    printf("\n=== Pilih Metode Pembayaran ===\n");
    printf("1. Tunai\n2. Kartu Kredit/Debit\n3. E-Wallet\nPilihan: ");
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

    printf("Pesanan berhasil dibayar dengan %s.\n", metodePembayaran);
    h->size = 0;
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
    for (i = 0; i < 6; i++)
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
    BSTNode *keranjang = NULL;
    Heap keranjangHeap;
    int choice, pilih, sortedFlag = 0;
    printf("====== Welcome To Pizza Hut (Food And Drink Ordering) =======\n");
    pizzaForm();
    menuMakanan(makanan, minuman);
    printf("Mau makan ditempat(0) atau take away(1)\nMasukkan pilihan anda : ");
    scanf("%d",&pilih);
    if (pilih == 0){
        while (1) {
            choice = printMenu();
            switch (choice) {
                case 1:
                    tampilkanMenuAwal(makanan, minuman, &sortedFlag);
                    break;

                case 2:
                    keranjang = tambahPesananbst(makanan, minuman, keranjang);
                    break;

                case 3:
                    keranjang = hapusPesananInputbst(keranjang);
                    break;

                case 4:
                    printf("=== Keranjang Anda ===\n");
                    tampilKeranjangbst(keranjang);
                    totalHargabst(keranjang);
                    break;

                case 5:
                    checkoutbst(&keranjang);
                    keranjang = NULL;
                    break;
                case 6:
                    printf("Terima kasih telah menggunakan aplikasi kami!!!\n");
                    freeKeranjang(keranjang);
                    return 0;

                default:
                    printf("Masukkan pilihan yang benar!\n\n");
            }
        }
    }else if(pilih == 1){
        keranjangHeap.size = 0;
        while (1) {
            choice = printMenu();
            switch (choice) {
                case 1:
                    tampilkanMenuAwal(makanan, minuman, &sortedFlag);
                    break;

                case 2:
                    tambahPesananheap(makanan, minuman, &keranjangHeap);
                    break;

                case 3:
                    hapusPesananHeap(&keranjangHeap);
                    break;

                case 4:
                    printf("=== Keranjang Anda ===\n");
                    tampilKeranjangheap(&keranjangHeap);
                    totalHargaheap(&keranjangHeap);
                    break;

                case 5:
                    checkoutheap(&keranjangHeap);
                    break;
                case 6:
                    printf("Terima kasih telah menggunakan aplikasi kami!!!\n");
                    return 0;
                default:
                    printf("Masukkan pilihan yang benar!\n\n");
            }
        }
    } else{
        printf("pilihan tidak valid!");
        return 0;
    }
}
