#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void printmap(std::vector<std::vector<int>> map, int N){
  

  int height=30, width=40;
  //getmaxyx(stdscr, height, width);

    int startY =0;
  int startX = 0;
for (int i = 0; i < 2*N + 1; i++) { // +2 для рамок, сверху и снизу
    move(startY, startX + i); // Верхняя граница
    addch(ACS_HLINE);

    move(startY + N + 1, startX + i); // Нижняя граница
    addch(ACS_HLINE);
  }

  for (int i = 0; i < N + 2; ++i) { // +2 для рамок, по бокам
    move(startY + i, startX); // Левая граница
    addch(ACS_VLINE);

    move(startY + i, startX + 2 * N + 1); // Правая граница
    addch(ACS_VLINE);
  }

 
  move(startY, startX); addch(ACS_ULCORNER);
  move(startY, startX + 2 * N + 1); addch(ACS_URCORNER);
  move(startY + N + 1, startX); addch(ACS_LLCORNER);
  move(startY + N + 1, startX + 2 * N + 1); addch(ACS_LRCORNER);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
                if (map[i][j] == 0) {
        mvprintw(i+1, j * 2+1, "- ");  // Умножаем j на 2 для пробела
      }
      else if (map[i][j] == 1) {
	attron(COLOR_PAIR(1));
        mvprintw(i+1, j * 2+1, "@ ");  // Умножаем j на 2 для пробела
	attroff(COLOR_PAIR(1));      
	}
	 else if (map[i][j] == 5) {
	attron(COLOR_PAIR(4));
        mvprintw(i+1, j * 2+1, "@ ");  // Умножаем j на 2 для пробела
	attroff(COLOR_PAIR(4));      
	}

	 else if (map[i][j] == 2 || map[i][j] == 4) {
        attron(COLOR_PAIR(2));
        mvprintw(i+1, j * 2+1, "* ");  
        attroff(COLOR_PAIR(2));
      } else if (map[i][j] == 3) {
        mvprintw(i+1, j * 2+1, "# ");  
      }
  }
}
   refresh();  
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
    
    }/*
    map11[1][0] = 1;
    map11[6][6] = 2;
*/
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
                        map11[i][j+1]=6;
                    }
                }
                else if(MM == 'a'){
                    if(map[i][j-1]!=2){
                        map11[i][j-1]=1;
                    }
                    else{
                        map11[i][j-1]=6;
                    }
                }
                else if(MM == 'w'){
                    if(map[i-1][j]!=2){
                        map11[i-1][j]=1;
                    }
                    else{
                        map11[i-1][j]=6;
                    }
                }
                else if(MM == 's'){
                    if(map[i+1][j]!=2){
                        map11[i+1][j]=1;
                    }
                    else{
                        map11[i+1][j]=6;
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

bool checkVin(std::vector<std::vector<int>> map, int N, int &area){
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
    int area1=sum;
    for(int j0 = 0; j0<sum; j0++){
    for(int j = 0; j<N; j++){
        for(int i = 0; i<N; i++){
            if (map1[i][j]==9 and i>0 and i<(N-1) and j>0 and j<(N-1)){
                if(map1[i+1][j]==0 or map1[i-1][j]==0 or
                map1[i][j+1]==0 or map1[i][j-1]==0 or 
                map1[i+1][j]==10 or map1[i-1][j]==10 or
                map1[i][j+1]==10 or map1[i][j-1]==10){
                    map1[i][j]=0;
		     area1--;
                }   
                }
            else if(map1[i][j]==9 and i == 0 and j == 0){
               if(map1[i+1][j]==0 or map1[i][j+1]==0 or 
                map1[i+1][j]==10 or map1[i][j+1]==10){
                    map1[i][j]=0;
                    area1--;
                } 
            }
            else if(map1[i][j]==9 and i == (N-1) and j == (N-1)){
               if(map1[i-1][j]==0 or map1[i][j-1]==0 or 
                map1[i-1][j]==10 or map1[i][j-1]==10){
                    map1[i][j]=0;
                    area1--;
                } 
            }    
            else if(map1[i][j]==9 and i == 0 and j == (N-1)){
               if(map1[i+1][j]==0 or map1[i][j-1]==0 or 
                map1[i+1][j]==10 or map1[i][j-1]==10){
                    map1[i][j]=0;
                    area1--;
                } 
            }     
              
             else if(map1[i][j]==9 and i == (N-1) and j == 0){
               if(map1[i-1][j]==0 or map1[i][j+1]==0 or 
                map1[i-1][j]==10 or map1[i][j+1]==10){
                    map1[i][j]=0;
                    area1--;
                } 
            }   
            
            if (map1[i][j]==9 and i==0 and j>0 and j<(N-1)){
                if(map1[i+1][j]==0 or map1[i][j+1]==0 
                or map1[i][j-1]==0 or map1[i+1][j]==10
                or map1[i][j+1]==10 or map1[i][j-1]==10){
                    map1[i][j]=0;
		     area1--;
                }
            }
            if (map1[i][j]==9 and i==(N-1) and j>0 and j<(N-1)){
                if(map1[i-1][j]==0 or map1[i][j+1]==0 
                or map1[i][j-1]==0 or map1[i-1][j]==10
                or map1[i][j+1]==10 or map1[i][j-1]==10){
                    map1[i][j]=0;
                    area1--;
                }
            }
            if (map1[i][j]==9 and i>0 and i<(N-1) and j==0){
                if(map1[i+1][j]==0 or map1[i-1][j]==0 or
                map1[i][j+1]==0 or map1[i+1][j]==10
                or map1[i-1][j]==10 or map1[i][j+1]==10){
                    map1[i][j]=0;
		     area1--;
                }   
                }
            if (map1[i][j]==9 and i>0 and i<(N-1) and j==(N-1)){
                if(map1[i+1][j]==0 or map1[i-1][j]==0 or
                map1[i][j-1]==0 or map1[i+1][j]==10
                or map1[i-1][j]==10 or map1[i][j-1]==10){
                    map1[i][j]=0;
		     area1--;
                }   
                }
            
            }
        
    }
	  area=area1;
    }    for(int i = 0; i<N; i++){
    for(int j = 0; j<N; j++){
        if(map1[i][j]==9 and map[i][j]==1){
            return true;
        }
        
    }
    }
     return false;
}

bool checkLose(std::vector<std::vector<int>> map, int N){
    for(int i = 0; i<N; i++){
    for(int j = 0; j<N; j++){
        if(map[i][j]==1){
            return false;
        }
        
    }
}
     return true;

}

std::vector<std::vector<int>> bestMuv(std::vector<std::vector<int>> map, int N){
    std::vector<std::vector<int>> map11 ;
    std::vector<std::vector<int>> mapEnd = map;
     std::vector<std::vector<int>> mapFind = map;
    srand(time(0));
    for(int i000 = 0; i000<N; i000++){
        for(int j000 = 0; j000<N; j000++){
            if(mapFind[i000][j000]==2){
                              map11 = map;
                
                
    int L=1, x0, y0, x00, y00;
 int len;
    bool find = false;
    int inf =-1 ;//std::numeric_limits<int>::max();
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
          
            
            {if(map11[i][j]==2 and i==i000 and j==j000){
                
                map11[i][j]=0;
                x0=i;
                y0=j;
                
            }
            else{
             
                map11[i][j]=inf;
            }}
            
         }   
        }
        mapFind[i000][j000]=4;
        //printmap(map11, N);
        int len2=N*N*100;
	int limit=0;
        while(find == false){
        for(int x = x0; x<N; x++){
        for(int y = y0; y<N; y++){
           
            
            if((x+1)<N and map11[x+1][y]==inf and map11[x][y]!= inf and map[x+1][y]!=3){
                map11[x+1][y]=map11[x][y]+1;
                if(map[x+1][y]==1 and map11[x+1][y]<len2){
                    len2=map11[x+1][y];
                    find = true;
                    x00=x+1;
                    y00=y;
                }
            }
           
            if((y-1)>=0 and map11[x][y-1]==inf and map11[x][y]!= inf and map[x][y-1]!=3){
                map11[x][y-1]=map11[x][y]+1;
                 if(map[x][y-1]==1 and map11[x][y-1]<len2){
                    len2=map[x][y-1];
                    find = true;
                    x00=x;
                    y00=y-1;
                }
            }
           
            if((y+1)<N and map11[x][y+1]==inf and map11[x][y]!= inf and map[x][y+1]!=3) {
                map11[x][y+1]=map11[x][y]+1;
                 if(map[x][y+1]==1  and map11[x][y+1]<len2){
                     len2=map[x][y+1];
                    find = true;
                    x00=x;
                    y00=y+1;
                }
            }
           
            if((x-1)>=0 and map11[x-1][y]==inf and map11[x][y]!= inf and map[x-1][y]!=3){
                map11[x-1][y]=map11[x][y]+1;
                if(map[x-1][y]==1 and map11[x-1][y]<len2){
                     len2=map11[x-1][y];
                    find = true;
                    x00=x-1;
                    y00=y;
                }
            }
             
        }}
       

            for(int x = x0; x>=0; x--){
        for(int y = y0; y>=0; y--){
        
            
           if((x+1)<N and map11[x+1][y]==inf and map11[x][y]!= inf and map[x+1][y]!=3){
                map11[x+1][y]=map11[x][y]+1;
                if(map[x+1][y]==1 and map11[x+1][y]<len2){
                    len2=map11[x+1][y];
                    find = true;
                    x00=x+1;
                    y00=y;
                }
            }
           
            if((y-1)>=0 and map11[x][y-1]==inf and map11[x][y]!= inf and map[x][y-1]!=3){
                map11[x][y-1]=map11[x][y]+1;
                 if(map[x][y-1]==1 and map11[x][y-1]<len2){
                    len2=map[x][y-1];
                    find = true;
                    x00=x;
                    y00=y-1;
                }
            }
           
            if((y+1)<N and map11[x][y+1]==inf and map11[x][y]!= inf and map[x][y+1]!=3) {
                map11[x][y+1]=map11[x][y]+1;
                 if(map[x][y+1]==1  and map11[x][y+1]<len2){
                     len2=map[x][y+1];
                    find = true;
                    x00=x;
                    y00=y+1;
                }
            }
           
            if((x-1)>=0 and map11[x-1][y]==inf and map11[x][y]!= inf and map[x-1][y]!=3){
                map11[x-1][y]=map11[x][y]+1;
                if(map[x-1][y]==1 and map11[x-1][y]<len2){
                     len2=map11[x-1][y];
                    find = true;
                    x00=x-1;
                    y00=y;
                }
            }
             
        }}
        
            for(int x = x0; x<N; x++){
        for(int y = y0; y>=0; y--){
        
           
            if((x+1)<N and map11[x+1][y]==inf and map11[x][y]!= inf and map[x+1][y]!=3){
                map11[x+1][y]=map11[x][y]+1;
                if(map[x+1][y]==1 and map11[x+1][y]<len2){
                    len2=map11[x+1][y];
                    find = true;
                    x00=x+1;
                    y00=y;
                }
            }
           
            if((y-1)>=0 and map11[x][y-1]==inf and map11[x][y]!= inf and map[x][y-1]!=3){
                map11[x][y-1]=map11[x][y]+1;
                 if(map[x][y-1]==1 and map11[x][y-1]<len2){
                    len2=map[x][y-1];
                    find = true;
                    x00=x;
                    y00=y-1;
                }
            }
           
            if((y+1)<N and map11[x][y+1]==inf and map11[x][y]!= inf and map[x][y+1]!=3) {
                map11[x][y+1]=map11[x][y]+1;
                 if(map[x][y+1]==1  and map11[x][y+1]<len2){
                     len2=map[x][y+1];
                    find = true;
                    x00=x;
                    y00=y+1;
                }
            }
           
            if((x-1)>=0 and map11[x-1][y]==inf and map11[x][y]!= inf and map[x-1][y]!=3){
                map11[x-1][y]=map11[x][y]+1;
                if(map[x-1][y]==1 and map11[x-1][y]<len2){
                     len2=map11[x-1][y];
                    find = true;
                    x00=x-1;
                    y00=y;
                }
            }
             
        }}
        
       for(int x = x0; x>=0; x--){
        for(int y = y0; y<N; y++){
        
            
            if((x+1)<N and map11[x+1][y]==inf and map11[x][y]!= inf and map[x+1][y]!=3){
                map11[x+1][y]=map11[x][y]+1;
                if(map[x+1][y]==1 and map11[x+1][y]<len2){
                    len2=map11[x+1][y];
                    find = true;
                    x00=x+1;
                    y00=y;
                }
            }
           
            if((y-1)>=0 and map11[x][y-1]==inf and map11[x][y]!= inf and map[x][y-1]!=3){
                map11[x][y-1]=map11[x][y]+1;
                 if(map[x][y-1]==1 and map11[x][y-1]<len2){
                    len2=map[x][y-1];
                    find = true;
                    x00=x;
                    y00=y-1;
                }
            }
           
            if((y+1)<N and map11[x][y+1]==inf and map11[x][y]!= inf and map[x][y+1]!=3) {
                map11[x][y+1]=map11[x][y]+1;
                 if(map[x][y+1]==1  and map11[x][y+1]<len2){
                     len2=map[x][y+1];
                    find = true;
                    x00=x;
                    y00=y+1;
                }
            }
           
            if((x-1)>=0 and map11[x-1][y]==inf and map11[x][y]!= inf and map[x-1][y]!=3){
                map11[x-1][y]=map11[x][y]+1;
                if(map[x-1][y]==1 and map11[x-1][y]<len2){
                     len2=map11[x-1][y];
                    find = true;
                    x00=x-1;
                    y00=y;
                }
            }
             
        }}
	limit++;
	if(limit>=N*N*N){
		x00=x0;
		y00=y0;
		break;
			}
        }
        
         len = map11[x00][y00];
    for(int i = 0; i<len-1; i++){   
        //mapEnd[x00][y00] = 2;
       if(x00+1<N and map11[x00+1][y00]<map11[x00][y00] and map11[x00+1][y00]!=inf){
                    
                    x00=x00+1;
                    
                }
        else if(x00-1>0 and map11[x00-1][y00]<map11[x00][y00] and map11[x00-1][y00]!=inf){
                    
                    x00=x00-1;
                    
                }
        else if(y00-1>0 and map11[x00][y00-1]<map11[x00][y00] and map11[x00][y00-1]!=inf){
                    
                    y00=y00-1;
                }
        else if(y00+1<N and map11[x00][y00+1]<map11[x00][y00] and map11[x00][y00+1]!=inf){
                    
                    y00=y00+1;
                }
    //printmap(mapEnd, N); 
    }
                mapEnd[x00][y00] = 2;
		
            }
	
           
        	}
        
    }

    printmap(mapEnd, N);  
    return mapEnd; 
}

