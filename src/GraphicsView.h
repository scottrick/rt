#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QResizeEvent>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView();

protected:
    void resizeEvent(QResizeEvent *event) {
                if (scene())
                    scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
                QGraphicsView::resizeEvent(event);
            }

signals:

public slots:

};

#endif // GRAPHICSVIEW_H
