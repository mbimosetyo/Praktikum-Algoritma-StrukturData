#include <iostream>   // Library untuk input dan output
using namespace std;  // Supaya tidak perlu menulis std::

int main() {
    // Membuat array integer
    int angka[] = {5, 10, 3, 8, 2};

    // Menghitung jumlah elemen dalam array
    int panjang = sizeof(angka) / sizeof(angka[0]);

    // Membuat pointer yang menunjuk ke array
    int *ptr = angka;

    // Menampilkan semua isi array
    cout << "Isi array = ";
    for (int i = 0; i < panjang; i++) {
        cout << *(ptr + i) << " ";   // Mengakses isi array dengan pointer
    }
    cout << endl;

    // Mencari nilai maksimum dan minimum
    int max = *ptr;   // Anggap elemen pertama sebagai maksimum awal
    int min = *ptr;   // Anggap elemen pertama sebagai minimum awal

    for (int i = 1; i < panjang; i++) {
        if (*(ptr + i) > max) {  // Jika lebih besar dari max
            max = *(ptr + i);    // Update max
        }
        if (*(ptr + i) < min) {  // Jika lebih kecil dari min
            min = *(ptr + i);    // Update min
        }
    }

    cout << "Nilai maksimum = " << max << endl;  // Menampilkan nilai maksimum
    cout << "Nilai minimum = " << min << endl;   // Menampilkan nilai minimum

    // Menghitung jumlah dan rata-rata
    int jumlah = 0;   // Variabel untuk menyimpan total isi array
    for (int i = 0; i < panjang; i++) {
        jumlah += *(ptr + i);   // Menambahkan setiap isi array ke jumlah dengan pointer
    }
    float rata = (float)jumlah / panjang;  // Menghitung rata-rata isi array

    cout << "Jumlah = " << jumlah << endl;   // Menampilkan jumlah isi array
    cout << "Rata-rata = " << rata << endl;  // Menampilkan rata-rata isi array

    return 0;   // Program selesai
}
