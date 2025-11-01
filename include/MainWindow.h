#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateEdit>
#include <QSqlTableModel>
#include <QComboBox>
#include <QTimer>
#include <QStandardItemModel>
#include "DatabaseManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadDatabase();
    void exportToCSV();
    void searchData();
    void showDatabaseDialog();
    void updateRealTimeData();
    void refreshTable();

private:
    void setupUI();
    void loadDataWithCalculations();
    
    // Calculation functions
    double calculateNightBonus(const QDateTime &startTime, int durationHours);
    double calculateRemainingTime(const QDateTime &endTime);
    QString getStatusString(const QDateTime &startTime, const QDateTime &endTime);
    QColor getStatusColor(const QString &status);
    
    DatabaseManager dbManager;
    QTableView *tableView;
    QStandardItemModel *displayModel;
    QSqlTableModel *sqlModel;
    QTimer *updateTimer;

    // Filter fields
    QLineEdit *idCustomerFilter;
    QLineEdit *namaCustomerFilter;
    QLineEdit *metodePembayaranFilter;
    QLineEdit *tipeRuanganFilter;
    QLineEdit *tanggalFilter;

    // Operator & date info
    QLineEdit *operatorNameEdit;
    QDateEdit *dateEdit;

    // Buttons
    QPushButton *searchButton;
    QPushButton *exportButton;
    QPushButton *dbConnectButton;
    QPushButton *refreshButton;
    
    // Database type selector
    QComboBox *dbTypeCombo;
    
    // Status label
    QLabel *statusLabel;
};

#endif // MAINWINDOW_H