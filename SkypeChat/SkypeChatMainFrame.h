#ifndef __SkypeChatMainFrame__
#define __SkypeChatMainFrame__

/**
@file
Subclass of MainFrame, which is generated by wxFormBuilder.
*/

#include "ClassPrototypes.h"


#include "wx/wxsqlite3.h"
#include <ctime>
#include <iostream>

using namespace std;

/** Implementing MainFrame */
class SkypeChatMainFrame : public MainFrame
{
protected:
	// Handlers for MainFrame events.
	void OnContactChage(wxCommandEvent& event);
	void OnRefresh( wxCommandEvent& event );
	void OnSelectAll( wxCommandEvent& event );
	void OnRemove( wxCommandEvent& event );
	void OnChange( wxCommandEvent& event );
	void OnClose( wxCommandEvent& event );
	
	void Init();
	void Connect();
	void InitContacts();
	void RefreshMessages();
	
	
public:
	/** Constructor */
	SkypeChatMainFrame( wxWindow* parent );
	
private:
	wxString m_szDbFile;

	wxSQLite3Database* m_db;
	
#if wxUSE_REGEX
	wxSQLite3RegExpOperator myRegExpOp;
#endif
};

#endif // __SkypeChatMainFrame__
