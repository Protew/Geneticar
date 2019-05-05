/*
 *  MainWindow.cpp
 *  PDBQuickViewer_04
 *
 *  Created by PRoTeW on 26/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "MainWindow.h"

MainWindow :: MainWindow( QWidget * parent )
:QTabWidget( parent )
{
	initWidgets();
	setWindowTitle( tr( " GENETIC CAR OPTIMIZATION " ) );
	//setFixedSize(sizeHint().width(), sizeHint().height());
}
void MainWindow::initWidgets( void )
{
	world_widget = new GLWorldWidget( this );
	//
	//MAIN LAYOUT
	//
	main_layout = new QVBoxLayout;
	main_layout->addWidget( world_widget );
	setLayout( main_layout );
}