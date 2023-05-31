#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}


void MainWindow::on_actionServer_On_triggered() {
  ///create socket, send some kind of response
  server = new QTcpServer();

  if (server->listen(QHostAddress::Any, 8080)) {
    connect(server, SIGNAL(newConnection()), this, SLOT(manConn()));
    QMessageBox::information(this, "Open", "Waiting connections...");

  } else QMessageBox::information(this, "Listening error", "The server could not initialize the client connection listening process");
}

void MainWindow::manConn() {
  while (server->hasPendingConnections()) {
    QTcpSocket* new_socket = server->nextPendingConnection();
    connection_list.push_front(new_socket);
    findChild<QTextEdit*>("clients_msgsEdit")->insertPlainText("\nClient " + QString::number(new_socket->socketDescriptor()) + " connected...");
    QMessageBox::information(this, "New client", ("\nClient " + QString::number(new_socket->socketDescriptor()) + " connected..."));
    //connect(new_socket, SIGNAL(readyRead()), this, SLOT());
  }
}
