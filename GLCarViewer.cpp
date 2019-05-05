/*
 *  GLCarViewer.cpp
 *  GenetiCar_R3
 *
 *  Created by PRoTeW on 05/03/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLCarViewer.h"
#include "GLWorldWidget.h"

b2Vec2* GLCarViewer ::QTtoOpenGl( b2Vec2* coord )
{
	//TRANSFORMA COORD QT -> OpenGl
	float32 wx = coord->x;
	float32 vxmax = (float32) xview + width;
	float32 vxmin = (float32) xview;
	float32 wxmax = (float32) width;
	float32 wxmin = (float32) 0;
	//
	float32 wy = coord->y;
	float32 vymax = (float32) yview;
	float32 vymin = (float32) yview + height;
	float32 wymax = (float32) height;
	float32 wymin = (float32) 0;
	
	return new b2Vec2( ( ( vxmax - vxmin )/( wxmax - wxmin ) ) * ( wx - wxmin ) + vxmin, ( ( vymax - vymin )/( wymax - wymin ) ) * ( wy - wymin ) + vymin );
}
b2Vec2* GLCarViewer :: OpenGltoQT( b2Vec2* coord )
{
	//TRANSFORMA OpenGl -> COORD QT
	float32 wx = coord->x;
	float32 vxmax = (float32) width;
	float32 vxmin = (float32) 0;
	float32 wxmax = (float32) xview + width;
	float32 wxmin = (float32) xview;
	//
	float32 wy = coord->y;
	float32 vymax = (float32) height;
	float32 vymin = (float32) 0;
	float32 wymax = (float32) yview;
	float32 wymin = (float32) yview + height;
	
	return new b2Vec2( ( ( vxmax - vxmin )/( wxmax - wxmin ) ) * ( wx - wxmin ) + vxmin, ( ( vymax - vymin )/( wymax - wymin ) ) * ( wy - wymin ) + vymin );
}
b2Vec2* GLCarViewer ::OpenGltoBox2d( b2Vec2* coord ) 
{
	//TRANSFORMA COORD OpenGl -> BOX2D
	float32 wx = coord->x;
	float32 vxmax = (float32) width/2;
	float32 vxmin = (float32) 0;
	float32 wxmax = (float32) width;
	float32 wxmin = (float32) 0;
	//
	float32 wy = coord->y;
	float32 vymax = (float32) 0;
	float32 vymin = (float32) height/2;
	float32 wymax = (float32) 0;
	float32 wymin = (float32) height;
	
	return new b2Vec2( ( ( vxmax - vxmin )/( wxmax - wxmin ) ) * ( wx - wxmin ) + vxmin, ( ( vymax - vymin )/( wymax - wymin ) ) * ( wy - wymin ) + vymin );
}
b2Vec2* GLCarViewer :: Box2dtoOpenGl( b2Vec2* coord ) 
{
	//TRANSFORMA COORD BOX2D -> OpenGl
	float32 wx = coord->x;
	float32 vxmax = (float32) width;
	float32 vxmin = (float32) 0;
	float32 wxmax = (float32) width/2;
	float32 wxmin = (float32) 0;
	//
	float32 wy = coord->y;
	float32 vymax = (float32) 0;
	float32 vymin = (float32) height;
	float32 wymax = (float32) 0;
	float32 wymin = (float32) height/2;
	
	return new b2Vec2( ( ( vxmax - vxmin )/( wxmax - wxmin ) ) * ( wx - wxmin ) + vxmin, ( ( vymax - vymin )/( wymax - wymin ) ) * ( wy - wymin ) + vymin );
}
GLCarViewer :: GLCarViewer( QWidget *parent, double W, double H ) 
: QGLWidget( parent )
{	
	width = W;
	height = H;
	//
	xview = yview = 0;
	//
	individue = NULL;
	//
	//
	timer = new QTimer;
	connect( timer, SIGNAL( timeout() ), this, SLOT( turn() ) );
	//timer->start(33);
	//
	setFormat( QGLFormat( QGL::DoubleBuffer | QGL::DepthBuffer ) );
	setFixedSize( width, height );
	//
	setFocus();
}
void GLCarViewer :: turn( void )
{	
	updateGL();
}
void GLCarViewer :: createDisplayList( void )
{
	//PEGA UM NUMERO DE LISTA DISPONÍVEL
	display_list = glGenLists( 1 );
	//INVOCA A LISTA
	glNewList( display_list, GL_COMPILE_AND_EXECUTE );
	//PREENCHE COM OS VÉRTICES
	fillDisplayList();
	//FIM DA CRIAÇÃO 
	glEndList();
}
void GLCarViewer :: fillDisplayList( void )
{
	individue->drawCommands();
}
void GLCarViewer :: setTarget( GeneticCar * T )
{
	individue = T;
	//
	if( individue )
	{
		xview = individue->getBody()->GetWorldCenter().x - width/2;
		yview = individue->getBody()->GetWorldCenter().y - height/2;
		makeCurrent();
		projection();
		//makeCurrent();
		createDisplayList();
		//makeCurrent();
		updateGL();
	}
	else {
		xview = yview = 0;
		makeCurrent();
		projection();
		updateGL();
	}

}
void GLCarViewer :: initializeGL( void )
{
	//PRERROGATIVAS OpenGl
	
	glViewport( 0, 0, width, height );
	
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ();
	
	gluOrtho2D( xview, xview + width, yview, yview + height );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_DEPTH_TEST);                 
	glEnable(GL_NORMALIZE);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	
	glShadeModel (GL_SMOOTH);
	
	individue = NULL;
}
void GLCarViewer :: paintGL() 
{
	glClearColor ( 0.8, 0.8, 0.8, 0.0 );
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glPushMatrix();
	//
	if( individue )
	{
		makeCurrent();
		glCallList( display_list ); 
	}
	else {
		glLineWidth( 100 );
		glColor3f( 0.0, 0.0, 0.0 );
		glBegin( GL_LINES );
		//DIAGONAL SECUNDARIA
		glVertex2f( 0.0, 0.0 );
		glVertex2f( 200.0, 200.0 );
		//DIAGONAL PRINCIPAL
		glVertex2f( 0.0, 200.0 );
		glVertex2f( 200.0, 0.0 );
		glEnd();
		glLineWidth( 1 );
	}
	//
	glPopMatrix();
	glDisable( GL_BLEND );
}
void GLCarViewer :: projection( void )
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	
	gluOrtho2D( xview, xview + width, yview, yview + height );
	
	glMatrixMode ( GL_MODELVIEW );
	glLoadIdentity ();
}
void GLCarViewer :: keyPressEvent( QKeyEvent * event )
{
	switch( event->key() )
	{
			//ESC
		case 16777216:  
			exit(0);
			break;
		case 27:
			break;
		case 32: 
			break;
		case '-':
			break;
		case '=':
			break;
		case '1': 
			break;
		case '2': 
			break;
		case '3': 
			break;
		case '4': 
			break;
		case '5': 
			break;
		case '6': 
			break;
		case '7': 
			break;
		case '8': 
			break;
		case '9': 
			break;
		case '0': 
			break;
		case 'a':
		case 'A': 
			break;
		case 'b':
		case 'B': 
			break;
		case 'c':
		case 'C': 
			break;
		case 'd':
		case 'D': 
			break;
		case 'e':
		case 'E': 
			break;
		case 'f':
		case 'F': 
			break;
		case 'g':
		case 'G':
			break;
		case 'h':
		case 'H':
			break;
		case 'i':
		case 'I':
			break;
		case 'j':
		case 'J':
			break;
		case 'k':
		case 'K':
			break;
		case 'l':
		case 'L':
			break;
		case 'm':
		case 'M':
			break;
		case 'n':
		case 'N':
			break;
		case 'o':
		case 'O':
			break;
		case 'p':
		case 'P':
			break;
		case 'q':
		case 'Q':
			break;
		case 'r':
		case 'R':
			break;
		case 's':
		case 'S':
			break;
		case 't':
		case 'T':
			break;
		case 'u':
		case 'U':
			break;
		case 'v':
		case 'V':
			break;
		case 'w':
		case 'W':
			break;
		case 'x':
		case 'X':
			break;
		case 'y':
		case 'Y':
			break;
		case 'z':
		case 'Z':
			break;
			//RIGHT
		case 16777236:
			xview += 10;
			break;
			//LEFT
		case 16777234:
			if( xview >= 10 )
				xview -= 10;
			else
				xview = 0;
			break;
			//UP
		case 16777235:
			yview += 10;
			break;
			//DOWN
		case 16777237:
			if( yview >= 10 )
				yview -= 10;
			else
				yview = 0;
			break;
	}
	event->accept();
}
void GLCarViewer :: mouseAction( QMouseEvent * event ) 
{
	event->accept();
}
void GLCarViewer :: mousePressEvent( QMouseEvent * event ) 
{
	std :: cout << "( " << event->x() << ", " << event->y() << " )" << std :: endl;
} 
void GLCarViewer :: mouseMoveEvent( QMouseEvent * event ) 
{
	event->accept();
} 
void GLCarViewer :: mouseReleaseEvent( QMouseEvent * event )
{
	event->accept();
}
