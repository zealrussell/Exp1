#ifndef DBUTIL_H
#define DBUTIL_H

#include <QSqlDatabase>
#include <QSqlError>

#include <QSqlQuery>
#include <QHash>
#include <QString>
#include <QVariant>

class DbUtil
{
public:
    DbUtil();
    ~DbUtil();
    bool open(const QString &dbName);
    void close();
    QString getConnectionName() const;

    bool createDb();
    bool createTable(const QString &tableName);

    QString queryByKey(const QString &tableName, const QString &key);
    bool insert(const QString &tableName, const QStringList &list);
private:
    QSqlDatabase db;
    QSqlQuery query;
    QSqlError sqlError;

};
#endif // DBUTIL_H
