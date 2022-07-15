typedef struct{//for map Features
	int x;
	int y;
	int fish;
	int way;
}hex;
typedef struct{//for players Features
	int fish;
	int abl;
	int dead;
	int rank;
	int movenum;
}fab;
void fish_cnt_generator(hex map[8][8]){//place fishs in map
	srand(time(0));//this function is used beacuse we want different set of number every time
	int i = 0, x, y, j;
	for(i = 0; i <= 7; i++) {
		for(j = 0; j <= 8; j++) {
			map[i][j].fish = 0;
		}
	}
	i = 0;
	while(i < 10) {
		x = rand() % 8;//generating a rand number for x index of a two d array
		y = rand() % 8;//generating a rand number for y index of a two d array
		if(map[x][y].fish == 0) {
			if(!(x % 2 == 0 && y == 0)) {//even rows has 7 hex instead of 8
				map[x][y].fish = 3;
				i++;
			}
		}
	}
	i = 0;
	while(i < 20) {
		x = rand() % 8;
		y = rand() % 8;
		if(map[x][y].fish == 0) {
			if(!(x % 2 == 0 && y == 0)) {
				map[x][y].fish = 2;
				i++;
			}
		}
	}
	i = 0;
	while(i < 30) {
		x = rand() % 8;
		y = rand() % 8;
		if(map[x][y].fish == 0) {
			if(!(x % 2 == 0 && y == 0)) {
				map[x][y].fish = 1;
				i++;
			}
		}
	}
	map[0][0].fish = -1;
	map[2][0].fish = -1;
	map[4][0].fish = -1;// -1 beacuse the first hex of even rows must be empty
	map[6][0].fish = -1;
}
void coord_generator(hex map[8][8], int width, int height) {//this function especify coord of each hex according to a two d array and the size of pictures of each hex
	int i, j;
	for(i = 0; i <= 7; i++) {
		if(i % 2 == 0) {
			for(j = 1; j <= 7; j++) {
				map[i][j].x = j * (width) - width / 2 + 268;
				map[i][j].y = i * (2.3 / 3) * height + 80;
			}
		} else {
			for(j = 0; j <= 7; j++) {
				map[i][j].x = j * width + 268;
				map[i][j].y = i * (2.3 / 3) * height + 80;
			}
		}
	}
}
int delta(int i,int j,int x2,int y2,hex map[8][8]){//this function is calculating the distance
	int x1=map[i][j].x+44;
	int y1=map[i][j].y+50;
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
int inbound(hex map[8][8],int x,int y){//checks that mouse cursor is inbound of which hex and returns the x and y coord index as a two digits number
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(map[i][j].fish<4&&map[i][j].fish>0){
				if(delta(i,j,x,y,map)<44){
					return 10*(i+1)+j+1;
				}
			}
		}
	}
	return 0;
}
int inbound2(hex map[8][8],int x,int y,int turn){//checks that mouse cursor is inbound of which penguin and returns the x and y coord index as a two digits number
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(map[i][j].fish==turn+6){
				if(delta(i,j,x,y,map)<44){
					return 10*(i+1)+j+1;
				}
			}
		}
	}
	return 0;
}
void pos(hex map[8][8],int i1,int j1){//especify the hexes that selected penguin can go
	int i,j, num = 0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			map[i][j].way=0;
		}
	}
	//right move
	i=i1;j=j1+1;
	while(j<8&&map[i][j].fish>0&&map[i][j].fish<4){
		map[i][j].way=1;
		j++;
		num++;
	}
	//left move
	i=i1;j=j1-1;
	while(j>-1&&map[i][j].fish>0&&map[i][j].fish<4){
		map[i][j].way=1;
		j--;
		num++;
	}
	//right up move
	i=i1-1;j=j1;if(i1%2)j++;
	while(i>-1&&j<8&&map[i][j].fish>0&&map[i][j].fish<4){
		map[i][j].way=1;
		if(i%2)j++;
		i--;
		num++;
		}
	//left up move
	i=i1-1;j=j1-1;if(i1%2)j++;
	while(i>-1&&j>-1&&map[i][j].fish>0&&map[i][j].fish<4){
		map[i][j].way=1;
		if(i%2==0)j--;
		i--;
		num++;
	}
	//right down move
	i=i1+1;j=j1;if(i1%2)j++;
	while(i<8&&j<8&&map[i][j].fish>0&&map[i][j].fish<4){
		map[i][j].way=1;
		if(i%2)j++;
		i++;
		num++;
	}
	//left down move
	i=i1+1;j=j1-1;if(i1%2)j++;
	while(i<8&&j>-1&&map[i][j].fish>0&&map[i][j].fish<4){
		map[i][j].way=1;
		if(i%2==0)j--;
		i++;
		num++;
	}
	if(num == 0) {
		map[i1][j1].way = 2;//for especifying that selecting penguin can not move
	}
}
int ablit(int player_num,int turn,hex map[8][8]){//checks that player is able to move or not
	for(int i = 0; i <= 7; i++) {
		for(int j = 0; j <= 7; j++) {
			if(map[i][j].fish == turn + 6) {
				pos(map, i, j);
				if(map[i][j].way!=2){
					return 1;//returns 1 if player is able to move
				}
			}
		}
	}
	return 0;
}

float delta_animation(int x1,int y1,int x2,int y2){//return distance between two point
	float s=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
	return s;
}