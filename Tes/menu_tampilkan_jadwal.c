#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "MenampilkanJadwal_Harian.h"
#include "MenampilkanJadwal_Mingguan.h"


void menu_tampilkan_jadwal() {
    int pilihan;
    
    while (1) {
        printf("\nTampilkan Jadwal\n");
        printf("1. Tampilkan Jadwal Harian\n");
        printf("2. Tampilkan Jadwal Mingguan\n");
        printf("3. Kembali ke Menu Utama\n");
        printf("Masukkan pilihan (1-3): ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                tampilkanJadwal_Harian();
                break;

            case 2:
                tampilkanJadwal_Mingguan();
                break;

            case 3:
                printf("Kembali ke menu utama\n");
                return;
                
            default:
                printf("Pilihan tidak valid. Masukkan angka 1-3.\n");
        }
    }
}
