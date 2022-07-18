#include "dialog.h"
#include "ui_dialog.h"

dialog::dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogEsc)
{
    ui->setupUi(this);
}
dialog::~dialog()
{
    delete ui;
}

int dialog:getNumLinhas()
{
    return ui->spinBoxLinhas->value();
}

int dialog::getNumColunas()
{
    return ui->spinBoxColunas->value();
}

int dialog::getNumPlanos()
{
    return ui->spinBoxPlanos->value();
}
