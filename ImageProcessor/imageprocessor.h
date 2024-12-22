#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>

class ImageProcessor : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageProcessor(QWidget *parent = nullptr); // 使用 explicit 避免隐式转换
    ~ImageProcessor();

private slots:
    void showOpenFile();
    void zoomIn();
    void zoomOut();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);

    QLabel *imgWin;            // 用于显示图像的控件
    QWidget *central;          // 中央小部件
    QImage img;                // 存储加载的图像
    double scaleFactor;        // 缩放比例

    // 动作与菜单
    QAction *openFileAction;
    QAction *exitAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QMenu *fileMenu;           // 文件菜单
    QMenu *toolMenu;           // 工具菜单
};

#endif // IMAGEPROCESSOR_H
