#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

// == Struktur Data ===========================================
struct Produk {
    char   name[60];
    char   category[30];
    double price;
    int    stock;
    float  rating;
};

Produk katalog[100];
int    n = 0;

// == File ====================================================
void simpanKeFile() {
    FILE* pf = fopen("shopease_db.txt", "w");
    if (!pf) { cout << "Gagal menyimpan file!\n"; return; }
    for (int i = 0; i < n; i++)
        fprintf(pf, "%s|%s|%.0lf|%d|%.1f\n",
            katalog[i].name, katalog[i].category,
            katalog[i].price, katalog[i].stock, katalog[i].rating);
    fclose(pf);
}

void muatDariFile() {
    FILE* pf = fopen("shopease_db.txt", "r");
    if (!pf) return;
    while (n < 100 &&
        fscanf(pf, " %[^|]|%[^|]|%lf|%d|%f\n",
            katalog[n].name, katalog[n].category,
            &katalog[n].price, &katalog[n].stock,
            &katalog[n].rating) != EOF) n++;
    fclose(pf);
}

// == Tampilan ===============================================
void cetakGaris() {
    cout << "================================================\n";
}

void tampilkanTabel() {
    if (n == 0) { cout << "Katalog masih kosong.\n"; return; }

    // header tabel
    cout << left
         << setw(4)  << "No"
         << setw(23) << "Nama"
         << setw(13) << "Kategori"
         << right
         << setw(12) << "Harga (Rp)"
         << setw(7)  << "Stok"
         << setw(7)  << "Rating"
         << "\n";
    cout << string(66, '-') << "\n";

    // isi tabel
    for (int i = 0; i < n; i++) {
        cout << left
             << setw(4)  << i+1
             << setw(23) << katalog[i].name
             << setw(13) << katalog[i].category
             << right
             << setw(12) << fixed << setprecision(0) << katalog[i].price
             << setw(7)  << katalog[i].stock
             << setw(7)  << fixed << setprecision(1) << katalog[i].rating
             << "\n";
    }
    cout << string(66, '-') << "\n";
    cout << "Total: " << n << " produk\n";
}

// == Sorting ================================================
void bubbleSortNama() {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1-i; j++)
            if (strcmp(katalog[j].name, katalog[j+1].name) > 0) {
                Produk tmp   = katalog[j];
                katalog[j]   = katalog[j+1];
                katalog[j+1] = tmp;
            }
}

int partisi(int kiri, int kanan) {
    float pivot = katalog[kanan].rating;
    int i = kiri - 1;
    for (int j = kiri; j < kanan; j++)
        if (katalog[j].rating > pivot) {
            i++;
            Produk tmp = katalog[i]; katalog[i] = katalog[j]; katalog[j] = tmp;
        }
    Produk tmp = katalog[i+1]; katalog[i+1] = katalog[kanan]; katalog[kanan] = tmp;
    return i + 1;
}

void quickSortRating(int kiri, int kanan) {
    if (kiri < kanan) {
        int p = partisi(kiri, kanan);
        quickSortRating(kiri, p-1);
        quickSortRating(p+1, kanan);
    }
}

// == Searching ==============================================
int cariProduk(char* keyword) {
    for (int i = 0; i < n; i++)
        if (strcmp(katalog[i].name, keyword) == 0) return i;
    return -1;
}

// == Menu 1 =================================================
void menuTambahProduk() {
    system("cls");
    cetakGaris();
    cout << "  TAMBAH PRODUK BARU\n";
    cetakGaris();

    if (n >= 100) { cout << "Katalog sudah penuh!\n"; return; }

    int jumlah;
    cout << "Mau tambah berapa produk? : ";
    cin >> jumlah;

    if (jumlah <= 0) { cout << "Jumlah tidak valid!\n"; return; }
    if (n + jumlah > 100) {
        cout << "Sisa kapasitas hanya " << 100-n << " produk.\n"; return;
    }

    for (int k = 1; k <= jumlah; k++) {
        cout << "\n--- Produk ke-" << k << " dari " << jumlah << " ---\n";
        Produk p;
        cin.ignore();
        cout << "Nama Produk  : "; cin.getline(p.name, 60);
        cout << "Kategori     : "; cin.getline(p.category, 30);
        cout << "Harga (Rp)   : "; cin >> p.price;
        cout << "Stok         : "; cin >> p.stock;
        cout << "Rating (0-5) : "; cin >> p.rating;
        katalog[n++] = p;
        cout << "Produk \"" << p.name << "\" berhasil ditambahkan!\n";
    }
    simpanKeFile();
    cout << "\nSemua produk berhasil disimpan!\n";
}

