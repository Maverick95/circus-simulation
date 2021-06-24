#include "BallStatusWindow.h"
#include <algorithm>



void BallStatusWindow::OnBallsUpdate()
{
	// Colour the throw boxes.

	auto h = GetValidHandler();

	if (h != NULL)
	{
		unsigned int numberBalls = h->GetNumberBalls();
		unsigned int numberActions = h->GetDisplayPattern()->GetNumberActions();

		bool* ballStatus = new bool[numberBalls];

		for (unsigned int i = 0U; i < numberBalls; i++)
		{
			ballStatus[i] = false;
		}
		
		for (unsigned int i = 0U; i < numberActions; i++)
		{
			const unsigned int* n = h->GetDisplayPattern()->GetBall(h->GetMappingCurrent(), i);
			if (n != NULL) { ballStatus[*n] = true; }
		};

		for (unsigned int i = 0U; i < numberBalls; i++)
		{
			pattern_balls[i]->SetBackgroundColour(ballStatus[i] ? (*wxGREEN) : (*wxLIGHT_GREY));
		}

		delete[] ballStatus;
	}
}

void BallStatusWindow::OnScreenUpdate(const long & time_elapsed)
{

}

void BallStatusWindow::OnScreenPaint(wxWindow* context)
{
	wxAutoBufferedPaintDC dc(context);
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
}

void BallStatusWindow::ResetD1()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		unsigned int num_balls = h->GetNumberBalls();

		for (unsigned int i = 0; i < num_balls; i++)
		{
			delete pattern_balls[i];
		}

		delete[] pattern_balls;
	}

	pattern_balls = NULL;
}

void BallStatusWindow::OnScreenResize()
{
	this->Layout();
}

void BallStatusWindow::PopulateD1()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		unsigned int num_balls = h->GetNumberBalls();

		pattern_balls = new wxStaticText*[num_balls];

		for (unsigned int i = 0; i < num_balls; i++)
		{
			pattern_balls[i] = new wxStaticText(this, -1, wxString(std::to_string(i + 1)),
				wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);

			pattern_balls[i]->SetBackgroundColour(*wxLIGHT_GREY);
		}

		// All sizers will be called sz_X_[something], where X is the depth of the sizer.
		// 0 is the top sizer.

		wxBoxSizer * sz_0 = new wxBoxSizer(wxVERTICAL);

		/*
		sz_1_balls_index
		Just displays the indices 1 to n_balls.
		*/

		wxBoxSizer * sz_1_balls_index = new wxBoxSizer(wxHORIZONTAL);

		for (unsigned int i = 0; i < num_balls; i++)
		{
			sz_1_balls_index->Add(pattern_balls[i], 1, wxEXPAND | wxALL, 10);
		}

		sz_0->Add(sz_1_balls_index, 0, wxEXPAND);

		SetSizer(sz_0);
	}
}

void BallStatusWindow::StopD1()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		for (unsigned int i = 0; i < h->GetNumberBalls(); i++)
		{
			if (pattern_balls[i]->GetBackgroundColour() == *wxGREEN)
			{
				pattern_balls[i]->SetBackgroundColour(*wxLIGHT_GREY);
				pattern_balls[i]->Refresh(false, NULL);
			}
		}
	}
}

BallStatusWindow::BallStatusWindow(wxWindow * parent)
	:
	ContextPatternWindow(parent),
	pattern_balls(NULL)
{

}

BallStatusWindow::~BallStatusWindow()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		unsigned int num_balls = h->GetNumberBalls();

		for (unsigned int i = 0; i < num_balls; i++)
		{
			delete pattern_balls[i];
		}

		delete[] pattern_balls;
	}
}