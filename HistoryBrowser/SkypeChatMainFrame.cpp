#include "SkypeChatMainFrame.h"
#include <DatabaseLayerException.h>
#include <wx/filedlg.h>
#include <wx/listimpl.cpp>
#include <wx/stdpaths.h>
#include <wx/filename.h>

SkypeChatMainFrame::SkypeChatMainFrame( wxWindow* parent ) : MainFrame( parent )
{
	m_db = NULL;
	
	wxFileDialog openFileDialog(this, _("Open file"), _(""), _(""),
		_("SQLite DB files (*.db)|*.db|All files (*.*)|*.*"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		exit(0);
		
	m_szDbFile = openFileDialog.GetPath();
	
	m_pConfig = new wxFileConfig(_(""), _(""), _("HistoryBrowser"));
	wxFileConfig::Set(m_pConfig);
	m_pConfig->DeleteAll();
	if ( !m_pConfig->Read(_("ContactsTbl"), &m_szContactsTbl) ) 
	{
		m_szContactsTbl =  _("Contacts");
	}
	if ( !m_pConfig->Read(_("MsgsTbl"), &m_szMsgsTbl) ) 
	{
		m_szMsgsTbl = _("Messages");
	}
	
	if ( !m_pConfig->Read(_("ContactsSql"), &m_szContactsSql) ) 
	{
		m_szContactsSql = _("select id, skypename, displayname from contacts order by displayname");
	}
	if ( !m_pConfig->Read(_("SNameSql"), &m_szSNameSql) ) 
	{
		m_szSNameSql = _("select skypename from contacts where id=%d");
	}
	if ( !m_pConfig->Read(_("MsgsSql"), &m_szMsgsSql) ) 
	{
		m_szMsgsSql = _("select id, author, dialog_partner, timestamp, body_xml from messages where author='%s' or dialog_partner='%s' order by timestamp desc");
	}
	if ( !m_pConfig->Read(_("RemMsgsSql"), &m_szRemMsgSql) ) 
	{
		m_szRemMsgSql = _T("delete from messages where id = %d;\n");
	}
	
	if ( !m_pConfig->Read(_("MsgsListFields"), &m_szMsgsListFields) ) 
	{
		m_szMsgsListFields = _("A:B:C:D:E");
	}

	Init();
	InitContacts();
}

SkypeChatMainFrame::~SkypeChatMainFrame()
{
	if(m_pConfig)
	{
		m_pConfig->Write(_("ContactsTbl"), m_szContactsTbl);
		m_pConfig->Write(_("MsgsTbl"), m_szMsgsTbl);
		
		m_pConfig->Write(_("ContactsSql"), m_szContactsSql);
		m_pConfig->Write(_("SNameSql"), m_szSNameSql);
		m_pConfig->Write(_("MsgsSql"), m_szMsgsSql);
		m_pConfig->Write(_("RemMsgsSql"), m_szRemMsgSql);

		m_pConfig->Write(_("MsgsListFields"), m_szMsgsListFields);

		m_pConfig->Flush();
		delete m_pConfig;
		m_pConfig=NULL;
	}
	wxConfigBase::Set(NULL);
}

void SkypeChatMainFrame::OnRefresh( wxCommandEvent& event )
{
	RefreshMessages();
}

void SkypeChatMainFrame::OnSelectAll( wxCommandEvent& event )
{
	for(long j = 0; j < m_listMsgs->GetItemCount(); ++j)
	{
		m_listMsgs->SetItemState(j, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
	}
}

void SkypeChatMainFrame::OnRemove( wxCommandEvent& event )
{
	wxString query = _T("");
	long nItem = -1;
	m_listMsgs->Freeze();
	int cnt = 0;
	do
	{
		nItem = m_listMsgs->GetNextItem(nItem, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if(wxNOT_FOUND == nItem)
			break;
			
		long id = m_listMsgs->GetItemData(nItem);
		query += wxString::Format(m_szRemMsgSql, id);
		
		if(cnt > 10)
		{
			m_db->ExecuteUpdate(query);
			query = _T("");
		}
			
	}while(1);
	m_listMsgs->Thaw();
	
	m_db->ExecuteUpdate(query);
	RefreshMessages();
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
	itemCol.SetText(_T("Msg ID"));
	itemCol.SetWidth(60);
	m_listMsgs->InsertColumn(0, itemCol);

	itemCol.SetText(_T("From"));
	itemCol.SetWidth(150);
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	m_listMsgs->InsertColumn(1, itemCol);

	itemCol.SetText(_T("To"));
	itemCol.SetWidth(150);
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	m_listMsgs->InsertColumn(2, itemCol);

	itemCol.SetText(_T("Date"));
	itemCol.SetWidth(150);
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	m_listMsgs->InsertColumn(3, itemCol);

	itemCol.SetText(_T("Msg"));
	itemCol.SetWidth(1200);
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	m_listMsgs->InsertColumn(4, itemCol);
	
	if(!Connect())
	{
		wxFAIL_MSG(_("Error connecting to database!"));
	}
}

bool SkypeChatMainFrame::Connect()
{
	bool res = true;
	
	m_db = new SqliteDatabaseLayer();
	
	PreparedStatement * pStatement(NULL);
	try
	{
		m_db->Open(m_szDbFile);
		if(!m_db->TableExists(m_szContactsTbl))
		{
			throw DatabaseLayerException(1, _T("Table 'contacts' does not exist."));
		}
		
		if(!m_db->TableExists(m_szMsgsTbl))
		{
			throw DatabaseLayerException(1, _T("Table 'messages' does not exist."));
		}
		res = true;
	}
	catch(DatabaseLayerException& e)
	{
		m_db->Close();
		m_db = NULL;
		
		wxFAIL_MSG(e.GetErrorMessage());
		res = false;
	}
	catch(...)
	{
		wxFAIL_MSG(_T("Unhandled exception. Exit."));
		res = false;
	}
	return res;
}

void SkypeChatMainFrame::InitContacts()
{
	m_comboContact->Clear();
	DatabaseResultSet* set = m_db->ExecuteQuery(m_szContactsSql);
	
	while (set->Next())
	{
		wxString name = set->GetResultString(_T("displayname"));
		wxString sname = set->GetResultString(_T("skypename"));
		wxString s = wxString::Format(_T("%s (%s)"), name.GetData(), sname.GetData());
		
		m_comboContact->Append(s, new MyClientId(set->GetResultLong(_T("id"))));
	}
	set->Close();
}

void SkypeChatMainFrame::RefreshMessages()
{
	int nIndex = m_comboContact->GetSelection();
	if(wxNOT_FOUND == nIndex)
		return;

	MyClientId* nId = (MyClientId*)m_comboContact->GetClientObject(nIndex);

	m_listMsgs->DeleteAllItems();

	wxString sname;
	wxString query = wxString::Format(m_szSNameSql, nId->GetId());
	DatabaseResultSet* set = m_db->ExecuteQuery(query);

	while (set->Next())
	{
		sname = set->GetResultString(_("skypename"));
	}
	set->Close();

	query = wxString::Format(m_szMsgsSql, sname.GetData(), sname.GetData());

	set = m_db->ExecuteQuery(query);

	while (set->Next())
	{
		long mid = set->GetResultLong(_("id"));
		wxString id = set->GetResultString(_("id"));
		wxString from = set->GetResultString(_("author"));
		wxString to = set->GetResultString(_("dialog_partner"));
		long ticks = set->GetResultLong(_("timestamp"));
		wxString date = wxDateTime((time_t)ticks).Format(_T("%Y-%m-%d %H:%M:%S"));
		wxString msg = set->GetResultString(_("body_xml"));

		long itemIndex = m_listMsgs->InsertItem(m_listMsgs->GetItemCount(), id);
		m_listMsgs->SetItem(itemIndex, 1, from);
		m_listMsgs->SetItem(itemIndex, 2, to);
		m_listMsgs->SetItem(itemIndex, 3, date);
		m_listMsgs->SetItem(itemIndex, 4, msg);
		m_listMsgs->SetItemData(itemIndex, mid);
	}

	set->Close();
}

void SkypeChatMainFrame::OnContactChage(wxCommandEvent& event)
{
	RefreshMessages();
}
