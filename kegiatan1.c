#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void tampil() ;
int hapus() ;
int ubah() ;
void tambah() ;

int main()
{
FILE* file;
    
    enum {
        TAMBAH = 1,
        TAMPIL,
        UBAH,
        HAPUS,
        KELUAR,
    };
    int pilihan;
    int kondisi = 1;

    file = fopen("data_produk.txt", "r");

    if (file == NULL)
    {
        fopen("data_produk.txt", "w");
        printf("Berhasil Membuat File!!\n\n");
        fclose(file);
    } else {
        fclose(file);
    }
    

    do
    {
        printf("Pilih Aksi : \n");
        printf("1. Tambahkan Data \n");
        printf("2. Tampilkan Data\n");
        printf("3. Update Data\n");
        printf("4. Hapus Data\n");
        printf("5. Keluar \n");
        printf("Masukkan Pilihan : "); scanf("%d", &pilihan);
        getchar();


        printf("\n");

        switch (pilihan)
        {
        case TAMBAH:
            tambah();
            break;
        case TAMPIL:
            tampil();
            break;
        case UBAH:
            ubah();
            break;
        case HAPUS:
            hapus();
            break;
        case KELUAR:
            kondisi = 0;
            printf("Terima Kasih !!");
            break;
        
        default:
            break;
        }
    } while (kondisi > 0);
    

    
    return 0;
}

void tambah() {
    FILE* file;
    FILE* file2;
    FILE* tempFile;
    char idProduk[10];
    char namaProduk[100];
    char kategoriProduk[100];
    long long int hargaProduk;
    int stokProduk;
    char data[200];
    int ditemukan = 0;

    file = fopen("data_produk.txt", "a");
    printf("Masukkan ID Produk : ");fgets(idProduk, sizeof(idProduk), stdin);idProduk[strcspn(idProduk, "\n")] = 0;
    printf("Masukkan Nama Produk : ");fgets(namaProduk, sizeof(namaProduk), stdin);namaProduk[strcspn(namaProduk, "\n")] = 0;
    printf("Masukkan Kategori Produk : ");fgets(kategoriProduk, sizeof(kategoriProduk), stdin);kategoriProduk[strcspn(kategoriProduk, "\n")] = 0;
    printf("Masukkan Harga Produk : ");scanf("%lld", &hargaProduk);
    printf("Masukkan Stok Produk : ");scanf("%d", &stokProduk);

    file2 = fopen("data_produk.txt", "r");
    while (fgets(data, sizeof(data), file2))
    {
        if (strstr(data, idProduk) && strstr(data, "ID :"))
        {
            ditemukan = 1;
            printf("\nID Sudah Di Gunakan Mohon Masukkan Kembali Data\n");
            getchar();            
            tambah();
        }
        
    }
    
    if (file != NULL)
    {
        if (ditemukan == 0)
        {
            fprintf(file, "ID : %s \n", idProduk);
            fprintf(file, "Nama : %s \n", namaProduk);
            fprintf(file, "Kategori : %s \n", kategoriProduk);
            fprintf(file, "Harga : %lld \n", hargaProduk);
            fprintf(file, "Stok : %d \n\n", stokProduk);
            printf("Produk telah ditambahkan\n\n");
        } 
    } else
    {
        perror("Error : File Tidak Ditemukan Dan Gagal Di Buka");
    }
    fclose(file);
}

