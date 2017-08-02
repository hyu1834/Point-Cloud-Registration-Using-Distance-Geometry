#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*
 *  Standard Libraries
*/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread> 

/*
 *  3rd Party Libraries
*/
//QT
#include <QTime>
#include <QtGui>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QCoreApplication>


//PCL
#include <pcl/common/common_headers.h>

/*
 *  Local Libraries
*/
#include "../build/ui_mainwindow.h"
#include "str_utils.h"
#include "point_cloud_utils.h"
#include "registration_point_cloud_container.h"
#include "point_cloud_distance_geometry_registration.h"

/*
	ENUM
*/

/*
	MACRO
*/
#define DEBUGGING

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		/*
			Clicked Signal Methods
		*/
		void on_pointCloud1BrowseButton_clicked();
		void on_pointCloud2BrowseButton_clicked();
		void on_pointCloudResultBrowseButton_clicked();
		void on_registerButton_clicked();
		void on_corrDeleteButton1_clicked();
		void on_corrDeleteButton2_clicked();
		void on_corrExportButton1_clicked();
		void on_corrExportButton2_clicked();
		void on_corrImportButton1_clicked();
		void on_corrImportButton2_clicked();

		/*
			Trigger Signal Methods
		*/
		void on_actionExit_triggered();
		void on_actionRegister_triggered();
		void updateCorrPoints_triggered();
		void on_actionHelp_triggered();
		void on_actionAbout_triggered();

	private:
		Ui::MainWindow *ui;
		QSize desktopSize;
		QTimer *timer;

		/*
			Private Class Variables
		*/
		// Point cloud container
		RegistrationPointCloudContainer* pointCloud;
		
		/*
			Class Methods
		*/
		void menuConfiguration(Ui::MainWindow *ui);
		std::string formatPoints(pcl::PointXYZRGB point);

		/*
			Callback Handler Methods
		*/
		void corrDeleteButtonCallback(QListWidget* listWidget, pcl::PointCloud<pcl::PointXYZRGB>::Ptr container);
		void corrExportButtonCallback(pcl::PointCloud<pcl::PointXYZRGB>::Ptr container);
		void pointCloudTransCallBack(std::string resultPath, pcl::PointCloud<pcl::PointXYZRGB>::Ptr srcCorrPoints, 
									 pcl::PointCloud<pcl::PointXYZRGB>::Ptr destCorrPoints,
									 pcl::PointCloud<pcl::PointXYZRGB>::Ptr srcPoints, std::string mode,
									 THREAD_MODE threadMode = THREAD_ENABLE);
};

#endif // MAINWINDOW_H
