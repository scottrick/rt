#ifndef RTWINDOW_H
#define RTWINDOW_H

#include <QtGui/QMainWindow>

class RTWindow : public QMainWindow
{
    Q_OBJECT

public:
    RTWindow(QWidget *parent = 0);
    ~RTWindow();
};

#endif // RTWINDOW_H
