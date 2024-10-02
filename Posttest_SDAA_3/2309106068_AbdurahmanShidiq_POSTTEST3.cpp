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
    Paket *next;
};

Pelanggan *head_pelanggan = nullptr;
Paket *head_paket = nullptr;

int menu_utama, menu_tambah, menu_ubah, menu_lihat, menu_hapus, idx;
string keluar = "n";
int counter = 3;

void tekan_enter()
{
    cout << "Tekan enter untuk melanjutkan.....";
    cin.ignore();
    cin.get();
    system("cls");
}

void tampil_paket()
{
    system("cls");
    cout << "Tampilkan paket: \n";
    cout << "----------------\n";
    Paket *temp = head_paket;
    int i = 1;
    while (temp != nullptr)
    {
        cout << i << ". " << temp->jenis << endl;
        temp = temp->next;
        i++;
    }
}

void tampil_pelanggan()
{
    system("cls");
    cout << "Tampilkan pelanggan: \n";
    cout << "---------------\n";
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
    cin.ignore();
    Paket *baru = new Paket;
    getline(cin, baru->jenis);
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
    cout << "Berhasil menambah paket.\n";
}

void tambah_pelanggan()
{
    if (head_paket == nullptr)
    {
        cout << "Tidak ada paket yang tersedia. Tambahkan paket terlebih dahulu sebelum menambah pelanggan.\n";
        tekan_enter();
        return;
    }

    int pilih_paket;
    Pelanggan *baru = new Pelanggan;
    system("cls");
    cout << "Masukkan nama pelanggan: ";
    cin.ignore();
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
            baru->jenis_paket = temp->jenis;
            baru->next = nullptr;

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
    system("cls");
    tampil_paket();
    cout << "Masukkan urutan yang ingin dihapus: ";
    cin >> idx;

    if (head_paket == nullptr)
    {
        cout << "Tidak ada paket untuk dihapus.\n";
        return;
    }

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
    system("cls");
    tampil_pelanggan();
    cout << "Masukkan urutan pelanggan yang ingin dihapus: ";
    cin >> idx;

    if (head_pelanggan == nullptr)
    {
        cout << "Tidak ada pelanggan untuk dihapus.\n";
        return;
    }

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
            while (true)
            {
                system("cls");
                cout << "Menu Utama:\n"
                     << "------------\n"
                     << "1. Tambah Data\n"
                     << "2. Ubah Data\n"
                     << "3. Lihat Data\n"
                     << "4. Hapus Data\n"
                     << "5. Keluar\n"
                     << "Masukkan pilihan: ";
                cin >> menu_utama;
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
                                system("cls");
                                cout << "Ubah Jenis Paket\n";
                                tampil_paket();
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
                                system("cls");
                                cout << "Ubah Paket Pelanggan\n";
                                tampil_pelanggan();
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
                else if (menu_utama == 5)
                {
                    system("cls");
                    cout << "Apakah anda ingin keluar? (y/n): ";
                    cin >> keluar;
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
