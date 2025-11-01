#include "MainWindow.h"
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QDate>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QInputDialog>
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QBrush>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), sqlModel(nullptr), displayModel(nullptr)
{
    setupUI();
    resize(1400, 800);
    setWindowTitle("Sistem Manajemen Rental PlayStation");
    
    // Setup real-time update timer (update every 30 seconds)
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateRealTimeData);
    updateTimer->start(30000); // 30 seconds
}

MainWindow::~MainWindow() {
    if (sqlModel) {
        delete sqlModel;
    }
    if (displayModel) {
        delete displayModel;
    }
    if (updateTimer) {
        updateTimer->stop();
        delete updateTimer;
    }
}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // ===== Status Label =====
    statusLabel = new QLabel("Status: Belum terhubung ke database");
    statusLabel->setObjectName("statusLabel");

    // ===== Database Type Selector =====
    dbTypeCombo = new QComboBox;
    dbTypeCombo->addItem("SQLite", DatabaseManager::SQLite);
    dbTypeCombo->addItem("PostgreSQL", DatabaseManager::PostgreSQL);
    dbTypeCombo->addItem("MySQL", DatabaseManager::MySQL);
    
    dbConnectButton = new QPushButton("🔌 Koneksi Database");
    dbConnectButton->setObjectName("primaryButton");

    QHBoxLayout *dbLayout = new QHBoxLayout;
    dbLayout->addWidget(new QLabel("Tipe Database:"));
    dbLayout->addWidget(dbTypeCombo);
    dbLayout->addWidget(dbConnectButton);
    dbLayout->addWidget(statusLabel);
    dbLayout->addStretch();

    // ===== Operator info =====
    operatorNameEdit = new QLineEdit;
    operatorNameEdit->setPlaceholderText("Nama operator");
    
    dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setDisplayFormat("dd/MM/yyyy");
    dateEdit->setCalendarPopup(true);

    QHBoxLayout *operatorLayout = new QHBoxLayout;
    operatorLayout->addWidget(new QLabel("👤 Operator:"));
    operatorLayout->addWidget(operatorNameEdit);
    operatorLayout->addWidget(new QLabel("📅 Tanggal:"));
    operatorLayout->addWidget(dateEdit);
    operatorLayout->addStretch();

    // ===== Filters =====
    idCustomerFilter = new QLineEdit;
    idCustomerFilter->setPlaceholderText("ID Customer");
    
    namaCustomerFilter = new QLineEdit;
    namaCustomerFilter->setPlaceholderText("Nama Customer");
    
    metodePembayaranFilter = new QLineEdit;
    metodePembayaranFilter->setPlaceholderText("Metode Pembayaran");
    
    tipeRuanganFilter = new QLineEdit;
    tipeRuanganFilter->setPlaceholderText("Tipe/Game");
    
    tanggalFilter = new QLineEdit;
    tanggalFilter->setPlaceholderText("YYYY-MM-DD");

    QHBoxLayout *filterLayout = new QHBoxLayout;
    filterLayout->addWidget(new QLabel("🔍 Filter - ID:"));
    filterLayout->addWidget(idCustomerFilter);
    filterLayout->addWidget(new QLabel("Nama:"));
    filterLayout->addWidget(namaCustomerFilter);
    filterLayout->addWidget(new QLabel("Pembayaran:"));
    filterLayout->addWidget(metodePembayaranFilter);
    filterLayout->addWidget(new QLabel("Game:"));
    filterLayout->addWidget(tipeRuanganFilter);
    filterLayout->addWidget(new QLabel("Tanggal:"));
    filterLayout->addWidget(tanggalFilter);

    // ===== Buttons =====
    searchButton = new QPushButton("🔍 Filter Data");
    searchButton->setObjectName("searchButton");
    
    refreshButton = new QPushButton("🔄 Refresh");
    refreshButton->setObjectName("refreshButton");
    
    exportButton = new QPushButton("📄 Ekspor ke CSV");
    exportButton->setObjectName("exportButton");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(exportButton);
    buttonLayout->addStretch();

    // ===== Table =====
    tableView = new QTableView;
    tableView->setAlternatingRowColors(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setObjectName("dataTable");
    tableView->verticalHeader()->setVisible(false);

    // ===== Layout utama =====
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    mainLayout->addLayout(dbLayout);
    
    // Separator line
    QFrame *line1 = new QFrame();
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    line1->setStyleSheet("background-color: #dcdde1;");
    mainLayout->addWidget(line1);
    
    mainLayout->addLayout(operatorLayout);
    
    QFrame *line2 = new QFrame();
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    line2->setStyleSheet("background-color: #dcdde1;");
    mainLayout->addWidget(line2);
    
    mainLayout->addLayout(filterLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(tableView);

    // ===== Connections =====
    connect(dbConnectButton, &QPushButton::clicked, this, &MainWindow::showDatabaseDialog);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::searchData);
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshTable);
    connect(exportButton, &QPushButton::clicked, this, &MainWindow::exportToCSV);
}

