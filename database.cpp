#include "database.h"
#include "ui_database.h"

database::database(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::database) {
  ui->setupUi(this);
  startDataBase();
}

database::database() {}

database::~database() {
  mDatabase.close();
  delete ui;
}

bool database::startDataBase(const QString& path) {
  mDatabase = QSqlDatabase::addDatabase("QSQLITE");
  mDatabase.setDatabaseName(path); //nameFile path of the database
  bool ok = mDatabase.open();

  if (!ok)
    qDebug() << "Problem with opening database";

  else {
    QSqlQuery query(mDatabase);
    QString create_table = "CREATE TABLE IF NOT EXISTS CHEDDARPP (ip INTEGER, projectName TEXT, taskNumber INTEGER, schedulable TEXT, timestamp TEXT, graph BLOB, PRIMARY KEY (ip, projectName, timestamp));";
    query.prepare(create_table);
    ok = query.exec();

    if (!ok)
      qDebug() << "Error creating table";

    else {
      ok = loadTable();

      if (!ok) qDebug() << "Error loading previous data";
    }
  }

  return ok;
}

bool database::loadTable() {
  // Load data
  QSqlQuery qry(mDatabase);
  qry.prepare("SELECT * FROM CHEDDARPP");
  bool loaded = qry.exec();

  if (loaded) {
    while(qry.next()) {
      QImage img;
      QByteArray arr = qry.value(5).toByteArray();
      img.loadFromData(arr);
      QPixmap pix = QPixmap::fromImage(img);
      pixmaps_assoc_.push_back(pix);
      //ui->label_LoadImage->setScaledContents(true);
      //QPixmap image = ui->label_Image->pixmap();
      //ui->label_LoadImage->setPixmap(image.scaled(ui->label_LoadImage->size(), Qt::KeepAspectRatio));
      ui->tableWidget->insertRow(ui->tableWidget->rowCount());

      for (int i = 0; i < 6; ++i)
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, i, new QTableWidgetItem(qry.value(i).toString()));
    }
  }

  return loaded;
}

void database::insertValues(QString projectName, int taskNumber, QString plannable, QString dateRealization, QByteArray image) {
  QSqlQuery query(mDatabase);
  query.prepare("INSERT INTO CHEDDARPP (ip, projectName, taskNumber, schedulable, timestamp, graph) VALUES (?,?,?,?,?,?);");
  query.addBindValue(1);
  query.addBindValue(projectName.toStdString().c_str());
  query.addBindValue(taskNumber);                         ///< To received
  query.addBindValue(plannable.toStdString().c_str());    ///< To received
  query.addBindValue(dateRealization);
  query.addBindValue(image);

  if(!query.exec()) {
    qDebug() << query.lastError();
    qDebug() << "Error adding values to database";

  } else {
    QImage img;
    img.loadFromData(image);
    QPixmap pix = QPixmap::fromImage(img);
    pixmaps_assoc_.push_back(pix);
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(projectName));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString(std::to_string(taskNumber).c_str())));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(plannable));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(dateRealization));
  }
}

void database::on_pushButton_AddRow_clicked() {
  QByteArray array;
  QBuffer buffer(&array);
  buffer.open(QIODevice::WriteOnly);
  QPixmap pix = ui->label_LoadImage->pixmap();
  pix.save(&buffer, "JPEG");
  insertValues(ui->lineEdit_ProjectName->text(), ui->spinBox_TaskNum->value(), ui->lineEdit_Schedulable->text(), ui->dateEdit->text(), array);
  qDebug() << "Fecha " << ui->dateEdit->text();
}

void database::on_tableWidget_cellClicked(int row, int column) {
  QPixmap& pix = pixmaps_assoc_[row];
  ui->label_LoadImage->resize(pix.width(), pix.height());
  ui->label_LoadImage->setPixmap(pix);
}