// == Menu 2 =================================================
void menuTampilkanProduk() {
    system("cls");
    cetakGaris();
    cout << "  TAMPILKAN DAFTAR PRODUK\n";
    cetakGaris();
    cout << "1. Urutkan berdasarkan Nama A-Z  (Bubble Sort)\n";
    cout << "2. Urutkan berdasarkan Rating    (Quick Sort)\n";
    cout << "Pilihan: ";
    int pilihan; cin >> pilihan;
    cout << "\n";

    if (pilihan == 1) {
        bubbleSortNama();
        cout << "-- Diurutkan Nama A-Z (Bubble Sort) --\n\n";
        tampilkanTabel();
    } else if (pilihan == 2) {
        quickSortRating(0, n-1);
        cout << "-- Diurutkan Rating Tertinggi (Quick Sort) --\n\n";
        tampilkanTabel();
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

// == Menu 3 =================================================
void menuCariProduk() {
    system("cls");
    cetakGaris();
    cout << "  CARI PRODUK\n";
    cetakGaris();
    cin.ignore();
    char keyword[60];
    cout << "Masukkan nama produk: ";
    cin.getline(keyword, 60);

    int idx = cariProduk(keyword);
    if (idx == -1) {
        cout << "\nProduk tidak ditemukan!\n";
    } else {
        cout << "\nProduk ditemukan!\n\n";
        cout << left  << setw(10) << "Nama"     << " : " << katalog[idx].name     << "\n";
        cout << left  << setw(10) << "Kategori" << " : " << katalog[idx].category << "\n";
        cout << left  << setw(10) << "Harga"    << " : Rp "
             << fixed << setprecision(0) << katalog[idx].price  << "\n";
        cout << left  << setw(10) << "Stok"     << " : " << katalog[idx].stock    << " unit\n";
        cout << left  << setw(10) << "Rating"   << " : "
             << fixed << setprecision(1) << katalog[idx].rating << " / 5.0\n";
    }
}

// == Menu 4 =================================================
void menuKeluar() {
    system("cls");
    simpanKeFile();
    cetakGaris();
    cout << "Data tersimpan ke shopease_db.txt\n";
    cout << "Terima kasih telah menggunakan ShopEase!\n";
    cout << "Sampai jumpa :)\n";
    cetakGaris();
}

// == Main ===================================================
int main() {
    muatDariFile();
    system("cls");
    cetakGaris();
    cout << "  SHOPEASE - Manajemen Katalog Produk\n";
    cetakGaris();
	if (n > 0) {
		cout << n << " produk dimuat dari file.\n\n";
	} else {
		cout << "Memulai dengan katalog kosong.\n\n";
	}

    int pilihan;
    do {
        cetakGaris();
        cout << "  MENU UTAMA\n";
        cetakGaris();
        cout << "1. Tambah Produk Baru\n";
        cout << "2. Tampilkan Daftar Produk\n";
        cout << "3. Cari Produk\n";
        cout << "4. Keluar dan Simpan\n";
        cetakGaris();
        cout << "Pilih menu [1-4]: ";
        cin >> pilihan;
        cout << "\n";

        if      (pilihan == 1) menuTambahProduk();
        else if (pilihan == 2) menuTampilkanProduk();
        else if (pilihan == 3) menuCariProduk();
        else if (pilihan == 4) menuKeluar();
        else                   cout << "Pilihan tidak valid!\n";

        if (pilihan != 4) {
            cout << "\nTekan Enter untuk kembali ke menu...";
            cin.ignore();
            cin.get();
        }
    } while (pilihan != 4);
    return 0;
}
