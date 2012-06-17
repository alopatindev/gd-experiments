#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QList>
#include <QPointF>
#include <QTimer>
#include <QImage>

const float INACCURACY = 50.;
const int ANIM_STEPS = 6;

class Canvas : public QWidget
{
    Q_OBJECT

    QList<QPointF> verts;
    QList<QPointF> allVerts;
    int vertIndex;
    int *flyAllVertsIndexes;
    int *flyVertIndexes;
    int *flyStep;
    QTimer vertRegenTimer;
    QTimer flyMoveTimer;
    int maxRadius;
    QImage flyImages[2];

    int vertsNumber;
    int fliesNumber;

    bool visibleCurve;

    bool fliesBetweenVerts(int vertIndex);
    void generateVerts(bool regen = false);
    void interpolateAllVerts();
    bool longFromVerts(float x, float y, float distance);
    void installFlies();
    QPointF getRandomVertex();

public:
    Canvas(QWidget *parent = 0);
    ~Canvas();
    float distance(QPointF & p1, QPointF & p2);

protected:
    void paintEvent(QPaintEvent *);
    void drawFly(int flyAllVertsIndex, int flyNumber);
    void drawCurve(QPainter & p);

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
    void setVertsNumber(int vertsn)
    {
        vertsNumber = vertsn;
        fliesNumber = vertsn / 3;
        installFlies();

        QString str = QString("(%1 flies)").arg(fliesNumber);
        emit fliesNumberChanged(str);
    }
signals:
    void fliesNumberChanged(QString text);
};

#endif
