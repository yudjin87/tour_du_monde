#ifndef NEWMOCKDIALOG_H
#define NEWMOCKDIALOG_H

#include "MockDialogModel.h"

#include <QtWidgets/QDialog>

class NewMockDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewMockDialog(MockDialogModel *model, QWidget *mainWindow = nullptr);
};

#endif // NEWMOCKDIALOG_H
