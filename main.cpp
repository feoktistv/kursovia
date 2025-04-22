#include "function.h"

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
	mvprintw(3, 0, "s:spesial");

	refresh();

	std::cin>>mod;
	if(mod=='h') {
		goto hard;
	}
	if(mod=='n') {
		goto normal;
	}
	if(mod=='e') {
		goto easy;
	}
	if(mod=='s') {
		goto spesial;
	}

noecho();

hard:
	map=makemap(N, 3, 3, true);

	printmap(map, N);

	for(;;)
	{

		attron(COLOR_PAIR(5)); 
		mvprintw(N+5, 0, "%s", word1.c_str()); 
		attroff(COLOR_PAIR(5));

		map = muv(map, N);

		attron(COLOR_PAIR(5)); 
		mvprintw(N+5, 0, "%s", word2.c_str());
		attroff(COLOR_PAIR(5));

		map = muv3(map, N);

		win=checkVin(map, N, area);
		if(win==true) {
			records=config["record"]["hardRec"];
			goto start;
		}
		map = bestMuv(map, N);
		
		lose=checkLose(map, N);
		if(lose==true) {
			goto start1;
		}
	}

normal:
	map=makemap(N, 3, 3, false);
	printmap(map, N);

	for(;;)
	{
		attron(COLOR_PAIR(5)); 
		mvprintw(N+5, 0, "%s", word1.c_str()); 
		attroff(COLOR_PAIR(5));

		map = muv(map, N);

		attron(COLOR_PAIR(5)); 
		mvprintw(N+5, 0, "%s", word2.c_str()); 
		attroff(COLOR_PAIR(5));

		map = muv3(map, N);
		win=checkVin(map, N, area);
		if(win==true) {
			records=config["record"]["normalRec"];
			goto start;
		}

		map = bestMuv(map, N);
		lose=checkLose(map, N);
		if(lose==true) {
			goto start1;
		}
	}

easy:
	map=makemap(N, 3, 3, false);

	printmap(map, N);
	for(;;) {

		attron(COLOR_PAIR(5));
		mvprintw(N+5, 0, "%s", word1.c_str()); 
		attroff(COLOR_PAIR(5));

		map = muv(map, N);

		attron(COLOR_PAIR(5)); 
		mvprintw(N+5, 0, "%s", word2.c_str()); 
		attroff(COLOR_PAIR(5));

		map = muv3(map, N);
		win=checkVin(map, N, area);
		if(win==true) {
			records=config["record"]["easyRec"];

			goto start;
		}

		map = muv2(map, N);
		lose=checkLose(map, N);
		if(lose==true) {
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

		if(area>config["record"]["hardRec"] and mod=='h') {
			mvprintw(start_y+4, start_x, "new record");
			std::ofstream output_file("records.json");
			config["record"]["hardRec"]=area;
			output_file << config.dump(4);
			output_file.close();
		}

		if(area>config["record"]["normalRec"] and mod=='n') {
			mvprintw(start_y+4, start_x, "new record");
			std::ofstream output_file("records.json");
			config["record"]["normalRec"]=area;
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

	if(mod=='n') {
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

spesial:
{

	endwin();

	std::cout<<"new or old (n/o)"<<std::endl;
	std::cin>>mod;
	

	std::string name;
	bool wall;
	int saiz, mans, beds, muw;
	 if (mod == 'n') {
        std::cout << "name level: " << std::endl;

        std::cin.ignore(); // �����: ������� ����� ����� ����� �������
        std::getline(std::cin, name); // ���������� getline ��� ������ �����

        std::cout << "saiz of map, number of @ and *: " << std::endl;
        std::cin >> saiz >> mans >> beds;
        std::cout << "how many move for *: " << std::endl;
        std::cin >> muw;
	std::cout << "wall of *(1/0): " << std::endl;

	std::cin >> wall;

        config["lewels"][name]["saiz"] = saiz;
        config["lewels"][name]["@"] = mans;
        config["lewels"][name]["*"] = beds;
        config["lewels"][name]["muve"] = muw;
        config["lewels"][name]["wall"] = wall;
	 
        std::ofstream ofs("records.json"); // ������: ���������� � ����
        ofs << std::setw(4) << config << std::endl; // �������� �����
        ofs.close();

	}
        else if (mod == 'o') {
        std::cout << config["lewels"] << std::endl; // ������� ������ lewels �������

        std::cout << "name level: " << std::endl;
        std::cin.ignore(); // �����: ������� ����� ����� ����� �������
        std::getline(std::cin, name);

        if (config["lewels"].contains(name)) { // �������� ������������� ����� name
            saiz = config["lewels"][name]["saiz"];
            mans = config["lewels"][name]["@"];
            beds = config["lewels"][name]["*"];
            muw = config["lewels"][name]["muve"];
            wall = config["lewels"][name]["wall"].get<bool>(); // ����� ���������� ���� � bool

            std::cout << "lewel fith name: " << name << std::endl;
            std::cout << "  saiz: " << saiz << std::endl;
            std::cout << "  @: " << mans << std::endl;
            std::cout << "  *: " << beds << std::endl;
            std::cout << "  muve: " << muw << std::endl;
            std::cout << "  wall: " << wall << std::endl;
		getch();
        }}
game:
	initscr();
	cbreak();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	map = makemap(saiz,beds ,mans, wall);
	for(;;)
	{attron(COLOR_PAIR(5)); 
	mvprintw(saiz+5, 0, "%s", word1.c_str()); 
	attroff(COLOR_PAIR(5));

	map = muv(map, saiz);

	attron(COLOR_PAIR(5)); 
	mvprintw(saiz+5, 0, "%s", word2.c_str());
	attroff(COLOR_PAIR(5));

	map = muv3(map, saiz);

	win=checkVin(map, saiz, area);
	if(win==true) {
		goto start11;
		}
	for(int i=0; i<muw; i++){
	map = bestMuv(map, saiz);}
	lose=checkLose(map, saiz);
	if(lose==true) {
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

		message = "score";

		mvprintw(start_y+2, start_x, message);
		mvprintw(start_y+2, start_x+5,"%d", area);
		mvprintw(start_y+3, start_x, "record");
		mvprintw(start_y+3, start_x+6,"%d",records);

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

