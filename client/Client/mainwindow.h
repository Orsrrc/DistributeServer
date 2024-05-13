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
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
