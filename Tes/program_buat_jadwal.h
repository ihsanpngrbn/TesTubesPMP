#ifndef PROGRAM_BUAT_JADWAL_H
#define PROGRAM_BUAT_JADWAL_H

#include <stdio.h>   // Untuk input/output seperti printf, scanf, FILE, perror
#include <stdlib.h>  // Untuk alokasi memori (malloc, free, calloc), srand
#include <string.h>  // Untuk manipulasi string (strncpy, strlen, dll.)
#include <time.h>    // Untuk fungsi waktu (time, srand)

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

extern dokter *head_dokter;
extern jadwal *head_jadwal;

// Fungsi untuk membuat node dokter baru
dokter* createDokter(int id, const char* nama, int maxshift, int prefShift);

// Fungsi untuk membuat node jadwal baru
jadwal* createJadwal(int tanggal);

// Fungsi untuk membuka dan membaca data dokter dari file CSV
void openfileDokter(const char* filename);

// Fungsi untuk menginisialisasi linked list jadwal dengan jumlah hari tertentu
void inisialisasiJadwal(int numDays);

// Fungsi untuk mengecek apakah seorang dokter sudah dijadwalkan pada hari tertentu
int cekDokter(jadwal* hari, dokter* dokter);

// Fungsi untuk menjadwalkan dokter berdasarkan preferensi shift
void jadwalDokter(int preference);

// Fungsi utama untuk membuat jadwal secara keseluruhan (memanggil jadwalDokter untuk berbagai preferensi)
void buatJadwal();

// Fungsi untuk mengecek apakah ada slot jadwal yang kosong
int checkEmpty(void);

// Fungsi untuk mengecek apakah penempatan dokter melanggar preferensi
int cekPelanggaran(dokter* dokter, int tipeShift);

// Fungsi untuk mengisi slot kosong secara acak dan menghitung pelanggaran preferensi
void randomtoEmpty(int* pelanggaran_preferensi);

// Fungsi untuk menyimpan jadwal yang telah dibuat ke file CSV
void simpanJadwalKeCSV(const char* namaFile);

// Fungsi untuk mencetak jadwal ke konsol
void printJadwal();

// Fungsi untuk membebaskan memori yang dialokasikan untuk linked list dokter
void freeDokter();

// Fungsi untuk membebaskan memori yang dialokasikan untuk linked list jadwal
void freeJadwal();

// Fungsi utama untuk menjalankan proses pembuatan jadwal (yang dipanggil dari main_tubes.c)
// Tipe kembaliannya int agar bisa mengindikasikan sukses (0) atau gagal (non-nol)
int program_buat_jadwal();

#endif // PROGRAM_BUAT_JADWAL_H
