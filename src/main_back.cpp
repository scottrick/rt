////	RayTracer 2.0
////	Written by Scott Atkins
////	September 22nd, 2007

//#include "globals.h"
//#include "Scene.h"

////#include <boost/thread.hpp>
//#include <iostream>
////#include <GL/glut.h>
////#include <windows.h>
//using namespace std;

///*
//	----------------------------------------------------------------------------------------------------------
//	FUNCTION DECLARATIONS
//	----------------------------------------------------------------------------------------------------------
//*/
//void		GameKeyboard(unsigned char key, int x, int y);
//void		Go();
//void		Initialize(int argc, char** argv);
//void		InitializeGlutAndGo(int argc, char** argv);
//void		LoopFunction();
//int			main(int argc, char** argv);
//void		MouseClick(int button, int state, int x, int y);
//void		MouseMove(int x, int y);
//void		MousePassiveMove(int x, int y);
//void		RayTrace();
//void		Render();
//void		ReshapeDisplay(GLsizei W, GLsizei H);
//void		SetViewport(int left, int right, int bottom, int top);
//void		ShootRays();

///*
//	----------------------------------------------------------------------------------------------------------
//	GLOBAL VARIABLES
//	----------------------------------------------------------------------------------------------------------
//*/
//Scene			*g_pScene							= 0;
//long			CurrentTime							= 0;
//long			DeltaTime							= 0;
//long			GameTime							= 0;
//int				PreviousRayCount					= 0;
//long			PreviousTime						= 0;
//bool			bLoop								= true;
//bool			bPaused								= false;
//bool			bRayTracedOnce						= false;
//bool			bRayTracing							= false;
//bool			bShowInfo							= false;

//int				STARTING_WINDOW_X					= 640;
//int				STARTING_WINDOW_Y					= 480;
//int				STARTING_WINDOW_DISPLACEMENT_X		= 50;
//int				STARTING_WINDOW_DISPLACEMENT_Y		= 50;
//unsigned int	BUFFER_SIZE_X						= 0;
//unsigned int	BUFFER_SIZE_X_DEFAULT				= STARTING_WINDOW_X;
//unsigned int	BUFFER_SIZE_Y						= 0;
//unsigned int	BUFFER_SIZE_Y_DEFAULT				= STARTING_WINDOW_Y;
//int				MOUSE_X								= 0;
//int				MOUSE_Y								= 0;
//int				WINDOW_X							= 0;
//int				WINDOW_Y							= 0;

///*
//	----------------------------------------------------------------------------------------------------------
//	FUNCTION DEFINITIONS
//	----------------------------------------------------------------------------------------------------------
//*/
//void DrawInfo()
//{
//	if (!bShowInfo || (PreviousRayCount == 0))
//	{
//		return;
//	}

//	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

//	GLboolean bTextureWasOn = glIsEnabled(GL_TEXTURE_2D);
//	GLboolean bLightingWasOn = glIsEnabled(GL_LIGHTING);
	
//	glDisable(GL_LIGHTING);
//	glDisable(GL_TEXTURE_2D); //disable textures when rendering the text

//	{
//		size_t size			= 50;
//		char *pDetails		= (char *)malloc(sizeof(char) * size);
//		memset(pDetails, 0, size);
//		sprintf_s(pDetails, size, "%d milliseconds for last frame", DeltaTime);

//		glRasterPos2f(-0.95f, -0.98f);
//		for (const char *c = pDetails; *c != '\0'; c++)
//		{
//			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
//		}

//		free(pDetails);
//	}

//	{
//		size_t size			= 50;
//		char *pDetails		= (char *)malloc(sizeof(char) * size);
//		memset(pDetails, 0, size);
//		sprintf_s(pDetails, size, "%u rays total in last frame", PreviousRayCount);

//		glRasterPos2f(-0.95f, -0.88f);
//		for (const char *c = pDetails; *c != '\0'; c++)
//		{
//			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
//		}

//		free(pDetails);
//	}

//	{
//		int	raysPerSecond	= (float)PreviousRayCount / ((float)DeltaTime / 1000.0f);
//		size_t size			= 50;
//		char *pDetails		= (char *)malloc(sizeof(char) * size);
//		memset(pDetails, 0, size);
//		sprintf_s(pDetails, size, "%d rays / second", raysPerSecond);

//		glRasterPos2f(-0.95f, -0.78f);
//		for (const char *c = pDetails; *c != '\0'; c++)
//		{
//			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
//		}

//		free(pDetails);
//	}

//	if (bTextureWasOn)
//	{
//		glEnable(GL_TEXTURE_2D);
//	}
//	if (bLightingWasOn)
//	{
//		glEnable(GL_LIGHTING);
//	}
//}

//void GameKeyboard(unsigned char key, int x, int y)
//{
//	if (key == 27) //listen for esc
//	{
//		exit(1);
//	}
//	else if ((key == 'i') || (key == 'I'))
//	{
//		bShowInfo = !bShowInfo;
//	}
//}

//void Go()
//{
//	//printf("GO\n");
//}

