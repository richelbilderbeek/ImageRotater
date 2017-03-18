#include "imagerotatermenudialog.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>

#include <QFile>

#include "fileio.h"
#include "imagecanvas.h"
#include "imagerotatermaindialog.h"
#pragma GCC diagnostic pop

void ribi_ImageRotaterMenuDialog_Test() noexcept
{
  ImageRotaterMenuDialog d;
  const std::string filename { fileio::FileIo().GetTempFileName(".png") };
  QFile file(":/imagerotater/images/R.png");
  file.copy(filename.c_str());
  d.Execute( { "ImageRotaterMenuDialog", "-f", filename, "-r", "30.0" } );
  fileio::FileIo().DeleteFile(filename);
}
