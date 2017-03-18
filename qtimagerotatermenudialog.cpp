#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtimagerotatermenudialog.h"

#include "qtaboutdialog.h"
#include "imagerotatermenudialog.h"
#include "qtimagerotatermaindialog.h"
#include "ui_qtimagerotatermenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtImageRotaterMenuDialog::QtImageRotaterMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtImageRotaterMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtImageRotaterMenuDialog::~QtImageRotaterMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtImageRotaterMenuDialog::on_button_start_clicked()
{
  QtImageRotaterMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtImageRotaterMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(ImageRotaterMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtImageRotaterMenuDialog::on_button_quit_clicked()
{
  this->close();
}
