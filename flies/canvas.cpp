#include "canvas.h"
#include "interpolation.h"
#include <QPainter>
#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace Interpolation;

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    flyImages[0].load("images/fly0.svg");
    flyImages[1].load("images/fly1.svg");

    visibleCurve = true;

    maxRadius = 200;
    srand(time(0));
    vertIndex = 0;
    memset(&flyAllVertsIndexes, 0, sizeof(int) * FLIES_NUMBER);
    memset(&flyVertIndexes, 0, sizeof(int) * FLIES_NUMBER);
    memset(&flyStep, 0, sizeof(int) * FLIES_NUMBER);
    generateVerts();
    interpolateAllVerts();

    for (int fi = 0, vi = 0; fi < FLIES_NUMBER; ++fi, vi += 3) {
        flyVertIndexes[fi] = vi;
        flyAllVertsIndexes[fi] = allVerts.indexOf(verts[flyVertIndexes[fi]]);
    }

    connect(&vertRegenTimer, SIGNAL(timeout()),
            this, SLOT(on_vertRegenTimer_timeout()));
    vertRegenTimer.start(150);
    connect(&flyMoveTimer, SIGNAL(timeout()),
            this, SLOT(on_flyMoveTimer_timeout()));
    flyMoveTimer.start(30);
}

Canvas::~Canvas()
{
}

void Canvas::generateVerts()
{
    if (verts.size() < VERTS_NUMBER) {
        vertIndex = 0;
        for (int i = 0; i < VERTS_NUMBER; ++i)
            verts.push_back(getRandomVertex());
    } else {
        // skipping vertices that have flies between
        do {
            vertIndex++;
            if (vertIndex >= VERTS_NUMBER)
                vertIndex = 0;
        } while (fliesBetweenVerts(vertIndex));

        verts[vertIndex] = getRandomVertex();
    }
}

bool Canvas::fliesBetweenVerts(int vertIndex)
{
    for (int i = 0; i < FLIES_NUMBER; ++i) {
        int flyVertIndex = flyVertIndexes[i];
        if (flyVertIndex == vertIndex ||
            flyVertIndex + 1 == vertIndex ||
            (vertIndex == 0 && flyVertIndex == verts.size()-1))
            return true;
    }
    return false;
}

QPointF Canvas::getRandomVertex()
{
    int x = 0,
        y = 0;
    int cx = width() / 2,
        cy = height() / 2;

    // generate new coordinates using random position of
    // circle with random radius, while the distance between other
    // vertices is not long enough (100 tries)
    int tryn = 0;
    do {
        int r = rand() % maxRadius;
        float a = (float)(rand() % (int)(2*M_PI * 1000)) / 1000;
        x = cx + r * cos(a) - 1 * sin(a);
        y = cy + r * sin(a) + 1 * cos(a);
    } while(++tryn < 100 && !longFromVerts(x, y, INACCURACY));

    return QPointF(x, y);
}

bool Canvas::longFromVerts(float x, float y, float distance)
{
    for (int i = 0; i < verts.size(); ++i) {
        QPointF p2(x, y);
        float d = Canvas::distance(verts[i], p2);
        if (d < distance)
            return false;
    }
    return true;
}

float Canvas::distance(QPointF & p1, QPointF & p2)
{
    float xx = p1.x() - p2.x();
    float yy = p1.y() - p2.y();
    return sqrt(xx * xx + yy * yy);
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    // background
    p.fillRect(0, 0, width(), height(), QColor(0x36, 0x36, 0x36));

    if (visibleCurve)
        drawCurve(p);

    for (int i = 0; i < FLIES_NUMBER; ++i)
        drawFly(flyAllVertsIndexes[i], i);
}

void Canvas::drawCurve(QPainter & p)
{
    // curve with vertices
    QPainterPath curvePath;
    curvePath.moveTo(verts[0]);
    for (int i = 0; i < allVerts.size(); ++i)
        curvePath.lineTo(allVerts[i]);
    p.setPen(Qt::green);
    p.drawPath(curvePath);
    for (int i = 0; i < verts.size(); ++i) {
        if (fliesBetweenVerts(i))
            p.fillRect(verts[i].x()-5, verts[i].y()-5, 10, 10, Qt::black);

        p.setPen( (Qt::GlobalColor)((i % 16) + 2) );
        p.drawText(verts[i], QString("%1").arg(i));
        p.drawEllipse(QPointF(verts[i]), 10, 10);
    }
}

