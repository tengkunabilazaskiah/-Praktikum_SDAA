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

// Fungsi untuk menghapus tiket berdasarkan ID (Digunakan juga untuk Stack dan Queue)
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

// --- STACK IMPLEMENTATION ---

// Fungsi untuk push tiket ke stack (LIFO)
void pushTiket(TiketKonser* &stack, int &jumlahTiket) {
    tambahTiket(stack, jumlahTiket);
    cout << "Tiket ditambahkan ke Stack (LIFO)\n";
}

// Fungsi untuk pop tiket dari stack
void popTiket(TiketKonser* &stack, int &jumlahTiket) {
    if (stack == nullptr) {
        cout << "Stack kosong, tidak ada tiket yang bisa di-pop.\n";
        return;
    }

    TiketKonser* tiketTerakhir = stack;
    stack = stack->next;
    cout << "Tiket ID: " << tiketTerakhir->idTiket << " di-pop dari Stack (LIFO)\n";
    delete tiketTerakhir;
    jumlahTiket--;
}

// --- QUEUE IMPLEMENTATION ---

// Fungsi untuk enqueue tiket ke queue (FIFO)
void enqueueTiket(TiketKonser* &queue, int &jumlahTiket) {
    tambahTiket(queue, jumlahTiket);
    cout << "Tiket ditambahkan ke Queue (FIFO)\n";
}

// Fungsi untuk dequeue tiket dari queue
void dequeueTiket(TiketKonser* &queue, int &jumlahTiket) {
    hapusTiket(queue, jumlahTiket);
    cout << "Tiket di-dequeue dari Queue (FIFO)\n";
}

// Fungsi untuk menggabungkan dua list yang sudah diurutkan
TiketKonser* merge(TiketKonser* kiri, TiketKonser* kanan) {
    if (kiri == nullptr) return kanan;
    if (kanan == nullptr) return kiri;

    if (kiri->hargaTiket <= kanan->hargaTiket) {
        kiri->next = merge(kiri->next, kanan);
        return kiri;
    } else {
        kanan->next = merge(kiri, kanan->next);
        return kanan;
    }
}

// Fungsi untuk memecah list menjadi dua bagian dan melakukan merge sort
TiketKonser* mergeSort(TiketKonser* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    // Temukan tengah list untuk membaginya
    TiketKonser* tengah = head;
    TiketKonser* cepat = head->next;

    while (cepat != nullptr && cepat->next != nullptr) {
        tengah = tengah->next;
        cepat = cepat->next->next;
    }

    TiketKonser* separuhKedua = tengah->next;
    tengah->next = nullptr;

    TiketKonser* kiri = mergeSort(head);
    TiketKonser* kanan = mergeSort(separuhKedua);

    return merge(kiri, kanan);
}

// Fungsi untuk memisahkan list ke dalam dua bagian berdasarkan pivot
TiketKonser* partition(TiketKonser* head, TiketKonser** depan, TiketKonser** belakang) {
    TiketKonser* pivot = head;
    TiketKonser* saatIni = head->next;

    TiketKonser* besar = nullptr;
    TiketKonser* kecil = nullptr;

    while (saatIni != nullptr) {
        TiketKonser* nextNode = saatIni->next;
        if (saatIni->hargaTiket > pivot->hargaTiket) {
            saatIni->next = besar;
            besar = saatIni;
        } else {
            saatIni->next = kecil;
            kecil = saatIni;
        }
        saatIni = nextNode;
    }

    *depan = besar;
    *belakang = kecil;
    return pivot;
}

// Fungsi untuk melakukan quick sort pada list
TiketKonser* quickSort(TiketKonser* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    TiketKonser* depan = nullptr;
    TiketKonser* belakang = nullptr;

    TiketKonser* pivot = partition(head, &depan, &belakang);

    depan = quickSort(depan);
    belakang = quickSort(belakang);

    // Gabungkan kembali list
    if (depan == nullptr) {
        pivot->next = belakang;
        return pivot;
    } else {
        TiketKonser* temp = depan;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = pivot;
        pivot->next = belakang;
        return depan;
    }
}

// Fungsi utama untuk menu CRUD
int main() {
    TiketKonser* tiket = nullptr; 
    TiketKonser* stack = nullptr; 
    TiketKonser* queue = nullptr; 
    tiket = mergeSort(tiket);
    tiket = quickSort(tiket);


    int jumlahTiket = 0;          
    int pilihan;
    do {
        cout << "\n=== Manajemen Penjualan Tiket Konser ===\n";
        cout << "1. Tambah Tiket\n";
        cout << "2. Lihat Semua Tiket\n";
        cout << "3. Push Tiket ke Stack\n";
        cout << "4. Pop Tiket dari Stack\n";
        cout << "5. Enqueue Tiket ke Queue\n";
        cout << "6. Dequeue Tiket dari Queue\n";
        cout << "7. Urutkan Tiket (Ascending Menggunakan Mergesort)\n";
        cout << "8. Urutkan Tiket (Descending Menggunakan Quicksort)\n";
        cout << "9. Keluar\n";

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
                pushTiket(stack, jumlahTiket);
                break;
            case 4:
                popTiket(stack, jumlahTiket);
                break;
            case 5:
                enqueueTiket(queue, jumlahTiket);
                break;
            case 6:
                dequeueTiket(queue, jumlahTiket);
                break;
            case 7:
                tiket = mergeSort(tiket);
                cout << "Tiket berhasil diurutkan (Ascending - Berdasarkan Harga Tiket)\n";
                break;
            case 8:
                tiket = quickSort(tiket);
                cout << "Tiket berhasil diurutkan (Descending - Berdasarkan Harga Tiket)\n";
                break;

            case 9:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 9);

    // Hapus semua node ketika program selesai
    TiketKonser* tiketSaatIni;
    while (tiket != nullptr) {
        tiketSaatIni = tiket;
        tiket = tiket->next;
        delete tiketSaatIni;
    }

    return 0;
}
