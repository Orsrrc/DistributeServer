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

signals:
    void stringUpdated(const QString &str);

private slots:
    void sendMessage()
    {
        // Create a client socket
        clientSocket = new QTcpSocket(this);
        // Connect the client to the server
        clientSocket->connectToHost("192.168.0.108", 9800);
        if (!clientSocket->waitForConnected()) {
            qDebug() << "Failed to connect to server.";
        }
        qDebug() << message;
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
            else
            {
                qDebug() << "Message is empty.";
            }
        }
        else
        {
            qDebug() << "Not connected to server.";
        }
    }

    void updateString()
    {
        QString result;
        for (auto lineEdit : lineEdits)
        {
            if(!lineEdit->text().isEmpty())
            {
                result += lineEdit->text() + "\n";
            }
        }
        message = result;
        emit stringUpdated(result);
    }
    // 当下拉框选项改变时，清空所有输入框内容的槽函数
    void clearInputFields()
    {
        for (auto lineEdit : lineEdits) {
            lineEdit->clear();
        }
    }

    // Slot to update text box content based on combo box selection
    void updateTextBoxContent(int index) {
        QString content;
        switch(index) {
        case 0:
            content =
                "参数1:\n"
                "参数2:\n"
                "参数3:\n"
                "参数4:\n"
                "参数5:\n";
            break;
        case 1: //TOP_S
            content =
                "参数1:ShardNum   分片数量    默认:10\n"
                "参数2:SourceNum 资源数量    默认:2\n"
                "参数3:alpha           共识消耗量 默认:0.5\n";

            break;
        case 2: //Average
            content =
                "参数1:ShardNum   分片数量    默认:10\n"
                "参数2:SourceNum 资源数量    默认:2\n"
                "参数3:alpha           共识消耗量 默认:0.5\n";

            break;
        case 3://Dualascent
            content =
                "参数1:Max_iteration 最大迭代次数        默认:10000\n"
                "参数2:tol                                             默认:1e-5\n"
                "参数3:t_lambda        拉格朗日乘子步长 默认:0.1\n"
                "参数4:t_x                  决策变量x的步长  默认:0.1\n";
            break;
        case 4://Dualascentfl
            content =
                "参数1:Max_iteration 最大迭代次数        默认:10000\n"
                "参数2:tol                                             默认:1e-5\n"
                "参数3:t_lambda        拉格朗日乘子步长 默认:0.1\n"
                "参数4:epsilon                                      默认:0.1\n"
                "参数5:t_x_1               决策变量x1的步长 默认:0.1\n"
                "参数6:t_x_2               决策变量x2的步长 默认:0,1\n";
            break;
        case 5://Elastic
            content =
                "参数1:ShardNum   分片数量    默认:10\n"
                "参数2:SourceNum 资源数量    默认:2\n"
                "参数3:alpha           共识消耗量 默认:0.5\n"
                "参数4:RTX              出队奖励   默认:5\n"
                "参数5:V                  惩罚值      默认:0\n";
            break;
        case 6://Longest
            content =
                "参数1:\n"
                "参数2:\n"
                "参数3:\n"
                "参数4:\n"
                "参数5:\n";
            break;

        case 7: //Random
            content =
                "参数1:\n"
                "参数2:\n"
                "参数3:\n"
                "参数4:\n"
                "参数5:\n";
        default:
            content =
                "参数1:\n"
                "参数2:\n"
                "参数3:\n"
                "参数4:\n"
                "参数5:\n";
        }
        textLabel->setText(content);
    }

private:
    Ui::MainWindow *ui;
    QTcpSocket *clientSocket;
    QString message;
    QList<QLineEdit*> lineEdits;
    QComboBox *combo;
    QStackedWidget *stack;
    QLabel * textLabel;
};

#endif // MAINWINDOW_H
