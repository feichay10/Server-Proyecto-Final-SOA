#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QMessageBox>
#include <QImage>
#include <QTextStream>
#include <QFileDialog>
#include <QBuffer>
#include <forward_list>
#include <QSpinBox>
#include "selectport.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 protected:
  void closeEvent(QCloseEvent* event) override;

 private slots:
  void on_actionServer_On_triggered();
  void manageConnect();
  void clientInteraction();
  void on_actionOff_Server_triggered();
  void on_actionClose_Data_Base_triggered();
  void on_actionSelect_the_port_to_server_triggered();

 private:
  Ui::MainWindow* ui;
  SelectPort* select_port_;
  QTcpServer* server;
  std::forward_list<QTcpSocket*> connection_list;
};
#endif // MAINWINDOW_H
