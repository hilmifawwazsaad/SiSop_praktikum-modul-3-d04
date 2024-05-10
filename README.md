[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/jYae_yK9)
<div align=center>

|    NRP     |      Name      |
| :--------: | :------------: |
| 5025221000 | Student 1 Name |
| 5025221000 | Student 2 Name |
| 5025221103 | Hilmi Fawwaz Sa'ad |

# Praktikum Modul 3 _(Module 3 Lab Work)_

</div>

### Daftar Soal _(Task List)_

- [Task 1 - Jess No Limit Push Rank](/task-1/)

- [Task 2 - BNBWT](/task-2/)

- [Task 3 - Volume Expansion](/task-3/)

- [Task 4 - WOTA Competition](/task-4/)

### Laporan Resmi Praktikum Modul 3 _(Module 3 Lab Work Report)_

Tulis laporan resmi di sini!

_Write your lab work report here!_

## 1️⃣ Soal 1
### Problem 1a
Download dataset menggunakan `kaggle datasets download -d irwansyah10010/mobilelegend` setelah berhasil mendownload dengan format file .zip, langkah selanjutnya adalah mengekstrak file tersebut. Kalian melakukannya di dalam file `ayamgoreng.c` untuk semua pengerjaannya

**Jawab**

*1. Sebelum memulai program, kita harus setup environtment terlebih dahulu. Instal pip (Python Package Installer) di sistem yang digunakan*
```bash
sudo apt update
```
```bash
sudo apt install python3-pip
```

*2. Jika sudah, selanjutnya install Kaggle CLI*
```bash
pip install kaggle
```

*3. Setelah berhasil menginstal Kaggle CLI, konfigurasi kredensial Kaggle dengan membuka halaman Kaggle, pergi ke tab "Account", dan klik pada tombol "Create API Token". Lalu akan mengunduh file kaggle.json.*

*4. Pindahkan file kaggle.json ke direktori ~/.kaggle/. Jika menggunakan wsl, bisa langsung memindahkan secara manual dengan masuk ke \\wsl.localhost/Ubuntu/home/{username}/.kaggle*

*5. Setelah selesai setup environtment, kita lanjutkan ke program ayamgoreng.c. Pertama adalah membuat struct untuk menampung nama hero, role, dan point skillnya*
```C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#define MAX 300 //remove and hero total
#define MAX_LINE 1000

typedef struct {
    char namaHero[40];
    char role[2][40];  // array untuk menyimpan hero yang memiliki 2 role
    int skillPoints;
} Hero;
```
- `char namaHero[40]` adalah array untuk menyimpan nama hero
- `char role[2][40]` adalah array dua dimensi untuk menyimpan role yang dimiliki hero. Ini untuk menangani apabila hero memiliki 2 role, contohnya Minotaur dengan role TANK/SUPPORT
- `int skillPoints` adalah variabel bertipe integer digunakan untuk menyimpan jumlah poin

*6. Membuat fungsi untuk mendownload dan mengekstrak file dari link : kaggle datasets download -d irwansyah10010/mobilelegend. Saya disini menggunakan fork untuk prosesnya*
```C
void download_extract_datasets(char *path) {
    int status;
    pid_t pid;
    pid = fork();
    
    if (pid == 0) {
        // child process
        execlp("kaggle", "kaggle", "datasets", "download", "-d", "irwansyah10010/mobilelegend", "-p", path, NULL);
        perror("execlp");
        exit(1);
    }
    else if (pid > 0) {
        // parent process
        wait(&status); 
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            printf("Download zip berhasil.\n");
            if (fork() == 0) {
                char zip_path[100]; // atau ukuran yang lebih besar jika diperlukan
                snprintf(zip_path, sizeof(zip_path), "%s/mobilelegend.zip", path);
                execlp("unzip", "unzip", "-q", "mobilelegend.zip", "-d", path, NULL); // mengextract file zip
                perror("execlp");
                exit(1);
            } else {
                wait(NULL); // menunggu child process selesai
                printf("Ekstraksi file zip berhasil.\n");
            }
        } else {
            printf("Download zip gagal.\n");
        }
    }    
    else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}
```
- Fungsi ini menerima satu parameter berupa string yang merupakan path (lokasi) tempat dataset akan diunduh dan diekstrak
- Menggunakan `fork()` untuk melakukan download dan ekstrak file .zip
- `execlp()` dipanggil untuk menjalankan perintah Kaggle CLI (`kaggle datasets download -d irwansyah10010/mobilelegend -p <path>`)
- Parent process menunggu child process selesai dengan `wait(&status)`. Jika child process selesai, maka akan mengoutputkan bahwa download telah berhasil
- Setelah itu child process untuk mengekstrak file zip yang sudah di download dengan `execlp("unzip", "unzip", "-q", "mobilelegend.zip", "-d", path, NULL)`

