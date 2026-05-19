#include <iostream>
#include <cstdlib>
using namespace std;

const int KAPASITAS = 5;

// =============================================
// STRUKTUR DATA
// =============================================
// Node BST - menyimpan data kendaraan
struct Kendaraan {
    string noPolisi, nama, status;
    Kendaraan *kiri, *kanan;
    Kendaraan(string np, string nm) {
        noPolisi = np; nama = nm;
        status = "Di Luar Parkiran";
        kiri = kanan = nullptr;
    }
};

// Node Stack - menyimpan riwayat aksi untuk undo
struct NodeStack {
    string noPolisi, aksi; // aksi: "MASUK" atau "KELUAR"
    NodeStack* bawah;
    NodeStack(string np, string a) {
        noPolisi = np; aksi = a; bawah = nullptr;
    }
};

// Node Queue - menyimpan antrian kendaraan
struct NodeQueue {
    string noPolisi;
    NodeQueue* next;
    NodeQueue(string np) { noPolisi = np; next = nullptr; }
};

// =============================================
// VARIABEL GLOBAL
// =============================================
Kendaraan* akar = nullptr;
NodeStack* tumpukan = nullptr;
NodeQueue *depan = nullptr, *belakang = nullptr;
int isiParkir = 0;

// =============================================
// FUNGSI BST
// =============================================
Kendaraan* sisip(Kendaraan* node, string np, string nm) {
    if (node == nullptr) return new Kendaraan(np, nm);
    if (np < node->noPolisi) node->kiri = sisip(node->kiri, np, nm);
    else if (np > node->noPolisi) node->kanan = sisip(node->kanan, np, nm);
    return node;
}

Kendaraan* cari(Kendaraan* node, string np) {
    if (node == nullptr || np == node->noPolisi) return node;
    if (np < node->noPolisi) return cari(node->kiri, np);
    return cari(node->kanan, np);
}

Kendaraan* terkecil(Kendaraan* node) {
    while (node->kiri != nullptr) node = node->kiri;
    return node;
}

Kendaraan* hapus(Kendaraan* node, string np) {
    if (node == nullptr) return nullptr;
    if (np < node->noPolisi) node->kiri = hapus(node->kiri, np);
    else if (np > node->noPolisi) node->kanan = hapus(node->kanan, np);
    else {
        if (node->kiri == nullptr) { Kendaraan* t = node->kanan; delete node; return t; }
        if (node->kanan == nullptr) { Kendaraan* t = node->kiri; delete node; return t; }
        Kendaraan* p = terkecil(node->kanan);
        node->noPolisi = p->noPolisi;
        node->nama = p->nama;
        node->status = p->status;
        node->kanan = hapus(node->kanan, p->noPolisi);
    }
    return node;
}

void tampilBST(Kendaraan* node) {
    if (node == nullptr) return;
    tampilBST(node->kiri);
    cout << "  No. Polisi : " << node->noPolisi << "\n";
    cout << "  Nama       : " << node->nama << "\n";
    cout << "  Status     : " << node->status << "\n";
    cout << "  ----------------------------\n";
    tampilBST(node->kanan);
}

// =============================================
// FUNGSI STACK (Undo)
// =============================================
void push(string np, string aksi) {
    NodeStack* baru = new NodeStack(np, aksi);
    baru->bawah = tumpukan;
    tumpukan = baru;
}

NodeStack* pop() {
    if (tumpukan == nullptr) return nullptr;
    NodeStack* atas = tumpukan;
    tumpukan = tumpukan->bawah;
    return atas;
}

// =============================================
// FUNGSI QUEUE (Antrian)
// =============================================
void enqueue(string np) {
    NodeQueue* baru = new NodeQueue(np);
    if (belakang == nullptr) depan = belakang = baru;
    else { belakang->next = baru; belakang = baru; }
}

string dequeue() {
    if (depan == nullptr) return "";
    NodeQueue* t = depan;
    string np = t->noPolisi;
    depan = depan->next;
    if (depan == nullptr) belakang = nullptr;
    delete t;
    return np;
}

// =============================================
// FUNGSI TAMPIL HEADER & JEDA
// =============================================
void cls() { system("cls || clear"); }

void header() {
    cout << "========================================\n";
    cout << "    SISTEM PARKIR INAP BANDARA GSA\n";
    cout << "    Kapasitas Parkir: " << KAPASITAS << " kendaraan\n";
    cout << "========================================\n";
}

void jeda() {
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore(); cin.get();
}

// =============================================
// MENU
// =============================================
void tambah() {
    string np, nm;
    cls(); header();
    cout << "\n=== TAMBAH KENDARAAN ===\n";
    cout << "Nomor Polisi : "; cin.ignore(); getline(cin, np);
    if (cari(akar, np) != nullptr) {
        cout << "Nomor polisi sudah terdaftar!\n";
        jeda(); return;
    }
    cout << "Nama Pemilik : "; getline(cin, nm);
    akar = sisip(akar, np, nm);
    cout << "Data kendaraan berhasil ditambahkan.\n";
    jeda();
}

