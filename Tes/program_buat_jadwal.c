#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct dokter {
    int id;
    char nama[50];
    int maxShift;
    int prefShift;
    int totalShift;
    struct dokter *next;
} dokter;

typedef struct jadwal {
    int tanggal;
    dokter *pagi[5];
    dokter *siang[5];
    dokter *malam[5];
    struct jadwal *next;
} jadwal;

dokter *head_dokter = NULL;
jadwal *head_jadwal = NULL;

dokter* createDokter(int id, const char* nama, int maxshift, int prefShift) {
    dokter *newDokter = malloc(sizeof(dokter));
    if (newDokter == NULL) {
        return NULL;
    }
    newDokter->id = id;
    strncpy(newDokter->nama, nama, sizeof(newDokter->nama) - 1);
    newDokter->nama[sizeof(newDokter->nama) - 1] = '\0';
    newDokter->maxShift = maxshift;
    newDokter->prefShift = prefShift;
    newDokter->totalShift = 0;
    newDokter->next = NULL;
    return newDokter;
}

jadwal* createJadwal(int tanggal) {
    jadwal *newHari = calloc(1, sizeof(jadwal));
    if (newHari == NULL) {
        return NULL;
    }
    newHari->tanggal = tanggal;
    return newHari;
}

void openfileDokter(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror(filename);
        return;
    }
    char line[256];
    dokter *current = NULL;
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file)) {
        int id, maxShift, prefShift;
        char name[50];
        int items_parsed = sscanf(line, "%d,%49[^,],%d,%d", &id, name, &prefShift, &maxShift);

        if (items_parsed == 4) {
            dokter *newDokter = createDokter(id, name, maxShift, prefShift);
            if (newDokter) {
                if (head_dokter == NULL) {
                    head_dokter = newDokter;
                    current = head_dokter;
                } else {
                    current->next = newDokter;
                    current = newDokter;
                }
            }
        }
    }
    fclose(file);
    printf("Successfully loaded %s\n", filename);
}

void inisialisasiJadwal(int numDays) {
    jadwal *tail_hari = NULL;
    for (int i = 1; i <= numDays; i++) {
        jadwal *newHariNode = createJadwal(i);
        if (!newHariNode) {
            return;
        }
        if (head_jadwal == NULL) {
            head_jadwal = newHariNode;
            tail_hari = newHariNode;
        } 
        else {
            tail_hari->next = newHariNode;
            tail_hari = newHariNode;
        }
    }
}

int cekDokter(jadwal* hari, dokter* dokter) {
    for (int i = 0; i < 5; i++) {
        if ((hari->pagi[i] == dokter) || (hari->siang[i] == dokter) || (hari->malam[i] == dokter)) {
            return 1;
        }
    }
    return 0;
}