*7. Selanjutnya, saya membuat fungsi untuk menghapus file .zip yang tidak digunakan (walaupun di soal tidak ada perintahnya)*
```C
void remove_zip(char *path) {
    char zip_path[MAX];
    snprintf(zip_path, sizeof(zip_path), "%s/mobilelegend.zip", path);
    
    if (fork() == 0) {
        execlp("rm", "rm", "-f", "mobilelegend.zip", NULL);
        perror("execlp");
        exit(1);
    } else {
        wait(NULL);
        printf("File zip berhasil dihapus.\n");
    }
}
```
- Fungsi ini yang menerima satu parameter berupa string yang merupakan path (lokasi) tempat file .zip berada
- Membuat child process dan mengeksekusi perintah `execlp("rm", "rm", "-f", "mobilelegend.zip", NULL)`
- Perintah `rm` untuk menghapus file zip dan `-f` untuk menghapus file tanpa mengkonfirmasi pengguna

*8. Setelah pembuatan fungsi, selanjutnya kita beralih ke Main Function*
```C
int main(int argc, char *argv[])
{
    char *ori_path = ".";
    Hero heroes[MAX];
    Hero best_heroes[6]; // inisialisasi array untuk menyimpan pahlawan terbaik untuk setiap peran

    download_extract_datasets(ori_path); // mendownload dan ekstrak zip
    remove_zip(ori_path); // menghapus zip

    .....
}
```
- `char *ori_path = "."` adalah variabel untuk menyimpan path (lokasi) saat in
- `Hero heroes[MAX]` adalah array untuk menyimpan data tentang pahlawan (hero) dari dataset yang akan diunduh dan diekstrak
- `Hero best_heroes[6]` adalah array untuk menyimpan pahlawan terbaik untuk setiap peran dengan ukuran 6, dimana sesuai dengan jumlah role yang ada
- Fungsi `download_extract_datasets()` untuk engunduh dataset dari Kaggle, mengekstraknya, dan menyimpannya di path yang ditentukan
- Fungsi `remove_zip()`untuk menghapus file zip setelah dataset diekstrak dari path yang ditentukan

*9. Dokumentasi. Program saya jalankan sesuai Main Function yang saya tunjukkan di atas*
- Terminal
![alt text](/resource/1a-1.png)
- Hasil download dan ekstrak dan remove zip
![alt text](/resource/1a-2.png)

### Problem 1b
`ayamgoreng.c` harus bisa mengoutputkan semua hero yang terbaik pada setiap role secara default tanpa argumen, namun juga bisa menampilkan sesuai dengan role yang diberikan pada argumen pada saat pemanggilan program (`./ayamgoreng [role]`). Data hero beserta rolenya dapat dilihat pada file identitas.csv, sedangkan data hero beserta atributnya dapat dilihat pada file atribut-hero.csv. Keluarkan informasi mengenai hero dan skillpointsnya dengan format `Hero terbaik adalah (nama hero) dengan skillpoint (jumlah skillpoint)`.

**Jawab**

