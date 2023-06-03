#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QDateTime>

// Creation the table
#define CREATE_TABLE_CHEDDAR++\
    "CREATE TABLE IF NOT EXISTS Cheddar++ ("\
    "ip VARCHAR(14) PRIMARY KEY AUTOINCREMENT NOT NULL"\
    "projectName TEXT UNIQUE NOT NULL"\
    "taskNumber INTEGER NOT NULL"\
    "scheduleable TEXT CHECK (scheduleable IN (\'Yes\', \'No\'))"\
    "timestamp DATETIME)"\
    "image BLOB)"

class database : public QObject
{
    Q_OBJECT
public:
    explicit database(QObject *parent = nullptr);
    bool startDataBase(QString &namefile);
    void createDataBase();
    bool insertValues(QString projectName, int taskNumber, bool plannable, QString dateRealization, QByteArray &image);

private:
    QSqlDatabase mDatabase;

};

#endif // DATABASE_H