void tampil() {
    cls(); header();
    cout << "\n=== DAFTAR KENDARAAN ===\n";
    if (akar == nullptr) cout << "Belum ada data kendaraan.\n";
    else { cout << "  ----------------------------\n"; tampilBST(akar); }
    jeda();
}

void masuk() {
    string np;
    cls(); header();
    cout << "\n=== KENDARAAN MASUK ===\n";
    cout << "Nomor Polisi : "; cin.ignore(); getline(cin, np);

    Kendaraan* k = cari(akar, np);
    if (k == nullptr) { cout << "Kendaraan tidak ditemukan!\n"; jeda(); return; }
    if (k->status == "Di Parkiran") { cout << "Kendaraan sudah berada di parkiran!\n"; jeda(); return; }

    for (NodeQueue* tmp = depan; tmp != nullptr; tmp = tmp->next) {
        if (tmp->noPolisi == np) { cout << "Kendaraan sudah berada dalam antrian!\n"; jeda(); return; }
    }

    if (isiParkir < KAPASITAS) {
        k->status = "Di Parkiran"; isiParkir++;
        push(np, "MASUK");
        cout << "Kendaraan berhasil masuk.\n";
    } else {
        enqueue(np);
        cout << "Parkiran penuh, kendaraan masuk ke dalam antrian.\n";
    }
    jeda();
}

void keluar() {
    string np;
    cls(); header();
    cout << "\n=== KENDARAAN KELUAR ===\n";
    cout << "Nomor Polisi : "; cin.ignore(); getline(cin, np);

    Kendaraan* k = cari(akar, np);
    if (k == nullptr) { cout << "Kendaraan tidak ditemukan!\n"; jeda(); return; }
    if (k->status != "Di Parkiran") { cout << "Kendaraan tidak sedang berada di parkiran!\n"; jeda(); return; }

    k->status = "Di Luar Parkiran"; isiParkir--;
    push(np, "KELUAR");
    cout << "Kendaraan berhasil keluar.\n";

    if (depan != nullptr) {
        string npA = dequeue();
        Kendaraan* ka = cari(akar, npA);
        if (ka != nullptr) {
            ka->status = "Di Parkiran"; isiParkir++;
            push(npA, "MASUK");
            cout << "Kendaraan berikutnya langsung masuk ke area parkir dari antrian.\n";
        }
    }
    jeda();
}

void hapusData() {
    string np;
    cls(); header();
    cout << "\n=== HAPUS KENDARAAN ===\n";
    cout << "Nomor Polisi : "; cin.ignore(); getline(cin, np);

    Kendaraan* k = cari(akar, np);
    if (k == nullptr) { cout << "Kendaraan tidak ditemukan!\n"; jeda(); return; }
    if (k->status == "Di Parkiran") isiParkir--;
    akar = hapus(akar, np);
    cout << "Data kendaraan berhasil dihapus.\n";
    jeda();
}

void undo() {
    cls(); header();
    cout << "\n=== UNDO AKSI TERAKHIR ===\n";
    NodeStack* aksi = pop();
    if (aksi == nullptr) { cout << "Tidak ada aksi untuk di-undo.\n"; jeda(); return; }

    Kendaraan* k = cari(akar, aksi->noPolisi);
    if (k == nullptr) { cout << "Kendaraan tidak ditemukan, undo dibatalkan.\n"; delete aksi; jeda(); return; }

    if (aksi->aksi == "MASUK") {
        k->status = "Di Luar Parkiran"; isiParkir--;
        cout << "Undo: Kendaraan keluar dari parkiran.\n";
    } else {
        k->status = "Di Parkiran"; isiParkir++;
        cout << "Undo: Kendaraan masuk kembali ke parkiran.\n";
    }
    delete aksi;
    jeda();
}

void tampilAntrian() {
    cls(); header();
    cout << "\n=== ANTRIAN KENDARAAN ===\n";
    if (depan == nullptr) cout << "Antrian kosong.\n";
    else {
        for (NodeQueue* tmp = depan; tmp != nullptr; tmp = tmp->next)
            cout << tmp->noPolisi << " menunggu giliran masuk parkiran.\n";
    }
    jeda();
}

// =============================================
// MAIN
// =============================================
int main() {
    int pilihan;
    do {
        cls(); header();
        cout << "\n--- MENU ---\n";
        cout << "1. Tambah Kendaraan\n";
        cout << "2. Tampil Kendaraan\n";
        cout << "3. Kendaraan Masuk\n";
        cout << "4. Kendaraan Keluar\n";
        cout << "5. Hapus Kendaraan\n";
        cout << "6. Undo Aksi Terakhir\n";
        cout << "7. Tampil Antrian\n";
        cout << "0. Keluar\n";
        cout << "Pilih: "; cin >> pilihan;

        switch (pilihan) {
            case 1: tambah(); break;
            case 2: tampil(); break;
            case 3: masuk(); break;
            case 4: keluar(); break;
            case 5: hapusData(); break;
            case 6: undo(); break;
            case 7: tampilAntrian(); break;
            case 0: cls(); cout << "Program selesai. Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n"; jeda();
        }
    } while (pilihan != 0);

    return 0;
}
