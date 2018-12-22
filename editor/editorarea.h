#ifndef EDITORAREA_H
#define EDITORAREA_H

#include <iostream>
#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QResource>
#include <QBrush>
#include <QDir>
#include <QShortcut>
#include <QPainter>
#include <QTimer>
#include <QScrollArea>
#include <QMessageBox>
#include <QColor>
#include <QMouseEvent>
#include <QBitmap>
#include <QInputEvent>


#include "mediator.h"
#include "file_stage.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define HUD_HEIGHT 144
#define TILESIZE 64


class editorArea : public QWidget
{
    Q_OBJECT
public:
    explicit editorArea(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent * event);

private:
    QWidget *myParent;
    double zoom;
    int editor_selectedTileX, editor_selectedTileY;

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
};



#endif // EDITORAREA_H
