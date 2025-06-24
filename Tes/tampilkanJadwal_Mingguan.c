#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tampilkanJadwal_Mingguan.h"

#define JADWAL_FILE_NAME "Jadwal_Dokter.csv"

typedef struct {
    int tanggal;
    char shift[10];     
    int slot;
    int id_dokter;
    char nama_dokter[50];
} JadwalEntry;

void tampilkanJadwal_Mingguan() {
    printf("\n+----------------------------------------------------+");
    printf("\n|             JADWAL DOKTER MINGGUAN                 |");
    printf("\n+----------------------------------------------------+");

    FILE *file = fopen(JADWAL_FILE_NAME, "r");
    if (!file) {
        perror("Error: Gagal membuka file Jadwal_Dokter.csv");
        printf("Pastikan file '%s' ada di direktori yang sama dengan executable.\n", JADWAL_FILE_NAME);
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file); // Lewati baris header baris pertama dari CSV

    // Siapkan penyimpanan sementara untuk data jadwal 7 hari
    // schedule_data[day_index][shift_type_index][slot_index][string_buffer]
    // shift_type_index: 0=Pagi, 1=Siang, 2=Malam
    // slot_index: 0-4
    char schedule_data[7][3][5][64]; // [hari][jenis_shift][slot_ke][string_dokter]

    // Inisialisasi semua slot sebagai "[Kosong]"
    for(int d = 0; d < 7; d++) {
        for(int s = 0; s < 3; s++) {
            for(int i = 0; i < 5; i++) {
                strcpy(schedule_data[d][s][i], "- [Kosong]");
            }
        }
    }

    // Baca dan parse file CSV untuk mengisi data mingguan
    while (fgets(line, sizeof(line), file) != NULL) {
        JadwalEntry entry;
        // Gunakan koma (,) sebagai delimiter sesuai format Jadwal_Dokter.csv
        int items_parsed = sscanf(line, "%d,%[^,],%d,%d,%[^\n]",
                                  &entry.tanggal,
                                  entry.shift,
                                  &entry.slot,
                                  &entry.id_dokter,
                                  entry.nama_dokter);

        // Hanya proses data untuk tanggal 1-7 yang relevan untuk jadwal mingguan
        if (items_parsed >= 4 && entry.tanggal >= 1 && entry.tanggal <= 7) {
            char doc_info[64];
            if (items_parsed == 5) { // Jika ada nama dokter
                snprintf(doc_info, sizeof(doc_info), "- %s (ID:%d)", entry.nama_dokter, entry.id_dokter);
            } else { // Jika nama dokter kosong (slot kosong)
                strcpy(doc_info, "- [Kosong]");
            }

            int shift_idx = -1;
            if (strcmp(entry.shift, "Pagi") == 0) shift_idx = 0;
            else if (strcmp(entry.shift, "Siang") == 0) shift_idx = 1;
            else if (strcmp(entry.shift, "Malam") == 0) shift_idx = 2;

            if (shift_idx != -1 && entry.slot >= 1 && entry.slot <= 5) {
                // Simpan info dokter ke posisi yang benar di array schedule_data
                strcpy(schedule_data[entry.tanggal - 1][shift_idx][entry.slot - 1], doc_info);
            }
        }
    }
    fclose(file); 
    const char* namaHari[7] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};
    const char* namaShift[3] = {"Pagi", "Siang", "Malam"};

    for (int d = 0; d < 7; d++) { // Loop untuk 7 hari
        printf("\n\n+----------------------------------------------------+");
        printf("\n|  Hari: %-8s                                       |", namaHari[d], d + 1);
        printf("\n+----------------------------------------------------+");

        for (int s = 0; s < 3; s++) { // Loop untuk 3 shift
            printf("\n-- SHIFT %s\n", namaShift[s]);
            printf("----------------------------------------------------\n");
            for (int i = 0; i < 5; i++) { // Loop untuk 5 slot
                printf("%s\n", schedule_data[d][s][i]);
            }
        }
    }
    printf("\n\n----------------------------------------------------\n");
}
