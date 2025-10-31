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

private:
    void setupUI();
    void refreshTable();
    
    DatabaseManager dbManager;
    QTableView *tableView;
    QSqlTableModel *model;

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
    QPushButton *loadButton;
    QPushButton *searchButton;
    QPushButton *exportButton;
    QPushButton *dbConnectButton;
    
    // Database type selector
    QComboBox *dbTypeCombo;
};

#endif // MAINWINDOW_H