#include "database.h"
#include "ui_database.h"

database::database(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::database)
{
    ui->setupUi(this);
}

database::database() {}

database::~database()
{
    delete ui;
}

bool database::startDataBase(QString &nameFile) {
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName(nameFile); //nameFile path of the database
    if (!mDatabase.open()) {
        qDebug() << "Problem with opening database";
    }
    return mDatabase.open();
}

void database::createDataBase() {
    QSqlQuery query;
    QString create_table = "CREATE TABLE IF NOT EXISTS Cheddar++"\
        "(ip VARCHAR(14) PRIMARY KEY AUTOINCREMENT NOT NULL"\
        ", projectName TEXT UNIQUE NOT NULL"\
        ", taskNumber INTEGER NOT NULL"\
        ", scheduleable TEXT CHECK (scheduleable IN (\'Yes\', \'No\'))"\
        ", timestamp DATETIME)"\
        ", image BLOB)";

    bool creation = query.exec(create_table);

    // Query creates data base if is not created
    if (!creation) {
        qDebug() << "Error creating table";
    } else {
        qDebug() << "The table has been created succesfully";
    }

    mDatabase.close();
}

bool database::insertValues(QString projectName, int taskNumber, bool plannable, QString dateRealization, QByteArray &image) {
    QSqlQuery query;
    QString isPlannable;

    if(plannable) {
        isPlannable = "Yes";
    } else {
        isPlannable = "No";
    }

    query.prepare("INSERT INTO Cheddar++ (projectName, taskNumber, plannable, dateRealization, image) "
                  "VALUES (?,?,?,?,?");

    query.addBindValue(projectName);
    query.addBindValue(taskNumber);
    query.addBindValue(isPlannable);
    query.addBindValue(QDateTime::fromString(dateRealization, "dd-mm-yyyy"));
    query.addBindValue(image);

    if(!query.exec()) {
        qDebug() << "Error adding values to database";
    }
}




