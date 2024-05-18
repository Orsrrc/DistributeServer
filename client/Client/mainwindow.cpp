#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("分片许可链仿真模拟系统");
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建左右分割器
    QSplitter *splitter = new QSplitter(Qt::Horizontal, centralWidget);

    //////////////////////////////////////////left window//////////////////////////
    QWidget *leftWidget = new QWidget(splitter);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftWidget->setLayout(leftLayout);
    leftWidget->setStyleSheet("background-color: lightGray;");



    QHBoxLayout *comboBoxLayout = new QHBoxLayout(leftWidget);

    QLabel *label = new QLabel("资源分配算法:", this);

    QComboBox *comboBox = new QComboBox(this);
    comboBox->addItem("Top_S");
    comboBox->addItem("Average");
    comboBox->addItem("Dualascent");
    comboBox->addItem("Dualascentfl");
    comboBox->addItem("Elastic");
    comboBox->addItem("Longest");
    comboBox->addItem("Random");


    comboBoxLayout->addWidget(label);
    comboBoxLayout->addWidget(comboBox);
    comboBoxLayout->setSpacing(0); // Set spacing to 0
    leftLayout->addLayout(comboBoxLayout);

    connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::comboBoxIndexChanged);

    // Create input widgets for each option
    for (int i = 0; i < 7; ++i) {
        QVector<QPair<QLabel*, QLineEdit*>> optionInputWidgets;
        for (int j = 0; j < 5; ++j) {
            QLineEdit *input = new QLineEdit(this);
            optionInputWidgets.append(qMakePair(new QLabel(this), input));
           leftLayout->addWidget(optionInputWidgets.back().first);
             leftLayout->addWidget(optionInputWidgets.back().second);
            optionInputWidgets.back().first->hide(); // Initially hide all labels
            optionInputWidgets.back().second->hide(); // Initially hide all input widgets
        }
        inputWidgets.append(optionInputWidgets);
    }




    QPushButton *btn_submmit = new QPushButton("发送",this);
    // Connect the button's clicked signal to a slot
    connect(btn_submmit, &QPushButton::clicked, this, &MainWindow::sendMessage);
    leftLayout->addWidget(btn_submmit);


    /////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////

    // Create a client socket
    clientSocket = new QTcpSocket(this);
    // Connect the client to the server
    clientSocket->connectToHost("192.168.0.108", 9800);
    message = "hello server";
    if (!clientSocket->waitForConnected()) {
        qDebug() << "Failed to connect to server.";
    }

    /// /////////////////////////////////////////////



    //////////////////////right window///////////////////////////////////////////////////////////////////////
    QWidget *rightWidget = new QWidget(splitter);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    rightWidget->setLayout(rightLayout);
    rightWidget->setStyleSheet("background-color: gray;");

    // 创建四个按钮
    QToolBar *toolBar = new QToolBar("Toolbar", rightWidget);
    QPushButton *btn_vary_V = new QPushButton("Performance evaluation while varying parameter V");
    QPushButton *btn_performance_comparison = new QPushButton("Performance comparison with baseline algorithms.");
    QPushButton *btn_attack_all_shards = new QPushButton("Continued bursty-TX injection attack against all network shards");
    QPushButton *btn_attack_single_shard = new QPushButton("Drastic bursty-TX injection attack against a single network shard");
    toolBar->addWidget(btn_vary_V);
    toolBar->addWidget(btn_performance_comparison);
    toolBar->addWidget(btn_attack_all_shards);
    toolBar->addWidget(btn_attack_single_shard);

    // 创建堆叠窗口
    QStackedWidget *stackedWidget = new QStackedWidget(rightWidget);
    QWidget *win_vary_V = createWindow();
    QWidget *win_performance_comparison = createWindow();
    QWidget *win_attack_all_shards = createWindow();
    QWidget *win_attack_single_shard = createWindow();
    stackedWidget->addWidget(win_vary_V);
    stackedWidget->addWidget(win_performance_comparison);
    stackedWidget->addWidget(win_attack_all_shards);
    stackedWidget->addWidget(win_attack_single_shard);

    // 连接按钮的点击信号和堆叠窗口的切换槽函数
    connect(btn_vary_V, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(0); });
    connect(btn_performance_comparison, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(1); });
    connect(btn_attack_all_shards, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(2); });
    connect(btn_attack_single_shard, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(3); });

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
