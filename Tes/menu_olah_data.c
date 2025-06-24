#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "olah_data.h"

void menu_olah_data() {
    bacaFile();
    int pilihan;
    
    while (1) {
        printf("\n+===========================================+\n");
        printf("|              OLAH DATA DOKTER            |\n");
        printf("+===========================================+\n");
        printf("| 1. Tambah Dokter                         |\n");
        printf("| 2. Hapus Dokter                          |\n");
        printf("| 3. Tampilkan Daftar Dokter               |\n");
        printf("| 4. Kembali ke Menu Utama                 |\n");
        printf("+===========================================+\n");
        printf("Pilih Menu (1 - 4): ");
        scanf("%d", &pilihan);
        printf("\n");
        
        switch (pilihan) {
            case 1:
                tambahDokter();
                break;
                
            case 2:
                hapusDokter();
                break;
                
            case 3:
                tampilkanData();
                break;
                
            case 4:
                printf("Kembali ke menu utama\n");
                return;
                
            default:
                printf("Pilihan tidak valid. Masukkan angka 1-4.\n");
        }
    }
}