//void Initialize(int argc, char** argv)
//{
//	InitializeRandomGenerator(GetTickCount());

//	if (argc > 2) //more than two arguments means we were passed two values, which will be used for the X and Y buffer size
//	{
//		BUFFER_SIZE_X = (unsigned int)atoi(argv[1]);
//		BUFFER_SIZE_Y = (unsigned int)atoi(argv[2]);
//	}
//	else //otherwise just use the default values
//	{
//		BUFFER_SIZE_X = BUFFER_SIZE_X_DEFAULT;
//		BUFFER_SIZE_Y = BUFFER_SIZE_Y_DEFAULT;
//	}

//	g_pScene = new Scene(BUFFER_SIZE_X, BUFFER_SIZE_Y); //create the scene
//	g_pScene->Add("test_in6.txt");
		
//	//start threads
//	for (int i = 0; i < NUM_RAY_THREADS; i++)
//	{
//		boost::thread renderThread(RayTrace);
//	}

//	PreviousTime	= 0;
//	CurrentTime		= GetTickCount();
//}

//void InitializeGlutAndGo(int argc, char** argv) {
//	//glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
//	//glutInitDisplayMode(GLUT_RGB);
//	glutInit(&argc, argv);

//	glutInitWindowPosition(STARTING_WINDOW_DISPLACEMENT_X, STARTING_WINDOW_DISPLACEMENT_Y);
//	glutInitWindowSize(BUFFER_SIZE_X, BUFFER_SIZE_Y);
//	glutCreateWindow("RayTracer 2.0");

//	//glutFullScreen();

//	glEnable(GL_NORMALIZE);

//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glutIdleFunc(LoopFunction);
//	glutDisplayFunc(Go);
//	glutReshapeFunc(ReshapeDisplay);
//	glutKeyboardFunc(GameKeyboard);
//	glutPassiveMotionFunc(MousePassiveMove);
//	glutMouseFunc(MouseClick);
//	glutMotionFunc(MouseMove);

//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
		
//	glutMainLoop();
//}

//void LoopFunction()
//{
//	if (bLoop || !bRayTracedOnce)
//	{
//		//printf("peek=%d\n", g_pScene->PeekNextRayIndex());

//		if ((g_pScene->PeekNextRayIndex() == -1) && (g_pScene->GetThreadCount() == 0))
//		{
//			PreviousRayCount	= g_pScene->GetNumRaysShot();
//			PreviousTime		= CurrentTime;
//			CurrentTime			= GetTickCount();
				
//			if (!bPaused)
//			{
//				DeltaTime = CurrentTime - PreviousTime;
//				GameTime += DeltaTime;

//				g_pScene->Refresh(DeltaTime);
				
//				/*
//				for (int i = 0; i < NUM_RAY_THREADS; i++)
//				{
//					boost::thread renderThread(RayTrace);
//				}
//				*/

//				bRayTracedOnce = true;
//			}
//		}
//	}

//	Render();
//}

///*
//	start the program
//*/
//int main(int argc, char** argv) {
//	printf("RayTracer 2.0\n");
//	printf("Written by Scott Atkins\n");
//	printf("September 22nd, 2007\n\n");

//	Initialize(argc, argv);
//	InitializeGlutAndGo(argc, argv);

//	return 1;
//}

//void MouseClick(int button, int state, int x, int y)
//{

//}

//void MouseMove(int x, int y)
//{

//}

//void MousePassiveMove(int x, int y)
//{

//}

//void RayTrace()
//{
//	g_pScene->ShootRays();
//}

///*
//	Where the actual drawing happens!
//*/
//void Render()
//{
//	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glClear(GL_COLOR_BUFFER_BIT);

//	//glLoadIdentity();

//	//glRasterPos2f(0.1f, 0.5f);
//	glRasterPos2i(-1, -1);
//	//glRasterPos4i((WINDOW_X - BUFFER_SIZE_X) / 2, (WINDOW_Y - BUFFER_SIZE_Y) / 2, 0, 1);

//	/*
//	GLint blah[4];
//	glGetIntegerv(GL_CURRENT_RASTER_POSITION, blah);
//	printf("%d, %d, %d, %d\n", blah[0], blah[1], blah[2], blah[3]);
//	*/

//	//draw the COLOR buffer!
//	//glDrawPixels(BUFFER_SIZE_X, BUFFER_SIZE_Y, GL_RGBA, GL_UNSIGNED_BYTE, g_pScene->GetBuffer()->GetBuffer());
//	glDrawPixels(BUFFER_SIZE_X, BUFFER_SIZE_Y, GL_RGBA, GL_FLOAT, g_pScene->GetBuffer()->GetBuffer());
	
//	DrawInfo();

//	glutSwapBuffers();
//	glFlush();
//}

//void ReshapeDisplay(GLsizei W, GLsizei H)
//{
//	WINDOW_X = (float) W;
//	WINDOW_Y = (float) H;

//	Render();
//}

//void SetViewport(int left, int right, int bottom, int top)
//{
//	glViewport(left, bottom, right - left, top - bottom);
//}
