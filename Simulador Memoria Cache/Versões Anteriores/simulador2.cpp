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


class MemoriaCache
{
	public:
		int tipoMap;
		int numBlocos;
		int tamBloco;
		int tamCache;
		int end;
		int nHit;
		int nMiss;
		bool configurada;
	/*
		calculo da tag
		add coisas na tabela	
	*/

	//configura a parametros da cache
	public:
		void configurar(int tipoMap,int numBlocos,int tamBloco)
		{	
			this->tipoMap = tipoMap;
			this->numBlocos = numBlocos;
			this->tamBloco = tamBloco;
			this->tamCache = tamBloco * numBlocos;
			this->nMiss = 0;
			this->nHit = 0;

			printf("%d\n",this->tipoMap);
        	printf("%d\n",this->numBlocos);
        	printf("%d\n",this->tamBloco);
        	printf("%d\n",this->tamCache);

		}

	// faz busca em um endereço
	public:
		void buscar(int end, string informacao)
		{
			this->end = end;
			cout << informacao << endl;
			printf("%d\n",this->end);


		}


};

class Simple : public wxFrame
{
	wxPanel* painel;
	wxGrid *grade;
	
	wxStaticText *tipoMap;
	wxStaticText *endBusca;
	wxStaticText *numBlocos;
	wxStaticText *tamByteBloco;
	wxStaticText *hit;
	wxStaticText *miss;
	wxStaticText *info;
	wxStaticText *infoTela;

	wxTextCtrl *cxTextE;
	wxTextCtrl *cxTextNB;
	wxTextCtrl *cxTextTBB;
	wxTextCtrl *cxTextMiss;
	wxTextCtrl *cxTextHit;
	wxTextCtrl *cxTextInfo;

	wxButton *btnConfigurar;
	wxButton *btnBuscar;
	wxButton *btnZerar;
	
	wxArrayString strings;
	wxComboBox *cbox;

	MemoriaCache memoria;


