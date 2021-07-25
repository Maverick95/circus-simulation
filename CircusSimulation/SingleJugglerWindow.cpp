#include "SingleJugglerWindow.h"
#include "SettingsEvents.h"


wxBEGIN_EVENT_TABLE(SingleJugglerWindow, DisplayJugglingWindow<ID2D1HwndRenderTarget>)

EVT_SET_COLOUR(SingleJugglerWindow::SetBallColour)

wxEND_EVENT_TABLE()


void SingleJugglerWindow::SetBallColour(SettingsEvents::SetColourEvent& event)
{
	brushCircles->Release();

	GetContext_RenderPattern()->CreateSolidColorBrush(
		D2D1::ColorF(
			(float)(event.Red()) / 256,
			(float)(event.Green()) / 256,
			(float)(event.Blue()) / 256),
		&brushCircles);
}


void SingleJugglerWindow::OnScreenResize_ContextPattern()
{
	wxSize size = GetClientSize();

	for (unsigned int i = 0; i < 3; i++)
	{
		window_widths_x[i] = (unsigned int)((unsigned int)(size.GetWidth()) * window_ratios_x[i] / 2);
	}

	for (unsigned int i = 0; i < 4; i++)
	{
		window_widths_y[i] = (unsigned int)((unsigned int)(size.GetHeight()) * window_ratios_y[i]);
	}
}

