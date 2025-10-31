# Sistem Manajemen Rental PlayStation

## 🔧 Perbaikan yang Dilakukan

### 1. **Syntax Errors**
- ✅ Fixed typo: `#inlcude` → `#include`
- ✅ Removed duplicate variable declarations (`tableWidget` vs `tableView`)
- ✅ Fixed inconsistent variable names (`tanggalEdit` → `dateEdit`)

### 2. **Security Improvements**
- ✅ Implemented prepared statements to prevent SQL injection
- ✅ Proper input sanitization for CSV export

### 3. **Memory Management**
- ✅ Added proper destructor to clean up resources
- ✅ Fixed potential memory leaks in model handling

### 4. **New Features**
- ✅ Multi-database support (SQLite, PostgreSQL, MySQL)
- ✅ Connection dialog untuk database server
- ✅ Better error handling dan user feedback
- ✅ CSV export dengan proper escaping

---

## 📦 Prerequisites

### Windows
```bash
# Install Qt6
# Download dari: https://www.qt.io/download-qt-installer

# Install CMake
# Download dari: https://cmake.org/download/

# Install compiler (MSVC atau MinGW)
```

### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    qt6-sql-sqlite \
    libqt6sql6-psql \
    libqt6sql6-mysql
```

### macOS
```bash
brew install qt@6 cmake
export PATH="/opt/homebrew/opt/qt@6/bin:$PATH"
```

---

## 🚀 Build Instructions

### 1. Clone/Extract Project
```bash
cd /path/to/your/project
```

### 2. Create Build Directory
```bash
mkdir build
cd build
```

### 3. Configure with CMake
```bash
# Linux/macOS
cmake ..

# Windows (dengan Visual Studio)
cmake .. -G "Visual Studio 17 2022" -A x64

# Windows (dengan MinGW)
cmake .. -G "MinGW Makefiles"
```

### 4. Build
```bash
# Linux/macOS
cmake --build .

# Windows
cmake --build . --config Release
```

### 5. Run
```bash
# Linux/macOS
./bin/RentalManagementSystem

# Windows
.\bin\Release\RentalManagementSystem.exe
```

---

## 🗄️ Database Setup

### SQLite (Default)
Tidak perlu setup khusus. Cukup pilih file `.db` atau `.sqlite` saat runtime.

### PostgreSQL
1. Install PostgreSQL
```bash
# Ubuntu/Debian
sudo apt install postgresql postgresql-contrib

# Start service
sudo systemctl start postgresql
```

2. Create database dan user
```sql
CREATE DATABASE rental_db;
CREATE USER rental_user WITH PASSWORD 'password123';
GRANT ALL PRIVILEGES ON DATABASE rental_db TO rental_user;
```

3. Di aplikasi:
   - Pilih "PostgreSQL" dari dropdown
   - Klik "Koneksi Database"
   - Masukkan credentials

### MySQL
1. Install MySQL
```bash
# Ubuntu/Debian
sudo apt install mysql-server

# Start service
sudo systemctl start mysql
```

2. Create database dan user
```sql
CREATE DATABASE rental_db;
CREATE USER 'rental_user'@'localhost' IDENTIFIED BY 'password123';
GRANT ALL PRIVILEGES ON rental_db.* TO 'rental_user'@'localhost';
FLUSH PRIVILEGES;
```

3. Di aplikasi: sama seperti PostgreSQL

---

## 📊 Database Schema

Aplikasi mengharapkan struktur tabel seperti berikut:

```sql
-- Tabel Customer
CREATE TABLE Customer (
    Id_Customer VARCHAR(50) PRIMARY KEY,
    Nama_Customer VARCHAR(100),
    Nomor_Telepon VARCHAR(20)
);

-- Tabel PlayStation
CREATE TABLE PlayStation (
    Id_PlayStation VARCHAR(50) PRIMARY KEY,
    Game VARCHAR(100),
    Status VARCHAR(20)
);

-- Tabel Operator
CREATE TABLE Operator (
    Id_Operator VARCHAR(50) PRIMARY KEY,
    Nama_Operator VARCHAR(100),
    Metode_Pembayaran VARCHAR(50)
);

-- Tabel Sistem_rental (Main)
CREATE TABLE Sistem_rental (
    Id_Rental VARCHAR(50) PRIMARY KEY,
    Id_Customer VARCHAR(50),
    Id_PlayStation VARCHAR(50),
    Id_Operator VARCHAR(50),
    Jam_Mulai DATETIME,
    Jam_Selesai DATETIME,
    Total_Biaya DECIMAL(10,2),
    FOREIGN KEY (Id_Customer) REFERENCES Customer(Id_Customer),
    FOREIGN KEY (Id_PlayStation) REFERENCES PlayStation(Id_PlayStation),
    FOREIGN KEY (Id_Operator) REFERENCES Operator(Id_Operator)
);
```

---

## 🎯 Cara Penggunaan

### 1. Koneksi Database
- Pilih tipe database (SQLite/PostgreSQL/MySQL)
- Klik "Koneksi Database"
- Untuk SQLite: pilih file database
- Untuk PostgreSQL/MySQL: masukkan credentials

### 2. Filter Data
- Isi field filter yang diinginkan (bisa multiple)
- Klik tombol "🔍 Filter Data"
- Data akan ditampilkan sesuai kriteria

### 3. Export Laporan
- Isi nama operator dan tanggal
- Klik "📄 Ekspor ke CSV"
- Pilih lokasi penyimpanan
- File CSV akan berisi header laporan + data tabel

---

## ⚠️ Troubleshooting

### Error: "Qt6 not found"
```bash
# Set Qt6 path
export CMAKE_PREFIX_PATH="/path/to/Qt/6.x.x/gcc_64"
```

### Error: "Cannot open database"
- Pastikan file database readable
- Check permissions folder
- Untuk server DB: pastikan service running

### Error: "SQL driver not loaded"
```bash
# Check available drivers
qmake -query QT_INSTALL_PLUGINS

# Install missing drivers (Linux)
sudo apt install libqt6sql6-sqlite libqt6sql6-psql libqt6sql6-mysql
```

### Aplikasi tidak bisa dibuka
```bash
# Check dependencies
ldd ./RentalManagementSystem  # Linux
otool -L ./RentalManagementSystem  # macOS
```

---

## 📝 File Structure

```
project/
├── CMakeLists.txt          # Build configuration
├── main.cpp                # Entry point
├── MainWindow.h            # UI header
├── MainWindow.cpp          # UI implementation
├── DatabaseManager.h       # DB manager header
├── DatabaseManager.cpp     # DB manager implementation
├── assets/
│   └── style.qss          # Optional stylesheet
└── build/                 # Build output (generated)
```

---

## 🔄 Update/Maintenance

### Rebuild setelah perubahan code
```bash
cd build
cmake --build . --clean-first
```

### Update dependencies
```bash
# Update Qt6
# Download installer terbaru dari qt.io

# Update CMake
sudo apt install cmake  # Linux
brew upgrade cmake      # macOS
```

---

## 📞 Support

Jika ada error atau pertanyaan:
1. Check log messages di console
2. Verify database schema sesuai dokumentasi
3. Pastikan semua dependencies terinstall
4. Check Qt6 documentation: https://doc.qt.io/qt-6/

---

## 📄 License

Project ini dibuat untuk keperluan tugas kuliah.

---

**Good luck dengan tugas kuliahmu! 🎓**
