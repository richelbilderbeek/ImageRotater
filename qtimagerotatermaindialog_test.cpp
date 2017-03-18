#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtimagerotatermaindialog.h"

#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <QFileDialog>
#include <QLabel>

#include "imagerotatermaindialog.h"
#include "trace.h"
#include "plane.h"
#include "ui_qtimagerotatermaindialog.h"
#pragma GCC diagnostic pop


void ribi_QtImageRotaterMainDialog_Test() noexcept
{
  const QImage source(":/imagerotater/images/ImageRotaterTest.png");
  assert(!source.isNull());
  QImage target(source);
  ImageRotaterMainDialog::Rotate(
    source,
    target,
    0.235
  );
  assert(!target.isNull());
  assert(target != source
    && "Images do not look identical after rotation");
}
