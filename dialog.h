#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>

namespace Ui{
class dialog;
}

class dialog: public QDialog
{
    Q_OBJECT

public:

   explicit dialog(QWidget *parent = nullptr);
   ~dialog();

    int getNumLinhas();
    int getNumColunas();
    int getNumPlanos();
private:
    Ui::dialog *ui;
};

#endif // DIALOG_H
