#include "database.h"
#include "ui_database.h"

database::database(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::database)
{
    ui->setupUi(this);
    startDataBase();
    QSqlQuery query(mDatabase);
    //QString create_table = "CREATE TABLE IF NOT EXISTS CheddarPP (ip TEXT PRIMARY KEY, projectName TEXT UNIQUE NOT NULL, taskNumber INTEGER NOT NULL, schedulable TEXT CHECK (schedulable IN ('Yes', 'No')), timestamp DATETIME)";
    QString create_table = "CREATE TABLE IF NOT EXISTS B (ip INTEGER, projectName TEXT, taskNumber INTEGER, schedulable TEXT, timestamp DATETIME, PRIMARY KEY (ip, projectName));";
    query.prepare(create_table);
    bool creation = query.exec();

    // Query creates data base if is not created
    if (!creation) {
        qDebug() << "Error creating table";
    } else {
        qDebug() << "The table has been created succesfully";
    }
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
    bool open = mDatabase.open();

    if (!open) {
        qDebug() << "Problem with opening database";
    }
    return open;
}

void database::insertValues(QString projectName, int taskNumber, QString plannable, QString dateRealization) {
    QSqlQuery query(mDatabase);

    /*query.prepare("INSERT INTO CheddarPP (ip, projectName, taskNumber, plannable, dateRealization) "
                  "VALUES (?,?,?,?,?);");*/

    query.prepare("INSERT INTO B (ip, projectName, taskNumber, schedulable, timestamp) VALUES (?,?,?,?,?);");

    query.addBindValue(1);
    //query.bindValue(":ip", 1);
    //query.bindValue(":projectName", projectName);
    query.addBindValue(projectName.toStdString().c_str());
    query.addBindValue(taskNumber);     ///< To received
    query.addBindValue(plannable.toStdString().c_str());    ///< To received
    query.addBindValue(QDateTime::fromString(dateRealization, "dd-mm-yyyy"));
    //query.addBindValue(image);

    if(!query.exec()) {
        qDebug() << query.lastError();
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

    insertValues(ui->lineEdit_ProjectName->text(), ui->spinBox_TaskNum->value(), ui->label_IsScheduleable->text(), ui->dateEdit->text());
    //insertValues();
}
