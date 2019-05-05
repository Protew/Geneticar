/*
 *  TargetOptionsSetWidget.h
 *  GenetiCar_R7
 *
 *  Created by PRoTeW on 09/03/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TARGETOPTIONSSETWIDGET_H
#define TARGETOPTIONSSETWIDGET_H

#include <QtGui> 

#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>

class TargetOptionsSetWidget : public QGroupBox
{
    Q_OBJECT
	
public:
	TargetOptionsSetWidget( QWidget * parent = 0 );
	void initWidgets( void );
	
	public slots:
	void terrainTypeChanged( QString );
	void initialPositionChanged( double );
	void maxTestIntervalChanged( double );
	void wheelsKickDiscountChanged( int );
	void bodyCrashDiscountChanged( int );
	void loopCountDiscountChanged( int );
	void hasObstaclesChanged( int );
	void minXVelocityChanged( double );
	
private:
	
	QHBoxLayout				*	terrain_type_layout;
	QLabel					*	lbl_terrain_type;
	QComboBox				*	cb_terrain_type;
	
	QCheckBox				*	chb_has_obstacles;
	
	QHBoxLayout				*	initial_position_layout;
	QLabel					*	lbl_initial_position;
	QDoubleSpinBox			*	dsb_initial_position;
	
	QHBoxLayout				*	minimum_x_velocity_layout;
	QLabel					*	lbl_minimum_x_velocity;
	QDoubleSpinBox			*	dsb_minimum_x_velocity;
	
	QHBoxLayout				*	maximum_test_interval_layout;
	QLabel					*	lbl_maximum_test_interval;
	QDoubleSpinBox			*	dsb_maximum_test_interval;
	
	QCheckBox			*	chb_wheels_kick_discounted;

	QCheckBox			*	chb_body_crash_discounted;

	QCheckBox			*	chb_loop_count_discounted;
	
	
	//
	QVBoxLayout			*	main_layout;
};

#endif
