#include "function.h"


void printmap(std::vector<std::vector<int>> map, int N){
  
  
  int height, width;
  getmaxyx(stdscr, height, width);

  int startY = (height-N)/2;
  int startX = (width-N)/2;
for (int i = 0; i < 2*N + 1; i++) { // +2 для рамок, сверху и снизу
    move(startY, startX + i); // Верхняя граница
    addch(ACS_HLINE);

    move(startY + N + 1, startX + i); 
    addch(ACS_HLINE);
  }

  for (int i = 0; i < N + 2; ++i) { 
    move(startY + i, startX); 
    addch(ACS_VLINE);

    move(startY + i, startX + 2 * N + 1); 
    addch(ACS_VLINE);
  }

 
  move(startY, startX); addch(ACS_ULCORNER);
  move(startY, startX + 2 * N + 1); addch(ACS_URCORNER);
  move(startY + N + 1, startX); addch(ACS_LLCORNER);
  move(startY + N + 1, startX + 2 * N + 1); addch(ACS_LRCORNER);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
                if (map[i][j] == 0) {
        mvprintw(startY + i+1,startX +  j * 2+1, "- ");  // Умножаем j на 2 для пробела
      }
      else if (map[i][j] == 1) {
	attron(COLOR_PAIR(1));
        mvprintw(startY + i+1,startX +  j * 2+1, "@ ");  // Умножаем j на 2 для пробела
	attroff(COLOR_PAIR(1));      
	}
	 else if (map[i][j] == 5) {
	attron(COLOR_PAIR(4));
        mvprintw(startY + i+1,startX +  j * 2+1, "@ ");  // Умножаем j на 2 для пробела
	attroff(COLOR_PAIR(4));      
	}

	 else if (map[i][j] == 2 || map[i][j] == 4) {
        attron(COLOR_PAIR(2));
        mvprintw(startY + i+1,startX +  j * 2+1, "* ");  // Умножаем j на 2 для пробела
        attroff(COLOR_PAIR(2));
      } else if (map[i][j] == 3) {
        mvprintw(startY + i+1,startX +  j * 2+1, "# ");  // Умножаем j на 2 для пробела
      }
 else if (map[i][j] == 6) {
        mvprintw(startY + i+1,startX +  j * 2+1, "x ");  // Умножаем j на 2 для пробела
      }

    }
  }
	mvprintw(startY +1, 0 , "v - move down");
	mvprintw(startY +2, 0 , "< - move right");
	mvprintw(startY +3, 0 , "> - move left");
	mvprintw(startY , 0 , "^ - move up");	
	mvprintw(startY -1, 0 , "enter - skip move");
	mvprintw(startY -2, 0 , "s - save game");
	mvprintw(startY -3, 0 , "m - menu");

   refresh();  
}
std::vector<std::vector<int>> makemap(int N, int a, int b, bool wall){
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
    if(wall){
   for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
	if(i==0 or j==0 or i==N-1 or j==N-1){
	map11[i][j]=2;}
}
}	
}

    int i = 0;
 while(i<a){
        int x = rand() % (end - start + 1) + start;
        int y = rand() % (end - start + 1) + start;
        if(map11[x][y] != 1){
            map11[x][y] = 2;
            i++;
        }    
    
    }
    i = 0;
   while(i<b){
        int x = rand() % (end - start + 1) + start;
        int y = rand() % (end - start + 1) + start;
        if(map11[x][y] != 2){
            map11[x][y] = 1;
            i++;
        }    
    
    }/*
    map11[1][1] = 1;
    map11[6][6] = 2;
 map11[4][1] = 1;
*/
        return map11;
}

