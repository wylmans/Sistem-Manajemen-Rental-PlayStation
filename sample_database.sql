-- ============================================
-- Sample Database for Rental PlayStation
-- ============================================
-- This file contains sample data structure
-- and test data including night rentals
-- ============================================

-- Drop table if exists (untuk clean setup)
DROP TABLE IF EXISTS Sistem_rental;
DROP TABLE IF EXISTS Customer;
DROP TABLE IF EXISTS PlayStation;
DROP TABLE IF EXISTS Operator;

-- ============================================
-- Table: Customer
-- ============================================
CREATE TABLE IF NOT EXISTS Customer (
    Id_Customer VARCHAR(10) PRIMARY KEY,
    Nama_Customer VARCHAR(100) NOT NULL,
    Uang DECIMAL(10,2),
    Jenis_Member VARCHAR(20)
);

-- Insert sample customers
INSERT INTO Customer VALUES
('C001', 'John Doe', 500000, 'VIP'),
('C002', 'Jane Smith', 300000, 'Regular'),
('C003', 'Bob Wilson', 200000, 'VIP'),
('C004', 'Alice Brown', 150000, 'Regular'),
('C005', 'Charlie Davis', 400000, 'VIP'),
('C006', 'Emma Johnson', 250000, 'Regular'),
('C007', 'Frank Miller', 180000, 'Regular'),
('C008', 'Grace Lee', 350000, 'VIP');

-- ============================================
-- Table: PlayStation
-- ============================================
CREATE TABLE IF NOT EXISTS PlayStation (
    Id_PlayStation VARCHAR(10) PRIMARY KEY,
    Kontroller VARCHAR(50),
    TV VARCHAR(50),
    Game VARCHAR(100),
    Harga_Per_Jam DECIMAL(10,2),
    Lokasi_Unit VARCHAR(20)
);

-- Insert sample PlayStation units
INSERT INTO PlayStation VALUES
('PS001', 'DualShock 4', 'Samsung 43"', 'FIFA 24', 15000, 'Ruang A'),
('PS002', 'DualShock 4', 'LG 50"', 'Call of Duty MW3', 20000, 'Ruang B'),
('PS003', 'DualShock 4', 'Sony 55"', 'God of War', 18000, 'Ruang C'),
('PS004', 'DualShock 4', 'Samsung 43"', 'Spider-Man 2', 18000, 'Ruang D'),
('PS005', 'DualSense', 'LG 65"', 'Hogwarts Legacy', 25000, 'VIP 1'),
('PS006', 'DualSense', 'Sony 65"', 'The Last of Us', 25000, 'VIP 2'),
('PS007', 'DualShock 4', 'Samsung 50"', 'Mortal Kombat 11', 16000, 'Ruang E'),
('PS008', 'DualSense', 'LG 55"', 'Gran Turismo 7', 22000, 'Ruang F');

-- ============================================
-- Table: Operator
-- ============================================
CREATE TABLE IF NOT EXISTS Operator (
    Id_Operator VARCHAR(10) PRIMARY KEY,
    Nama_Operator VARCHAR(100) NOT NULL,
    Shift VARCHAR(20),
    Metode_Pembayaran VARCHAR(20),
    Uang DECIMAL(10,2)
);

-- Insert sample operators
INSERT INTO Operator VALUES
('OP001', 'Ahmad Hidayat', 'Pagi', 'Cash', 5000000),
('OP002', 'Siti Nurhaliza', 'Siang', 'Transfer', 4500000),
('OP003', 'Budi Santoso', 'Malam', 'E-Wallet', 4800000),
('OP004', 'Dewi Lestari', 'Pagi', 'Cash', 4200000);

-- ============================================
-- Table: Sistem_rental (Main Transaction Table)
-- ============================================
CREATE TABLE IF NOT EXISTS Sistem_rental (
    Id_Rental INTEGER PRIMARY KEY AUTOINCREMENT,
    Id_Customer VARCHAR(10),
    Id_PlayStation VARCHAR(10),
    Id_Operator VARCHAR(10),
    Jam_Mulai DATETIME NOT NULL,
    Jam_Selesai DATETIME NOT NULL,
    Total_Jam INTEGER NOT NULL,
    Total_Bayar DECIMAL(10,2),
    Metode_Pembayaran VARCHAR(20),
    Status_Pembayaran VARCHAR(20),
    Catatan TEXT,
    FOREIGN KEY (Id_Customer) REFERENCES Customer(Id_Customer),
    FOREIGN KEY (Id_PlayStation) REFERENCES PlayStation(Id_PlayStation),
    FOREIGN KEY (Id_Operator) REFERENCES Operator(Id_Operator)
);

-- ============================================
-- Insert Sample Data
-- ============================================

