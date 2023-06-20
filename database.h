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
#include <QKeyEvent>
#include <QBuffer>
#include <QStandardPaths>
#include <QFileDialog>
#include <QImage>

namespace Ui {
class database;
}

class database : public QMainWindow {
  Q_OBJECT
  friend class MainWindow;

 public:
  explicit database(QWidget* parent = nullptr);
  explicit database();
  ~database();
  void insertValues(QString ip, QString projectName, int taskNumber, QString plannable, QString dateRealization, QByteArray image);

 protected:
  void keyPressEvent( QKeyEvent* event );

 private slots:

  void on_tableWidget_cellClicked(int row, int column);

  void on_pushButton_LoadDB_clicked();

  void on_pushButton_NewDB_clicked();

 private:
  Ui::database* ui;
  QSqlDatabase mDatabase;
  QVector<QPixmap> pixmaps_assoc_;
  bool startDataBase(const QString& = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/pred_db_cheddarpp");
  bool loadTable();

};

#endif // DATABASE_H
