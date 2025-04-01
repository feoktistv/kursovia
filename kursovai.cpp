#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

void printmap(std::vector<std::vector<int>> map, int N){
    
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (map[i][j] == 0) {
        mvprintw(i, j * 2, "- ");  // Умножаем j на 2 для пробела
      }
      else if (map[i][j] == 1) {
	attron(COLOR_PAIR(1));
        mvprintw(i, j * 2, "@ ");  // Умножаем j на 2 для пробела
	attroff(COLOR_PAIR(1));      
	}
	 else if (map[i][j] == 5) {
	attron(COLOR_PAIR(4));
        mvprintw(i, j * 2, "@ ");  // Умножаем j на 2 для пробела
	attroff(COLOR_PAIR(4));      
	}

	 else if (map[i][j] == 2 || map[i][j] == 4) {
        attron(COLOR_PAIR(2));
        mvprintw(i, j * 2, "* ");  // Умножаем j на 2 для пробела
        attroff(COLOR_PAIR(2));
      } else if (map[i][j] == 3) {
        mvprintw(i, j * 2, "# ");  // Умножаем j на 2 для пробела
      }
    }
  }
//getch();
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

std::vector<std::vector<int>> muv(std::vector<std::vector<int>> map, int N){
    std::vector<std::vector<int>> map11 = map;
    
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            
            if(map[i][j]==1){

                char MM;
                               map11[i][j]=5;
		printmap(map11, N);

		std::cin>>MM;
              		map11[i][j]=0;
                if(MM == 'd'){
                    if(map[i][j+1]!=2){
                        map11[i][j+1]=1;
                    }
                    else{
                        map11[i][j+1]=2;
                    }
                }
                else if(MM == 'a'){
                    if(map[i][j-1]!=2){
                        map11[i][j-1]=1;
                    }
                    else{
                        map11[i][j-1]=2;
                    }
                }
                else if(MM == 'w'){
                    if(map[i-1][j]!=2){
                        map11[i-1][j]=1;
                    }
                    else{
                        map11[i-1][j]=2;
                    }
                }
                else if(MM == 's'){
                    if(map[i+1][j]!=2){
                        map11[i+1][j]=1;
                    }
                    else{
                        map11[i+1][j]=2;
                    }
                
                }
                else{
			map11[i][j]=1;

		}
            printmap(map11, N);
                
            }
        }
    }

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
usleep(10000);
             printmap(map11, N);
              
  }    
 	                     
            }
        }
    }
    return map11;
}

std::vector<std::vector<int>> muv3(std::vector<std::vector<int>> map, int N){
    std::vector<std::vector<int>> map11 = map;
    
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            
            if(map[i][j]==1){
                char MM;
               
                map11[i][j]=5;
		printmap(map11, N);
			
		std::cin>>MM;
		map11[i][j]=1;

                
                if(MM == 'd'){
                        map11[i][j+1]=3;
                }
                else if(MM == 'a'){
                    map11[i][j-1]=3;
                    
                }
                else if(MM == 'w'){
                    
                        map11[i-1][j]=3;
                    
                }
                else if(MM == 's'){
                   
                        map11[i+1][j]=3;
                    
                }
            
             //printmap(map11, N);    
            }
        }
    }

    return map11;
}

