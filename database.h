#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>

// Creation the table
#define CREATE_TABLE_CHEDDAR++\
    "(id INTEGER"\
    ", projectName TEXT UNIQUE NOT NULL"\
    ", taskNumber INTEGER NOT NULL"\
    ", hyperperiod INTEGER"\
    ", scheduleable TEXT CHECK (scheduleable IN (\'Yes\', \'No\'))"\
    ", timestamp TEXT DEFAULT(date('now','localtime'))"\
    ", image BLOB)"

class database : public QObject
{
    Q_OBJECT
public:
    explicit database(QObject *parent = nullptr);
    bool startDataBase(QString &namefile);
    void createDataBase();

private:
    QSqlDatabase mDatabase;

};

#endif // DATABASE_H
