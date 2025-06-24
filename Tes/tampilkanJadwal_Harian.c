#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tampilkanJadwal_Harian.h"
// jadwal harian
void tampilkanJadwal_Harian(jadwal* head_jadwal) {
    int tanggalCari;
    printf("\n╔════════════════════════════════════════════════════╗");
    printf("\n║               📅 TAMPILKAN JADWAL HARIAN           ║");
    printf("\n╚════════════════════════════════════════════════════╝");
    printf("\nMasukkan tanggal yang ingin ditampilkan (1 - 30): ");
    scanf("%d", &tanggalCari);

    if (tanggalCari < 1 || tanggalCari > 30) {
        printf("❌ Error: Tanggal tidak valid.\n");
        return;
    }

    // Cari node dengan tanggal sesuai
    jadwal* current = head_jadwal;
    while (current != NULL && current->tanggal != tanggalCari) {
        current = current->next;
    }

    if (!current) {
        printf("❌ Jadwal untuk tanggal %d tidak ditemukan.\n", tanggalCari);
        return;
    }

    // Header
    printf("\n╔════════════════════════════════════════════════════╗");
    printf("\n║             🗓️  JADWAL UNTUK TANGGAL %-3d           ║", tanggalCari);
    printf("\n╚════════════════════════════════════════════════════╝");

    char buffer[64];

    // Shift Pagi
    printf("\n\n🔹 SHIFT PAGI\n");
    printf("────────────────────────────────────────────────────\n");
    for (int i = 0; i < 5; i++) {
        if (current->pagi[i]) {
            snprintf(buffer, sizeof(buffer), "• %s (ID:%d)", current->pagi[i]->nama, current->pagi[i]->id);
            printf("%-50s\n", buffer);
        } else {
            printf("• [Kosong]\n");
        }
    }

    // Shift Siang
    printf("\n🔸 SHIFT SIANG\n");
    printf("────────────────────────────────────────────────────\n");
    for (int i = 0; i < 5; i++) {
        if (current->siang[i]) {
            snprintf(buffer, sizeof(buffer), "• %s (ID:%d)", current->siang[i]->nama, current->siang[i]->id);
            printf("%-50s\n", buffer);
        } else {
            printf("• [Kosong]\n");
        }
    }

    // Shift Malam
    printf("\n🌙 SHIFT MALAM\n");
    printf("────────────────────────────────────────────────────\n");
    for (int i = 0; i < 5; i++) {
        if (current->malam[i]) {
            snprintf(buffer, sizeof(buffer), "• %s (ID:%d)", current->malam[i]->nama, current->malam[i]->id);
            printf("%-50s\n", buffer);
        } else {
            printf("• [Kosong]\n");
        }
    }

    printf("────────────────────────────────────────────────────\n");
}
