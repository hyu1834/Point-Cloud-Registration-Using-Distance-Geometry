#include "point_cloud_container.h"

PointCloudContainer* PointCloudContainer::instance = NULL;

/*
	Constructor/Destructor
*/
PointCloudContainer::PointCloudContainer(int size)	{
	for(int i = 0; i < size; i++)	{
		// create a point cloud pointer
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudPtr3D(new pcl::PointCloud<pcl::PointXYZRGB>);
		// insert such pointer into the vector
		pointCloud3D.push_back(cloudPtr3D);
	}
}

PointCloudContainer::~PointCloudContainer()	{
	pointCloud3D.clear();	
}

/*
	Class Methods
*/
PointCloudContainer* PointCloudContainer::init(int size)	{
	if(!instance)	{
		instance = new PointCloudContainer(size);
	}

	return instance;
}

/*
	Getter/Setter
*/
pcl::PointCloud<pcl::PointXYZRGB>::Ptr PointCloudContainer::getPCContainer3D(int index)	{
	if(index < pointCloud3D.size())	{
		return pointCloud3D[index];
	}

	return NULL;
}
