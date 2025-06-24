#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tampilkan_jumlah_shift.h"

#define JADWAL_FILE_NAME "Jadwal_Dokter.csv"
#define MAX_UNIQUE_DOCTORS 100 

typedef struct {
    int id;
    char nama[50];
    int totalShiftCount;
} DoctorShiftSummary;

void tampilkan_jumlah_shift() {
    printf("\n+----------------------------------------------------+");
    printf("\n|           TOTAL SHIFT MASING-MASING DOKTER         |");
    printf("\n+----------------------------------------------------+");

    FILE *file = fopen(JADWAL_FILE_NAME, "r");
    if (!file) {
        perror("Error: Gagal membuka file Jadwal_Dokter.csv");
        printf("Pastikan file '%s' ada di direktori yang sama dengan executable.\n", JADWAL_FILE_NAME);
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file); // skip header 

    DoctorShiftSummary summaries[MAX_UNIQUE_DOCTORS];
    int numSummaries = 0; // Jumlah dokter berbeda

    while (fgets(line, sizeof(line), file) != NULL) {
        int tanggal, slot, id_dokter;
        char shift[10], nama_dokter[50];
        
        // Parse baris CSV: Tanggal,Shift,Slot,ID_Dokter,Nama_Dokter
        // Menggunakan koma (,) sebagai delimiter
        int items_parsed = sscanf(line, "%d,%[^,],%d,%d,%[^\n]",
                                  &tanggal,
                                  shift,
                                  &slot,
                                  &id_dokter,
                                  nama_dokter);
        
        if (items_parsed >= 4 && id_dokter > 0) {
            // Cari apakah ID dokter ini sudah ada di daftar ringkasan
            int found_idx = -1;
            for (int i = 0; i < numSummaries; i++) {
                if (summaries[i].id == id_dokter) {
                    found_idx = i;
                    break;
                }
            }

            if (found_idx != -1) {
                summaries[found_idx].totalShiftCount++;
            } else {
                if (numSummaries < MAX_UNIQUE_DOCTORS) {
                    summaries[numSummaries].id = id_dokter;
                    // Salin nama dokter, pastikan tidak overflow
                    strncpy(summaries[numSummaries].nama, nama_dokter, sizeof(summaries[numSummaries].nama) - 1);
                    summaries[numSummaries].nama[sizeof(summaries[numSummaries].nama) - 1] = '\0';
                    summaries[numSummaries].totalShiftCount = 1; // Shift pertama untuk dokter ini
                    numSummaries++;
                } else {
                    fprintf(stderr, "Peringatan: Melebihi batas MAX_UNIQUE_DOCTORS (%d). Beberapa shift mungkin tidak terhitung.\n", MAX_UNIQUE_DOCTORS);
                }
            }
        }
    }
    fclose(file); 

    if (numSummaries == 0) {
        printf("\nTidak ada data shift dokter yang ditemukan di '%s'.\n", JADWAL_FILE_NAME);
        return;
    }

    printf("\nID\tNama Dokter\t\tTotal Shift\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < numSummaries; i++) {
        printf("%d\t%-15s\t%d\n", summaries[i].id, summaries[i].nama, summaries[i].totalShiftCount);
    }
    printf("----------------------------------------------------\n");
}
