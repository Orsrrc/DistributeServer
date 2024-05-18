#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QApplication>
#include <QSplitter>
#include <QWidget>
#include <QVBoxLayout>
#include <QToolBar>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QComboBox>
#include <QLineEdit>
#include <ClientSocket.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget* createWindow();

private slots:
    void comboBoxIndexChanged(int index)
    {
        // Hide all labels and input widgets
        for (auto optionInputs : inputWidgets) {
            for (auto pair : optionInputs) {
                pair.first->hide();
                pair.second->hide();
            }
        }

        // Show labels and input widgets for the selected option
        if (index >= 0 && index < inputWidgets.size()) {
            QVector<QPair<QLabel*, QLineEdit*>> optionInputs = inputWidgets[index];
            QString str = " ";
            switch (index)
            {
            case 0:
                 str = "Top_S";
                break;
            case 1:
                 str = "Average";
                break;
            case 2:
                 str = "Dualascent";
                break;
            case 3:
                 str = "Elastic";
                break;
            case 4:
                 str = "Longest";
                break;
            case 5:
                 str = "Random";
                break;
            default:
                break;
            }

            for (int i = 0; i < optionInputs.size(); ++i)
            {
                optionInputs[i].first->setText(QString("%1 参数 %2").arg(str).arg(i + 1));
                optionInputs[i].first->show();
                optionInputs[i].second->show();
            }
        }
    }

    void sendMessage() {
        if (clientSocket->state() == QAbstractSocket::ConnectedState) {
            // Get text from input line edit
            if (!message.isEmpty()) {
                // Send message to server
                QByteArray data = message.toUtf8();
                clientSocket->write(data);
                clientSocket->waitForBytesWritten();

                // Receive response from server
                if (clientSocket->waitForReadyRead()) {
                    qDebug() << "Response from server: " << clientSocket->readAll();
                }

                // Clear input line edit after sending message
                message = " ";
            }
            else {
                qDebug() << "Message is empty.";
            }
        } else {
            qDebug() << "Not connected to server.";
        }
    }


private:
    Ui::MainWindow *ui;
    QTcpSocket *clientSocket;
    QString message;
    QVector<QVector<QPair<QLabel*, QLineEdit*>>> inputWidgets;
};

#endif // MAINWINDOW_H
