#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JADWAL_FILE_NAME "Jadwal_Dokter.csv"

typedef struct {
    int tanggal;
    char shift[10];
    int slot;
    int id_dokter;
    char nama_dokter[50];
} JadwalEntry;

void tampilkanJadwal_Harian() {
    int tanggalCari;
    printf("\n+----------------------------------------------------+");
    printf("\n|             TAMPILKAN JADWAL HARIAN                |");
    printf("\n+----------------------------------------------------+");
    printf("\nMasukkan tanggal yang ingin ditampilkan (1 - 30): ");
    scanf("%d", &tanggalCari);

    if (tanggalCari < 1) {
        printf("X Error: Tanggal tidak valid.\n");
        return;
    }

    int mapped_tanggal = ((tanggalCari - 1) % 7) + 1;

    FILE *file = fopen(JADWAL_FILE_NAME, "r");
    if (!file) {
        perror("Error: Gagal membuka file Jadwal_Dokter.csv");
        printf("Pastikan file '%s' ada di direktori yang sama dengan executable.\n", JADWAL_FILE_NAME);
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file); // Skip header

    char pagi_docs[5][64];
    char siang_docs[5][64];
    char malam_docs[5][64];

    for(int i = 0; i < 5; i++) {
        strcpy(pagi_docs[i], "- [Kosong]");
        strcpy(siang_docs[i], "- [Kosong]");
        strcpy(malam_docs[i], "- [Kosong]");
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        JadwalEntry entry;
        int items_parsed = sscanf(line, "%d,%[^,],%d,%d,%[^\n]",
                                  &entry.tanggal,
                                  entry.shift,
                                  &entry.slot,
                                  &entry.id_dokter,
                                  entry.nama_dokter);
        
        if (items_parsed >= 4 && entry.tanggal == mapped_tanggal) {
            char doc_info[64];
            if (items_parsed == 5) {
                snprintf(doc_info, sizeof(doc_info), "- %s (ID:%d)", entry.nama_dokter, entry.id_dokter);
            } else {
                strcpy(doc_info, "- [Kosong]");
            }

            if (strcmp(entry.shift, "Pagi") == 0 && entry.slot >= 1 && entry.slot <= 5) {
                strcpy(pagi_docs[entry.slot - 1], doc_info);
            } else if (strcmp(entry.shift, "Siang") == 0 && entry.slot >= 1 && entry.slot <= 5) {
                strcpy(siang_docs[entry.slot - 1], doc_info);
            } else if (strcmp(entry.shift, "Malam") == 0 && entry.slot >= 1 && entry.slot <= 5) {
                strcpy(malam_docs[entry.slot - 1], doc_info);
            }
        }
    }
    fclose(file);

    printf("\n+----------------------------------------------------+");
    printf("\n|                  JADWAL TANGGAL %-3d                |", tanggalCari);
    printf("\n+----------------------------------------------------+");

    printf("\n\n-- SHIFT PAGI\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", pagi_docs[i]);
    }

    printf("\n-- SHIFT SIANG\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", siang_docs[i]);
    }

    printf("\n-- SHIFT MALAM\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", malam_docs[i]);
    }

    printf("----------------------------------------------------\n");
}
