#include <cartoUI/FeatureLayerDelegate.h>
#include <QtWidgets/QLineEdit>

FeatureLayerDelegate::FeatureLayerDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *FeatureLayerDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setFrame(false);
    return editor;
}

void FeatureLayerDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString name = index.model()->data(index, Qt::EditRole).toString();

    QLineEdit *textEdit = static_cast<QLineEdit*>(editor);
    textEdit->setText(name);
}

void FeatureLayerDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *textEdit = static_cast<QLineEdit*>(editor);
    QString name = textEdit->text();
    model->setData(index, name, Qt::EditRole);
}
