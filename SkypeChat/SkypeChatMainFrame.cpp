#include "SkypeChatMainFrame.h"

SkypeChatMainFrame::SkypeChatMainFrame( wxWindow* parent ) : MainFrame( parent )
{
	m_db = NULL;
	m_szDbFile = wxT("main.db");
	
	Init();
	Connect();
	InitContacts();
	RefreshMessages();
}

void SkypeChatMainFrame::OnRefresh( wxCommandEvent& event )
{
	// TODO: Implement OnRefresh
}

void SkypeChatMainFrame::OnSelectAll( wxCommandEvent& event )
{
	// TODO: Implement OnSelectAll
}

void SkypeChatMainFrame::OnRemove( wxCommandEvent& event )
{
	// TODO: Implement OnRemove
}

void SkypeChatMainFrame::OnChange( wxCommandEvent& event )
{
	// TODO: Implement OnChange
}

void SkypeChatMainFrame::OnClose( wxCommandEvent& event )
{
	Close();
}

void SkypeChatMainFrame::Init()
{
	m_listMsgs->ClearAll();
	
	wxListItem itemCol;
	itemCol.SetText(_T(" "));
	itemCol.SetWidth(50);
	m_listMsgs->InsertColumn(0, itemCol);

	itemCol.SetText(_T("From"));
	itemCol.SetWidth(150);
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	m_listMsgs->InsertColumn(1, itemCol);

	itemCol.SetText(_T("To"));
	itemCol.SetWidth(150);
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	m_listMsgs->InsertColumn(2, itemCol);

	itemCol.SetText(_T("Msg"));
	itemCol.SetWidth(-1);
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	m_listMsgs->InsertColumn(3, itemCol);
}

void SkypeChatMainFrame::Connect()
{
	cout << "Start..."<<endl;
	wxSQLite3Database* db = new wxSQLite3Database();
	if(NULL == db)
	{
		cout << "Create DB pointer error." << endl;
		return;
	}
	cout << "Open DB file " << endl;
	db->Open(m_szDbFile);
	cout << "Opened" << endl;
	
	m_db = db;
	cout << "Open DB file " << m_szDbFile.GetData() << endl;
	bool foreignKeysEnabled = db->EnableForeignKeySupport(true);
	cout << endl << "Foreign key constraints are ";
	if(foreignKeysEnabled)
		cout << "enabled.";
	else
		cout << "not enforced.";
	cout << endl;

	cout << endl << "contacts table exists=" << (db->TableExists(wxT("contacts")) ? "TRUE":"FALSE") << endl;
	cout << endl << "messages table exists=" << (db->TableExists(wxT("messages")) ? "TRUE":"FALSE") << endl;
}

void SkypeChatMainFrame::InitContacts()
{
	m_comboContact->Clear();
	
	wxSQLite3ResultSet set = m_db->ExecuteQuery(wxT("select id, skypename, displayname from contacts order by displayname"));
	
	while (set.NextRow())
	{
		wxString name = set.GetAsString(2);
		wxString sname = set.GetAsString(1);
		wxString s = wxString::Format(_T("%s (%s)"), name.GetData(), sname.GetData());
		
		m_comboContact->Append(s);
	}
	set.Finalize();
}

void SkypeChatMainFrame::RefreshMessages()
{
}

void SkypeChatMainFrame::OnContactChage(wxCommandEvent& event)
{
	m_listMsgs->DeleteAllItems();
	wxString query = wxString::Format(_T("select id, author, dialog_partner, body_xml from messages where author='%s' or dialog_partner='%s' order by timestamp desc"),
	);
	
	wxSQLite3ResultSet set = m_db->ExecuteQuery(query);
	
	while (set.NextRow())
	{
		wxString name = set.GetAsString(2);
		wxString sname = set.GetAsString(1);
		wxString s = wxString::Format(_T("%s (%s)"), name.GetData(), sname.GetData());
		
		long itemIndex = m_listMsgs->InsertItem(0, _(" "));
		m_listMsgs->SetItem(itemIndex, 1, name);
		m_listMsgs->SetItem(itemIndex, 2, sname);

	}
	set.Finalize();
}
