#ifndef __SkypeChatMainFrame__
#define __SkypeChatMainFrame__

/**
@file
Subclass of MainFrame, which is generated by wxFormBuilder.
*/

#include "ClassPrototypes.h"

#include <Databaselayer.h>
#include <SqliteDatabaseLayer.h>
#include <wx/fileconf.h>      // for wxFileConfig

class MyClientId : public wxClientData
{
	int m_id;

public:
	MyClientId(int id):m_id(id)
	{
	}
	
	int GetId()
	{
		return m_id;
	};
};

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
	bool Connect();
	void InitContacts();
	void RefreshMessages();
	
public:
	/** Constructor */
	SkypeChatMainFrame( wxWindow* parent );
	virtual ~SkypeChatMainFrame();
	
private:
	wxString m_szDbFile;

	DatabaseLayer* m_db;
	wxFileConfig* m_pConfig;
	
	wxString m_szContactsTbl;
	wxString m_szMsgsTbl;
	wxString m_szContactsSql;
	wxString m_szSNameSql;
	wxString m_szMsgsSql;
	wxString m_szRemMsgSql;
	wxString m_szMsgsListFields;
	
	
};

#endif // __SkypeChatMainFrame__
