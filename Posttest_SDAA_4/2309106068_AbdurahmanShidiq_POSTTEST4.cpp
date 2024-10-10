#include <iostream>
using namespace std;

struct Pelanggan
{
    string nama;
    string jenis_paket;
    Pelanggan *next;
};

struct Paket
{
    string jenis;
    int kapasitas;
    int jumlah_pelanggan;
    Paket *next;
};

Pelanggan *head_pelanggan = nullptr;
Paket *head_paket = nullptr;

int menu_utama, menu_tambah, menu_ubah, menu_lihat, menu_hapus, idx;
string keluar = "n";
int counter = 3;

struct NodeStack
{
    string data;
    NodeStack *next;
};

NodeStack *top = nullptr;

void push(string value)
{
    NodeStack *baru = new NodeStack;
    baru->data = value;
    baru->next = top;
    top = baru;
}

void pop()
{
    if (top != nullptr)
    {
        NodeStack *temp = top;
        top = top->next;
        delete temp;
    }
}

string peek()
{
    if (top != nullptr)
        return top->data;
    return "";
}

bool isStackEmpty()
{
    return top == nullptr;
}

struct NodeQueue
{
    string data;
    NodeQueue *next;
};

NodeQueue *front = nullptr;
NodeQueue *rear = nullptr;

void enqueue(string value)
{
    NodeQueue *baru = new NodeQueue;
    baru->data = value;
    baru->next = nullptr;

    if (rear == nullptr)
    {
        front = rear = baru;
    }
    else
    {
        rear->next = baru;
        rear = baru;
    }
}

void dequeue()
{
    if (front != nullptr)
    {
        NodeQueue *temp = front;
        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete temp;
    }
}

string getFront()
{
    if (front != nullptr)
        return front->data;
    return "";
}

bool isQueueEmpty()
{
    return front == nullptr;
}

void tekan_enter()
{
    cout << "Tekan enter untuk melanjutkan.....";
    cin.get();
    system("cls");
}

void tampil_paket()
{
    system("cls");
    cout << "Tampilkan paket: \n";
    cout << "---------------\n";
    if (head_paket == nullptr)
    {
        cout << "Tidak ada paket yang tersedia.\n";
        return;
    }

    int no = 1;
    Paket *temp = head_paket;
    while (temp != nullptr)
    {
        cout << no++ << ". " << temp->jenis;
        if (temp->kapasitas == -1)
        {
            cout << " (Tidak Terbatas)";
        }
        else
        {
            cout << " (Kapasitas: " << temp->kapasitas << ", Terdaftar: " << temp->jumlah_pelanggan << ")";
        }
        cout << endl;
        temp = temp->next;
    }
}

void tampil_pelanggan()
{
    system("cls");
    cout << "Tampilkan pelanggan: \n";
    cout << "---------------\n";
    if (head_pelanggan == nullptr)
    {
        cout << "Tidak ada pelanggan yang terdaftar.\n";
        return;
    }

    Pelanggan *temp = head_pelanggan;
    int i = 1;
    while (temp != nullptr)
    {
        cout << i << ".\tNama Pelanggan: " << temp->nama << endl;
        cout << "\tJenis Paket: " << temp->jenis_paket << endl;
        temp = temp->next;
        i++;
    }
}

void tambah_paket()
{
    system("cls");
    cout << "Tambah Jenis Paket\n";
    cout << "Masukkan jenis Paket (Harga/Jangka Waktu): ";
    Paket *baru = new Paket;
    getline(cin, baru->jenis);
    cout << "Masukkan kapasitas maksimal pelanggan (masukkan -1 jika tidak terbatas): ";
    cin >> baru->kapasitas;
    baru->jumlah_pelanggan = 0; // Set jumlah pelanggan awal ke 0
    baru->next = nullptr;

    if (head_paket == nullptr)
    {
        head_paket = baru;
    }
    else
    {
        Paket *temp = head_paket;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = baru;
    }

    // Tambahkan ke riwayat penambahan menggunakan stack
    push("Paket: " + baru->jenis + " (Kapasitas: " + (baru->kapasitas == -1 ? "Tidak Terbatas" : to_string(baru->kapasitas)) + ")");
    cout << "Berhasil menambah paket.\n";
}

