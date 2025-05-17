#include "function.h"
#include <cctype>
int main()
{
	int N=10, records;
	int area=0;
	std::string name;
	bool win, lose;
	std::string word1=" MOVE ";
	std::string word2="BLOCKS";
	std::vector<std::vector<int>> map;
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	start_color();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	char mod;
	
	bool wall, muve1, code=false;
	int saiz, mans, beds, muw;
	std::string num;
std::vector<std::string> Case = {
        "case 1",
        "case 2",
	"case 3"
    };

	json config;
nlohmann::json config1;
	int start_y;
std::vector<std::string> endGame = {
        "new game",
        "end game"
    };
int yMax, xMax;
int message_len;
int start_x;
const char* message1 = "LOSE";
        getmaxyx(stdscr, yMax, xMax);
	
    
    std::vector<std::string> menuItems = {
        "Easy",
        "Normal",
        "Hard",
        "Special",
	"Quick load",
	"Load game",
        "Exit"
    };
int highlight = 0;

startGame:
std::ifstream  input_file("records.json");
input_file >> config;


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
                
                if (menuItems[highlight] == "Exit") {
                    endwin(); 
                    return 0;
                }
	if (menuItems[highlight] == "Hard") {	
	goto hard;
	}
	else if (menuItems[highlight] == "Easy") {
	goto easy;
	}
else if (menuItems[highlight] == "Normal") {		
goto normal;
	}
		else if (menuItems[highlight] == "Quick load") {
    std::ifstream input_file("saves.json");
     input_file >> config1;
    input_file.close();	
	map=config1["Quick"]["map"].get<std::vector<std::vector<int>>>();
	name=config1["Quick"]["name"];
	muve1=config1["Quick"]["muve1"];
	muw=config1["Quick"]["muve"];

	goto ldgame;
	}

    else if (menuItems[highlight] == "Load game") {
    std::ifstream input_file("saves.json");
    input_file >> config1;
    input_file.close();	
    clear();refresh();
    highlight=0;

	for(;;){
    mvprintw(1, xMax / 2 - 5, "GAME MENU");
	    for (int i = 0; i < Case.size(); ++i) {
    if (i == highlight) {
         attron(A_REVERSE);             }
            mvprintw(yMax / 2 -Case.size() / 2 + i, xMax / 2 - Case[i].length() / 2, Case[i].c_str());
            attroff(A_REVERSE); 
        }

        refresh(); 

        
        int choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1) {
                    highlight = Case.size() - 1;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == Case.size()) {
                    highlight = 0; 
                }
                break;
            case 10:
            {
                
                if (Case[highlight] == "case 1") {
                   num = "1";
		goto Q;

                }
	if (Case[highlight] ==  "case 2") {	
	num = "2";
	goto Q;

	}
	if (Case[highlight] ==  "case 3") {	
	num = "3";
	goto Q;
	}
}}}
	Q:
	map=config1["old"][num]["map"].get<std::vector<std::vector<int>>>();
	name=config1["old"][num]["name"];
	muve1=config1["old"][num]["muve1"];
	muw=config1["old"][num]["muve"];

	goto ldgame;
	}


else {
		goto spesial;
	}

}}}
noecho();

ldgame:
saiz = map[0].size(); muw=1;
goto gameS;

hard:
	    name = "hard";
	    saiz = config["lewels"][name]["saiz"];
            mans = config["lewels"][name]["@"];
            beds = config["lewels"][name]["*"];
            muw = config["lewels"][name]["muve"];
            wall = config["lewels"][name]["wall"].get<bool>();
	    muve1 = config["lewels"][name]["muve1"].get<bool>();

	goto game;
normal:
		name = "normal";
	    saiz = config["lewels"][name]["saiz"];
            mans = config["lewels"][name]["@"];
            beds = config["lewels"][name]["*"];
            muw = config["lewels"][name]["muve"];
            wall = config["lewels"][name]["wall"].get<bool>();
	    muve1 = config["lewels"][name]["muve1"].get<bool>();

	goto game;

easy:
	name = "easy";
	    saiz = config["lewels"][name]["saiz"];
            mans = config["lewels"][name]["@"];
            beds = config["lewels"][name]["*"];
            muw = config["lewels"][name]["muve"];
            wall = config["lewels"][name]["wall"].get<bool>();
	    muve1 = config["lewels"][name]["muve1"].get<bool>();
		
	goto game;



endGame:

	 highlight = 0;

for(;;){
	clear(); 

                mvprintw(1, xMax / 2 - 5, "GAME MENU");

        
        for (int i = 0; i < endGame.size(); ++i) {
            if (i == highlight) {
                attron(A_REVERSE);
            }
            mvprintw(yMax / 2 - endGame.size() / 2 + i, xMax / 2 - endGame[i].length() / 2, endGame[i].c_str()); 
            attroff(A_REVERSE); 
        }

        refresh(); 

        
        int choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1) {
                    highlight = endGame.size() - 1;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == endGame.size()) {
                    highlight = 0; 
                }
                break;
            case 10:             {
                
                if (endGame[highlight] == "end game") {
                    endwin(); 
                    return 0;
                }
		else{
		goto startGame;
	}
}}}
start1:

	clear();
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	
	 message_len = strlen(message1);
	start_y = max_y / 2;
	 start_x = (max_x - message_len) / 2;
	mvprintw(start_y, start_x, message1);
	refresh();
	getch();
	goto endGame;

