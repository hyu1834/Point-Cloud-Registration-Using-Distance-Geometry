#include "registration_point_cloud_container.h"

RegistrationPointCloudContainer* RegistrationPointCloudContainer::instance = NULL;

/*
	Constructor/Destructor
*/
RegistrationPointCloudContainer::RegistrationPointCloudContainer(int size) : PointCloudContainer(size)	{
	for(int i = 0; i < size; i++)	{
		// create a point cloud pointer
		pcl::PointCloud<pcl::PointXY>::Ptr cloudPtr2D(new pcl::PointCloud<pcl::PointXY>);
		// pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudPtr3D(new pcl::PointCloud<pcl::PointXYZRGB>);
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr corrPoints(new pcl::PointCloud<pcl::PointXYZRGB>);
		// insert such pointer into the vector
		pointCloud2D.push_back(cloudPtr2D);
		// pointCloud3D.push_back(cloudPtr3D);
		correspondencePoints.push_back(corrPoints);

		// KdTree instance
		pcl::KdTree<pcl::PointXY>::Ptr kdTreePtr(new pcl::KdTreeFLANN<pcl::PointXY>);
		kdTrees.push_back(kdTreePtr);
	}
}

RegistrationPointCloudContainer::~RegistrationPointCloudContainer()	{
	pointCloud3D.clear();
	pointCloud2D.clear();	
}

/*
	Class Methods
*/
RegistrationPointCloudContainer* RegistrationPointCloudContainer::init(int size)	{
	if(!instance)	{
		instance = new RegistrationPointCloudContainer(size);
	}

	return instance;
}

/*
	Getter/Setter
*/
pcl::PointCloud<pcl::PointXY>::Ptr RegistrationPointCloudContainer::getPCContainer2D(int index)	{
	if(index < pointCloud2D.size())	{
		return pointCloud2D[index];
	}

	return NULL;
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr RegistrationPointCloudContainer::getPCContainer3D(int index)	{
	if(index < pointCloud3D.size())	{
		return pointCloud3D[index];
	}

	return NULL;
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr RegistrationPointCloudContainer::getCorrPCContainer(int index)	{
	if(index < pointCloud3D.size())	{
		return correspondencePoints[index];
	}

	return NULL;
}

pcl::KdTree<pcl::PointXY>::Ptr RegistrationPointCloudContainer::getKdTree(int index)	{
	if(index < kdTrees.size())	{
		return kdTrees[index];
	}

	return NULL;
}

void RegistrationPointCloudContainer::setKdTreeCloud(pcl::PointCloud<pcl::PointXY>::Ptr pointCloud, int index)	{
	if(index >= kdTrees.size())	{
		return;
	}

	kdTrees[index]->setInputCloud(pointCloud);
}

