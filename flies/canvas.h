#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QList>
#include <QPointF>
#include <QTimer>
#include <QImage>

const float INACCURACY = 50.;
const int ANIM_STEPS = 6;
const int VERTS_NUMBER = 24;
const int FLIES_NUMBER = 8;

class Canvas : public QWidget
{
    Q_OBJECT

    QList<QPointF> verts;
    QList<QPointF> allVerts;
    int vertIndex;
    int flyAllVertsIndexes[FLIES_NUMBER];
    int flyVertIndexes[FLIES_NUMBER];
    int flyStep[FLIES_NUMBER];
    QTimer vertRegenTimer;
    QTimer flyMoveTimer;
    int maxRadius;
    QImage flyImages[2];

    bool visibleCurve;

    bool fliesBetweenVerts(int vertIndex);
    void generateVerts();
    void interpolateAllVerts();
    bool longFromVerts(float x, float y, float distance);
    QPointF getRandomVertex();

public:
    Canvas(QWidget *parent = 0);
    ~Canvas();
    float distance(QPointF & p1, QPointF & p2);

protected:
    void paintEvent(QPaintEvent *);
    void drawFly(int flyAllVertsIndex, int flyNumber);
    void drawCurve(QPainter & p);
    /*void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);*/

public slots:
    void on_vertRegenTimer_timeout();
    void on_flyMoveTimer_timeout();
    void setVisibleCurve(bool visible)
    {
        visibleCurve = visible;
    }
    void setMaxRadius(int maxRadius)
    {
        this->maxRadius = maxRadius;
    }
};

#endif
