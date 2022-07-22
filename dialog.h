#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    int getNumLinhas();
    int getNumColunas();
    int getNumPlanos();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
