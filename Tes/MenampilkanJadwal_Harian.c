#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "MenampilkanJadwal_Harian.h"
// jadwal harian
void tampilkanJadwal_Harian(hari* head) {
    int nomorHari;
    printf("\n╔════════════════════════════════════════════════════╗");
    printf("\n║               📅 TAMPILKAN JADWAL HARIAN           ║");
    printf("\n╚════════════════════════════════════════════════════╝");
    printf("\nMasukkan nomor hari (1 - 30): ");
    scanf("%d", &nomorHari);

    if (nomorHari < 1) {
        printf("❌ Error: Nomor hari tidak valid.\n");
        return;
    }

    // Hitung indeks dalam 7 hari (0 sampai 6)
    int indeks = (nomorHari - 1) % 7;

    // Akses node ke-indeks dari linked list
    hari* current = head;
    for (int i = 0; i < indeks; i++) {
        if (current->next != NULL)
            current = current->next;
    }

    // Header
    printf("\n╔════════════════════════════════════════════════════╗");
    printf("\n║             🗓️  JADWAL UNTUK HARI KE-%-3d          ║", nomorHari);
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
