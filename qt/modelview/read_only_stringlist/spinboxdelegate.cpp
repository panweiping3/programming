#include "spinboxdelegate.h"

SpinBoxDelegate::SpinBoxDelegate(QObject *parent)
{
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(100);

    return editor;
}

// get data from model
void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
   int value = index.model()->data(index, Qt::EditRole).toInt();
   QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
   spinBox->setValue(value);
}

// save data from delegate into model
void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
    spinBox->interpretText();
    int value = spinBox->value();

    model->setData(index, value, Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

bool SpinBoxDelegate::eventFilter(QObject *editor, QEvent *event)
{
    if ((editor == NULL) || (event == NULL)) {
        return true;
    }

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent == NULL){
            return false;
        }

        if (keyEvent->key() == Qt::Key_Return){
            emit closeEditor(qobject_cast<QWidget *>(editor), QAbstractItemDelegate::EditNextItem);
            return true;
        }
    }

    return false;
}

