#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {
	setFocusPolicy(Qt::ClickFocus);
	// Widget Setting/Variables
	// this->grabKeyboard();
	widgetWidth = 0;
	widgetHeight = 0;
	widgetCenterX = 0;
	widgetCenterY = 0;

	// Point Cloud Variables
	pointClouds = RegistrationPointCloudContainer::init(3);
	pointSize = MIN_POINT_SIZE;

	// View Variables
	enableView2 = true;
	enable3DView = false;
	zoomView1 = {1.0, 1.0, 1.0};
	zoomView2 = {1.0, 1.0, 1.0};
	translateView1 = {0.0, 0.0, 0.0};
	translateView2 = {0.0, 0.0, 0.0};
	positionView1 = {0.0, 0.0, 2.0};
	positionView2 = {0.0, 0.0, 2.0};
	centerView1 = {0.0, 0.0, 0.0};
	centerView2 = {0.0, 0.0, 0.0};
	upView1 = {0.0, 0.1, 0.0};
	upView2 = {0.0, 0.1, 0.0};

	// Variables for keeping track
	viewDrag1 = false;
	viewDrag2 = false;
	prevDragX = 0.0;
	prevDragY = 0.0;
	modelViewMatrix1 = new GLdouble[16];
	modelViewMatrix2 = new GLdouble[16];
}

void GLWidget::initializeGL()	{
	if(enable3DView)	{
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glMatrixMode(GL_PROJECTION);
		gluPerspective(75.0, 1.0, .20, 25000.0);
		glMatrixMode(GL_MODELVIEW);
		glClearDepth(1.0f);

		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	}
	else	{
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
		glShadeModel(GL_SMOOTH);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glMatrixMode(GL_PROJECTION);
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	}
}

/*
	2D Class Methods
*/
void GLWidget::drawCrossMark2D(double size, double viewX, double viewY, double width, double height,
							   double clipLeft, double clipRight, double clipBottom, double clipTop)	{
	// Local Variables
	double centerX = width / 2.0, centerY = height / 2.0;
	double hozSize = width * size, verSize = height * size;

	glPushMatrix();
		glViewport(viewX, viewY, width, height);
		glLoadIdentity();
		// set clipping plane
		gluOrtho2D(clipLeft, clipRight, clipBottom, clipTop);
		
		glColor3f(1.0, 1.0, 1.0);	
		// draw the vertical line
		glBegin(GL_LINES);
			glVertex2d(centerX, centerY + verSize);
			glVertex2d(centerX, centerY - verSize);
		glEnd();
		glBegin(GL_LINES);
			glVertex2d(centerX + hozSize, centerY);
			glVertex2d(centerX - hozSize, centerY);
		glEnd();
	
	glPopMatrix();
}
void GLWidget::drawPointCloud2D(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointCloud, 
								double viewX, double viewY, double width, double height,
								double clipLeft, double clipRight, double clipBottom, double clipTop,
								Coordinate3D zoom, Coordinate3D translate, GLdouble* modelViewMatrix)	{
	glPushMatrix();
		glViewport(viewX, viewY, width, height);
		glLoadIdentity();
		gluOrtho2D(clipLeft, clipRight, clipBottom, clipTop);
		// translate and scale the points
		glTranslated(translate.x, translate.y, 0);
		glScaled(zoom.x, zoom.y, 1);

		glPointSize(pointSize);
		glBegin(GL_POINTS);
			for(pcl::PointCloud<pcl::PointXYZRGB>::iterator it = pointCloud->begin(); it != pointCloud->end(); it++)  {
				glColor3f(it->r / 255.0, it->g / 255.0, it->b / 255.0);
				glVertex2d(it->x, it->y);
			}
		glEnd();

		//Update model view matrix
		glGetDoublev(GL_MODELVIEW_MATRIX, modelViewMatrix);

	glPopMatrix();
}

