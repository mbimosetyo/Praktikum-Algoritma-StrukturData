#include <iostream>
using namespace std;

// Struct untuk menyimpan data buku
struct Buku{
    string nama;   // menyimpan nama buku
    int harga;     // menyimpan harga buku
};

// SEKUENSIAL TANPA SENTINEL
void sekuensialBiasa(Buku data[], int jumlah, string cari){
    int i = 0;              // indeks awal
    bool found = false;     // penanda apakah data ditemukan

    // perulangan selama belum mencapai akhir array dan belum ditemukan
    while(i < jumlah && found == false){
        if(data[i].nama == cari){   // jika nama buku cocok
            found = true;           // ubah status menjadi ditemukan
        }
        else{
            i++;                    // pindah ke indeks berikutnya
        }
    }

    // cek hasil pencarian
    if(found){
        cout << cari << " ditemukan pada indeks ke-" << i << endl;
        cout << "Harga = Rp " << data[i].harga << endl;
    }
    else{
        cout << cari << " tidak ditemukan dalam data\n";
    }
}

// SEKUENSIAL SENTINEL
void sekuensialSentinel(Buku data[], int jumlah, string cari){
    int i = 0;  

    data[jumlah].nama = cari; // pasang sentinel di indeks terakhir

    // perulangan tanpa pengecekan batas karena ada sentinel
    while(data[i].nama != cari){
        i++;
    }

    // cek hasil pencarian
    if(i < jumlah){
        cout << cari << " ditemukan pada indeks ke-" << i << endl;
        cout << "Harga = Rp " << data[i].harga << endl;
    }
    else{
        cout << cari << " tidak ditemukan dalam data\n";
    }
}

// BINER (DATA HARUS URUT BERDASARKAN NAMA)
void biner(Buku data[], int jumlah, string cari){
    int i = 0;                // batas kiri
    int j = jumlah - 1;       // batas kanan
    int k;                    // indeks tengah
    bool found = false;       // penanda ditemukan atau tidak

    // perulangan selama belum ditemukan dan batas masih valid
    while((!found) && (i <= j)){
        k = (i + j) / 2;      // menentukan indeks tengah

        if(cari == data[k].nama){   // jika data tengah sama dengan yang dicari
            found = true;
        }
        else{
            if(cari < data[k].nama){
                j = k - 1;    // geser batas kanan ke kiri
            }
            else{
                i = k + 1;    // geser batas kiri ke kanan
            }
        }
    }

    // cek hasil pencarian
    if(found){
        cout << cari << " ditemukan pada indeks ke-" << k << endl;
        cout << "Harga = Rp " << data[k].harga << endl;
    }
    else{
        cout << cari << " tidak ditemukan dalam data\n";
    }
}

// MAIN PROGRAM
int main(){
    // Data buku sudah terurut (syarat pencarian biner)
    Buku data[6] = {
        {"Algoritma", 85000},
        {"BasisData", 90000},
        {"Jaringan", 75000},
        {"Pemrograman", 95000},
        {"StrukturData", 80000}
    };

    int jumlah = 5;   // jumlah data sebenarnya (1 slot tambahan untuk sentinel)
    string cari;      // variabel untuk menyimpan input pencarian
    int metode;       // pilihan metode pencarian

    cout << "Masukkan nama buku yang dicari = ";
    cin >> cari;

    cout << "\nPilih metode pencarian:\n";
    cout << "1. Sekuensial\n";
    cout << "2. Biner\n";
    cout << "Pilihan = ";
    cin >> metode;

    // jika memilih sekuensial
    if(metode == 1){
        int jenis;
        cout << "\n1. Tanpa Sentinel\n";
        cout << "2. Dengan Sentinel\n";
        cout << "Pilihan = ";
        cin >> jenis;

        if(jenis == 1){
            sekuensialBiasa(data, jumlah, cari);
        }
        else if(jenis == 2){
            sekuensialSentinel(data, jumlah, cari);
        }
        else{
            cout << "Pilihan tidak valid\n";
        }
    }
    // jika memilih biner
    else if(metode == 2){
        biner(data, jumlah, cari);
    }
    else{
        cout << "Pilihan tidak valid\n";
    }
    return 0;  // program selesai
}
