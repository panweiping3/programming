#include "delegate.h"

#include <QtGui>

SpinBoxDelegate::SpinBoxDelegate(QObject *parent)
	: QItemDelegate(parent)
{
	
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if (index.column() == 1)
	{
		QLineEdit *editor = new QLineEdit(parent);
		return editor;
	}
	else
	{
		QSpinBox *editor = new QSpinBox(parent);
		editor->setMinimum(0);
		editor->setMaximum(100);
		return editor;
	}
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (index.column() == 1)
	{
		QString value = index.model()->data(index, Qt::EditRole).toString();
		QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
		lineEdit->setText(value);
	}
	else
	{
		int value = index.model()->data(index, Qt::EditRole).toInt();

		QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
		spinBox->setValue(value);
	}
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	if (index.column() == 0)
	{
		QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
		spinBox->interpretText();

		int value = spinBox->value();
		model->setData(index, value, Qt::EditRole);
	}
	else
	{
		QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);

		QString value =lineEdit->text();
		model->setData(index, value, Qt::EditRole);
	}
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	editor->setGeometry(option.rect);
}

bool SpinBoxDelegate::eventFilter(QObject *editor, QEvent *event)
{
	if ((editor == NULL) || (event == NULL))	
	{
		return true;
	}

	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		if (keyEvent == NULL)
		{
			return false;
		}

		if (keyEvent->key() == Qt::Key_Return)
		{
			emit closeEditor(qobject_cast<QWidget *>(editor), QAbstractItemDelegate::EditPreviousItem);
			return true;
		}
	}	

	return false;
}
