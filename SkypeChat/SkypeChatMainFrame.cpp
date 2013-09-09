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
	wxString query = _T("");
	long nItem = 0;
	do
	{
		long nItem = m_listMsgs->GetNextItem(nItem, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if(wxNOT_FOUND == nItem)
			break;
			
		long id = m_listMsgs->GetItemData(nItem);
		query += wxString::Format(_T("delete from messages where id = %d;"), id);
		
		cout << "Remove ID:" << id << endl;
	}while(1);
	
	//m_db->ExecuteUpdate(query);
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
	itemCol.SetWidth(1200);
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
	wxSQLite3ResultSet set = m_db->ExecuteQuery(_T("select id, skypename, displayname from contacts order by displayname"));
	
	while (set.NextRow())
	{
		wxString name = set.GetAsString(2);
		wxString sname = set.GetAsString(1);
		wxString s = wxString::Format(_T("%s (%s)"), name.GetData(), sname.GetData());
		
		m_comboContact->Append(s, new MyClientId(set.GetInt(_T("id"))));
	}
	set.Finalize();
}

void SkypeChatMainFrame::RefreshMessages()
{
}

void SkypeChatMainFrame::OnContactChage(wxCommandEvent& event)
{
	int nIndex = m_comboContact->GetSelection();
	if(wxNOT_FOUND == nIndex)
		return;
		
	MyClientId* nId = (MyClientId*)m_comboContact->GetClientObject(nIndex);
	
	m_listMsgs->DeleteAllItems();
	
	wxString sname;
	wxString query = wxString::Format(_T("select skypename from contacts where id=%d"), nId->GetId());
	wxSQLite3ResultSet set = m_db->ExecuteQuery(query);
	
	while (set.NextRow())
	{
		sname = set.GetAsString(0);
	}
	set.Finalize();
	
	query = wxString::Format(_T("select id, author, dialog_partner, body_xml from messages where author='%s' or dialog_partner='%s' order by timestamp desc"),
	sname.GetData(), sname.GetData());
	
	set = m_db->ExecuteQuery(query);
	
	while (set.NextRow())
	{
		long mid = set.GetInt(0);
		wxString id = set.GetAsString(0);
		wxString from = set.GetAsString(1);
		wxString to = set.GetAsString(2);
		wxString msg = set.GetAsString(3);
		
		long itemIndex = m_listMsgs->InsertItem(m_listMsgs->GetItemCount(), id);
		m_listMsgs->SetItem(itemIndex, 1, from);
		m_listMsgs->SetItem(itemIndex, 2, to);
		m_listMsgs->SetItem(itemIndex, 3, msg);
		m_listMsgs->SetItemData(itemIndex, mid);
	}
	
	set.Finalize();
}