bool checkVin(std::vector<std::vector<int>> map, int N){
    std::vector<std::vector<int>> map1 = map;
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            if (map[i][j]==3){
                for(int j1=0; j1<N; j1++){
                    if(map[i][j1]!=3){
                        map1[i][j1]=10;
                    }
                }
            break;
        } 
    }
    }
   
    int sum=0;
    for(int j = 0; j<N; j++){
        for(int i = 0; i<N; i++){
            if (map[i][j]==3){
                for(int i1=0; i1<N; i1++){
                    if(map[i1][j]!=3 and map1[i1][j]==10){
                        map1[i1][j]=9;
                        sum=sum+1;
                    }
                }
            break;
        } 
    }
    }
    for(int j0 = 0; j0<sum; j0++){
    for(int j = 0; j<N; j++){
        for(int i = 0; i<N; i++){
            if (map1[i][j]==9 and i>0 and i<(N-1) and j>0 and j<(N-1)){
                if(map1[i+1][j]==0 or map1[i-1][j]==0 or
                map1[i][j+1]==0 or map1[i][j-1]==0 or 
                map1[i+1][j]==10 or map1[i-1][j]==10 or
                map1[i][j+1]==10 or map1[i][j-1]==10){
                    map1[i][j]=0;
                }   
                }
            else if(map1[i][j]==9 and i == 0 and j == 0){
               if(map1[i+1][j]==0 or map1[i][j+1]==0 or 
                map1[i+1][j]==10 or map1[i][j+1]==10){
                    map1[i][j]=0;
                    
                } 
            }
            else if(map1[i][j]==9 and i == (N-1) and j == (N-1)){
               if(map1[i-1][j]==0 or map1[i][j-1]==0 or 
                map1[i-1][j]==10 or map1[i][j-1]==10){
                    map1[i][j]=0;
                    
                } 
            }    
            else if(map1[i][j]==9 and i == 0 and j == (N-1)){
               if(map1[i+1][j]==0 or map1[i][j-1]==0 or 
                map1[i+1][j]==10 or map1[i][j-1]==10){
                    map1[i][j]=0;
                    
                } 
            }     
              
             else if(map1[i][j]==9 and i == (N-1) and j == 0){
               if(map1[i-1][j]==0 or map1[i][j+1]==0 or 
                map1[i-1][j]==10 or map1[i][j+1]==10){
                    map1[i][j]=0;
                    
                } 
            }   
            
            if (map1[i][j]==9 and i==0 and j>0 and j<(N-1)){
                if(map1[i+1][j]==0 or map1[i][j+1]==0 
                or map1[i][j-1]==0 or map1[i+1][j]==10
                or map1[i][j+1]==10 or map1[i][j-1]==10){
                    map1[i][j]=0;
                }
            }
            if (map1[i][j]==9 and i==(N-1) and j>0 and j<(N-1)){
                if(map1[i-1][j]==0 or map1[i][j+1]==0 
                or map1[i][j-1]==0 or map1[i-1][j]==10
                or map1[i][j+1]==10 or map1[i][j-1]==10){
                    map1[i][j]=0;
                }
            }
            if (map1[i][j]==9 and i>0 and i<(N-1) and j==0){
                if(map1[i+1][j]==0 or map1[i-1][j]==0 or
                map1[i][j+1]==0 or map1[i+1][j]==10
                or map1[i-1][j]==10 or map1[i][j+1]==10){
                    map1[i][j]=0;
                }   
                }
            if (map1[i][j]==9 and i>0 and i<(N-1) and j==(N-1)){
                if(map1[i+1][j]==0 or map1[i-1][j]==0 or
                map1[i][j-1]==0 or map1[i+1][j]==10
                or map1[i-1][j]==10 or map1[i][j-1]==10){
                    map1[i][j]=0;
                }   
                }
            
            }
        
    }
    }
    for(int i = 0; i<N; i++){
    for(int j = 0; j<N; j++){
        if(map1[i][j]==9 and map[i][j]==1){
            return true;
        }
        
    }
    }
     return false;
}


int main()
{
    int N=10;	
    bool win;
    std::vector<std::vector<int>> map;
    map=makemap(N, 3, 3);
    initscr();
    cbreak();
    noecho();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    printmap(map, N);
    for(int i = 0; i<10; i++){
    map = muv(map, N);
    map = muv3(map, N);
    map = muv2(map, N);
    win=checkVin(map, N);
    if(win==true){
clear();
int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

    const char* message = "WIN";
  int message_len = strlen(message);
  int start_y = max_y / 2;
  int start_x = (max_x - message_len) / 2;


  mvprintw(start_y, start_x, message);

 
  refresh();

    getch();
    break;
    }
    }

   endwin(); 
    return 0;
}
