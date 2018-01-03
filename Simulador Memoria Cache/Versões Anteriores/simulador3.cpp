#include <wx/wx.h>
#include <wx/grid.h>
#include <iostream>
#include <sstream>
#include <bitset>
#include <iomanip>
#include <string>

using namespace std;
using std::string;


class Simple : public wxFrame
{
	wxPanel* painel;

	wxStaticText *titulo;
	wxButton *btn1;
	wxButton *btn2;
	wxButton *btn3;



	public:
		Simple(const wxString& title)
			: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400,400))
		{	
			painel = new wxPanel(this, wxID_ANY);
			

			void botao1(wxCommandEvent& event);
			void botao2(wxCommandEvent& event);
			void botao3(wxCommandEvent& event);	

			titulo = new wxStaticText(painel, wxID_ANY,wxT("Escolha o botao"),wxPoint(140,150));
			
			btn1 = new wxButton (painel, wxID_EXIT, wxT("1"),wxPoint(80,200),wxSize(80,80));
			btn1->Connect(wxEVT_BUTTON,wxCommandEventHandler(Simple::botao1),NULL,this);
			
			btn2 = new wxButton (painel, wxID_EXIT, wxT("2"),wxPoint(160,200),wxSize(80,80));
			btn2->Connect(wxEVT_BUTTON,wxCommandEventHandler(Simple::botao2),NULL,this);

			btn3 = new wxButton (painel, wxID_EXIT, wxT("3"),wxPoint(240,200),wxSize(80,80));
			btn3->Connect(wxEVT_BUTTON,wxCommandEventHandler(Simple::botao3),NULL,this);


			Centre();

		}

	public:
		void botao1(wxCommandEvent& event)
	{
		cout << "cliquei no botao1"<< endl;

	} 

	public:
		void botao2(wxCommandEvent& event)
	{  
		
		cout << " cliquei no botao2" << endl;
    }

    public:
		void botao3(wxCommandEvent& event)
	{ 
		cout << "cliquei no botao3" << endl;
    }

};

class MyApp : public wxApp
{
	public:
		bool OnInit()
		{
			Simple *simple = new Simple(wxT("sim"));
			simple->Show(true);
			return true;
		}
};

wxIMPLEMENT_APP(MyApp);