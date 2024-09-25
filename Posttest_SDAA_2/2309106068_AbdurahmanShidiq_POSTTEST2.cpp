#include <iostream>
using namespace std;

const int MAX_PELANGGAN = 50;
const int MAX_PAKET = 50;

struct Pelanggan
{
    string nama;
    string jenis_paket;
};

struct Paket
{
    string jenis;
};

Pelanggan pelanggan[MAX_PELANGGAN];
Paket paket[MAX_PAKET];

int jml_pelanggan = 0;
int jml_paket = 0;
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
    for (int i = 0; i < jml_paket; i++)
    {
        cout << i + 1 << ". " << paket[i].jenis << endl;
    }
}

void tampil_pelanggan_ptr(Pelanggan *pelangganArr)
{
    system("cls");
    cout << "Tampilkan pelanggan: \n";
    cout << "---------------\n";
    for (int i = 0; i < jml_pelanggan; i++)
    {
        cout << i + 1 << ".\tNama Pelanggan: " << (pelangganArr + i)->nama << endl;
        cout << "\tJenis Paket: " << (pelangganArr + i)->jenis_paket << endl
             << endl;
    }
}

string tambah_paket()
{
    system("cls");
    cout << "Tambah Jenis Paket\n";
    cout << "Masukkan jenis Paket (Harga/Jangka Waktu): ";
    cin.ignore();
    getline(cin, paket[jml_paket].jenis);
    jml_paket++;
    return "Berhasil menambah paket.\n";
}

string tambah_pelanggan_ptr(Pelanggan *pelangganPtr)
{
    try
    {
        int pilih_paket;
        while (true)
        {
            system("cls");
            cout << "Masukkan nama pelanggan: ";
            cin.ignore();
            getline(cin, pelangganPtr->nama);
            system("cls");
            cout << "Nama Pelanggan: " << pelangganPtr->nama << endl;
            cout << "Menu Jenis Paket: \n";
            tampil_paket();
            cout << jml_paket + 1 << ". Kembali\n";
            cout << "Masukkan pilihan: ";
            cin >> pilih_paket;
            if (pilih_paket == jml_paket + 1)
            {
                break;
            }
            else if (pilih_paket <= jml_paket)
            {
                pelangganPtr->jenis_paket = paket[pilih_paket - 1].jenis;
                jml_pelanggan++;
                break;
            }
            else
            {
                system("cls");
                cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                tekan_enter();
            }
        }
        return "Berhasil menambah pelanggan.\n";
    }
    catch (...)
    {
        cout << "Terjadi Kesalahan, Silahkan coba lagi!";
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
            try
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
                                cout << tambah_paket();
                                tekan_enter();
                            }
                            else if (menu_tambah == 2)
                            {
                                cout << tambah_pelanggan_ptr(&pelanggan[jml_pelanggan]);
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
                                    cout << jml_paket + 1 << ". Kembali\n";
                                    cout << "Masukkan urutan jenis paket yang ingin diubah: ";
                                    cin >> idx;
                                    if (idx >= 1 && idx <= jml_paket)
                                    {
                                        cout << "Masukkan jenis paket baru (Harga/Jangka Waktu): ";
                                        cin.ignore();
                                        getline(cin, paket[idx - 1].jenis);
                                    }
                                    else if (idx == jml_paket + 1)
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
                            else if (menu_ubah == 2)
                            {
                                while (true)
                                {
                                    system("cls");
                                    cout << "Ubah Paket Pelanggan\n";
                                    tampil_pelanggan_ptr(pelanggan);
                                    cout << jml_pelanggan / 2 + 1 << "\tKembali\n";
                                    cout << "Masukkan urutan pelanggan yang ingin diubah: ";
                                    cin >> idx;
                                    if (idx >= 1 && idx <= jml_pelanggan / 2)
                                    {
                                        int pilih_paket;
                                        system("cls");
                                        cout << "Nama Pelanggan: " << pelanggan[idx * 2 - 2].nama << endl;
                                        cout << "Menu Jenis Paket: \n";
                                        tampil_paket();
                                        cout << jml_paket + 1 << ". Kembali\n";
                                        cout << "Masukkan pilihan: ";
                                        cin >> pilih_paket;
                                        if (pilih_paket <= jml_paket)
                                        {
                                            pelanggan[idx * 2 - 1].jenis_paket = paket[pilih_paket - 1].jenis;
                                        }
                                        else if (pilih_paket == jml_paket + 1)
                                        {
                                            continue;
                                        }
                                        else
                                        {
                                            system("cls");
                                            cout << "Maaf, pilihan tidak tersedia.\nSilahkan masukkan lagi.";
                                            tekan_enter();
                                        }
                                    }
                                    else if (idx == jml_pelanggan / 2 + 1)
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
                                 << "2. Lihat Paket Pelanggan\n"
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
                                tampil_pelanggan_ptr(pelanggan);
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
                                while (true)
                                {
                                    system("cls");
                                    cout << "Menu Hapus Paket\n";
                                    tampil_paket();
                                    cout << jml_paket + 1 << ". Kembali\n";
                                    cout << "Masukkan urutan yang ingin di hapus: ";
                                    cin >> idx;
                                    if (idx >= 1 && idx <= jml_paket)
                                    {
                                        for (int i = idx - 1; i < jml_paket; i++)
                                            paket[i] = paket[i + 1];
                                        jml_paket--;
                                        break;
                                    }
                                    else if (idx == jml_paket + 1)
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
                            else if (menu_hapus == 2)
                            {
                                while (true)
                                {
                                    system("cls");
                                    cout << "Menu Hapus Pelanggan\n";
                                    tampil_pelanggan_ptr(pelanggan);
                                    cout << jml_pelanggan + 1 << ".\tKembali.\n";
                                    cout << "Masukkan urutan yang ingin dihapus: ";
                                    cin >> idx;
                                    if (idx >= 1 && idx <= jml_pelanggan)
                                    {
                                        for (int i = (idx - 1); i < jml_pelanggan - 1; i++)
                                        {
                                            pelanggan[i].nama = pelanggan[i + 2].nama;
                                            pelanggan[i].jenis_paket = pelanggan[i + 2].jenis_paket;
                                        }
                                        jml_pelanggan--;
                                        break;
                                    }
                                    else if (idx == jml_pelanggan + 1)
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
            catch (...)
            {
                cout << "Terjadi Kesalahan, Silahkan coba lagi!";
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