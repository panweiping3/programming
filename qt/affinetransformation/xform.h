#ifndef XFORM_H 
#define XFORM_H

#include <QBasicTimer>
#include <QPolygonF>

class HoverPoints;
QT_FORWARD_DECLARE_CLASS(QLineEdit);

class XFormView : public ArthurFrame
{
	Q_OBJECT

	Q_PROPERTY(bool animation READ animation WRITE setAnimation)
	Q_PROPERTY(qreal shear READ shear WRITE setShear)
	Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
	Q_PROPERTY(qreal scale READ scale WRITE setScale)

	public:
		XFormView(QWidget *parent);
		void paint(QPainter *painter);
		void drawVectorType(QPainter *painter);
		void drawPixmapType(QPainter *painter);
		void drawTextType(QPainter *painter);
		QSize sizeHint() const { return QSize(500, 500); };

		void mousePressEvent(QMouseEvent *e);
		void resizeEvent(QResizeEvent *e);
		HoverPoints *hoverPoints() { return pts; }
		
		QLineEdit *textEdit;

		bool animation() const { return timer.isActive(); }
		qreal shear() const { return m_shear; }	
		qreal rotation() const { return m_rotation; }	
		qreal scale() const { return m_scale; }	
		void setShear(qreal s);
		void setScale(qreal s);
		void setRotation(qreal r);
		
	public slots:
		void setAnimation(bool animate);
		void updateCtrlPoints(const QPolygonF &);		
		void changeRoation(int rotation);
		void changeShear(int shear);
		void changeScale(int scale);
		void setVectorType();
		void setPixmapType();
		void setTextType();
		void reset();

	signals:
		void rotationChanged(int rotation);
		void scaleChanged();
		void shearChanged();
	
	protected:
		void timerEvent(QTimerEvent *e);
		void wheelEvent(QWheelEvent *e);
	
	private:
		enum XFormType 
		{
			VectorType, PixmapType, TextType 
		};

	QPolygonF ctrlPoints;
	HoverPoints *pts;
	qreal m_rotation;
	qreal m_scale;
	qreal m_shear;
	XFormType type;
	QPixmap pixmap;
	QBasicTimer timer;
};

class XFormWidget : public QWidget
{
	Q_OBJECT
	
	public:
		XFormWidget(QWidget *parent);
	
	private:
		XFormView *view;
		QLineEdit *textEditor;
};

#endif
