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
#include <QFileDialog>
#include <QImage>

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

class database : public QMainWindow {
  Q_OBJECT

 public:
  explicit database(QWidget* parent = nullptr);
  explicit database();
  ~database();
  void insertValues(QString ip, QString projectName, int taskNumber, QString plannable, QString dateRealization, QByteArray image);
  void clearEverything();

 private slots:
  void on_pushButton_AddRow_clicked();

  void on_tableWidget_cellClicked(int row, int column);

  void on_pushButton_LoadDB_clicked();

 private:
  Ui::database* ui;
  QSqlDatabase mDatabase;
  QVector<QPixmap> pixmaps_assoc_;
  bool startDataBase(const QString& = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/pred_db_cheddarpp");
  bool loadTable();

};

#endif // DATABASE_H