*1. Membuat fungsi untuk membaca csv dan menyimpan nama hero beserta role-nya*
```C
int read_identitas_hero(const char *csvname, Hero heroes[]) {
    FILE *file = fopen(csvname, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char line[MAX_LINE];
    bool firstLine = true;
    while (fgets(line, MAX_LINE, file) != NULL && count < MAX) {
        if (firstLine) {
        firstLine = false;
        continue;
        }

        char temp_name[40], temp_role[40];
        sscanf(line, "%[^;];%[^;];%*[^;];%*s", temp_name, temp_role);
        char *token = strtok(temp_role, "/");
        int role_count = 0;
        while (token != NULL && role_count < 2) {
            strcpy(heroes[count].namaHero, temp_name);
            strncpy(heroes[count].role[role_count], token, sizeof(heroes[count].role[role_count]) - 1);
            heroes[count].role[role_count][sizeof(heroes[count].role[role_count]) - 1] = '\0'; // memastikan akhiran string
            count++;
            token = strtok(NULL, "/");
        }
    }
    fclose(file);
    return count;
}
```
- Fungsi ini menerima dua parameter, yaitu `csvname` yang merupakan path nama file CSV yang akan dibaca, dan `heroes[]` yang merupakan array dari tipe `Hero` di mana data hero akan disimpan
- `int count = 0` digunakan untuk menghitung jumlah hero yang berhasil dibaca dan disimpan
- `char line[MAX_LINE]` digunakan untuk menyimpan satu baris dari file CSV yang sedang dibaca
- `bool firstLine = true`digunakan untuk memeriksa apakah baris yang sedang dibaca adalah baris pertama dari file CSV. Jika iya, maka akan diabaikan dan mengubah `firstLine` menjadi `False` 
- `while (fgets(line, MAX_LINE, file) != NULL && count < MAX)` adalah loop while yang membaca setiap baris dari file CSV menggunakan `fgets`
- `char temp_name[40]` dan `temp_role[40]` digunakan untuk menyimpan nama dan peran sementara dari hero yang sedang dibaca
- `sscanf` digunakan untuk memformat dan memindai string yang terbaca dari `line` dengan memisahkan nama hero dan role-nya
- Karena dalam dataset satu hero dapat memiliki lebih dari satu role, maka `char *token = strtok(temp_role, "/")` digunakan untuk memisahkan kedua role tersebut. Selanjutnya, loop while akan membaca setiap token dari string `temp_role` (peran hero). Loop akan berhenti jika tidak ada token lagi yang dapat dibaca atau jika jumlah peran hero yang telah dibaca sudah mencapai 2
- Di dalam loop, data hero (nama dan role) akan disimpan dalam array `heroes[]`
- `token = strtok(NULL, "/")` digunakan untuk melanjutkan proses pemecahan string yang dimulai oleh pemanggilan sebelumnya ke fungsi `strtok()`
- `return count` digunakan untuk mengembalikan jumlah hero yang berhasil dibaca dan disimpan dalam array `heroes[]`

*2. Selanjutnya, kita membuat fungsi untuk menghitung point skill setiap hero dengan rumus yang sudah diberikan sesuai role-nya*
```C
void calculate_point(const char *csvskill, int data_hero, Hero heroes[]) {
    FILE *skill = fopen(csvskill, "r");
    if (skill == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE];
    int total_point = 0;
    while(fgets(line, MAX_LINE, skill) != NULL) {
        char namaHero[40];
        float hp, physical_attack, attack_speed, mana, mana_regen, attack_speed_total;

        sscanf(line, "%[^;];%f;%*f;%f;%*f;%f;%*f;%f;%f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%f", 
            namaHero, &hp, &physical_attack, &attack_speed, &mana, &mana_regen, &attack_speed_total);

        for (int i = 0; i < data_hero; i++) {
            if (strcmp(heroes[i].namaHero, namaHero) == 0) {
            for (int j = 0; j < 2 && heroes[i].role[j][0] != '\0'; j++) {
                if (strcmp(heroes[i].role[j], "TANK") == 0) {
                total_point += hp;
                } else if (strcmp(heroes[i].role[j], "ASSASSIN") == 0) {
                total_point += physical_attack;
                } else if (strcmp(heroes[i].role[j], "FIGHTER") == 0) {
                total_point += hp + physical_attack;
                } else if (strcmp(heroes[i].role[j], "MM") == 0) {
                total_point += physical_attack * attack_speed;
                } else if (strcmp(heroes[i].role[j], "MAGE") == 0) {
                total_point += mana / mana_regen;
                } else if (strcmp(heroes[i].role[j], "SUPPORT") == 0) {
                total_point += mana_regen + hp;
                }
            }
            heroes[i].skillPoints = total_point;
            }
            total_point = 0;
        }
    }
    fclose(skill);
}
```
- Fungsi ini menerima tiga parameter, yaitu `csvskill` yang merupakan path nama file CSV yang berisi data keterampilan (skill) hero, `data_hero` yang merupakan jumlah hero yang telah dibaca dan disimpan, dan `heroes[]` yang merupakan array dari tipe `Hero` yang berisi data hero
- Setelah membaca filenya, program akan membaca setiap baris dari file CSV menggunakan fgets dengan `while` loop. Loop akan berhenti jika tidak ada baris lagi yang dapat dibaca
- `sscanf` digunakan untuk memformat dan memindai string yang terbaca dari line, yang berisi data keterampilan hero. Data yang terbaca kemudian disimpan dalam variabel-variabel yang sesuai
- Setelah data keterampilan hero terbaca, dilakukan perulangan untuk mencocokkan nama hero dari file CSV dengan nama hero yang sudah disimpan sebelumnya dalam array `heroes[]`. Jika nama hero cocok, maka dilakukan perulangan lagi untuk setiap peran hero yang dimilikinya.Di dalam perulangan untuk setiap peran hero, nilai total poin keterampilan `total_point` dihitung berdasarkan aturan/operasi yang diberikan, sesuai dengan peran masing-masing hero. 
- Setelah perulangan selesai, nilai `total_point` disimpan dalam atribut `skillPoints` dari struktur `Hero` yang bersangkutan