std::vector<std::vector<int>> muv(std::vector<std::vector<int>> map, int N, std::string &name, bool &muve1, bool &code,int &muve){
    std::vector<std::vector<int>> map11 = map;
        for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            
            if(map[i][j]==1){

                int ch;
		Q:
                map11[i][j]=5;
		printmap(map11, N);
		map11[i][j]=0;
		ch = getch(); 
		switch (ch) {
              	case KEY_RIGHT:
                    if(map[i][j+1]!=2){
                        map11[i][j+1]=1;
                    }
                    else{
                        map11[i][j+1]=6;
                    }
          	    break;
                case KEY_LEFT:
                    if(map[i][j-1]!=2){
                        map11[i][j-1]=1;
                    }
                    else{
                        map11[i][j-1]=6;
                    }
                break;
            	case KEY_UP:
                    if(map[i-1][j]!=2){
                        map11[i-1][j]=1;
                    }
                    else{
                        map11[i-1][j]=6;
                    }
                break;
                case KEY_DOWN:
                    if(map[i+1][j]!=2){
                        map11[i+1][j]=1;
                    }
                    else{
                        map11[i+1][j]=6;
                    }
                
		break;
                case 10:
			map11[i][j]=1;
		break;
		case 's':
                        saveGame(map, N, name, muve1, muve);
			goto Q;
			break;
		case 'm':
                        int k=menu(map, N, name, muve1, muve);
			switch (k) {
			case 1:
				clear();
				goto Q;
				break;
			case 0:
				clear();
				endwin();
				std::exit(EXIT_SUCCESS);
				break;
			case 2:
				clear();
				code = true;
				return map11;
				break;


}
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
            if(map[i1][j1]==2 or map[i1][j1]==6){
               if(map[i1][j1]==2){ map11[i1][j1]=2;}
		if(map[i1][j1]==6){ map11[i1][j1]=6;}

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
                            if((i1+1)<N and abs(i-i1)>=abs(j-j1) and i1<i and map11[i1+1][j1]!=3 and map11[i1+1][j1]!=4){
                            if(i1+1!=I and j1!=J and map11[i1+1][j1]!=6){    
			    map11[i1+1][j1]=2;}
			    else if((i1+1==I and j1==J) or map11[i1+1][j1]==6)
                            { map11[i1+1][j1]=6;}
                          }
                        else if((i1-1)>=0 and abs(i-i1)>=abs(j-j1) and i1>i and map11[i1-1][j1]!=3 and map11[i1-1][j1]!=4){
                            if(i1-1!=I and j1!=J and  map11[i1-1][j1]!=6){    
			    map11[i1-1][j1]=2;}
			    else if((i1-1==I and j1==J) or  map11[i1-1][j1]==6){
 			     map11[i1-1][j1]=6;}
                        }
                        else if((j1-1)>=0 and abs(i-i1)<=abs(j-j1) and j1>j and map11[i1][j1-1]!=3 and map11[i1][j1-1]!=4){
                            if(i1!=I and j1-1!=J and map11[i1][j1-1]!=6){ 
                            map11[i1][j1-1]=2;}
                            else if ((i1==I and j1-1==J) or map11[i1][j1-1]==6){ map11[i1][j1-1]=6;}

                        }
                        else if((j1+1)<N and (i-i1)<=abs(j-j1) and j1<j and map11[i1][j1+1]!=3 and map11[i1][j1+1]!=4){
                            if(i1!=I and j1+1!=J and map11[i1][j1+1]!=6){ 
                            map11[i1][j1+1]=2;}
                            else if ((i1==I and j1+1==J) or map11[i1][j1+1]==6){ map11[i1][j1+1]=6;}
                        }
                        else if((i1+1)<N and map11[i1][j1+1]==3 and map11[i1+1][j1]!=3 ){

                            map11[i1+1][j1]=2;

                        }
                        else if((i1+1)<N and map11[i1][j1-1]==3  and map11[i1+1][j1]!=3){

                            map11[i1+1][j1]=2;

                        }
                        else if((j1+1)<N and map11[i1+1][j1]==3 and map11[i1][j1+1]!=3){
                            map11[i1][j1+1]=2;
                        }
                        else if((j1+1)<N and map11[i1-1][j1]==3 and map11[i1][j1+1]!=3){
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

std::vector<std::vector<int>> muv3(std::vector<std::vector<int>> map, int N, std::string &name, bool &muve1, bool &code, int &muve){
    std::vector<std::vector<int>> map11 = map;
    
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            
            if(map[i][j]==1){
                int ch;
               
                map11[i][j]=5;
		printmap(map11, N);
			
		
		map11[i][j]=1;

                Q:
                ch = getch(); 
		switch (ch) {
		case KEY_RIGHT:
                        map11[i][j+1]=3;
			break;
                case KEY_LEFT:
                    map11[i][j-1]=3;
			break;
                case KEY_UP: 
                        map11[i-1][j]=3;
			break;
                case KEY_DOWN:
                        map11[i+1][j]=3;
      			break;   
		case 's':
                        saveGame(map, N, name, muve1, muve);
			goto Q;           
                }     
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
            if(mapFind[i000][j000]==2 or mapFind[i000][j000]==6){
                              map11 = map;
                
                
    int L=1, x0, y0, x00, y00;
 int len;
    bool find = false;
    int inf =-1 ;//std::numeric_limits<int>::max();
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
          
            
            {if((map11[i][j]==6 or map11[i][j]==2) and i==i000 and j==j000){
                
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
    }
		if(map[x00][y00] != 6 and  map[x00][y00] != 1){
                mapEnd[x00][y00] = 2;}
		else if(map[x00][y00] == 6 or map[x00][y00] == 1) 
		{(mapEnd[x00][y00] = 6);}
		
            }
	
           
        	}
        
    }

    printmap(mapEnd, N);  
    return mapEnd; 
}

void saveGame(std::vector<std::vector<int>> map, int N, std::string &name, bool &muve1, int &muve){
	
	nlohmann::json config;
	std::ifstream  input_file("saves.json");
	input_file >> config;
	input_file.close();
	config["Quick"]["map"]=map;
	config["Quick"]["name"]=name;
	config["Quick"]["muve1"]=muve1;
	config["Quick"]["muve"]=muve;

	std::ofstream output_file("saves.json");
	
	output_file  << std::setw(4) << config << std::endl; 
	output_file.close();
 mvprintw(1,1, "game was saved");
	}

void saveGameOld(std::vector<std::vector<int>> map, int N, std::string &name, bool &muve1, int &muve){
	clear();
	nlohmann::json config;
	std::string num;
	std::ifstream  input_file("saves.json");
	input_file >> config;
	input_file.close();

	int highlight = 0;
	std::vector<std::string> menuItems = {
        "case 1",
        "case 2",
	"case 3"
    };

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	for(;;){
	clear(); 

        
        mvprintw(1, xMax / 2 - 5, "GAME MENU");

        
        for (int i = 0; i < menuItems.size(); ++i) {
            if (i == highlight) {
                attron(A_REVERSE);             }
            mvprintw(yMax / 2 - menuItems.size() / 2 + i, xMax / 2 - menuItems[i].length() / 2, menuItems[i].c_str());
            attroff(A_REVERSE); 
        }

        refresh(); 

        
        int choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1) {
                    highlight = menuItems.size() - 1;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == menuItems.size()) {
                    highlight = 0; 
                }
                break;
            case 10:
            {
                
                if (menuItems[highlight] == "case 1") {
                   num = "1";
		goto Q;

                }
	if (menuItems[highlight] ==  "case 2") {	
	num = "2";
	goto Q;

	}
	if (menuItems[highlight] ==  "case 3") {	
	num = "3";
	goto Q;
	}
	
	

}}}
Q:


	config["old"][num]["map"]=map;
	config["old"][num]["name"]=name;
	config["old"][num]["muve1"]=muve1;
	config["old"][num]["muve"]=muve;

	std::ofstream output_file("saves.json");
	
	output_file << std::setw(4) << config << std::endl; 
	output_file.close();

	}


int menu(std::vector<std::vector<int>> map, int N, std::string &name, bool &muve1, int &muve){
	int highlight = 0;
	std::vector<std::string> menuItems = {
        "Continue",
	"Save game",
	"Exit to menu",
	"Exit game"
    };

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	for(;;){
	clear(); 

        
        mvprintw(1, xMax / 2 - 5, "GAME MENU");

        
        for (int i = 0; i < menuItems.size(); ++i) {
            if (i == highlight) {
                attron(A_REVERSE);             }
            mvprintw(yMax / 2 - menuItems.size() / 2 + i, xMax / 2 - menuItems[i].length() / 2, menuItems[i].c_str());
            attroff(A_REVERSE); 
        }

        refresh(); 

        
        int choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1) {
                    highlight = menuItems.size() - 1;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == menuItems.size()) {
                    highlight = 0; 
                }
                break;
            case 10:
            {
                
                if (menuItems[highlight] == "Exit game") {
                    return 0;
                }
	if (menuItems[highlight] ==  "Continue") {	
	return 1;

	}
	if (menuItems[highlight] ==  "Exit to menu") {	
	return 2;

	}
	
	if (menuItems[highlight] ==  "Save game") {	
	 saveGameOld(map, N, name, muve1, muve);

	}


}}}

}