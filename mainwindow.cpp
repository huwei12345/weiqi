#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    goWidget = new GoBoardWidget(this);
    QObject::connect(this, &MainWindow::keyEventCaptured,
                         goWidget, &GoBoardWidget::onKeyPressEvent);
    //goWidget->show();
    QLayout* layout = ui->panWidget->layout();
    layout->addWidget(goWidget);
    goWidget->setUITree(ui->pieceTree);
    recTool = new ImageRecognition;
    ui->toolButton_4->setCheckable(true);
    ui->toolButton_4->setChecked(false);
    // 设置上下文菜单策略为菜单触发
    ui->pieceTree->setContextMenuPolicy(Qt::CustomContextMenu);

    setWindowTitle("围棋练习助手");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showSetupInfo(std::map<std::string, std::string> setupInfo)
{
    //ui->lineEdit;
    QString str;
    for (auto info : setupInfo) {
        str += QString::fromStdString(info.first + " : " + info.second + "  ");
    }
    ui->textEdit->append(str);
}


void MainWindow::on_LoadBtn_clicked()
{
    // 弹出文件选择对话框
    /*
            tr("Open Image"),
            "",
            tr("Images (*.png *.jpg *.jpeg *.bmp *.gif);;All Files (*)"));
    */
    QString fileName = QFileDialog::getOpenFileName(this,
                        tr("Open File"),
                        "",
                        tr("All Files (*);;Text Files (*.txt)"));
    //D:/easybcd.zip
    if (!fileName.isEmpty()) {
        qDebug() << "Selected file:" << fileName;
    } else {
        qDebug() << "No file selected.";
        return;
    }
    bool ret = goWidget->readSGF(fileName.toStdString());
    if (ret) {
        // 设置滑块的范围
        ui->horizontalSlider->setMinimum(0);  // 设置最小值
        qDebug() << " allNumber " << goWidget->allNumber;
        ui->horizontalSlider->setMaximum(goWidget->allNumber);  // 设置最大值
        ui->horizontalSlider->setSingleStep(1);
        ui->horizontalSlider->setValue(goWidget->allNumber);
        showSetupInfo(goWidget->setupInfo);
    }
}


void MainWindow::on_storeBtn_clicked()
{
    // 打开文件对话框，选择保存的文件位置和文件名
    QString fileName = QFileDialog::getSaveFileName(
        this, "保存棋谱", "", "SGF Files (*.sgf);;All Files (*)");

    if (fileName.isEmpty()) {
        // 如果没有选择文件名，则返回
        return;
    }

    // 确保文件扩展名是 .sgf
    if (!fileName.endsWith(".sgf", Qt::CaseInsensitive)) {
        fileName += ".sgf";
    }
    goWidget->saveSGF(fileName.toStdString());
}


void MainWindow::on_WinBtn_clicked()
{
    goWidget->calculateScore();
}

void MainWindow::on_clearBtn_clicked()
{
    goWidget->clear();
}


void MainWindow::on_judgeBtn_clicked(bool checked)
{
    qDebug() << (checked ? "open Judge" : "close Judge");
    //auto p = goWidget->calculateScore2(checked);
    if (checked) {
        goWidget->r();
    }
    else {
        goWidget->v();
    }
    //qDebug() << "black " << p.first << " white " << p.second;
}

// reset
void MainWindow::on_toolButton_clicked()
{
    goWidget->clearJudge();
}


void MainWindow::on_pieceTree_itemClicked(QTreeWidgetItem *item, int column)
{
    TreeData data = item->data(0, 1).value<TreeData>();
    auto p = data.node.lock();
    qDebug() << p->moveNum;
    goWidget->jumptoPiece(p);
}



void MainWindow::on_toolButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                        tr("Open File"),
                        "",
                        tr("All Files (*);;Text Files (*.txt)"));
    //D:/easybcd.zip
    if (!fileName.isEmpty()) {
        qDebug() << "Selected file:" << fileName;
    } else {
        qDebug() << "No file selected.";
        return;
    }
    goWidget->loadDingShiBook(fileName.toStdString());
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    int currentValue = ui->horizontalSlider->value();
    qDebug() << "from " << currentValue << "jumpto " << value;
    goWidget->jumptoPiece(value);
}


void MainWindow::on_Begin_clicked()
{
    ui->horizontalSlider->setValue(0);
}

void MainWindow::on_End_clicked()
{
    ui->horizontalSlider->setValue(goWidget->allNumber);
}

void MainWindow::on_leftOne_clicked()
{
    int currentValue = ui->horizontalSlider->value() - 1;
    if (currentValue >= 0 && currentValue <= goWidget->allNumber) {
        qDebug() << "from " << ui->horizontalSlider->value() << "jumpto " << currentValue;
        ui->horizontalSlider->setValue(currentValue);
    }
}

