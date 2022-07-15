/*group members:
Amirhossein Akhundzadeh - 4001262148
Hamidreza Ramezani - 4001262568
*/
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_ttf.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include "object.h"
int main() 
{
	int yn = 1;
	do{
		int i, j;//for columns and raws
		int posm_x = 0, posm_y = 0, mouse_mood = 1;//mouse positions
		int dead_cnt = 0;
		hex map[8][8];//base map
		fish_cnt_generator(map);//random fish
		int player_num;
		int width = 1240;//width of display
		int height = 800;//height of display
		int imageWidth = 0;
		int imageHeight = 0;
		float speed=20;
		fab player[4];//move abilities and number of fishs
		for(int lp=0;lp<4;lp++){
			player[lp].fish=0;//each player fish number
			player[lp].dead=0;
			player[lp].movenum=0;
			player[lp].rank=lp+1;
		}
		bool done = false;
	    //init
		al_init();
	    al_init_image_addon();//init fase
	    al_init_primitives_addon();
	    al_install_keyboard();
	    al_install_mouse();
	    al_init_font_addon();
	    al_init_ttf_addon();
	    ALLEGRO_KEYBOARD_STATE kbdstate;
		ALLEGRO_DISPLAY *display = al_create_display(width, height);
	    ALLEGRO_EVENT_QUEUE *event = al_create_event_queue();//main event
	    ALLEGRO_BITMAP *image0 = al_load_bitmap("fish0.png");
	    ALLEGRO_BITMAP *image1 = al_load_bitmap("fish1.png");
	    ALLEGRO_BITMAP *image2 = al_load_bitmap("fish2.png");//creating pictures for each possible number of fish
	    ALLEGRO_BITMAP *image3 = al_load_bitmap("fish3.png");
	    ALLEGRO_BITMAP *background4 = al_load_bitmap("background4.png");
	    ALLEGRO_BITMAP *background2 = al_load_bitmap("background2.png");//background with scoreboard for each number of players
	    ALLEGRO_BITMAP *background3 = al_load_bitmap("background3.png");
	    ALLEGRO_BITMAP *score_board4 = al_load_bitmap("scoreboard4.png");
	    ALLEGRO_BITMAP *score_board3 = al_load_bitmap("scoreboard3.png");//scoreboard only for each number of players
	    ALLEGRO_BITMAP *score_board2 = al_load_bitmap("scoreboard2.png");
	    ALLEGRO_BITMAP *introp = al_load_bitmap("intro.png");//intro background
	    ALLEGRO_BITMAP *Pnum = al_load_bitmap("Pnum.png");//player selection fase background
	    ALLEGRO_BITMAP *yellow_hex = al_load_bitmap("yellowhex.png");
	    ALLEGRO_BITMAP *yellow_squar = al_load_bitmap("yellowsquar.png");
	    ALLEGRO_BITMAP *red_hex = al_load_bitmap("redhex.png");//red hex whith 45% opacity for showing that penging is unable to move
	    ALLEGRO_BITMAP *cursor = al_load_bitmap("cursor.png");
	    ALLEGRO_BITMAP *cursor2 = al_load_bitmap("cursor2.png");
	    ALLEGRO_BITMAP *pangb = al_load_bitmap("blue.png");
	    ALLEGRO_BITMAP *pangp = al_load_bitmap("pink.png");//penguin's pictures
	    ALLEGRO_BITMAP *pangr = al_load_bitmap("red.png");
	    ALLEGRO_BITMAP *pangg = al_load_bitmap("green.png");
	    ALLEGRO_FONT *font0 = al_load_font("number.ttf",36,0);
	    ALLEGRO_BITMAP *turnR4 = al_load_bitmap("turnR4.png");
	    ALLEGRO_BITMAP *turnB4 = al_load_bitmap("turnB4.png");
	    ALLEGRO_BITMAP *turnP4 = al_load_bitmap("turnP4.png");
	    ALLEGRO_BITMAP *turnG4 = al_load_bitmap("turnG4.png");
	    ALLEGRO_BITMAP *turnR3 = al_load_bitmap("turnR3.png");//turn compass
	    ALLEGRO_BITMAP *turnB3 = al_load_bitmap("turnB3.png");
	    ALLEGRO_BITMAP *turnP3 = al_load_bitmap("turnP3.png");
	    ALLEGRO_BITMAP *turnR2 = al_load_bitmap("turnR2.png");
	    ALLEGRO_BITMAP *turnB2 = al_load_bitmap("turnB2.png");
	    ALLEGRO_BITMAP *leader_board = al_load_bitmap("leaderboard.png");//
	    ALLEGRO_BITMAP *s_yellow_squar = al_load_bitmap("syellowsquar.png");
	    ALLEGRO_BITMAP *guide_squar = al_load_bitmap("guidesquar.png");//picture for hidding guide
	    ALLEGRO_BITMAP *guide_squar2 = al_load_bitmap("guidesquar2.png");//shows guide
	    ALLEGRO_BITMAP *yellow_guide_squar = al_load_bitmap("yellowguidesquar.png");//to show that mouse isinbound of guide icone
	    ALLEGRO_BITMAP *guide = al_load_bitmap("guide.png");//guide page
		imageWidth = al_get_bitmap_width(image0);
	    imageHeight = al_get_bitmap_height(image0);
	    coord_generator(map, imageWidth, imageHeight);
	    al_register_event_source(event, al_get_keyboard_event_source());
	    al_register_event_source(event, al_get_display_event_source(display));//registring sources if events
	    al_register_event_source(event, al_get_mouse_event_source());
	    al_hide_mouse_cursor(display);
	    //intro of the game fase
	    done = false;
		while(!done) {
	    	al_draw_bitmap(introp, 0, 0, 0);
	    	al_flip_display();
	    	ALLEGRO_EVENT ev;
	    	al_wait_for_event(event, &ev);
	    	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
	    		return 0;
	    	} else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
	    		done = true; //passing intro after player pressed a key
			}
		}
	    done = false;
	    //player number selection fase 
		while(!done) {
	    	al_clear_to_color(al_map_rgb(0, 0, 0));
	    	al_draw_bitmap(Pnum, 0, 0, 0);
	    	ALLEGRO_EVENT ev;
	    	al_wait_for_event(event, &ev);
	    	//draw the mouse cursor according to its mood
			if(al_is_event_queue_empty(event)) {
				//drawing the mouse cursor according to its mood
				if(mouse_mood == 1) {
					al_draw_bitmap(cursor, posm_x, posm_y, 0);
				} else {
					al_draw_bitmap(cursor2, posm_x, posm_y, 0);
				}
			}
			//updating the mouse position
	    	if(ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
				posm_x = ev.mouse.x;
				posm_y = ev.mouse.y;
			}
	    	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				return 0;
	    		//exits the game if player press display_close icon
			}
			//inbound of 2
			if(posm_x >= 274 && posm_x <= 489 && posm_y >= 171 && posm_y <= 475) {
				mouse_mood = 2;
				al_draw_bitmap(yellow_squar, 274, 171, 0);//draw a square with 45% opacity to show that mouse is inbound of that number
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if(ev.mouse.button & 1) {
						player_num = 2;
						done = true;
					}
				}
			//inbound of 3
			} else if(posm_x >= 514 && posm_x <= 729 && posm_y >= 171 && posm_y <= 475) {
				mouse_mood = 2;
				al_draw_bitmap(yellow_squar, 514, 171, 0);
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if(ev.mouse.button & 1) {
						player_num = 3;
						done = true;
					}
				}
			//inbound of 4
			} else if(posm_x >= 754 && posm_x <= 969 && posm_y >= 171 && posm_y <= 475) {
				mouse_mood = 2;
				al_draw_bitmap(yellow_squar, 754, 171, 0);
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if(ev.mouse.button & 1) {
						player_num = 4;
						done = true;
					}
				}
			} else {
				mouse_mood = 1;
			}
			al_flip_display();
		}
	    done = false;
	    //show map
	    //drawing background according to the number of players
		al_clear_to_color(al_map_rgb(0, 0, 0));
		if(player_num == 2) {
			al_draw_bitmap(background2, 0, 0, 0);
		} else if(player_num == 3) {
			al_draw_bitmap(background3, 0, 0, 0);
		} else {
			al_draw_bitmap(background4, 0, 0, 0);
		}
		for(i = 0; i <= 7; i++) {
			for(j = 0; j <= 7; j++) {
				if(map[i][j].fish == 1) {
					al_draw_bitmap(image1, map[i][j].x, map[i][j].y, 0);
				} else if(map[i][j].fish == 2) {
						al_draw_bitmap(image2, map[i][j].x, map[i][j].y, 0); // drawing hexes in map
				} else if(map[i][j].fish == 3) {
					al_draw_bitmap(image3, map[i][j].x, map[i][j].y, 0);
				} else if(map[i][j].fish == 0) {
					al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
				}else {
					continue;
				}
			}
		}
		al_flip_display();
		//select penguine
		int pangnum = 6 - player_num;
		for(int pangturn=0;pangturn<pangnum;pangturn++){
			for(int turn=0;turn<player_num;turn++){
				al_draw_bitmap(guide_squar, 1240 - al_get_bitmap_width(guide_squar), 800 - al_get_bitmap_height(guide_squar), 0);
				if(turn == 0) {
					//drawing turn compass
					if(player_num == 4) {
						al_draw_bitmap(turnR4, 1000, 50, 0);
					} else if(player_num == 3) {
						al_draw_bitmap(turnR3, 1000, 50, 0);
					} else {
						al_draw_bitmap(turnR2, 1000, 50, 0);
						}
					} else if(turn == 1) {
						if(player_num == 4) {
							al_draw_bitmap(turnB4, 1000, 50, 0);
						} else if(player_num == 3) {
							al_draw_bitmap(turnB3, 1000, 50, 0);
						} else {
								al_draw_bitmap(turnB2, 1000, 50, 0);
						}
					} else if(turn == 2) {
						if(player_num == 4) {
							al_draw_bitmap(turnP4, 1000, 50, 0);
						} else {
							al_draw_bitmap(turnP3, 1000, 50, 0);
						}
					} else {
						al_draw_bitmap(turnG4, 1000, 50, 0);
					}
				al_flip_display();
				int done1 = 1;
				while(done1){
					//hidding the guide
					al_draw_bitmap(guide_squar, 1240 - al_get_bitmap_width(guide_squar), 800 - al_get_bitmap_height(guide_squar), 0);				
					ALLEGRO_EVENT ev;
		 	 	 	al_wait_for_event(event, &ev);
		 	 	 	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
	    				return 0;
					}
					if(ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
						posm_x = ev.mouse.x;
						posm_y = ev.mouse.y;
						al_clear_to_color(al_map_rgb(0, 0, 0));
						//drawing background
						if(player_num == 2) {
							al_draw_bitmap(background2, 0, 0, 0);
						} else if(player_num == 3) {
							al_draw_bitmap(background3, 0, 0, 0);
						} else {
							al_draw_bitmap(background4, 0, 0, 0);
						}
						for(i = 0; i <= 7; i++) {
							for(j = 0; j <= 7; j++) {
								if(map[i][j].fish == 1) {
									al_draw_bitmap(image1, map[i][j].x, map[i][j].y, 0);
								} else if(map[i][j].fish == 2) {
									al_draw_bitmap(image2, map[i][j].x, map[i][j].y, 0); // drawing hexes in map
								} else if(map[i][j].fish == 3) {
									al_draw_bitmap(image3, map[i][j].x, map[i][j].y, 0);
								} else if(map[i][j].fish == 0) {
									al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
								}  else if(map[i][j].fish == 6) {
									al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
									al_draw_bitmap(pangr, map[i][j].x+11, map[i][j].y+7, 0);
								}  else if(map[i][j].fish == 7) {
									al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
									al_draw_bitmap(pangb, map[i][j].x+10, map[i][j].y+11, 0);
								}  else if(map[i][j].fish == 8) {
									al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
									al_draw_bitmap(pangp, map[i][j].x+15, map[i][j].y+7, 0);
								}  else if(map[i][j].fish == 9) {
									al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
									al_draw_bitmap(pangg, map[i][j].x+15, map[i][j].y+9, 0);
								}else {
									continue;
								}
							}
						}
						//drawing scores
						if(player_num==2){
							al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
							al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
						}else if(player_num==3){
							al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
							al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
							al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
						}else if(player_num==4){
							al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
							al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
							al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 650, ALLEGRO_ALIGN_CENTER, "%i",player[3].fish);
							al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
						}
						if(turn == 0) {
						//drawing turn compass
							if(player_num == 4) {
								al_draw_bitmap(turnR4, 1000, 50, 0);
							} else if(player_num == 3) {
								al_draw_bitmap(turnR3, 1000, 50, 0);
							} else {
								al_draw_bitmap(turnR2, 1000, 50, 0);
							}
						} else if(turn == 1) {
							if(player_num == 4) {
								al_draw_bitmap(turnB4, 1000, 50, 0);
							} else if(player_num == 3) {
								al_draw_bitmap(turnB3, 1000, 50, 0);
							} else {
								al_draw_bitmap(turnB2, 1000, 50, 0);
							}
						} else if(turn == 2) {
							if(player_num == 4) {
								al_draw_bitmap(turnP4, 1000, 50, 0);
							} else {
								al_draw_bitmap(turnP3, 1000, 50, 0);
							}
						} else {
							al_draw_bitmap(turnG4, 1000, 50, 0);
						}
						al_draw_bitmap(cursor2, posm_x, posm_y, 0);
						al_draw_bitmap(guide_squar, 1240 - al_get_bitmap_width(guide_squar), 800 - al_get_bitmap_height(guide_squar), 0);
						if(inbound(map,posm_x,posm_y)){
							int plac=inbound(map,posm_x,posm_y);
							al_draw_bitmap(yellow_hex, map[plac/10-1][plac%10-1].x, map[plac/10-1][plac%10-1].y, 0);
						}
						al_flip_display();	
					}
					if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
						if(inbound(map,posm_x,posm_y)){//this function show that the mouse is inbound of which hex
							int ppan=inbound(map,posm_x,posm_y);//ppan keeps panguin's x and y coord in a two digits number
							int xpan=ppan/10-1;//x coord
							int ypan=ppan%10-1;//y coord
//							place[turn][pangturn].x=xpan;
//							place[turn][pangturn].y=ypan;
							//drawing the turn compass
							if(turn==0){
								al_draw_bitmap(image0, map[xpan][ypan].x, map[xpan][ypan].y, 0);
								al_draw_bitmap(pangr, map[xpan][ypan].x+11, map[xpan][ypan].y+7, 0);
								done1--;
								player[0].fish+=map[xpan][ypan].fish;
								map[xpan][ypan].fish=6;
							}else if(turn==1){
								al_draw_bitmap(image0, map[xpan][ypan].x, map[xpan][ypan].y, 0);
								al_draw_bitmap(pangb, map[xpan][ypan].x+10, map[xpan][ypan].y+11, 0);
								done1--;
								player[1].fish+=map[xpan][ypan].fish;
								map[xpan][ypan].fish=7;
							}else if(turn==2){
								al_draw_bitmap(image0, map[xpan][ypan].x, map[xpan][ypan].y, 0);
								al_draw_bitmap(pangp, map[xpan][ypan].x+15, map[xpan][ypan].y+7, 0);
								done1--;
								player[2].fish+=map[xpan][ypan].fish;
								map[xpan][ypan].fish=8;
							}else if(turn==3){
								al_draw_bitmap(image0, map[xpan][ypan].x, map[xpan][ypan].y, 0);
								al_draw_bitmap(pangg, map[xpan][ypan].x+15, map[xpan][ypan].y+9, 0);
								done1--;
								player[3].fish+=map[xpan][ypan].fish;
								map[xpan][ypan].fish=9;
								}
							al_draw_bitmap(cursor2, posm_x, posm_y, 0);
							al_flip_display();
						}
					}
					//drawing score board instead of the whole map
					if(player_num == 2) {
						al_draw_bitmap(score_board2, 0, 0, 0);
					} else if(player_num == 3) {
						al_draw_bitmap(score_board3, 0, 0, 0);
					} else {
						al_draw_bitmap(score_board4, 0, 0, 0);
					}
					//drawing the score of each player
					if(player_num==2){
						al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
						al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
					}else if(player_num==3){
						al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
						al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
						al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
					}else if(player_num==4){
						al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
						al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
						al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 650, ALLEGRO_ALIGN_CENTER, "%i",player[3].fish);
						al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
					}
					al_flip_display();
				}
			}
		}
		al_show_mouse_cursor(display);
		//show map
		al_clear_to_color(al_map_rgb(0, 0, 0));
		//drawing the background
		if(player_num == 2) {
			al_draw_bitmap(background2, 0, 0, 0);
		} else if(player_num == 3) {
			al_draw_bitmap(background3, 0, 0, 0);
		} else {
			al_draw_bitmap(background4, 0, 0, 0);
		}
		for(i = 0; i <= 7; i++) {
			for(j = 0; j <= 7; j++) {
				if(map[i][j].fish == 1) {
					al_draw_bitmap(image1, map[i][j].x, map[i][j].y, 0);
				} else if(map[i][j].fish == 2) {
					al_draw_bitmap(image2, map[i][j].x, map[i][j].y, 0); // drawing hexes in map
				} else if(map[i][j].fish == 3) {
					al_draw_bitmap(image3, map[i][j].x, map[i][j].y, 0);
				} else if(map[i][j].fish == 0) {
					al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
				}  else if(map[i][j].fish == 6) {
					al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
					al_draw_bitmap(pangr, map[i][j].x+11, map[i][j].y+7, 0);
				}  else if(map[i][j].fish == 7) {
					al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
					al_draw_bitmap(pangb, map[i][j].x+10, map[i][j].y+11, 0);
				}  else if(map[i][j].fish == 8) {
					al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
					al_draw_bitmap(pangp, map[i][j].x+15, map[i][j].y+7, 0);
				}  else if(map[i][j].fish == 9) {
					al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
					al_draw_bitmap(pangg, map[i][j].x+15, map[i][j].y+9, 0);
				}else {
					continue;
				}
			}
		}
		//drawing scores
		if(player_num==2){
			al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
			al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
		}else if(player_num==3){
			al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
			al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
			al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
		}else if(player_num==4){
			al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
			al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
			al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 650, ALLEGRO_ALIGN_CENTER, "%i",player[3].fish);
			al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
		}
		al_flip_display();	
		//moves
		int k=1;
		do{
			if(dead_cnt == (player_num * (6 - player_num))) {
				break;
				//ends the game if all players are unable to move
			}
			for(int turn=0;turn<player_num;turn++){
				if(player[turn].dead == 1)continue;
				if(!ablit(player_num,turn,map)){//shows that the player is able to move or not
					if(player[turn].dead != 1) {
						dead_cnt+= 6 - player_num;//if player is unable to move al of his/her penguin are considered as dead
						player[turn].dead = 1;//this is beacuse we want to count the player's penguins' dead number once
					}
					continue;
				}
				if(dead_cnt == (player_num * (6 - player_num))) {
					break;
				}
				int move2=1,move1=1;
				int xpan,ypan,ppan;
				while(move1||move2){
					if(dead_cnt == (player_num * (6 - player_num))) break;
					move2=1;move1=1;
					while(move1){
						//drawing turn compass
						if(turn == 0) {
							if(player_num == 4) {
								al_draw_bitmap(turnR4, 1000, 50, 0);
							} else if(player_num == 3) {
								al_draw_bitmap(turnR3, 1000, 50, 0);
							} else {
								al_draw_bitmap(turnR2, 1000, 50, 0);
							}
						} else if(turn == 1) {
							if(player_num == 4) {
								al_draw_bitmap(turnB4, 1000, 50, 0);
							} else if(player_num == 3) {
								al_draw_bitmap(turnB3, 1000, 50, 0);
							} else {
								al_draw_bitmap(turnB2, 1000, 50, 0);
							}
						} else if(turn == 2) {
							if(player_num == 4) {
								al_draw_bitmap(turnP4, 1000, 50, 0);
							} else {
								al_draw_bitmap(turnP3, 1000, 50, 0);
							}
						} else {
							al_draw_bitmap(turnG4, 1000, 50, 0);
						}
						al_flip_display();
						ALLEGRO_EVENT ev;
						al_wait_for_event(event, &ev);
						if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
	    					return 0;
						}
						if(ev.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP){	
							posm_x = ev.mouse.x;
							posm_y = ev.mouse.y;
							if(inbound2(map,posm_x,posm_y,turn)){
								i=inbound2(map,posm_x,posm_y,turn)/10-1;
								j=inbound2(map,posm_x,posm_y,turn)%10-1;
								pos(map,i,j);
								if(map[i][j].way!=2){
									if(map[i][j].fish == 6) {
										al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
										al_draw_bitmap(pangr, map[i][j].x+11, map[i][j].y+7, 0);
									}  else if(map[i][j].fish == 7) {
										al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
										al_draw_bitmap(pangb, map[i][j].x+10, map[i][j].y+11, 0);
									}  else if(map[i][j].fish == 8) {
										al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
										al_draw_bitmap(pangp, map[i][j].x+15, map[i][j].y+7, 0);
									}  else if(map[i][j].fish == 9) {
										al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
										al_draw_bitmap(pangg, map[i][j].x+15, map[i][j].y+9, 0);
									}
									al_draw_bitmap(yellow_hex, map[i][j].x, map[i][j].y, 0);
									al_flip_display();
								}else {
									if(map[i][j].fish == 6) {
										al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
										al_draw_bitmap(pangr, map[i][j].x+11, map[i][j].y+7, 0);
									}  else if(map[i][j].fish == 7) {
										al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
										al_draw_bitmap(pangb, map[i][j].x+10, map[i][j].y+11, 0);
									}  else if(map[i][j].fish == 8) {
										al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
										al_draw_bitmap(pangp, map[i][j].x+15, map[i][j].y+7, 0);
									}  else if(map[i][j].fish == 9) {
										al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
										al_draw_bitmap(pangg, map[i][j].x+15, map[i][j].y+9, 0);
									}
									al_draw_bitmap(red_hex, map[i][j].x, map[i][j].y, 0);
									al_flip_display();
								}
							}else{
								if(map[i][j].fish == 6) {
									al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
									al_draw_bitmap(pangr, map[i][j].x+11, map[i][j].y+7, 0);
								}  else if(map[i][j].fish == 7) {
									al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
									al_draw_bitmap(pangb, map[i][j].x+10, map[i][j].y+11, 0);
								}  else if(map[i][j].fish == 8) {
									al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
									al_draw_bitmap(pangp, map[i][j].x+15, map[i][j].y+7, 0);
								}  else if(map[i][j].fish == 9) {
									al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
									al_draw_bitmap(pangg, map[i][j].x+15, map[i][j].y+9, 0);
								}
								al_flip_display();
							}
						}
						//draw the yellow guide squar if mouse cursor is inbound with it and simple guide square if it is not
						if(posm_x >= 1055 && posm_x <= 1230 && posm_y >= 675 && posm_y <= 780) {
	          				al_draw_bitmap(yellow_guide_squar, 1240 - al_get_bitmap_width(yellow_guide_squar), 800 - al_get_bitmap_height(yellow_guide_squar), 0);
	       				} else{
	       					al_draw_bitmap(guide_squar2, 1240 - al_get_bitmap_width(guide_squar2), 800 - al_get_bitmap_height(guide_squar2), 0);
						}
						if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
							if(posm_x >= 1055 && posm_x <= 1230 && posm_y >= 675 && posm_y <= 780) {
								if(ev.mouse.button && 1) {
									while(1) {
										//show guid
										al_draw_bitmap(guide ,0, 0, 0);
										if(posm_x >= 1055 && posm_x <= 1230 && posm_y >= 675 && posm_y <= 780) {
											al_draw_bitmap(s_yellow_squar, 1055, 675, 0);
										}
										al_flip_display();
										al_wait_for_event(event, &ev);
										if(ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
											posm_x = ev.mouse.x;
											posm_y = ev.mouse.y;
										}
										if(posm_x >= 1055 && posm_x <= 1230 && posm_y >= 675 && posm_y <= 780) {
											al_draw_bitmap(s_yellow_squar, 1055, 675, 0);
											al_flip_display();
										}
										if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
											return 0;
										}
										if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
											if(ev.mouse.button && 1) {
												if(posm_x >= 1055 && posm_x <= 1230 && posm_y >= 675 && posm_y <= 780) {
													break;
													//exits the guide if player press close icon
												}
											}
										}
									}
									//drawing the background
									if(player_num == 2) {
										al_draw_bitmap(background2, 0, 0, 0);
									}else if(player_num == 3) {
										al_draw_bitmap(background3, 0, 0, 0);
									} else {
										al_draw_bitmap(background4, 0, 0, 0);
									}
									//drawing turn compass
									if(turn == 0) {
										if(player_num == 4) {
											al_draw_bitmap(turnR4, 1000, 50, 0);
										} else if(player_num == 3) {
											al_draw_bitmap(turnR3, 1000, 50, 0);
										} else {
											al_draw_bitmap(turnR2, 1000, 50, 0);
										}
									} else if(turn == 1) {
										if(player_num == 4) {
											al_draw_bitmap(turnB4, 1000, 50, 0);
										} else if(player_num == 3) {
											al_draw_bitmap(turnB3, 1000, 50, 0);
										} else {
											al_draw_bitmap(turnB2, 1000, 50, 0);
										}
									} else if(turn == 2) {
										if(player_num == 4) {
											al_draw_bitmap(turnP4, 1000, 50, 0);
										} else {
											al_draw_bitmap(turnP3, 1000, 50, 0);
										}
									} else {
										al_draw_bitmap(turnG4, 1000, 50, 0);
									}
									for(i = 0; i <= 7; i++) {
										for(j = 0; j <= 7; j++) {
											if(map[i][j].fish == 1) {
												al_draw_bitmap(image1, map[i][j].x, map[i][j].y, 0);
											} else if(map[i][j].fish == 2) {
												al_draw_bitmap(image2, map[i][j].x, map[i][j].y, 0); // drawing hexes in map
											} else if(map[i][j].fish == 3) {
												al_draw_bitmap(image3, map[i][j].x, map[i][j].y, 0);
											} else if(map[i][j].fish == 0) {
												al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											}  else if(map[i][j].fish == 6) {
												al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
												al_draw_bitmap(pangr, map[i][j].x+11, map[i][j].y+7, 0);
											}  else if(map[i][j].fish == 7) {
												al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
												al_draw_bitmap(pangb, map[i][j].x+10, map[i][j].y+11, 0);
											}  else if(map[i][j].fish == 8) {
												al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
												al_draw_bitmap(pangp, map[i][j].x+15, map[i][j].y+7, 0);
											}  else if(map[i][j].fish == 9) {
												al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
												al_draw_bitmap(pangg, map[i][j].x+15, map[i][j].y+9, 0);
											}else {
												continue;
											}
										}
									}
									//drawing scores
									if(player_num==2){
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
									}else if(player_num==3){
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
									}else if(player_num==4){
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 650, ALLEGRO_ALIGN_CENTER, "%i",player[3].fish);
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
									}
									if(posm_x >= 1055 && posm_x <= 1230 && posm_y >= 675 && posm_y <= 780) {
				          				al_draw_bitmap(yellow_guide_squar, 1240 - al_get_bitmap_width(yellow_guide_squar), 800 - al_get_bitmap_height(yellow_guide_squar), 0);
				       				} else{
				       					al_draw_bitmap(guide_squar2, 1240 - al_get_bitmap_width(guide_squar2), 800 - al_get_bitmap_height(guide_squar2), 0);
									}
									al_flip_display();
								}
							}else if(inbound2(map,posm_x,posm_y,turn)){
								move1--;
								ppan=inbound2(map,posm_x,posm_y,turn);
								xpan=ppan/10-1;
								ypan=(ppan%10)-1;
								pos(map,xpan,ypan);
								//show					
								for(i = 0; i <= 7; i++) {
									for(j = 0; j <= 7; j++) {
										if(map[i][j].fish == 1) {
											al_draw_bitmap(image1, map[i][j].x, map[i][j].y, 0);
										} else if(map[i][j].fish == 2) {
											al_draw_bitmap(image2, map[i][j].x, map[i][j].y, 0); // drawing hexes in map
										} else if(map[i][j].fish == 3) {
											al_draw_bitmap(image3, map[i][j].x, map[i][j].y, 0);
										} else if(map[i][j].fish == 0) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
										}  else if(map[i][j].fish == 6) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangr, map[i][j].x+11, map[i][j].y+7, 0);
										}  else if(map[i][j].fish == 7) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangb, map[i][j].x+10, map[i][j].y+11, 0);
										}  else if(map[i][j].fish == 8) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangp, map[i][j].x+15, map[i][j].y+7, 0);
										}  else if(map[i][j].fish == 9) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangg, map[i][j].x+15, map[i][j].y+9, 0);
										}else {
											continue;
										}
										if(map[i][j].way == 1)
											al_draw_bitmap(yellow_hex, map[i][j].x, map[i][j].y, 0);
										if(map[i][j].way == 2) {
											al_draw_bitmap(red_hex, map[i][j].x, map[i][j].y, 0);
										}
									}
								}
								al_flip_display();
							}
						}
					}
					while(move2){
						ALLEGRO_EVENT ev;
						al_wait_for_event(event, &ev);
						if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
	    					return 0;
						}		
						if(ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
							posm_x = ev.mouse.x;
							posm_y = ev.mouse.y;
						}
						//draw the yellow guide squar if mouse cursor is inbound with it and simple guide square if it is not
						if(posm_x >= 1055 && posm_x <= 1230 && posm_y >= 675 && posm_y <= 780) {
	          				al_draw_bitmap(yellow_guide_squar, 1240 - al_get_bitmap_width(yellow_guide_squar), 800 - al_get_bitmap_height(yellow_guide_squar), 0);
	       				} else{
	       					al_draw_bitmap(guide_squar2, 1240 - al_get_bitmap_width(guide_squar2), 800 - al_get_bitmap_height(guide_squar2), 0);
						}
						al_flip_display();
						if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
							if(posm_x >= 1055 && posm_x <= 1230 && posm_y >= 675 && posm_y <= 780) {
								if(ev.mouse.button && 1) {
									float posm1_x=posm_x,posm1_y=posm_y;
									while(1) {
										//drawing the guide page
										al_draw_bitmap(guide ,0, 0, 0);
										if(posm1_x >= 1055 && posm1_x <= 1230 && posm1_y >= 675 && posm1_y <= 780) {
											al_draw_bitmap(s_yellow_squar, 1055, 675, 0);
										}
										al_flip_display();
										al_wait_for_event(event, &ev);
										if(ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
											posm1_x = ev.mouse.x;
											posm1_y = ev.mouse.y;
										}
										if(posm1_x >= 1055 && posm1_x <= 1230 && posm1_y >= 675 && posm1_y <= 780) {
											al_draw_bitmap(s_yellow_squar, 1055, 675, 0);
											al_flip_display();
										}
										if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
											return 0;
										}
										if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
											if(ev.mouse.button && 1) {
												if(posm1_x >= 1055 && posm1_x <= 1230 && posm1_y >= 675 && posm1_y <= 780) {
													break;
												}
											}
										}
									}
								}
								//drawing guide compass
								if(player_num == 2) {
									al_draw_bitmap(background2, 0, 0, 0);
								}else if(player_num == 3) {
									al_draw_bitmap(background3, 0, 0, 0);
								} else {
									al_draw_bitmap(background4, 0, 0, 0);
								}
								if(turn == 0) {
									if(player_num == 4) {
										al_draw_bitmap(turnR4, 1000, 50, 0);
									} else if(player_num == 3) {
										al_draw_bitmap(turnR3, 1000, 50, 0);
									} else {
										al_draw_bitmap(turnR2, 1000, 50, 0);
									}
								} else if(turn == 1) {
									if(player_num == 4) {
										al_draw_bitmap(turnB4, 1000, 50, 0);
									} else if(player_num == 3) {
										al_draw_bitmap(turnB3, 1000, 50, 0);
									} else {
										al_draw_bitmap(turnB2, 1000, 50, 0);
									}
								} else if(turn == 2) {
									if(player_num == 4) {
										al_draw_bitmap(turnP4, 1000, 50, 0);
									} else {
										al_draw_bitmap(turnP3, 1000, 50, 0);
									}
								} else {
									al_draw_bitmap(turnG4, 1000, 50, 0);
								}
								for(i = 0; i <= 7; i++) {
									for(j = 0; j <= 7; j++) {
										if(map[i][j].fish == 1) {
											al_draw_bitmap(image1, map[i][j].x, map[i][j].y, 0);
										} else if(map[i][j].fish == 2) {
											al_draw_bitmap(image2, map[i][j].x, map[i][j].y, 0); // drawing hexes in map
										} else if(map[i][j].fish == 3) {
											al_draw_bitmap(image3, map[i][j].x, map[i][j].y, 0);
										} else if(map[i][j].fish == 0) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
										}  else if(map[i][j].fish == 6) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangr, map[i][j].x+11, map[i][j].y+7, 0);
										}  else if(map[i][j].fish == 7) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangb, map[i][j].x+10, map[i][j].y+11, 0);
										}  else if(map[i][j].fish == 8) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangp, map[i][j].x+15, map[i][j].y+7, 0);
										}  else if(map[i][j].fish == 9) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangg, map[i][j].x+15, map[i][j].y+9, 0);
										}else {
											continue;
										}
										if(map[i][j].way==1){
											al_draw_bitmap(yellow_hex, map[i][j].x, map[i][j].y, 0);
										}
										if(map[i][j].way == 2) {
											al_draw_bitmap(red_hex, map[i][j].x, map[i][j].y, 0);
										}
									}
								}
								//drawing scores
								if(player_num==2){
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
								}else if(player_num==3){
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
								}else if(player_num==4){
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 650, ALLEGRO_ALIGN_CENTER, "%i",player[3].fish);
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
								}
								al_flip_display();
							}
							else if((inbound(map,posm_x,posm_y)&&!map[inbound(map,posm_x,posm_y)/10-1][inbound(map,posm_x,posm_y)%10-1].way)||!inbound(map,posm_x,posm_y)){//checks that the player is able to go to hex that he/she clicked on
								for(i = 0; i <= 7; i++) {
									for(j = 0; j <= 7; j++) {
										if(map[i][j].fish == 1) {
											al_draw_bitmap(image1, map[i][j].x, map[i][j].y, 0);
										} else if(map[i][j].fish == 2) {
											al_draw_bitmap(image2, map[i][j].x, map[i][j].y, 0); // drawing hexes in map
										} else if(map[i][j].fish == 3) {
											al_draw_bitmap(image3, map[i][j].x, map[i][j].y, 0);
										} else if(map[i][j].fish == 0) {
												al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
										}  else if(map[i][j].fish == 6) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangr, map[i][j].x+11, map[i][j].y+7, 0);
										}  else if(map[i][j].fish == 7) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangb, map[i][j].x+10, map[i][j].y+11, 0);
										}  else if(map[i][j].fish == 8) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangp, map[i][j].x+15, map[i][j].y+7, 0);
										}  else if(map[i][j].fish == 9) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangg, map[i][j].x+15, map[i][j].y+9, 0);
										}else {
											continue;
										}
									}
								}
								////draw the yellow guide squar if mouse cursor is inbound with it and simple guide square if it is not
								if(posm_x >= 1055 && posm_x <= 1230 && posm_y >= 675 && posm_y <= 780) {
									al_draw_bitmap(yellow_guide_squar, 1240 - al_get_bitmap_width(yellow_guide_squar), 800 - al_get_bitmap_height(yellow_guide_squar), 0);
								} else{
				    				al_draw_bitmap(guide_squar2, 1240 - al_get_bitmap_width(guide_squar2), 800 - al_get_bitmap_height(guide_squar2), 0);
								}
								al_flip_display();
								break;
							}
							else if(inbound(map,posm_x,posm_y)&&map[inbound(map,posm_x,posm_y)/10-1][inbound(map,posm_x,posm_y)%10-1].way&&!move1){
								player[turn].movenum++;
								move2--;
								int ilast=inbound(map,posm_x,posm_y)/10-1;
								int jlast=inbound(map,posm_x,posm_y)%10-1;
								player[turn].fish+=map[ilast][jlast].fish;
								float frame=delta_animation(map[xpan][ypan].x,map[xpan][ypan].y,map[ilast][jlast].x,map[ilast][jlast].y);
								frame/=speed;
								float delta_y=map[ilast][jlast].y-map[xpan][ypan].y;
								float delta_x=map[ilast][jlast].x-map[xpan][ypan].x;
								delta_y/=frame;
								delta_x/=frame;
								int showpang=1;
								while(showpang<=frame){
									al_rest(0.1);
									al_clear_to_color(al_map_rgb(0, 0, 0));
									//drawing background
									if(player_num == 2) {
										al_draw_bitmap(background2, 0, 0, 0);
									} else if(player_num == 3) {
										al_draw_bitmap(background3, 0, 0, 0);
									} else {
										al_draw_bitmap(background4, 0, 0, 0);
									}
									for(i = 0; i <= 7; i++) {
										for(j = 0; j <= 7; j++) {
											if(i==xpan&&j==ypan){
												al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											} else if(map[i][j].fish == 1) {
												al_draw_bitmap(image1, map[i][j].x, map[i][j].y, 0);
											} else if(map[i][j].fish == 2) {
												al_draw_bitmap(image2, map[i][j].x, map[i][j].y, 0); // drawing hexes in map
											} else if(map[i][j].fish == 3) {
												al_draw_bitmap(image3, map[i][j].x, map[i][j].y, 0);
											} else if(map[i][j].fish == 0) {
												al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											}  else if(map[i][j].fish == 6) {
												al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
												al_draw_bitmap(pangr, map[i][j].x+11, map[i][j].y+7, 0);
											}  else if(map[i][j].fish == 7) {
												al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
												al_draw_bitmap(pangb, map[i][j].x+10, map[i][j].y+11, 0);
											}  else if(map[i][j].fish == 8) {
												al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
												al_draw_bitmap(pangp, map[i][j].x+15, map[i][j].y+7, 0);
											}  else if(map[i][j].fish == 9) {
												al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
												al_draw_bitmap(pangg, map[i][j].x+15, map[i][j].y+9, 0);
											}else {
												continue;
											}
										}
									}
									//drawing scores
									if(player_num==2){
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
									}else if(player_num==3){
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
									}else if(player_num==4){
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 650, ALLEGRO_ALIGN_CENTER, "%i",player[3].fish);
										al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
									}
									if(turn==0){
										al_draw_bitmap(pangr, map[xpan][ypan].x+11+showpang*delta_x, map[xpan][ypan].y+11+showpang*delta_y, 0);
									}else if(turn==1){
										al_draw_bitmap(pangb, map[xpan][ypan].x+11+showpang*delta_x, map[xpan][ypan].y+11+showpang*delta_y, 0);
									}else if(turn==2){
										al_draw_bitmap(pangp, map[xpan][ypan].x+11+showpang*delta_x, map[xpan][ypan].y+11+showpang*delta_y, 0);
									}else if(turn==3){
										al_draw_bitmap(pangg, map[xpan][ypan].x+11+showpang*delta_x, map[xpan][ypan].y+11+showpang*delta_y, 0);
									}
									al_flip_display();
									showpang++;
								}
								map[ilast][jlast].fish=turn+6;
								map[xpan][ypan].fish=0;
								al_clear_to_color(al_map_rgb(0, 0, 0));
								//drawing background
								if(player_num == 2) {
									al_draw_bitmap(background2, 0, 0, 0);
								} else if(player_num == 3) {
									al_draw_bitmap(background3, 0, 0, 0);
								} else {
									al_draw_bitmap(background4, 0, 0, 0);
								}
								for(i = 0; i <= 7; i++) {
									for(j = 0; j <= 7; j++) {
										if(map[i][j].fish == 1) {
											al_draw_bitmap(image1, map[i][j].x, map[i][j].y, 0);
										} else if(map[i][j].fish == 2) {
											al_draw_bitmap(image2, map[i][j].x, map[i][j].y, 0); // drawing hexes in map
										} else if(map[i][j].fish == 3) {
											al_draw_bitmap(image3, map[i][j].x, map[i][j].y, 0);
										} else if(map[i][j].fish == 0) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
										}  else if(map[i][j].fish == 6) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangr, map[i][j].x+11, map[i][j].y+7, 0);
										}  else if(map[i][j].fish == 7) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangb, map[i][j].x+10, map[i][j].y+11, 0);
										}  else if(map[i][j].fish == 8) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangp, map[i][j].x+15, map[i][j].y+7, 0);
										}  else if(map[i][j].fish == 9) {
											al_draw_bitmap(image0, map[i][j].x, map[i][j].y, 0);
											al_draw_bitmap(pangg, map[i][j].x+15, map[i][j].y+9, 0);
										}else {
											continue;
										}
									}
								}
								//drawing scores
								if(player_num==2){
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
								}else if(player_num==3){
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
								}else if(player_num==4){
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 650, ALLEGRO_ALIGN_CENTER, "%i",player[3].fish);
									al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
								}
								al_flip_display();
							}
						}
					}			
				}
			}
		}while(1);
		//winner
		int temp;
		for(int i = 0; i < player_num ; i++) {
			//especify each player rank
			for(int j = 0; j < player_num ; j++) {
				if(player[j].fish > player[i].fish&&player[j].rank > player[i].rank) {
					temp = player[i].rank;
 					player[i].rank= player[j].rank;
 					player[j].rank=temp;
				} else if(player[j].fish == player[i].fish&&player[j].rank > player[i].rank&&player[j].movenum> player[i].movenum) {
					temp = player[i].rank;
 					player[i].rank= player[j].rank;
 					player[j].rank=temp;
				}
			}
		}
		while(1) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			//drawing end game page
			al_draw_bitmap(leader_board, 0, 0, 0);
			//drawing score board
			if(player_num == 2) {
				al_draw_bitmap(score_board2, 0, 0, 0);
			} else if(player_num == 3) {
				al_draw_bitmap(score_board3, 0, 0, 0);
			} else {
				al_draw_bitmap(score_board4, 0, 0, 0);
			}
			//drawing penguins according to their rank
			switch (player[0].rank){
				case 1:
					al_draw_bitmap(pangr, 590,560,0);
					break;
				case 2:
					al_draw_bitmap(pangr, 720,600,0);
					break;
				case 3:
					al_draw_bitmap(pangr, 460,620,0);
					break;
			}switch (player[1].rank){
				case 1:
					al_draw_bitmap(pangb, 590,560,0);
					break;
				case 2:
					al_draw_bitmap(pangb, 720,600,0);
					break;
				case 3:
					al_draw_bitmap(pangb, 460,620,0);
					break;
			}
			if(player_num >= 3) {
				switch (player[2].rank){
					case 1:
						al_draw_bitmap(pangp, 590,560,0);
						break;
					case 2:
						al_draw_bitmap(pangp, 720,600,0);
						break;
					case 3:
						al_draw_bitmap(pangp, 460,620,0);
						break;
				}
			}
			if(player_num == 4) {
				switch (player[3].rank){
					case 1:
						al_draw_bitmap(pangg,  590,560,0);
						break;
					case 2:
						al_draw_bitmap(pangg, 720,600,0);
						break;
					case 3:
						al_draw_bitmap(pangg, 460,620,0);
						break;
				}
			}
			//drawing scores
			if(player_num==2){
				al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
				al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
			}else if(player_num==3){
				al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
				al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
				al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
			}else if(player_num==4){
				al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 105, ALLEGRO_ALIGN_CENTER, "%i",player[0].fish);
				al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 290, ALLEGRO_ALIGN_CENTER, "%i",player[1].fish);
				al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 465, ALLEGRO_ALIGN_CENTER, "%i",player[2].fish);
				al_draw_textf(font0, al_map_rgb(255, 255, 255), 100, 650, ALLEGRO_ALIGN_CENTER, "%i",player[3].fish);
			}		
			ALLEGRO_EVENT ev;
			al_wait_for_event(event, &ev);
			if(ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
				posm_x = ev.mouse.x;
				posm_y = ev.mouse.y;
			}
			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				return 0;
			}
			//inbound of yes icon
			if(posm_x >= 385&& posm_x <= 560&& posm_y >= 370 && posm_y <= 475) {
				al_draw_bitmap(s_yellow_squar, 385, 370,0);
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if(ev.mouse.button && 1) {
						yn = 1;
						break;
					}
				}
			}
			//inbound of no icon
			else if(posm_x >= 660 && posm_x <= 835&& posm_y >= 370 && posm_y <= 475) {
				al_draw_bitmap(s_yellow_squar, 660, 370, 0);
				if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if(ev.mouse.button && 1) {
						yn = 0;
						break;
					}
				}
			}
			al_flip_display();
		}
		//free
		al_destroy_bitmap(background4);
		al_destroy_bitmap(background3);
		al_destroy_bitmap(background2);
		al_destroy_bitmap(introp);
		al_destroy_bitmap(Pnum);
		al_destroy_bitmap(yellow_hex);
		al_destroy_bitmap(yellow_squar);
		al_destroy_bitmap(s_yellow_squar);
		al_destroy_bitmap(red_hex);
		al_destroy_bitmap(image0);
		al_destroy_bitmap(image1);
		al_destroy_bitmap(image2);
		al_destroy_bitmap(image3);
		al_destroy_bitmap(pangb);
		al_destroy_bitmap(pangg);
		al_destroy_bitmap(cursor);
		al_destroy_bitmap(cursor2);
		al_destroy_bitmap(pangr);
		al_destroy_bitmap(pangp);
		al_destroy_bitmap(turnB2);
		al_destroy_bitmap(turnB3);
		al_destroy_bitmap(turnB4);
		al_destroy_bitmap(turnR2);
		al_destroy_bitmap(turnR3);
		al_destroy_bitmap(turnR4);
		al_destroy_bitmap(turnP3);
		al_destroy_bitmap(turnP4);
		al_destroy_bitmap(turnG4);
		al_destroy_bitmap(leader_board);
		al_destroy_bitmap(score_board4);
		al_destroy_bitmap(score_board3);
		al_destroy_bitmap(score_board2);
		al_destroy_bitmap(guide_squar);
		al_destroy_bitmap(guide_squar2);
		al_destroy_bitmap(yellow_guide_squar);
		al_destroy_bitmap(guide);
	    al_destroy_display(display);
	    al_destroy_event_queue(event);
	    al_destroy_font(font0);
	    al_uninstall_mouse();
	    al_uninstall_keyboard();
	}while(yn);//restart the game of exit it according to what player selected
return 0;
}