void jadwalDokter(int preference) {
    for (dokter* currentDokter = head_dokter; currentDokter != NULL; currentDokter = currentDokter->next) {
        if (currentDokter->prefShift != preference) continue;

        for (jadwal* currentHari = head_jadwal; currentHari != NULL; currentHari = currentHari->next) {
            if (currentDokter->totalShift < currentDokter->maxShift && !cekDokter(currentHari, currentDokter)) {
                int assigned = 0;
                for (int i = 0; i < 5 && !assigned; i++) {
                    switch (preference) {
                        case 0: 
                            if (!currentHari->pagi[i])  { 
                                currentHari->pagi[i]  = currentDokter; 
                                assigned = 1; 
                            } 
                            break;
                        case 1: 
                            if (!currentHari->siang[i]) { 
                                currentHari->siang[i] = currentDokter; 
                                assigned = 1; 
                            } 
                            break;
                        case 2: 
                            if (!currentHari->malam[i]) { 
                                currentHari->malam[i] = currentDokter; 
                                assigned = 1; 
                            }   
                            break;
                        case 3:
                            if (!currentHari->pagi[i]) { 
                                currentHari->pagi[i]  = currentDokter; assigned = 1; 
                            }
                            else if (!currentHari->siang[i]){ 
                                currentHari->siang[i] = currentDokter; 
                                assigned = 1; 
                            }
                            break;
                        case 4:
                            if (!currentHari->pagi[i]) { 
                                currentHari->pagi[i]  = 
                                currentDokter; 
                                assigned = 1; 
                            }
                            else if (!currentHari->malam[i]) { 
                                currentHari->malam[i] = currentDokter; 
                                assigned = 1; 
                            }
                            break;
                        case 5:
                            if (!currentHari->siang[i]) { 
                                currentHari->siang[i] = currentDokter; 
                                assigned = 1; 
                            }
                            else if (!currentHari->malam[i]) { 
                                currentHari->malam[i] = currentDokter; 
                                assigned = 1; 
                            }
                            break;
                        case 6:
                            if (!currentHari->pagi[i]) { 
                                currentHari->pagi[i]  = currentDokter; 
                                assigned = 1; 
                            }
                            else if (!currentHari->siang[i]) { 
                                currentHari->siang[i] = currentDokter;
                                assigned = 1; 
                                }
                            else if (!currentHari->malam[i]) { 
                                currentHari->malam[i] = currentDokter; 
                                assigned = 1; 
                            }
                            break;
                    }
                }
                if (assigned) {
                    currentDokter->totalShift++;
                }
            }
        }
    }
}

void buatJadwal() {
    if (!head_jadwal || !head_dokter) {
        return;
    }
    jadwalDokter(0);
    jadwalDokter(1);
    jadwalDokter(2);
    jadwalDokter(3);
    jadwalDokter(4);
    jadwalDokter(5);
    jadwalDokter(6);
}

int checkEmpty(void) {
    for (jadwal* currentHari = head_jadwal; currentHari != NULL; currentHari = currentHari->next) {
        dokter** shifts[] = { currentHari->pagi, currentHari->siang, currentHari->malam };
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
                if (shifts[i][j] == NULL) {
                    return 1; 
                }
            }
        }
    }
    return 0;
}

int cekPelanggaran(dokter* dokter, int tipeShift) {
    int preferensi = dokter->prefShift;
    switch (tipeShift) {
        case 0: // Assigned di Pagi
            if (preferensi == 0 || preferensi == 3 || preferensi == 4 || preferensi == 6) {
                return 0;
                break;
            }
        case 1: // Assigned di Siang
            if (preferensi == 1 || preferensi == 3 || preferensi == 5 || preferensi == 6) {
                return 0;
                break;
            }
        case 2: // Assigned di Malam
            if (preferensi == 2 || preferensi == 4 || preferensi == 5 || preferensi == 6) {
                return 0;
                break;
            }
    }
    return 1;
}



void randomtoEmpty(int* pelanggaran_preferensi) {
    if (!head_dokter) return;

    for (jadwal* currentHari = head_jadwal; currentHari != NULL; currentHari = currentHari->next) {
        dokter** shifts[] = { currentHari->pagi, currentHari->siang, currentHari->malam };
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 5; i++) {
                
                if (shifts[j][i] == NULL) { 
                    int availableCount = 0;
                    for (dokter* d = head_dokter; d != NULL; d = d->next) {
                        if (d->totalShift < d->maxShift && !cekDokter(currentHari, d)) {
                            availableCount++;
                        }
                    }
                    if (availableCount == 0) continue;

                    dokter** availableDocs = malloc(availableCount * sizeof(dokter*));
                    if (!availableDocs) return;
                    
                    int k = 0;
                    for (dokter* d = head_dokter; d != NULL; d = d->next) {
                        if (d->totalShift < d->maxShift && !cekDokter(currentHari, d)) {
                            availableDocs[k++] = d;
                        }
                    }
                    
                    for (int n = availableCount - 1; n > 0; n--) {
                        int r = rand() % (n + 1);
                        dokter* temp = availableDocs[r];
                        availableDocs[r] = availableDocs[n];
                        availableDocs[n] = temp;
                    }

                    if (availableCount > 0) {
                        dokter* candidate = availableDocs[0];
                        shifts[j][i] = candidate;
                        candidate->totalShift++;

                        if (cekPelanggaran(candidate, j)) {
                            pelanggaran_preferensi++;
                        }
                    }
                    
                    free(availableDocs);
                }
            }
        }
    }
}

