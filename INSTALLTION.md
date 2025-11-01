# 📦 Panduan Instalasi Lengkap

Panduan step-by-step instalasi Sistem Manajemen Rental PlayStation untuk berbagai platform.

## Daftar Isi
- [Windows Installation](#windows-installation)
- [Linux Installation](#linux-installation)
- [macOS Installation](#macos-installation)
- [Database Setup](#database-setup)
- [Verification](#verification)

---

## Windows Installation

### Prerequisites

1. **Install Visual Studio 2019/2022** (Community Edition)
   - Download: https://visualstudio.microsoft.com/downloads/
   - Pilih workload: "Desktop development with C++"
   - Atau install MinGW-w64 sebagai alternatif

2. **Install Qt 6**
   ```
   Download Qt Online Installer:
   https://www.qt.io/download-qt-installer

   Komponen yang dipilih:
   ✅ Qt 6.5.x (atau versi terbaru)
      ✅ MSVC 2019 64-bit (jika pakai Visual Studio)
      ✅ MinGW 11.2.0 64-bit (jika pakai MinGW)
      ✅ Qt 5 Compatibility Module
   ✅ Developer and Designer Tools
      ✅ CMake
      ✅ Ninja
   ```

3. **Install CMake** (jika belum terinstall)
   ```
   Download dari: https://cmake.org/download/
   Pilih: Windows x64 Installer
   ✅ Add CMake to system PATH
   ```

### Build Steps

1. **Clone Repository**
   ```cmd
   git clone https://github.com/username/rental-playstation.git
   cd rental-playstation
   ```

2. **Setup Environment Variables**
   ```cmd
   # Set Qt path (sesuaikan dengan instalasi Anda)
   set Qt6_DIR=C:\Qt\6.5.3\msvc2019_64
   set PATH=%Qt6_DIR%\bin;%PATH%
   ```

3. **Build dengan CMake**
   ```cmd
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022" -A x64
   cmake --build . --config Release
   ```

   Atau dengan MinGW:
   ```cmd
   mkdir build
   cd build
   cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
   cmake --build .
   ```

4. **Run Application**
   ```cmd
   cd bin
   RentalManagementSystem.exe
   ```

### Troubleshooting Windows

**Problem: "Qt6 not found"**
```cmd
# Set CMAKE_PREFIX_PATH
cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.5.3/msvc2019_64"
```

**Problem: "VCRUNTIME140.dll missing"**
```
Install Visual C++ Redistributable:
https://aka.ms/vs/17/release/vc_redist.x64.exe
```

**Problem: "Cannot find Qt DLLs"**
```cmd
# Copy Qt DLLs ke folder executable
windeployqt.exe bin\RentalManagementSystem.exe
```

---

## Linux Installation

### Ubuntu/Debian

1. **Install Dependencies**
   ```bash
   sudo apt update
   sudo apt install -y \
       build-essential \
       cmake \
       git \
       qt6-base-dev \
       qt6-tools-dev \
       qt6-tools-dev-tools \
       libqt6sql6 \
       libqt6sql6-sqlite \
       libqt6sql6-psql \
       libqt6sql6-mysql
   ```

2. **Clone Repository**
   ```bash
   git clone https://github.com/username/rental-playstation.git
   cd rental-playstation
   ```

3. **Build**
   ```bash
   mkdir build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   make -j$(nproc)
   ```

4. **Install (Optional)**
   ```bash
   sudo make install
   ```

5. **Run**
   ```bash
   ./bin/RentalManagementSystem
   ```

### Fedora/RHEL/CentOS

1. **Install Dependencies**
   ```bash
   sudo dnf install -y \
       gcc-c++ \
       cmake \
       git \
       qt6-qtbase-devel \
       qt6-qttools-devel \
       qt6-qtbase-mysql \
       qt6-qtbase-postgresql
   ```

2. **Build Steps** (sama seperti Ubuntu)

### Arch Linux

1. **Install Dependencies**
   ```bash
   sudo pacman -S --needed \
       base-devel \
       cmake \
       git \
       qt6-base \
       qt6-tools \
       qt6-svg
   ```

2. **Build Steps** (sama seperti Ubuntu)

### Troubleshooting Linux

**Problem: "Could not find Qt6"**
```bash
# Find Qt6 installation
dpkg -L qt6-base-dev | grep Qt6Config.cmake

# Set CMAKE_PREFIX_PATH
export CMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt6
cmake .. -DCMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH
```

**Problem: "libQt6Core.so.6: cannot open shared object file"**
```bash
# Update library cache
sudo ldconfig

# Check Qt libraries
ldd bin/RentalManagementSystem
```

**Problem: Permission denied**
```bash
# Make executable
chmod +x bin/RentalManagementSystem

# Or run with sudo if needed
sudo ./bin/RentalManagementSystem
```

---

## macOS Installation

### Prerequisites

1. **Install Homebrew**
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

2. **Install Xcode Command Line Tools**
   ```bash
   xcode-select --install
   ```

### Installation Steps

1. **Install Qt6 and CMake**
   ```bash
   brew install qt@6 cmake
   ```

2. **Setup Environment**
   ```bash
   # Add to ~/.zshrc or ~/.bash_profile
   export PATH="/usr/local/opt/qt@6/bin:$PATH"
   export LDFLAGS="-L/usr/local/opt/qt@6/lib"
   export CPPFLAGS="-I/usr/local/opt/qt@6/include"
   export CMAKE_PREFIX_PATH="/usr/local/opt/qt@6"
   
   # Reload shell
   source ~/.zshrc
   ```

3. **Clone and Build**
   ```bash
   git clone https://github.com/username/rental-playstation.git
   cd rental-playstation
   mkdir build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   make -j$(sysctl -n hw.ncpu)
   ```

4. **Run**
   ```bash
   open bin/RentalManagementSystem.app
   # atau
   ./bin/RentalManagementSystem
   ```

### Troubleshooting macOS

**Problem: "Qt6 not found"**
```bash
# Check Qt installation
brew list qt@6

# Set CMAKE_PREFIX_PATH explicitly
cmake .. -DCMAKE_PREFIX_PATH="$(brew --prefix qt@6)"
```

**Problem: "dyld: Library not loaded"**
```bash
# Fix library paths
install_name_tool -add_rpath "@executable_path/../Frameworks" bin/RentalManagementSystem

# Or use macdeployqt
macdeployqt bin/RentalManagementSystem.app
```

---

## Database Setup

### SQLite (No Setup Required)

SQLite tidak memerlukan server. Cukup buat file database:

```bash
# Create sample database
sqlite3 rental.db

# Create table
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

# Insert sample data
INSERT INTO Sistem_rental VALUES (
    1, 'C001', 'John Doe', 'PS001', 'FIFA 24',
    '2024-11-01 22:00:00', '2024-11-02 04:00:00', 6, 'Cash'
);

.quit
```

### PostgreSQL Setup

1. **Install PostgreSQL**
   ```bash
   # Ubuntu/Debian
   sudo apt install postgresql postgresql-contrib
   
   # macOS
   brew install postgresql
   brew services start postgresql
   
   # Windows
   # Download dari https://www.postgresql.org/download/windows/
   ```

2. **Create Database**
   ```bash
   # Login as postgres user
   sudo -u postgres psql
   
   # Or on Windows
   psql -U postgres
   ```

   ```sql
   -- Create database
   CREATE DATABASE rental_db;
   
   -- Create user (optional)
   CREATE USER rental_user WITH PASSWORD 'password123';
   
   -- Grant privileges
   GRANT ALL PRIVILEGES ON DATABASE rental_db TO rental_user;
   
   -- Connect to database
   \c rental_db
   
   -- Create table
   CREATE TABLE sistem_rental (
       id_rental SERIAL PRIMARY KEY,
       id_customer VARCHAR(10),
       nama_customer VARCHAR(100),
       id_playstation VARCHAR(10),
       game VARCHAR(100),
       jam_mulai TIMESTAMP,
       jam_selesai TIMESTAMP,
       total_jam INTEGER,
       metode_pembayaran VARCHAR(20)
   );
   
   -- Insert sample data
   INSERT INTO sistem_rental VALUES (
       DEFAULT, 'C001', 'John Doe', 'PS001', 'FIFA 24',
       '2024-11-01 22:00:00', '2024-11-02 04:00:00', 6, 'Cash'
   );
   
   \q
   ```

3. **Configure Connection in App**
   - Host: `localhost`
   - Port: `5432`
   - Database: `rental_db`
   - Username: `rental_user`
   - Password: `password123`

### MySQL/MariaDB Setup

1. **Install MySQL**
   ```bash
   # Ubuntu/Debian
   sudo apt install mysql-server
   
   # macOS
   brew install mysql
   brew services start mysql
   
   # Windows
   # Download dari https://dev.mysql.com/downloads/installer/
   ```

2. **Secure Installation**
   ```bash
   sudo mysql_secure_installation
   ```

3. **Create Database**
   ```bash
   mysql -u root -p
   ```

   ```sql
   -- Create database
   CREATE DATABASE rental_db;
   
   -- Create user
   CREATE USER 'rental_user'@'localhost' IDENTIFIED BY 'password123';
   
   -- Grant privileges
   GRANT ALL PRIVILEGES ON rental_db.* TO 'rental_user'@'localhost';
   FLUSH PRIVILEGES;
   
   -- Use database
   USE rental_db;
   
   -- Create table
   CREATE TABLE Sistem_rental (
       Id_Rental INT AUTO_INCREMENT PRIMARY KEY,
       Id_Customer VARCHAR(10),
       Nama_Customer VARCHAR(100),
       Id_PlayStation VARCHAR(10),
       Game VARCHAR(100),
       Jam_Mulai DATETIME,
       Jam_Selesai DATETIME,
       Total_Jam INT,
       Metode_Pembayaran VARCHAR(20)
   );
   
   -- Insert sample data
   INSERT INTO Sistem_rental VALUES (
       NULL, 'C001', 'John Doe', 'PS001', 'FIFA 24',
       '2024-11-01 22:00:00', '2024-11-02 04:00:00', 6, 'Cash'
   );
   
   EXIT;
   ```

4. **Configure Connection in App**
   - Host: `localhost`
   - Port: `3306`
   - Database: `rental_db`
   - Username: `rental_user`
   - Password: `password123`

---

## Verification

### Check Installation

```bash
# Check Qt version
qmake --version
# atau
qmake6 --version

# Check CMake
cmake --version

# Check compiler
g++ --version    # Linux/macOS
cl               # Windows (MSVC)
```

### Test Application

1. **Run Application**
   ```bash
   ./bin/RentalManagementSystem
   ```

2. **Connect Database**
   - Pilih SQLite
   - Browse sample database
   - Klik "Koneksi Database"

3. **Verify Calculations**
   - Check "Bonus Malam" column (harus > 0 untuk rental di malam hari)
   - Check "Sisa Waktu" column (harus update setiap 30 detik)
   - Check "Status" column (warna sesuai status)

4. **Test Export**
   - Isi operator dan tanggal
   - Klik "Ekspor ke CSV"
   - Buka file CSV, pastikan semua kolom ada

### Check Qt SQL Drivers

```bash
# List available SQL drivers
# Compile dan run program ini:
```

```cpp
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    
    qDebug() << "Available SQL drivers:";
    QStringList drivers = QSqlDatabase::drivers();
    for (const QString &driver : drivers) {
        qDebug() << "  -" << driver;
    }
    
    return 0;
}
```

Expected output:
```
Available SQL drivers:
  - QSQLITE
  - QPSQL
  - QMYSQL
```

---

## Getting Help

Jika mengalami masalah:

1. **Check logs**
   ```bash
   # Run dengan verbose output
   ./RentalManagementSystem --verbose
   ```

2. **Enable Qt debug**
   ```bash
   export QT_DEBUG_PLUGINS=1
   ./RentalManagementSystem
   ```

3. **Report issue**
   - GitHub Issues: https://github.com/username/rental-playstation/issues
   - Include: OS, Qt version, error message, steps to reproduce

---

**Installation complete! 🎉**

Proceed to [README.md](README.md) for usage guide.
