#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DatabaseManager {
public:
    enum DatabaseType {
        SQLite,
        PostgreSQL,
        MySQL,
        ODBC
    };

    DatabaseManager();
    ~DatabaseManager();
    
    bool connect(const QString &path, DatabaseType type = SQLite);
    bool connectPostgreSQL(const QString &host, int port, const QString &dbName, 
                          const QString &user, const QString &password);
    bool connectMySQL(const QString &host, int port, const QString &dbName,
                     const QString &user, const QString &password);
    
    void disconnect();
    bool isConnected() const;
    
    QSqlQuery getFilteredData(const QString &idCustomer,
                              const QString &namaCustomer,
                              const QString &metodePembayaran,
                              const QString &tipeRuangan,
                              const QString &tanggal);
    
    QSqlDatabase getDatabase() const { return db; }
    QString getLastError() const;

private:
    QSqlDatabase db;
    DatabaseType currentType;
    QString connectionName;
    
    QString generateConnectionName();
};

#endif // DATABASEMANAGER_H