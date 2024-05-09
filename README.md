[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/jYae_yK9)
<div align=center>

|    NRP     |      Name      |
| :--------: | :------------: |
| 5025221000 | Student 1 Name |
| 5025221000 | Student 2 Name |
| 5025221103 | Hilmi Fawwaz Sa'ad |

# Praktikum Modul 1 _(Module 1 Lab Work)_

</div>

### Daftar Soal _(Task List)_

- [Task 1 - Jess No Limit Push Rank](/task-1/)

- [Task 2 - BNBWT](/task-2/)

- [Task 3 - Volume Expansion](/task-3/)

- [Task 4 - WOTA Competition](/task-4/)

### Laporan Resmi Praktikum Modul 1 _(Module 1 Lab Work Report)_

Tulis laporan resmi di sini!

_Write your lab work report here!_

## 1️⃣ Soal 1
### Problem 1a
Download dataset menggunakan `kaggle datasets download -d irwansyah10010/mobilelegend` setelah berhasil mendownload dengan format file .zip, langkah selanjutnya adalah mengekstrak file tersebut. Kalian melakukannya di dalam file `ayamgoreng.c` untuk semua pengerjaannya

**Jawab**

[Jawab Disini]

### Problem 1b
`ayamgoreng.c` harus bisa mengoutputkan semua hero yang terbaik pada setiap role secara default tanpa argumen, namun juga bisa menampilkan sesuai dengan role yang diberikan pada argumen pada saat pemanggilan program (`./ayamgoreng [role]`). Data hero beserta rolenya dapat dilihat pada file identitas.csv, sedangkan data hero beserta atributnya dapat dilihat pada file atribut-hero.csv. Keluarkan informasi mengenai hero dan skillpointsnya dengan format `Hero terbaik adalah (nama hero) dengan skillpoint (jumlah skillpoint)`.

**Jawab**

[Jawab Disini]

### Problem 1c
Jess No Limit menyadari bahwa sistem kalian sangat berguna dan ingin sistem ini bisa diakses oleh teman satu timnya. Oleh karena itu, kalian perlu menjadikan sistem yang dibuat ke sebuah Docker Container agar mudah di-distribute dan dijalankan di lingkungan lain tanpa perlu setup environment dari awal. Buatlah Dockerfile yang berisi semua langkah yang diperlukan untuk setup environment dan menentukan bagaimana aplikasi harus dijalankan. Notes: Command yang dijalankan pada docker file tidak terdapat argumen dan akan menampilkan semua role

**Jawab**

[Jawab Disini]

### Problem 1d
Merasa terpanggil untuk membantu Jess No Limit lebih jauh, kalian memutuskan untuk mem-publish Docker Image sistem ke Docker Hub, sebuah layanan cloud yang memungkinkan kalian untuk membagikan aplikasi Docker kalian ke seluruh dunia. Output dari pekerjaan ini adalah file Docker kalian bisa dilihat secara public pada `https://hub.docker.com/r/{Username}/joki-ml-bang`.

**Jawab**

[Jawab Disini]

### Problem 1e
Melihat betapa banyaknya fans Jess No Limit, kalian diminta untuk menerapkan skala pada layanan menggunakan Docker Compose dengan instance sebanyak 6 (untuk setiap role). Pastikan setiap instance memanggil program untuk menampilkan hero terbaik sesuai dengan role yang diberikan pada argumen. Penamaan setiap instance sama dengan role yang akan ditampilkan (instance mage, instance fighter, dst).

**Jawab**

[Jawab Disini]

### Kendala

[Tulis Disini]

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