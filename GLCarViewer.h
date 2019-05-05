/*
 *  GLCarViewer.h
 *  GenetiCar_R3
 *
 *  Created by PRoTeW on 05/03/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GLCARVIEWER_H
#define GLCARVIEWER_H

#include <QtGui> 
#include <QTimer>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

#include "GroundBlock.h"
#include "GeneticCar.h"

class GLCarViewer : public QGLWidget {
	
	Q_OBJECT
	
private: 
	//
	float32 xview;
	float32 yview;
	//
	long clock;
	QTimer * timer;
	//
	b2Vec2 position;
	//
	double width;
	double height;
	//
	//OBJECTS
	GeneticCar * individue;
	std :: list<b2Fixture*> :: iterator iter;
	std :: list<b2Fixture*> fixtures;
	GLuint display_list;
	//
	//LAYOUT
	//
	QVBoxLayout * main_layout;
	QLabel		* lbl_description;
	//
	public slots:
	void turn( void );
	
public: 
	GLCarViewer( QWidget *, double, double );
	//
	void projection( void );
	//
	b2Vec2* QTtoOpenGl( b2Vec2* );
	b2Vec2* OpenGltoQT( b2Vec2* );
	b2Vec2* OpenGltoBox2d( b2Vec2* );
	b2Vec2* Box2dtoOpenGl( b2Vec2* );
	void mousePress( int, int, int ); 
	void mouseMotion( int, int );
	void mouseAction( QMouseEvent * );
	//
	void setTarget( GeneticCar * );
	void createDisplayList( void );
	void fillDisplayList( void );
	
	
protected: 
	void initializeGL( void ); 
	//void resizeGL( int, int ); 
	void paintGL( void ); 
	void keyPressEvent( QKeyEvent * );
	void mousePressEvent( QMouseEvent * ); 
	void mouseMoveEvent( QMouseEvent * ); 
	void mouseReleaseEvent( QMouseEvent * );
	//void mouseDoubleClickEvent(QMouseEvent *);
	void initComponents( void );
};

#endif
