/*
 *  CarInfoWidget.h
 *  GenetiCar_R4
 *
 *  Created by PRoTeW on 07/03/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

/*
 *  CarInfoWidget.h
 *  3DChallenge
 *
 *  Created by PRoTeW on 15/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CARINFOWIDGET_H
#define CARINFOWIDGET_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "GLCarViewer.h"

class CarInfoWidget : public QWidget
{
	Q_OBJECT
	
public:
	CarInfoWidget( QWidget* );
	void initComponents( void );
	//
	//SETs
	void setCar( GeneticCar * ); 
	void setDescription( QString * );
	
private:
	
	//VIEWER
	GLCarViewer		*	car_viewer;
	//
	QLabel			*	lbl_description;
	QLabel			*	lbl_car_id;
	//
	QHBoxLayout		*	car_description_layout;
	//
	QVBoxLayout		*	main_layout;
};

#endif
