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
		int nVias;
	/*
		calculo da tag
		add coisas na tabela	
	*/

	//configura a parametros da cache
	public:
		void configurar(int tipoMap,int numBlocos,int tamBloco,int nVias)
		{	
			this->tipoMap = tipoMap;
			this->numBlocos = numBlocos;
			this->tamBloco = tamBloco;
			this->tamCache = tamBloco * numBlocos * nVias;
			this->nMiss = 0;
			this->nHit = 0;
			this->nVias = nVias;

			printf("%d\n",this->tipoMap);
        	printf("%d\n",this->numBlocos);
        	printf("%d\n",this->tamBloco);
        	printf("%d\n",this->tamCache);
        	printf("%d\n",this->nVias);

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
	wxStaticText *vias;

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
	wxArrayString stringsLabelVias;
	wxComboBox *cbox;
	wxComboBox *cboxVias;

	MemoriaCache memoria;


	public:
		Simple(const wxString& title)
			: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000,600))
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
			//grade = new wxGrid(painel,-1, wxPoint(10,200), wxSize(800,360),0);
			//grade->SetRowSize( 0, 20);
			//grade->SetColSize( 0, 20);

			strings.Add(wxT("Direto"));
			strings.Add(wxT("Tot. Associativo"));
			strings.Add(wxT("Assoc. Conj"));

			stringsLabelVias.Add(wxT("2"));
			stringsLabelVias.Add(wxT("4"));
		
			cbox = new wxComboBox(painel,-1,wxT(""),wxPoint(120,20),wxSize(130,25),strings);
			cboxVias = new wxComboBox(painel,-1,wxT(""),wxPoint(400,20),wxSize(130,25),stringsLabelVias);

			tipoMap = new wxStaticText(painel, wxID_ANY,wxT("Tipo Mapeamento :"),wxPoint(10,20));
			vias = new wxStaticText(painel, wxID_ANY, wxT("N° Vias :"),wxPoint(340,20));
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

			miss = new wxStaticText(painel, wxID_ANY, wxT("Hit :"),wxPoint(850,50));
			hit = new wxStaticText(painel, wxID_ANY, wxT("Miss :"),wxPoint(850,80));
			cxTextHit = new wxTextCtrl(painel, wxID_ANY,wxString(""),wxPoint(890,50),wxSize(40,20));
			cxTextMiss = new wxTextCtrl(painel, wxID_ANY,wxString(""),wxPoint(890,80),wxSize(40,20));

			infoTela = new wxStaticText(painel, wxID_ANY, wxT("Endereço de memória de 32 bits"),wxPoint(700,10));

			/*
			grade->CreateGrid(0,7);
			grade->SetColLabelValue(0,  wxString::FromUTF8("V"));
			grade->SetColLabelValue(1,  wxString::FromUTF8("TAG"));
			grade->SetColLabelValue(2,  wxString::FromUTF8("Índice"));
			grade->SetColLabelValue(3,  wxString::FromUTF8("Offset"));
			grade->SetColLabelValue(4,  wxString::FromUTF8("N° bloco"));
			grade->SetColLabelValue(5,  wxString::FromUTF8("Conteúdo"));
			grade->SetColLabelValue(6,  wxString::FromUTF8("N° acessos"));
			grade->SetColSize(0,30);
			grade->SetColSize(1,250);
			grade->SetColSize(2,100);
			grade->SetColSize(3,100);
			grade->SetColSize(4,60);
			grade->SetColSize(5,90);
			grade->SetColSize(6,70);
			*/
		}

	public:
		void AlterarTabela(int numEnderecos)
		{
		
		}

	public:
		void botaoConfigurar(wxCommandEvent& event)
	{
		
   		if(cbox->GetValue() == wxT("Direto") && (cxTextNB->GetValue().IsEmpty()||cxTextTBB->GetValue().IsEmpty()))
		{
			wxMessageBox(wxT("Preencha tamanho blocos e n° blocos"));
	
		}else if(cbox->GetValue() == wxT("Assoc. Conj") && (cxTextNB->GetValue().IsEmpty()||cxTextTBB->GetValue().IsEmpty()|| cboxVias->GetValue().IsEmpty()))
		{
			wxMessageBox(wxT("Preencha tamanho blocos,n° blocos e n° vias"));

		}
		else if(cbox->GetValue() == wxT("Tot. Associativo") && cxTextTBB->GetValue().IsEmpty())
		{
			
				wxMessageBox(wxT("Preencha tamanho blocos"));
		}else
		{
			if(memoria.configurada)
			{
				wxMessageBox(wxT("Você precisa zerar a configuracao da memória!"));
			}
			else
	    	{
	    		
	    		memoria.configurada = true;
	    		int tm;
				int nb;
				int tb;
				int tc;
				
				string tag;
				string indice;
				string offset;

				

	    		if (cbox->GetValue() == wxT("Direto"))
		    	{

		    		// criando grade e configurando
		    		grade = new wxGrid(painel,-1, wxPoint(10,200), wxSize(800,360),0);

					grade->CreateGrid(0,7);
					grade->SetColLabelValue(0,  wxString::FromUTF8("V"));
					grade->SetColLabelValue(1,  wxString::FromUTF8("TAG"));
					grade->SetColLabelValue(2,  wxString::FromUTF8("Índice"));
					grade->SetColLabelValue(3,  wxString::FromUTF8("Offset"));
					grade->SetColLabelValue(4,  wxString::FromUTF8("N° bloco"));
					grade->SetColLabelValue(5,  wxString::FromUTF8("Conteúdo"));
					grade->SetColLabelValue(6,  wxString::FromUTF8("N° acessos"));
					grade->SetColSize(0,30);
					grade->SetColSize(1,250);
					grade->SetColSize(2,100);
					grade->SetColSize(3,100);
					grade->SetColSize(4,60);
					grade->SetColSize(5,90);
					grade->SetColSize(6,70);

		    		tm = 0;

			    	nb = wxAtoi(cxTextNB->GetValue());
			    	tb = wxAtoi(cxTextTBB->GetValue());

			    	// configura parametros da memoria cache
			    	memoria.configurar(tm,nb,tb,1); 

			    	// altera numero de linhas da TABELA de acordo com o tamanho da cache
			    	grade->InsertRows(0,memoria.tamCache,true);

			    	//metodo que preenche a tabela como os enderecos de memoria
			    	//seta conteudo de cada endereco como vazio

		 			for (int i = 0; i < memoria.tamCache; i++)
		 			{
		 				string s;
				   	
		 				//stringstream sEnd;
		 				//sEnd << i << endl;
		 				//string convEnd = sEnd.str();

		 				// campo de validade por padrao recebe 0
		 				grade->SetCellValue(i,0,wxString("0"));
		 				grade->SetCellValue(i,6,wxString("0"));

		 				//convertendo linha para binario
		 				string convEnd = binario(i);

		 				tag = bitsTag(convEnd,nb,tb);
		 				indice = bitsIndice(convEnd,nb,tb);
		 				offset = bitsOffset(convEnd,tb);

		 				grade->SetCellValue(i,1,wxString(tag));
		 				grade->SetCellValue(i,2,wxString(indice));
		 				grade->SetCellValue(i,3,wxString(offset));

		 				// calculo do bloco

		 				int bloco = (i/memoria.tamBloco) % memoria.numBlocos;

		 				string conv = intParaString(bloco);

		 				grade->SetCellValue(i,4,wxString(conv));

		 			}
		 			
		    	}
		    	else if(cbox->GetValue() == wxT("Tot. Associativo"))
		    	{

		    		tm = 1;

			    	tb = wxAtoi(cxTextTBB->GetValue());

			    	// configura parametros da memoria cache
			    	//memoria.configurar(tm,1,tb); 

			    	// altera numero de linhas da tabela de acordo com o tamanho da cache
			    	grade->InsertRows(0,memoria.tamCache,true);

			    	cout << "tam cache" << memoria.tamCache << endl;

			    	//cxTextNB->SetValue("1");

		    	}else if(cbox->GetValue() == wxT("Assoc. Conj"))
		    	{
		    		tm = 2;
		    		/*
		    		int numVias = wxAtoi(cboxVias->GetValue());

		    		// numero de colunas fixo eh 7, add + 2 para vias
		    		grade = new wxGrid(painel,-1, wxPoint(10,200), wxSize(800,360),0);
		    		grade->CreateGrid(0,6+numVias);
		    		
					grade->SetColLabelValue(0,  wxString::FromUTF8("V"));
					grade->SetColLabelValue(1,  wxString::FromUTF8("TAG"));
					grade->SetColLabelValue(2,  wxString::FromUTF8("Índice"));
					grade->SetColLabelValue(3,  wxString::FromUTF8("Offset"));
					grade->SetColLabelValue(4,  wxString::FromUTF8("N° bloco"));
					grade->SetColLabelValue(5,  wxString::FromUTF8("N° acessos"));

					grade->SetColSize(0,30);
					grade->SetColSize(1,250);
					grade->SetColSize(2,100);
					grade->SetColSize(3,100);
					grade->SetColSize(4,60);
					grade->SetColSize(5,90);
					
					int c = 0;

					for (int i = 6; i < 6 + numVias; i++)
					{
						grade->SetColSize(i,40);
						grade->SetColLabelValue(i,wxString::FromUTF8("Via"));
						
					}

					nb = wxAtoi(cxTextNB->GetValue());
			    	tb = wxAtoi(cxTextTBB->GetValue());

			    	// configura parametros da memoria cache
			    	memoria.configurar(tm,nb,tb,numVias); 

			    	// altera numero de linhas da TABELA de acordo com o tamanho da cache
			    	grade->InsertRows(0,memoria.tamCache,true);

			    	cout << "tam cache" << memoria.tamCache << endl;

					//metodo que preenche a tabela como os enderecos de memoria
			    	//seta conteudo de cada endereco como vazio

			    	
		 			for (int i = 0; i < memoria.tamCache; i++)
		 			{
		 				string s;
				   	
		 				//stringstream sEnd;
		 				//sEnd << i << endl;
		 				//string convEnd = sEnd.str();

		 				// campo de validade por padrao recebe 0
		 				grade->SetCellValue(i,0,wxString("0"));
		 				grade->SetCellValue(i,6,wxString("0"));

		 				//convertendo linha para binario
		 				string convEnd = binario(i);

		 				tag = bitsTag(convEnd,nb,tb);
		 				indice = bitsIndice(convEnd,nb,tb);
		 				offset = bitsOffset(convEnd,tb);

		 				grade->SetCellValue(i,1,wxString(tag));
		 				grade->SetCellValue(i,2,wxString(indice));
		 				grade->SetCellValue(i,3,wxString(offset));

		 				// calculo do bloco

		 				int bloco = (i/memoria.tamBloco) % memoria.numBlocos;

		 				string conv = intParaString(bloco);

		 				grade->SetCellValue(i,4,wxString(conv));
		    		}
		    		*/

		    	cxTextHit->SetValue("0");
		    	cxTextMiss->SetValue("0");
		    
	    	} 
		}
		
		
    }
		

	public:
		void botaoBuscar(wxCommandEvent& event)
	{  
		
		if(cxTextNB->GetValue().IsEmpty()||cxTextTBB->GetValue().IsEmpty()||cbox->GetValue().IsEmpty()||cxTextE->GetValue().IsEmpty())
		{
			wxMessageBox(wxT("Os campos nao estao preenchidos"));
	
		}
		if(memoria.configurada == false)
		{
			wxMessageBox(wxT("Memória não esta configurada!"));
		}
		else
		{

			int enderecoInt = wxAtoi(cxTextE->GetValue()); 
			string informacao = string(cxTextInfo->GetValue());

			memoria.buscar(enderecoInt,informacao);

			bool entrei = false;
			
			// mapeamento direto
			if(memoria.tipoMap == 0)
			{
				//int bloco = (endereco/memoria.tamBloco) % memoria.numBlocos;

	 			//convertendo endereco para binario
	 			string convEnd = binario(enderecoInt);

	 			string tag = bitsTag(convEnd,memoria.numBlocos,memoria.tamBloco);
	 			
	 			string indice = bitsIndice(convEnd,memoria.numBlocos,memoria.tamBloco);

	 			string offset = bitsOffset(convEnd,memoria.tamBloco);

	 			int bloco = (enderecoInt/memoria.tamBloco) % memoria.numBlocos;


				for (int i = 0; i < memoria.tamCache; i++)
				{	

					// se tags forem iguais e bit de validade igual a 1, cache hit
					if((grade->GetCellValue(i,1) == wxString(tag)) && (grade->GetCellValue(i,0) == "1") && (grade->GetCellValue(i,5) == wxString(informacao)))
					{
						
			
						memoria.nHit++;
						entrei = true;
						cxTextHit->SetValue(intParaString(memoria.nHit));
						break;
					}
				}


				if (!entrei)
				{
					
					for (int i = 0; i < memoria.tamCache; i++)
					{	
						// se tags forem iguais e bit de validade igual a 0, cache miss
						if((grade->GetCellValue(i,1) == tag) && (grade->GetCellValue(i,0) == "0") || (grade->GetCellValue(i,1) == tag) && (grade->GetCellValue(i,0) == "1") && (grade->GetCellValue(i,5) != informacao))
						{
							

							if((i/memoria.tamBloco) % memoria.numBlocos == bloco)
							{
								grade->SetCellValue(i,5,wxString(informacao));
								grade->SetCellValue(i,0,"1");
								//cout << "he" << endl;

								int nAcessos = wxAtoi(grade->GetCellValue(i,6));
								nAcessos++;
								grade->SetCellValue(i,6,intParaString(nAcessos));
							}				
						}
					}


					memoria.nMiss++;		
	    			cxTextMiss->SetValue(intParaString(memoria.nMiss));
				}

			}else if(memoria.tipoMap == 1)
			{
				cout << "Associativo por con" << endl;

				

			}		
		}

		cxTextInfo->SetValue("");

    }

    public:
		void botaoZerar(wxCommandEvent& event)
	{ 
		
		cxTextNB->SetValue("");
		cxTextTBB->SetValue("");
		cxTextE->SetValue("");
		memoria.configurada = false;
		memoria.nHit = 0;
		memoria.nMiss = 0;

		// remove todas as linhas da tabela
		//grade->DeleteRows(0,memoria.tamCache,true);

		// pega numero de linhas e numero de colunas da tabela
		int nColunas = grade->GetNumberCols();
		int nLinhas = grade->GetNumberRows();
		cout << "linhas" << nLinhas << endl;
		cout << "colunas" << nColunas << endl;
		// Deleta todas as linhas e colunas da tabela
		grade->DeleteCols(0,nColunas,true);
		grade->DeleteRows(0,nLinhas,true);

		//grade->ClearGrid();
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