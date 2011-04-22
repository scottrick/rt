#include <QtGui/QApplication>
#include <QApplication>
#include <QGLWidget>
#include <QIcon>

#include "GraphicsView.h"
#include "RTGraphicsScene.h"

#include <iostream>
using namespace std;

bool                    bApplicationRunning     = true;
RTGraphicsScene         *pRTScene               = 0;

void refreshAll();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGLWidget glWidget(QGLFormat(QGL::SampleBuffers));
    GraphicsView view;
    pRTScene = new RTGraphicsScene(&view);

    view.setWindowIcon(QIcon(":/planets/resources/icon.xpm"));

    view.setViewport(&glWidget);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view.setScene(pRTScene);

    view.move(80, 60);
    view.resize(800, 600);

    if (view.isFullScreen())
    {
        view.showFullScreen();
    }
    else
    {
        view.show();
    }

    while (bApplicationRunning)
    {
        a.processEvents();
        refreshAll();

        pRTScene->update();
    }

    delete pRTScene;
}

void refreshAll()
{
    pRTScene->refresh();
}
