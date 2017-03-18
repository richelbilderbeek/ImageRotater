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

int ribi::ImageRotaterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc != 5
    || argv[1] == argv[3]
    || (argv[1] != "-f" && argv[1] != "--filename" && argv[1] != "-r" && argv[1] != "--rotation")
    || (argv[3] != "-f" && argv[3] != "--filename" && argv[3] != "-r" && argv[3] != "--rotation")
  )
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  std::string filename;
  if (argv[1] == "-f" || argv[1] == "--filename") filename = argv[2];
  if (argv[3] == "-f" || argv[3] == "--filename") filename = argv[4];
  if (!fileio::FileIo().IsRegularFile(filename))
  {
    std::cout << "Please supply the filename of an existing file" << std::endl;
    return 1;
  }
  std::string angle_str;
  if (argv[1] == "-r" || argv[1] == "--rotation") angle_str = argv[2];
  if (argv[3] == "-r" || argv[3] == "--rotation") angle_str = argv[4];
  double angle = 0.0;
  try
  {
    angle = boost::lexical_cast<double>(angle_str);
  }
  catch (boost::bad_lexical_cast&)
  {
    std::cout << "Please supply a number for the rotation" << std::endl;
    return 1;
  }
  const double pi = boost::math::constants::pi<double>();

  const QImage source(filename.c_str());
  assert(!source.isNull());
  QImage target(source);
  assert(!target.isNull());

  ImageRotaterMainDialog::Rotate(source,target,pi * angle / 180.0);

  const std::string target_filename = fileio::FileIo().GetTempFileName(".png");
  target.save(target_filename.c_str());

  const boost::shared_ptr<ImageCanvas> canvas {
    new ImageCanvas(target_filename,40) //,CanvasColorSystem::invert)
  };
  std::cout << (*canvas) << std::endl;
  return 0;
}

ribi::About ribi::ImageRotaterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "ImageRotater",
    "tool to rotate images",
    "December 31st of 2015",
    "2007-2015",
    "http://www.richelbilderbeek.nl/ToolImageRotater.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("ImageCanvas version: " + ImageCanvas::GetVersion());
  return a;
}

ribi::Help ribi::ImageRotaterMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    GetAbout().GetFileTitle(),
    GetAbout().GetFileDescription(),
    {
      Help::Option('f',"filename","Image filename"),
      Help::Option('r',"rotation","Rotation angle in degrees")
    },
    {
      GetAbout().GetFileTitle() + " -f MyFile.png -r 45",
      GetAbout().GetFileTitle() + " --filename MyFile.png --rotation 135"
    }
  );
}

std::string ribi::ImageRotaterMenuDialog::GetVersion() const noexcept
{
  return "3.0";
}

std::vector<std::string> ribi::ImageRotaterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2007-xx-xx: version 1.0: initial Windows-only version",
    "2013-11-29: version 2.0: port to Qt",
    "2014-02-06: version 2.1: added command-line version",
    "2015-12-31: version 3.0: moved to own GitHub"
  };
}