*3. Setelah mendapatkan semua poin skill hero untuk setiap rolenya, dilanjutkan membuat fungsi untuk mencari hero dengan poin skill terbaik/tertinggi dari masing-masing role*
```C
void best_hero(int data_hero, Hero heroes[], Hero best_heroes[6]) {
    int max_points[6] = {0}; // inisialisasi array untuk menyimpan poin maksimum untuk setiap role
    for (int i = 0; i < data_hero; i++) {
        for (int j = 0; j < 2 && heroes[i].role[j][0] != '\0'; j++) {
            if (strcmp(heroes[i].role[j], "TANK") == 0 && heroes[i].skillPoints > max_points[0]) {
                max_points[0] = heroes[i].skillPoints;
                strcpy(best_heroes[0].namaHero, heroes[i].namaHero);
                strcpy(best_heroes[0].role[0], heroes[i].role[0]);
                best_heroes[0].skillPoints = heroes[i].skillPoints;
            } else if (strcmp(heroes[i].role[j], "ASSASSIN") == 0 && heroes[i].skillPoints > max_points[1]) {
                max_points[1] = heroes[i].skillPoints;
                strcpy(best_heroes[1].namaHero, heroes[i].namaHero);
                strcpy(best_heroes[1].role[0], heroes[i].role[0]);
                best_heroes[1].skillPoints = heroes[i].skillPoints;
            } else if (strcmp(heroes[i].role[j], "FIGHTER") == 0 && heroes[i].skillPoints > max_points[2]) {
                max_points[2] = heroes[i].skillPoints;
                strcpy(best_heroes[2].namaHero, heroes[i].namaHero);
                strcpy(best_heroes[2].role[0], heroes[i].role[0]);
                best_heroes[2].skillPoints = heroes[i].skillPoints;
            } else if (strcmp(heroes[i].role[j], "MM") == 0 && heroes[i].skillPoints > max_points[3]) {
                max_points[3] = heroes[i].skillPoints;
                strcpy(best_heroes[3].namaHero, heroes[i].namaHero);
                strcpy(best_heroes[3].role[0], heroes[i].role[0]);
                best_heroes[3].skillPoints = heroes[i].skillPoints;
            } else if (strcmp(heroes[i].role[j], "MAGE") == 0 && heroes[i].skillPoints > max_points[4]) {
                max_points[4] = heroes[i].skillPoints;
                strcpy(best_heroes[4].namaHero, heroes[i].namaHero);
                strcpy(best_heroes[4].role[0], heroes[i].role[0]);
                best_heroes[4].skillPoints = heroes[i].skillPoints;
            } else if (strcmp(heroes[i].role[j], "SUPPORT") == 0 && heroes[i].skillPoints > max_points[5]) {
                max_points[5] = heroes[i].skillPoints;
                strcpy(best_heroes[5].namaHero, heroes[i].namaHero);
                strcpy(best_heroes[5].role[0], heroes[i].role[0]);
                best_heroes[5].skillPoints = heroes[i].skillPoints;
            }
        }
    }
}
```
- Fungsi ini menerima tiga parameter, yaitu `data_hero` yang merupakan jumlah hero yang telah dibaca dan disimpan, dan `heroes[]` yang merupakan array dari struktur `Hero` yang berisi data hero, dan `best_heroes[6]` yang merupakan array dari struktur `Hero` untuk menyimpan data hero dengan poin skill terbaik
- `int max_points[6] = {0}` digunakan untuk menyimpan jumlah poin maksimum untuk setiap role. Array ini diinisialisasi dengan nilai 0 untuk setiap role
- Nested loop digunakan untuk memeriksa setiap hero dan setiap perannya. Loop pertama digunakan untuk mengakses setiap hero dalam array `heroes[]`, sedangkan loop kedua digunakan untuk mengakses setiap role dari hero tersebut
- Jika role yang dimiliki sama, maka akan dilakukan perbandingan poin skill. Jika jumlah poin skill hero tersebut lebih besar dari poin maksimum yang telah disimpan sebelumnya, maka poin maksimum tersebut diperbarui dengan nilai poin skukk hero, dan informasi hero tersebut disalin ke array `best_heroes[]`

