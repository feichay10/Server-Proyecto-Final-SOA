#include "database.h"

database::database(QObject *parent) {}

bool database::startDataBase(QString &namefile) {
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName(nameFile); //nameFile path of the database
    if (!mDatabase.open()) {
        qDebug() << "Problem with opening database";
    }
    return mDatabase.open();
}

void database::createDataBase() {
    QSqlQuery query;
    bool creation = query.exec(CREATE_TABLE_CHEDDAR++);

    // Query creates data base if is not created
    if (!creation) {
        qDebug() << "Error creating table";
    }

    return creation;
}

