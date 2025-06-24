#ifndef OLAH_DATA_H
#define OLAH_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi struct Dokter agar dapat digunakan oleh file lain
typedef struct {
    int ID;
    char Nama[50];
    int PrefShift;
    int MaxShift;
} Dokter;

// Deklarasi fungsi-fungsi
// Fungsi-fungsi ini akan diimplementasikan di olah_data.c
// dan dapat dipanggil dari menu_olah_data.c

void bacaFile();    // <-- Sekarang dideklarasikan di sini
void simpanFile();  // <-- Sekarang dideklarasikan di sini

void tampilkanData();
void tambahDokter();
void hapusDokter();

#endif // OLAH_DATA_H
