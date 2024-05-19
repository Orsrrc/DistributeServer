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
    // 设置分割器的大小
    splitter->setSizes(QList<int>() << 200 << 600);
    setCentralWidget(splitter);

    //////////////////////////////////////////left window/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    QWidget *leftWidget = new QWidget(splitter);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftWidget->setLayout(leftLayout);
    leftWidget->setStyleSheet("background-color: lightGray;");

    ///////////////////comboBox///////////////////////////////////////////////////
    QLabel *label = new QLabel("仿真:", this);
    // 创建下拉框和界面
    combo = new QComboBox(this);
    stack = new QStackedWidget(this);

    QStringList options = {"...",
                           "Performance evaluation while varying parameter V .",
                           "Performance comparison with baseline algorithms." ,
                           "Performance evaluation under the continued bursty-TX injection attack against all network shards.",
                           "Performance evaluation under the drastic bursty-TX injection attack against a single network shard."  };
    combo->addItems(options);

    // 添加第一个界面，无输入框
    QWidget *firstPage = new QWidget(stack);
    stack->addWidget(firstPage);

    for (int i = 1; i < options.size(); ++i) {
        QWidget *page = new QWidget(stack);
        QVBoxLayout *layout = new QVBoxLayout(page);

        for (int j = 0; j < 5; ++j) {
            QHBoxLayout *hLayout = new QHBoxLayout();
            QLabel *label = new QLabel("参数" + QString::number(j + 1) + ":", page);
            QLineEdit *lineEdit = new QLineEdit(page);
            hLayout->addWidget(label);
            hLayout->addWidget(lineEdit);
            layout->addLayout(hLayout);
            lineEdits.append(lineEdit);
        }
        stack->addWidget(page);
    }
    ///////////////////////////////////////////////////////////////////////////////////



    ////////////////////////////////////////////label//////////////////////////////////////////////////////

    textLabel = new QLabel(this);
    // Initialize text box content based on initial combo box selection
    updateTextBoxContent(0);

    ///////////////////////////////////////button////////////////////////////////////
    QPushButton *btn_submmit = new QPushButton("发送",this);
    // Connect the button's clicked signal to a slot
    connect(btn_submmit, &QPushButton::clicked, this, &MainWindow::sendMessage);
    leftLayout->addWidget(btn_submmit);
    /////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////connect/////////////////////////////////////////////
    // 连接信号和槽
    connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            stack, &QStackedWidget::setCurrentIndex);


    for (auto lineEdit : lineEdits) {
        connect(lineEdit, &QLineEdit::textChanged,
                this, &MainWindow::updateString);
    }

    // 连接信号和槽，下拉框选项改变时清空输入框内容
    connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::clearInputFields);


    // Connect combo box signal to slot
    connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::updateTextBoxContent);
    ///////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////Layout//////////////////////////////////////////////
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addWidget(label);
    labelLayout->addWidget(combo);

    QVBoxLayout *lineEditLayout = new QVBoxLayout(this);
    lineEditLayout->addLayout(labelLayout);
    lineEditLayout->addWidget(stack);

    leftLayout->addWidget(textLabel);
    leftLayout->addLayout(lineEditLayout);

    //////////////////////////////////////////////////////////////////////////////////////////////////

    /// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    //////////////////////right window////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    QWidget *rightWidget = new QWidget(splitter);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    rightWidget->setLayout(rightLayout);
    rightWidget->setStyleSheet("background-color: gray;");


    ///////////////////////button////////////////////////////////////////////////////////////////////////////////////////////////
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
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////windows//////////////////////////////////////////////////////////////////
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
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    /// //////////////////////////////////////////////connect/////////////////////////////////////////////////////////////////////
    // 连接按钮的点击信号和堆叠窗口的切换槽函数
    connect(btn_vary_V, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(0); });
    connect(btn_performance_comparison, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(1); });
    connect(btn_attack_all_shards, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(2); });
    connect(btn_attack_single_shard, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(3); });

    //////////////////////////////////////Layout///////////////////////////////////////////////////////////////
    // 将工具栏和堆叠窗口添加到右侧布局中
    rightLayout->addWidget(toolBar);
    rightLayout->addWidget(stackedWidget);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
