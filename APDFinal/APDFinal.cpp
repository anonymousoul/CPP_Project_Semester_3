#include "APDFinal.h"
#include "ui_APDFinal.h"

APDFinal::APDFinal(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::APDFinalClass)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot1()));
}

APDFinal::~APDFinal()
{
    delete ui;
}

void APDFinal::slot1()
{
    mw = new MainWindow;
    mw->show();
}