*4. Setelah semua fungsi ada, lanjut ke Main Function*
```C
int main(int argc, char *argv[])
{
    .....

    char *csvhero = "./Data Mobile Legend/identitas.csv";
    char *csvskill = "./Data Mobile Legend/Atribut/atribut-hero.csv";
    
    int data_hero = read_identitas_hero(csvhero, heroes); // membaca dan menyimpan data hero
    calculate_point(csvskill, data_hero, heroes); // menghitung poin skill setiap hero
    best_hero(data_hero, heroes, best_heroes); // mencari hero dengan poin skill tertinggi untuk setiap role

    // periksa apakah argumen role ada
    if (argc > 1) {
        char *role = argv[1];
        printf("\nHero terbaik untuk role:\n");
        printf("-- %s --\n", role);
        for (int i = 0; i < 6; i++) {
            if (strcmp(best_heroes[i].role[0], role) == 0) {
                printf("Hero terbaik adalah %s dengan skillpoint %d\n", best_heroes[i].namaHero, best_heroes[i].skillPoints);
            }
        }
    }
    else {
        // rinr hero terbaik untuk setiap role
        printf("\nHero terbaik setiap role:\n");
        for (int i = 0; i < 6; i++) {
            printf("-- %s --\n", best_heroes[i].role[0]);
            printf("Hero terbaik adalah %s dengan skillpoint %d\n", best_heroes[i].namaHero, best_heroes[i].skillPoints);
        }
    }

    return 0;
}
```
- `csvhero` dan `csvskill` dideklarasikan untuk menyimpan path ke dua file CSV. `csvhero` berisi path ke file CSV yang berisi informasi identitas hero, sedangkan `csvskill` berisi path ke file CSV yang berisi atribut keterampilan hero
- Pemanggilan fungsi `read_identitas_hero` untuk membaca dan menyimpan data hero dari file CSV ke dalam array `heroes[]`. Kemudian data tersebut disimpan dalam variabel `data_hero`
- Pemanggilan fungsi `calculate_point` dan juga `best_hero`
- Pada _Main Function_, program memiliki 2 kondisi, yaitu ketika ada argumen dan juga tidak ada argumen. Kondisi pertama, jika ada argumen role yang diberikan saat menjalankan program, maka program akan mengeksekusi blok `if (argc > 1)` dan menampilkan informasi hero terbaik untuk role yang diberikan.
- Kondisi kedua, jika tidak ada argumen yang diberikan saat menjalankan program, maka program akan mengeksekusi blok `else` dan menampilkan informasi hero terbaik untuk semua role

*5. Dokumentasi*
- Terminal (ketika tidak ada argumen)
![alt text](/resource/1b-1.png)
- Terminal (ketika ada argumen)
![alt text](/resource/1b-2.png)

### Problem 1c
Jess No Limit menyadari bahwa sistem kalian sangat berguna dan ingin sistem ini bisa diakses oleh teman satu timnya. Oleh karena itu, kalian perlu menjadikan sistem yang dibuat ke sebuah Docker Container agar mudah di-distribute dan dijalankan di lingkungan lain tanpa perlu setup environment dari awal. Buatlah Dockerfile yang berisi semua langkah yang diperlukan untuk setup environment dan menentukan bagaimana aplikasi harus dijalankan. Notes: Command yang dijalankan pada docker file tidak terdapat argumen dan akan menampilkan semua role

**Jawab**

*1. Dockerfile*
```Dockerfile
# Base Image
FROM ubuntu:latest

# Instal Dependencies
RUN apt-get update
RUN apt-get install -y \
    gcc \
    unzip \
    python3 \
    python3-pip \
    python3-venv
RUN apt-get clean

# Create and activate virtual environment
RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:${PATH}"

# Install Kaggle CLI
RUN pip install kaggle

# Generate Kaggle API Key
RUN mkdir -p /root/.kaggle && \
    echo '{"username":"hfwzsd","key":"1be2d13700ab981c07f30afcca6d057d"}' > /root/.kaggle/kaggle.json && \
    chmod 600 /root/.kaggle/kaggle.json

# Set working directory
WORKDIR /APP

# Copy source code to working directory
COPY ayamgoreng.c .

# Set execute permission
RUN chmod +x ayamgoreng.c

# Compile source code
RUN gcc -o ayamgoreng ayamgoreng.c
```
- `FROM ubuntu:latest` merubakan base image untuk membangun container Docker. Image dasar adalah gambar yang digunakan sebagai titik awal untuk membangun dan menjalankan container Docker. Dalam hal ini, dipilih menggunakan image ubuntu:latest, yang merupakan versi terbaru dari sistem operasi Ubuntu.
- `RUN apt-get update` untuk memperbarui daftar paket pada image
- `RUN apt-get install -y \ gcc \ unzip \ python3 \ python3-pip \ python3-venv` untuk dependensi yang dibutuhkan, termasuk GCC (GNU Compiler Collection) untuk kompilasi, unzip untuk mengekstrak file, dan Python 3 serta beberapa paket pendukungnya
- `gcc` adalah kompiler C yang diperlukan untuk mengkompilasi kode C
- `unzip` adalah utilitas untuk mengekstrak file ZIP
- `python3` adalah interpreter Python versi 3, yang diperlukan untuk menjalankan skrip Python dalam container
- `python3-pip` adalah alat manajemen paket untuk Python versi 3, yang diperlukan untuk menginstal paket-paket Python tambahan
- `python3-venv` adalah paket di lingkungan Python yang menyediakan modul venv untuk membuat lingkungan virtual Python
- `RUN apt-get clean` untuk membersihkan cache yang dihasilkan oleh apt-get untuk mengurangi ukuran image
- `RUN python3 -m venv /opt/venv` untuk membuat dan mengaktifkan virtual environment Python di direktori `/opt/venv`
- `ENV PATH="/opt/venv/bin:${PATH}"` untuk mengatur PATH environment variable agar mencakup direktori `/opt/venv/bin`, sehingga perintah-perintah yang terinstal di virtual environment dapat diakses secara langsung
- `RUN pip install kaggle` untuk menginstal Kaggle CLI (Command Line Interface) menggunakan pip dalam container Docker
- `RUN mkdir -p /root/.kaggle && \
    echo '{"username":"hfwzsd","key":"1be2d13700ab981c07f30afcca6d057d"}' > /root/.kaggle/kaggle.json && \
    chmod 600 /root/.kaggle/kaggle.json` untuk membuat direktori `.kaggle` di dalam direktori home root, dan menyimpan file kaggle.json yang berisi informasi autentikasi API Kaggle