void MainWindow::showDatabaseDialog() {
    DatabaseManager::DatabaseType dbType = 
        static_cast<DatabaseManager::DatabaseType>(dbTypeCombo->currentData().toInt());
    
    if (dbType == DatabaseManager::SQLite) {
        loadDatabase();
    } else if (dbType == DatabaseManager::PostgreSQL || dbType == DatabaseManager::MySQL) {
        QDialog dialog(this);
        dialog.setWindowTitle(dbType == DatabaseManager::PostgreSQL ? 
                             "Koneksi PostgreSQL" : "Koneksi MySQL");
        dialog.setMinimumWidth(400);
        
        QFormLayout *form = new QFormLayout(&dialog);
        
        QLineEdit *hostEdit = new QLineEdit("localhost");
        QSpinBox *portSpin = new QSpinBox;
        portSpin->setRange(1, 65535);
        portSpin->setValue(dbType == DatabaseManager::PostgreSQL ? 5432 : 3306);
        QLineEdit *dbNameEdit = new QLineEdit("rental_db");
        QLineEdit *userEdit = new QLineEdit(dbType == DatabaseManager::PostgreSQL ? "postgres" : "root");
        QLineEdit *passEdit = new QLineEdit;
        passEdit->setEchoMode(QLineEdit::Password);
        
        form->addRow("Host:", hostEdit);
        form->addRow("Port:", portSpin);
        form->addRow("Database:", dbNameEdit);
        form->addRow("Username:", userEdit);
        form->addRow("Password:", passEdit);
        
        QDialogButtonBox *buttonBox = new QDialogButtonBox(
            QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
        form->addRow(buttonBox);
        
        if (dialog.exec() == QDialog::Accepted) {
            bool success = false;
            
            if (dbType == DatabaseManager::PostgreSQL) {
                success = dbManager.connectPostgreSQL(
                    hostEdit->text(),
                    portSpin->value(),
                    dbNameEdit->text(),
                    userEdit->text(),
                    passEdit->text()
                );
            } else {
                success = dbManager.connectMySQL(
                    hostEdit->text(),
                    portSpin->value(),
                    dbNameEdit->text(),
                    userEdit->text(),
                    passEdit->text()
                );
            }
            
            if (success) {
                statusLabel->setText("Status: ✅ Terhubung ke database");
                statusLabel->setStyleSheet("color: #27ae60; font-weight: bold;");
                QMessageBox::information(this, "Berhasil", 
                    "Terhubung ke database!");
                refreshTable();
            } else {
                statusLabel->setText("Status: ❌ Gagal terhubung");
                statusLabel->setStyleSheet("color: #e74c3c; font-weight: bold;");
                QMessageBox::critical(this, "Gagal", 
                    "Tidak dapat terhubung: " + dbManager.getLastError());
            }
        }
    }
}

void MainWindow::loadDatabase() {
    QString fileName = QFileDialog::getOpenFileName(
        this, "Pilih File Database", "", "Database (*.db *.sqlite *.sqlite3);;All Files (*)");
    
    if (fileName.isEmpty()) 
        return;

    if (dbManager.connect(fileName, DatabaseManager::SQLite)) {
        statusLabel->setText("Status: ✅ Terhubung ke " + QFileInfo(fileName).fileName());
        statusLabel->setStyleSheet("color: #27ae60; font-weight: bold;");
        QMessageBox::information(this, "Berhasil", "Database berhasil dimuat!");
        refreshTable();
    } else {
        statusLabel->setText("Status: ❌ Gagal terhubung");
        statusLabel->setStyleSheet("color: #e74c3c; font-weight: bold;");
        QMessageBox::critical(this, "Gagal", 
            "Tidak dapat membuka database: " + dbManager.getLastError());
    }
}

void MainWindow::refreshTable() {
    if (!dbManager.isConnected()) {
        QMessageBox::warning(this, "Error", "Database belum terhubung!");
        return;
    }

    loadDataWithCalculations();
}

void MainWindow::loadDataWithCalculations() {
    // Clean up old models
    if (displayModel) {
        delete displayModel;
        displayModel = nullptr;
    }
    
    if (sqlModel) {
        delete sqlModel;
        sqlModel = nullptr;
    }

    // Create SQL model
    sqlModel = new QSqlTableModel(this, dbManager.getDatabase());
    
    // Try common table names
    QStringList tableNames = {"Sistem_rental", "rental_data", "rental"};
    bool tableFound = false;
    QString foundTableName;
    
    for (const QString &tableName : tableNames) {
        sqlModel->setTable(tableName);
        if (sqlModel->select()) {
            tableFound = true;
            foundTableName = tableName;
            qDebug() << "✅ Loaded table:" << tableName;
            qDebug() << "📊 Total rows:" << sqlModel->rowCount();
            break;
        }
    }
    
    if (!tableFound) {
        QMessageBox::warning(this, "Error", 
            "Tidak dapat menemukan tabel rental di database!");
        delete sqlModel;
        sqlModel = nullptr;
        return;
    }

    // Create display model with calculated columns
    displayModel = new QStandardItemModel(this);
    
    // Get column names and indices
    QMap<QString, int> columnMap;
    QStringList headers;
    for (int c = 0; c < sqlModel->columnCount(); ++c) {
        QString headerName = sqlModel->headerData(c, Qt::Horizontal).toString();
        headers << headerName;
        columnMap[headerName] = c;
        qDebug() << "Column" << c << ":" << headerName;
    }
    
    // Add calculated columns
    headers << "Bonus Malam (Jam)" << "Sisa Waktu (Jam)" << "Status";
    displayModel->setHorizontalHeaderLabels(headers);

    // Find required column indices
    int jamMulaiCol = -1, jamSelesaiCol = -1, totalJamCol = -1;
    
    // Try different possible column names
    QStringList jamMulaiNames = {"Jam_Mulai", "jam_mulai", "JamMulai", "waktu_mulai", "start_time"};
    QStringList jamSelesaiNames = {"Jam_Selesai", "jam_selesai", "JamSelesai", "waktu_selesai", "end_time"};
    QStringList totalJamNames = {"Total_Jam", "total_jam", "TotalJam", "durasi", "duration"};
    
    for (const QString &name : jamMulaiNames) {
        if (columnMap.contains(name)) {
            jamMulaiCol = columnMap[name];
            qDebug() << "✅ Found Jam_Mulai column:" << name << "at index" << jamMulaiCol;
            break;
        }
    }
    
    for (const QString &name : jamSelesaiNames) {
        if (columnMap.contains(name)) {
            jamSelesaiCol = columnMap[name];
            qDebug() << "✅ Found Jam_Selesai column:" << name << "at index" << jamSelesaiCol;
            break;
        }
    }
    
    for (const QString &name : totalJamNames) {
        if (columnMap.contains(name)) {
            totalJamCol = columnMap[name];
            qDebug() << "✅ Found Total_Jam column:" << name << "at index" << totalJamCol;
            break;
        }
    }
    
    if (jamMulaiCol == -1 || jamSelesaiCol == -1 || totalJamCol == -1) {
        qWarning() << "⚠️ Warning: Could not find required time columns";
        qWarning() << "   Jam_Mulai column:" << (jamMulaiCol != -1 ? "Found" : "NOT FOUND");
        qWarning() << "   Jam_Selesai column:" << (jamSelesaiCol != -1 ? "Found" : "NOT FOUND");
        qWarning() << "   Total_Jam column:" << (totalJamCol != -1 ? "Found" : "NOT FOUND");
    }

    // Populate display model with calculated data
    QDateTime currentTime = QDateTime::currentDateTime();
    qDebug() << "🕐 Current time:" << currentTime.toString("yyyy-MM-dd HH:mm:ss");
    
    for (int row = 0; row < sqlModel->rowCount(); ++row) {
        QList<QStandardItem*> rowItems;
        
        // Copy original columns
        for (int col = 0; col < sqlModel->columnCount(); ++col) {
            QString data = sqlModel->data(sqlModel->index(row, col)).toString();
            QStandardItem *item = new QStandardItem(data);
            item->setEditable(false);
            rowItems.append(item);
        }
        
        // Extract time data for calculations
        QDateTime jamMulai, jamSelesai;
        int totalJam = 0;
        
        if (jamMulaiCol >= 0) {
            QString jamMulaiStr = sqlModel->data(sqlModel->index(row, jamMulaiCol)).toString();
            jamMulai = QDateTime::fromString(jamMulaiStr, "yyyy-MM-dd HH:mm:ss");
            if (!jamMulai.isValid()) {
                jamMulai = QDateTime::fromString(jamMulaiStr, "yyyy-MM-dd HH:mm");
            }
            if (!jamMulai.isValid()) {
                jamMulai = QDateTime::fromString(jamMulaiStr, Qt::ISODate);
            }
        }
        
        if (jamSelesaiCol >= 0) {
            QString jamSelesaiStr = sqlModel->data(sqlModel->index(row, jamSelesaiCol)).toString();
            jamSelesai = QDateTime::fromString(jamSelesaiStr, "yyyy-MM-dd HH:mm:ss");
            if (!jamSelesai.isValid()) {
                jamSelesai = QDateTime::fromString(jamSelesaiStr, "yyyy-MM-dd HH:mm");
            }
            if (!jamSelesai.isValid()) {
                jamSelesai = QDateTime::fromString(jamSelesaiStr, Qt::ISODate);
            }
        }
        
        if (totalJamCol >= 0) {
            totalJam = sqlModel->data(sqlModel->index(row, totalJamCol)).toInt();
        }
        
        // Debug first row
        if (row == 0) {
            qDebug() << "🔍 Sample row 0 data:";
            qDebug() << "   Jam Mulai:" << jamMulai.toString("yyyy-MM-dd HH:mm:ss") << (jamMulai.isValid() ? "✅" : "❌");
            qDebug() << "   Jam Selesai:" << jamSelesai.toString("yyyy-MM-dd HH:mm:ss") << (jamSelesai.isValid() ? "✅" : "❌");
            qDebug() << "   Total Jam:" << totalJam;
        }
        
        // CALCULATE NIGHT BONUS
        double nightBonus = calculateNightBonus(jamMulai, totalJam);
        QStandardItem *bonusItem = new QStandardItem(QString::number(nightBonus, 'f', 1));
        bonusItem->setTextAlignment(Qt::AlignCenter);
        bonusItem->setEditable(false);
        if (nightBonus > 0) {
            bonusItem->setForeground(QBrush(QColor("#27ae60")));
            QFont boldFont = bonusItem->font();
            boldFont.setBold(true);
            bonusItem->setFont(boldFont);
        }
        rowItems.append(bonusItem);
        
        // CALCULATE REMAINING TIME
        double sisaWaktu = calculateRemainingTime(jamSelesai);
        QStandardItem *sisaItem = new QStandardItem(QString::number(sisaWaktu, 'f', 2));
        sisaItem->setTextAlignment(Qt::AlignCenter);
        sisaItem->setEditable(false);
        if (sisaWaktu < 0) {
            sisaItem->setForeground(QBrush(QColor("#e74c3c")));
        } else if (sisaWaktu < 1.0) {
            sisaItem->setForeground(QBrush(QColor("#f39c12")));
            QFont boldFont = sisaItem->font();
            boldFont.setBold(true);
            sisaItem->setFont(boldFont);
        } else {
            sisaItem->setForeground(QBrush(QColor("#27ae60")));
        }
        rowItems.append(sisaItem);
        
        // CALCULATE STATUS
        QString status = getStatusString(jamMulai, jamSelesai);
        QStandardItem *statusItem = new QStandardItem(status);
        statusItem->setTextAlignment(Qt::AlignCenter);
        statusItem->setEditable(false);
        statusItem->setForeground(QBrush(getStatusColor(status)));
        QFont boldFont = statusItem->font();
        boldFont.setBold(true);
        statusItem->setFont(boldFont);
        rowItems.append(statusItem);
        
        displayModel->appendRow(rowItems);
    }
    
    qDebug() << "✅ Display model created with" << displayModel->rowCount() << "rows";
    
    tableView->setModel(displayModel);
    tableView->resizeColumnsToContents();
    
    // Adjust column widths for calculated columns
    int colCount = displayModel->columnCount();
    if (colCount >= 3) {
        tableView->setColumnWidth(colCount - 3, 150); // Bonus Malam
        tableView->setColumnWidth(colCount - 2, 150); // Sisa Waktu
        tableView->setColumnWidth(colCount - 1, 120); // Status
    }
}

double MainWindow::calculateNightBonus(const QDateTime &startTime, int durationHours) {
    if (!startTime.isValid() || durationHours <= 0) {
        return 0.0;
    }
    
    // Night hours: 21:00 - 06:00
    QTime nightStart(21, 0);
    QTime nightEnd(6, 0);
    
    double nightHours = 0.0;
    QDateTime currentCheck = startTime;
    QDateTime endTime = startTime.addSecs(durationHours * 3600);
    
    // Check each hour of the rental period
    while (currentCheck < endTime) {
        QTime checkTime = currentCheck.time();
        
        // Count hours between 21:00-23:59 or 00:00-05:59
        if (checkTime >= nightStart || checkTime < nightEnd) {
            nightHours += 1.0;
        }
        
        currentCheck = currentCheck.addSecs(3600); // Add 1 hour
    }
    
    // Bonus: 1 hour for every 3 hours played at night
    double bonus = nightHours / 3.0;
    
    qDebug() << "🌙 Night Bonus Calculation:";
    qDebug() << "   Start:" << startTime.toString("yyyy-MM-dd HH:mm");
    qDebug() << "   Duration:" << durationHours << "hours";
    qDebug() << "   Night hours:" << nightHours;
    qDebug() << "   Bonus:" << bonus << "hours";
    
    return bonus;
}

double MainWindow::calculateRemainingTime(const QDateTime &endTime) {
    if (!endTime.isValid()) {
        return 0.0;
    }
    
    QDateTime now = QDateTime::currentDateTime();
    qint64 secondsRemaining = now.secsTo(endTime);
    double hoursRemaining = secondsRemaining / 3600.0;
    
    qDebug() << "⏰ Remaining Time:";
    qDebug() << "   End time:" << endTime.toString("yyyy-MM-dd HH:mm:ss");
    qDebug() << "   Current:" << now.toString("yyyy-MM-dd HH:mm:ss");
    qDebug() << "   Remaining:" << hoursRemaining << "hours";
    
    return hoursRemaining;
}

QString MainWindow::getStatusString(const QDateTime &startTime, const QDateTime &endTime) {
    QDateTime now = QDateTime::currentDateTime();
    
    if (!startTime.isValid() || !endTime.isValid()) {
        return "N/A";
    }
    
    if (now < startTime) {
        return "Belum Mulai";
    } else if (now >= startTime && now <= endTime) {
        return "Sedang Main";
    } else {
        return "Selesai";
    }
}

QColor MainWindow::getStatusColor(const QString &status) {
    if (status == "Sedang Main") {
        return QColor("#27ae60"); // Green
    } else if (status == "Belum Mulai") {
        return QColor("#3498db"); // Blue
    } else if (status == "Selesai") {
        return QColor("#95a5a6"); // Gray
    }
    return QColor("#000000"); // Black
}

void MainWindow::updateRealTimeData() {
    if (!displayModel || displayModel->rowCount() == 0) {
        return;
    }
    
    qDebug() << "🔄 Updating real-time data...";
    
    int colCount = displayModel->columnCount();
    if (colCount < 3) return;
    
    int sisaWaktuCol = colCount - 2;
    int statusCol = colCount - 1;
    
    // Find Jam_Mulai and Jam_Selesai column indices in original data
    int jamMulaiIdx = -1, jamSelesaiIdx = -1;
    for (int c = 0; c < colCount - 3; ++c) {
        QString header = displayModel->headerData(c, Qt::Horizontal).toString();
        if (header.contains("Jam_Mulai", Qt::CaseInsensitive) || 
            header.contains("mulai", Qt::CaseInsensitive)) {
            jamMulaiIdx = c;
        }
        if (header.contains("Jam_Selesai", Qt::CaseInsensitive) || 
            header.contains("selesai", Qt::CaseInsensitive)) {
            jamSelesaiIdx = c;
        }
    }
    
    if (jamMulaiIdx < 0 || jamSelesaiIdx < 0) {
        qWarning() << "⚠️ Cannot find time columns for update";
        return;
    }
    
    for (int row = 0; row < displayModel->rowCount(); ++row) {
        // Parse times
        QString jamMulaiStr = displayModel->data(displayModel->index(row, jamMulaiIdx)).toString();
        QString jamSelesaiStr = displayModel->data(displayModel->index(row, jamSelesaiIdx)).toString();
        
        QDateTime jamMulai = QDateTime::fromString(jamMulaiStr, "yyyy-MM-dd HH:mm:ss");
        if (!jamMulai.isValid()) {
            jamMulai = QDateTime::fromString(jamMulaiStr, "yyyy-MM-dd HH:mm");
        }
        
        QDateTime jamSelesai = QDateTime::fromString(jamSelesaiStr, "yyyy-MM-dd HH:mm:ss");
        if (!jamSelesai.isValid()) {
            jamSelesai = QDateTime::fromString(jamSelesaiStr, "yyyy-MM-dd HH:mm");
        }
        
        // Update remaining time
        double sisaWaktu = calculateRemainingTime(jamSelesai);
        QStandardItem *sisaItem = displayModel->item(row, sisaWaktuCol);
        if (sisaItem) {
            sisaItem->setText(QString::number(sisaWaktu, 'f', 2));
            if (sisaWaktu < 0) {
                sisaItem->setForeground(QBrush(QColor("#e74c3c")));
            } else if (sisaWaktu < 1.0) {
                sisaItem->setForeground(QBrush(QColor("#f39c12")));
            } else {
                sisaItem->setForeground(QBrush(QColor("#27ae60")));
            }
        }
        
        // Update status
        QString status = getStatusString(jamMulai, jamSelesai);
        QStandardItem *statusItem = displayModel->item(row, statusCol);
        if (statusItem) {
            statusItem->setText(status);
            statusItem->setForeground(QBrush(getStatusColor(status)));
        }
    }
    
    qDebug() << "✅ Real-time data updated";
}

void MainWindow::searchData() {
    if (!dbManager.isConnected()) {
        QMessageBox::warning(this, "Error", "Database belum terhubung!");
        return;
    }

    if (!sqlModel) {
        QMessageBox::warning(this, "Error", "Tabel belum dimuat!");
        return;
    }

    QStringList filters;
    
    if (!idCustomerFilter->text().isEmpty()) {
        filters << QString("Id_Customer LIKE '%%1%'").arg(idCustomerFilter->text());
    }
    if (!namaCustomerFilter->text().isEmpty()) {
        filters << QString("Nama_Customer LIKE '%%1%'").arg(namaCustomerFilter->text());
    }
    if (!metodePembayaranFilter->text().isEmpty()) {
        filters << QString("Metode_Pembayaran LIKE '%%1%'").arg(metodePembayaranFilter->text());
    }
    if (!tipeRuanganFilter->text().isEmpty()) {
        filters << QString("Game LIKE '%%1%'").arg(tipeRuanganFilter->text());
    }
    if (!tanggalFilter->text().isEmpty()) {
        filters << QString("Jam_Mulai LIKE '%%1%'").arg(tanggalFilter->text());
    }

    QString filterString = filters.join(" AND ");
    sqlModel->setFilter(filterString);
    sqlModel->select();
    
    qDebug() << "🔍 Applied filter:" << filterString;
    
    // Reload with calculations
    loadDataWithCalculations();
}

void MainWindow::exportToCSV() {
    if (!displayModel || displayModel->rowCount() == 0) {
        QMessageBox::warning(this, "Peringatan", "Tidak ada data untuk diekspor!");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this, "Simpan Laporan CSV", 
        QString("laporan_rental_%1.csv").arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss")),
        "CSV Files (*.csv);;All Files (*)");
    
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Tidak dapat membuat file!");
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    // Header laporan
    out << "LAPORAN RENTAL PLAYSTATION\n";
    out << "========================================\n";
    out << "Operator:," << operatorNameEdit->text() << "\n";
    out << "Tanggal:," << dateEdit->date().toString("dd/MM/yyyy") << "\n";
    out << "Waktu Ekspor:," << QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss") << "\n";
    out << "Total Data:," << displayModel->rowCount() << "\n";
    out << "========================================\n\n";

    // Header kolom
    QStringList headers;
    for (int c = 0; c < displayModel->columnCount(); ++c) {
        headers << displayModel->headerData(c, Qt::Horizontal).toString();
    }
    out << headers.join(",") << "\n";

    // Data baris
    for (int r = 0; r < displayModel->rowCount(); ++r) {
        QStringList rowData;
        for (int c = 0; c < displayModel->columnCount(); ++c) {
            QString data = displayModel->data(displayModel->index(r, c)).toString();
            // Escape commas and quotes
            if (data.contains(",") || data.contains("\"") || data.contains("\n")) {
                data = "\"" + data.replace("\"", "\"\"") + "\"";
            }
            rowData << data;
        }
        out << rowData.join(",") << "\n";
    }

    file.close();
    QMessageBox::information(this, "Berhasil", 
        QString("✅ Laporan berhasil disimpan!\n\nFile: %1\nTotal data: %2 baris\n\nTermasuk kolom kalkulasi:\n- Bonus Malam\n- Sisa Waktu\n- Status")
        .arg(fileName)
        .arg(displayModel->rowCount()));
    
    qDebug() << "📄 CSV exported:" << fileName << "with" << displayModel->rowCount() << "rows";
}