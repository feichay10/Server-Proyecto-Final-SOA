#ifndef DATABASE_H
#define DATABASE_H

#include <QMainWindow>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QBuffer>
#include <QStandardPaths>

// Creation the table
/*#define CREATE_TABLE_CHEDDAR++\
    "CREATE TABLE IF NOT EXISTS Cheddar++"\
    "(ip VARCHAR(14) PRIMARY KEY AUTOINCREMENT NOT NULL"\
    ", projectName TEXT UNIQUE NOT NULL"\
    ", taskNumber INTEGER NOT NULL"\
    ", scheduleable TEXT CHECK (scheduleable IN (\'Yes\', \'No\'))"\
    ", timestamp DATETIME)"\
    ", image BLOB)"*/

namespace Ui {
class database;
}

class database : public QMainWindow
{
    Q_OBJECT

public:
    explicit database(QWidget *parent = nullptr);
    explicit database();
    ~database();
    bool startDataBase();
    void createTable();
    void insertValues(QString projectName = "hola", int taskNumber = 5, QString plannable = "Y", QString dateRealization = "14/06/23");

private slots:
    void on_pushButton_AddRow_clicked();

private:
    Ui::database *ui;
    QSqlDatabase mDatabase;

};

#endif // DATABASE_H
