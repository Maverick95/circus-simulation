23/05/2021

This is a rough outline of the class hierarchy of the windows used to
visualise juggling patterns, and the functionality managed / included at each level.



DisplayPatternWindow

1) Manages link to the Pattern Handler.
2) Handles the regular drawing of the screen,
3) Handles addition of a new pattern to the screen.
3) Handles starting / stopping of timer for updating screen.

Properties retrieved -

the valid handler (NULL if invalid - use as consistent test in derived functions)

Functions to be filled in -

void OnBallsUpdate_DisplayPattern()
void OnScreenUpdate_DisplayPattern(const long &)
void Reset_DisplayPattern()
void Populate_DisplayPattern()
void Stop_DisplayPattern()



		RenderPatternWindow<class T>

		T is the class required in order for the window to handle ALL drawing functionality.
		This involves the creation / destruction of contexts.

		e.g.
		for wxWidgets windows, T is wxWindow, because this creates / destroys the context.
		for Direct2D windows, T is ID2D1HwndRenderTarget.

		Functions to be filled in -

		T* GetContext_RenderPattern()
		void OnScreenPaint_RenderPattern(T* context)
		void OnScreenResize_RenderPattern()
		---
		void OnBallsUpdate_DisplayPattern()
		void OnScreenUpdate_DisplayPattern(const long &)
		void Reset_DisplayPattern()
		void Populate_DisplayPattern()
		void Stop_DisplayPattern()



				ContextPatternWindow<class T>

				Dummy empty class, this allows individual class types to customise their internal definition.

				###

				ContextPatternWindow<wxWindow>

				Implemented functions -

				wxWindow* GetContext_RenderPattern()

				Functions to be filled in -

				void OnScreenPaint_RenderPattern(T* context)
				void OnScreenResize_RenderPattern()
				---
				void OnBallsUpdate_DisplayPattern()
				void OnScreenUpdate_DisplayPattern(const long &)
				void Reset_DisplayPattern()
				void Populate_DisplayPattern()
				void Stop_DisplayPattern()

				###

				ContextPatternWindow<ID2D1HwndRenderTarget>

				Implemented functions -

				ID2D1HwndRenderTarget* GetContext_RenderPattern();
				void OnScreenResize_RenderPattern();

				Functions to be filled in -

				void OnScreenResize_ContextPattern()
				---
				void OnScreenPaint_RenderPattern(T* context)
				---
				void OnBallsUpdate_DisplayPattern()
				void OnScreenUpdate_DisplayPattern(const long &)
				void Reset_DisplayPattern()
				void Populate_DisplayPattern()
				void Stop_DisplayPattern()



						DisplayJugglingWindow<class T>
				
						1) Handles data regarding mapping of actions to sites.

						Implemented functions -

						void OnBallsUpdate_DisplayPattern()
						void Reset_DisplayPattern();
						void Populate_DisplayPattern();
						void Stop_DisplayPattern();

						Functions to be filled in -

						void OnBallsUpdate_DisplayJuggling()
						void Reset_DisplayJuggling()
						void Populate_DisplayJuggling()