- `WORKDIR /APP` untuk menetapkan direktori kerja ke `/APP`
- `COPY ayamgoreng.c .` untuk menyalin file `ayamgoreng.c` dari host ke dalam direktori kerja Docker
- `RUN chmod +x ayamgoreng.c` untuk memberikan izin eksekusi ke file `ayamgoreng.c`
- `RUN gcc -o ayamgoreng ayamgoreng.c` untuk mengompilasi file ayamgoreng.c menjadi sebuah binary ayamgoreng. Perintah tersebut akan dijalankan di dalam container Docker

*2. Dokumentasi*
- Build image joki-ml-bang
![alt text](/resource/1c-1.png)
- Cek image
![alt text](/resource/1c-2.png)
- Jalankan container, tanpa argumen
![alt text](/resource/1c-3.png)
- Jalankan container, dengan argumen (di soal tidak diminta, tetapi saya hanya menunjukkan)
![alt text](/resource/1c-4.png)

### Problem 1d
Merasa terpanggil untuk membantu Jess No Limit lebih jauh, kalian memutuskan untuk mem-publish Docker Image sistem ke Docker Hub, sebuah layanan cloud yang memungkinkan kalian untuk membagikan aplikasi Docker kalian ke seluruh dunia. Output dari pekerjaan ini adalah file Docker kalian bisa dilihat secara public pada `https://hub.docker.com/r/{Username}/joki-ml-bang`.

**Jawab**

Pada bagian ini tidak ada kode yang diperlukan, kita hanya perlu melakukan push image yang telah di-build ke akun Dockerhub kita. Berikut lankah-langkahnya:

*1. Pastikan telah memiliki akun Dockerhub, lalu login pada terminal linux*
![alt text](/resource/1d-1.png)
*2. Pastikan image yang telah dibangun sudah ada*
![alt text](/resource/1d-2.png)
*3. Push image ke Dockerhub. Sebelum di push, bisa lakukan tag terlebih dahulu seperti tampilan di bawah*
![alt text](/resource/1d-3.png)
*4. Jika sudah, kunjungi alamat `https://hub.docker.com/r/{Username}/joki-ml-bang`. Jika berhasil, tampilan akan seperti dibawah ini*
![alt text](/resource/1d-4.png)

### Problem 1e
Melihat betapa banyaknya fans Jess No Limit, kalian diminta untuk menerapkan skala pada layanan menggunakan Docker Compose dengan instance sebanyak 6 (untuk setiap role). Pastikan setiap instance memanggil program untuk menampilkan hero terbaik sesuai dengan role yang diberikan pada argumen. Penamaan setiap instance sama dengan role yang akan ditampilkan (instance mage, instance fighter, dst).

**Jawab**

