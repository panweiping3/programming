#include "xform.h"
#include "hoverpoints.h"

#include <QLayout>
#include <QPainter>
#include <QPainterPath>

const int alpha = 155;

XFormView::XFormView(QWidget *parent)
	: ArthurFrame(parent)
{
	
}
void XFormView::paint(QPainter *painter)
void XFormView::drawVectorType(QPainter *painter)
void XFormView::drawPixmapType(QPainter *painter)
void XFormView::drawTextType(QPainter *painter)
QSize XFormView::sizeHint() const { return QSize(500, 500) };

void XFormView::mousePressEvent(QMouseEvent *e)
void XFormView::resizeEvent(QResizeEvent *e)
HoverPoints *XFormView::hoverPoints() { return pts }

bool XFormView::animation() const { return timer.isActive() }
qreal XFormView::shear() const { return m_shear }	
qreal XFormView::rotation() const { return m_rotation }	
qreal XFormView::scale() const { return m_scale }	
void XFormView::setShear(qreal s)
void XFormView::setScale(qreal s)
void XFormView::setRotation(qreal r)

void XFormView::setAnimation(bool animate)
void XFormView::updateCtrlPoints(const QPolygonF &)		
void XFormView::changeRoation(int rotation)
void XFormView::changeShear(int shear)
void XFormView::changeScale(int scale)
void XFormView::setVectorType()
void XFormView::setPixmapType()
void XFormView::setTextType()
void XFormView::reset()

void XFormView::rotationChanged(int rotation)
void XFormView::scaleChanged()
void XFormView::shearChanged()

void XFormView::timerEvent(QTimerEvent *e)
void XFormView::wheelEvent(QWheelEvent *e)
	
