#include "RTGraphicsScene.h"

#include <QDateTime>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QPaintEngine>
#include <QPainter>
#include <QPlastiqueStyle>
#include <QVBoxLayout>
#include <QDialog>

#include "glee/GLee.h"

#include <iostream>
using namespace std;

RTGraphicsScene::RTGraphicsScene(GraphicsView *pGraphicsView, QObject *parent) :
        QGraphicsScene(parent)
{
    m_pGraphicsView = pGraphicsView;

    //setup a FPS dialog window
    m_pFpsLabel = new QLabel(tr("FPS:"));

    QWidget *stats = createWidget(tr("stats"));
    stats->layout()->addWidget(m_pFpsLabel);

    addWidget(stats);

    //now that we have added all the windows we want, go through them all and position them correctly
    QPointF pos(10, 10);

    foreach (QGraphicsItem *item, items())
    {
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

        const QRectF rect = item->boundingRect();
        item->setPos(pos.x() - rect.x(), pos.y() - rect.y());
        pos += QPointF(0, 10 + rect.height());
    }

    initialize();
}

QWidget *RTGraphicsScene::createWidget(const QString &widgetTitle) const
{
    QWidget *widget = new QWidget(0, Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    widget->setStyle(new QPlastiqueStyle());
    widget->setWindowOpacity(0.5);
    widget->setWindowTitle(widgetTitle);
    widget->setLayout(new QVBoxLayout());

    return widget;
}

//Do the raytracing and draw it in the widget!
void RTGraphicsScene::draw()
{

}

void RTGraphicsScene::drawBackground(QPainter *painter, const QRectF &)
{
    //check for opengl errors
    GLenum error = glGetError();
    while (error != GL_NO_ERROR)
    {
        cout << "error: " << hex << error << dec << endl;
        error = glGetError();
    }

    if (painter->paintEngine()->type() != QPaintEngine::OpenGL && painter->paintEngine()->type() != QPaintEngine::OpenGL2)
    {
        cout << "PaintEnginer of incorrect type! (type " << painter->paintEngine()->type() << ")" << endl;
        return;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    draw();

    ++m_fpsCounter;

    glPopMatrix();
}

void RTGraphicsScene::initialize()
{
    bFullscreen = false;

    m_fpsCounter = 0;
    m_lastTimeUpdate = QDateTime::currentMSecsSinceEpoch();

    fTime = 0.0f;

    bPaused             = true;
}

void RTGraphicsScene::refresh()
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    if (currentTime - m_lastTimeUpdate > 1000)
    {
        m_lastTimeUpdate += 1000;

        QString num;
        num.setNum(m_fpsCounter);
        m_pFpsLabel->setText(num + tr(" fps"));
        m_fpsCounter = 0;
    }
}