void tambah_pelanggan()
{
    if (head_paket == nullptr)
    {
        system("cls");
        cout << "Tidak ada paket yang tersedia. Tambahkan paket terlebih dahulu sebelum menambah pelanggan.\n";
        return;
    }

    int pilih_paket;
    Pelanggan *baru = new Pelanggan;
    system("cls");
    cout << "Masukkan nama pelanggan: ";
    getline(cin, baru->nama);

    while (true)
    {
        system("cls");
        cout << "Nama Pelanggan: " << baru->nama << endl;
        cout << "Menu Jenis Paket: \n";
        tampil_paket();
        cout << "Masukkan pilihan: ";
        cin >> pilih_paket;

        Paket *temp = head_paket;
        for (int i = 1; i < pilih_paket && temp != nullptr; i++)
        {
            temp = temp->next;
        }

        if (temp != nullptr)
        {
            // Periksa apakah paket memiliki batas kapasitas dan sudah penuh
            if (temp->kapasitas != -1 && temp->jumlah_pelanggan >= temp->kapasitas)
            {
                cout << "Maaf, paket " << temp->jenis << " sudah penuh.\n";
                tekan_enter();
                return;
            }

            baru->jenis_paket = temp->jenis;
            baru->next = nullptr;

            // Tambahkan pelanggan ke paket
            if (head_pelanggan == nullptr)
            {
                head_pelanggan = baru;
            }
            else
            {
                Pelanggan *temp_pelanggan = head_pelanggan;
                while (temp_pelanggan->next != nullptr)
                {
                    temp_pelanggan = temp_pelanggan->next;
                }
                temp_pelanggan->next = baru;
            }

            // Tambahkan jumlah pelanggan di paket
            temp->jumlah_pelanggan++;

            // Tambahkan ke riwayat penambahan menggunakan stack
            push("Pelanggan: " + baru->nama + " memilih paket " + temp->jenis);
            cout << "Berhasil menambah pelanggan.\n";
            break;
        }
        else
        {
            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
            tekan_enter();
        }
    }
}

void hapus_paket()
{
    int idx;
    cin.ignore();
    system("cls");
    if (head_paket == nullptr)
    {
        cout << "Tidak ada paket untuk dihapus.\n";
        return;
    }
    tampil_paket();
    cout << "Masukkan urutan yang ingin dihapus: ";
    cin >> idx;

    Paket *temp = head_paket;
    if (idx == 1)
    {
        head_paket = head_paket->next;
        delete temp;
        cout << "Paket berhasil dihapus.\n";
    }
    else
    {
        Paket *prev = nullptr;
        for (int i = 1; i < idx && temp != nullptr; i++)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp != nullptr)
        {
            prev->next = temp->next;
            delete temp;
            cout << "Paket berhasil dihapus.\n";
        }
        else
        {
            cout << "Urutan tidak ditemukan.\n";
        }
    }
}

void hapus_pelanggan()
{
    int idx;
    cin.ignore();
    system("cls");
    if (head_pelanggan == nullptr)
    {
        cout << "Tidak ada pelanggan untuk dihapus.\n";
        return;
    }
    tampil_pelanggan();
    cout << "Masukkan urutan pelanggan yang ingin dihapus: ";
    cin >> idx;

    Pelanggan *temp = head_pelanggan;
    if (idx == 1)
    {
        head_pelanggan = head_pelanggan->next;
        delete temp;
        cout << "Pelanggan berhasil dihapus.\n";
    }
    else
    {
        Pelanggan *prev = nullptr;
        for (int i = 1; i < idx && temp != nullptr; i++)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp != nullptr)
        {
            prev->next = temp->next;
            delete temp;
            cout << "Pelanggan berhasil dihapus.\n";
        }
        else
        {
            cout << "Urutan tidak ditemukan.\n";
        }
    }
}

void antrian_paket_populer()
{
    if (head_paket == nullptr)
    {
        system("cls");
        cout << "Tidak ada paket yang tersedia. Tambahkan paket terlebih dahulu.\n";
        return;
    }

    system("cls");
    cout << "Pendaftaran untuk Paket Populer Terbatas\n";
    cout << "Masukkan nama pelanggan: ";
    string nama;
    cin.ignore();
    getline(cin, nama);

    int pilih_paket;
    while (true)
    {
        system("cls");
        cout << "Nama Pelanggan: " << nama << endl;
        cout << "Menu Jenis Paket: \n";
        tampil_paket();
        cout << "Masukkan pilihan paket populer: ";
        cin >> pilih_paket;

        Paket *temp = head_paket;
        for (int i = 1; i < pilih_paket && temp != nullptr; i++)
        {
            temp = temp->next;
        }

        if (temp != nullptr)
        {
            if (temp->kapasitas != -1 && temp->jumlah_pelanggan >= temp->kapasitas)
            {
                enqueue(nama);
                cout << "Paket " << temp->jenis << " sudah penuh. Pelanggan " << nama << " telah ditambahkan ke antrian.\n";
            }
            else
            {
                cout << "Paket masih tersedia. Pelanggan dapat langsung memilih paket.\n";
            }
            tekan_enter();
            break;
        }
        else
        {
            cout << "Paket tidak ditemukan.\n";
            tekan_enter();
        }
    }
}

