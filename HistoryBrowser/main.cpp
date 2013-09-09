#include <wx/wx.h>
#include "SkypeChatMainFrame.h"

// application class
class wxMiniApp : public wxApp
{
public:
	// function called at the application initialization
	virtual bool OnInit();

	// event handler for button click
	void OnClick(wxCommandEvent& event) {
		GetTopWindow()->Close();
	}
};

IMPLEMENT_APP(wxMiniApp);

bool wxMiniApp::OnInit()
{
	// create a new frame and set it as the top most application window
	SetTopWindow( new SkypeChatMainFrame(NULL));

	// show main frame
	GetTopWindow()->Show();

	// enter the application's main loop
	return true;
}
