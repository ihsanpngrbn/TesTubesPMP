#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "menu_olah_data.h"
#include "program_buat_jadwal.h"
#include "menu_tampilkan_jadwal.h"

int main() {
    int pilihan;
    
    while (1) {
    printf("\n+--------------------------------------------------+");
    printf("\n|         SISTEM INFORMASI JADWAL DOKTER          |");
    printf("\n+--------------------------------------------------+");
    printf("\n|  1. Olah Data Dokter                            |");
    printf("\n|  2. Buat Jadwal                                 |");
    printf("\n|  3. Tampilkan Jadwal                            |");
    printf("\n|  4. Keluar                                      |");
    printf("\n+--------------------------------------------------+");
    printf("\nMasukkan pilihan Anda (1 - 4): ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                menu_olah_data();

                break;
                
            case 2:
                int status = program_buat_jadwal();
                if (status != 0) {
                    printf("Gagal membuat jadwal.\n");
                }
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
