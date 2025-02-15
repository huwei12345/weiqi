#include "aboutdialog.h"
#include "helppage.h"
#include "kata.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QMetaObject>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    goWidget = new GoBoardWidget(this);
    QObject::connect(this, &MainWindow::keyEventCaptured,
                         goWidget, &GoBoardWidget::onKeyPressEvent);
    //goWidget->show();
    mSoftSetting = new SettingPage;
    QLayout* layout = ui->panWidget->layout();
    layout->addWidget(goWidget);
    goWidget->setUITree(ui->pieceTree);
    recTool = new ImageRecognition;
    ui->toolButton_4->setCheckable(true);
    ui->toolButton_4->setChecked(false);
    // 设置上下文菜单策略为菜单触发
    ui->pieceTree->setContextMenuPolicy(Qt::CustomContextMenu);

    setWindowTitle(tr("围棋练习助手"));
    QIcon windowIcon(QPixmap(":/images/appIcon.jpg")); // 假设你的图标文件位于资源文件中或者项目目录下
    setWindowIcon(windowIcon);

    connect(goWidget, &GoBoardWidget::playerChange, this, &MainWindow::playerChange);
    blackPiece = QPixmap(":/images/black.png"); // 使用资源文件
    blackPiece = blackPiece.scaled(QSize(15,15), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    whitePiece = QPixmap(":/images/white.png"); // 使用资源文件
    whitePiece = whitePiece.scaled(QSize(15,15), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->pieceLabel->setPixmap(blackPiece);
    mRunAutoTimer = new QTimer(this);
    connect(mRunAutoTimer, &QTimer::timeout, this, [=]() {
        MainWindow::on_rightOne_clicked();
        mRunAutoTimer->start();
    } );
    mKata = new Kata(&goWidget->board);
    mKataThread = new QThread(this);
    mKataThread->start();
    connect(goWidget, &GoBoardWidget::getAIPiece, this, &MainWindow::getAIPiece);
    mKata->moveToThread(mKataThread);
    QMetaObject::invokeMethod(mKata, "startKata", Qt::QueuedConnection);
    connect(mKata, &Kata::getAIPieceSuccess, this, &MainWindow::getAIPieceSuccess);
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

// reset 仅清空形势判断残余
void MainWindow::on_toolButton_clicked()
{
    goWidget->clearJudge();
}


void MainWindow::on_pieceTree_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
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
    Q_UNUSED(previous);
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


void MainWindow::on_toolButton_19_clicked()
{
    goWidget->passOnePiece();
}

void MainWindow::Quit() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "退出", "你确定要退出吗？",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit(); // 如果用户点击“Yes”，则退出应用程序
    }
}

void MainWindow::playerChange(int currentPlayer)
{
    if (currentPlayer == BLACK) {
        qDebug() << "BLACK";
        ui->pieceLabel->setPixmap(blackPiece);
    }
    else if (currentPlayer == WHITE) {
        qDebug() << "WHITE";
        ui->pieceLabel->setPixmap(whitePiece);
    }
}

//退出
void MainWindow::on_toolButton_9_clicked()
{
    Quit();
}

void MainWindow::on_actiontuichu_triggered()
{
    Quit();
}


void MainWindow::on_actionguanyu_triggered()
{
    AboutDialog* dialog = new AboutDialog(this);
    dialog->exec();
}


void MainWindow::on_action_triggered()
{
    HelpPage* page = new HelpPage();
    page->show();
}


void MainWindow::on_actionsearchStep_triggered()
{
    //TODO: 或许可以放在定式集结果界面动态改变
    bool ok = false;
    int number = QInputDialog::getInt(this, tr("Enter stepNumber"),
                                      tr("请设置搜索定式后续的stepN步（1-1000）: "), 0, 1, 1000, 1, &ok);
    if (ok) {
        // 用户输入了数字，并且点击了OK
        goWidget->setSearchStep(number);
    }
}

void MainWindow::on_actioncunchu_triggered()
{
    emit on_storeBtn_clicked();
}


void MainWindow::on_actionduqu_triggered()
{
    emit on_LoadBtn_clicked();
}


void MainWindow::on_actionjudgeWin_triggered()
{
    emit on_WinBtn_clicked(true);
}


void MainWindow::on_actionnextStep_triggered()
{
    QString pos = QInputDialog::getText(this, tr("Enter Position"),
                                      tr("请输入下一步想下的位置 例[A13]: "));
    if (pos.size() == 0) {
        qDebug() << "input error";
        return;
    }
    if (!pos[0].isLetter()) {
        qDebug() << "input error";
        return;
    }
    pos[0] = pos[0].toUpper();
    int col = 0;
    if (pos[0] >= 'I') {
        col = pos[0].toLatin1() - 'A' - 1;
    }
    else {
        col = pos[0].toLatin1() - 'A';
    }
    QString tmp = pos.mid(1);
    if (tmp.size() == 0) {
        qDebug() << "input error";
        return;
    }
    int row = 19 - tmp.toInt();
    qDebug() << "input: row " << row << " col " << col << " " << showPiece(row, col);
    std::vector<std::vector<Piece>> ans;
    goWidget->remember(row, col, ans);
}