spesial:
{

	
   endwin();

	std::cout<<"new or old (n/o)"<<std::endl;
	std::cin>>mod;
	

	
        if (mod == 'n') {
        std::cout << "name level: " << std::endl;

        std::cin.ignore(); 
        std::getline(std::cin, name); 

        std::cout << "saiz of map, number of @ and *: " << std::endl;
        std::cin >> saiz >> mans >> beds;
        std::cout << "how many move for *: " << std::endl;
        std::cin >> muw;
	std::cout << "wall of *(1/0): " << std::endl;
	std::cin >> wall;
	std::cout << "best muve * (1/0): " << std::endl;
	std::cin >> muve1;
	
	config["lewels"][name]["name"] = name;
        config["lewels"][name]["saiz"] = saiz;
        config["lewels"][name]["@"] = mans;
        config["lewels"][name]["*"] = beds;
        config["lewels"][name]["muve"] = muw;
        config["lewels"][name]["wall"] = wall;
	config["lewels"][name]["muve1"] = muve1;
 
        std::ofstream ofs("records.json"); 
        ofs << std::setw(4) << config << std::endl; 
        ofs.close();

	}
        else if (mod == 'o') {
	for(auto m : config["lewels"]){
	std::cout <<m["name"]<< std::endl;
	
        std::cout << "  saiz: " << m["saiz"] << std::endl;
            std::cout << "  @: " << m["@"]<< std::endl;
            std::cout << "  *: " << m["*"]<< std::endl;
            std::cout << "  muve: " << m["muve"]<< std::endl;
            std::cout << "  wall: " << m["wall"]<< std::endl;
	    std::cout << "  best muve: " << m["muve1"]<< std::endl;

}
        std::cout << "name level: " << std::endl;
        std::cin.ignore(); 
        std::getline(std::cin, name);

        if (config["lewels"].contains(name)) { 
            saiz = config["lewels"][name]["saiz"];
            mans = config["lewels"][name]["@"];
            beds = config["lewels"][name]["*"];
            muw = config["lewels"][name]["muve"];
            wall = config["lewels"][name]["wall"].get<bool>(); 
	    muve1 = config["lewels"][name]["muve1"].get<bool>();
            std::cout << "lewel fith name: " << name << std::endl;
            std::cout << "  saiz: " << saiz << std::endl;
            std::cout << "  @: " << mans << std::endl;
            std::cout << "  *: " << beds << std::endl;
            std::cout << "  muve: " << muw << std::endl;
            std::cout << "  wall: " << wall << std::endl;
	    std::cout << "  best muve: " << muve1 << std::endl;

		getch();
        }}
game:
	code=false;
	initscr();
	cbreak();
	curs_set(0);
	noecho();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);

	map = makemap(saiz,beds ,mans, wall);
	gameS:
	clear(); refresh();
	for(;;)
	{	attron(COLOR_PAIR(5)); 
		mvprintw(yMax/2, 0, "%s", word1.c_str()); 
		attroff(COLOR_PAIR(5));


	map = muv(map, saiz, name, muve1, code, muw);
	if(code){goto startGame;}
	attron(COLOR_PAIR(5)); 
	mvprintw(yMax/2, 0, "%s", word2.c_str());
	attroff(COLOR_PAIR(5));

	map = muv3(map, saiz, name, muve1, code, muw);
	if(code){goto startGame;}
	win=checkVin(map, saiz, area);

	if(win) {
		goto start11;
		}
	
	for(int i=0; i<muw; i++){
	if(muve1){map = bestMuv(map, saiz);}
	else{map =  muv2(map, saiz);}
	}
	lose=checkLose(map, saiz);
	if(lose) {
		
		goto start1;
		}
	}
start11:
	clear();
		int max_y, max_x;
		getmaxyx(stdscr, max_y, max_x);

		const char* message = "WIN";
		int message_len = strlen(message);
		int start_y = max_y / 2;

		int start_x = (max_x - message_len) / 2;
		mvprintw(start_y, start_x, message);

		message = "score ";

		mvprintw(start_y+2, start_x, message);
		mvprintw(start_y+2, start_x+6,"%d", area);
		mvprintw(start_y+3, start_x, "record ");
		mvprintw(start_y+3, start_x+7,"%d",records);

		if(area>config["lewels"][name]["Rec"]) {
			mvprintw(start_y+4, start_x, "new record");
			std::ofstream output_file("records.json");
			config["lewels"][name]["Rec"]=area;
			output_file << config.dump(4);
			output_file.close();
		}
	refresh();

		getch();

	
	goto endGame;


}
	
}

