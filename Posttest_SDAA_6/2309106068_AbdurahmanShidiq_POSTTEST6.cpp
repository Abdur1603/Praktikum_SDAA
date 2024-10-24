#include <iostream>
#include <string>
#include <unordered_map>
#include <bits/stdc++.h>
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
Pelanggan *tail_pelanggan = nullptr;

Paket *head_paket = nullptr;
Paket *tail_paket = nullptr;

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

bool isStackEmpty()
{
    return top == nullptr;
}

struct NodeQueueSewa
{
    string nama_pelanggan;
    int durasi;
    NodeQueueSewa *next;
};

NodeQueueSewa *front = nullptr;
NodeQueueSewa *rear = nullptr;

void enqueueSewa(string nama, int durasi)
{
    NodeQueueSewa *baru = new NodeQueueSewa;
    baru->nama_pelanggan = nama;
    baru->durasi = durasi;
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
    cout << nama << " berhasil ditambahkan ke antrian penyewaan gym dengan durasi " << durasi << " jam.\n";
}

void dequeueSewa()
{
    if (front == nullptr)
    {
        system("cls");
        cout << "Antrian penyewaan gym kosong.\n";
        return;
    }

    NodeQueueSewa *temp = front;
    front = front->next;

    if (front == nullptr)
    {
        rear = nullptr;
    }

    system("cls");
    cout << temp->nama_pelanggan << " telah selesai menyewa gym selama " << temp->durasi << " jam.\n";
    delete temp;
}

void tekan_enter()
{
    cout << "Tekan enter untuk melanjutkan.....";
    cin.get();
    system("cls");
}

Paket *getTail(Paket *head)
{
    while (head != nullptr && head->next != nullptr)
    {
        head = head->next;
    }
    return head;
}

