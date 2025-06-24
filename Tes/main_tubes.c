#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "menu_olah_data.h"
#include "mainprogram2.h"
#include "menu_tampilkan_jadwal.h"

int main() {
    int pilihan;
    
    while (1) {
        printf("\nSistem Informasi Jadwal Dokter\n");
        printf("1. Olah Data Dokter\n");
        printf("2. Buat Jadwal\n");
        printf("3. Tampilkan Jadwal\n");
        printf("4. Keluar\n");
        printf("Masukkan pilihan (1-4): ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                menu_olah_data();

                break;
                
            case 2:
                main2()

                break;
                
            case 3:
                menu_tampilkan_jadwal();

                break;
                
            case 4:
                printf("Keluar dari program.\n");
                return 0;
                
            default:
                printf("Pilihan tidak valid. Masukkan angka 1-7.\n");
        }
    }
    
    return 0;
}