int main()
{
    int N=10, records;
    int area=0;	
    bool win, lose;
    std::string word1=" MOVE ";
    std::string word2="BLOCKS";
    std::vector<std::vector<int>> map;
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    char mod;
    json config;
startGame:
    std::ifstream  input_file("records.json");
    
     input_file >> config;
    mvprintw(0, 0, "h:hard");
    mvprintw(1, 0, "n:normal");
    mvprintw(2, 0, "e:easy");
    refresh();

     std::cin>>mod;      
    if(mod=='h'){
    goto hard;
    }
    if(mod=='n'){
    goto normal;
    }
    if(mod=='e'){
    goto easy;
    }
    hard:
 map=makemap(N, 4, 5);

    printmap(map, N);
    for(;;){

    attron(COLOR_PAIR(5)); // Включаем цвет 5 (черный текст, белый фон)
    mvprintw(N+5, 0, "%s", word1.c_str()); // Выводим текст
    attroff(COLOR_PAIR(5));
    
    map = muv(map, N);

    attron(COLOR_PAIR(5)); // Включаем цвет 5 (черный текст, белый фон)
    mvprintw(N+5, 0, "%s", word2.c_str()); // Выводим текст
    attroff(COLOR_PAIR(5));

    map = muv3(map, N);
    win=checkVin(map, N, area);
	if(win==true){
 records=config["record"]["hardRec"];

	goto start; 
    }
    map = bestMuv(map, N);
    map = bestMuv(map, N);

    map = bestMuv(map, N);
    lose=checkLose(map, N);
    if(lose==true){
	goto start1; 
    }
    }

    normal:
 map=makemap(N, 3, 3);

    printmap(map, N);
    for(;;){

    attron(COLOR_PAIR(5)); // Включаем цвет 5 (черный текст, белый фон)
    mvprintw(N+5, 0, "%s", word1.c_str()); // Выводим текст
    attroff(COLOR_PAIR(5));
    
    map = muv(map, N);

    attron(COLOR_PAIR(5)); // Включаем цвет 5 (черный текст, белый фон)
    mvprintw(N+5, 0, "%s", word2.c_str()); // Выводим текст
    attroff(COLOR_PAIR(5));

    map = muv3(map, N);
    win=checkVin(map, N, area);
	if(win==true){
records=config["record"]["normalRec"];

	goto start; 
    }

    map = bestMuv(map, N);
    lose=checkLose(map, N);
    if(lose==true){
	goto start1; 
    }
    }

    easy:
 map=makemap(N, 3, 2);

    printmap(map, N);
    for(;;){

    attron(COLOR_PAIR(5)); // Включаем цвет 5 (черный текст, белый фон)
    mvprintw(N+5, 0, "%s", word1.c_str()); // Выводим текст
    attroff(COLOR_PAIR(5));
    
    map = muv(map, N);

    attron(COLOR_PAIR(5)); // Включаем цвет 5 (черный текст, белый фон)
    mvprintw(N+5, 0, "%s", word2.c_str()); // Выводим текст
    attroff(COLOR_PAIR(5));

    map = muv3(map, N);
    win=checkVin(map, N, area);
	if(win==true){
records=config["record"]["easyRec"];

	goto start; 
    }

    map = muv2(map, N);
    lose=checkLose(map, N);
    if(lose==true){
	goto start1; 
    }
    }

start:    
{
clear();
int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  const char* message = "WIN";
  int message_len = strlen(message);
  int start_y = max_y / 2;
  
  int start_x = (max_x - message_len) / 2;
  mvprintw(start_y, start_x, message);
  
  message = "score";

  mvprintw(start_y+2, start_x, message);
  mvprintw(start_y+2, start_x+5,"%d", area);
  mvprintw(start_y+3, start_x, "record");
  mvprintw(start_y+3, start_x+6,"%d",records);

if(area>config["record"]["hardRec"] and mod=='h'){
mvprintw(start_y+4, start_x, "new record");
std::ofstream output_file("records.json");
config["record"]["hardRec"]=area;
    output_file << config.dump(4);
output_file.close();
}

if(area>config["record"]["normalRec"] and mod=='n'){
mvprintw(start_y+4, start_x, "new record");
std::ofstream output_file("records.json");
config["record"]["normalRec"]=area;
    output_file << config.dump(4);
output_file.close();
}

if(area>config["record"]["easyRec"] and mod=='e'){
mvprintw(start_y+4, start_x, "new record");
std::ofstream output_file("records.json");
config["record"]["easyRec"]=area;
    output_file << config.dump(4);
output_file.close();
}


refresh();

  getch();

    }
   goto endGame;


endGame:  
  clear();
  mvprintw(1, 0, "n:new game");
  mvprintw(2, 0, "e:end");
  refresh();
   std::cin>>mod;   

    if(mod=='n'){
    goto startGame;
    }
   endwin(); 
   return 0;

start1:    

clear();
int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  const char* message = "LOSE";
  int message_len = strlen(message);
  int start_y = max_y / 2;
  int start_x = (max_x - message_len) / 2;


  mvprintw(start_y, start_x, message);

 
  refresh();
  getch();
  goto endGame;
  


}
