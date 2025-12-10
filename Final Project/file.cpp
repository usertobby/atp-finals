#include <iostream>
#include <fstream> // read-write operations
#include <string>
using namespace std;

struct expense {
    int index;
    int day, month, year;
    long amount;
    string pengeluaran;
    string kategori;
    expense* next;
};

// Lowercase sebuah string
string toLowerCase(const string& str) { 
    string lower = str;
    for (char& c : lower)
        c = tolower(c);
    return lower;
}

// Kapitalisasi huruf pertama string
string kapitalAwal(const string& str) {
    if (str.empty()) {                          // jika string empty
        return str;
    }
    string kap = str;
    kap[0] = toupper(kap[0]);                   // bikin huruf pertama kapital
    for (size_t i = 1; i < kap.size(); i++) {
        kap[i] = tolower(kap[i]);               // bikin sisa string lowercase
    }
    return kap;
}

void addexpense(expense*& head, string p, string k, int n, int d, int m, int y){
    expense* temp = new expense;
    
    temp->day = d;
    temp->month = m;
    temp->year = y;

    temp->pengeluaran = p;  
    temp->kategori = k;
    temp->amount = n;

    temp->next = head;
    head = temp;

    cout << "\nBerhasil menambahkan pengeluaran.\n";
}

void loadFromFile(const string& filename, expense*& head) {
    ifstream file(filename);
    if (!file.is_open()) {
        // file belum ada / user baru -> tidak apa-apa
        return;
    }

    int day, month, year;
    long amount;
    string pengeluaran, kategori;

    // Format file per baris: day month year pengeluaran kategori amount
    while (file >> day >> month >> year >> pengeluaran >> kategori >> amount) {
        expense* temp = new expense;
        temp->day = day;
        temp->month = month;
        temp->year = year;
        temp->pengeluaran = pengeluaran;
        temp->kategori = kategori;
        temp->amount = amount;
        temp->next = head;
        head = temp;
    }
    file.close();
}

void saveToFile(const string& filename, expense* head) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk menyimpan!\n";
        return;
    }

    expense* temp = head;
    while (temp != nullptr) {
        file << temp->day << " "
             << temp->month << " "
             << temp->year << " "
             << temp->pengeluaran << " "
             << temp->kategori << " "
             << temp->amount << "\n";

        temp = temp->next;
    }
    file.close();
    cout << "\nData berhasil disimpan ke file!\n";
}

bool loginUser(string& outUsername) {
    string username, password;
    cout << "\n--- LOGIN EXPENSE TRACKER ---" << endl;
    cout << "Masukkan Username : ";
    getline(cin, username);
    cout << "Masukkan Password : ";
    getline(cin, password);

    ifstream file("users.txt");
    if (!file.is_open()) {
        cout << "Belum ada akun terdaftar. Silakan registrasi dulu.\n";
        return false;
    }

    string u, p;
    while (file >> u >> p) {
        if (u == username && p == password) {
            outUsername = username;
            cout << "\nLogin berhasil. Selamat datang, " << username << "!\n";
            file.close();
            return true;
        }
    }

    file.close();
    cout << "\nUsername atau password salah!\n";
    return false;
}

void registerUser() {
    string username, password, confirm;
        cout << "\n--- REGISTER AKUN BARU ---\n";
        cout << "Masukkan Username : ";
        getline(cin, username);
        cout << "Masukkan Password : ";
        getline(cin, password);
        cout << "Konfirmasi Password : ";
        getline(cin, confirm);

    if (password != confirm) {
        cout << "Password tidak cocok!\n";
    return;
    }

    ofstream file("users.txt", ios::app);
    file << username << " " << password << "\n";
    file.close();


    string expenseFile = username + "_expense.txt";
    ofstream e(expenseFile);
    e.close();

    cout << "Akun berhasil dibuat!\n";
}

