#include "dbutil.h"

DbUtil::DbUtil()
{

}
DbUtil::~DbUtil()
{
    close();
    qDebug() << "Close the db!";
}

bool DbUtil::open(const QString &dbName)
{
    // QString path = QApplication::applicationDirPath() + "/" + dbName;
    QString path = "/Users/zeal/work/project/TestQT/Exp1/" + dbName;
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
            db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");

        db.setDatabaseName(path);
    }
    if (db.isOpen()) {
        close();
    }

    if (!db.open()) {
        qDebug() << "Error: Failed to connect database." << db.lastError().text();
        return false;
    }
    qDebug() << "Open the db success!" << path;
    query = QSqlQuery(db);
    return true;
}

void DbUtil::close()
{
    db.close();
}

bool DbUtil::createTable(const QString &tableName)
{
    QString sql = QString("CREATE TABLE IF NOT EXISTS %1 (id INTEGER PRIMARY KEY AUTOINCREMENT, username CHAR (50) UNIQUE NOT NULL, password CHAR(30) NOT NULL, sex INTEGER, age INTEGER) ").arg(tableName);
    if (!query.exec(sql)) {
        sqlError = query.lastError();
        qDebug() << "Create table " << tableName << " failed, " << sqlError.text();
        return false;
    }
    qDebug() << QString("Create table %1 success!").arg(tableName);
    return true;
}

QString DbUtil::queryByKey(const QString &tableName, const QString &key)
{
    QString sql = QString("SELECT password from %1 WHERE username='%2' ").arg(tableName, key);
    if (!query.exec(sql)) {
        sqlError = query.lastError();
    } else {
        while(query.next()) {
            QString pwd = query.value(0).toString();
            if (!pwd.isEmpty() && !pwd.isNull())
                return pwd;
        }
    }
    return "";
}

bool DbUtil::insert(const QString &tableName, const QStringList &list)
{
    if (list.size() != 4) return false;
    QString sql = QString("INSERT INTO %1 VALUES(null, '%2', '%3', '%4', '%5')").arg(tableName, list.at(0), list.at(1) ,list.at(2), list.at(3));
    if (!query.exec(sql)) {
        sqlError = query.lastError();
        qDebug() << "Insert failed, " << sqlError.text();
        return false;
    }
    qDebug() << "Insert table success!";
    return true;
}
