#include <iostream>
#include <fstream> // read-write operations
#include <string>
#include <ctime>
using namespace std;

// notes;
// untuk add expense, function namenya pakai "addExpense" (cek line 59)]
// buat yang sorting berdasarkan nominal dan tanggal (cek line )

// placeholder test batasin length string
// #define NAME_LEN 64
// #define CAT_LEN 32

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

void addexpense(expense*& head, string p, string k, int n){

    time_t sekarang = time(0);
    tm* ltm = localtime(&sekarang);
    
    int hari = ltm->tm_mday;
    int bulan = ltm->tm_mon + 1;
    int tahun = ltm->tm_year + 1900;
    
    expense* temp = new expense;

    
    temp->day = hari;
    temp->month = bulan;
    temp->year = tahun;

    temp->pengeluaran = p;  
    temp->kategori = k;
    temp->amount = n;

    temp->next = head;
    head = temp;
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

void deleteExpense (expense*& head, int id) {       

    cout << "Masukkan No pengeluaran yang ingin dihapus: ";
    cin >> id;

    if (head == nullptr) {
        cout << "List kosong\n";
        return;
    }

    if (id < 0) {
        cout << "\nNomor menu tidak valid!\n" << endl;
        return;
    }

    // delete the head or index 0
    if (id == 0) {
        expense* temp = head;
        head = head->next;
        delete temp;
        cout << "\nPenghapusan berhasil!\n\n";
        return;
    }

    expense* temp = head;          // mulai dari head
    for (int i = 0; i < id - 1 && temp != nullptr; i++) { // loop sampai ketemu index - 1
        temp = temp->next;
    }

    if (temp == nullptr || temp->next == nullptr) {         // jika out of range
        cout << "\nIndex tidak dapat dijangkau!\n" << endl;
        return;
    }

    expense* toDelete = temp->next;
    temp->next = temp->next->next;
    delete toDelete;
    cout << "\nPenghapusan berhasil\n\n";
}

int main() {
    expense* head = nullptr;
    int choice, choice2;
    int id;

    expense data;
    string username = "Adudu";
    string password = "CoklatTokAba";
    string* ptruser = &username;
    string* ptrpass = &password;
    string passconfirm;

    // string filename = "data.txt";
    // loadFromFile(filename);
    cout << endl;
    cout << "--- Expense Tracker Anak Kos ---\n\n";

    cout << "--- SELAMAT DATANG ---" << endl;
    cout << "Apakah Sudah Memiliki Akun ?" << endl;
    cout << "1. Iya" << endl;
    cout << "2. Tidak" << endl;
    cout << "Pilih Opsi : ";
    cin >> choice2;
    cin.ignore();

    switch (choice2){
    case 1:
            cout << "--- LOGIN EXPENSE TRACKER ANAK KOS ---" << endl;
            cout << "Masukkan Username : ";
            getline(cin, username);
            cout << "Masukkan Password : ";
            getline(cin, password);

            if (username == "Adudu" && password == "CoklatTokAba"){
                // ini placeholder
                    do {
                        cout << "-- OPSI MENU --\n";
                        cout << "1. Tambah Pengeluaran\n";
                        cout << "2. Hapus Pengeluaran\n";
                        cout << "3. Tampilkan Pengeluaran\n";
                        cout << "4. Cari Berdasarkan Kategori\n";
                        cout << "5. Cari Berdasarkan Nominal\n";            // <-- nanti di dalamnya bisa pilih mau sort by highest/lowest
                        cout << "6. Cari Berdasarkan Tanggal\n";            // <-- nanti di dalamnya bisa pilih mau sort by latest/oldest
                        cout << "7. Total Pengeluaran\n";
                        cout << "8. Simpan Perubahan\n";                    // <-- yang ini pakai metode simpen no.1
                        cout << "0. Keluar\n";
                        cout << "Pilih opsi: ";
                        cin >> choice;

                        switch (choice) {
                            case 1:
                                cin.ignore();
                                cout << "Jenis Pengeluaran : ";
                                getline(cin, data.pengeluaran);
                                cout << "Kategori : ";
                                getline(cin, data.kategori);
                                cout << "Besar Nominal : Rp.  ";
                                cin >> data.amount;
                                addexpense(head, data.pengeluaran, data.kategori, data.amount);
                                // addExpense();
                                break;
                            case 2:
                                deleteExpense(head, id - 1);
                                // deleteExpense();
                                break;
                            case 3:
                                displayExpense(head);
                                // displayExpense();
                                break;
                            case 4:
                                // searchExpense();
                                break;
                            case 5:
                                // SortBy<nominal>Expense();
                                break;
                            case 6:
                                // SortBy<date>Expense();
                                break;
                            case 7:
                                // sumExpense();
                                break;
                            case 8:
                                /* saveToFile(filename); */
                                break;
                            case 0:
                                /* saveToFile(filename); */
                                cout << "Keluar dari program.\n";
                                break;
                            default:
                                cout << "Opsi tidak valid. Silakan coba lagi.\n";
                        }
                    } while (choice);
                }
                else if(username != "Adudu"){
                    cout << "Username salah!";
                }
                else if(password != "CoklatTokAba"){
                    cout << "Password salah!";
                }
                else{
                    cout << "Username dan Password salah!";
                }
                break;
    case 2:
            cout << "--- REGISTRASI AKUN EXPENSES TRACKER ---" << endl;
            cout << "Silahkan Masukkan Username : ";
            getline(cin, *ptruser);
            cout << "Silahkan Masukkan Password : ";
            getline(cin, *ptrpass);
            cout << "Silahkan Masukkan Kembali Password : ";
            getline(cin, passconfirm);

            if (passconfirm == *ptrpass)
            {
                cout << "Akun berhasil registrasi" << endl;
                    cout << "--- LOGIN EXPENSE TRACKER ANAK KOS ---" << endl;
            cout << "Masukkan Username : ";
            getline(cin, username);
            cout << "Masukkan Password : ";
            getline(cin, password);

            if (username == "Adudu" && password == "CoklatTokAba"){
                // ini placeholder
                    do {
                        cout << "-- OPSI MENU --\n";
                        cout << "1. Tambah Pengeluaran\n";
                        cout << "2. Hapus Pengeluaran\n";
                        cout << "3. Tampilkan Pengeluaran\n";
                        cout << "4. Cari Berdasarkan Kategori\n";
                        cout << "5. Cari Berdasarkan Nominal\n";            // <-- nanti di dalamnya bisa pilih mau sort by highest/lowest
                        cout << "6. Cari Berdasarkan Tanggal\n";            // <-- nanti di dalamnya bisa pilih mau sort by latest/oldest
                        cout << "7. Total Pengeluaran\n";
                        cout << "8. Simpan Perubahan\n";                    // <-- yang ini pakai metode simpen no.1
                        cout << "0. Keluar\n";
                        cout << "Pilih opsi: ";
                        cin >> choice;

                        switch (choice) {
                            case 1:
                                cin.ignore();
                                cout << "Jenis Pengeluaran : ";
                                getline(cin, data.pengeluaran);
                                cout << "Kategori : ";
                                getline(cin, data.kategori);
                                cout << "Besar Nominal : Rp.  ";
                                cin >> data.amount;
                                addexpense(head, data.pengeluaran, data.kategori, data.amount);
                                // addExpense();
                                break;
                            case 2:
                                // deleteExpense();
                                break;
                            case 3:
                                displayExpense(head);
                                // displayExpense();
                                break;
                            case 4:
                                // SortBy<__>Expense();
                                break;
                            case 5:
                                // SortBy<__>Expense();
                                break;
                            case 6:
                                // SortBy<__>Expense();
                                break;
                            case 7:
                                // sumExpense();
                                break;
                            case 8:
                                /* saveToFile(filename); */
                                break;
                            case 0:
                                /* saveToFile(filename); */
                                cout << "Keluar dari program.\n";
                                break;
                            default:
                                cout << "Opsi tidak valid. Silakan coba lagi.\n";
                        }
                    } while (choice);
                }
                else if(username != "Adudu"){
                    cout << "Username salah!";
                }
                else if(password != "CoklatTokAba"){
                    cout << "Password salah!";
                }
                else{
                    cout << "Username dan Password salah!";
                }
            }
            else if(passconfirm != *ptrpass){
                cout << "Password tidak sama" << endl;
            }
            else{
                cout << "Silahkan isi Username dan Password dengan benar!" << endl;
            }


        default:
            cout << "silahkan pilih opsi yang benar";
            break;
        }
        
}
    


    

// notes lagi; jadi ini setelah baca-baca, ada dua tipe kalo kita mau simpen datanya di file
// 1. simpen data saat user pilih opsi save, -> di function add/delete ngga ada manggil saveToFile(), sehingga user bisa simpen pas klik opsi save
// 2. simpen data setiap kali user add/delete data, jadi di function add/delete nya nanti langsung panggil saveToFile() gitu rek