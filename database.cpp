#include "database.h"
#include "ui_database.h"

database::database(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::database)
{
    ui->setupUi(this);
    startDataBase();
    QSqlQuery query(mDatabase);
    QString create_table = "CREATE TABLE IF NOT EXISTS B (ip INTEGER, projectName TEXT, taskNumber INTEGER, schedulable TEXT, timestamp TEXT, graph BLOB, PRIMARY KEY (ip, projectName));";
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

    // Load data
    QSqlQuery qry(mDatabase);
    qry.prepare("SELECT * FROM B");
    if (!qry.exec()) {
        qDebug() << "Error loading previous data";
    } else {
        while(qry.next()) {
            QImage oso;
            QByteArray arr= qry.value(5).toByteArray();
            oso.loadFromData(arr);
            QPixmap image = QPixmap::fromImage(oso);
            ui->label_LoadImage->setScaledContents(true);
            //QPixmap image = ui->label_Image->pixmap();
            ui->label_LoadImage->setPixmap(image.scaled(ui->label_LoadImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            qDebug() << qry.value(0).toString();
            qDebug() << qry.value(1).toString();
            qDebug() << qry.value(2).toString();
            qDebug() << qry.value(3).toString();
            qDebug() << qry.value(4).toString();
            //qDebug() << qry.value(5).toString();
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            for (int i = 0; i < 6; ++i)
            {
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, i, new QTableWidgetItem(qry.value(i).toString()));
            }
        }
    }

    return open;
}

void database::insertValues(QString projectName, int taskNumber, QString plannable, QString dateRealization, QByteArray image) {
    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO B (ip, projectName, taskNumber, schedulable, timestamp, graph) VALUES (?,?,?,?,?,?);");

    query.addBindValue(1);
    query.addBindValue(projectName.toStdString().c_str());
    query.addBindValue(taskNumber);                         ///< To received
    query.addBindValue(plannable.toStdString().c_str());    ///< To received
    query.addBindValue(dateRealization);
    query.addBindValue(image);

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

    insertValues(ui->lineEdit_ProjectName->text(), ui->spinBox_TaskNum->value(), ui->lineEdit_Schedulable->text(), ui->dateEdit->text(), array);
    qDebug() << "Fecha " << ui->dateEdit->text();
}
