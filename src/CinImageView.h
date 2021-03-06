#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QApplication>
#include <QtSql>
#include <QMainWindow>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QGraphicsView>
#include <QDir>
#include <QFormLayout>
#include <QSqlField>
#include <QStyleFactory>
#include <QMouseEvent>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QImage>
#include <QPaintEvent>
#include <QPixmapCache>
#include <QFileInfo>

#include <iostream>
#include <cstring>

#include "CinParamSet.h"

//! Manages the imageviewer and interactions on it.
/*!
 *  This class contains everything it needs to show the right image given the current
 *  parameter values. It is also responsible for controlling the mouse drag event, which 
 *  is another way of interacting and changing the images while exploring the database.
*/

class CinImageView : public QGraphicsView
{
    Q_OBJECT

public:
    CinImageView(QWidget *parent);
    
    void setParameters(CinParamSet *paramset) {mParamSet = paramset;}
    void setHorizontalParameter(const QString &h) {mCurHorParam = h;}
    void setVerticalParameter(const QString &v)   {mCurVerParam = v;}

    const QString &getHorizontalParameter() {return mCurHorParam;}
    const QString &getVerticalParameter()   {return mCurVerParam;}

    bool loadImage(const QString &path);
    void clear();


public slots:
    void onLoadImage(const QString &key, const QString &path);

protected:

    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent * event);

    QString mCurImage; /* the current image */
    CinParamSet *mParamSet=NULL;

private:
    int          mCurrentXloc;
    int          mCurrentYloc;
    int          mLastXloc=0;
    int          mLastYloc=0;
    const int    mSlidePixelHor=50;
    const int    mSlidePixelVer=50;
    float        mCurrentHor;
    float        mCurrentVer;
    QPixmapCache mCache;
    QString      mCurHorParam;
    QString      mCurVerParam;
};

#endif
