#include <wx/wx.h>
#include <wx/grid.h>
#include <iostream>
#include <sstream>
#include <bitset>
#include <iomanip>
#include <string>
#include "util.cpp"

using namespace std;
using std::string;



class Simple2 : public wxFrame
{
	wxPanel* painel;

	wxStaticText *titulo;
	wxButton *btnMapDir;
	wxButton *btnMapAss;
	wxButton *btnMapTot;



	public:
		Simple2(const wxString& title)
			: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400,400))
		{	
			painel = new wxPanel(this, wxID_ANY);
			
			void botaoMapDir(wxCommandEvent& event);
			void botaoMapAss(wxCommandEvent& event);
			void botaoMapTot(wxCommandEvent& event);

			titulo = new wxStaticText(painel, wxID_ANY,wxT("Tipo de Mapeamento"),wxPoint(140,150));
			btnMapDir = new wxButton (painel, wxID_EXIT, wxT("Map. Direto"),wxPoint(80,200),wxSize(80,80));
			btnMapDir->Connect(wxEVT_BUTTON,wxCommandEventHandler(Simple::botaoMapDir),NULL,this);

			btnMapAss = new wxButton (painel, wxID_EXIT, wxT("Map. Ass"),wxPoint(160,200),wxSize(80,80));
			btnMapAss->Connect(wxEVT_BUTTON,wxCommandEventHandler(Simple::botaoMapAss),NULL,this);

			btnMapTot = new wxButton (painel, wxID_EXIT, wxT("Map. Tot. Ass"),wxPoint(240,200),wxSize(80,80));
			btnMapTot->Connect(wxEVT_BUTTON,wxCommandEventHandler(Simple::botaoMapTot),NULL,this);
			
			Centre();
			
		}

	public:
		void botaoMapDir(wxCommandEvent& event)
	{
		printf("cliquei no Map Direto\n");
	} 

	public:
		void botaoMapAss(wxCommandEvent& event)
	{  
		
		cout << " cliquei no Map Ass" << endl;
    }

    public:
		void botaoMapTot(wxCommandEvent& event)
	{ 
		cout << "cliquei no Map  Tot" << endl;
    }

};


class MyApp : public wxApp
{
	public:
		bool OnInit()
		{
			Simple2 *simple = new Simple(wxT("Simulador Memória Cache"));
			simple->Show(true);
			return true;
		}
};

wxIMPLEMENT_APP(MyApp);