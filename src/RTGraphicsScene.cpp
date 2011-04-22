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

#include "GraphicsView.h"
#include "globals.h"
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
    glDrawPixels(SCENE_WIDTH, SCENE_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, buffer);
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

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    //don't clear depth, since we aren't actually doing much opengl stuff
    glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    draw();

    ++m_fpsCounter;
}

void RTGraphicsScene::keyPressEvent(QKeyEvent *pKeyEvent)
{
    //cout << "key=" << pKeyEvent->key() << endl;

    switch (pKeyEvent->key())
    {
    case 112: // 'p' and 'P'
    case 80:
        bPaused = !bPaused;
        break;

    case 'C':
    case 'c': //CTRL + C to quit
        if (pKeyEvent->modifiers() == Qt::ControlModifier)
        {
            exit(1);
        }
        break;
    case 'f':
    case 'F':
        if (bFullscreen)
        {
            m_pGraphicsView->move(80, 60);
            m_pGraphicsView->resize(800, 600);
        }
        else
        {
            m_pGraphicsView->showFullScreen();
        }

    default:

        break;
    }
}

void RTGraphicsScene::initialize()
{
    bFullscreen = false;

    m_fpsCounter = 0;
    m_lastTimeUpdate = QDateTime::currentMSecsSinceEpoch();

    fTime = 0.0f;

    bPaused             = true;

    cout << "initalizing buffer..." << endl;
    buffer = malloc(sizeof(GLubyte) * 3 * SCENE_HEIGHT * SCENE_WIDTH);

    unsigned int offset = 0;

    for (int x = 0; x < SCENE_WIDTH; ++x)
    {
        for (int y = 0; y < SCENE_HEIGHT; ++y)
        {
            offset = (y * SCENE_WIDTH * 3) + (x * 3);

            if (x == y || abs(x - y) == 1)
            {
                *((GLubyte *)(buffer + offset + 0)) = 255;
                *((GLubyte *)(buffer + offset + 1)) = 255;
                *((GLubyte *)(buffer + offset + 2)) = 255;
            }
            else
            {
                *((GLubyte *)(buffer + offset + 0)) = (GLubyte)GenerateRandomUnsignedInt(0, 255);
                *((GLubyte *)(buffer + offset + 1)) = (GLubyte)GenerateRandomUnsignedInt(0, 255);
                *((GLubyte *)(buffer + offset + 2)) = (GLubyte)GenerateRandomUnsignedInt(0, 255);
    //            *((GLubyte *)(buffer + offset + 2)) = 255;
            }
        }
    }

    cout << "finished creating buffer!" << endl;
}

void RTGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *pMouseEvent)
{
    QGraphicsScene::mouseMoveEvent(pMouseEvent);

    if (pMouseEvent->isAccepted())
    {
        return;
    }

//    if (pMouseEvent->buttons() & Qt::LeftButton) {
//        const QPointF delta = pMouseEvent->scenePos() - pMouseEvent->lastScenePos();

//        if (delta.y() || delta.x())
//        { //make sure it actually changed before we rotate
//            Vector3 axis = Vector3(-delta.y(), -delta.x(), 0.0f);
//            Matrix rot = Matrix();
//            rot.SetRotation(axis, sqrt((float)abs(delta.x()) + (float)abs(delta.y())));

//            rotation.RotateBy(rot);
//        }

//        pMouseEvent->accept();
//    }
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