void GLWidget::drawCorrPoints2D(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointCloud, 
								double viewX, double viewY, double width, double height,
								double clipLeft, double clipRight, double clipBottom, double clipTop,
								Coordinate3D zoom, Coordinate3D translate)	{
	glPushMatrix();
		glViewport(viewX, viewY, width, height);
		glLoadIdentity();
		gluOrtho2D(clipLeft, clipRight, clipBottom, clipTop);
		// translate and scale the points
		glTranslated(translate.x, translate.y, 0);
		glScaled(zoom.x, zoom.y, 1);

		glPointSize(pointSize);
		glBegin(GL_POINTS);
			for(int i = 0; i < pointCloud->size(); i++)	{
				// If color not already generated
				if(colorMap.size() <= i)	{
					colorMap.push_back(randomColor());
				}
				glColor3f(colorMap[i].r / 255.0, colorMap[i].g / 255.0, colorMap[i].b / 255.0);
				glVertex2d(pointCloud->points[i].x, pointCloud->points[i].y);
			}
		glEnd();
	glPopMatrix();
}


/*
	3D Class Methods
*/
void GLWidget::drawCrossMark3D(double size, double viewX, double viewY, double width, double height,
							   Coordinate3D positionView, Coordinate3D centerView, Coordinate3D upView)	{
	glPushMatrix();
		glViewport(viewX, viewY, width, height);
		glLoadIdentity();
		gluLookAt(positionView.x, positionView.y, positionView.z, centerView.x, centerView.y, centerView.z,
					  upView.x, upView.y, upView.z);

		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
			glVertex3d(0.0, -size, 10.0);
			glVertex3d(0.0, size, 10.0);
		glEnd();
		glBegin(GL_LINES);
			glVertex3d(-size, 0.0, 10.0);
			glVertex3d(size, 0.0, 10.0);
		glEnd();
	glPopMatrix();
}

void GLWidget::drawPointCloud3D(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointCloud, 
								double viewX, double viewY, double width, double height,
								Coordinate3D positionView, Coordinate3D centerView, Coordinate3D upView,
								Coordinate3D zoom, Coordinate3D translate)	{
	glPushMatrix();
		glViewport(viewX, viewY, width, height);
		glLoadIdentity();
		gluLookAt(positionView.x, positionView.y, positionView.z, centerView.x, centerView.y, centerView.z,
				  upView.x, upView.y, upView.z);
		// translate and scale the points
		glTranslated(translate.x, translate.y, translate.z);
		glScaled(zoom.x, zoom.y, zoom.z);

		glPointSize(pointSize);
		glBegin(GL_POINTS);
			for(pcl::PointCloud<pcl::PointXYZRGB>::iterator it = pointCloud->begin(); it != pointCloud->end(); it++)  {
				glColor3f(it->r / 255.0, it->g / 255.0, it->b / 255.0);
				glVertex3d(it->x, it->y, it->z);
			}
		glEnd();
	glPopMatrix();
}

void GLWidget::drawCorrPoints3D(pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointCloud, 
								double viewX, double viewY, double width, double height,
								Coordinate3D positionView, Coordinate3D centerView, Coordinate3D upView,
								Coordinate3D zoom, Coordinate3D translate)	{
	glPushMatrix();
		glViewport(viewX, viewY, width, height);
		glLoadIdentity();
		gluLookAt(positionView.x, positionView.y, positionView.z, centerView.x, centerView.y, centerView.z,
				  upView.x, upView.y, upView.z);
		// translate and scale the points
		glTranslated(translate.x, translate.y, translate.z);
		glScaled(zoom.x, zoom.y, zoom.z);

		glPointSize(pointSize);
		glBegin(GL_POINTS);
			for(int i = 0; i < pointCloud->size(); i++)	{
				// If color not already generated
				if(colorMap.size() <= i)	{
					colorMap.push_back(randomColor());
				}
				glColor3f(colorMap[i].r / 255.0, colorMap[i].g / 255.0, colorMap[i].b / 255.0);
				glVertex3d(pointCloud->points[i].x, pointCloud->points[i].y, pointCloud->points[i].z);
			}
		glEnd();
	glPopMatrix();
}


/*
	Enabler/Disabler Class Methods
*/
void GLWidget::enableDualView(bool mode)	{
	enableView2 = mode;
}

void GLWidget::enable3DViewer(bool mode)	{
	enable3DView = mode;
}


/*
	Class Methods
*/
pcl::PointXY GLWidget::screenCoordinateToWorldCoordinate(double x, double y, GLdouble* modelViewMatrix)	{
	// prepare Eigen vector and matrix for calculation
	Eigen::VectorXd point(4);
	Eigen::MatrixXd matrix(4, 4);
	point << x, y, 0.0, 1.0;

	// Copy the matrix 
	for(int i = 0; i < 4; i++)	{
		for(int j = 0; j < 4; j++)	{
			matrix(i, j) = modelViewMatrix[j * 4 + i];
		}
	}
	// Compute the world coordinate
	Eigen::VectorXd worldPoint = matrix.inverse() * point;

	return pcl::PointXY({float(worldPoint(0)), float(worldPoint(1))});
}

