#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "olahdata.h"

void menu_olah_data() {
    int pilihan;
    
    while (1) {
        printf("\nOlah Data Dokter\n");
        printf("1. Tambah Dokter\n");
        printf("2. Hapus Dokter\n");
        printf("3. Tampilkan Dokter\n");
        printf("4. Kembali ke Menu Utama\n");
        printf("Masukkan pilihan (1-4): ");
        scanf("%d", &pilihan);
        
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
