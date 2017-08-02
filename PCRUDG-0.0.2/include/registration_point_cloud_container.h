#ifndef REGISTRATION_POINT_CLOUD_CONTAINER_H
	#define REGISTRATION_POINT_CLOUD_CONTAINER_H
/*
 *  Standard Libraries
*/
#include <cstdlib>
#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
 *  3rd Party Libraries
*/
//PCL
#include <pcl/common/common_headers.h>
#include <pcl/kdtree/kdtree_flann.h>


/*
 *  Local Libraries
*/
#include "point_cloud_container.h"

/*
	MACRO
*/
#define POINTCLOUD1 0
#define POINTCLOUD2 1
#define POINTCLOUDRESULT 2


class RegistrationPointCloudContainer : public PointCloudContainer 	{
	private:
		static RegistrationPointCloudContainer* instance;
		// std::vector<pcl::PointCloud<pcl::PointXYZRGB>::Ptr> pointCloud3D;
		std::vector<pcl::PointCloud<pcl::PointXY>::Ptr> pointCloud2D;
		std::vector<pcl::PointCloud<pcl::PointXYZRGB>::Ptr> correspondencePoints;
		std::vector<pcl::KdTree<pcl::PointXY>::Ptr> kdTrees;


		/*
			Constructor
		*/
		RegistrationPointCloudContainer(int size);
	protected:
	public:
		/*
			Destructor
		*/
		~RegistrationPointCloudContainer();

		/*
			Class Methods
		*/
		static RegistrationPointCloudContainer* init(int size = 3);


		/*
			Getter/Setter
		*/
		pcl::PointCloud<pcl::PointXY>::Ptr getPCContainer2D(int index);
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr getPCContainer3D(int index);
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr getCorrPCContainer(int index);
		pcl::KdTree<pcl::PointXY>::Ptr getKdTree(int index);
		void setKdTreeCloud(pcl::PointCloud<pcl::PointXY>::Ptr pointCloud, int index);

};

#endif