void MainWindow::on_actionundo_triggered()
{
    goWidget->undo();
}


void MainWindow::on_actionredo_triggered()
{
    goWidget->redo();
}


void MainWindow::on_actionjump_triggered()
{
    bool ok = false;
    int number = QInputDialog::getInt(this, tr("Enter step"),
                                      tr("请输入要跳转的手数: "), 0, 0, 1000, 1, &ok);
    if (ok) {
        goWidget->jumptoPiece(number);
    }
}


void MainWindow::on_actiondelete_triggered()
{
    auto item = ui->pieceTree->currentItem();
    //删除当前选中item
    if (item != nullptr) {
        goWidget->deleteSGFTreeItem(item);
    }
}

void MainWindow::on_actiontry_triggered(bool checked)
{
    qDebug() << (checked ? "start TryMode" : "close TryMode");
    goWidget->openTryMode(checked);
}

void MainWindow::on_actionxuandian_triggered(bool checked)
{
    if (checked) {
        goWidget->showXuanDian();
    }
    else {
        goWidget->clearXuanDian();
    }
}


void MainWindow::on_toolButton_22_clicked()
{
    auto item = ui->pieceTree->currentItem();
    //删除当前选中item
    if (item != nullptr) {
        goWidget->deleteSGFTreeItem(item);
    }
}


//仅试下模式可以使用摆黑摆白，或者以后有练习模式等
void MainWindow::on_BAlwaysBtn_clicked()
{
    if (goWidget->isTryMode()) {
        goWidget->setBAlways();
    }
    else {
        qDebug() << "not in TryMode";
    }
}


void MainWindow::on_WAlwaysBtn_clicked()
{
    if (goWidget->isTryMode()) {
        goWidget->setWAlways();
    }
    else {
        qDebug() << "not in TryMode";
    }
}


void MainWindow::on_toolButton_25_clicked()
{
    goWidget->setBWChange();
}


//悔棋
void MainWindow::on_RetractPiece_clicked()
{
//    if (goWidget->getCurrentPlayer() == BLACK) {
//    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "悔棋", "你同意悔棋吗？",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }
    //连退两步
    auto item = ui->pieceTree->currentItem();
    //删除当前选中item
    if (item != nullptr) {
        goWidget->deleteSGFTreeItem(item);
    }

    item = ui->pieceTree->currentItem();
    //删除当前选中item
    if (item != nullptr) {
        goWidget->deleteSGFTreeItem(item);
    }
}

//认输
void MainWindow::on_giveUpBtn_clicked()
{
    auto player = goWidget->getCurrentPlayer();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "认输", "你同意认输吗？",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }
    qDebug() << (player == BLACK ? "BLACK " : "WHITE ") << "Give Up";
    qDebug() << (player == BLACK ? "WHITE " : "BLACK ") << "Win!!!";
}


void MainWindow::on_toolButton_20_clicked()
{
    goWidget->ChangeShouShuState();
}


void MainWindow::on_autoPlay_clicked(bool checked)
{
    if (checked) {
        mRunAutoTimer->start(1000);
        ui->autoPlay->setText("■");
    }
    else {
        ui->autoPlay->setText("▶");
        mRunAutoTimer->stop();
    }
}

//setting
void MainWindow::on_setting_triggered()
{
    mSoftSetting->show();
}


void MainWindow::on_AIBtn_clicked()
{
    mKata->test();
}


void MainWindow::on_toolButton_11_clicked()
{
    if (goWidget->root != nullptr && goWidget->root->branches.size() != 0) {
        mKata->reInitKata(goWidget->root->branches[0]);
    }
}

bool MainWindow::getAIPiece(Piece piece, int color)
{
    //阻塞获取
    goWidget->forbidPut(true);
    bool ret = QMetaObject::invokeMethod(mKata, "getAIPiece", Qt::QueuedConnection, Q_ARG(Piece, piece), Q_ARG(int, color));
    return ret;
    //Piece *newPiece = mKata->getAIPiece(piece, color);
}

void MainWindow::getAIPieceSuccess(Piece* piece) {
    goWidget->waitAIFlag = false;
    goWidget->forbidPut(false);
    goWidget->putAIPiece(piece);
}


void MainWindow::on_AIPlayBtn_clicked(bool checked)
{
    goWidget->openAIMode(checked);
}

