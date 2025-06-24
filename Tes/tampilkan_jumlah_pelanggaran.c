#include <stdio.h>
#include "tampilkan_jumlah_pelanggaran.h" 
#include "program_buat_jadwal.h"      

void tampilkan_jumlah_pelanggaran() {
    printf("\n+----------------------------------------------------+");
    printf("\n|             JUMLAH PELANGGARAN PREFERENSI          |");
    printf("\n+----------------------------------------------------+");
    printf("\nTotal pelanggaran preferensi: %d\n", pelanggaran_preferensi);
    printf("+----------------------------------------------------+\n");
}