void Canvas::drawFly(int flyAllVertsIndex, int flyNumber)
{
    // rotating a fly to the angle between
    // the line (between current and next point)
    // and the abscissa plus pi/2
    QPainter painterFly(this);
    static const int fw = 35;
    static const int fh = 25;
    painterFly.translate(allVerts[flyAllVertsIndex].x(),
                         allVerts[flyAllVertsIndex].y());

    QPointF nextPoint = flyAllVertsIndex < allVerts.size()-1
                        ? allVerts[flyAllVertsIndex + 1]
                        : allVerts[0];

    float xb = nextPoint.x() - allVerts[flyAllVertsIndex].x();
    float yb = nextPoint.y() - allVerts[flyAllVertsIndex].y();
    float flyAngle = atan(yb / xb) + M_PI/2.;

    // rotate by 180 degrees if negative
    if (xb < 0)
        flyAngle += M_PI;

    painterFly.rotate((180./M_PI) * flyAngle);

    // drawing a fly
    //painterFly.fillRect(-fw/2, -fh/2, fw, fh, Qt::yellow); 
    painterFly.drawImage(QRect(-fw/2, -fh/2, fw, fh),
                         flyImages[flyStep[flyNumber] < ANIM_STEPS/2]);
}

void Canvas::interpolateAllVerts()
{
    if (verts.size() > 0) {
        allVerts.clear();

        // interpolating from 0 to n vertex
        float *xs = (float *) malloc(sizeof(float) * verts.size());
        float *ys = (float *) malloc(sizeof(float) * verts.size());
        for (int m = 0; m < verts.size(); ++m) {
            xs[m] = verts[m].x();
            ys[m] = verts[m].y();
        }
        for (int i = 0; i < verts.size() - 1; ++i) {
            allVerts.push_back(verts[i]);

            float *dots_x = interpolateX(xs, i, SMOOTH);
            float *dots_y = interpolateY(ys, i, SMOOTH);

            for (int ii = 0; ii < SMOOTH - 1; ++ii)
                allVerts.push_back(QPointF(dots_x[ii], dots_y[ii]));

            free(dots_x);
            free(dots_y);
        }
        free(xs);
        free(ys);
        allVerts.push_back(verts[verts.size()-1]);

        // joining n to 0 vertex
        float xxs[] = {verts[verts.size()-1].x(), verts[0].x()};
        float yys[] = {verts[verts.size()-1].y(), verts[0].y()};
        float *dots_x = interpolateX(xxs, 0, SMOOTH);
        float *dots_y = interpolateY(yys, 0, SMOOTH);
        for (int ii = 0; ii < SMOOTH - 1; ++ii)
            allVerts.push_back(QPointF(dots_x[ii], dots_y[ii]));
        free(dots_x);
        free(dots_y);
    }
}

void Canvas::on_vertRegenTimer_timeout()
{
    generateVerts();
    interpolateAllVerts();
    emit update();
}

void Canvas::on_flyMoveTimer_timeout()
{
    for (int fi = 0; fi < FLIES_NUMBER; ++fi) {
        int & flyVertIndex = flyVertIndexes[fi];
        int & flyAllVertsIndex = flyAllVertsIndexes[fi];
        flyStep[fi]++;
        if (flyStep[fi] > ANIM_STEPS)
            flyStep[fi] = 0;

        // skip some of next points
        // if the distance between vertices is too small
        QPointF nextVert = flyVertIndex == verts.size()-1
                           ? verts[0]
                           : verts[flyVertIndex + 1];
        float d = distance(verts[flyVertIndex], nextVert);
        float longDistance = (float)(maxRadius * (fi + 1));
        int addVerts = 5 + (int)(abs(longDistance - d)) % 10;

        if (addVerts <= 0)
            addVerts = 1;

        /*flyAllVertsIndex++;
        if (flyAllVertsIndex >= allVerts.size())
            flyAllVertsIndex = 0;*/

        for (int i = 0; i < addVerts; ++i) {
            flyAllVertsIndex++;
            if (flyAllVertsIndex >= allVerts.size())
                flyAllVertsIndex = 0;

            int vi = verts.indexOf(allVerts[flyAllVertsIndex]);
            if (vi != -1)
                flyVertIndex = vi;
        }
    }

    emit update();
}