-- Sample 1: Night rental (22:00 - 04:00) = 6 jam di malam
-- Bonus: 6 jam malam / 3 = 2 jam bonus
INSERT INTO Sistem_rental VALUES (
    1,
    'C001',
    'PS001',
    'OP003',
    '2024-11-01 22:00:00',
    '2024-11-02 04:00:00',
    6,
    90000,
    'Cash',
    'Lunas',
    'Main malam, dapat bonus 2 jam'
);

-- Sample 2: Partial night rental (20:00 - 02:00) = 5 jam (4 jam malam)
-- Bonus: 4 jam malam / 3 = 1.33 jam bonus
INSERT INTO Sistem_rental VALUES (
    2,
    'C002',
    'PS002',
    'OP003',
    '2024-11-01 20:00:00',
    '2024-11-02 02:00:00',
    6,
    120000,
    'Transfer',
    'Lunas',
    'Sebagian waktu di jam malam'
);

-- Sample 3: Day rental (10:00 - 15:00) = 5 jam siang
-- Bonus: 0 jam (tidak ada jam malam)
INSERT INTO Sistem_rental VALUES (
    3,
    'C003',
    'PS003',
    'OP001',
    '2024-11-01 10:00:00',
    '2024-11-01 15:00:00',
    5,
    90000,
    'E-Wallet',
    'Lunas',
    'Main siang, tidak dapat bonus'
);

-- Sample 4: Cross-midnight rental (23:00 - 05:00) = 6 jam semua malam
-- Bonus: 6 jam malam / 3 = 2 jam bonus
INSERT INTO Sistem_rental VALUES (
    4,
    'C004',
    'PS004',
    'OP003',
    '2024-11-01 23:00:00',
    '2024-11-02 05:00:00',
    6,
    108000,
    'Cash',
    'Lunas',
    'Full night session'
);

-- Sample 5: Evening to night (19:00 - 01:00) = 6 jam (5 jam malam)
-- Bonus: 5 jam malam / 3 = 1.67 jam bonus
INSERT INTO Sistem_rental VALUES (
    5,
    'C005',
    'PS005',
    'OP003',
    '2024-11-02 19:00:00',
    '2024-11-03 01:00:00',
    6,
    150000,
    'Transfer',
    'Lunas',
    'VIP room, dapat bonus malam'
);

-- Sample 6: Current active rental (untuk test "Sedang Main")
-- Mulai 2 jam yang lalu, selesai 3 jam ke depan
INSERT INTO Sistem_rental VALUES (
    6,
    'C006',
    'PS006',
    'OP002',
    datetime('now', '-2 hours'),
    datetime('now', '+3 hours'),
    5,
    125000,
    'Cash',
    'Belum Lunas',
    'Sedang berlangsung'
);

-- Sample 7: Future rental (untuk test "Belum Mulai")
-- Mulai 2 jam ke depan
INSERT INTO Sistem_rental VALUES (
    7,
    'C007',
    'PS007',
    'OP002',
    datetime('now', '+2 hours'),
    datetime('now', '+6 hours'),
    4,
    64000,
    'E-Wallet',
    'DP',
    'Booking untuk nanti'
);

-- Sample 8: Finished rental (untuk test "Selesai")
-- Sudah selesai 1 jam yang lalu
INSERT INTO Sistem_rental VALUES (
    8,
    'C008',
    'PS008',
    'OP001',
    datetime('now', '-5 hours'),
    datetime('now', '-1 hour'),
    4,
    88000,
    'Cash',
    'Lunas',
    'Sudah selesai'
);

-- Sample 9: Long night session (21:00 - 09:00) = 12 jam (9 jam malam)
-- Bonus: 9 jam malam / 3 = 3 jam bonus
INSERT INTO Sistem_rental VALUES (
    9,
    'C001',
    'PS001',
    'OP003',
    '2024-11-03 21:00:00',
    '2024-11-04 09:00:00',
    12,
    180000,
    'Cash',
    'Lunas',
    'Marathon night session'
);

-- Sample 10: Short day rental (14:00 - 16:00) = 2 jam siang
-- Bonus: 0 jam
INSERT INTO Sistem_rental VALUES (
    10,
    'C002',
    'PS002',
    'OP002',
    '2024-11-03 14:00:00',
    '2024-11-03 16:00:00',
    2,
    40000,
    'Transfer',
    'Lunas',
    'Rental singkat'
);

-- Sample 11: Early morning (04:00 - 08:00) = 4 jam (2 jam malam)
-- Bonus: 2 jam malam / 3 = 0.67 jam bonus
INSERT INTO Sistem_rental VALUES (
    11,
    'C003',
    'PS003',
    'OP001',
    '2024-11-04 04:00:00',
    '2024-11-04 08:00:00',
    4,
    72000,
    'Cash',
    'Lunas',
    'Pagi-pagi, masih dapat bonus'
);

-- Sample 12: Overtime rental (planned 3 hours, but still playing)
-- Started 4 hours ago, should have ended 1 hour ago
INSERT INTO Sistem_rental VALUES (
    12,
    'C004',
    'PS004',
    'OP002',
    datetime('now', '-4 hours'),
    datetime('now', '-1 hour'),
    3,
    54000,
    'Cash',
    'Belum Lunas',
    'Overtime - sisa waktu negatif'
);