void MainWindow::on_rightOne_clicked()
{
    int currentValue = ui->horizontalSlider->value() + 1;
    if (currentValue >= 0 && currentValue <= goWidget->allNumber) {
        qDebug() << "from " << ui->horizontalSlider->value() << "jumpto " << currentValue;
        ui->horizontalSlider->setValue(currentValue);
    }
}

void MainWindow::on_leftFive_clicked()
{
    int currentValue = ui->horizontalSlider->value() - 5;
    if (currentValue >= 0 && currentValue <= goWidget->allNumber) {
        qDebug() << "from " << ui->horizontalSlider->value() << "jumpto " << currentValue;
        ui->horizontalSlider->setValue(currentValue);
    }
}

void MainWindow::on_rightFive_clicked()
{
    int currentValue = ui->horizontalSlider->value() + 5;
    if (currentValue >= 0 && currentValue <= goWidget->allNumber) {
        qDebug() << "from " << ui->horizontalSlider->value() << "jumpto " << currentValue;
        ui->horizontalSlider->setValue(currentValue);
    }
}

//redo undo也可以加入进度条显示，但要考虑是否是主分支


void MainWindow::on_pushButton_clicked()
{
    QString str = ui->pieceEdit->text();
    int num = str.toInt();
    if (num >= 0 && num <= goWidget->allNumber) {
        qDebug() << "from " << ui->horizontalSlider->value() << "jumpto " << num;
        ui->horizontalSlider->setValue(num);
    }
}


//目前只是从剪贴板复制，不具备真实截图功能，需要外部截图。
void MainWindow::on_toolButton_27_clicked()
{
    // 获取剪贴板内容
    QClipboard *clipboard = QApplication::clipboard();
    QImage image = clipboard->image();  // 获取剪贴板中的图像

    if (!image.isNull()) {
        // 显示图片
        //ui->ImageLabel->setPixmap(QPixmap::fromImage(image));
        // 创建 QLabel 来显示图片
            QLabel *label = new QLabel;
            // 加载图片
            QPixmap r = QPixmap::fromImage(image);
            label->setPixmap(r);
            // 设置窗口标题
            label->setWindowTitle("Image Display");
            // 调整 QLabel 以适应图片大小
            label->setAlignment(Qt::AlignCenter);
            label->setScaledContents(true);
            // 根据图片大小调整窗口尺寸
            label->resize(r.size());
            // 显示窗口
            label->show();
        recTool->recogniton2(image, goWidget->board);
    } else {
        //ui->ImageLabel->setText("No image in clipboard");
        QLabel *label = new QLabel;
        // 加载图片
        label->setText("No image in clipboard");
        label->setWindowTitle("Image Display");
        // 显示窗口
        label->resize(QSize(400, 400));
        label->show();
    }
}

//将当前界面的落子顺序解析入库
void MainWindow::on_addDSBtn_clicked()
{
    bool ret = goWidget->addDSintoBook();
    if (ret) {
        std::string bookPath = "";
        ret = goWidget->storeDingShiBook(bookPath);
        if (ret) {
            qDebug() << "insert DingShi success";
        }
    }
}


void MainWindow::on_pieceTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if (current) {
        // 输出当前选中的项的文本
        qDebug() << "Current selected item: " << current->text(0);
        TreeData data = current->data(0, 1).value<TreeData>();
        auto p = data.node.lock();
        qDebug() << p->moveNum;
        goWidget->jumptoPiece(p);
    }
}


void MainWindow::on_pieceTree_customContextMenuRequested(const QPoint &pos)
{
    // 创建右键菜单
    QMenu contextMenu;

    // 获取右键点击位置对应的item
    QTreeWidgetItem *item = ui->pieceTree->itemAt(pos);
    if (item) {
        // 添加菜单项
        QAction *action1 = contextMenu.addAction("delete");

        // 连接菜单项的动作
        connect(action1, &QAction::triggered, this, [this, item]() {
            goWidget->deleteSGFTreeItem(item);
        });
        // 弹出菜单
        contextMenu.exec(ui->pieceTree->mapToGlobal(pos));
    }
}


void MainWindow::on_toolButton_4_clicked(bool checked)
{
    qDebug() << (checked ? "start TryMode" : "close TryMode");
    goWidget->openTryMode(checked);
}


void MainWindow::on_WinBtn_clicked(bool checked)
{
    qDebug() << (checked ? "start calc" : "close calc");
    if (checked) {
        goWidget->calculateScore();
    }
    else {
        goWidget->clearCalcResult();
    }
}

