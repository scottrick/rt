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
#include "Scene.h"
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

RTGraphicsScene::~RTGraphicsScene()
{
    if (m_pScene)
    {
        delete m_pScene;
        m_pScene = 0;
    }
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
    if (m_pScene->GetEye()->IsUpdateNeeded())
    {
        updateRays();
        m_pScene->GetEye()->SetUpdateNeeded(false);
    }
    shootRays();

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
    m_pScene = new Scene("../Scenes/test.txt");
    m_pScene->Print();

    bFullscreen = false;

    m_fpsCounter = 0;
    m_lastTimeUpdate = QDateTime::currentMSecsSinceEpoch();

    fTime = 0.0f;

    bPaused = true;

    cout << "initalizing buffer..." << endl;
    buffer = malloc(sizeof(GLubyte) * 3 * SCENE_HEIGHT * SCENE_WIDTH);

    int offset = 0;

    for (int x = 0; x < SCENE_WIDTH; ++x)
    {
        for (int y = 0; y < SCENE_HEIGHT; ++y)
        {
            offset = (y * SCENE_WIDTH * 3) + (x * 3);

            if (x == y || abs(x - y) == 1)
            {
                *((GLubyte *)((GLubyte *)buffer + offset + 0)) = 255;
                *((GLubyte *)((GLubyte *)buffer + offset + 1)) = 255;
                *((GLubyte *)((GLubyte *)buffer + offset + 2)) = 255;
            }
            else
            {
                *((GLubyte *)((GLubyte *)buffer + offset + 0)) = (GLubyte)GenerateRandomUnsignedInt(0, 255);
                *((GLubyte *)((GLubyte *)buffer + offset + 1)) = (GLubyte)GenerateRandomUnsignedInt(0, 255);
//                *((GLubyte *)((GLubyte *)buffer + offset + 2)) = (GLubyte)GenerateRandomUnsignedInt(0, 255);
                *((GLubyte *)((GLubyte *)buffer + offset + 2)) = 255;
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

void RTGraphicsScene::shootRays()
{
    RAY *pRay = 0;
    INTERSECTION *pIntersection = 0;
    int offset = 0;

    for (int x = 0; x < SCENE_WIDTH; ++x)
    {
        for (int y = 0; y < SCENE_HEIGHT; ++y)
        {
            offset = (y * SCENE_WIDTH * 3) + (x * 3);

            pRay = &(m_Rays[x][y]);

//            cout << "shooting ray (" << x << ", " << y << ")" << endl;

            pIntersection = m_pScene->findIntersection(pRay);

            if (pIntersection)
            {
                COLOR32 *pDiffuseColor = pIntersection->object->GetMaterial().GetDiffuseColor();

//                cout << "found an intersection with 0x" << hex << (unsigned int)pIntersection->object << dec << endl;

                *((GLubyte *)((GLubyte *)buffer + offset + 0)) = pDiffuseColor->r;
                *((GLubyte *)((GLubyte *)buffer + offset + 1)) = pDiffuseColor->g;
                *((GLubyte *)((GLubyte *)buffer + offset + 2)) = pDiffuseColor->b;

                delete pIntersection; //clean up
            }
            else
            {
                *((GLubyte *)((GLubyte *)buffer + offset + 0)) = 0;
                *((GLubyte *)((GLubyte *)buffer + offset + 1)) = 0;
                *((GLubyte *)((GLubyte *)buffer + offset + 2)) = 0;
            }
        }
    }
}

void RTGraphicsScene::updateRays()
{
    //THE eye look dir and position aren't used for anything yet!
    Eye *pEye = m_pScene->GetEye();

    float xFoV = pEye->GetFoV() * 3.141592654f / 180.0f; //is in degrees, so we have to convert to radians!

    cout << "FoV X " << pEye->GetFoV() << endl;
    cout << "FoV X rad " << xFoV << endl;

    float yFoV = ((float)SCENE_HEIGHT / (float)SCENE_WIDTH) * xFoV;

    cout << "FoV Y rad " << yFoV << endl;

    float tanXfov = tan(xFoV);
    float tanYfov = tan(yFoV);

    float rayX;
    float rayY;

    for (int x = 0; x < SCENE_WIDTH; ++x)
    {
        rayX = (2.0f * x - SCENE_WIDTH) / SCENE_WIDTH * tanXfov;

//        float theta = xFoV * (float)(x - (SCENE_WIDTH / 2)) / (float)SCENE_WIDTH;
//        cout << "x Theta " << theta << endl;
//        rayX = -1.0f / tan(theta);

        for (int y = 0; y < SCENE_HEIGHT; ++y)
        {
            rayY = (2.0f * y - SCENE_HEIGHT) / SCENE_HEIGHT * tanYfov;

//            theta = yFoV * ((float)y - ((float)SCENE_HEIGHT / 2.0f)) / (float)SCENE_HEIGHT;
//            rayY = -1.0f / tan(theta);

            //just assuming the eye is at the origin, and looking in the negative Z direction for now
            m_Rays[x][y].vStart.Set(0.0f, 0.0f, 0.0f);
            m_Rays[x][y].vDirection.Set(rayX, rayY, -1.0f);
//            m_Rays[x][y].vDirection.Normalize();

//            m_Rays[x][y].Print();
        }
    }
}
