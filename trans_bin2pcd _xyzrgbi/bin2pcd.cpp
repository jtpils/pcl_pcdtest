#include <boost/program_options.hpp>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/point_operators.h>
#include <pcl/common/io.h>
#include <pcl/search/organized.h>
#include <pcl/search/octree.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/filters/conditional_removal.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/surface/gp3.h>
#include <pcl/io/vtk_io.h>
#include <pcl/filters/voxel_grid.h>
 
#include <iostream>
#include <fstream>
 
using namespace pcl;
using namespace std;
 
namespace po = boost::program_options;
 
int main(int argc, char **argv){
	///The file to read from.
	string infile;
 
	///The file to output to.
	string outfile;
 
	// Declare the supported options.
	po::options_description desc("Program options");
	desc.add_options()
		//Options
		("infile", po::value<string>(&infile)->required(), "the file to read a point cloud from")
		("outfile", po::value<string>(&outfile)->required(), "the file to write the DoN point cloud & normals to")
		;
	// Parse the command line
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
 
	// Print help
	if (vm.count("help"))
	{
		cout << desc << "\n";
		return false;
	}
 
	// Process options.
	po::notify(vm);
 
	// load point cloud
	fstream input(infile.c_str(), ios::in | ios::binary);
	if(!input.good()){
		cerr << "Could not read file: " << infile << endl;
		exit(EXIT_FAILURE);
	}
	input.seekg(0, ios::beg);
 
	pcl::PointCloud<PointXYZRGB>::Ptr points (new pcl::PointCloud<PointXYZRGB>);
 
	int r=20, g=30, b=40;
	float c;
	for (i=0; input.good() && !input.eof(); i++) {
		PointXYZRGB point;
		input.read((char *) &point.x, sizeof(float));
		input.read((char *) &point.y, sizeof(float));
		input.read((char *) &point.z, sizeof(float));

		input.read((char *) &point.r, sizeof(float));
		input.read((char *) &point.g, sizeof(float));
		input.read((char *) &point.b, sizeof(float));

		// input.read((char *) &point.a, sizeof(float));
		input.read((char *) &c, sizeof(float));

		points->push_back(point);
	}
	input.close();
 
	cout << "Read KTTI point cloud with " << i << " points, writing to " << outfile << endl;
 
    //pcl::PCDWriter writer;
 
    // Save DoN features
    pcl::io::savePCDFileASCII(outfile, *points);
    //writer.write<PointXYZI> (outfile, *points, false);
}