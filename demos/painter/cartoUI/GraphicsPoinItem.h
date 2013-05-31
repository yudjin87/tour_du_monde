#ifndef GRAPHICSPOINITEM_H
#define GRAPHICSPOINITEM_H

#include <QtCore/QPointF>
#include <QtWidgets/QAbstractGraphicsShapeItem>

class GraphicsPoinItem : public QAbstractGraphicsShapeItem
{
public:
    GraphicsPoinItem(const QPointF &data);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    const QPointF &m_data;
};

#endif // GRAPHICSPOINITEM_H
