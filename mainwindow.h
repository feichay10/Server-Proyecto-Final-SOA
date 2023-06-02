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

 private slots:
  void on_actionServer_On_triggered();
  void manageConnect();
  void clientInteraction();

  void on_actionOff_Server_triggered();

  void on_actionClose_Data_Base_triggered();

  private:
  Ui::MainWindow* ui;
  QTcpServer* server;
  std::forward_list<QTcpSocket*> connection_list;
};
#endif // MAINWINDOW_H