void displayExpense(expense*& head) {
    expense* temp = head;

    int id = 1;
    cout << "\n=== Daftar Pengeluaran ===\n";

    while (temp != nullptr) {
        cout << "No : " << id << "\n";
        cout << "Tanggal : " << temp->day << "-" << temp->month << "-" << temp->year << "\n";
        cout << "Nama    : " << kapitalAwal(temp->pengeluaran) << "\n";
        cout << "Kategori: " << kapitalAwal(temp->kategori) << "\n";
        cout << "Nominal : Rp " << temp->amount << "\n";
        cout << "------------------------------\n";
        temp = temp->next;
        id++;
    }
}  

void deleteExpense(expense*& head) {
    int id;
    cout << "Masukkan Nomor pengeluaran yang ingin dihapus: ";
    cin >> id;
    
    if (head == nullptr) {
        cout << "\nTidak ada data pengeluaran.\n";
        return;
    }

    if (id < 1) {
        cout << "Nomor tidak valid!\n";
        return;
    }

    // hapus node pertama
    if (id == 1) {
        expense* temp = head;
        head = head->next;
        delete temp;
        cout << "Penghapusan berhasil!\n";
        return;
    }

    expense* current = head;

    for (int i = 1; i < id - 1 && current != nullptr; i++) {
        current = current->next;
    }

    if (current == nullptr || current->next == nullptr) {
        cout << "\nIndex tidak dapat dijangkau!\n";
        return;
    }

    expense* nextNode = current->next;

    current->next = nextNode->next;
    delete nextNode;

    cout << "Penghapusan berhasil!\n";
}

void searchCategory(expense* head) {
    if (head == nullptr) {
        cout << "\nTidak ada data pengeluaran.\n";
        return;
    }

    int pilih;
    string dicari;
 
    cout << "\n=== Cari Berdasarkan Kategori ===\n";
    cout << "1. Primer\n";
    cout << "2. Sekunder\n";
    cout << "3. Tersier\n";
    cout << "Pilih kategori [1-3]: ";
    cin >> pilih;
    cin.ignore();

    switch (pilih) {
        case 1:
            dicari = "primer";
            break;
        case 2:
            dicari = "sekunder";
            break;
        case 3:
            dicari = "tersier";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            return;
    }

    bool found = false;
    expense* temp = head;
    int nomor = 1;

    cout << "\n=== Hasil pencarian kategori: " << kapitalAwal(dicari) << " ===\n";

    while (temp != nullptr) {
        if (toLowerCase(temp->kategori) == dicari) {
            found = true;
            cout << "No : " << nomor << "\n";
            cout << "Tanggal : " << temp->day << "-" << temp->month << "-" << temp->year << "\n";
            cout << "Nama    : " << kapitalAwal(temp->pengeluaran) << "\n";
            cout << "Kategori: " << kapitalAwal(temp->kategori) << "\n";
            cout << "Nominal : Rp " << temp->amount << "\n";
            cout << "------------------------------\n";
            nomor++;
        }

        temp = temp->next;
    }

    if (!found) {
        cout << "\nTidak ada pengeluaran pada kategori ini.\n";
    }
}

// Menghitung total pengeluaran
long totalExpense(expense* head) {
    long total = 0;
    expense* temp = head;

    while (temp != nullptr) {
            total += temp->amount;
            temp = temp->next;
    }

    return total;
}

// Function untuk mengurutkan tanggal
bool isEarlier(expense* a, expense* b) {
    if (a->year != b->year) return a->year < b->year;
    if (a->month != b->month) return a->month < b->month;
    return a->day < b->day;
}
bool isLater(expense* a, expense* b) {
    return !isEarlier(a, b);
}

// Swap function untuk nominal
void swapExpense(expense* a, expense* b) {
    int tempDay = a->day;
    a->day = b->day;
    b->day = tempDay;

    int tempMonth = a->month;
    a->month = b->month;
    b->month = tempMonth;

    int tempYear = a->year;
    a->year = b->year;
    b->year = tempYear;

    long tempAmount = a->amount;
    a->amount = b->amount;
    b->amount = tempAmount;

    string tempExpense = a->pengeluaran;
    a->pengeluaran = b->pengeluaran;
    b->pengeluaran = tempExpense;

    string tempCategory = a->kategori;
    a->kategori = b->kategori;
    b->kategori = tempCategory;
}

