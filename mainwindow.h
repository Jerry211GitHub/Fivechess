#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QVector>
#include <QMessageBox>

#include "chessitem.h"

/*
 * QT的2D绘画
 * 1、画棋盘
 * 2、画鼠标上的棋子
 * 3、画棋盘上的棋子
 * 4、判断五子棋是否连接
 * QT的绘画工具
 * QPainter
 *  1、画线
 *  2、画图片
 *  3、画矩形，
 *  4、写字等
 * 虚函数：窗口绘制的方法
 * QPaintEvent()绘制界面
 * 鼠标事件：
 * MousePressEvent()
*/

#define CHESS_R 15    //最大的高度
#define CHESS_C 15    //最大的宽度
#define MAX_X 40
#define MAX_Y 40

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void InitUi();//初始化界面
    void DrawChessBoard(); //画棋盘
    void DrawHandChess();//画鼠标上的棋子
    void DrawChessItem();//绘制棋盘上的棋子
    void DrawChessAtPoint(QPainter &painter, QPoint &point); //画棋子的样式与位置

    int CounterNearItem(ChessItem item, QPoint pt); //判断棋子是否五子连接
private:
    Ui::MainWindow *ui;
    bool b_black; //定义棋子的颜色 默认为黑色

    QVector <ChessItem> p_ChessItem; //定义棋子个数
};
#endif // MAINWINDOW_H
