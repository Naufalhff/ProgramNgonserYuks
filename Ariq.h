#ifndef ARIQ_h
#define ARIQ_h

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
