#include <iostream>
#include <string>
using namespace std;

// Struct untuk mendefinisikan tiket konser
struct TiketKonser {
    int idTiket;             
    string namaKonser;       
    float hargaTiket;        
    int jumlahTiket;         
};

// Fungsi untuk menambah tiket ke array (menggunakan pointer)
void tambahTiket(TiketKonser* &tiket, int &jumlahTiket, int &idCounter) {
    cout << "Masukkan Nama Konser: ";
    cin.ignore();
    getline(cin, tiket[jumlahTiket].namaKonser);
    
    cout << "Masukkan Harga Tiket: ";
    cin >> tiket[jumlahTiket].hargaTiket;
    
    cout << "Masukkan Jumlah Tiket Tersedia: ";
    cin >> tiket[jumlahTiket].jumlahTiket;

    tiket[jumlahTiket].idTiket = ++idCounter;  
    jumlahTiket++;

    cout << "Tiket berhasil ditambahkan!\n";
}

// Fungsi untuk menampilkan semua tiket
void lihatTiket(TiketKonser* tiket, int jumlahTiket) {
    if (jumlahTiket == 0) {
        cout << "Belum ada tiket yang terdaftar.\n";
        return;
    }
    for (int i = 0; i < jumlahTiket; i++) {
        cout << "ID Tiket: " << tiket[i].idTiket << endl;
        cout << "Nama Konser: " << tiket[i].namaKonser << endl;
        cout << "Harga Tiket: " << tiket[i].hargaTiket << endl;
        cout << "Jumlah Tiket: " << tiket[i].jumlahTiket << endl;
        cout << "-----------------------------\n";
    }
}

// Fungsi untuk memperbarui tiket berdasarkan ID
void updateTiket(TiketKonser* tiket, int jumlahTiket) {
    int id;
    cout << "Masukkan ID tiket yang ingin diubah: ";
    cin >> id;

    for (int i = 0; i < jumlahTiket; i++) {
        if (tiket[i].idTiket == id) {
            cout << "Masukkan Nama Konser Baru: ";
            cin.ignore();
            getline(cin, tiket[i].namaKonser);

            cout << "Masukkan Harga Tiket Baru: ";
            cin >> tiket[i].hargaTiket;

            cout << "Masukkan Jumlah Tiket Tersedia Baru: ";
            cin >> tiket[i].jumlahTiket;

            cout << "Tiket berhasil diperbarui!\n";
            return;
        }
    }
    cout << "Tiket dengan ID tersebut tidak ditemukan.\n";
}

// Fungsi untuk menghapus tiket berdasarkan ID
void hapusTiket(TiketKonser* &tiket, int &jumlahTiket) {
    int id;
    cout << "Masukkan ID tiket yang ingin dihapus: ";
    cin >> id;

    for (int i = 0; i < jumlahTiket; i++) {
        if (tiket[i].idTiket == id) {
            for (int j = i; j < jumlahTiket - 1; j++) {
                tiket[j] = tiket[j + 1];
            }
            jumlahTiket--;
            cout << "Tiket berhasil dihapus!\n";
            return;
        }
    }
    cout << "Tiket dengan ID tersebut tidak ditemukan.\n";
}

// Fungsi utama untuk menu CRUD
int main() {
    int jumlahTiket = 0;             
    int idCounter = 0;               
    TiketKonser* tiket = new TiketKonser[100]; 
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
                tambahTiket(tiket, jumlahTiket, idCounter);
                break;
            case 2:
                lihatTiket(tiket, jumlahTiket);
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

    delete[] tiket;
    return 0;
}
