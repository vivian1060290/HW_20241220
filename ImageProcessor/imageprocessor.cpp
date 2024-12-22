/*#include "ImageProcessor.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("影像處理"));

    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    imgWin = new QLabel();

    QPixmap *initPixmap = new QPixmap(300, 200);
    initPixmap->fill(QColor(255, 255, 255));
    imgWin->resize(300, 200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget(central);

    createActions();
    createMenus();
    createToolBars();
}

ImageProcessor::~ImageProcessor()
{}

void ImageProcessor::createActions()
{
    openFileAction = new QAction(QStringLiteral("打開文件&O"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("打開圖像文件"));
    //connect(openFileAction, SIGNAL(triggered()), this, SLOT(showOpenFile()));
    connect(openFileAction, &QAction::triggered, this, &ImageProcessor::showOpenFile);

    exitAction = new QAction(QStringLiteral("退出&Q"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出應用程序"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void ImageProcessor::createMenus()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案&F"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);
}

void ImageProcessor::createToolBars()
{
    // 可擴展的工具欄功能
}

void ImageProcessor::loadFile(QString filename)
{
    qDebug() << "Loading file:" << filename;

    if (!img.load(filename)) {
        qDebug() << "Failed to load image:" << filename;
        QMessageBox::warning(this, QStringLiteral("錯誤"), QStringLiteral("無法加載圖像檔案！"));
        return;
    }

    imgWin->setPixmap(QPixmap::fromImage(img));
    imgWin->adjustSize(); // 確保控件尺寸正確
}

void ImageProcessor::showOpenFile()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    QStringLiteral("打開文件"),
                                                    QString(),
                                                    "PNG (*.png);;BMP (*.bmp);;JPEG (*.jpg *.jpeg)");

    if (!filename.isEmpty()) {
        QString nativeFilename = QDir::toNativeSeparators(filename);
        loadFile(nativeFilename);
    }
}
*/
#include "ImageProcessor.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QToolBar>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("影像處理"));

    // 初始化中央小部件
    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    imgWin = new QLabel();

    // 預設初始化一個空白圖像
    QPixmap *initPixmap = new QPixmap(300, 200);
    initPixmap->fill(QColor(255, 255, 255));
    imgWin->resize(300, 200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget(central);

    // 初始化縮放比例
    scaleFactor = 1.0;

    // 建立動作、菜單與工具列
    createActions();
    createMenus();
    createToolBars();
}

ImageProcessor::~ImageProcessor()
{}

void ImageProcessor::createActions()
{
    // 打開文件
    openFileAction = new QAction(QStringLiteral("打開文件(&O)"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("打開圖像文件"));
    connect(openFileAction, &QAction::triggered, this, &ImageProcessor::showOpenFile);

    // 退出應用
    exitAction = new QAction(QStringLiteral("退出(&Q)"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出應用程序"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    // 放大
    zoomInAction = new QAction(QStringLiteral("放大(&L)"), this);
    zoomInAction->setShortcut(tr("Ctrl+L"));
    zoomInAction->setStatusTip(QStringLiteral("放大圖像"));
    connect(zoomInAction, &QAction::triggered, this, &ImageProcessor::zoomIn);

    // 縮小
    zoomOutAction = new QAction(QStringLiteral("縮小(&D)"), this);
    zoomOutAction->setShortcut(tr("Ctrl+D"));
    zoomOutAction->setStatusTip(QStringLiteral("縮小圖像"));
    connect(zoomOutAction, &QAction::triggered, this, &ImageProcessor::zoomOut);
}

void ImageProcessor::createMenus()
{
    // 檔案菜單
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案(&F)"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);

    // 工具菜單
    toolMenu = menuBar()->addMenu(QStringLiteral("工具(&T)"));
    toolMenu->addAction(zoomInAction);
    toolMenu->addAction(zoomOutAction);
}

void ImageProcessor::createToolBars()
{
    // 工具列
    QToolBar *toolBar = addToolBar(QStringLiteral("工具"));
    toolBar->addAction(openFileAction);
    toolBar->addAction(zoomInAction);
    toolBar->addAction(zoomOutAction);
}

void ImageProcessor::loadFile(QString filename)
{
    qDebug() << "Loading file:" << filename;

    if (!img.load(filename)) {
        qDebug() << "Failed to load image:" << filename;
        QMessageBox::warning(this, QStringLiteral("錯誤"), QStringLiteral("無法加載圖像檔案！"));
        return;
    }

    imgWin->setPixmap(QPixmap::fromImage(img));
    imgWin->adjustSize(); // 確保控件尺寸正確
    scaleFactor = 1.0;    // 重置縮放比例
}

void ImageProcessor::showOpenFile()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    QStringLiteral("打開文件"),
                                                    QString(),
                                                    "PNG (*.png);;BMP (*.bmp);;JPEG (*.jpg *.jpeg)");

    if (!filename.isEmpty()) {
        QString nativeFilename = QDir::toNativeSeparators(filename);
        loadFile(nativeFilename);
    }
}

void ImageProcessor::zoomIn()
{
    scaleFactor *= 1.25; // 每次放大 25%
    imgWin->resize(imgWin->size() * 1.25);
}

void ImageProcessor::zoomOut()
{
    scaleFactor *= 0.8; // 每次縮小 20%
    imgWin->resize(imgWin->size() * 0.8);
}
