#include "PoolJugglers2dWindow.h"

#include <cmath>

PoolJugglers2dWindow::PoolJugglers2dWindow(wxWindow* parent, const unsigned int& ns)
	: DisplayJugglingWindow(parent, ns),
	site_x(NULL), site_y(NULL),
	plot_x(NULL), plot_y(NULL),
	brushBlack(NULL)
{
	const auto num_sites = GetNumberSites();
	site_x = new double[num_sites];
	site_y = new double[num_sites];

	GetContext_RenderPattern()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black),
		&brushBlack);

	UpdateSiteCoordinates();
}

PoolJugglers2dWindow::~PoolJugglers2dWindow()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		delete[] plot_x;
		delete[] plot_y;
	}

	delete[] site_x;
	delete[] site_y;

	brushBlack->Release();
}

void PoolJugglers2dWindow::UpdateSiteCoordinates()
{
	const auto num_sites = GetNumberSites();
	const auto size = GetClientSize();
	const double width = size.GetWidth() / 2.0, height = size.GetHeight() / 2.0;

	for (auto i = 0U; i < num_sites; i++)
	{
		site_x[i] = width;
		site_y[i] = height;
	}

	if (num_sites > 1U)
	{ 
		// TODO - move setting to Settings class.
		const double radioFromMiddle = 0.7;

		const auto
			width_extra = radioFromMiddle * width,
			height_extra = radioFromMiddle * height;

		for (auto i = 0U; i < num_sites; i++)
		{
			const auto radians = (2 * M_PI * i) / num_sites;
			site_x[i] += width_extra * sin(radians);
			site_y[i] -= height_extra * cos(radians);
		}
	}
}

void PoolJugglers2dWindow::OnScreenUpdate_DisplayPattern(const long& time_elapsed)
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		// Define pattern-level variables.

		double beat_time_seconds = ((double)(h->GetPatternBeatTimeMilliseconds())) / 1000;
		double beat_time_elapsed_seconds = ((double)time_elapsed) / 1000;

		for (unsigned int i = 0; i < h->GetNumberBalls(); i++)
		{
			double lp_plot_x = 0.0, lp_plot_y = 0.0;

			// Only alter if the ball is being thrown.

			const DisplayPatternBall* b = h->GetBall(i);

			if (b->GetState() == STATE_BEING_THROWN)
			{
				double time_elapsed_seconds = b->GetBeatsElapsed() * beat_time_seconds + beat_time_elapsed_seconds;
				double total_time_seconds = b->GetThrowValue() * beat_time_seconds;

				double time_percentage_passed =
					(total_time_seconds == 0.0 ?
						0.0 :
						time_elapsed_seconds / total_time_seconds);

				const auto site_source = (*GetBallSiteSource(i));
				const auto site_destination = (*GetBallSiteDestination(i));

				lp_plot_x = (1.0 - time_percentage_passed) * site_x[site_source] + time_percentage_passed * site_x[site_destination];
				lp_plot_y = (1.0 - time_percentage_passed) * site_y[site_source] + time_percentage_passed * site_y[site_destination];
			}

			plot_x[i] = lp_plot_x;
			plot_y[i] = lp_plot_y;
		}
	}
}

void PoolJugglers2dWindow::OnScreenPaint_RenderPattern(ID2D1HwndRenderTarget* context)
{
	context->BeginDraw();
	context->Clear(D2D1::ColorF(D2D1::ColorF::White));

	auto h = GetValidHandler();

	const auto num_sites = GetNumberSites();

	for (auto i = 0U; i < num_sites; i++)
	{
		D2D1_ELLIPSE point = { { site_x[i], site_y[i] }, 10, 10 };
		context->FillEllipse(point, brushBlack);
	}

	if (h != NULL)
	{
		for (unsigned int i = 0; i < h->GetNumberBalls(); i++)
		{
			if (h->GetBall(i)->GetState() == STATE_BEING_THROWN)
			{
				D2D1_ELLIPSE point = { { plot_x[i], plot_y[i] }, 10, 10 };
				context->DrawEllipse(point, brushBlack);
			}
		}
	}

	context->EndDraw();
}

void PoolJugglers2dWindow::OnScreenResize_ContextPattern()
{
	UpdateSiteCoordinates();
}

void PoolJugglers2dWindow::OnBallsUpdate_DisplayJuggling()
{

}

void PoolJugglers2dWindow::Reset_DisplayJuggling()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		delete[] plot_x;
		delete[] plot_y;
	}

	plot_x = NULL; plot_y = NULL;

	Refresh(false, NULL);
}

void PoolJugglers2dWindow::Populate_DisplayJuggling()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		// Set up co-ordinate elements.

		unsigned int num_balls = h->GetNumberBalls();
		plot_x = new double[num_balls];
		plot_y = new double[num_balls];
	}

}

