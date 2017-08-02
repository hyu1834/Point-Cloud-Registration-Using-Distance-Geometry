#ifndef POINT_CLOUD_CONTAINER_H
	#define POINT_CLOUD_CONTAINER_H
/*
	Standard Libraries
*/
#include <cstdlib>
#include <climits>
#include <vector>
/*
	3rd Party Libraries
*/
//PCL
#include <pcl/common/common_headers.h>
#include <pcl/kdtree/kdtree_flann.h>


/*
	Local Libraries
*/


/*
	MACRO
*/
#define POINTCLOUD1 0
#define POINTCLOUD2 1
#define POINTCLOUDRESULT 2


class PointCloudContainer 	{
	private:
		static PointCloudContainer* instance;
		

	protected:
		/*
			Constructor
		*/
		PointCloudContainer(int size);

		/*
			Class Variables
		*/
		std::vector<pcl::PointCloud<pcl::PointXYZRGB>::Ptr> pointCloud3D;
	public:
		/*
			Destructor
		*/
		~PointCloudContainer();

		/*
			Class Methods
		*/
		static PointCloudContainer* init(int size = 1);


		/*
			Getter/Setter
		*/
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr getPCContainer3D(int index);
};

#endif