// Sorting by Nominal descending
void sortByNominalDesc(expense*& head) {
    if (!head) return;

    bool swapped;
    expense* ptr;
    expense* last = nullptr;

    do {
        swapped = false;
        ptr = head;

        while (ptr->next != last) {
            if (ptr->amount < ptr->next->amount) {
                swapExpense(ptr, ptr->next);
                swapped = true;
            }
            ptr = ptr->next;
        }
        last = ptr;
    }
    while (swapped);
}

// Sorting by nominal ascending
void sortByNominalAsc(expense*& head) {
    if (!head) return;

    bool swapped;
    expense* ptr;
    expense* last = nullptr;

    do {
        swapped = false;
        ptr = head;

        while (ptr->next != last) {
            if (ptr->amount > ptr->next->amount) {
                swapExpense(ptr, ptr->next);
                swapped = true;
            }
            ptr = ptr->next;
        }
        last = ptr;
    }
    while (swapped);
}

// Sorting tanggal descending
void sortByDateDesc(expense*& head) {
    if (!head) return;

    bool swapped;
    expense* ptr;
    expense* last = nullptr;

    do {
        swapped = false;
        ptr = head;

        while (ptr->next != last) {
            if (isEarlier(ptr, ptr->next)) {
                swapExpense(ptr, ptr->next);
                swapped = true;
            }
            ptr = ptr->next;
        }
        last = ptr;
    }
    while (swapped);
}

// Sorting tanggal ascending
void sortByDateAsc(expense*& head) {
    if (!head) return;

    bool swapped;
    expense* ptr;
    expense* last = nullptr;

    do {
        swapped = false;
        ptr = head;

        while (ptr->next != last) {
            if (isLater(ptr, ptr->next)) {
                swapExpense(ptr, ptr->next);
                swapped = true;
            }
            ptr = ptr->next;
        }
        last = ptr;
    }
    while (swapped);
}