void SingleJugglerWindow::OnScreenUpdate_DisplayPattern(const long& time_elapsed)
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		// Define pattern-level variables.

		double beat_time_seconds = ((double)(h->GetPatternBeatTimeMilliseconds())) / 1000;
		double beat_time_elapsed_seconds = ((double)time_elapsed) / 1000;

		unsigned int max_width_pixels = window_widths_x[1] + 2 * window_widths_x[2];
		unsigned int max_height_pixels = window_widths_y[1] / 2 + window_widths_y[2];

		double throw_time_seconds_max_throw = (h->GetDisplayPattern()->GetMaxThrow() - 2 * dwell_ratio) * beat_time_seconds;

		for (unsigned int i = 0; i < h->GetNumberBalls(); i++)
		{
			double lp_plot_x = 0.0, lp_plot_y = 0.0;

			// Only alter if the ball is being thrown.

			const DisplayPatternBall* b = h->GetBall(i);

			if (b->GetState() == STATE_BEING_THROWN)
			{
				// Define ball-level variables.

				unsigned int lp_throw_value = b->GetThrowValue();

				PatternHand handSource =
					(*GetBallSiteSource(i)) == 0 ?
					PatternHand::HAND_LEFT :
					PatternHand::HAND_RIGHT;
				
				PatternHand handDestination =
					(*GetBallSiteDestination(i)) == 0U ?
					PatternHand::HAND_LEFT :
					PatternHand::HAND_RIGHT;
				
				PatternQuerySingleJugglerType patternType =
					h->GetDisplayPattern()->GetNumberActions() > 1U ?
					PatternQuerySingleJugglerType::TYPE_SYNC :
					PatternQuerySingleJugglerType::TYPE_ASYNC;

				unsigned int lp_beats_elapsed = b->GetBeatsElapsed();

				double time_elapsed_seconds = lp_beats_elapsed * beat_time_seconds + beat_time_elapsed_seconds;
				double throw_time_seconds = (lp_throw_value - 2 * dwell_ratio) * beat_time_seconds;
				double total_time_seconds = lp_throw_value * beat_time_seconds;

				// Modify position based on throw being processed.
				// Throw >= 3, regular throw.

				if ((patternType == PatternQuerySingleJugglerType::TYPE_ASYNC && lp_throw_value >= 3U) ||
					(patternType == PatternQuerySingleJugglerType::TYPE_SYNC && lp_throw_value >= 2U))
				{
					// Either ball is in hand or being thrown.

					if (time_elapsed_seconds >= throw_time_seconds)
					{
						// Note - opposite hands where relevant.

						// Offset
						
						switch (handDestination)
						{
						case PatternHand::HAND_LEFT:
							lp_plot_x += window_widths_x[0];
							break;
						case PatternHand::HAND_RIGHT:
							lp_plot_x += window_widths_x[0] + 2 * (window_widths_x[1] + window_widths_x[2]);
							break;
						}
						
						// Time

						double percent_elapsed = (time_elapsed_seconds - throw_time_seconds) / (total_time_seconds - throw_time_seconds);

						double rotation_x = window_widths_x[1] * (1 - cos(M_PI * percent_elapsed)) / 2;
						double rotation_y = window_widths_y[1] * sin(M_PI * percent_elapsed) / 2;

						double multiplier_x = handDestination == PatternHand::HAND_LEFT ? 1.0 : -1.0;
						double multiplier_y = -1.0;

						lp_plot_x += multiplier_x * rotation_x;
						lp_plot_y += multiplier_y * rotation_y;
					}

					else
					{
						// y co-ordinate is same whether even/odd throw.

						lp_plot_y +=
							(4 * max_height_pixels * time_elapsed_seconds) *
							(throw_time_seconds - time_elapsed_seconds) /
							(throw_time_seconds_max_throw * throw_time_seconds_max_throw);

						// x co-ordinate updated differently for even / odd throws.

						// Offset

						switch (handSource)
						{
						case HAND_LEFT:
							lp_plot_x += window_widths_x[0] + window_widths_x[1];
							break;
						case HAND_RIGHT:
							lp_plot_x += window_widths_x[0] + window_widths_x[1] + 2 * window_widths_x[2];
							break;
						}

						// Time

						double multiplier = 0.0;

						switch (handSource)
						{
						case PatternHand::HAND_LEFT:
						{
							switch (handDestination)
							{
							case PatternHand::HAND_LEFT:
								multiplier = -1.0;
								lp_plot_x += multiplier * window_widths_x[1] * time_elapsed_seconds / throw_time_seconds;
								break;
							case PatternHand::HAND_RIGHT:
								multiplier = 1.0;
								lp_plot_x += multiplier * max_width_pixels * time_elapsed_seconds / throw_time_seconds;
								break;
							}
						}
						break;
						case PatternHand::HAND_RIGHT:
						{
							switch (handDestination)
							{
							case PatternHand::HAND_LEFT:
								multiplier = -1.0;
								lp_plot_x += multiplier * max_width_pixels * time_elapsed_seconds / throw_time_seconds;
								break;
							case PatternHand::HAND_RIGHT:
								multiplier = 1.0;
								lp_plot_x += multiplier * window_widths_x[1] * time_elapsed_seconds / throw_time_seconds;
								break;
							}
						}
						break;
						}
					}
				}

				else if ((patternType == PatternQuerySingleJugglerType::TYPE_ASYNC && lp_throw_value == 2U) ||
					(patternType == PatternQuerySingleJugglerType::TYPE_SYNC && lp_throw_value == 1U && handSource == handDestination))
				{
					// Offset

					switch (handSource)
					{
					case PatternHand::HAND_LEFT:
						lp_plot_x += window_widths_x[0] + window_widths_x[1];
						break;
					case PatternHand::HAND_RIGHT:
						lp_plot_x += window_widths_x[0] + window_widths_x[1] + 2 * window_widths_x[2];
						break;
					}

					// Time

					double percent_elapsed = time_elapsed_seconds / total_time_seconds;

					double rotation_x = window_widths_x[1] * (1 - cos(2 * M_PI * percent_elapsed)) / 2;
					double rotation_y = window_widths_y[1] * sin(2 * M_PI * percent_elapsed) / 2;

					double multiplier_x = 0.0;
					double multiplier_y = 1.0;

					switch (handSource)
					{
					case PatternHand::HAND_LEFT:
						multiplier_x = -1.0;
						break;
					case PatternHand::HAND_RIGHT:
						multiplier_x = 1.0;
						break;
					}

					lp_plot_x += multiplier_x * rotation_x;
					lp_plot_y += multiplier_y * rotation_y;
				}

				else if ((patternType == PatternQuerySingleJugglerType::TYPE_ASYNC && lp_throw_value == 1U) ||
				(patternType == PatternQuerySingleJugglerType::TYPE_SYNC && lp_throw_value == 1U && handSource != handDestination))
				{
					// Special relationship.

					double half_beat_time_seconds = 0.5 * beat_time_seconds;

					if (time_elapsed_seconds >= half_beat_time_seconds)
					{
						// Offset
						// Note - opposite hands apply.

						switch (handSource)
						{
						case PatternHand::HAND_LEFT:
							lp_plot_x += window_widths_x[0] + window_widths_x[1] + 2 * window_widths_x[2];
							break;
						case PatternHand::HAND_RIGHT:
							lp_plot_x += window_widths_x[0] + window_widths_x[1];
							break;
						}

						// Time
					}
					else
					{
						// Offset

						switch (handSource)
						{
						case PatternHand::HAND_LEFT:
							lp_plot_x += window_widths_x[0] + window_widths_x[1];
							break;
						case PatternHand::HAND_RIGHT:
							lp_plot_x += window_widths_x[0] + window_widths_x[1] + 2 * window_widths_x[2];
							break;
						}

						// Time

						double multiplier = 0.0;

						switch (handSource)
						{
						case PatternHand::HAND_LEFT:
							multiplier = 1.0;
							break;
						case PatternHand::HAND_RIGHT:
							multiplier = -1.0;
							break;
						}

						lp_plot_x += multiplier * 2 * window_widths_x[2] * time_elapsed_seconds / half_beat_time_seconds;

					}

				}

				// Offset for y is same regardless.

				lp_plot_y += window_widths_y[0] + window_widths_y[1] / 2;

			}

			plot_x[i] = lp_plot_x;
			plot_y[i] = lp_plot_y;
		}
	}
}