*1. Membuat docker-compose.yml (program saya ada 2 versi, dimana versi pertama akan menghasilkan container task-1 dan versi kedua menghasilkan container joki-ml-bang. Pada case kali ini saya menggunakan versi pertama)*
```yml
version: '3'

services:
  mage:
    build:
      context: . # use current directory
      dockerfile: Dockerfile # use Dockerfile
    command: ./ayamgoreng MAGE # run the container with MAGE argument
    scale: 6 # 6 instances


  fighter:
    build:
      context: .
      dockerfile: Dockerfile
    command: ./ayamgoreng FIGHTER
    scale: 6 # 6 instances

  tank:
    build:
      context: .
      dockerfile: Dockerfile
    command: ./ayamgoreng TANK
    scale: 6 # 6 instances

  assassin:
    build:
      context: .
      dockerfile: Dockerfile
    command: ./ayamgoreng ASSASSIN
    scale: 6 # 6 instances

  support:
    build:
      context: .
      dockerfile: Dockerfile
    command: ./ayamgoreng SUPPORT
    scale: 6 # 6 instances

  mm:
    build:
      context: .
      dockerfile: Dockerfile
    command: ./ayamgoreng MM
    scale: 6 # 6 instances
```
- `version: '3'` mendefinisikan versi Docker Compose yang digunakan dalam file ini. Dalam hal ini, menggunakan versi 3
- `services:` mendefinisikan layanan-layanan yang akan dijalankan menggunakan Docker Compose. Setiap layanan akan memiliki konfigurasi yang berbeda
- `mage`, `fighter`, `tank`, `assassin`, `support`, `mm` merupakan nama layanan untuk kontainer yang akan dijalankan. Setiap layanan mewakili role dalam sebuah permainan (game)
- `build` menunjukkan bahwa image untuk setiap layanan akan dibangun dari Dockerfile yang ada di dalam direktori yang sama dengan file `docker-compose.yml`
- `context: .` Menunjukkan bahwa Docker Compose akan menggunakan konteks saat ini (direktori yang berisi file `docker-compose.yml`) untuk membangun image
- `dockerfile: Dockerfile` menunjukkan nama Dockerfile yang akan digunakan untuk membangun image. Dalam hal ini, Dockerfile yang sama digunakan untuk semua layanan
- `command:` untuk mnentukan perintah yang akan dijalankan saat kontainer dimulai. Di sini, `./ayamgoreng` adalah nama file yang akan dieksekusi dan argumen setiap layanan ditentukan (misalnya: `MAGE`, `FIGHTER`, dll.)
- `scale: 6` menunjukkan bahwa setiap layanan akan dijalankan sebanyak 6 instance

*2. Dokumentasi*
> Anda bisa memilih antara 2 versi program yang ada pada docker-compose.yml. Versi pertama akan membuat container task-1 dan versi kedua akan membuat container joki-ml-bang. Walaupun nama container berbeda, isi dari container tetap sama
- Run `docker-compose.yml`
![alt text](/resource/1e-1.png)
- Cek hasilnya pada Docker Desktop
![alt text](/resource/1e-2.png)
![alt text](/resource/1e-3.png)
- Jika ingin menghentikan dan membersihkan lingkungan yang dibangun, dapat menjalankan `docker-compose down`
![alt text](/resource/1e-4.png)

### Kendala

Sejauh ini belum ada kendala dalam mengerjakan soal no 1.

## 2️⃣ Soal 2
### Problem 2a
Buatlah 2 file, yaitu `server.c` dan `client.c`.

Disaat `server.c` pertama kali dijalankan, dia akan meminta prompt user untuk mengetikkan berapa banyak client yang akan dilayani (range 1-5).

Disaat `client.c` pertama kali dijalankan, dia akan meminta prompt user untuk mengetikkan username. Username ini kemudian dikirim ke server, untuk di check apakah sudah ada sebelumnya atau tidak. Jika sudah ada, maka akan meminta prompt lagi untuk mengetikkan username sampai diterima oleh server.

**Jawab**

[Jawab Disini]

### Problem 2b
Ketika semua client yang dibutuhkan oleh server telah terkumpul, setiap client akan mulai diberikan prompt untuk mengetikkan service yang dibutuhkan, yaitu `Nama Container`, `Image yang Digunakan`, `Perintah Saat Kontainer Dimulai`, dan `Volume`. Urutan client yang mengirimkan request service ke server ditentukan dari waktu mereka register. Contoh: Jika username ragnar registrasi pertama kali, lalu diikuti username towel, maka ragnar yang akan mengirim request terlebih dahulu, lalu diikuti towel, dst.

**Jawab**

[Jawab Disini]

### Problem 2c
Setelah semua request service dari client terkumpul, server lalu menggabungkannya menjadi sebuah file docker compose. Lalu jalankan file docker compose yang dibuat tadi.

**Jawab**

[Jawab Disini]

### Problem 2d
 Tidak sampai situ, setelah docker compose sebelumnya selesai dijalankan, `client.c` akan meminta prompt lagi dari user. Prompt yang diberikan sesuai dengan point (b). Jika setiap client melakukan hal yang sama pada point (b), maka server akan menghasilkan file docker compose yang baru. Lalu container yang telah dijalankan sebelumnya akan dihancurkan, yang kemudian akan digantikan oleh service terbaru yang telah di request dari client tadi.

