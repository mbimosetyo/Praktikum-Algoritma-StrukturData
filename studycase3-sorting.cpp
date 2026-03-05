#include <iostream>      // Library untuk input dan output (cin, cout)
using namespace std;     // Agar tidak perlu menulis std:: sebelum cin/cout

// FUNGSI MENAMPILKAN DATA
void tampilData(string array[], int n){
    
    // Perulangan untuk menampilkan setiap elemen array
    for(int i = 0; i < n; i++){
        cout << array[i] << endl;
    }
}

// BUBBLE SORT ASCENDING
void bubbleSortAscending(string array[], int n){ 
    // Perulangan luar untuk jumlah tahap
    for(int i = 0; i < n - 1; i++){
        // Perulangan dalam untuk membandingkan elemen
        for(int j = 0; j < n - i - 1; j++){
            // Jika elemen sekarang lebih besar dari setelahnya (ascending)
            if(array[j] > array[j + 1]){
                string temp = array[j + 1];		// Simpan sementara
                array[j + 1] = array[j];		// Tukar posisi
                array[j] = temp;
            }
        }
    }
}

// QUICK SORT DESCENDING
void quickSortDescending(string array[], int awal, int akhir){
    int low = awal;     // Pointer kiri
    int high = akhir;   // Pointer kanan
    
    // Pivot diambil dari tengah array
    string pivot = array[(awal + akhir) / 2];

    do{
        // Untuk descending:
        // Geser low jika elemen lebih BESAR dari pivot
        while (array[low] > pivot)
            low++;

        // Geser high jika elemen lebih KECIL dari pivot
        while (array[high] < pivot)
            high--;

        // Jika posisi low belum melewati high
        if (low <= high) {
            
            // Tukar posisi elemen
            swap(array[low], array[high]);
            low++;
            high--;
        }
    } while (low <= high);
    // Rekursif bagian kiri
    if (awal < high)
        quickSortDescending(array, awal, high);

    // Rekursif bagian kanan
    if (low < akhir)
        quickSortDescending(array, low, akhir);
}

// MAIN PROGRAM
int main() {
    int n;  // Variabel untuk menyimpan jumlah mahasiswa
    
    // Meminta user memasukkan jumlah nama
    cout << "Masukkan jumlah mahasiswa: "; cin >> n;

    // Membuat array string sesuai jumlah yang diinput user
    string nama[n];

    // Membersihkan newline yang tersisa setelah input angka
    cin.ignore();

    // Input nama mahasiswa satu per satu
    for (int i = 0; i < n; i++) {
        cout << "Masukkan nama mahasiswa ke-" << i + 1 << ": ";
        getline(cin, nama[i]);  // Menggunakan getline agar bisa membaca spasi
    }

	// Menampilkan data sebelum sorting
	cout << "\nData sebelum diurutan (sorting):\n";
	tampilData(nama, n);

    // Panggil fungsi bubble sort ascending
    bubbleSortAscending(nama, n);

    // Menampilkan hasil pengurutan ascending
    cout << "\nHasil pengurutan Ascending (Bubble Sort):" << endl;
    for (int i = 0; i < n; i++) {
        cout << nama[i] << endl;
    }

    // Panggil fungsi quick sort descending
    quickSortDescending(nama, 0, n - 1);

    // Menampilkan hasil pengurutan descending
    cout << "\nHasil pengurutan Descending (Quick Sort):" << endl;
    for (int i = 0; i < n; i++) {
        cout << nama[i] << endl;
    }
    return 0;  // Mengakhiri program
}
