#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tampilkanJadwal_Bulanan.h" 

#define JADWAL_FILE_NAME "Jadwal_Dokter.csv"

#define TOTAL_MONTH_DAYS 30   // Total hari dalam bulan yang ditampilkan
#define DAYS_IN_CYCLE 7       // Siklus hari (Senin-Minggu)
#define SHIFTS_PER_DAY 3      // Pagi, Siang, Malam
#define SLOTS_PER_SHIFT 5     // Jumlah slot per shift

typedef struct {
    int tanggal;
    char shift[10];      
    int slot;
    int id_dokter;
    char nama_dokter[50];
} JadwalEntry;

void tampilkanJadwal_Bulanan() {
    printf("\n+----------------------------------------------------+");
    printf("\n|             JADWAL DOKTER BULANAN                  |");
    printf("\n+----------------------------------------------------+");

    FILE *file = fopen(JADWAL_FILE_NAME, "r");
    if (!file) {
        perror("Error: Gagal membuka file Jadwal_Dokter.csv");
        printf("Pastikan file '%s' ada di direktori yang sama dengan executable.\n", JADWAL_FILE_NAME);
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file); // Skip header baris pertama dari CSV

    // Penyimpanan sementara untuk DATA SUMBER 7 hari saja dari CSV
    // schedule_data_source[day_index_0_to_6][shift_type_index][slot_index][string_buffer]
    char schedule_data_source[DAYS_IN_CYCLE][SHIFTS_PER_DAY][SLOTS_PER_SHIFT][64];

    // Inisialisasi semua slot sebagai "[Kosong]" untuk 7 hari sumber
    for(int d = 0; d < DAYS_IN_CYCLE; d++) {
        for(int s = 0; s < SHIFTS_PER_DAY; s++) {
            for(int i = 0; i < SLOTS_PER_SHIFT; i++) {
                strcpy(schedule_data_source[d][s][i], "- [Kosong]");
            }
        }
    }

    // Baca dan parse file CSV untuk mengisi data SUMBER 7 hari
    while (fgets(line, sizeof(line), file) != NULL) {
        JadwalEntry entry;
        // Gunakan koma (,) sebagai delimiter
        int items_parsed = sscanf(line, "%d,%[^,],%d,%d,%[^\n]",
                                  &entry.tanggal,
                                  entry.shift,
                                  &entry.slot,
                                  &entry.id_dokter,
                                  entry.nama_dokter);
        
        // Hanya ambil data untuk hari ke-1 sampai hari ke-7 dari CSV
        if (items_parsed >= 4 && entry.tanggal >= 1 && entry.tanggal <= DAYS_IN_CYCLE) {
            char doc_info[64];
            if (items_parsed == 5) { // Jika ada nama dokter (slot terisi)
                snprintf(doc_info, sizeof(doc_info), "- %s (ID:%d)", entry.nama_dokter, entry.id_dokter);
            } else { // Jika nama dokter kosong (slot tidak terisi)
                strcpy(doc_info, "- [Kosong]");
            }

            int shift_idx = -1;
            if (strcmp(entry.shift, "Pagi") == 0) shift_idx = 0;
            else if (strcmp(entry.shift, "Siang") == 0) shift_idx = 1;
            else if (strcmp(entry.shift, "Malam") == 0) shift_idx = 2;

            if (shift_idx != -1 && entry.slot >= 1 && entry.slot <= SLOTS_PER_SHIFT) {
                // Simpan info dokter ke posisi yang benar di array sumber (0-indexed)
                strcpy(schedule_data_source[entry.tanggal - 1][shift_idx][entry.slot - 1], doc_info);
            }
        }
    }
    fclose(file); // Tutup file setelah selesai membaca

    // Array nama hari untuk siklus 7 hari (misal: hari ke-1 adalah Senin)
    const char* namaHari[DAYS_IN_CYCLE] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};

    // Lebar kolom untuk formatting (sesuaikan agar rapi di terminal Anda)
    const int COLUMN_WIDTH = 45; // Lebar konten dalam kolom

    // Tampilkan jadwal bulanan dalam dua kolom
    // Loop untuk setiap pasangan hari (misal: Hari 1 & 16, Hari 2 & 17, dst.)
    for (int i = 0; i < TOTAL_MONTH_DAYS / 2; i++) {
        int day1_num = i + 1; // Nomor hari untuk kolom kiri (1, 2, ..., 15)
        int day2_num = i + 1 + TOTAL_MONTH_DAYS / 2; // Nomor hari untuk kolom kanan (16, 17, ..., 30)

        // Tentukan indeks data sumber dari schedule_data_source (0-6) untuk kolom kiri
        // Dengan ((day_num - 1) % DAYS_IN_CYCLE) akan secara otomatis memetakan
        // 1->0, 8->0, 29->0 (untuk hari ke-1)
        // 2->1, 9->1, 30->1 (untuk hari ke-2)
        int source_idx_day1 = (day1_num - 1) % DAYS_IN_CYCLE;

        // Tentukan indeks data sumber untuk kolom kanan
        int source_idx_day2 = -1; // Inisialisasi -1 jika kolom kanan tidak ada
        if (day2_num <= TOTAL_MONTH_DAYS) { // Pastikan hari kedua masih dalam rentang bulan
            source_idx_day2 = (day2_num - 1) % DAYS_IN_CYCLE;
        }

        // Tentukan nama hari dalam siklus 7 hari untuk ditampilkan di header
        int hari_ke_idx_day1 = (day1_num - 1) % DAYS_IN_CYCLE;
        int hari_ke_idx_day2 = (day2_num - 1) % DAYS_IN_CYCLE;

        printf("\n\n"); // Baris kosong antar pasangan hari

        // Batas atas kolom
        printf("+--------------------------------------------+   ");
        if (day2_num <= TOTAL_MONTH_DAYS) {
            printf("+--------------------------------------------+\n");
        } else {
            printf("\n");
        }

        // Header kolom: Tanggal dan Nama Hari
        printf("| Tanggal %-2d                      |   ", day1_num);
        if (day2_num <= TOTAL_MONTH_DAYS) {
            printf("| Tanggal %-2d                      |\n", day2_num);
        } else {
            printf("\n");
        }
        
        // Batas tengah setelah header
        printf("+--------------------------------------------+   ");
        if (day2_num <= TOTAL_MONTH_DAYS) {
            printf("+--------------------------------------------+\n");
        } else {
            printf("\n");
        }

        // Tampilkan detail shift untuk kedua kolom
        for (int s = 0; s < SHIFTS_PER_DAY; s++) {
            printf("| %-42s |   ", s == 0 ? "SHIFT Pagi" : (s == 1 ? "SHIFT Siang" : "SHIFT Malam"));
            if (day2_num <= TOTAL_MONTH_DAYS) {
                printf("| %-42s |\n", s == 0 ? "SHIFT Pagi" : (s == 1 ? "SHIFT Siang" : "SHIFT Malam"));
            } else {
                printf("\n");
            }
            printf("|--------------------------------------------|   ");
            if (day2_num <= TOTAL_MONTH_DAYS) {
                printf("|--------------------------------------------|\n");
            } else {
                printf("\n");
            }

            for (int slot = 0; slot < SLOTS_PER_SHIFT; slot++) {
                // Konten kolom kiri
                printf("| %-42s |   ", schedule_data_source[source_idx_day1][s][slot]);

                // Konten kolom kanan (jika ada)
                if (day2_num <= TOTAL_MONTH_DAYS) {
                    printf("| %-42s |\n", schedule_data_source[source_idx_day2][s][slot]);
                } else {
                    printf("\n");
                }
            }
            // Batas bawah untuk setiap blok shift
            printf("+--------------------------------------------+   ");
            if (day2_num <= TOTAL_MONTH_DAYS) {
                printf("+--------------------------------------------+\n");
            } else {
                printf("\n");
            }
        }
    }
    printf("\n===================================================================================================\n");
}
