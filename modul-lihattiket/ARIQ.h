#ifndef ariq_h
#define ariq_h

/* Definisi Tipe Data */
// Tipe data untuk menyimpan informasi berupa string
typedef char infotype[100];

// Tipe data untuk merepresentasikan root dari pohon konser
typedef struct rootTree *addressRoot;

// Tipe data untuk merepresentasikan node konser dalam daftar konser
typedef struct nodeKonser *addressKonser;

// Tipe data untuk merepresentasikan isi dari sebuah node dalam daftar pengguna
typedef struct isiNode *addressNode;

// Tipe data untuk merepresentasikan isi dari sebuah daftar pengguna
typedef struct isiList *addressUser;

// Struktur data untuk merepresentasikan root dari pohon konser
typedef struct rootTree
{
    infotype info;         // Informasi yang disimpan di root
    addressKonser down;    // Pointer ke daftar konser
} Root;

// Struktur data untuk merepresentasikan node konser dalam daftar konser
typedef struct nodeKonser
{
    int nomorKonser;        // Nomor konser
    infotype info;          // Nama konser
    addressUser VIP;        // Pointer ke daftar pengguna VIP
    addressUser REG;        // Pointer ke daftar pengguna REG
    addressKonser next;     // Pointer ke node konser berikutnya dalam daftar
} listKonser;

// Struktur data untuk merepresentasikan isi dari sebuah node dalam daftar pengguna
typedef struct isiNode
{
    int idUser;             // ID pengguna
    infotype nama;          // Nama pengguna
    int frekuensi;          // Jumlah tiket yang dipesan pengguna
    addressNode next;       // Pointer ke node pengguna berikutnya dalam daftar
} Node;

// Struktur data untuk merepresentasikan isi dari sebuah daftar pengguna
typedef struct isiList
{
    addressNode front;      // Pointer ke depan daftar pengguna
    addressNode rear;       // Pointer ke belakang daftar pengguna
    int jumlah;             // Jumlah pengguna dalam daftar
    int kapasitas;          // Kapasitas maksimum daftar pengguna
} listUser;

/* MENU ADMIN */
addressRoot buatRoot();
/* 
   Tujuan : Membuat root node untuk struktur data konser.
   I.S    : Tidak ada root node yang ada dalam struktur data konser.
   F.S    : Sebuah root node baru telah dibuat dan dialokasikan dalam memori.
*/

addressKonser buatNodeKonser(int nomorKonser, infotype namaKonser, int maxVIP, int maxREG);
/* 
   Tujuan : Membuat node baru untuk data konser.
   I.S    : Tidak ada node konser yang ada.
   F.S    : Sebuah node konser baru telah dibuat dengan informasi yang sesuai dan dialokasikan dalam memori.
*/

addressNode buatNodeUser(int id, char *username, int jumlah);
/* 
   Tujuan : Membuat node baru untuk data pengguna.
   I.S    : Tidak ada node pengguna yang ada.
   F.S    : Sebuah node pengguna baru telah dibuat dengan informasi yang sesuai dan dialokasikan dalam memori.
*/

addressUser buatListUser(int maxList);
/* 
   Tujuan : Membuat list kosong untuk data pengguna.
   I.S    : Tidak ada list pengguna yang ada.
   F.S    : Sebuah list pengguna baru telah dibuat dengan kapasitas yang ditentukan dan dialokasikan dalam memori.
*/

addressKonser cariKonserById(addressKonser first, int idKonser);
/* 
   Tujuan : Mencari konser berdasarkan ID.
   I.S    : List konser telah tersedia.
   F.S    : Konser yang sesuai dengan ID yang diberikan telah ditemukan atau tidak ditemukan.
*/

int cariKonserByNama(addressRoot root, char *namaKonser);
/* 
   Tujuan : Mencari konser berdasarkan nama.
   I.S    : List konser telah tersedia.
   F.S    : Konser yang sesuai dengan nama yang diberikan telah ditemukan atau tidak ditemukan.
*/

addressNode cariUser(addressUser list, int idUser, addressNode *prev);
/* 
   Tujuan : Mencari pengguna berdasarkan ID.
   I.S    : List user telah tersedia.
   F.S    : Pengguna yang sesuai dengan ID yang diberikan telah ditemukan atau tidak ditemukan.
*/

addressKonser enqueueKonser(addressKonser first, addressKonser nodeBaru);
/* 
   Tujuan : Menambahkan konser ke dalam antrian.
   I.S    : List konser telah tersedia.
   F.S    : Konser baru telah ditambahkan ke dalam antrian konser.
*/

addressKonser enqueueKonserFromFile(char *fileName, addressKonser first);
/* 
   Tujuan : Menambahkan konser dari file ke dalam antrian.
   I.S    : List konser telah tersedia.
   F.S    : Konser-konser dari file telah ditambahkan ke dalam antrian konser.
*/

