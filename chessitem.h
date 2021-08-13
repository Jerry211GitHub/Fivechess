#ifndef CHESSITEM_H
#define CHESSITEM_H

#include <QPoint>

class ChessItem
{
public:
    ChessItem(void);
    ChessItem(QPoint point, bool isBlack);

    bool operator == (const ChessItem &t1)const
    {
        return ((_pt == t1._pt) && (_black == t1._black));
    }

    QPoint _pt; //棋子的位置
    bool _black; //棋子的颜色
};

#endif // CHESSITEM_H
