#include<bits/stdc++.h>
using namespace std;

struct Coor
{
    int row,col;
};

char human = 'X' , ai ='O';

char getValue(char a, char v)
{
    if(a==' ')
    {
        return v;
    }
    return a;
}

void drawBoard(char board[3][3])
{
    cout<<"You: X  "<<"Computer: O"<<endl<<endl;
	cout<<"       "<< "     |     |     "<<endl<<"       "<< "  "<<getValue(board[0][0],'0')<<"  "<<"|  "<<getValue(board[0][1],'1')<<"  |"<<"  "<<getValue(board[0][2],'2')<<"  "<<endl<<"       "<<"_____|_____|_____"<<endl<<"       "<<"     |     |     "<<endl;
	cout<<"       "<<"  "<<getValue(board[1][0],'3')<<"  |"<<"  "<<getValue(board[1][1],'4')<<"  |"<<"  "<<getValue(board[1][2],'5')<<"  "<<endl<<"       "<<"_____|_____|_____"<<endl;
	cout<<"       "<<"     |     |     "<<endl<<"       "<<"  "<<getValue(board[2][0],'6')<<"  |"<<"  "<<getValue(board[2][1],'7')<<"  |"<<"  "<<getValue(board[2][2],'8')<<"  "<<endl<<"       "<<"     |     |     "<<endl;
}

bool isAvail(int row,int col, char board[3][3])
{
    if(board[row][col]==' ')
    {
        return true;
    }
    return false;
}

int getCol(int row,int val)
{
    if(row==0)
    {
        return val-0;
    }else if(row==1)
    {
        return val-3;
    }else if(row==2)
    {
        return val-6;
    }
}

int evaluate(char board[3][3])
{
    for(int i=0;i<3;++i)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2])
        {
            if(board[i][0]==human)
            {
                return -1;
            }else if(board[i][0]==ai)
            {
                return 1;
            }
        }
    }

    for(int i=0;i<3;++i)
    {
        if(board[0][i]==board[1][i] && board[1][i] == board[2][i])
        {
            if(board[0][i]==human)
            {
                return -1;
            }else if(board[0][i]==ai)
            {
                return 1;
            }
        }
    }

    if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if(board[0][0]==human)
        {
            return -1;
        }else if(board[0][0]==ai)
        {
            return 1;
        }
    }

    if(board[0][2]==board[1][1] && board[1][1] == board[2][0])
    {
        if(board[0][2]==human)
        {
            return -1;
        }else if(board[0][2]==ai)
        {
            return 1;
        }
    }

    return 0;
}

bool hasMove(char board[3][3])
{
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<3;++j)
        {
            if(board[i][j]==' ')
            {
                return true;
            }
        }
    }
    return false;
}

int minimax(char board[3][3], bool isMaximizer)
{
    int s = evaluate(board);

    if(s==1 || s==-1)
    {
        return s;
    }else if(!hasMove(board))
    {

        return 0;
    }
    if(isMaximizer)
    {
        int bestMove = -10000;
        for(int i=0;i<3;++i)
        {
            for(int j=0;j<3;++j)
            {
                if(board[i][j]==' ')
                {
                    board[i][j]=ai;

                    bestMove = max(bestMove, minimax(board,!isMaximizer));

                    board[i][j]=' ';
                }
            }
        }
        return bestMove;
    }
    else
    {
        int bestMove = 10000;
        for(int i=0;i<3;++i)
        {
            for(int j=0;j<3;++j)
            {
                if(board[i][j]==' ')
                {
                    board[i][j]=human;

                    bestMove = min(bestMove,minimax(board,!isMaximizer));
                    board[i][j]=' ';
                }
            }
        }
        return bestMove;
    }
}

Coor analyzeMove(char board[3][3])
{
    int best = -10000;
    Coor bestMove;
    bestMove.row=-1;
    bestMove.col=-1;

    for(int i=0;i<3;++i)
    {
        for(int j=0;j<3;++j)
        {
            if(board[i][j]==' ')
            {
                board[i][j] = ai;

                int mve = minimax(board, false);

                board[i][j]=' ';

                if(mve>best)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    best = mve;
                }
            }
        }
    }

    return bestMove;
}

int main()
{
    char board[3][3]={
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };
    int mve;

    Coor bestMove;
    while(true)
    {
        drawBoard(board);
        cout<< "Your turn: ";
        cin>>mve;
        system("cls");
        if(mve>8) continue;

        int row = mve/3;
        int col = getCol(row,mve);
        if(!isAvail(row,col,board)) continue;
        board[row][col]=human;

        bestMove = analyzeMove(board);
        board[bestMove.row][bestMove.col] = ai;

        int win = evaluate(board);
        if(win==0 && !hasMove(board))
        {
            drawBoard(board);
            cout<<"Match draw"<<endl;
            break;
        }else if(win==1)
        {
            drawBoard(board);
            cout<<"Computer wins\n"<<"You loose"<<endl;
            break;
        }else if(win==-1)
        {
            drawBoard(board);
            cout<<"You Win"<<endl;
            break;
        }
    }
}