void enqueueFromFile(char *fileName, addressKonser first, addressRoot root);
/* 
   Tujuan : Menambahkan data pengguna dari file ke dalam antrian.
   I.S    : List user telah tersedia.
   F.S    : Data pengguna dari file telah ditambahkan ke dalam antrian pengguna.
*/

void hapusFileDequeue(addressKonser konser, addressNode data);
/* 
   Tujuan : Menghapus data pengguna dari file setelah di-dequeue.
   I.S    : Tree telah tersedia dan file sudah tersedia
   F.S    : Data pengguna yang sesuai dengan yang di-dequeue telah dihapus dari file.
*/

void dequeue1(addressKonser konser, addressUser list, int index);
/* 
   Tujuan : Menghapus data pengguna dari antrian.
   I.S    : List user telah tersedia.
   F.S    : Data pengguna yang dipilih telah dihapus dari antrian dan dari file.
*/

int tampilanULU(addressRoot root);
/* 
   Tujuan : Menampilkan tampilan utama daftar konser.
   I.S    : Tree sudah tersedia.
   F.S    : Tampilan utama daftar konser ditampilkan dan pengguna diminta memilih konser.
*/

int VipOrReg ();
/* 
   Tujuan : Menampilkan opsi untuk memilih jenis tiket.
   I.S    : -
   F.S    : Opsi untuk memilih jenis tiket ditampilkan dan pengguna diminta memilih.
*/

void simpanHistoryKehadiran(int idUser, char *nama, int frekuensi);
/* 
   Tujuan : Menyimpan data kehadiran pengguna ke dalam file history kehadiran.
   I.S    : Data kehadiran pengguna.
   F.S    : Data kehadiran pengguna disimpan dalam file history kehadiran.
*/

void kehadiranUser(addressUser list, int index, int jumlah);
/* 
   Tujuan : Memproses kehadiran pengguna pada konser dan menyimpan data kehadiran.
   I.S    : Indeks pengguna dalam daftar, jumlah tiket yang dibeli.
   F.S    : Kehadiran pengguna diproses dan data kehadiran disimpan.
*/

void printUser(addressNode front);
/* 
   Tujuan : Menampilkan daftar pengguna yang telah membeli tiket.
   I.S    : Daftar pengguna yang telah membeli tiket telah tersedia.
   F.S    : Daftar pengguna yang telah membeli tiket ditampilkan.
*/

void menuLihatUser(addressRoot root);
/* 
   Tujuan : Menampilkan menu untuk melihat dan mengelola data pengguna pada suatu konser.
   I.S    : Tree sudah tersedia.
   F.S    : Pengguna dapat memilih beberapa opsi yang ada di menu untuk melihat dan mengelola data pengguna.
*/

void menuLihatHistory();
/* 
   Tujuan : Menampilkan history kehadiran pengguna pada konser.
   I.S    : Tree sudah tersedia.
   F.S    : History kehadiran pengguna pada konser ditampilkan.
*/

void rekursifHapusUser(addressNode *node);
/*
   Tujuan : Menghapus semua node dari daftar pengguna secara rekursif.
   I.S    : Daftar pengguna sudah tersedia.
   F.S    : Semua node dari daftar pengguna terhapus dari memori.
*/

void hapusKonserById(addressRoot root, int idKonser);
/*
   Tujuan : Menghapus konser beserta semua pengguna dari daftar pengguna berdasarkan ID konser.
   I.S    : Tree yang berisi daftar konser sudah tersedia.
   F.S    : Konser beserta semua pengguna dari daftar pengguna berdasarkan ID konser terhapus dari daftar konser.
*/

/* MENU USER */
void pembayaranUser (int idNow);
/* Tujuan : Menjalankan aplikasi utama untuk mengelola pembayaran tiket
   I.S    : -
   F.S    : Program pembayaran akan dijalankan, dan pengguna dapat memilih beberapa opsi yang ada di menu pembayaran
*/

int menuPembayaran ();
/* Tujuan : Menampilkan menu pembayaran dan mengembalikan pilihan pengguna
   I.S    : -
   F.S    : Mengembalikan pilihan menu yang dipilih pengguna dalam bentuk karakter
*/

void opsiBayar(char *fileName, int idNow);
/* Tujuan : Memproses pembayaran tiket untuk pengguna dengan ID tertentu
   I.S    : Nama file data dan ID pengguna diberikan
   F.S    : Data pembayaran pengguna diperbarui di file, status pembayaran diubah jika perlu
*/

void statusPembayaran(char *fileName, int idNow);
/* Tujuan : Menampilkan status pembayaran tiket untuk pengguna dengan ID tertentu
   I.S    : Nama file data dan ID pengguna diberikan
   F.S    : Menampilkan status pembayaran tiket (belum pesan, pending, lunas, atau belum lunas)
*/

void cetakTiket(char *fileName, int idNow);
/* Tujuan : Menampilkan tiket konser untuk dicetak bagi pengguna dengan ID tertentu
   I.S    : Nama file data dan ID pengguna diberikan
   F.S    : Menampilkan informasi tiket jika pembayaran sudah lunas, atau pesan kesalahan jika belum
*/

#endif