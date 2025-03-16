#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <ncurses.h>

void printmap(std::vector<std::vector<int>> map, int N){
    
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (map[i][j] == 0) {
        mvprintw(i, j * 2, "- ");  // Умножаем j на 2 для пробела
      } else if (map[i][j] == 1) {
	attron(COLOR_PAIR(1));
        mvprintw(i, j * 2, "@ ");  // Умножаем j на 2 для пробела
	attroff(COLOR_PAIR(1));      
	} else if (map[i][j] == 2 || map[i][j] == 4) {
        attron(COLOR_PAIR(2));
        mvprintw(i, j * 2, "* ");  // Умножаем j на 2 для пробела
        attroff(COLOR_PAIR(2));
      } else if (map[i][j] == 3) {
        mvprintw(i, j * 2, "# ");  // Умножаем j на 2 для пробела
      }
    }
  }
getch();
  refresh();  // Обновляем экран
}
std::vector<std::vector<int>> makemap(int N, int a, int b){
    std::vector<std::vector<int>> map11;
    
    srand(time(0));
    int start = 0;
    int end = N-1;
    for(int i = 0; i<N; i++){
        std::vector<int> map1;
        for(int j = 0; j<N; j++){
            map1.push_back(0); //rand() % (end - start + 1) + start);
        }
        map11.push_back(map1);
    }
    int i = 0;
  while(i<a){
        int x = rand() % (end - start + 1) + start;
        int y = rand() % (end - start + 1) + start;
        if(map11[x][y] != 1){
            map11[x][y] = 1;
            i++;
        }    
    
    }
    i = 0;
   while(i<b){
        int x = rand() % (end - start + 1) + start;
        int y = rand() % (end - start + 1) + start;
        if(map11[x][y] != 1){
            map11[x][y] = 2;
            i++;
        }    
    
    } /*
    map11[0][2] = 1;
    map11[N-1][2] = 2;
    map11[2][2] = 3;
    map11[2][1] = 3;
    map11[2][3] = 3;
    //map11[1][1] = 3;
    //map11[1][3] = 3;*/
    return map11;
}


std::vector<std::vector<int>> muv2(std::vector<std::vector<int>> map, int N){
    std::vector<std::vector<int>> map11 = map;
    
    srand(time(0));
    int I = N+1;
    int J = N+1;
    
    for(int i1 = 0; i1<N; i1++){
        for(int j1 = 0; j1<N; j1++){
            if(map[i1][j1]==2){
                map11[i1][j1]=4;
                for(int i = 0; i<N; i++){
                    for(int j = 0; j<N; j++){
                        if(map[i][j]==1 and (abs(i-i1)+abs(j-j1))<=(abs(I-i1)+abs(J-j1))){
                            J=j;
                            I=i;
                        }
                    }
                }
                
                for(int i = 0; i<N; i++){
                    for(int j = 0; j<N; j++){
                        if(map[i][j]==1 and J==j){
                            if(abs(i-i1)>=abs(j-j1) and i1<i and map11[i1+1][j1]!=3 and map11[i1+1][j1]!=4){
                                map11[i1+1][j1]=2;
                        }
                        else if(abs(i-i1)>=abs(j-j1) and i1>i and map11[i1-1][j1]!=3 and map11[i1-1][j1]!=4){
                                map11[i1-1][j1]=2;
                        }
                        else if(abs(i-i1)<=abs(j-j1) and j1>j and map11[i1][j1-1]!=3 and map11[i1][j1-1]!=4){
                            map11[i1][j1-1]=2;
                        }
                        else if((i-i1)<=abs(j-j1) and j1<j and map11[i1][j1+1]!=3 and map11[i1][j1+1]!=4){
                            map11[i1][j1+1]=2;
                        }
                        else if( map11[i1][j1+1]==3 and map11[i1+1][j1]!=3 ){
                            map11[i1+1][j1]=2;
                        }
                        else if( map11[i1][j1-1]==3  and map11[i1+1][j1]!=3){
                            map11[i1+1][j1]=2;
                        }
                        else if( map11[i1+1][j1]==3 and map11[i1][j1+1]!=3){
                            map11[i1][j1+1]=2;
                        }
                        else if( map11[i1-1][j1]==3 and map11[i1][j1+1]!=3){
                            map11[i1][j1+1]=2;
                        }
                        } 
                    }
                }    
 
             printmap(map11, N);
                
            }
        }
    }
    return map11;
}


int main()
{
    int N=10;	
    std::vector<std::vector<int>> map;
    map=makemap(N, 3, 3);
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    init_pair(3, COLOR_BLUE, COLOR_BLACK);

    printmap(map, N);
    for(int i = 0; i<10; i++){
   
    map = muv2(map, N);
    
    }
//refresh();
   endwin(); 
    return 0;
}
