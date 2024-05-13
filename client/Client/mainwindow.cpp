#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建左右分割器
    QSplitter *splitter = new QSplitter(Qt::Horizontal, centralWidget);

    //////////////////////////////////////////left window//////////////////////////
    QWidget *leftWidget = new QWidget(splitter);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftWidget->setLayout(leftLayout);
    leftWidget->setStyleSheet("background-color: lightGray;");




    /////////////////////////////////////////////////////////////////////////////////





    //////////////////////right window///////////////////////////////////////////////////////////////////////
    QWidget *rightWidget = new QWidget(splitter);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    rightWidget->setLayout(rightLayout);
    rightWidget->setStyleSheet("background-color: gray;");

    // 创建四个按钮
    QToolBar *toolBar = new QToolBar("Toolbar", rightWidget);
    QPushButton *button1 = new QPushButton("Performance evaluation while varying parameter V");
    QPushButton *button2 = new QPushButton("Performance comparison with baseline algorithms.");
    QPushButton *button3 = new QPushButton("Continued bursty-TX injection attack against all network shards");
    QPushButton *button4 = new QPushButton("Drastic bursty-TX injection attack against a single network shard");
    toolBar->addWidget(button1);
    toolBar->addWidget(button2);
    toolBar->addWidget(button3);
    toolBar->addWidget(button4);

    // 创建堆叠窗口
    QStackedWidget *stackedWidget = new QStackedWidget(rightWidget);
    QWidget *window1 = createWindow();
    QWidget *window2 = createWindow();
    QWidget *window3 = createWindow();
    QWidget *window4 = createWindow();
    stackedWidget->addWidget(window1);
    stackedWidget->addWidget(window2);
    stackedWidget->addWidget(window3);
    stackedWidget->addWidget(window4);

    // 连接按钮的点击信号和堆叠窗口的切换槽函数
    connect(button1, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(0); });
    connect(button2, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(1); });
    connect(button3, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(2); });
    connect(button4, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(3); });

    // 将工具栏和堆叠窗口添加到右侧布局中
    rightLayout->addWidget(toolBar);
    rightLayout->addWidget(stackedWidget);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////



    // 设置分割器的大小
    splitter->setSizes(QList<int>() << 200 << 600);

    setCentralWidget(splitter);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QWidget *MainWindow::createWindow()
{
    QWidget *window = new QWidget();
    QGridLayout *gridLayout = new QGridLayout(window);
    // 创建四个 QChart 对象
    QChart *chart1 = new QChart();
    QChart *chart2 = new QChart();
    QChart *chart3 = new QChart();
    QChart *chart4 = new QChart();

    // 创建四个 QChartView 对象，并分别设置对应的 QChart
    QChartView *chartView1 = new QChartView(chart1);
    QChartView *chartView2 = new QChartView(chart2);
    QChartView *chartView3 = new QChartView(chart3);
    QChartView *chartView4 = new QChartView(chart4);

    gridLayout->addWidget(chartView1, 0, 0);
    gridLayout->addWidget(chartView2, 0, 2);
    gridLayout->addWidget(chartView3, 2, 0);
    gridLayout->addWidget(chartView4, 2, 2);

    // 添加一些示例数据
    QList<QPointF> data;
    for (int i = 0; i < 10; ++i) {
        data.append(QPointF(i, rand() % 100));
    }

    // 向每个图表添加一些示例数据
    QLineSeries *series1 = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();
    QLineSeries *series3 = new QLineSeries();
    QLineSeries *series4 = new QLineSeries();

    series1->append(data);
    series2->append(data);
    series3->append(data);
    series4->append(data);

    chart1->addSeries(series1);
    chart2->addSeries(series2);
    chart3->addSeries(series3);
    chart4->addSeries(series4);





    return window;
}
