#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog *loginDialog = new LoginDialog();
    loginDialog->showMinimized();


    /*
    // Create a TCP socket
    QTcpSocket socket;

    // Connect to the server
    socket.connectToHost("192.168.0.106", 9800); // Change the IP address and port to match your server

    // Check if the connection is successful
    if(socket.waitForConnected()) {
        qDebug() << "Connected to server";

        // Send data to the server
        QString message = "Hello from client";
        qDebug() << "Sending message: " << message;
        socket.write(message.toUtf8());

        // Wait for the data to be written
        socket.waitForBytesWritten();

        // Close the connection
        socket.close();
    } else {
        qDebug() << "Failed to connect to server:" << socket.errorString();
    }
    */

    return a.exec();
}