void SingleJugglerWindow::OnScreenPaint_RenderPattern(ID2D1HwndRenderTarget* context)
{
	context->BeginDraw();
	context->Clear(D2D1::ColorF(D2D1::ColorF::White));

	auto h = GetValidHandler();

	if (h != NULL)
	{
		for (unsigned int i = 0; i < h->GetNumberBalls(); i++)
		{
			if (h->GetBall(i)->GetState() == STATE_BEING_THROWN)
			{
				D2D1_ELLIPSE point = { { plot_x[i], this->GetClientSize().GetHeight() - plot_y[i] }, 10, 10 };
				context->FillEllipse(point, brushCircles);
				context->DrawEllipse(point, brushCirclesOutlines);
			}
		}
	}

	context->EndDraw();
}

void SingleJugglerWindow::Reset_DisplayJuggling()
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

void SingleJugglerWindow::Populate_DisplayJuggling()
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

void SingleJugglerWindow::SetNumberSites_DisplayJuggling()
{

}

SingleJugglerWindow::SingleJugglerWindow(wxWindow* parent, const unsigned int* w_r_x, const unsigned int* w_r_y, const double& dr)
	: DisplayJugglingWindow(parent, 2),
	plot_x(NULL), plot_y(NULL),
	window_ratios_x(NULL), window_ratios_y(NULL),
	window_widths_x(NULL), window_widths_y(NULL),
	dwell_ratio(dr),
	brushCircles(NULL)
{
	// Modify the dwell ratio as appropriate.

	if (dwell_ratio < 0.0)
	{
		dwell_ratio = 0.0;
	}
	else if (dwell_ratio > 1.0)
	{
		dwell_ratio = 1.0;
	}

	// Set up window ratio elements.

	window_ratios_x = new double[3];
	window_ratios_y = new double[4];

	unsigned int w_r_x_total = 3u;
	unsigned int w_r_y_total = 4u;

	if (w_r_x != NULL)
	{
		w_r_x_total = 0u;
		for (unsigned int i = 0; i < 3; i++) { w_r_x_total += (w_r_x[i] == 0u ? 1u : w_r_x[i]); }
	}

	if (w_r_y != NULL)
	{
		w_r_y_total = 0u;
		for (unsigned int i = 0; i < 4; i++) { w_r_y_total += (w_r_y[i] == 0u ? 1u : w_r_y[i]); }
	}

	for (unsigned int i = 0; i < 3; i++)
	{
		if (w_r_x != NULL)
		{
			window_ratios_x[i] = ((double)(w_r_x[i] == 0u ? 1u : w_r_x[i])) / w_r_x_total;
		}
		else
		{
			window_ratios_x[i] = ((double)(1u)) / w_r_x_total;
		}
	}

	for (unsigned int i = 0; i < 4; i++)
	{
		if (w_r_y != NULL)
		{
			window_ratios_y[i] = ((double)(w_r_y[i] == 0u ? 1u : w_r_y[i])) / w_r_y_total;
		}
		else
		{
			window_ratios_y[i] = ((double)(1u)) / w_r_y_total;
		}
	}

	// Set up the actual widths required.

	window_widths_x = new unsigned int[3];
	window_widths_y = new unsigned int[4];

	OnScreenResize_ContextPattern();

	GetContext_RenderPattern()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Red),
		&brushCircles);

	GetContext_RenderPattern()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black),
		&brushCirclesOutlines);
}

SingleJugglerWindow::~SingleJugglerWindow()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		delete[] plot_x;
		delete[] plot_y;
	}

	delete[] window_ratios_x;
	delete[] window_ratios_y;

	delete[] window_widths_x;
	delete[] window_widths_y;

	brushCircles->Release();
	brushCirclesOutlines->Release();
}
