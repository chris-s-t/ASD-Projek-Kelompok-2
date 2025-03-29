#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct menuStruct
{
    char name[50];
    int harga;
    struct menuStruct *next;
} menuStruct;

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
    printf("\nMenampilkan Menu Makanan\n");
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
            printf("|%-2d| %-40s | Rp. %-6d |   ============================================================\n", i, makanan[i].name, makanan[i].harga);
        }
        else
        {
            printf("|%-2d| %-40s | Rp. %-6d |\n", i + 1, makanan[i].name, makanan[i].harga);
        }
    }
    printf("============================================================\n\n");
}

// Menambahkan pesanan ke keranjang
void tambahpesanan(menuStruct **head, menuStruct **tail, menuStruct makanan[], menuStruct minuman[])
{
    int choice, pilih;
    menuStruct *node;
    node = (menuStruct *)malloc(sizeof(menuStruct));
    if (!node)
    {
        printf("Gagal mengalokasikan memori!\n");
        return;
    }
    printf("mau (1)makanan atau (2)minuman : ");
    scanf("%d", &choice);
    getchar();
    if (choice == 1)
    {
        printf("masukan makanan pilihan anda : ");
        scanf("%d", &pilih);
        getchar();
        if (pilih > 40 || pilih < 1)
        {
            printf("masukan pilihan yang benar!");
            return;
        }
        strcpy(node->name, makanan[pilih - 1].name);
        node->harga = makanan[pilih - 1].harga;
    }
    else if (choice == 2)
    {
        printf("masukan minuman pilihan anda : ");
        scanf("%d", &pilih);
        getchar();
        if (pilih > 15 || pilih < 1)
        {
            printf("masukan pilihan yang benar!");
            return;
        }
        strcpy(node->name, minuman[pilih - 1].name);
        node->harga = minuman[pilih - 1].harga;
    }
    else
    {
        printf("masukan pilihan yang benar!");
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
void tambahdana(int *dana)
{
    int tambah = 0;
    printf("Input dana: Rp. ");
    scanf("%d", &tambah);
    *dana += tambah;
    printf("\n");
}
void hapuspesanan(menuStruct **head, menuStruct **tail)
{
    if (*head == NULL)
    {
        printf("Belum ada pesanan yang terisi\n");
        return;
    }
    menuStruct *temp = *head;
    int i = 1, del;
    printf("Keranjang anda:\n");
    while (temp != NULL)
    {
        printf("%d. %s\n", i, temp->name);
        temp = temp->next;
        i++;
    }
    printf("Hapus pesanan no: ");
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
void totalharga(menuStruct **head, int *total)
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
void metodepembayaran(int *dana, int total)
{
    int choice;
    while (1)
    {
        printf("Total harga: Rp. %d\nTotal dana: Rp. %d\nMetode pembayaran\n1. Cash\n2. Credit\n3. Tambah credit\n4. Kembali\nPilih metode pembayaran : ", total, *dana);
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            printf("Pembayaran: Cash\nTerima kasih atas pesananya!\n\n\n");
            return;
        }
        case 2:
        {
            if (*dana < total)
            {
                printf("Dana tidak cukup, silahkan isi dana atau pilih metode lain.\n\n");
                break;
            }
            printf("Pembayaran: Credit\nTerima kasih atas pesananya!\n\n\n");
            return;
        }
        case 3:
        {
            tambahdana(&*dana);
            break;
        }
        case 4:
        {
            printf("\n\n");
            return;
        }
        }
    }
}
// Menampilkan isi keranjang
void tampilkeranjang(menuStruct **head)
{
    menuStruct *temp = *head;
    int i = 1;
    printf("\nkeranjang anda :\n");
    while (temp != NULL)
    {
        printf("%d. %s\n", i, temp->name);
        temp = temp->next;
        i++;
    }
    printf("\n\n");
}

void checkhistory()
{
    FILE *fp = fopen("history.txt", "r");
    if (!fp)
    {
        printf("Belum ada riwayat pesanan.\n");
        return;
    }

    printf("\n===== Riwayat Pesanan =====\n");

    char line[100];
    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    printf("===========================\n");
    fclose(fp);
}

void checkout(menuStruct **head, menuStruct **tail)
{
    static int historyCount = 1;
    FILE *fp = fopen("history.txt", "a");

    if (!fp)
    {
        printf("Gagal membuka history.txt untuk checkout!\n");
        return;
    }

    if (*head == NULL)
    {
        printf("Keranjang kosong! Silahkan pesan makanan atau minuman terlebih dahulu.\n");
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

    fprintf(fp, "\n===== History %d =====\n", historyCount);
    fprintf(fp, "Metode Pembayaran: %s\n", metodePembayaran);
    fprintf(fp, "Daftar Pesanan:\n");

    menuStruct *current = *head;
    while (current)
    {
        fprintf(fp, "- %s \t(Rp. %d)\n", current->name, current->harga);
        totalHarga += current->harga;
        current = current->next;
    }

    fprintf(fp, "Total Harga: Rp. %d\n", totalHarga);
    fclose(fp);
    historyCount++;

    while (*head)
    {
        menuStruct *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *tail = NULL;

    printf("\nCheckout berhasil!\n");
    printf("Total: Rp. %d\n", totalHarga);
    printf("Metode: %s\n", metodePembayaran);
}

// Menampilkan menu utama
int printMenu()
{
    int i, choice;
    char menu[][25] = {"Tampilkan Menu",
                       "Tambah Pesanan",
                       "Hapus Pesanan",
                       "Total Harga",
                       "Check History Pesanan",
                       "Cek Keranjang",
                       "Checkout"};

    printf("\nWelcome To Pizza Hut (Food And Drinks Ordering)\n");

    for (i = 0; i < 7; i++)
    {
        printf("%d. %s\n", i + 1, menu[i]);
    }

    printf("Masukkan pilihan anda : ");
    scanf("%d", &choice);
    getchar();

    return choice;
}

// Main
int main()
{
    menuStruct makanan[40], minuman[40], *head, *tail;
    head = tail = NULL;
    menuMakanan(makanan, minuman);
    int choice, i = 0, dana = 0, total = 0;
    char orderType[20];

    while (1)
    {
        choice = printMenu();
        switch (choice)
        {
        case 1:
        {
            tampilkanMenu(makanan, minuman);
            break;
        }
        case 2:
        {
            tambahpesanan(&head, &tail, makanan, minuman);
            break;
        }
        case 3:
        {
            hapuspesanan(&head, &tail);
            break;
        }
        case 4:
        {
            totalharga(&head, &total);
            break;
        }
        case 5:
        {
            metodepembayaran(&dana, total);
            break;
        }
        case 6:
        {
            checkhistory();
            break;
        }
        case 7:
        {
            tampilkeranjang(&head);
            break;
        }
        case 8:
        {
            checkout(&head, &tail);
            break;
        }
        case 9:
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