pcl::PointXYZRGB GLWidget::nearestNeighbor(pcl::PointXY point, pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointCloud,
										   pcl::KdTree<pcl::PointXY>::Ptr kdTree)	{
	if(pointCloud->size() > 1)	{
		std::vector<int> nn_indices(1);
		std::vector<float> nn_dists(1);

		if(kdTree->nearestKSearch(point, 1, nn_indices, nn_dists) > 0)	{
			// std::cout << pointClouds->getPCContainer2D(POINTCLOUD1)->points[nn_indices[0]].x << "  " << 
			// 			 pointClouds->getPCContainer2D(POINTCLOUD1)->points[nn_indices[0]].y << "\n";
			// std::cout << nn_dists[0] << "\n"; 
			if(nn_dists[0] < 2)	{
				return pointCloud->points[nn_indices[0]];
			}
		}
	}

	pcl::PointXYZRGB temp;
	temp.x = -99999999;
	return temp;
}



/*
	Overloading Class Methods
*/

void GLWidget::paintGL()	{
	if(enable3DView)	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	glLoadIdentity();
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*
		Draw the point cloud
	*/
	if(enable3DView)	{
		if(enableView2)	{
			// Draw cross on the center of the screen
			drawCrossMark3D(CROSS_MARK_SIZE, 0.0, 0.0, widgetCenterX, widgetHeight, positionView1, centerView1, upView1);
			// Draw cross on the center of the screen
			drawCrossMark3D(CROSS_MARK_SIZE, widgetCenterX, 0.0, widgetCenterX, widgetHeight, positionView1, centerView1, upView1);
			// draw point cloud 1
			drawPointCloud3D(pointClouds->getPCContainer3D(POINTCLOUD1), 0.0, 0.0, widgetCenterX, widgetHeight,
							 positionView1, centerView1, upView1, zoomView1, translateView1);
			//draw point cloud 2
			drawPointCloud3D(pointClouds->getPCContainer3D(POINTCLOUD2), widgetCenterX, 0.0, widgetCenterX, widgetHeight,
							 positionView1, centerView1, upView1, zoomView1, translateView1);
		}
		else	{
			// Draw cross on the center of the screen
			drawCrossMark3D(CROSS_MARK_SIZE, 0.0, 0.0, widgetWidth, widgetHeight, positionView1, centerView1, upView1);
			// draw point cloud 1
			drawPointCloud3D(pointClouds->getPCContainer3D(POINTCLOUD1), 0.0, 0.0, widgetWidth, widgetHeight,
							 positionView1, centerView1, upView1, zoomView1, translateView1);
		}
	}
	else	{
		if(enableView2)	{
			// Draw cross on the center of the screen
			drawCrossMark2D(CROSS_MARK_SIZE, 0.0, 0.0, widgetCenterX, widgetHeight, 0.0, widgetCenterX, 0.0, widgetHeight);
			// Draw cross on the center of the screen
			drawCrossMark2D(CROSS_MARK_SIZE, widgetCenterX, 0.0, widgetCenterX, widgetHeight, 0.0, widgetCenterX, 0.0, widgetHeight);

			// Draw point cloud 1
			drawPointCloud2D(pointClouds->getPCContainer3D(POINTCLOUD1), 0.0, 0.0, widgetCenterX, widgetHeight,
							 0.0, widgetCenterX, 0.0, widgetHeight, zoomView1, translateView1, modelViewMatrix1);
			// Draw point cloud 2
			drawPointCloud2D(pointClouds->getPCContainer3D(POINTCLOUD2), widgetCenterX, 0.0, widgetCenterX, widgetHeight,
							 0.0, widgetCenterX, 0.0, widgetHeight, zoomView2, translateView2, modelViewMatrix2);
			// Draw Correspondence Points 1
			drawCorrPoints2D(pointClouds->getCorrPCContainer(POINTCLOUD1), 0.0, 0.0, widgetCenterX, widgetHeight,
							 0.0, widgetCenterX, 0.0, widgetHeight, zoomView1, translateView1);
			// Draw Correspondence Points 2
			drawCorrPoints2D(pointClouds->getCorrPCContainer(POINTCLOUD2), widgetCenterX, 0.0, widgetCenterX, widgetHeight,
							 0.0, widgetCenterX, 0.0, widgetHeight, zoomView2, translateView2);
			
		}
		else	{
			// Draw cross on the center of the screen
			drawCrossMark2D(CROSS_MARK_SIZE, 0.0, 0.0, widgetWidth, widgetHeight, 0.0, widgetWidth, 0.0, widgetHeight);
			// draw point cloud 1
			drawPointCloud2D(pointClouds->getPCContainer3D(POINTCLOUD1), 0.0, 0.0, widgetWidth, widgetHeight,
							 0.0, widgetWidth, 0.0, widgetHeight, zoomView1, translateView1, modelViewMatrix1);
		}

	}

	glFlush();
}

