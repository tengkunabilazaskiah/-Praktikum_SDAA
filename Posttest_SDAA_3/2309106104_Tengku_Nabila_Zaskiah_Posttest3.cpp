#include <iostream>
#include <string>
using namespace std;

// Struct untuk mendefinisikan node yang menyimpan tiket konser
struct TiketKonser {
    int idTiket;
    string namaKonser;
    float hargaTiket;
    int jumlahTiket;
    TiketKonser* next; 
};

// Fungsi untuk menambah tiket ke linked list
void tambahTiket(TiketKonser* &tiket, int &jumlahTiket) {
    TiketKonser* tiketBaru = new TiketKonser; 
    cout << "Masukkan Nama Konser: ";
    cin.ignore();
    getline(cin, tiketBaru->namaKonser);

    cout << "Masukkan Harga Tiket: ";
    cin >> tiketBaru->hargaTiket;

    cout << "Masukkan Jumlah Tiket Tersedia: ";
    cin >> tiketBaru->jumlahTiket;

    tiketBaru->idTiket = ++jumlahTiket;  
    tiketBaru->next = nullptr;          

    // Jika list masih kosong, tiketBaru menjadi node pertama
    if (tiket == nullptr) {
        tiket = tiketBaru;
    } else {
        TiketKonser* tiketSaatIni = tiket;
        // Traverse sampai ke node terakhir
        while (tiketSaatIni->next != nullptr) {
            tiketSaatIni = tiketSaatIni->next;
        }
        tiketSaatIni->next = tiketBaru; 
    }
    cout << "Tiket berhasil ditambahkan!\n";
}

// Fungsi untuk menampilkan semua tiket
void lihatTiket(TiketKonser* tiket) {
    if (tiket == nullptr) {
        cout << "Belum ada tiket yang terdaftar.\n";
        return;
    }
    TiketKonser* tiketSaatIni = tiket;
    while (tiketSaatIni != nullptr) {
        cout << "ID Tiket: " << tiketSaatIni->idTiket << endl;
        cout << "Nama Konser: " << tiketSaatIni->namaKonser << endl;
        cout << "Harga Tiket: " << tiketSaatIni->hargaTiket << endl;
        cout << "Jumlah Tiket: " << tiketSaatIni->jumlahTiket << endl;
        cout << "-----------------------------\n";
        tiketSaatIni = tiketSaatIni->next;  
    }
}

// Fungsi untuk memperbarui tiket berdasarkan ID
void updateTiket(TiketKonser* tiket, int jumlahTiket) {
    int id;
    cout << "Masukkan ID tiket yang ingin diubah: ";
    cin >> id;

    TiketKonser* tiketSaatIni = tiket;
    while (tiketSaatIni != nullptr) {
        if (tiketSaatIni->idTiket == id) {
            cout << "Masukkan Nama Konser Baru: ";
            cin.ignore();
            getline(cin, tiketSaatIni->namaKonser);

            cout << "Masukkan Harga Tiket Baru: ";
            cin >> tiketSaatIni->hargaTiket;

            cout << "Masukkan Jumlah Tiket Tersedia Baru: ";
            cin >> tiketSaatIni->jumlahTiket;

            cout << "Tiket berhasil diperbarui!\n";
            return;
        }
        tiketSaatIni = tiketSaatIni->next;
    }
    cout << "Tiket dengan ID tersebut tidak ditemukan.\n";
}

// Fungsi untuk menghapus tiket berdasarkan ID
void hapusTiket(TiketKonser* &tiket, int &jumlahTiket) {
    int id;
    cout << "Masukkan ID tiket yang ingin dihapus: ";
    cin >> id;

    TiketKonser* tiketSaatIni = tiket;
    TiketKonser* tiketSebelumnya = nullptr; 

    if (tiketSaatIni != nullptr && tiketSaatIni->idTiket == id) {
        tiket = tiketSaatIni->next;  
        delete tiketSaatIni;         
        jumlahTiket--;               
        cout << "Tiket berhasil dihapus!\n";
        return;
    }

    // Traverse untuk menemukan node yang akan dihapus
    while (tiketSaatIni != nullptr && tiketSaatIni->idTiket != id) {
        tiketSebelumnya = tiketSaatIni;        
        tiketSaatIni = tiketSaatIni->next;     
    }

    // Jika node tidak ditemukan
    if (tiketSaatIni == nullptr) {
        cout << "Tiket dengan ID tersebut tidak ditemukan.\n";
        return;
    }

    // Node ditemukan, hapus node dengan menyambungkan tiketSebelumnya ke tiketSaatIni->next
    tiketSebelumnya->next = tiketSaatIni->next;  
    delete tiketSaatIni;                       
    jumlahTiket--;                               
    cout << "Tiket berhasil dihapus!\n";
}

// Fungsi utama untuk menu CRUD
int main() {
    TiketKonser* tiket = nullptr; 
    int jumlahTiket = 0;          
    int pilihan;
    do {
        cout << "\n=== Manajemen Penjualan Tiket Konser ===\n";
        cout << "1. Tambah Tiket\n";
        cout << "2. Lihat Semua Tiket\n";
        cout << "3. Update Tiket\n";
        cout << "4. Hapus Tiket\n";
        cout << "5. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahTiket(tiket, jumlahTiket);
                break;
            case 2:
                lihatTiket(tiket);
                break;
            case 3:
                updateTiket(tiket, jumlahTiket);
                break;
            case 4:
                hapusTiket(tiket, jumlahTiket);
                break;
            case 5:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);

    // Hapus semua node ketika program selesai
    TiketKonser* tiketSaatIni;
    while (tiket != nullptr) {
        tiketSaatIni = tiket;
        tiket = tiket->next;
        delete tiketSaatIni;
    }

    return 0;
}
