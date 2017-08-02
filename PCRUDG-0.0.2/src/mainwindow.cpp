#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)	{
	ui->setupUi(this);
	// Open application in full screen mode
	// QWidget::showFullScreen();
	QWidget::showMaximized();
	//Get screen size
	// desktopSize = QDesktopWidget().availableGeometry(this).size();
	//Set the window size to be the maximun
	// this->setFixedSize(desktopSize.width(), desktopSize.height());

	//Menu Configuration
	menuConfiguration(ui);

	// Point cloud container
	pointCloud = RegistrationPointCloudContainer::init(3);

	//trigger list view update every second
	timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateCorrPoints_triggered()));
	timer->start(1000); //time specified in ms
}

MainWindow::~MainWindow()	{
	// delete pointer
	delete ui;
}


/*
	Clicked Signal Methods
*/
void MainWindow::on_pointCloud1BrowseButton_clicked()	{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open Point Cloud 1 File"), QString(),
														  tr("Text Files (*.txt);;All Files (*.*)"));
	// if a file is selected
	if(filePath != "")  {
		// import the point cloud
		importPointCloud<pcl::PointXY, pcl::PointXYZRGB>(filePath.toUtf8().constData(), 
														 pointCloud->getPCContainer2D(POINTCLOUD1),
														 pointCloud->getPCContainer3D(POINTCLOUD1));
		// Construct the kdtree in 2D
		pointCloud->setKdTreeCloud(pointCloud->getPCContainer2D(POINTCLOUD1), POINTCLOUD1);

		int pointCloudSize = pointCloud->getPCContainer3D(POINTCLOUD1)->size();
		// if theres at least 1 point loaded, display message to user on point cloud size
		if(pointCloudSize > 0)  {
			ui->pointCloud1Path->setText(filePath);
			QMessageBox::information(this, "Point Cloud 1", QString::fromStdString("Loaded: " + formatNumber<int>(pointCloudSize) + " points"));
			
			//Enable Features
			ui->pointCloud2BrowseButton->setEnabled(true);
			ui->corrImportButton1->setEnabled(true);
		}
		else	{
			QMessageBox::warning(this, "Warning!", "Warning: Invalid/Empty Point Cloud File");
		}
		
	}
}

void MainWindow::on_pointCloud2BrowseButton_clicked()	{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open Point Cloud 2 File"), QString(),
														  tr("Text Files (*.txt);;All Files (*.*)"));

	// if a file is selected
	if(filePath != "")  {
		// import the point cloud
		importPointCloud<pcl::PointXY, pcl::PointXYZRGB>(filePath.toUtf8().constData(), 
														 pointCloud->getPCContainer2D(POINTCLOUD2),
														 pointCloud->getPCContainer3D(POINTCLOUD2));
		// Construct the kdtree in 2D
		pointCloud->setKdTreeCloud(pointCloud->getPCContainer2D(POINTCLOUD2), POINTCLOUD2);

		int pointCloudSize = pointCloud->getPCContainer3D(POINTCLOUD2)->size();
		// if theres at least 1 point loaded, display message to user on point cloud size
		if(pointCloudSize > 0)  {
			ui->pointCloud2Path->setText(filePath);
			QMessageBox::information(this, "Point Cloud 2", QString::fromStdString("Loaded: " + formatNumber<int>(pointCloudSize) + " points"));

			//Enable Features
			ui->registrationGroup->setEnabled(true);
			ui->pointCloudResultBrowseButton->setEnabled(true);
			ui->corrImportButton2->setEnabled(true);

		}
		else	{
			QMessageBox::warning(this, "Warning!", "Warning: Invalid/Empty Point Cloud File");
		}
	}
}

void MainWindow::on_pointCloudResultBrowseButton_clicked()	{
	QString filePath = QFileDialog::getSaveFileName(this, tr("Save Point Cloud File"), QString(),
														  tr("Text Files (*.txt);;All Files (*.*)"));

	// if a file is selected
	if(filePath != "")  {
		ui->pointCloudResultPath->setText(filePath);
	}

	// Enable register button
	ui->registerButton->setEnabled(true);
}

