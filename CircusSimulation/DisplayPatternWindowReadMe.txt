23/05/2021

This is a rough outline of the class hierarchy of the windows used to
visualise juggling patterns, and the functionality managed / included at each level.



DisplayPatternWindow

1) Manages link to the Pattern Handler.
2) Handles the regular drawing of the screen (but passes invalidation to child)
3) Handles addition of a new pattern to the screen.
3) Handles starting / stopping of timer for updating screen.

Properties retrieved -

the valid handler (NULL if invalid - use as consistent test in derived functions)

Functions to be filled in -

void OnBallsUpdate()
void OnScreenUpdateD1(const long &)
void ResetD1()
void PopulateD1()
void StopD1()



		DisplayPatternWxWindow

		1) Manages basic painting and resizing for windows drawn with wxWidgets.
		2) On drawing, automatically fills in white backgrounds.

		Functions to be filled in -

		void OnBallsUpdate()
		void OnScreenUpdateD1(const long &)
		void ResetD1()
		void PopulateD1()
		void StopD1()

		void OnScreenPaintD1(wxAutoBufferedPaintDC& dc)



		DisplayPatternDirect2dWindow

		1) Manages basic painting and resizing for windows drawn with Direct2D.
		2) On drawing, automatically fills in white backgrounds.

		Properties retrieved -

		the render target (used to create brushes and draw)

		Functions to be filled in -

		void OnBallsUpdate()
		void OnScreenUpdateD1(const long &)
		void ResetD1()
		void PopulateD1()
		void StopD1()

		void OnScreenResizeD1()
		void OnScreenPaintD1()



				DisplayJugglingWindow
				
				1) Handles data regarding mapping of actions to sites.

				Implemented functions -

				void OnBallsUpdate()
				void ResetD1();
				void PopulateD1();
				void StopD1();

				Functions to be filled in -

				void OnScreenUpdateD1(const long &)
				void OnScreenResizeD1()
				void OnScreenPaintD1()
				void OnBallsUpdateD1()
				void ResetD2()
				void PopulateD2()



		