**Jawab**

[Jawab Disini]

### Kendala

[Tulis Disini]

## 3️⃣ Soal 3
### Problem 3a
Buatlah program `chat.c` yang dapat menulis pesan dan membaca pesan pada sebuah file. dimana pesan yang akan ditulis harus dijalankan menggunakan multithread, sehingga 1 thread mewakili 1 kata.

**Jawab**

[Jawab Disini]

### Problem 3b
Buatlah Docker Image yang didalamnya berisi `chat.c` yang telah dibuat sebelumnya dan juga sudah tercompile dengan gcc (alias compile program c nya harus pada Dockerfile) dan beri nama `dockermessage`.

**Jawab**

[Jawab Disini]

### Problem 3c
Lalu buatlah `pengaturan.c` yang dapat membuat container baru yang unik dan menghapus container tersebut dari host, dengan docker image yang telah kalian buat sebelumnya menggunakan Dockerfile. contoh:

untuk membuat container dengan nama dhafin: `./pengaturan create dhafin`

untuk menghapus container dhafin: `./pengaturan delete dhafin`

untuk melihat semua container yang tersedia `./pengaturan list`

untuk login atau masuk ke dalam container `./pengaturan login dhafin`

**Jawab**

[Jawab Disini]

### Problem 3d
Modifikasi `chat.c` dan build ulang menjadi docker image `dockermessage:v2` agar dapat mengirim chat ke container lain dan tambahkan argument pada pengaturan.c agar dapat connect dan uncoonnect sebuah container. (agar container dapat chat dengan container tujuan, container yang ingin chat harus connect terlebih dahulu ke container tujuan. Dan ketika sebuah container terbuat, secara otomatis dia juga memiliki kotak pesan yang nantinya dapat dia read dan dikirimi pesan oleh container lain). contoh:

untuk connect container dhafin ke container wahid: `./pengaturan connect dhafin wahid`

untuk unconnect container dhafin ke container wahid: `./pengaturan unconnect dhafin wahid`

ketika user sedang dalam container dhafin dan ingin mengirim pesan ke container wahid: `./chat write halo teman wahid`

ketika user sedang dalam container wahid dan ingin mengirim pesan ke dhafin: `./chat write halo teman dhafin`

untuk melihat isi kotak pesan di container saat ini: `./chat read`

**Jawab**

[Jawab Disini]

### Kendala

[Tulis Disini]

## 4️⃣ Soal 4
### Problem 4a
Akses URL berikut untuk mendapatkan resource yang dibutuhkan, yaitu sebuah aplikasi yang sedang dibuat oleh Shaniz696969!

https://drive.google.com/file/d/1iMCSmUzlQ1OqIU72o9IGbPMeghFbj_zK/view?usp=sharing

It’s kinda legit, right? Aneh juga ya dia tidak pakai GitHub atau semacamnya tapi malah pakai Google Drive (kocak). Tapi gapapa lah ya. Nah, tugas kamu adalah untuk membuat image dari aplikasi tersebut!

**Jawab**

[Jawab Disini]

### Problem 4b
Selanjutnya, karena Shaniz696969 mengatakan bahwa aplikasi ini menggunakan relational database berupa MySQL, mau tidak mau kamu harus membuat container yang menjalankan image dari MySQL! Pastikan container berjalan sebagai daemon.

**Jawab**

[Jawab Disini]

### Problem 4c
Kamu ingat bahwa sudah membuat image dari aplikasi Shaniz696969? Nah, sekarang, jalankan image tersebut sebagai container. Pastikan container berjalan sebagai daemon.

**Jawab**

[Jawab Disini]

### Problem 4d
Apa lagi yang kurang? Yup, kamu harus melakukan koneksi antara aplikasi backend tersebut dengan database yang telah dijalankan. Tentunya, dalam container yang telah kita jalankan di poin-poin sebelumnya, kan? Nah, lakukan koneksi antara dua container tersebut dalam satu network bernama Shani-net!

**Jawab**

[Jawab Disini]

### Problem 4e
Terakhir, kamu harus lakukan setup pada aplikasi backend tersebut dengan menggunakan dokumentasi Laravel sebagai panduan kalian! Aplikasi harus bisa diakses melalui http://localhost:9090. Agar lebih legit, kalian bisa melakukan hit pada endpoint /api/province.

**Jawab**

[Jawab Disini]

### Kendala

[Tulis Disini]

<div align=center>

# ------- SELESAI -------

</div>