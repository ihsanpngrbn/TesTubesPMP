#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "Data_Dokter.csv"

typedef struct {
    int ID;
    char Nama[50];
    int PrefShift;
    int MaxShift;
} Dokter;

Dokter data[MAX];
int jumlah = 0;

// Fungsi untuk membaca file CSV
void bacaFile() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Gagal membuka file.\n");
        return;
    }

    jumlah = 0;
    char baris[100];
    fgets(baris, sizeof(baris), file); // Skip header

    while (fgets(baris, sizeof(baris), file)) {
        sscanf(baris, "%d,%49[^,],%d,%d", 
            &data[jumlah].ID, 
            data[jumlah].Nama, 
            &data[jumlah].PrefShift, 
            &data[jumlah].MaxShift);
        jumlah++;
    }

    fclose(file);
}

// Fungsi untuk menyimpan data ke CSV
void simpanFile() {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Gagal menyimpan file.\n");
        return;
    }

    fprintf(file, "ID,Nama,PrefShift,MaxShift\n");
    for (int i = 0; i < jumlah; i++) {
        fprintf(file, "%d,%s,%d,%d\n",
                data[i].ID, data[i].Nama,
                data[i].PrefShift, data[i].MaxShift);
    }

    fclose(file);
}

// Menampilkan daftar dokter
void tampilkanData() {
    printf("\n+===========================================================+\n");
    printf("|                      DAFTAR DOKTER                        |\n");
    printf("+=====+=======================+=============+===============+\n");
    printf("| ID  | Nama Dokter           | Max Shift   | Pref. Shift   |\n");
    printf("+=====+=======================+=============+===============+\n");
    for (int i = 0; i < jumlah; i++) {
        printf("| %-3d | %-21s | %-11d | %-13d |\n",
               data[i].ID,
               data[i].Nama,
               data[i].MaxShift,
               data[i].PrefShift);
    }
    if (jumlah == 0) {
        printf("|     Tidak ada data dokter yang tersedia.                |\n");
    }
    printf("+=====+=======================+=============+===============+\n");
}

// Menambahkan data dokter
void tambahDokter() {
    if (jumlah >= MAX) {
        printf("Data penuh. Tidak dapat menambah dokter baru.\n");
        return;
    }

    printf("\n+---------------------------+\n");
    printf("|        TAMBAH DOKTER      |\n");
    printf("+---------------------------+\n");

    printf("Masukkan nama dokter: ");
    scanf(" %[^\n]", data[jumlah].Nama);

    printf("Masukkan maksimal shift per minggu [1-21]: ");
    scanf("%d", &data[jumlah].MaxShift);

    printf(
        "Masukkan preferensi shift (0–6):\n"
        "  0 = Pagi\n"
        "  1 = Siang\n"
        "  2 = Malam\n"
        "  3 = Pagi + Siang\n"
        "  4 = Pagi + Malam\n"
        "  5 = Siang + Malam\n"
        "  6 = Bebas\n"
        "Pilihan: "
    );
    scanf("%d", &data[jumlah].PrefShift);

    if (data[jumlah].PrefShift < 0 || data[jumlah].PrefShift > 6) {
        printf("Input preferensi tidak valid. Dokter tidak ditambahkan.\n");
        return;
    }

    data[jumlah].ID = jumlah + 1;
    jumlah++;

    simpanFile();
    printf("Data dokter berhasil ditambahkan.\n");
}

// Menghapus dokter berdasarkan nama
void hapusDokter() {
    char nama[50];

    printf("\n+---------------------------+\n");
    printf("|        HAPUS DOKTER       |\n");
    printf("+---------------------------+\n");

    printf("Masukkan nama dokter yang ingin dihapus: "); 
    scanf(" %[^\n]", nama);

    int index = -1;
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(data[i].Nama, nama) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Dokter \"%s\" tidak ditemukan.\n", nama);
        return;
    }

    for (int i = index; i < jumlah - 1; i++) {
        data[i] = data[i + 1];
    }
    jumlah--;

    // Perbarui ulang ID agar tetap urut
    for (int i = 0; i < jumlah; i++) {
        data[i].ID = i + 1;
    }

    simpanFile();
    printf("Data dokter \"%s\" berhasil dihapus.\n", nama);
}
