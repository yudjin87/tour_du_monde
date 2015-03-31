#pragma once
#include "MockDialogModel.h"

#include <QtWidgets/QDialog>

class NewMockDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewMockDialog(MockDialogModel *model, QWidget *mainWindow = nullptr);
};

