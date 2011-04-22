#ifndef RTGRAPHICSSCENE_H
#define RTGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QtGlobal>

class QKeyEvent;
class QLabel;
class QMouseEvent;
class QPainter;

class GraphicsView;
class Scene;

static const unsigned int SCENE_HEIGHT  = 600;
static const unsigned int SCENE_WIDTH   = 800;

class RTGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit RTGraphicsScene(GraphicsView *pGraphicsView, QObject *parent = 0);
    ~RTGraphicsScene();

    bool            isFullscreen() { return bFullscreen; }

    void            drawBackground(QPainter *painter, const QRectF &);

    void            refresh();

protected:
    QDialog         *createDialog(const QString &windowTitle) const;
    QWidget         *createWidget(const QString &widgetTitle) const;

    void            keyPressEvent(QKeyEvent *pKeyEvent);

    void            mouseMoveEvent(QGraphicsSceneMouseEvent *pMouseEvent);

private:
    QLabel          *m_pFpsLabel;

    GraphicsView    *m_pGraphicsView;

    bool            bFullscreen;

    bool            bPaused;
    float           fTime;
    int             m_fpsCounter;
    qint64          m_lastTimeUpdate;

    void            draw();
    void            initialize();

    Scene           *m_pScene;

    void            *buffer;

signals:

public slots:

};

#endif // RTGRAPHICSSCENE_H