int ubah(){
    FILE* file;
    FILE* tempFile;
    char buffer[300], idProdukCari[10];
    int stokProdukBaru;
    char namaProdukBaru[100], kategoriProdukBaru[100];
    long long int hargaProdukBaru;
    int ditemukan = 0;

    printf("Masukkan ID Produk : ");fgets(idProdukCari, sizeof(idProdukCari), stdin);idProdukCari[strcspn(idProdukCari, "\n")] = 0;

    file = fopen("data_produk.txt", "r");
    if (file == NULL)
    {
        printf("Gagal Membuka File\n");
        return 1;
    }

    tempFile = fopen("data_produk_sementara.txt", "w");
    if (tempFile == NULL)
    {
        printf("Gagal Membuat File Sementara \n");
        fclose(file);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (strstr(buffer, idProdukCari) && strstr(buffer, "ID :"))
        {
            ditemukan = 1;
            printf("Data Ditemukan. Masukkan Data Baru.\n");

            printf("Nama Produk Baru : "); fgets(namaProdukBaru, sizeof(namaProdukBaru), stdin);namaProdukBaru[strcspn(namaProdukBaru, "\n")] = 0;
            printf("Kategori Produk Baru : "); fgets(kategoriProdukBaru, sizeof(kategoriProdukBaru), stdin);kategoriProdukBaru[strcspn(kategoriProdukBaru, "\n")] = 0;
            printf("Harga Produk Baru : "); scanf("%lld", &hargaProdukBaru);
            printf("Stok Produk Baru : "); scanf("%d", &stokProdukBaru);

            fprintf(tempFile, "ID : %s \n", idProdukCari);
            fprintf(tempFile, "Nama : %s \n", namaProdukBaru);
            fprintf(tempFile, "Kategori : %s \n", kategoriProdukBaru);
            fprintf(tempFile, "Harga : %lld \n", hargaProdukBaru);
            fprintf(tempFile, "Stok : %d \n", stokProdukBaru);


            fgets(buffer, sizeof(buffer), file);
            fgets(buffer, sizeof(buffer), file);
            fgets(buffer, sizeof(buffer), file);
            fgets(buffer, sizeof(buffer), file);
            fgets(buffer, sizeof(buffer), file);
            // continue;
        }
        fputs(buffer, tempFile);
    }
    
    if (fclose(file) != 0) {
        perror("Gagal menutup file asli");
        return 1;
    }
    if (fclose(tempFile) != 0) {
        perror("Gagal menutup Temp  File ");
        return 1;
    }

    // fclose(file);
    // fclose(tempFile);

    if (ditemukan)
    {
       if (remove("data_produk.txt") != 0) {
            perror("Gagal menghapus file asli");
            return 1;
        }

        if (rename("data_produk_sementara.txt", "data_produk.txt") != 0) {
            perror("Gagal mengganti nama file sementara");
            return 1;
        }

        printf("Data Berhasil Di Rubah\n");
    } else
    {
        remove("data_produk_sementara.txt");
        printf("Data Tidak Ditemukan\n");
    }
}

int hapus() {
    FILE* file;
    FILE* tempFile;
    char buffer[300], idProdukCari[10];
    int ditemukan = 0;

    printf("Masukkan ID Produk : ");fgets(idProdukCari, sizeof(idProdukCari), stdin);idProdukCari[strcspn(idProdukCari, "\n")] = 0;

    file = fopen("data_produk.txt", "r");
    if (file == NULL)
    {
        printf("Gagal Membuka File\n");
        return 1;
    }

    tempFile = fopen("data_produk_sementara.txt", "w");
    if (tempFile == NULL)
    {
        printf("Gagal Membuat File Sementara \n");
        fclose(file);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (strstr(buffer, idProdukCari) && strstr(buffer, "ID :"))
        {
            ditemukan = 1;
            fgets(buffer, sizeof(buffer), file);
            fgets(buffer, sizeof(buffer), file);
            fgets(buffer, sizeof(buffer), file);
            fgets(buffer, sizeof(buffer), file);
            fgets(buffer, sizeof(buffer), file);
            continue;
        }
        fputs(buffer, tempFile);
    }

    
    if (fclose(file) != 0) {
        fclose(file);
        perror("Gagal menutup file asli");
        return 1;
    }
    if (fclose(tempFile) != 0) {
        fclose(tempFile);
        perror("Gagal menutup Temp  File ");
        return 1;
    }

    

    if (ditemukan)
    {
        if (remove("data_produk.txt") != 0) {
            perror("Gagal menghapus file asli");
            return 1;
        }

        if (rename("data_produk_sementara.txt", "data_produk.txt") != 0) {
            perror("Gagal mengganti nama file sementara");
            return 1;
        }

        printf("Data Berhasil Di Hapus\n");
    } else
    {
        remove("data_produk_sementara.txt");
        printf("Data Tidak Ditemukan\n");

    } 

}

void tampil() {
    FILE* file;
    file = fopen("data_produk.txt", "r");
    char data[200];

    printf("Data Produk : \n\n");

    if (file != NULL)
    {
        while (fgets(data, sizeof(data), file))
        {
            printf("%s", data);
        }
        fclose(file);
        // main();
    } else {
        printf("\nError : File Gagal Dibuka dan Data Gagal Di Tampilkan");
    }
}

