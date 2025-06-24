#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "tampilkanJadwal_Harian.h"
#include "tampilkanJadwal_Mingguan.h"
#include "tampilkanJadwal_Bulanan.h"
#include "tampilkan_jumlah_pelanggaran.h"
#include "tampilkan_jumlah_shift.h"


void menu_tampilkan_jadwal() {
    int pilihan;
    
    while (1) {
        printf("\nTampilkan Jadwal\n");
        printf("1. Tampilkan Jadwal Harian\n");
        printf("2. Tampilkan Jadwal Mingguan\n");
        printf("3. Tampilkan Jadwal Bulanan\n");
        printf("4. Tampilkan Jumlah Pelanggaran\n");
        printf("5. Tampilkan Jumlah Shift Masing-Masing Dokter\n");
        printf("6. Kembali ke Menu Utama\n");
        printf("Masukkan pilihan (1-6): ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                tampilkanJadwal_Harian();
                break;

            case 2:
                tampilkanJadwal_Mingguan();
                break;
            
            case 3:
                tampilkanJadwal_Bulanan();
                break;

            case 4:
                tampilkan_jumlah_pelanggaran();
                break;

            case 5:
                tampilkan_jumlah_shift();
                break;

            case 6:
                printf("Kembali ke menu utama\n");
                return;
                
            default:
                printf("Pilihan tidak valid. Masukkan angka 1-6.\n");
        }
    }
}
