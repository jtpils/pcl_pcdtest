#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

int
  main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZRGB> cloud;

  if (pcl::io::loadPCDFile<pcl::PointXYZRGB> ("100.pcd", cloud) == -1) //* load the file
  {
    PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
    return (-1);
  }

  pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud);
  std::cerr << "Saved " << cloud.points.size () << " data points to test_pcd.pcd." << std::endl;


  return (0);
}