int main() {
    expense* head = nullptr;
    int choice, choice2, opsi;
    int id;

    expense data;
    string username;
    string password;
    string* ptruser = &username;
    string* ptrpass = &password;
    string passconfirm;

    cout << endl;
    cout << "================================\n";
    cout << "=== Expense Tracker Anak Kos ===\n";
    cout << "================================\n\n";

    cout << "--- SELAMAT DATANG ---" << endl;
    cout << "Apakah Sudah Memiliki Akun ?" << endl;
    cout << "1. Iya" << endl;
    cout << "2. Tidak" << endl;
    cout << "Pilih Opsi : ";
    cin >> choice2;
    cin.ignore();

    switch (choice2){
        case 1:
            {
            // Ganti alur login-hardcode dengan file-based login
            string loggedUser;
            bool ok = loginUser(loggedUser);
            if (!ok) {
                // Jika login gagal, kembali / exit
                cout << "Gagal login. Program berhenti.\n";
                return 0;
            }

            // Setelah login sukses -> load data user dari file (mode advanced)
            string currentFile = loggedUser + "_expense.txt";
            loadFromFile(currentFile, head);
                do {
                    cout << "\n--- OPSI MENU ---\n";
                    cout << "1. Tambah Pengeluaran\n";
                    cout << "2. Hapus Pengeluaran\n";
                    cout << "3. Tampilkan Pengeluaran\n";
                    cout << "4. Cari Berdasarkan Kategori\n";
                    cout << "5. Cari Berdasarkan Nominal\n";
                    cout << "6. Cari Berdasarkan Tanggal\n";
                    cout << "7. Total Pengeluaran\n";
                    cout << "8. Simpan Perubahan\n";
                    cout << "0. Keluar\n";
                    cout << "Pilih opsi: ";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            cin.ignore();
                            cout << "Tanggal Pengeluaran : ";
                            cin >> data.day;
                            cout << "Bulan Pengeluaran : ";
                            cin >> data.month;
                            cout << "Tahun Pengeluaran : ";
                            cin >> data.year;
                            cin.ignore();
                            cout << "Jenis Pengeluaran [Gunakan tanda (_)] : ";
                            getline(cin, data.pengeluaran);

                            int pilihKategori;
                            while (true) {
                                cout << "Pilih Kategori:\n";
                                cout << "1. Primer\n";
                                cout << "2. Sekunder\n";
                                cout << "3. Tersier\n";
                                cout << "Pilih [1-3]: ";
                                cin >> pilihKategori;
                                cin.ignore();

                                switch (pilihKategori) {
                                    case 1:
                                        data.kategori = "primer";
                                        break;
                                    case 2:
                                        data.kategori = "sekunder";
                                        break;
                                    case 3:
                                        data.kategori = "tersier";
                                        break;
                                    default:
                                        cout << "Input tidak valid! Silakan pilih 1-3.\n";
                                        continue;
                                }
                                break;
                            }
                            
                            cout << "Besar Nominal : Rp. ";
                            cin >> data.amount;
                            addexpense(head, data.pengeluaran, data.kategori, data.amount, data.day, data.month, data.year);
                            break;
                        case 2:
                            deleteExpense(head);
                            break;
                        case 3:
                            displayExpense(head);
                            break;
                        case 4:
                            searchCategory(head);
                            break;
                        case 5:
                            cout << "Mau dari yang terbesar atau yang terkecil?" << endl;
                            cout << "1. Terbesar" << endl;
                            cout << "2. Terkecil" << endl;
                            cout << "Pilih opsi : ";
                            cin >> opsi;

                            if (!head) cout << "\nData kosong";

                            if (opsi == 1) {
                                sortByNominalDesc(head);
                                displayExpense(head);
                            }
                            else if (opsi == 2) {
                                sortByNominalAsc(head);
                                displayExpense(head);
                            }
                            else {
                                cout << "\nInput Tidak Valid" << endl;
                            }
                            break;
                        case 6:
                            cout << "Mau dari yang terbaru atau yang terlama?" << endl;
                            cout << "1. Terbaru" << endl;
                            cout << "2. Terlama" << endl;
                            cout << "Pilih opsi : ";
                            cin >> opsi;

                            if (!head) cout << "\nData kosong";

                            if (opsi == 1){
                                sortByDateDesc(head);
                                displayExpense(head);
                            }
                            else if (opsi == 2) {
                                sortByDateAsc(head);
                                displayExpense(head);
                            }
                            else {
                                cout << "\nInput Tidak Valid" << endl;
                            }
                            break;
                        case 7:
                            cout << "\nTotal : Rp" << totalExpense(head) << endl;
                            break;
                        case 8: {
                            string expenseFile = loggedUser + "_expense.txt";
                            saveToFile(expenseFile, head);
                            break;
                        }
                        case 0: {
                            string expenseFile = loggedUser + "_expense.txt";
                            saveToFile(expenseFile, head);
                            cout << "Keluar dari program.\n";
                            break;
                        }
                        default:
                            cout << "Opsi tidak valid. Silakan coba lagi.\n";
                    }
                } while (choice);
            }
            break;

        case 2:
            registerUser();
            {
            string newUser;
            cout << "\nSilakan login kembali menggunakan akun yang baru dibuat.\n";

            // USER HARUS LOGIN ULANG UNTUK MENGISI newUser
            if (!loginUser(newUser)) {
                cout << "Login gagal setelah registrasi. Program dihentikan.\n";
                return 0;
            }   

            // load file pengeluaran user baru
            string currentFile = newUser + "_expense.txt";
            loadFromFile(currentFile, head);
                do {
                    cout << "\n--- OPSI MENU ---\n";
                    cout << "1. Tambah Pengeluaran\n";
                    cout << "2. Hapus Pengeluaran\n";
                    cout << "3. Tampilkan Pengeluaran\n";
                    cout << "4. Cari Berdasarkan Kategori\n";
                    cout << "5. Cari Berdasarkan Nominal\n";
                    cout << "6. Cari Berdasarkan Tanggal\n";
                    cout << "7. Total Pengeluaran\n";
                    cout << "8. Simpan Perubahan\n";
                    cout << "0. Keluar\n";
                    cout << "Pilih opsi: ";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            cin.ignore();
                            cout << "Tanggal Pengeluaran : ";
                            cin >> data.day;
                            cout << "Bulan Pengeluaran : ";
                            cin >> data.month;
                            cout << "Tahun Pengeluaran : ";
                            cin >> data.year;
                            cin.ignore();
                            cout << "Jenis Pengeluaran [Gunakan tanda (_)] : ";
                            getline(cin, data.pengeluaran);

                            int pilihKategori;
                            while (true) {
                                cout << "Pilih Kategori:\n";
                                cout << "1. Primer\n";
                                cout << "2. Sekunder\n";
                                cout << "3. Tersier\n";
                                cout << "Pilih [1-3]: ";
                                cin >> pilihKategori;
                                cin.ignore();

                                switch (pilihKategori) {
                                    case 1:
                                        data.kategori = "primer";
                                        break;
                                    case 2:
                                        data.kategori = "sekunder";
                                        break;
                                    case 3:
                                        data.kategori = "tersier";
                                        break;
                                    default:
                                        cout << "Input tidak valid! Silakan pilih 1-3.\n";
                                        continue;
                                }
                                break;
                            }

                            cout << "Besar Nominal : Rp. ";
                            cin >> data.amount;
                            addexpense(head, data.pengeluaran, data.kategori, data.amount, data.day, data.month, data.year);
                            break;
                        case 2:
                            deleteExpense(head);
                            break;
                        case 3:
                            displayExpense(head);
                            break;
                        case 4:
                            searchCategory(head);
                            break;
                        case 5:
                            cout << "Mau dari yang terbesar atau yang terkecil?" << endl;
                            cout << "1. Terbesar" << endl;
                            cout << "2. Terkecil" << endl;
                            cout << "Pilih opsi : ";
                            cin >> opsi;

                            if (!head) cout << "\nData kosong";

                            if (opsi == 1) {
                                sortByNominalDesc(head);
                                displayExpense(head);
                            }
                            else if (opsi == 2) {
                                sortByNominalAsc(head);
                                displayExpense(head);
                            }
                            else {
                                cout << "\nInput Tidak Valid" << endl;
                            }
                            break;
                        case 6:
                            cout << "Mau dari yang terbaru atau yang terlama?" << endl;
                            cout << "1. Terbaru" << endl;
                            cout << "2. Terlama" << endl;
                            cout << "Pilih opsi : ";
                            cin >> opsi;

                            if (!head) cout << "\nData kosong";

                            if (opsi == 1){
                                sortByDateDesc(head);
                                displayExpense(head);
                            }
                            else if (opsi == 2) {
                                sortByDateAsc(head);
                                displayExpense(head);
                            }
                            else {
                                cout << "\nInput Tidak Valid" << endl;
                            }
                            break;
                        case 7:
                            cout << "\nTotal : Rp" << totalExpense(head) << endl;
                            break;
                        case 8: {
                            string expenseFile = newUser + "_expense.txt";
                            saveToFile(expenseFile, head);
                            break;
                        }
                        case 0: {
                            string expenseFile = newUser + "_expense.txt";
                            saveToFile(expenseFile, head);
                            cout << "Keluar dari program.\n";
                            break;
                        }
                        default:
                            cout << "Opsi tidak valid. Silakan coba lagi.\n";
                    }
                } while (choice);
            }
            break;
        default:
            cout << "Silakan Pilih Opsi yang Benar!";
            break;
    }
}