void simpanJadwalKeCSV(const char* namaFile) {
    FILE *file = fopen(namaFile, "w");
    if (file == NULL) {
        perror("Error: Gagal membuat atau membuka file untuk menyimpan jadwal");
        return;
    }

    fprintf(file, "Tanggal,Shift,Slot,ID_Dokter,Nama_Dokter\n");

    for (jadwal* day = head_jadwal; day != NULL; day = day->next) {
        const char* nama_shift[] = {"Pagi", "Siang", "Malam"};
        dokter** daftar_shift[] = {day->pagi, day->siang, day->malam};

        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 5; i++) {
                dokter* d = daftar_shift[j][i];
                int nomor_slot = i + 1;

                if (d != NULL) {
                    // Jika slot terisi, tulis semua data
                    fprintf(file, "%d,%s,%d,%d,%s\n", day->tanggal, nama_shift[j], nomor_slot, d->id, d->nama);
                } else {
                    // Jika slot kosong, tulis data hari, shift, dan slot, lalu kosongkan data dokter
                    fprintf(file, "%d,%s,%d,,\n", day->tanggal, nama_shift[j], nomor_slot);
                }
            }
        }
    }

    fclose(file);
    printf("\nJadwal telah berhasil disimpan ke file: %s\n", namaFile);
}

void printJadwal() {
    printf("========================================= WEEKLY SCHEDULE =========================================\n");
    for (jadwal* day = head_jadwal; day != NULL; day = day->next) {
        printf("\n------------------------------------------- DAY %d -------------------------------------------\n", day->tanggal);
        char buffer[64];
        // Pagi
        printf("Pagi:\t");
        for (int i = 0; i < 5; i++) {
            if (day->pagi[i]) {
                snprintf(buffer, sizeof(buffer), "%s (ID:%d)", day->pagi[i]->nama, day->pagi[i]->id);
                printf("%-22s\t", buffer);
            } else {
                printf("%-22s\t", "[Empty]");
            }
        }
        printf("\n");
        // Siang
        printf("Siang:\t");
        for (int i = 0; i < 5; i++) {
            if (day->siang[i]) {
                snprintf(buffer, sizeof(buffer), "%s (ID:%d)", day->siang[i]->nama, day->siang[i]->id);
                printf("%-22s\t", buffer);
            } else {
                printf("%-22s\t", "[Empty]");
            }
        }
        printf("\n");
        // Malam
        printf("Malam:\t");
        for (int i = 0; i < 5; i++) {
            if (day->malam[i]) {
                snprintf(buffer, sizeof(buffer), "%s (ID:%d)", day->malam[i]->nama, day->malam[i]->id);
                printf("%-22s\t", buffer);
            } else {
                printf("%-22s\t", "[Empty]");
            }
        }
        printf("\n");
    }
    printf("===================================================================================================\n");
}

void freeDokter() {
    dokter *current = head_dokter, *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void freeJadwal() {
    jadwal *current = head_jadwal, *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void program_buat_jadwal() {
    int pelanggaran_preferensi = 0;
    srand(time(NULL));
    const char* csv_filename = "data_dokter.csv";
    openfileDokter(csv_filename);
    if (head_dokter == NULL) {
        printf("Tidak dapat memperoleh data dokter.\n");
        return 1;
    }
    inisialisasiJadwal(7);
    buatJadwal();
    if (checkEmpty()) {
        randomtoEmpty(&pelanggaran_preferensi);
    }  
    simpanJadwalKeCSV("JadwalDokter.csv");
    freeDokter();
    freeJadwal();
}
