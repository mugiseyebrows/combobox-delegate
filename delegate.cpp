#include "delegate.h"

#include <QComboBox>

#include <QStylePainter>
#include <QApplication>
#include <QStyleOption>
#include <QStyle>
#include <QDebug>

Delegate::Delegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data(Qt::UserRole).isNull()) {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
    return new QComboBox(parent);
}

void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    if (!comboBox) {
        return QStyledItemDelegate::setEditorData(editor, index);
    }
    QStringList options = index.data(Qt::UserRole).toStringList();
    comboBox->addItems(options);
    QString value = index.data().toString();
    int current = options.indexOf(value);
    if (current > -1) {
        comboBox->setCurrentIndex(current);
    }
    comboBox->showPopup();
}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    if (!comboBox) {
        return QStyledItemDelegate::setModelData(editor, model, index);
    }
    model->setData(index, comboBox->currentText());
}

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data(Qt::UserRole).isNull()) {
        return QStyledItemDelegate::paint(painter, option, index);
    }
    QStyle* style = qApp->style();
    QStyleOptionComboBox opt;
    opt.rect = option.rect;
    opt.currentText = index.data().toString();
    opt.palette = option.palette;
    opt.state = option.state;
    opt.subControls = QStyle::SC_All;
    opt.activeSubControls = QStyle::SC_All;
    opt.editable = false;
    opt.frame = true;
    style->drawComplexControl(QStyle::CC_ComboBox, &opt, painter, 0);
    style->drawControl(QStyle::CE_ComboBoxLabel, &opt, painter, 0);
}