void tampilkan_riwayat_penambahan()
{
    system("cls");
    cout << "Riwayat Penambahan Terbaru:\n";
    cout << "---------------------------\n";

    if (isStackEmpty())
    {
        cout << "Belum ada riwayat penambahan.\n";
    }
    else
    {
        NodeStack *temp = top;
        while (temp != nullptr)
        {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
}

void menu()
{
    while (true)
    {
        system("cls");
        cout << "Menu Utama:\n"
             << "------------\n"
             << "1. Tambah Data\n"
             << "2. Ubah Data\n"
             << "3. Lihat Data\n"
             << "4. Hapus Data\n"
             << "5. Lihat Riwayat Penambahan\n"
             << "6. Antrian Paket Populer\n"
             << "7. Keluar\n"
             << "Masukkan pilihan: ";
        cin >> menu_utama;
        cin.ignore();
        if (menu_utama == 1)
        {
            while (true)
            {
                system("cls");
                cout << "Menu Tambah Data:\n"
                     << "-----------------\n"
                     << "1. Tambah Jenis Paket\n"
                     << "2. Tambah Pelanggan\n"
                     << "3. Kembali\n"
                     << "Masukkan pilihan: ";
                cin >> menu_tambah;
                cin.ignore();
                if (menu_tambah == 1)
                {
                    tambah_paket();
                    tekan_enter();
                }
                else if (menu_tambah == 2)
                {
                    tambah_pelanggan();
                    tekan_enter();
                }
                else if (menu_tambah == 3)
                {
                    menu();
                }
                else
                {
                    system("cls");
                    cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                    tekan_enter();
                }
            }
        }
        else if (menu_utama == 2)
        {
            while (true)
            {
                system("cls");
                cout << "Menu Ubah Data:\n"
                     << "---------------\n"
                     << "1. Ubah Jenis Paket\n"
                     << "2. Ubah Paket Pelanggan\n"
                     << "3. Kembali\n"
                     << "Masukkan pilihan: ";
                cin >> menu_ubah;
                if (menu_ubah == 1)
                {
                    while (true)
                    {
                        cin.ignore();
                        system("cls");
                        cout << "Ubah Jenis Paket\n";
                        tampil_paket();
                        if (head_paket == nullptr)
                        {
                            system("cls");
                            cout << "Tidak ada paket yang tersedia.\n";
                            tekan_enter();
                            break;
                        }
                        cout << "Masukkan urutan jenis paket yang ingin diubah (atau 0 untuk kembali): ";
                        cin >> idx;
                        if (idx == 0)
                        {
                            break;
                        }
                        Paket *temp = head_paket;
                        int index = 1;
                        while (temp != nullptr && index < idx)
                        {
                            temp = temp->next;
                            index++;
                        }
                        if (temp != nullptr)
                        {
                            cout << "Masukkan jenis paket baru (Harga/Jangka Waktu): ";
                            cin.ignore();
                            getline(cin, temp->jenis);
                            system("cls");
                            cout << "Paket berhasil diubah!\n";
                            tekan_enter();
                        }
                        else
                        {
                            cout << "Paket tidak ditemukan.\n";
                            tekan_enter();
                        }
                    }
                }
                else if (menu_ubah == 2)
                {
                    while (true)
                    {
                        cin.ignore();
                        system("cls");
                        cout << "Ubah Paket Pelanggan\n";
                        tampil_pelanggan();
                        if (head_pelanggan == nullptr)
                        {
                            system("cls");
                            cout << "Tidak ada pelanggan yang terdaftar.\n";
                            tekan_enter();
                            break;
                        }
                        cout << "Masukkan urutan pelanggan yang ingin diubah paketnya (atau 0 untuk kembali): ";
                        cin >> idx;
                        if (idx == 0)
                        {
                            break;
                        }
                        Pelanggan *temp_pelanggan = head_pelanggan;
                        int index = 1;
                        while (temp_pelanggan != nullptr && index < idx)
                        {
                            temp_pelanggan = temp_pelanggan->next;
                            index++;
                        }
                        if (temp_pelanggan != nullptr)
                        {
                            int pilih_paket;
                            system("cls");
                            cout << "Nama Pelanggan: " << temp_pelanggan->nama << endl;
                            cout << "Pilih Paket Baru:\n";
                            tampil_paket();
                            cout << "Masukkan pilihan paket: ";
                            cin >> pilih_paket;
                            Paket *temp_paket = head_paket;
                            index = 1;
                            while (temp_paket != nullptr && index < pilih_paket)
                            {
                                temp_paket = temp_paket->next;
                                index++;
                            }

                            if (temp_paket != nullptr)
                            {
                                temp_pelanggan->jenis_paket = temp_paket->jenis;
                                cout << "Paket pelanggan berhasil diubah!\n";
                                tekan_enter();
                            }
                            else
                            {
                                cout << "Paket tidak ditemukan.\n";
                                tekan_enter();
                            }
                        }
                        else
                        {
                            cout << "Pelanggan tidak ditemukan.\n";
                            tekan_enter();
                        }
                    }
                }
                else if (menu_ubah == 3)
                {
                    menu();
                }
                else
                {
                    system("cls");
                    cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                    tekan_enter();
                }
            }
        }
        else if (menu_utama == 3)
        {
            while (true)
            {
                system("cls");
                cout << "Menu Lihat Data:\n"
                     << "----------------\n"
                     << "1. Lihat Jenis Paket\n"
                     << "2. Lihat Pelanggan\n"
                     << "3. Kembali\n"
                     << "Masukkan pilihan: ";
                cin >> menu_lihat;
                cin.ignore();
                if (menu_lihat == 1)
                {
                    tampil_paket();
                    tekan_enter();
                }
                else if (menu_lihat == 2)
                {
                    tampil_pelanggan();
                    tekan_enter();
                }
                else if (menu_lihat == 3)
                {
                    menu();
                }
                else
                {
                    system("cls");
                    cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                    tekan_enter();
                }
            }
        }
        else if (menu_utama == 4)
        {
            while (true)
            {
                system("cls");
                cout << "Menu Hapus Data:\n"
                     << "----------------\n"
                     << "1. Hapus Jenis Paket\n"
                     << "2. Hapus Pelanggan\n"
                     << "3. Kembali\n"
                     << "Masukkan pilihan: ";
                cin >> menu_hapus;
                if (menu_hapus == 1)
                {
                    hapus_paket();
                    tekan_enter();
                }
                else if (menu_hapus == 2)
                {
                    hapus_pelanggan();
                    tekan_enter();
                }
                else if (menu_hapus == 3)
                {
                    break;
                }
                else
                {
                    system("cls");
                    cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                    tekan_enter();
                }
            }
        }
        if (menu_utama == 5)
        {
            tampilkan_riwayat_penambahan();
            tekan_enter();
        }
        else if (menu_utama == 6)
        {
            antrian_paket_populer();
            tekan_enter();
        }
        else if (menu_utama == 7)
        {
            system("cls");
            cout << "Apakah anda ingin keluar? (y/n): ";
            cin >> keluar;
            cin.ignore();
            if (keluar != "n")
            {
                system("cls");
                cout << "PROGRAM BERHENTI";
                return;
            }
        }
        else
        {
            system("cls");
            cout << "Maaf pilihan anda salah! Silakan coba lagi." << endl;
            tekan_enter();
        }
    }
};

void login(int counter)
{
    string username;
    string password;
    if (counter == 0)
    {
        system("cls");
        cout << "Maaf, Kesempatan login anda telah habis.";
    }
    else if (counter > 0)
    {
        cout << "HALAMAN LOGIN" << endl;
        cout << "Masukkan username: ";
        getline(cin, username);
        cout << "Masukkan password: ";
        getline(cin, password);
        if (username == "Abdurahman Shidiq" && password == "2309106068")
        {
            menu();
        }
        else if (username == "Abdurahman Shidiq" && password != "2309106068")
        {
            system("cls");
            cout << "Password salah. Coba lagi." << endl;
            cout << "Sisa kesempatan login: " << counter - 1 << endl;
            login(counter - 1);
        }
        else if (username != "Abdurahman Shidiq" && password == "2309106068")
        {
            system("cls");
            cout << "Username salah. Coba lagi." << endl;
            cout << "Sisa kesempatan login: " << counter - 1 << endl;
            login(counter - 1);
        }
        else
        {
            system("cls");
            cout << "Username dan Password salah. Coba lagi." << endl;
            cout << "Sisa kesempatan login: " << counter - 1 << endl;
            login(counter - 1);
        }
    }
    else
    {
        system("cls");
        cout << "Program Berhenti";
    }
}

int main()
{
    login(counter);
    return 0;
}
