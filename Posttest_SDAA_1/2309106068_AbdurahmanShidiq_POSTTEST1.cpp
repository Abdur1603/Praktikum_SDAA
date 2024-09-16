#include <iostream>
using namespace std;

int tingkat;

// Fungsi rekursif untuk menghitung nilai segitiga pascal (baris,kolom)
int nilai_pascal(int baris, int kolom)
{
    if (kolom == 0 || kolom == baris)
    {
        return 1;
    }
    return nilai_pascal(baris - 1, kolom - 1) + nilai_pascal(baris - 1, kolom);
}

// Fungsi untuk mencetak Segitiga Pascal
void segitigaPascal(int tingkat)
{
    for (int baris = 0; baris < tingkat; baris++)
    {

        // Menampilkan nilai-nilai dalam segitiga Pascal
        for (int kolom = 0; kolom <= baris; kolom++)
        {
            cout << nilai_pascal(baris, kolom) << " ";
        }
        cout << endl;
    }
}

// Fungsi untuk menghitung bilangan pokok berpangkat
// bilangan utama yang berpangkat disebut pokok
// bilangan yang berada diatas bilangan pokok sebagai pangkat disebut eksponen
int pangkat(int pokok, int eksponen)
{
    int hasil = 1;
    for (int i = 0; i < eksponen; i++)
    {
        hasil *= pokok;
    }
    return hasil;
}

// Fungsi untuk membuat rumus pangkat berdasarkan segitiga pascal dan menghitung hasilnya
int hasil_pangkat_segitiga_pascal(int a, int b, int baris)
{
    int hasil_akhir = 0; // Untuk menyimpan hasil akhir perhitungan
    cout << endl
         << "Rumus pangkat dalam segitiga pascal tingkat " << tingkat << " :" << endl;
    cout << "(" << a << " + " << b << ")^" << baris << " = ";

    // perulangan untuk menghitung dan mencetak setiap suku
    for (int kolom = 0; kolom <= baris; ++kolom)
    {
        // koefisien dalam rumus pangkat segitiga pascal merupakan hasil dari segitiga pascal
        int koefisien = nilai_pascal(baris, kolom);

        // Hitung nilai dari setiap suku
        // satu suku dipisahkan oleh tanda operator seperti + atau -
        // contohnya pada (a + b)^3 = a^3 + 3a^2b + 3ab^2 + b^3
        // maka a^3 adalah suku pertama, 3a^2b adalah suku kedua, dan seterusnya
        int hasil_suku = koefisien * pangkat(a, baris - kolom) * pangkat(b, kolom);
        hasil_akhir += hasil_suku; // Tambahkan nilai setiap suku ke hasil akhir

        // Mencetak koefisien setiap suku
        if (koefisien != 1)
            cout << koefisien;

        // Mencetak bagian variabel a
        if (baris - kolom > 0) // Jika pangkat a sama dengan 0, maka variabel a tidak perlu ditulis
        {
            cout << "a";
            if (baris - kolom > 1) // Jika pangkat a sama dengan 1, maka pangkat tidak perlu ditulis
                cout << "^" << baris - kolom;
        }

        // Mencetak bagian variabel b
        if (kolom > 0) // Jika pangkat b sama dengan 0, maka variabel b tidak perlu ditulis
        {
            cout << "b";
            if (kolom > 1) // Jika pangkat b sama dengan 1, maka pangkat tidak perlu ditulis
                cout << "^" << kolom;
        }

        // Menambahkan tanda plus di antara suku-suku
        if (kolom != baris)
            cout << " + ";
    }
    cout << endl;
    return hasil_akhir;
}

int main()
{
    int a, b, baris;

    // Memasukkan nilai a, b, dan tingkat eksponen baris
    cout << "Masukkan nilai a: ";
    cin >> a;
    cout << "Masukkan nilai b: ";
    cin >> b;
    cout << "Masukkan tingkat segitiga pascal: ";
    cin >> tingkat;
    baris = tingkat - 1;

    // Mencetak segitiga pascal
    segitigaPascal(tingkat);
    // Hitung dan tampilkan hasilnya
    int hasil_akhir = hasil_pangkat_segitiga_pascal(a, b, baris);
    cout << endl
         << "Hasil dari (" << a << " + " << b << ")^" << baris << " = " << hasil_akhir << endl;

    return 0;
}