void GLWidget::resizeGL(int w, int h)	{
	// update class variables about widget size
	widgetWidth = w;
	widgetHeight = h;
	widgetCenterX = w / 2.0;
	widgetCenterY = h / 2.0;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)   {
	// std::cout << "Mouse Move: " << event->x() <<"  " << event->y() << "  " << event->button() << "\n";
	if(event->buttons() == Qt::LeftButton)	{

	}
	else if(event->buttons() == Qt::MidButton)	{

	}
	else if(event->buttons() == Qt::RightButton)	{
		bool moveUp = ((prevDragY - event->y()) > 0)? true : false;
		bool moveRight = ((prevDragX - event->x()) < 0)? true : false;
		if(viewDrag1)	{
			if(enable3DView)	{
				translateView1.y += (moveUp) ? TRANSLATE_SPEED_3D : -TRANSLATE_SPEED_3D;
				translateView1.x += (moveRight) ? TRANSLATE_SPEED_3D : -TRANSLATE_SPEED_3D;				
			}
			else	{
				translateView1.y += (moveUp) ? TRANSLATE_SPEED_2D : -TRANSLATE_SPEED_2D;
				translateView1.x += (moveRight) ? TRANSLATE_SPEED_2D : -TRANSLATE_SPEED_2D;					
			}
		}
		else	{
			if(enable3DView)	{
				translateView2.y += (moveUp) ? TRANSLATE_SPEED_3D : -TRANSLATE_SPEED_3D;
				translateView2.x += (moveRight) ? TRANSLATE_SPEED_3D : -TRANSLATE_SPEED_3D;				
			}
			else	{
				translateView2.y += (moveUp) ? TRANSLATE_SPEED_2D : -TRANSLATE_SPEED_2D;
				translateView2.x += (moveRight) ? TRANSLATE_SPEED_2D : -TRANSLATE_SPEED_2D;				
			}
		}
		prevDragX = event->x();
		prevDragY = event->y();
	}

	// force update frame
	update();
}

