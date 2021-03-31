#include <QApplication>
#include <QTreeView>
#include <QStandardItem>
#include <QVariant>

#include "delegate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTreeView* treeView = new QTreeView();

    QStandardItemModel* standardModel = new QStandardItemModel;
    standardModel->setColumnCount(2);

    QStandardItem *root = new QStandardItem("ROOT");
    root->setCheckable(true);
    root->setCheckState(Qt::Checked);
    root->setEditable(false);

    standardModel->setItem(0, 0, root);

    QList< QStandardItem * > listOne ;
    QStandardItem  *f1 = new QStandardItem( "Field_1" );
    f1->setCheckable(true);
    f1->setCheckState(Qt::Checked);
    f1->setEditable(false);

    listOne.append(f1) ;
    listOne.append( new QStandardItem( "<Free text>" ) ) ;
    root->appendRow(listOne);


    QList< QStandardItem * > listTwo ;
    QStandardItem  *f2 = new QStandardItem( "Field_2" );
    listTwo.append(f2) ;

    QStringList options = {"one", "two", "three"};
    QStandardItem* item = new QStandardItem(options[0]);
    item->setData(QVariant(options),Qt::UserRole);
    listTwo.append(item) ;
    root->appendRow(listTwo);

    Delegate* delegate = new Delegate(treeView);
    treeView->setItemDelegate(delegate);

    treeView->setEditTriggers(QAbstractItemView::AllEditTriggers);

    treeView->setModel(standardModel);
    treeView->expandAll();

    treeView->show();

    return a.exec();
}