-- Sample 13: Multi-day rental with nights
-- 2 days rental crossing multiple nights
INSERT INTO Sistem_rental VALUES (
    13,
    'C005',
    'PS005',
    'OP001',
    '2024-11-05 20:00:00',
    '2024-11-07 08:00:00',
    36,
    900000,
    'Transfer',
    'Lunas',
    'Rental 2 hari, banyak bonus malam'
);

-- Sample 14: Peak hour rental (18:00 - 22:00) = 4 jam (1 jam malam)
-- Bonus: 1 jam malam / 3 = 0.33 jam bonus
INSERT INTO Sistem_rental VALUES (
    14,
    'C006',
    'PS006',
    'OP002',
    '2024-11-05 18:00:00',
    '2024-11-05 22:00:00',
    4,
    100000,
    'E-Wallet',
    'Lunas',
    'Prime time'
);

-- Sample 15: Normal afternoon (13:00 - 17:00) = 4 jam siang
-- Bonus: 0 jam
INSERT INTO Sistem_rental VALUES (
    15,
    'C007',
    'PS007',
    'OP002',
    '2024-11-05 13:00:00',
    '2024-11-05 17:00:00',
    4,
    64000,
    'Cash',
    'Lunas',
    'Rental siang biasa'
);

-- ============================================
-- Create Indexes for Performance
-- ============================================
CREATE INDEX IF NOT EXISTS idx_jam_mulai ON Sistem_rental(Jam_Mulai);
CREATE INDEX IF NOT EXISTS idx_jam_selesai ON Sistem_rental(Jam_Selesai);
CREATE INDEX IF NOT EXISTS idx_customer ON Sistem_rental(Id_Customer);
CREATE INDEX IF NOT EXISTS idx_playstation ON Sistem_rental(Id_PlayStation);
CREATE INDEX IF NOT EXISTS idx_status ON Sistem_rental(Status_Pembayaran);

-- ============================================
-- Views for Analysis
-- ============================================

-- View: Rental dengan informasi lengkap
CREATE VIEW IF NOT EXISTS v_rental_lengkap AS
SELECT 
    sr.Id_Rental,
    sr.Id_Customer,
    c.Nama_Customer,
    c.Jenis_Member,
    sr.Id_PlayStation,
    ps.Game,
    ps.Lokasi_Unit,
    ps.Harga_Per_Jam,
    sr.Id_Operator,
    op.Nama_Operator,
    op.Shift,
    sr.Jam_Mulai,
    sr.Jam_Selesai,
    sr.Total_Jam,
    sr.Total_Bayar,
    sr.Metode_Pembayaran,
    sr.Status_Pembayaran,
    sr.Catatan
FROM Sistem_rental sr
LEFT JOIN Customer c ON sr.Id_Customer = c.Id_Customer
LEFT JOIN PlayStation ps ON sr.Id_PlayStation = ps.Id_PlayStation
LEFT JOIN Operator op ON sr.Id_Operator = op.Id_Operator;

-- ============================================
-- Sample Queries untuk Testing
-- ============================================

-- Query 1: Get all night rentals (rentals yang overlap dengan 21:00-06:00)
-- SELECT * FROM Sistem_rental 
-- WHERE time(Jam_Mulai) >= '21:00:00' OR time(Jam_Mulai) < '06:00:00'
--    OR time(Jam_Selesai) >= '21:00:00' OR time(Jam_Selesai) < '06:00:00';

-- Query 2: Get currently active rentals
-- SELECT * FROM Sistem_rental 
-- WHERE datetime('now') BETWEEN Jam_Mulai AND Jam_Selesai;

-- Query 3: Get future rentals
-- SELECT * FROM Sistem_rental 
-- WHERE Jam_Mulai > datetime('now');

-- Query 4: Get completed rentals
-- SELECT * FROM Sistem_rental 
-- WHERE Jam_Selesai < datetime('now');

-- Query 5: Get rentals with payment pending
-- SELECT * FROM Sistem_rental 
-- WHERE Status_Pembayaran != 'Lunas';

-- ============================================
-- Notes:
-- ============================================
-- 1. Bonus Malam dihitung di software, BUKAN di database
-- 2. Sisa Waktu dihitung real-time di software
-- 3. Status (Belum Mulai/Sedang Main/Selesai) dihitung di software
-- 4. datetime('now') akan menggunakan waktu UTC
-- 5. Untuk production, gunakan timezone yang sesuai
-- ============================================

-- Display success message
SELECT 'Database created successfully!' AS Message,
       (SELECT COUNT(*) FROM Sistem_rental) AS Total_Rentals,
       (SELECT COUNT(*) FROM Customer) AS Total_Customers,
       (SELECT COUNT(*) FROM PlayStation) AS Total_Units;
