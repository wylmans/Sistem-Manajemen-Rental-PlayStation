# 🎮 Sistem Manajemen Rental PlayStation

![Qt](https://img.shields.io/badge/Qt-6.x-green.svg)
![C++](https://img.shields.io/badge/C++-17-blue.svg)
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)

Sistem manajemen rental PlayStation yang modern, profesional, dan real-time dengan fitur kalkulasi otomatis untuk bonus malam, sisa waktu bermain, dan status rental.

## 📋 Daftar Isi

- [Fitur Utama](#-fitur-utama)
- [Screenshot](#-screenshot)
- [Persyaratan Sistem](#-persyaratan-sistem)
- [Instalasi](#-instalasi)
- [Konfigurasi Database](#-konfigurasi-database)
- [Cara Penggunaan](#-cara-penggunaan)
- [Logika Kalkulasi](#-logika-kalkulasi)
- [Struktur Database](#-struktur-database)
- [Struktur Project](#-struktur-project)
- [Troubleshooting](#-troubleshooting)
- [Kontribusi](#-kontribusi)
- [Lisensi](#-lisensi)

---

## ✨ Fitur Utama

### 🔌 Multi-Database Support
- **SQLite** - Database file lokal (tidak perlu server)
- **PostgreSQL** - Enterprise-grade database
- **MySQL/MariaDB** - Popular open-source database

### 📊 Kalkulasi Real-time (Logika Software)
- **Bonus Malam** 🌙
  - Otomatis menghitung bonus jam bermain untuk sesi di malam hari
  - Waktu malam: **21:00 - 06:00**
  - Formula: **1 jam bonus per 3 jam bermain di waktu malam**
  - Tidak tersimpan di database, dihitung on-the-fly

- **Sisa Waktu Bermain** ⏰
  - Menampilkan sisa waktu rental dalam jam (real-time)
  - Update otomatis setiap 30 detik
  - Indikator warna:
    - 🟢 Hijau: > 1 jam tersisa
    - 🟡 Kuning: < 1 jam tersisa (peringatan)
    - 🔴 Merah: Waktu habis (nilai negatif)

- **Status Rental** 📍
  - **Belum Mulai** (Biru): Rental akan dimulai
  - **Sedang Main** (Hijau): Rental aktif berlangsung
  - **Selesai** (Abu-abu): Rental sudah selesai

### 🎨 Modern UI/UX
- Desain modern dengan gradient buttons
- Hover effects dan smooth transitions
- Color-coded status indicators
- Responsive layout
- Dark-themed table headers

### 🔍 Filtering & Export
- Filter multi-kriteria (ID, Nama, Pembayaran, Game, Tanggal)
- Export ke CSV dengan metadata lengkap
- Include calculated columns dalam export

### 🔄 Auto-Refresh
- Update otomatis setiap 30 detik
- Manual refresh tersedia
- Real-time status tracking

---

## 📸 Screenshot

### Main Interface
```
[Database Connection] → [Filter Section] → [Data Table with Calculations]
```

### Calculated Columns Display
| Original Data | Bonus Malam | Sisa Waktu | Status |
|--------------|-------------|------------|---------|
| ... | 2.3 jam | 3.45 jam | Sedang Main |

---

## 💻 Persyaratan Sistem

### Minimum Requirements
- **OS**: Windows 10/11, Ubuntu 20.04+, macOS 10.15+
- **RAM**: 4 GB
- **Storage**: 100 MB free space
- **Display**: 1280x720

### Software Requirements
- **Qt Framework**: 6.2 or higher
- **C++ Compiler**: 
  - Windows: MSVC 2019+ atau MinGW-w64
  - Linux: GCC 9+ atau Clang 10+
  - macOS: Xcode 12+ (Apple Clang)
- **CMake**: 3.16 or higher
- **Database** (pilih salah satu):
  - SQLite3 (built-in dengan Qt)
  - PostgreSQL 12+ (optional)
  - MySQL 8.0+ / MariaDB 10.5+ (optional)

---

## 🚀 Instalasi

### 1. Clone Repository
```bash
git clone https://github.com/username/rental-playstation.git
cd rental-playstation
```

### 2. Install Qt 6
**Windows:**
```bash
# Download dari https://www.qt.io/download
# Pilih Qt 6.x dengan komponen:
# - Qt 6.x for MSVC/MinGW
# - Qt Creator
# - CMake
```

**Linux (Ubuntu/Debian):**
```bash
sudo apt update
sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential
sudo apt install libqt6sql6-sqlite libqt6sql6-psql libqt6sql6-mysql
```

**macOS:**
```bash
brew install qt@6 cmake
```

### 3. Build Project

#### Menggunakan CMake (Command Line)
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

#### Menggunakan Qt Creator
1. Buka Qt Creator
2. File → Open File or Project
3. Pilih `CMakeLists.txt`
4. Configure Project (pilih kit)
5. Build → Build All (Ctrl+B)
6. Run (Ctrl+R)

### 4. Setup Assets
Pastikan folder `assets/` berada di level yang sama dengan executable:
```
build/
├── bin/
│   ├── RentalManagementSystem (executable)
│   └── assets/
│       └── style.qss
```

---

## 🗄️ Konfigurasi Database

### SQLite (Recommended untuk Pemula)
1. Klik tombol **"🔌 Koneksi Database"**
2. Pilih tipe database: **SQLite**
3. Browse dan pilih file `.db` / `.sqlite`
4. Data akan dimuat otomatis

### PostgreSQL
1. Install PostgreSQL server
2. Buat database:
```sql
CREATE DATABASE rental_db;
```
3. Di aplikasi:
   - Pilih tipe: **PostgreSQL**
   - Host: `localhost`
   - Port: `5432`
   - Database: `rental_db`
   - Username: `postgres`
   - Password: `your_password`

### MySQL/MariaDB
1. Install MySQL/MariaDB server
2. Buat database:
```sql
CREATE DATABASE rental_db;
```
3. Di aplikasi:
   - Pilih tipe: **MySQL**
   - Host: `localhost`
   - Port: `3306`
   - Database: `rental_db`
   - Username: `root`
   - Password: `your_password`

---

## 📖 Cara Penggunaan

### 1. Koneksi Database
- Pilih tipe database dari dropdown
- Klik "🔌 Koneksi Database"
- Masukkan kredensial (jika PostgreSQL/MySQL)
- Status akan menunjukkan: ✅ Terhubung

### 2. View Data dengan Kalkulasi
Setelah koneksi berhasil, tabel akan menampilkan:
- **Kolom asli database** (Id, Nama, Jam Mulai, dll.)
- **Bonus Malam (Jam)** - Dihitung real-time
- **Sisa Waktu (Jam)** - Update setiap 30 detik
- **Status** - Belum Mulai / Sedang Main / Selesai

### 3. Filter Data
Isi field filter yang diinginkan:
- **ID**: Filter berdasarkan ID customer
- **Nama**: Filter berdasarkan nama customer
- **Pembayaran**: Filter metode pembayaran
- **Game**: Filter berdasarkan game/tipe
- **Tanggal**: Format YYYY-MM-DD

Klik **"🔍 Filter Data"** untuk apply filter.

### 4. Refresh Data
- **Auto-refresh**: Berjalan otomatis setiap 30 detik
- **Manual refresh**: Klik tombol **"🔄 Refresh"**

### 5. Export Data
1. Isi informasi operator dan tanggal
2. Klik **"📄 Ekspor ke CSV"**
3. Pilih lokasi dan nama file
4. File CSV akan berisi:
   - Header laporan
   - Semua kolom (termasuk kolom kalkulasi)
   - Metadata (operator, tanggal, waktu export)

---

## 🧮 Logika Kalkulasi

### 1. Bonus Malam (Night Bonus)

**Konsep:**
Customer yang bermain di malam hari (21:00 - 06:00) mendapat bonus waktu bermain.

**Formula:**
```
Bonus = (Jumlah Jam di Waktu Malam) / 3
```

**Contoh:**
```
Sewa: 2024-11-01 22:00 - 2024-11-02 04:00 (6 jam)
Jam malam: 22:00-23:59 (2 jam) + 00:00-04:00 (4 jam) = 6 jam
Bonus: 6 / 3 = 2 jam bonus
```

**Implementasi (C++):**
```cpp
double MainWindow::calculateNightBonus(const QDateTime &startTime, int durationHours) {
    QTime nightStart(21, 0);  // 21:00
    QTime nightEnd(6, 0);      // 06:00
    
    double nightHours = 0.0;
    QDateTime currentCheck = startTime;
    QDateTime endTime = startTime.addSecs(durationHours * 3600);
    
    // Hitung jam per jam
    while (currentCheck < endTime) {
        QTime checkTime = currentCheck.time();
        
        // Cek apakah di waktu malam
        if (checkTime >= nightStart || checkTime < nightEnd) {
            nightHours += 1.0;
        }
        
        currentCheck = currentCheck.addSecs(3600);
    }
    
    return nightHours / 3.0;
}
```

### 2. Sisa Waktu (Remaining Time)

**Konsep:**
Menghitung berapa lama lagi customer bisa bermain.

**Formula:**
```
Sisa Waktu = (Jam Selesai - Jam Sekarang) dalam jam
```

**Indikator:**
- Positif: Masih ada waktu
- Negatif: Sudah lewat waktu (overtime)

**Implementasi:**
```cpp
double MainWindow::calculateRemainingTime(const QDateTime &endTime) {
    QDateTime now = QDateTime::currentDateTime();
    qint64 secondsRemaining = now.secsTo(endTime);
    return secondsRemaining / 3600.0;  // Convert to hours
}
```

### 3. Status Rental

**Konsep:**
Menentukan status rental berdasarkan waktu saat ini.

**Logika:**
```
IF waktu_sekarang < jam_mulai THEN
    Status = "Belum Mulai"
ELSE IF jam_mulai <= waktu_sekarang <= jam_selesai THEN
    Status = "Sedang Main"
ELSE
    Status = "Selesai"
END IF
```

**Implementasi:**
```cpp
QString MainWindow::getStatusString(const QDateTime &startTime, const QDateTime &endTime) {
    QDateTime now = QDateTime::currentDateTime();
    
    if (now < startTime) {
        return "Belum Mulai";
    } else if (now >= startTime && now <= endTime) {
        return "Sedang Main";
    } else {
        return "Selesai";
    }
}
```

### Update Real-time (Auto-refresh)

Timer dijalankan setiap 30 detik untuk update:
- Sisa Waktu
- Status

Bonus Malam tidak perlu update karena nilainya tetap (dihitung dari data historis).

---

## 🗃️ Struktur Database

### Tabel: `Sistem_rental` (atau `rental_data`)

**Kolom Minimal yang Dibutuhkan:**

| Kolom | Tipe | Deskripsi | Contoh |
|-------|------|-----------|---------|
| `Id_Rental` | INTEGER/VARCHAR | Primary key | 1 |
| `Id_Customer` | INTEGER/VARCHAR | Foreign key | C001 |
| `Nama_Customer` | VARCHAR | Nama customer | John Doe |
| `Id_PlayStation` | INTEGER/VARCHAR | Foreign key | PS001 |
| `Game` | VARCHAR | Game yang dimainkan | FIFA 24 |
| `Jam_Mulai` | DATETIME | Waktu mulai rental | 2024-11-01 22:00:00 |
| `Jam_Selesai` | DATETIME | Waktu selesai rental | 2024-11-02 04:00:00 |
| `Total_Jam` | INTEGER | Durasi rental (jam) | 6 |
| `Metode_Pembayaran` | VARCHAR | Cash/Transfer/E-wallet | Cash |

**Catatan Penting:**
- Nama kolom case-insensitive (aplikasi akan mencari variasi)
- Format datetime yang didukung:
  - `yyyy-MM-dd HH:mm:ss` (recommended)
  - `yyyy-MM-dd HH:mm`
  - ISO 8601 format

**Contoh Create Table (SQLite):**
```sql
CREATE TABLE Sistem_rental (
    Id_Rental INTEGER PRIMARY KEY AUTOINCREMENT,
    Id_Customer VARCHAR(10),
    Nama_Customer VARCHAR(100),
    Id_PlayStation VARCHAR(10),
    Game VARCHAR(100),
    Jam_Mulai DATETIME,
    Jam_Selesai DATETIME,
    Total_Jam INTEGER,
    Metode_Pembayaran VARCHAR(20)
);
```

**Contoh Insert Data:**
```sql
INSERT INTO Sistem_rental VALUES (
    1,
    'C001',
    'John Doe',
    'PS001',
    'FIFA 24',
    '2024-11-01 22:00:00',
    '2024-11-02 04:00:00',
    6,
    'Cash'
);
```

---

## 📁 Struktur Project

```
rental-playstation/
│
├── assets/
│   └── style.qss              # Modern stylesheet
│
├── include/
│   ├── MainWindow.h           # Main window header
│   └── DatabaseManager.h      # Database manager header
│
├── src/
│   ├── main.cpp               # Application entry point
│   ├── MainWindow.cpp         # Main window implementation
│   └── DatabaseManager.cpp    # Database operations
│
├── CMakeLists.txt             # CMake build configuration
├── README.md                  # Documentation (this file)
├── LICENSE                    # License file
└── .gitignore                 # Git ignore rules
```

### File Descriptions

#### `main.cpp`
- Entry point aplikasi
- Load stylesheet
- Initialize main window

#### `MainWindow.h/cpp`
- UI setup dan layout
- Implementasi logika kalkulasi
- Event handlers (connect, filter, export)
- Real-time update timer

#### `DatabaseManager.h/cpp`
- Abstraksi koneksi database
- Support multi-database (SQLite, PostgreSQL, MySQL)
- Query management

#### `style.qss`
- Modern CSS-like styling
- Color schemes
- Button gradients
- Table styling

---

## 🔧 Troubleshooting

### Database Connection Issues

**Problem:** "Could not find table rental"
```
Solution:
- Pastikan tabel bernama: Sistem_rental, rental_data, atau rental
- Check case-sensitivity (Linux/macOS)
```

**Problem:** "Cannot open database"
```
Solution:
- Check file path SQLite
- Verify database file permissions
- Ensure Qt SQL drivers installed
```

**Problem:** PostgreSQL/MySQL connection failed
```
Solution:
- Verify server is running: systemctl status postgresql
- Check credentials and port
- Firewall rules: sudo ufw allow 5432
```

### Calculation Issues

**Problem:** Bonus Malam shows 0.0 untuk semua data
```
Solution:
- Check format Jam_Mulai: harus datetime valid
- Verify Total_Jam > 0
- Enable debug output: lihat qDebug() di console
```

**Problem:** Sisa Waktu tidak update
```
Solution:
- Check timer running: updateTimer->isActive()
- Verify Jam_Selesai format correct
- Check system time is synchronized
```

### Build Issues

**Problem:** CMake cannot find Qt6
```bash
# Linux
export CMAKE_PREFIX_PATH=/path/to/Qt/6.x/gcc_64

# Windows (PowerShell)
$env:CMAKE_PREFIX_PATH="C:\Qt\6.x\msvc2019_64"

# macOS
export CMAKE_PREFIX_PATH=/usr/local/opt/qt@6
```

**Problem:** Missing SQL drivers
```bash
# Ubuntu/Debian
sudo apt install libqt6sql6-sqlite libqt6sql6-psql libqt6sql6-mysql

# Check available drivers
qsql6 -plugins
```

### Stylesheet Not Loading

**Problem:** "Warning: Could not load stylesheet"
```
Solution:
1. Check folder structure: executable/assets/style.qss
2. Copy assets folder ke build directory
3. Verify file permissions: chmod +r assets/style.qss
```

---

## 🤝 Kontribusi

Kontribusi sangat diterima! Berikut cara berkontribusi:

### 1. Fork Repository
```bash
git clone https://github.com/yourusername/rental-playstation.git
cd rental-playstation
git checkout -b feature/fitur-baru
```

### 2. Development Guidelines
- Follow Qt C++ coding standards
- Add comments untuk logika kompleks
- Test dengan berbagai database types
- Update documentation

### 3. Commit Changes
```bash
git add .
git commit -m "Add: fitur kalkulasi diskon member"
git push origin feature/fitur-baru
```

### 4. Create Pull Request
- Describe changes clearly
- Include screenshots (jika UI changes)
- Reference related issues

### Ideas for Contribution
- 🎯 Fitur diskon member
- 📊 Dashboard dengan statistik
- 📧 Email notification untuk reminder
- 🖨️ Print receipt
- 📱 Responsive design untuk tablet
- 🌐 Multi-language support
- 🔐 User authentication
- 📈 Revenue analytics

---

## 📄 Lisensi

MIT License

Copyright (c) 2024 [Your Name]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

## 📞 Kontak & Support

- **GitHub Issues**: [Report Bug](https://github.com/username/rental-playstation/issues)
- **Email**: your.email@example.com
- **Documentation**: [Wiki](https://github.com/username/rental-playstation/wiki)

---

## 🙏 Acknowledgments

- Qt Framework team
- Contributors and testers
- Icon resources from [source]

---

**Made with ❤️ using Qt6 and C++**
