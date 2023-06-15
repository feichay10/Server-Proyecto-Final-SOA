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
    mDatabase.close();
    delete ui;
}

bool database::startDataBase() {
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    QString aux = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    aux += "/prueba";
    mDatabase.setDatabaseName(aux); //nameFile path of the database

    if (!mDatabase.open()) {
        qDebug() << "Problem with opening database";
    }
    return mDatabase.open();
}

void database::createTable() {
    QSqlQuery query(mDatabase);
    //QString create_table = "CREATE TABLE IF NOT EXISTS CheddarPP (ip TEXT PRIMARY KEY, projectName TEXT UNIQUE NOT NULL, taskNumber INTEGER NOT NULL, schedulable TEXT CHECK (schedulable IN ('Yes', 'No')), timestamp DATETIME)";
    QString create_table = "CREATE TABLE IF NOT EXISTS A (ip INTEGER PRIMARY KEY);";
    query.prepare(create_table);
    bool creation = query.exec();

    // Query creates data base if is not created
    if (!creation) {
        qDebug() << "Error creating table";
    } else {
        qDebug() << "The table has been created succesfully";
    }
}

void database::insertValues(QString projectName, int taskNumber, bool plannable, QString dateRealization) {
    startDataBase();
    createTable();
    QSqlQuery query(mDatabase);
    QString isPlannable;

    if(plannable) {
        isPlannable = "Yes";
    } else {
        isPlannable = "No";
    }

    /*query.prepare("INSERT INTO CheddarPP (ip, projectName, taskNumber, plannable, dateRealization) "
                  "VALUES (?,?,?,?,?);");*/

    query.prepare("INSERT INTO A (ip) VALUES (:ip);");

    //query.addBindValue(1);
    query.bindValue(":ip", 1);
    /*query.addBindValue(projectName);
    query.addBindValue(taskNumber);     ///< To received
    query.addBindValue(isPlannable);    ///< To received
    query.addBindValue(QDateTime::fromString(dateRealization, "dd-mm-yyyy"));*/
    //query.addBindValue(image);

    if(!query.exec()) {
        qDebug() << "Error adding values to database";
    }
}

void database::on_pushButton_AddRow_clicked()
{
    QByteArray array;
    QBuffer buffer(&array);
    buffer.open(QIODevice::WriteOnly);
    QPixmap pix = ui->label_LoadImage->pixmap();
    pix.save(&buffer, "JPEG");

    //insertValues(ui->lineEdit_ProjectName->text(), ui->spinBox_TaskNum->value(), ui->label_IsScheduleable->text() == "YES" || ui->label_IsScheduleable->text() == "Y", ui->dateEdit->text(), array);
    insertValues();
}