void MainWindow::on_registerButton_clicked()	{	
	// Make sure both point cloud not empty
	if(pointCloud->getPCContainer3D(POINTCLOUD1)->size() < 1)	{
		QMessageBox::critical(this, "Error!", "Error: Point cloud 1 is Empty!!");
		return;
	}
	if(pointCloud->getPCContainer3D(POINTCLOUD2)->size() < 1)	{
		QMessageBox::critical(this, "Error!", "Error: Point cloud 2 is Empty!!");
		return;
	}

	// Make sure both correspondence point cloud not empty and that they have the same size
	if(pointCloud->getCorrPCContainer(POINTCLOUD1)->size() < 4 || pointCloud->getCorrPCContainer(POINTCLOUD2)->size() < 4)	{
		QMessageBox::critical(this, "Error!", "Error: Minimum of 4 correspondence points is required.");
		return;
	}

	if(pointCloud->getCorrPCContainer(POINTCLOUD1)->size() != pointCloud->getCorrPCContainer(POINTCLOUD2)->size())	{
		QMessageBox::critical(this, "Error!", "Error: Correspondence points size must be equal.");
		return;
	}

	// We will create pointer everytime register button is called to ensure quality
	// Registered Point Cloud Dest
	std::string resultPath = ui->pointCloudResultPath->text().toUtf8().constData();

	// After all check, display message on registration process
	if(ui->pc1ToPc2Radio->isChecked())   {
		// Point Cloud Transformation
		pointCloudTransCallBack(resultPath, pointCloud->getCorrPCContainer(POINTCLOUD1), 
								pointCloud->getCorrPCContainer(POINTCLOUD2), pointCloud->getPCContainer3D(POINTCLOUD1), 
								"PC1 --> PC2", 
								((ui->threadEnableCheckBox->isChecked()) ? THREAD_ENABLE : THREAD_DISABLE));
	}
	else	{
		// Point Cloud Transformation
		pointCloudTransCallBack(resultPath, pointCloud->getCorrPCContainer(POINTCLOUD2), 
								pointCloud->getCorrPCContainer(POINTCLOUD1), pointCloud->getPCContainer3D(POINTCLOUD2),
								"PC2 --> PC1", 
								((ui->threadEnableCheckBox->isChecked() ) ? THREAD_ENABLE : THREAD_DISABLE));
	}
}

void MainWindow::on_corrDeleteButton1_clicked()	{
	corrDeleteButtonCallback(ui->corrListWidget1, pointCloud->getCorrPCContainer(POINTCLOUD1));
}

void MainWindow::on_corrDeleteButton2_clicked()	{
	corrDeleteButtonCallback(ui->corrListWidget2, pointCloud->getCorrPCContainer(POINTCLOUD2));
}

void MainWindow::on_corrExportButton1_clicked()	{
	corrExportButtonCallback(pointCloud->getCorrPCContainer(POINTCLOUD1));
}

void MainWindow::on_corrExportButton2_clicked()	{
	corrExportButtonCallback(pointCloud->getCorrPCContainer(POINTCLOUD2));
}

void MainWindow::on_corrImportButton1_clicked()	{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open Correspondence Points File"), QString(),
														  tr("Text Files (*.txt);;All Files (*.*)"));
	if(filePath != "")  {
		// First clear listwidget
		while(ui->corrListWidget1->count()>0)	{
			delete ui->corrListWidget1->takeItem(0);
		}
		// Import point cloud
		importPointCloud<pcl::PointXYZRGB>(filePath.toUtf8().constData(), pointCloud->getCorrPCContainer(POINTCLOUD1));
		QMessageBox::information(this, "Correspondence Points 1", 
								 QString::fromStdString("Loaded: " + formatNumber<int>(pointCloud->getCorrPCContainer(POINTCLOUD1)->size()) + " points"));

	}
}

void MainWindow::on_corrImportButton2_clicked()	{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open Correspondence Points File"), QString(),
														  tr("Text Files (*.txt);;All Files (*.*)"));
	if(filePath != "")  {
		// First clear listwidget
		while(ui->corrListWidget2->count()>0)	{
			delete ui->corrListWidget2->takeItem(0);
		}
		// Import point cloud
		importPointCloud<pcl::PointXYZRGB>(filePath.toUtf8().constData(), pointCloud->getCorrPCContainer(POINTCLOUD2));
		QMessageBox::information(this, "Correspondence Points 2", 
								 QString::fromStdString("Loaded: " + formatNumber<int>(pointCloud->getCorrPCContainer(POINTCLOUD2)->size()) + " points"));
	}
}


