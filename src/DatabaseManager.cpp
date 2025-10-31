#include "DatabaseManager.h"
#include <QDebug>
#include <QDateTime>

DatabaseManager::DatabaseManager() 
    : currentType(SQLite)
{
    connectionName = generateConnectionName();
}

DatabaseManager::~DatabaseManager() {
    disconnect();
}

QString DatabaseManager::generateConnectionName() {
    return QString("db_connection_%1").arg(QDateTime::currentMSecsSinceEpoch());
}

bool DatabaseManager::connect(const QString &path, DatabaseType type) {
    disconnect(); // Close existing connection
    
    currentType = type;
    
    switch(type) {
        case SQLite:
            db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
            db.setDatabaseName(path);
            break;
        case PostgreSQL:
            qDebug() << "Use connectPostgreSQL() for PostgreSQL connections";
            return false;
        case MySQL:
            qDebug() << "Use connectMySQL() for MySQL connections";
            return false;
        default:
            qDebug() << "Unsupported database type";
            return false;
    }
    
    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
        return false;
    }
    
    qDebug() << "Successfully connected to database";
    return true;
}

bool DatabaseManager::connectPostgreSQL(const QString &host, int port, 
                                       const QString &dbName, 
                                       const QString &user, 
                                       const QString &password) {
    disconnect();
    
    currentType = PostgreSQL;
    db = QSqlDatabase::addDatabase("QPSQL", connectionName);
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(password);
    
    if (!db.open()) {
        qDebug() << "Failed to connect to PostgreSQL:" << db.lastError().text();
        return false;
    }
    
    qDebug() << "Successfully connected to PostgreSQL";
    return true;
}

bool DatabaseManager::connectMySQL(const QString &host, int port,
                                  const QString &dbName,
                                  const QString &user,
                                  const QString &password) {
    disconnect();
    
    currentType = MySQL;
    db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(password);
    
    if (!db.open()) {
        qDebug() << "Failed to connect to MySQL:" << db.lastError().text();
        return false;
    }
    
    qDebug() << "Successfully connected to MySQL";
    return true;
}

void DatabaseManager::disconnect() {
    if (db.isOpen()) {
        db.close();
    }
    if (QSqlDatabase::contains(connectionName)) {
        QSqlDatabase::removeDatabase(connectionName);
    }
}

bool DatabaseManager::isConnected() const {
    return db.isOpen();
}

QString DatabaseManager::getLastError() const {
    return db.lastError().text();
}

QSqlQuery DatabaseManager::getFilteredData(const QString &idCustomer,
                                           const QString &namaCustomer,
                                           const QString &metodePembayaran,
                                           const QString &tipeRuangan,
                                           const QString &tanggal)
{
    // Using prepared statements to prevent SQL injection
    QString queryStr =
        "SELECT * FROM Sistem_rental "
        "JOIN Customer ON Sistem_rental.Id_Customer = Customer.Id_Customer "
        "JOIN PlayStation ON Sistem_rental.Id_PlayStation = PlayStation.Id_PlayStation "
        "JOIN Operator ON Sistem_rental.Id_Operator = Operator.Id_Operator "
        "WHERE 1=1 ";

    QStringList conditions;
    QMap<QString, QString> bindings;

    if (!idCustomer.isEmpty()) {
        conditions << "Customer.Id_Customer LIKE :idCustomer";
        bindings[":idCustomer"] = "%" + idCustomer + "%";
    }
    if (!namaCustomer.isEmpty()) {
        conditions << "Customer.Nama_Customer LIKE :namaCustomer";
        bindings[":namaCustomer"] = "%" + namaCustomer + "%";
    }
    if (!metodePembayaran.isEmpty()) {
        conditions << "Operator.Metode_Pembayaran LIKE :metodePembayaran";
        bindings[":metodePembayaran"] = "%" + metodePembayaran + "%";
    }
    if (!tipeRuangan.isEmpty()) {
        conditions << "PlayStation.Game LIKE :tipeRuangan";
        bindings[":tipeRuangan"] = "%" + tipeRuangan + "%";
    }
    if (!tanggal.isEmpty()) {
        conditions << "date(Sistem_rental.Jam_Mulai) = :tanggal";
        bindings[":tanggal"] = tanggal;
    }

    if (!conditions.isEmpty()) {
        queryStr += "AND " + conditions.join(" AND ");
    }

    QSqlQuery query(db);
    query.prepare(queryStr);
    
    // Bind values
    for (auto it = bindings.constBegin(); it != bindings.constEnd(); ++it) {
        query.bindValue(it.key(), it.value());
    }
    
    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
    }
    
    return query;
}