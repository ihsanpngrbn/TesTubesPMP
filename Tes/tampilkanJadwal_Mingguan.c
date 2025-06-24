#include "program_buat_jadwal.h"

void tampilkanJadwal_Mingguan() {
    const char* namaHari[7] = {
        "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"
    };

    printf("\n╔════════════════════════════════════════════════════╗");
    printf("\n║             📅 JADWAL DOKTER MINGGUAN              ║");
    printf("\n╚════════════════════════════════════════════════════╝");

    jadwal* current = head_jadwal;

    for (int h = 0; h < 7 && current != NULL; h++) {
        printf("\n\n╔════════════════════════════════════════════════════╗");
        printf("\n║  📌 HARI: %-8s | TANGGAL: %-2d                   ║", namaHari[h], current->tanggal);
        printf("\n╚════════════════════════════════════════════════════╝");

        // SHIFT PAGI
        printf("\n🕗 SHIFT PAGI\n");
        printf("────────────────────────────────────────────────────\n");
        for (int i = 0; i < 5; i++) {
            if (current->pagi[i]) {
                printf("• %s (ID:%d)\n", current->pagi[i]->nama, current->pagi[i]->id);
            } else {
                printf("• [Kosong]\n");
            }
        }

        // SHIFT SIANG
        printf("\n🕛 SHIFT SIANG\n");
        printf("────────────────────────────────────────────────────\n");
        for (int i = 0; i < 5; i++) {
            if (current->siang[i]) {
                printf("• %s (ID:%d)\n", current->siang[i]->nama, current->siang[i]->id);
            } else {
                printf("• [Kosong]\n");
            }
        }

        // SHIFT MALAM
        printf("\n🕖 SHIFT MALAM\n");
        printf("────────────────────────────────────────────────────\n");
        for (int i = 0; i < 5; i++) {
            if (current->malam[i]) {
                printf("• %s (ID:%d)\n", current->malam[i]->nama, current->malam[i]->id);
            } else {
                printf("• [Kosong]\n");
            }
        }

        current = current->next;
    }

    printf("\n\n====================================================\n");
}
