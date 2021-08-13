#include "chessitem.h"

ChessItem::ChessItem(void)
{

}


ChessItem::ChessItem(QPoint point, bool isBlack)
{
    _pt = point;
    _black = isBlack;
}