/*
	Trigger Signal Methods
*/
void MainWindow::on_actionExit_triggered()	{
	QApplication::quit();
}

void MainWindow::on_actionRegister_triggered()	{
	on_registerButton_clicked();
}

void MainWindow::updateCorrPoints_triggered()	{
	// Update correspondence points for listview 1
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr container = pointCloud->getCorrPCContainer(POINTCLOUD1);
	for(pcl::PointCloud<pcl::PointXYZRGB>::iterator it = container->begin(); it != container->end(); it++)	{
		QString itemStr = QString::fromStdString(formatPoints(*it));
		if(ui->corrListWidget1->findItems(itemStr, Qt::MatchExactly).count() > 0)	{
			continue;
		}

		ui->corrListWidget1->addItem(itemStr);
	}

	// Update correspondence points for listview 2
	container = pointCloud->getCorrPCContainer(POINTCLOUD2);
	for(pcl::PointCloud<pcl::PointXYZRGB>::iterator it = container->begin(); it != container->end(); it++)	{
		QString itemStr = QString::fromStdString(formatPoints(*it));
		if(ui->corrListWidget2->findItems(itemStr, Qt::MatchExactly).count() > 0)	{
			continue;
		}

		ui->corrListWidget2->addItem(itemStr);
	}
}

void MainWindow::on_actionHelp_triggered()	{
	QString helpStr = QString::fromStdString(std::string("\n") +
											 ""
											);
	QMessageBox::information(this, "Help", helpStr);
}

void MainWindow::on_actionAbout_triggered()	{
	QString aboutStr = QString::fromStdString(std::string("Program Title: Point Cloud Registration Using Distance Geometry\n") + 
											  "Thesis Author: Zhenxiang Jian\n" +
											  "Developer: Hiu Hong Yu\n" +
											  "Developer Email: hiuyu@ucdavis.edu\n" +
											  "Organization: Advanced Highway Maintenance and Construction Research Center (AHMCT), University of California, Davis\n" +
											  "Copy Right 2017"
											 );
	QMessageBox::information(this, "About", aboutStr);
}


/*
	Class Methods
*/
void MainWindow::menuConfiguration(Ui::MainWindow *ui)  {
	/*
		Disable some features for later
	*/
	//Disable Text Box, make the text box non-editable
	ui->pointCloud1Path->setEnabled(false);
	ui->pointCloud2Path->setEnabled(false);
	ui->pointCloudResultPath->setEnabled(false);

	//Disable Button
	ui->pointCloud2BrowseButton->setEnabled(false);
	ui->pointCloudResultBrowseButton->setEnabled(false);
	ui->registerButton->setEnabled(false);

	// Disable  group
	ui->registrationGroup->setEnabled(false);
}

std::string MainWindow::formatPoints(pcl::PointXYZRGB point)	{
	std::stringstream ss;
	ss << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << 
		  ", r: "<< (unsigned int)point.r << ", g: "<< (unsigned int)point.g << ", b: "<< (unsigned int)point.b;

	return ss.str();
}


/*
	Callback Handler Methods
*/
void MainWindow::corrDeleteButtonCallback(QListWidget* listWidget, pcl::PointCloud<pcl::PointXYZRGB>::Ptr container)	{
	// For each selected item
	foreach(QListWidgetItem* item, listWidget->selectedItems())	{
		// Locate the index of the correspondence points
		int index = -1;
		for(int i = 0; i < container->size(); i++)	{
			// if found the matching item
			if(QString::fromStdString(formatPoints(container->points[i])) == item->text())	{
				index = i;
				break;
			}
		}
		if(index != -1)	{
			container->erase(container->begin() + index);
		}
	}
	qDeleteAll(listWidget->selectedItems());
}

void MainWindow::corrExportButtonCallback(pcl::PointCloud<pcl::PointXYZRGB>::Ptr container)	{
	QString filePath = QFileDialog::getSaveFileName(this, QFileDialog::tr("Export Correspondence Point Cloud File"), QString(), 
													QFileDialog::tr("Text Files (*.txt);;All Files (*.*)"));
	if(filePath != "")  {
		exportPointCloud<pcl::PointXYZRGB>(filePath.toUtf8().constData(), container);
		QMessageBox::information(this, "Export Point Cloud", 
								 QString::fromStdString("Exported: " + formatNumber<int>(container->size()) + " points"));
	}

}

