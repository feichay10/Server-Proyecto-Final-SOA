#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->actionServer_On->setEnabled(true); ///< We turn on the On buttom
  ui->actionOff_Server->setEnabled(false); ///< We turn off the Off buttom
  ui->actionClose_Data_Base->setEnabled(false); ///< We turn off the close_data_base buttom
  server = NULL;
}

MainWindow::~MainWindow() {
  delete ui;
}


void MainWindow::on_actionServer_On_triggered() {
  ///create socket, send some kind of response
  server = new QTcpServer();

  if (server->listen(QHostAddress::Any, 8080)) {
    connect(server, SIGNAL(newConnection()), this, SLOT(manageConnect()));
    ui->actionServer_On->setEnabled(false); ///< We turn off the On buttom
    ui->actionOff_Server->setEnabled(true); ///< We turn on the Off buttom
    QMessageBox::information(this, "Server is activated", "Waiting connections...");

  } else QMessageBox::critical(this, "Listening error", server->errorString());
}

void MainWindow::manageConnect() {
  while (server->hasPendingConnections()) {
    QTcpSocket* new_socket = server->nextPendingConnection();
    connection_list.push_front(new_socket);
    connect(new_socket, SIGNAL(readyRead()), this, SLOT(clientInteraction()));
    ui->clients_msgsEdit->insertPlainText("\nClient " + QString::number(new_socket->socketDescriptor()) + " connected...");
    QMessageBox::information(this, "New client", ("\nClient " + QString::number(new_socket->socketDescriptor()) + " connected..."));
    // connection_list.front()->write("Hola cliente"); //temporarily
  }
}

// // Abrir archivo de foto
//QString nameFile = QFileDialog::getOpenFileName(this, "Abrir imagen", QDir::rootPath(), "Imágenes (*.png *.jpg *.jpeg);;Cualquier archivo(*.*)");
//ui->lineEdit_image->setText(nameFile);
//QPixmap pixmap(ui->lineEdit_image->text());
// // set a scaled pixmap
//ui->imageLabel->resize(pixmap.width(), pixmap.height());
//ui->imageLabel->setPixmap(pixmap.scaled(pixmap.width(),pixmap.height(),Qt::KeepAspectRatio));

void MainWindow::clientInteraction() {
  QTcpSocket* client_conn = reinterpret_cast<QTcpSocket*>(sender());
  QByteArray message_from_client;

  while (client_conn->bytesAvailable() > 0)
    message_from_client = client_conn->readAll();

  if (message_from_client.toStdString() == "SEND_IMG") {
    client_conn->write("OK");
    client_conn->flush();
    client_conn->waitForBytesWritten();
    client_conn->waitForReadyRead();

    while (client_conn->bytesAvailable() > 0)
      message_from_client = client_conn->readAll();

    QImage image_from_client;
    bool delivery_success = image_from_client.loadFromData(message_from_client);

    if (delivery_success) {
      ui->lineEdit_client_number->setText("Client " + QString::number(client_conn->socketDescriptor()) + " sent this image:");
      QPixmap pixmap_image_client = QPixmap::fromImage(image_from_client);
      ui->label_to_show_image->resize(pixmap_image_client.width(), pixmap_image_client.height());
      ui->label_to_show_image->setPixmap(pixmap_image_client);

    } else
      QMessageBox::critical(this, "Error: Cannot be able to get the image", "The image from client " + QString::number(server->nextPendingConnection()->socketDescriptor()) + " has some problems to be read");

  } else if (message_from_client.toStdString() == "RECEIVE_IMG") {
    QString imagePath = QFileDialog::getOpenFileName(this, "Select image to send to client", QDir::homePath(), "Images (*.png *.jpg *.jpeg);;Any file(*.*)");

    if (!imagePath.isEmpty()) {
      QImage image_to_client(imagePath); ///< We store the image correctly from the file system
      QByteArray byteArrayImage;
      QBuffer bufferImage(&byteArrayImage);
      bufferImage.open(QIODevice::WriteOnly);
      image_to_client.save(&bufferImage, "JPEG"); ///< We store the image in the "bufferImage" as a "JPEG" to be sent to client
      client_conn->write(byteArrayImage);
      client_conn->waitForBytesWritten();
    }
  } else {
    QMessageBox::critical(this, "ERROR: Command to server is not recognized", "The client " + QString::number(client_conn->socketDescriptor()) + " wants to do an unknown action");
    client_conn->write("ERROR1");
    client_conn->waitForBytesWritten();
  }

  // client_conn->write("¿Pasó usted por casa?"); //temporarily
}

void MainWindow::on_actionOff_Server_triggered() {
  for(auto i : connection_list) {
    i->disconnect(); ///< We disconnect each socket before delete it
    delete i; ///< We delete each socket of server
  }

  connection_list.clear();
  delete server;
  server = NULL;

  if (!connection_list.empty())
    QMessageBox::critical(this, "Error: The task to clean the client's list failed", "The server had some problems to shut down, try again");

  ui->actionServer_On->setEnabled(true); ///< We turn on the On buttom
  ui->actionOff_Server->setEnabled(false); ///< We turn  the Off buttom
  QMessageBox::information(this, "Shutdown successful", "The server was turn off successful");
}

void MainWindow::on_actionClose_Data_Base_triggered() {
  ui->actionClose_Data_Base->setEnabled(false); ///< We turn on the close data base buttom
}