Paket *partition(Paket *head, Paket *end, Paket **newHead, Paket **newEnd)
{
    Paket *pivot = end;
    Paket *prev = nullptr, *curr = head, *tail = pivot;

    while (curr != pivot)
    {
        if (curr->jenis < pivot->jenis)
        {
            if ((*newHead) == nullptr)
                (*newHead) = curr;
            prev = curr;
            curr = curr->next;
        }
        else
        {
            if (prev)
                prev->next = curr->next;
            Paket *temp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    if ((*newHead) == nullptr)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

Paket *quickSortRecur(Paket *head, Paket *end)
{
    if (!head || head == end)
        return head;

    Paket *newHead = nullptr, *newEnd = nullptr;
    Paket *pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        Paket *temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;
        newHead = quickSortRecur(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

void quickSortPaket()
{
    system("cls");
    if (!head_paket || !head_paket->next)
    {
        cout << "Tidak ada paket yang perlu diurutkan.\n";
        return;
    }
    head_paket = quickSortRecur(head_paket, getTail(head_paket));
    cout << "Data paket berhasil diurutkan secara ascending.\n";
}

int listLength(Paket *head)
{
    int length = 0;
    while (head != nullptr)
    {
        length++;
        head = head->next;
    }
    return length;
}

Paket *getNodeAt(Paket *head, int index)
{
    for (int i = 0; i < index && head != nullptr; i++)
    {
        head = head->next;
    }
    return head;
}

void shellSortPaket()
{
    int length = listLength(head_paket);
    for (int gap = length / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < length; i++)
        {
            Paket *tempNode = getNodeAt(head_paket, i);
            string temp = tempNode->jenis;

            int j;
            for (j = i; j >= gap && getNodeAt(head_paket, j - gap)->jenis < temp; j -= gap)
            {
                getNodeAt(head_paket, j)->jenis = getNodeAt(head_paket, j - gap)->jenis;
            }
            getNodeAt(head_paket, j)->jenis = temp;
        }
    }
    system("cls");
    cout << "Data paket berhasil diurutkan secara descending.\n";
}

void tampil_paket()
{
    int pilihan;
    system("cls");
    cout << "Tampilkan paket: \n";
    cout << "---------------\n";
    if (head_paket == nullptr)
    {
        cout << "Tidak ada paket yang tersedia.\n";
        return;
    }

    cout << "1. Tampilkan paket secara ascending\n";
    cout << "2. Tampilkan paket secara descending\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1)
    {
        quickSortPaket();
    }
    else if (pilihan == 2)
    {
        shellSortPaket();
    }
    else
    {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    Paket *temp = head_paket;
    int no = 1;
    while (temp != nullptr)
    {
        cout << no++ << ". " << temp->jenis;
        cout << endl;
        temp = temp->next;
    }
}

Pelanggan *getTail(Pelanggan *head)
{
    while (head != nullptr && head->next != nullptr)
    {
        head = head->next;
    }
    return head;
}

Pelanggan *partitionPelanggan(Pelanggan *head, Pelanggan *end, Pelanggan **newHead, Pelanggan **newEnd)
{
    Pelanggan *pivot = end;
    Pelanggan *prev = nullptr, *curr = head, *tail = pivot;

    while (curr != pivot)
    {
        if (curr->nama < pivot->nama)
        {
            if ((*newHead) == nullptr)
                (*newHead) = curr;
            prev = curr;
            curr = curr->next;
        }
        else
        {
            if (prev)
                prev->next = curr->next;
            Pelanggan *temp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    if ((*newHead) == nullptr)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

Pelanggan *quickSortRecurPelanggan(Pelanggan *head, Pelanggan *end)
{
    if (!head || head == end)
        return head;

    Pelanggan *newHead = nullptr, *newEnd = nullptr;
    Pelanggan *pivot = partitionPelanggan(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        Pelanggan *temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;
        newHead = quickSortRecurPelanggan(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecurPelanggan(pivot->next, newEnd);
    return newHead;
}

void quickSortPelanggan()
{
    system("cls");
    if (!head_pelanggan || !head_pelanggan->next)
    {
        cout << "Tidak ada pelanggan yang perlu diurutkan.\n";
        return;
    }
    head_pelanggan = quickSortRecurPelanggan(head_pelanggan, getTail(head_pelanggan));
    cout << "Data pelanggan berhasil diurutkan secara ascending.\n";
}

int listLengthPelanggan(Pelanggan *head)
{
    int length = 0;
    while (head != nullptr)
    {
        length++;
        head = head->next;
    }
    return length;
}

Pelanggan *getNodeAtPelanggan(Pelanggan *head, int index)
{
    for (int i = 0; i < index && head != nullptr; i++)
    {
        head = head->next;
    }
    return head;
}

void shellSortPelanggan()
{
    int length = listLengthPelanggan(head_pelanggan);
    for (int gap = length / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < length; i++)
        {
            Pelanggan *tempNode = getNodeAtPelanggan(head_pelanggan, i);
            string temp = tempNode->nama;

            int j;
            for (j = i; j >= gap && getNodeAtPelanggan(head_pelanggan, j - gap)->nama > temp; j -= gap)
            {
                getNodeAtPelanggan(head_pelanggan, j)->nama = getNodeAtPelanggan(head_pelanggan, j - gap)->nama;
            }
            getNodeAtPelanggan(head_pelanggan, j)->nama = temp;
        }
    }
    system("cls");
    cout << "Data pelanggan berhasil diurutkan secara descending.\n";
}

void tampil_pelanggan()
{
    int pilihan;
    system("cls");
    cout << "Tampilkan pelanggan: \n";
    cout << "-------------------\n";
    if (head_pelanggan == nullptr)
    {
        cout << "Tidak ada pelanggan yang tersedia.\n";
        return;
    }

    cout << "1. Tampilkan pelanggan secara ascending\n";
    cout << "2. Tampilkan pelanggan secara descending\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1)
    {
        quickSortPelanggan();
    }
    else if (pilihan == 2)
    {
        shellSortPelanggan();
    }
    else
    {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    Pelanggan *temp = head_pelanggan;
    int i = 1;
    while (temp != nullptr)
    {
        cout << i++ << ".\tNama Pelanggan: " << temp->nama << endl;
        cout << "\tJenis Paket: " << temp->jenis_paket << endl;
        cout << endl;
        temp = temp->next;
    }
}

void tambah_paket()
{
    system("cls");
    cout << "Tambah Jenis Paket\n";
    cout << "Masukkan jenis Paket (Harga/Jangka Waktu): ";
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
    push("Paket: " + baru->jenis + " berhasil ditambahkan.");
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

void ubah_paket()
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
            cout << "Ubah Jenis Paket: \n";
            cout << "-----------------\n";
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

void ubah_paket_pelanggan()
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
            cout << "Ubah Paket Pelanggan: \n";
            cout << "---------------------\n";
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

void tampil_antrian_sewa()
{
    system("cls");
    if (front == nullptr)
    {
        cout << "Antrian penyewaan gym kosong.\n";
        return;
    }

    cout << "Antrian Penyewaan Gym:\n";
    cout << "----------------------\n";
    NodeQueueSewa *temp = front;
    int i = 1;
    while (temp != nullptr)
    {
        cout << i++ << ". " << temp->nama_pelanggan << " - Durasi: " << temp->durasi << " jam\n";
        temp = temp->next;
    }
}

void sewa_gym()
{
    system("cls");
    if (head_pelanggan == nullptr)
    {
        cout << "Tidak ada pelanggan yang terdaftar.\n";
        return;
    }

    int idx, durasi;
    tampil_pelanggan();
    cout << "Masukkan urutan pelanggan yang ingin menyewa gym: ";
    cin >> idx;
    cin.ignore();
    Pelanggan *temp_pelanggan = head_pelanggan;
    int i = 1;

    while (temp_pelanggan != nullptr && i < idx)
    {
        temp_pelanggan = temp_pelanggan->next;
        i++;
    }

    if (temp_pelanggan != nullptr)
    {
        cout << "Masukkan durasi penyewaan (jam): ";
        cin >> durasi;
        enqueueSewa(temp_pelanggan->nama, durasi);
    }
    else
    {
        cout << "Pelanggan tidak ditemukan.\n";
    }
}

void menu_sewa()
{
    int menu_antrian;
    while (true)
    {
        system("cls");
        cout << "Antrian Penyewaan GYM\n";
        cout << "---------------------\n";
        cout << "1. Tambah Penyewaan GYM\n";
        cout << "2. Tampilkan Antrian\n";
        cout << "3. Selesaikan Penyewaan (Dequeue)\n";
        cout << "4. Kembali\n";
        cout << "Masukkan pilihan: ";
        cin >> menu_antrian;
        cin.ignore();

        if (menu_antrian == 1)
        {
            sewa_gym();
            tekan_enter();
        }
        else if (menu_antrian == 2)
        {
            tampil_antrian_sewa();
            tekan_enter();
        }
        else if (menu_antrian == 3)
        {
            dequeueSewa();
            tekan_enter();
        }
        else if (menu_antrian == 4)
        {
            break;
        }
        else
        {
            cout << "Pilihan tidak valid. Coba lagi.\n";
            tekan_enter();
        }
    }
}

int length(NodeQueueSewa *front)
{
    int count = 0;
    NodeQueueSewa *temp = front;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
};

int min(int x, int y) { return (x <= y) ? x : y; };

int fibMonaccianSearch(NodeQueueSewa *front, int x, int n)
{
    NodeQueueSewa *temp = front;
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;
    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    int offset = -1;
    while (fibM > 1)
    {
        int i = min(offset + fibMMm2, n - 1);

        temp = front;
        for (int j = 0; j < i; j++)
        {
            temp = temp->next;
        }

        if (temp->durasi < x)
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (temp->durasi > x)
        {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else
            return i;
    }
    temp = front;
    for (int j = 0; j < offset + 1; j++)
    {
        temp = temp->next;
    }
    if (fibMMm1 && temp->durasi == x)
        return offset + 1;
    return -1;
}

int findNode(NodeQueueSewa *front, int idx)
{
    for (int i = 0; i < idx; i++)
    {
        front = front->next;
    }
    return front->durasi;
}

int jumpSearch(NodeQueueSewa *front, int x, int n)
{
    int step = sqrt(n);
    int prev = 0;
    int idx = min(step, n) - 1;
    while (findNode(front, idx) < x)
    {
        prev = step;
        step += sqrt(n);
        idx = min(step, n) - 1;
        if (prev >= n)
        {
            return -1;
        }
    }
    while (findNode(front, prev) < x)
    {
        prev++;
    }
    cout << endl;
    if (findNode(front, prev) == x)
    {
        return prev;
    }
    return -1;
}

void jump_output()
{
    int x;
    cout << "Masukkan durasi penyewaan yang ingin dicari: ";
    cin >> x;
    int idx = jumpSearch(front, x, length(front));
    if (idx != -1)
    {
        cout << "Data ditemukan pada urutan ke-" << idx + 1 << endl;
    }
    else
    {
        cout << "Data tidak ditemukan.\n";
    }
    tekan_enter();
}

void fibonacci_output()
{
    int x;
    cout << "Masukkan durasi penyewaan yang ingin dicari: ";
    cin >> x;
    int idx = fibMonaccianSearch(front, x, length(front));
    if (idx != -1)
    {
        cout << "Data ditemukan pada urutan ke-" << idx + 1 << endl;
    }
    else
    {
        cout << "Data tidak ditemukan.\n";
    }
    tekan_enter();
};

void badCharHeuristic(string str, int size, unordered_map<char, int> &badChar)
{
    for (int i = 0; i < size; i++)
    {
        badChar[str[i]] = i;
    }
}

bool boyerMoorePaket(string text, string pattern)
{
    int m = pattern.size();
    int n = text.size();

    unordered_map<char, int> badChar;
    badCharHeuristic(pattern, m, badChar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
        {
            j--;
        }

        if (j < 0)
        {
            return true;
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        }
        else
        {
            s += max(1, j - badChar[text[s + j]]);
        }
    }
    return false;
}

void boyerMoorePaketOutput()
{
    string searchTerm;
    cout << "Masukkan jenis paket yang ingin dicari: ";
    getline(cin, searchTerm);

    Paket *temp = head_paket;
    bool found = false;

    while (temp != nullptr)
    {
        if (boyerMoorePaket(temp->jenis, searchTerm))
        {
            cout << "Data ditemukan!\n";
            cout << "Jenis Paket: " << temp->jenis << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "Data tidak ditemukan.\n";
    }
    tekan_enter();
}

bool boyerMoorePelanggan(string text, string pattern)
{
    int m = pattern.size();
    int n = text.size();

    unordered_map<char, int> badChar;
    badCharHeuristic(pattern, m, badChar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
        {
            j--;
        }

        if (j < 0)
        {
            return true;
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        }
        else
        {
            s += max(1, j - badChar[text[s + j]]);
        }
    }
    return false;
}

void boyerMoorePelangganOutput()
{
    string searchTerm;
    cout << "Masukkan nama pelanggan yang ingin dicari: ";
    getline(cin, searchTerm);

    Pelanggan *temp = head_pelanggan;
    bool found = false;

    while (temp != nullptr)
    {
        if (boyerMoorePelanggan(temp->nama, searchTerm))
        {
            cout << "Data ditemukan!\n";
            cout << "Nama Pelanggan: " << temp->nama << endl;
            cout << "Jenis Paket: " << temp->jenis_paket << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "Data tidak ditemukan.\n";
    }
    tekan_enter();
}

void menu_search_durasi()
{
    int pilihan;
    while (true)
    {
        system("cls");
        cout << "Menu Searching\n";
        cout << "--------------\n";
        cout << "1. Fibonacci Search\n";
        cout << "2. Jump Search\n";
        cout << "3. Kembali\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();
        if (pilihan == 1)
        {
            fibonacci_output();
            tekan_enter();
        }
        else if (pilihan == 2)
        {
            jump_output();
            tekan_enter();
        }
        else if (pilihan == 3)
        {
            break;
        }
        else
        {
            cout << "Pilihan tidak valid. Coba lagi.\n";
            tekan_enter();
        }
    }
};

void menu_search()
{
    int pilihan;
    while (true)
    {
        system("cls");
        cout << "Menu Searching\n";
        cout << "--------------\n";
        cout << "1. Mencari Jenis paket\n";
        cout << "2. Mencari Nama Pelanggan\n";
        cout << "3. Mencari Durasi Sewa\n";
        cout << "4. Kembali\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();
        if (pilihan == 1)
        {
            boyerMoorePaketOutput();
        }
        else if (pilihan == 2)
        {
            boyerMoorePelangganOutput();
        }
        else if (pilihan == 3)
        {
            menu_search_durasi();
        }
        else if (pilihan == 4)
        {
            break;
        }
        else
        {
            cout << "Pilihan tidak valid. Coba lagi.\n";
            tekan_enter();
        }
    }
};

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
             << "6. Penyewaan GYM\n"
             << "7. Searching\n"
             << "8. Keluar\n"
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
                    ubah_paket();
                }
                else if (menu_ubah == 2)
                {
                    ubah_paket_pelanggan();
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
            menu_sewa();
        }
        else if (menu_utama == 7)
        {
            menu_search();
        }
        else if (menu_utama == 8)
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
    // login(counter);
    menu();
    return 0;
}