// Function to perform Point Cloud Transformation
void MainWindow::pointCloudTransCallBack(std::string resultPath, pcl::PointCloud<pcl::PointXYZRGB>::Ptr srcCorrPoints, 
										 pcl::PointCloud<pcl::PointXYZRGB>::Ptr destCorrPoints,
										 pcl::PointCloud<pcl::PointXYZRGB>::Ptr srcPoints, std::string mode,
										 THREAD_MODE threadMode)	{
	int threadAmount = 1;
	/*
		Up/Down Scale Point Cloud
	*/
	double ratio = scalePointCloud<pcl::PointXYZRGB>(srcCorrPoints, destCorrPoints, srcPoints);

	/*
		Point Cloud Registration
	*/
	// Point cloud registration instance
	DistanceGeometryRegistration<pcl::PointXYZRGB>* dgr = new DistanceGeometryRegistration<pcl::PointXYZRGB>();

	// Compute transformation matrix by correspondence point
	if(!dgr->computeTransformation(srcCorrPoints, destCorrPoints))	{
		QMessageBox::critical(this, "Error!", QString::fromStdString("Error: Unable to compute transformation matrix for: " + mode));
		
		// Delete instance
		delete dgr;
		return;
	}
	
	//Apply transformation to the src correspondence points
	dgr->pointCloudTransformation(srcCorrPoints);
	// compute the absolute error
	double absoluteError = dgr->estimateError(srcCorrPoints, destCorrPoints);

	// Determine thread amount for point cloud transformation
	if(threadMode == THREAD_ENABLE)	{
		for(threadAmount = 9; threadAmount > 0; threadAmount--)	{
			if((srcPoints->size() % threadAmount) == 0)	{
				break;
			}
		}
	}

	#ifdef DEBUGGING
		std::clog << "Point Cloud Registration Information:\n" << 
					 "Transformation Mode: " << mode << "\n" <<
					 "Transformation Scale: " << ratio << "\n" <<
					 "Transformation Error: " << absoluteError << " millimeter(s)\n" <<
					 "Transformation Thread(s): " << threadAmount << " thread(s)\n";
	#endif
	
	// Dialog window to show information
	QString pcrInfo = QString::fromStdString(std::string("Point cloud registration will be preform with the following setting:\n") +
											 "Src Point Cloud Size: " + formatNumber<int>(srcPoints->size()) + " points\n" +
											 "Transformation Mode: " + mode + "\n" +
											 "Transformation Scale: " + std::to_string(ratio) + "\n" +
					  						 "Transformation Error: " + std::to_string(absoluteError) + " millimeter(s)\n" +
					  						 "Transformation Thread(s): " + std::to_string(threadAmount) + " thread(s)\n"
											);

	// Ask user for confirmation on point cloud registration
	QMessageBox::StandardButton userChoice = QMessageBox::question(this, "Point Cloud Registration Information", pcrInfo);

	/*
		Apply transformation to point cloud using thread
	*/
	if(userChoice == QMessageBox::Yes)	{
		if(threadMode == THREAD_ENABLE)	{
			std::thread transformationThreads[threadAmount]; 
			for(int i = 0; i < srcPoints->size(); i += threadAmount)	{
				for(int t = 0; t < threadAmount; t++)	{
					transformationThreads[t] = std::thread(&DistanceGeometryRegistration<pcl::PointXYZRGB>::pointTransformation, 
														   dgr, std::ref(srcPoints->points[i + t]));
				}

				for(int t = 0; t < threadAmount; t++)	{
					transformationThreads[t].join();
				}
			}
		}
		else	{
			dgr->pointCloudTransformation(srcPoints);
		}

		exportPointCloud<pcl::PointXYZRGB>(resultPath, srcPoints);
		QMessageBox::information(this, "Export Point Cloud", 
								 QString::fromStdString("Exported: " + formatNumber<int>(srcPoints->size()) + " points"));
	}

	// Delete DistanceGeometryRegistration instance
	delete dgr;
}
