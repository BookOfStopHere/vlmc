#include <QtDebug>
#include "GraphicsCursorItem.h"

GraphicsCursorItem::GraphicsCursorItem( int height, const QPen& pen )
        : m_pen( pen ), m_moveRequired( false )
{
    setFlags( QGraphicsItem::ItemIgnoresTransformations | QGraphicsItem::ItemIsMovable );
    setCursor( QCursor( Qt::SizeHorCursor ) );
    setZValue( 100 );

    m_boundingRect = QRectF( -2, 0, 3, height );
}

QRectF GraphicsCursorItem::boundingRect() const
{
    return m_boundingRect;
}

void GraphicsCursorItem::paint( QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* )
{
    painter->setPen( m_pen );
    painter->drawLine( 0, 0, 0, m_boundingRect.height() );
}

QVariant GraphicsCursorItem::itemChange( GraphicsItemChange change, const QVariant& value )
{
    if ( change == ItemPositionChange )
    {
        qreal posX = value.toPointF().x();
        if ( posX < 0 ) posX = 0;
        return QPoint( ( int ) posX, ( int ) pos().y() );
    }
    if ( change == ItemPositionHasChanged )
    {
        if ( m_moveRequired == false )
            emit cursorPositionChanged( ( qint64 ) pos().x() );
        else
            m_moveRequired = false;
    }
    return QGraphicsItem::itemChange( change, value );
}

void GraphicsCursorItem::setCursorPos( int position )
{
    setPos( position, pos().y() );
    m_moveRequired = true;
}

void    GraphicsCursorItem::updateCursorPos( qint64 position )
{
    setCursorPos( (qint64) position );
}

void GraphicsCursorItem::setHeight( int height )
{
    m_boundingRect.setHeight( height );
    update();
}