#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    DrawChessBoard();
    DrawChessItem();
    DrawHandChess();


    update(); //强制更新界面
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //获取鼠标点击位置
    qDebug() << event->pos();

    QPoint pt ; //定义点位
    pt.setX( (event->pos().x()) / MAX_X);
    pt.setY( (event->pos().y()) / MAX_Y);

    //判断棋子是否存在
    for (int i = 0; i < p_ChessItem.size(); i++) {
        ChessItem item = p_ChessItem[i];
        if(item._pt == pt)
        {
            return;   //如果存在就不做任何事情
        }
    }

    //如果不存在我们就要进行绘制 并且判断五子是否连接
    ChessItem item(pt, b_black);
    p_ChessItem.append(item);

    //统计四个点位是否连接
    int nLeft       = CounterNearItem(item, QPoint(-1,0));
    int nLeftUp     = CounterNearItem(item, QPoint(-1,-1));
    int nLeftDown   = CounterNearItem(item, QPoint(-1,1));
    int nRight      = CounterNearItem(item, QPoint(1,0));
    int nRithtUp    = CounterNearItem(item, QPoint(1,-1));
    int nRightDown  = CounterNearItem(item, QPoint(1,1));
    int nUp         = CounterNearItem(item, QPoint(0,-1));
    int nDown       = CounterNearItem(item, QPoint(0,1));

    if( (nLeft + nRight) >= 4 ||
            (nLeftUp + nRightDown) >= 4 ||
            (nUp + nDown) >= 4 ||
            (nRithtUp + nLeftDown) >= 4
            )
    {
        QString str = b_black ? "红飞赢了" : "方正赢了";
        QMessageBox::information(NULL, "GAME OVER", str, QMessageBox::Yes);
        p_ChessItem.clear();
        return;
    }
    qDebug() << "nLeft" << QString::number(nLeft);
    //该另一方下棋了
    b_black = !b_black;

    update();
}

void MainWindow::InitUi()
{
    this->resize((CHESS_C + 1)*MAX_X, (CHESS_R + 1)*MAX_Y);
    this->setMaximumSize((CHESS_C + 1)*MAX_X, (CHESS_R + 1)*MAX_Y);
    this->setMinimumSize((CHESS_C + 1)*MAX_X, (CHESS_R + 1)*MAX_Y);
    this->setWindowTitle("上美佳五子棋");

    b_black = false;
}

void MainWindow::DrawChessBoard()
{
    QPainter painter(this);//绘图工具
    painter.setRenderHint(QPainter::HighQualityAntialiasing,true); //防止棋盘变形
    painter.setPen(QPen(QColor(Qt::black),2));//给边框线颜色和大小
   // painter.setBrush(Qt::gray);//给棋盘格子颜色

    QPixmap pix("./2.jpg");
    QRect ret = QRect(0,0,(CHESS_C + 1)*MAX_X,(CHESS_R + 1)*MAX_Y);
    painter.drawPixmap(ret , pix);
    //painter.drawPixmap(0, 0 , pix);

    for(int i=0; i< CHESS_C;i++)//遍历绘制棋盘所有的格子
    {
        for(int j=0; j< CHESS_R; j++)
        {
            //绘制棋盘的格子
            painter.drawRect((i+0.5)*MAX_X,(j+0.5)*MAX_Y, MAX_X, MAX_Y);
        }
    }


}

void MainWindow::DrawHandChess()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));

    if(b_black)
    {
        painter.setBrush(Qt::black);
    }
    else
    {
        painter.setBrush(Qt::white);
    }
    //获取鼠标位置  圆的半径
    painter.drawEllipse(mapFromGlobal(QCursor::pos()), MAX_X/2, MAX_Y/2);

}

void MainWindow::DrawChessItem()
{
    //p_ChessItem

    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));


    //    //遍历棋子，它有就进行绘制，没有就不绘制
    for (int i = 0; i < p_ChessItem.size(); i++)
    {
        ChessItem item = p_ChessItem[i]; //把当前棋子的样式与位置赋值给棋子的这个类
        if(item._black)
        {
            painter.setBrush(Qt::black);
        }
        else
        {
            painter.setBrush(Qt::white);
        }
        DrawChessAtPoint(painter, item._pt);
    }
}

void MainWindow::DrawChessAtPoint(QPainter &painter, QPoint &point)
{
    //获取棋子的摆放位置
    QPoint ptCenter((point.x()+0.5)*MAX_X, (point.y()+0.5)*MAX_Y);
    painter.drawEllipse(ptCenter, MAX_X/2*0.9, MAX_Y/2*0.9);

}

int MainWindow::CounterNearItem(ChessItem item, QPoint pt)
{
    int nCount = 0;
    item._pt += pt;
    while(p_ChessItem.contains(item)){
        nCount++;
        item._pt += pt;
    }


    return nCount;
}

