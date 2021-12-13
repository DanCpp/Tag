//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#pragma hdrstop
using namespace std;

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

UnicodeString field[][4] = {
	{"", "", "", ""},
	{"", "", "", ""},
	{"", "", "", ""},
	{"", "", "", ""}
};
vector<TButton*> buttons;
int choosen[] = {-1, -1};
int rows = 0, cols = 0;


bool CheckWin()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
            if(field[i][j] == " ") continue;
            if(StrToInt(field[i][j]) != (i*4) + j + 1) return false;
        }
	}
    return true;
}

void setvect(vector<int>& vect)
{
	for(int i = 1; i < 16; i++)
	{
        vect.push_back(i);
    }
}


void printfield()
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
            ShowMessage(field[i][j]);
        }
    }
}

void CreateButton(int x, int y, UnicodeString name, UnicodeString caption, int sizex, int sizey)
{
	 TButton* b = new TButton(Form1);
	 b->Parent = Form1;
	 b->Caption = caption;
	 b->Name = name;
	 b->Width = sizex;
	 b->Height = sizey;
	 b->Left = x;
	 b->Top = y;
	 b->OnClick = Form1->Button1Click;
	 field[rows][cols] = caption;
     buttons.push_back(b);
}


int emptyonrow(int row, int col)
{
	int dirx[] = {1, -1};
	for(int i = 0; i < 2; i++)
	{
//		if(col == 0 and i == 1) break;
//		if(col == 3 and i == 0) break;
		if(field[row][col+dirx[i]] == " ")return dirx[i];
	}
    return 0;
}

int emptyoncol(int row, int col)
{
	int diry[] = {1, -1};
	for(int i = 0; i < 2; i++)
	{
//		if(row == 0 and i == 1) break;
//		if(row == 3 and i == 0) break;
		if(field[row+diry[i]][col] == " ") return diry[i];
	}
    return 0;
}

int findrow(int &idx)
{
	int row = 0;
	while(idx >= 4)
	{
		idx-=4;
        row++;
	}
    return row;
}

void swapcaptions(int idx1, int idx2)
{
	UnicodeString cpth = buttons[idx1]->Caption;
	buttons[idx1]->Caption = buttons[idx2]->Caption;
	buttons[idx2]->Caption = cpth;

}

int getidx(int row, int index)
{
	while(row > 0)
	{
		index+=4;
        row--;
	}
    return index;
}

void ButtonClicked(TButton* btn)
{
	if(btn->Caption == " ") return;
	UnicodeString num = btn->Caption;
	int index = StrToInt(btn->Name.SubString(4, 2)) - 1;
	int row = findrow(index);
	int nrow, nindex;
	if(emptyonrow(row, index) != 0) {
		nindex = index + emptyonrow(row, index);
		nrow = row;
	}
	else if(emptyoncol(row, index) != 0)
	{
		nindex = index;
		nrow = row + emptyoncol(row, index);
	}
	else return;
	UnicodeString temp = field[row][index];
	field[row][index] = field[nrow][nindex];
	field[nrow][nindex] = temp;
	swapcaptions(getidx(row, index), getidx(nrow, nindex));
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	randomize();
	vector<int> numbers;
    setvect(numbers);
    int HeadLine = Height - ClientHeight;
	int NWidth = Width / 4;
	int NHeight = (Height - HeadLine) / 4;
	int x = 0, y = 0;
	for(int i = 0; i < 15; i++)
	{
		int rn = rand() % numbers.size();
		if(i%4 == 0 and i != 0)
		{
			x = 0;
			y += NHeight;
			rows+=1;
            cols = 0;
		}
		CreateButton(x, y, "btn" + IntToStr(i + 1), numbers[rn], NWidth, NHeight);
		numbers.erase(numbers.begin() + rn);
		x+=NWidth;
        cols+=1;
	}
    CreateButton(x, y, "btn16", " ", NWidth, NHeight);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	ButtonClicked(((TButton*)Sender));
    if(CheckWin()) ShowMessage("Ура! Победа!");
}
//---------------------------------------------------------------------------
