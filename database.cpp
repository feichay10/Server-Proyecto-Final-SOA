#include "database.h"

database::database(QObject *parent) {}

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
    bool creation = query.exec(CREATE_TABLE_CHEDDAR++);

    // Query creates data base if is not created
    if (!creation) {
        qDebug() << "Error creating table";
    }

    mDatabase.close();
}

bool database::insertValues(QString projectName, int taskNumber, bool plannable, QString dateRealization, QByteArray &image) {
    QSqlQuery query;
    QString isPlannable;

    if(plannable) {
        isPlannable = "Sí";
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