void GLWidget::mousePressEvent(QMouseEvent *event)  {
	if(event->button() == Qt::LeftButton)	{
		int pixelX = event->x(), pixelY = widgetHeight - event->y();
		if(enableView2)	{
			if(event->x() < widgetCenterX)	{
				double scaleX = (((double)pixelX / widgetCenterX) * 2.0) - 1.0;
				double scaleY = (((double)pixelY / widgetHeight) * 2.0) - 1.0;
				/*
					Compute the world point coordinate
				*/
				pcl::PointXY worldPoint = screenCoordinateToWorldCoordinate(scaleX, scaleY, modelViewMatrix1);
				// Perform Nearest Neighbor Search
				pcl::PointXYZRGB cloestPoint = nearestNeighbor(worldPoint,
															   pointClouds->getPCContainer3D(POINTCLOUD1),
															   pointClouds->getKdTree(POINTCLOUD1));
				// add point to the correspondence point container
				if(cloestPoint.x != -99999999)	{
					pointClouds->getCorrPCContainer(POINTCLOUD1)->push_back(cloestPoint);
				}
			}
			else	{
				double scaleX = (((double)(pixelX - widgetCenterX) / widgetCenterX) * 2.0) - 1.0;
				double scaleY = (((double)pixelY / widgetHeight) * 2.0) - 1.0;
				/*
					Compute the world point coordinate
				*/
				pcl::PointXY worldPoint = screenCoordinateToWorldCoordinate(scaleX, scaleY, modelViewMatrix2);
				// Perform Nearest Neighbor Search
				pcl::PointXYZRGB cloestPoint = nearestNeighbor(worldPoint,
															   pointClouds->getPCContainer3D(POINTCLOUD2),
															   pointClouds->getKdTree(POINTCLOUD2));
				// add point to the correspondence point container
				if(cloestPoint.x != -99999999)	{
					pointClouds->getCorrPCContainer(POINTCLOUD2)->push_back(cloestPoint);
				}
			}
		}
		else	{
			double scaleX = (((double)pixelX / widgetWidth) * 2.0) - 1.0;
			double scaleY = (((double)pixelY / widgetHeight) * 2.0) - 1.0;
			/*
				Compute the world point coordinate
			*/
			pcl::PointXY worldPoint = screenCoordinateToWorldCoordinate(scaleX, scaleY, modelViewMatrix1);
			// Perform Nearest Neighbor Search
			pcl::PointXYZRGB cloestPoint = nearestNeighbor(worldPoint,
														   pointClouds->getPCContainer3D(POINTCLOUD1),
														   pointClouds->getKdTree(POINTCLOUD1));
			// add point to the correspondence point container
			if(cloestPoint.x != -99999999)	{
				pointClouds->getCorrPCContainer(POINTCLOUD1)->push_back(cloestPoint);
			}
		}
	}
	else if(event->button() == Qt::MidButton)	{

	}
	else if(event->button() == Qt::RightButton)	{
		if(enableView2)	{
			if(event->x() < widgetCenterX)	{
				viewDrag1 = true;
			}
			else	{
				viewDrag2 = true;
			}
		}
		else	{
			viewDrag1 = true;
		}
		prevDragX = event->x();
		prevDragY = event->y();
	}
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)  {
	if(enableView2)	{
		if(event->x() < widgetCenterX)	{
			viewDrag1 = false;
		}
		else	{
			viewDrag2 = false;
		}
	}
	else	{
		viewDrag1 = false;
	}
}

void GLWidget::wheelEvent(QWheelEvent * event)	{
	// change made to view 1
	if(enableView2)	{
		if(event->x() < widgetCenterX)	{
			if(event->delta() > 0)	{
				zoomView1.x *= ZOOM_SPEED;
				zoomView1.y = zoomView1.x;
			}
			else	{
				zoomView1.x /= ZOOM_SPEED;
				zoomView1.y = zoomView1.x;
			}
		}
		// changes to view 2
		else	{
			if(event->delta() > 0)	{
				zoomView2.x *= ZOOM_SPEED;
				zoomView2.y = zoomView2.x;
			}
			else	{
				zoomView2.x /= ZOOM_SPEED;
				zoomView2.y = zoomView2.x;
			}
		}
	}
	else	{
		if(event->delta() > 0)	{
			zoomView1.x *= ZOOM_SPEED;
			zoomView1.y = zoomView1.x;
		}
		else	{
			zoomView1.x /= ZOOM_SPEED;
			zoomView1.y = zoomView1.x;
		}
	}

	// force update frame
	update();
}


void GLWidget::keyPressEvent(QKeyEvent* event)	{
	switch (event->key()) {
		case Qt::Key_C:
			zoomView1 = {1.0, 1.0, 1.0};
			zoomView2 = {1.0, 1.0, 1.0};
			translateView1 = {0.0, 0.0, 0.0};
			translateView2 = {0.0, 0.0, 0.0};
			break;
		case Qt::Key_R:
			zoomView1 = {1.0, 1.0, 1.0};
			zoomView2 = {1.0, 1.0, 1.0};
			translateView1 = {0.0, 0.0, 0.0};
			translateView2 = {0.0, 0.0, 0.0};
			pointSize = MIN_POINT_SIZE;
			break;
		case Qt::Key_U:
			break;
		case Qt::Key_D:
			break;
		case Qt::Key_Plus:
			if(pointSize + 1 <= MAX_POINT_SIZE)
				pointSize += 1;
			break;
		case Qt::Key_Minus:
			if(pointSize - 1 >= MIN_POINT_SIZE)
				pointSize -= 1;
			break;
		default:
			event->ignore();
			break;
	}

	// force update frame
	update();
}

Color GLWidget::randomColor()	{
	// Generate number between 0 - 255
	unsigned int r = rand() % 256;
	unsigned int g = rand() % 256;
	unsigned int b = rand() % 256;

	return Color({r, g, b});
}