	public:
		Simple(const wxString& title)
			: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800,600))
		{	

			void botaoConfigurar(wxCommandEvent& event);
			void botaoBuscar(wxCommandEvent& event);
			void botaoZerar(wxCommandEvent& event);

    		//void OnAbout(wxCommandEvent& event);
    		//void OnConnect(wxCommandEvent& event);
			Centre();
		}

	public:
		void CriarTela(int numEnderecos)
		{
			painel = new wxPanel(this, wxID_ANY);
			grade = new wxGrid(painel,-1, wxPoint(10,200), wxSize(600,360),0);
			//grade->SetRowSize( 0, 20);
			//grade->SetColSize( 0, 20);

			strings.Add(wxT("Direto"));
			strings.Add(wxT("Tot. Associativo"));
			strings.Add(wxT("Associativo"));

			cbox = new wxComboBox(painel,-1,wxT(""),wxPoint(120,20),wxSize(130,25),strings);

			tipoMap = new wxStaticText(painel, wxID_ANY,wxT("Tipo Mapeamento :"),wxPoint(10,20));
			tamByteBloco = new wxStaticText(painel, wxID_ANY,wxT("Tam. Bytes/Bloco :"),wxPoint(10,60));
			numBlocos = new wxStaticText(painel, wxID_ANY, wxT("N° Blocos :"),wxPoint(10,100));

			cxTextTBB = new wxTextCtrl(painel, wxID_ANY,wxString(""),wxPoint(120,60),wxSize(100,30));
			cxTextNB = new wxTextCtrl(painel, wxID_ANY,wxString(""),wxPoint(120,100),wxSize(100,30));
			
			btnConfigurar = new wxButton (painel, wxID_EXIT, wxT("Configurar"),wxPoint(230,60),wxSize(100,30));

			btnConfigurar->Connect(wxEVT_BUTTON,wxCommandEventHandler(Simple::botaoConfigurar),NULL,this);
			
			btnZerar = new wxButton (painel, wxID_ANY, wxT("Zerar"),wxPoint(340,60),wxSize(100,30));
			btnZerar->Connect(wxEVT_BUTTON,wxCommandEventHandler(Simple::botaoZerar),NULL,this);

			
			endBusca = new wxStaticText(painel, wxID_ANY, wxT("Endereço:"),wxPoint(10,150));
			cxTextE = new wxTextCtrl(painel, wxID_ANY,wxString(""),wxPoint(70,150),wxSize(100,30));

			info = new wxStaticText(painel, wxID_ANY, wxT("Informação :"),wxPoint(180,150));
			cxTextInfo = new wxTextCtrl(painel, wxID_ANY,wxString(""),wxPoint(260,150),wxSize(130,30));

			btnBuscar = new wxButton (painel, wxID_ANY, wxT("Buscar"),wxPoint(400,150),wxSize(100,30));
			btnBuscar->Connect(wxEVT_BUTTON,wxCommandEventHandler(Simple::botaoBuscar),NULL,this);

			miss = new wxStaticText(painel, wxID_ANY, wxT("Hit :"),wxPoint(650,250));
			hit = new wxStaticText(painel, wxID_ANY, wxT("Miss :"),wxPoint(650,280));
			cxTextHit = new wxTextCtrl(painel, wxID_ANY,wxString(""),wxPoint(690,250),wxSize(40,20));
			cxTextMiss = new wxTextCtrl(painel, wxID_ANY,wxString(""),wxPoint(690,280),wxSize(40,20));

			infoTela = new wxStaticText(painel, wxID_ANY, wxT("Endereço de memória de 32 bits"),wxPoint(600,10));

			grade->CreateGrid(0,4);
			grade->SetColLabelValue(0,  wxString::FromUTF8("Endereço"));
			grade->SetColLabelValue(1,  wxString::FromUTF8("N° bloco"));
			grade->SetColLabelValue(2,  wxString::FromUTF8("Conteúdo"));
			grade->SetColLabelValue(3,  wxString::FromUTF8("N° acessos"));
			grade->SetColSize(0,250);
			grade->SetColSize(1,70);
			grade->SetColSize(2,100);
			grade->SetColSize(3,80);

		}

	public:
		void AlterarTabela(int numEnderecos)
		{
		
		}

	public:
		void botaoConfigurar(wxCommandEvent& event)
	{
		
   		if(cxTextNB->GetValue().IsEmpty()||cxTextTBB->GetValue().IsEmpty()||cbox->GetValue().IsEmpty())
		{
			wxMessageBox("Os campos nao estao preenchidos!");
	
		}else if(memoria.configurada)
		{
			wxMessageBox("Você precisa zerar a configuracao da memória!");
		}
		else
    	{
    		memoria.configurada = true;
    		int tm;
			int nb;
			int tb;
			int tc;
	

    		if (cbox->GetValue() == wxT("Direto"))
	    	{
	    		tm = 0;

		    	nb = wxAtoi(cxTextNB->GetValue());
		    	tb = wxAtoi(cxTextTBB->GetValue());
		   
		    	printf("Cliquei no botao configurar\n");

		    	// configura parametros da memoria cache
		    	memoria.configurar(tm,nb,tb); 

		    	// altera numero de linhas da tabela de acordo com o tamanho da cache
		    	grade->InsertRows(0,memoria.tamCache,true);

		    	//metodo que preenche a tabela como os enderecos de memoria
		    	//seta conteudo de cada endereco como vazio

		    	//SetCellValue (int row, int col, const wxString &s)
	 			//Sets the string value for the cell at the specified location. More...

	 			for (int i = 0; i < memoria.tamCache; i++)
	 			{
	 				string s;
			   	
	 				//stringstream sEnd;
	 				//sEnd << i << endl;
	 				//string convEnd = sEnd.str();

	 				string convEnd = binario(i);

	 				grade->SetCellValue(i,0,wxString(convEnd));
	 				grade->SetCellValue(i,3,wxString("0"));

	 				// calculo do bloco

	 				int bloco = (i/memoria.tamBloco) % memoria.numBlocos;

	 				string conv = intParaString(bloco);

	 				grade->SetCellValue(i,1,wxString(conv));

	 			}
	 			printf("Cliquei no botao configurar2\n");

	    	}
	    	else if(cbox->GetValue() == wxT("Tot. Associativo"))
	    	{
	    		tm = 1;

	    	}else
	    	{
	    		tm = 2;
	    	}

	    	cxTextHit->SetValue("0");
	    	cxTextMiss->SetValue("0");
    	} 

	}

	public:
		void botaoBuscar(wxCommandEvent& event)
	{ 
		printf("Cliquei no botao buscar\n");

		if(cxTextNB->GetValue().IsEmpty()||cxTextTBB->GetValue().IsEmpty()||cbox->GetValue().IsEmpty()||cxTextE->GetValue().IsEmpty())
		{
			wxMessageBox("Os campos nao estao preenchidos");
	
		}
		if(memoria.configurada == false)
		{
			wxMessageBox("Memória não esta configurada!");
		}
		else
		{
			int endereco = wxAtoi(cxTextE->GetValue()); 
			string informacao = string(cxTextInfo->GetValue());

			memoria.buscar(endereco,informacao);
			
			// mapeamento direto
			if(memoria.tipoMap == 0)
			{
				int bloco = (endereco/memoria.tamBloco) % memoria.numBlocos;

	 			string conv = intParaString(bloco);

	 			int linhaBusca;

				for (int i = 0; i < memoria.tamCache; i++)
				{
					if(grade->GetCellValue(i,1) == conv)
					{
						linhaBusca = i;
						break;
					}
				}

				if(grade->GetCellValue(linhaBusca,2) == "")
				{
					cout<<"deu cache miss"<<endl;
					memoria.nMiss = memoria.nMiss + 1;

					for (int i = 0; i < memoria.tamCache;i++)
					{
						if((i/memoria.tamBloco) % memoria.numBlocos == bloco)
						{
							grade->SetCellValue(i,2,wxString(informacao));
						}
					}

				}else
				{

					if(grade->GetCellValue(linhaBusca,2) == informacao)
					{
						memoria.nHit = memoria.nHit + 1;
						cout<<"deu cache hit"<<endl;

					}else
					{
						cout<<"deu cache miss"<<endl;
						for (int i = 0; i < memoria.tamCache;i++)
						{
							if((i/memoria.tamBloco) % memoria.numBlocos == bloco)
							{
								grade->SetCellValue(i,2,informacao);
							}
						}

						memoria.nMiss = memoria.nMiss + 1;
					}
				}

				cxTextHit->SetValue(intParaString(memoria.nHit));
	    		cxTextMiss->SetValue(intParaString(memoria.nMiss));
					
			}
				

		}
    }

    public:
		void botaoZerar(wxCommandEvent& event)
	{ 
		printf("Cliquei no botao zerar\n");
		

		cxTextNB->SetValue("");
		cxTextTBB->SetValue("");
		cxTextE->SetValue("");
		memoria.configurada = false;
		memoria.nHit = 0;
		memoria.nMiss = 0;

		// remove todas as linhas da tabela
		grade->DeleteRows(0,memoria.tamCache,true);

		
    }

};


class MyApp : public wxApp
{
	public:
		bool OnInit()
		{
			Simple *simple = new Simple(wxT("Simulador Memória Cache"));
			simple->CriarTela(40);
			simple->Show(true);
			return true;
		}
};

wxIMPLEMENT_APP(MyApp);