/*****************************************************************************
 * Copyright (C) Karan Dhiran dhirankaran@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
#include<ncurses.h>
#include "productinformation.h"
#include "customerinformation.h"
enum {ADMIN, USER};
#define VIEWPROD 1
#define ADDPROD 2
#define DELETEPROD 3
#define MODIFYPROD 4
#define MODPRICE 5
#define MODDISC 6
#define MODQTY 7
#define STATS 8
#define END 9
/* The product which we enter is the generalised version. For example, if I buy 20 good day biscuits, the quantity of good day biscuits will reduce by 20. Also, if I add a product, for example butter with quantity of 100, it means I have added 100 butter packs, each having the same price, discount, exp date and manu date. In this we have assumed that all the items of a particular product have the same product number. This may or may not be correct. */
int main() {
	initscr();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	int x, y;
	getmaxyx(stdscr, y, x);
	keypad(stdscr, TRUE);
	int a = 0;
	int nflag = 0, nindex = 0;
	while(1) {
		clear();
		attron(COLOR_PAIR(1));
		mvprintw(15, 60, "1. Admin");
		attroff(COLOR_PAIR(1));
		mvprintw(15 + 3, 60, "2. User");
		refresh();
		if(nindex) {
			nindex = 0;
			getch();
		}	
		int startchoice = -1, flag = 0;
		while(a != '\n') {
			a = getch();
			if(a == 'q') {
				nflag = 1;
				break;
			}
			int nowy, nowx;
			getyx(stdscr, nowy, nowx);
			if(a == KEY_UP && nowy == 15) {
				attron(COLOR_PAIR(1));
				mvprintw(15, 60, "1. Admin");
				attroff(COLOR_PAIR(1));
				mvprintw(15 + 3, 60, "2. User");
				refresh();
				startchoice = ADMIN;
			}
			else if(a == KEY_DOWN && nowy == 15) {
				mvprintw(15, 60, "1. Admin");
				attron(COLOR_PAIR(1));
				mvprintw(15 + 3, 60, "2. User");
				attroff(COLOR_PAIR(1));
				startchoice = USER;
				refresh();
			}
			else if(a == KEY_UP && nowy == 18) {
				attron(COLOR_PAIR(1));
				mvprintw(15, 60, "1. Admin");
				attroff(COLOR_PAIR(1));
				mvprintw(15 + 3, 60, "2. User");
				refresh();
				startchoice = ADMIN;
			}
			else if(a == KEY_DOWN && nowy == 18) {
				mvprintw(15, 60, "1. Admin");
				attron(COLOR_PAIR(1));
				mvprintw(15 + 3, 60, "2. User");
				attroff(COLOR_PAIR(1));
				refresh();
				startchoice = USER;
			}
		}
		if(nflag)
			break;
		if(startchoice == -1)
			startchoice = ADMIN;
		WINDOW *adminwin = newwin(y, x, 0, 0);
		WINDOW *userwin = newwin(y, x, 0, 0);
		int adminchoice = -1;
		if(startchoice == ADMIN) {
			while(1) {
				wattron(adminwin, COLOR_PAIR(1));
				mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
				wattroff(adminwin, COLOR_PAIR(1));
				mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
				mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
				mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
				mvwprintw(adminwin, 19, 60, "5. STATISTICS");
				mvwprintw(adminwin, 20, 60, "6. END DAY");
				mvwprintw(adminwin, 21, 60, "PRESS 'q' TO GO BACK TO PREVIOUS WINDOW");
				wrefresh(adminwin);
				a = 0;
				keypad(adminwin, TRUE);
				flushinp();
				wmove(adminwin, 15, 60);
				adminchoice = -1;
				while(a != '\n') {
					a = wgetch(adminwin);
					if(a == 'q') {
						flag = 1;
						break;
					}	
					int nowy, nowx;
					getyx(adminwin, nowy, nowx);
					if(a == KEY_UP && nowy == 15) {	
						wattron(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
						wattroff(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
						mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
						mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
						mvwprintw(adminwin, 19, 60, "5. STATISTICS");
						mvwprintw(adminwin, 20, 60, "6. END DAY");
						wrefresh(adminwin);
						wmove(adminwin, 15, 60);
						adminchoice = VIEWPROD;
					}
					else if(a == KEY_UP && nowy == 16) {	
						wattron(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
						wattroff(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
						mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
						mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
						mvwprintw(adminwin, 19, 60, "5. STATISTICS");
						mvwprintw(adminwin, 20, 60, "6. END DAY");
						wrefresh(adminwin);
						wmove(adminwin, 15, 60);
						adminchoice = VIEWPROD;
					}
					else if(a == KEY_UP && nowy == 17) {	
						mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
						wattron(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
						wattroff(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
						mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
						mvwprintw(adminwin, 19, 60, "5. STATISTICS");
						mvwprintw(adminwin, 20, 60, "6. END DAY");
						wrefresh(adminwin);
						wmove(adminwin, 16, 60);
						adminchoice = ADDPROD;
					}
					else if(a == KEY_UP && nowy == 18) {	
						mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
						mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
						wattron(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
						wattroff(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
						mvwprintw(adminwin, 19, 60, "5. STATISTICS");
						mvwprintw(adminwin, 20, 60, "6. END DAY");
						wrefresh(adminwin);
						wmove(adminwin, 17, 60);
						adminchoice = DELETEPROD;
					}
					else if(a == KEY_UP && nowy == 19) {	
						mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
						mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
						mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
						wattron(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
						wattroff(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 19, 60, "5. STATISTICS");
						mvwprintw(adminwin, 20, 60, "6. END DAY");
						wrefresh(adminwin);
						wmove(adminwin, 18, 60);
						adminchoice = MODIFYPROD;
					}
					else if(a == KEY_UP && nowy == 20) {	
						mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
						mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
						mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
						mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
						wattron(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 19, 60, "5. STATISTICS");
						wattroff(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 20, 60, "6. END DAY");
						wmove(adminwin, 19, 60);
						wrefresh(adminwin);
						adminchoice = STATS;
					}	
					else if(a == KEY_DOWN && nowy == 15) {	
						mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
						wattron(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
						wattroff(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
						mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
						mvwprintw(adminwin, 19, 60, "5. STATISTICS");
						mvwprintw(adminwin, 20, 60, "6. END DAY");
						wrefresh(adminwin);
						wmove(adminwin, 16, 60);
						adminchoice = ADDPROD;
					}
					else if(a == KEY_DOWN && nowy == 16) {	
						mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
						mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
						wattron(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
						wattroff(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
						mvwprintw(adminwin, 19, 60, "5. STATISTICS");
						mvwprintw(adminwin, 20, 60, "6. END DAY");
						wrefresh(adminwin);
						wmove(adminwin, 17, 60);
						adminchoice = DELETEPROD;
					}
					else if(a == KEY_DOWN && nowy == 17) {	
						mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
						mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
						mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
						wattron(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
						wattroff(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 19, 60, "5. STATISTICS");
						mvwprintw(adminwin, 20, 60, "6. END DAY");
						wrefresh(adminwin);
						wmove(adminwin, 18, 60);
						adminchoice = MODIFYPROD;
					}
					else if(a == KEY_DOWN && nowy == 18) {	
						mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
						mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
						mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
						mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
						wattron(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 19, 60, "5. STATISTICS");
						wattroff(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 20, 60, "6. END DAY");
						wrefresh(adminwin);
						wmove(adminwin, 19, 60);
						adminchoice = STATS;
					}
					else if(a == KEY_DOWN && nowy == 19) {	
						mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
						mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
						mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
						mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
						mvwprintw(adminwin, 19, 60, "5. STATISTICS");
						wattron(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 20, 60, "6. END DAY");
						wattroff(adminwin, COLOR_PAIR(1));
						wrefresh(adminwin);
						wmove(adminwin, 20, 60);
						adminchoice = END;
					}
					else if(a == KEY_DOWN && nowy == 20) {	
						mvwprintw(adminwin, 15, 60, "1. VIEW PRODUCTS");
						mvwprintw(adminwin, 16, 60, "2. ADD PRODUCT");
						mvwprintw(adminwin, 17, 60, "3. DELETE PRODUCT");
						mvwprintw(adminwin, 18, 60, "4. MODIFY PRODUCT");
						mvwprintw(adminwin, 19, 60, "5. STATISTICS");
						wattron(adminwin, COLOR_PAIR(1));
						mvwprintw(adminwin, 20, 60, "6. END DAY");
						wattroff(adminwin, COLOR_PAIR(1));
						wrefresh(adminwin);
						wmove(adminwin, 20, 60);
						adminchoice = END;
					}
				}
				if(flag) {
					flag = 0;
					break;
				}
/* It will read the PRODUCT.txt file and display the contents on the screen*/	
				if(adminchoice == -1)
					adminchoice = VIEWPROD;	
				if(adminchoice == VIEWPROD) {
					wclear(adminwin);
					FILE *fp = fopen("PRODUCT.txt", "r");
					if(!fp)	
						return 1;
					wprintw(adminwin, "LIST OF PRODUCTS : \n");
					productinfo tmp;
					int c = 0;
					while(fread(&tmp, sizeof(tmp), 1, fp)) {
						wprintw(adminwin, "\nPRODUCT NUMBER : %ld\n", tmp.prnumb);
						wprintw(adminwin, "STOCK : %ld\n", tmp.stock);
						wprintw(adminwin, "PRODUCT NAME : %s\n", tmp.productname);
						wprintw(adminwin, "QUANTITY : %ld\n", tmp.quantity);
						wprintw(adminwin, "DISCOUNT : %f\n", tmp.discount);
						wprintw(adminwin, "PRICE : %f\n", tmp.price);
						wprintw(adminwin, "Manufacturing Date : %d %d %d\n", tmp.manudate.dd, tmp.manudate.mm, tmp.manudate.yy);
						wprintw(adminwin, "Expiry Date : %d %d %d\n", tmp.expdate.dd, tmp.expdate.mm, tmp.expdate.yy);
						c++;
						wrefresh(adminwin);
						if(c % 4 == 0) {
							int get = wgetch(adminwin);
							wclear(adminwin);
						}
						wrefresh(adminwin);
					}		
					wgetch(adminwin);
					fclose(fp);
				}
/* It will delete the product from the PRODUCT.txt file*/
				else if(adminchoice == DELETEPROD) {
					wclear(adminwin);
					long int t;
	       				wprintw(adminwin, "ENTER THE PRODUCT NUMBER : \n");    
			        	wscanw(adminwin, "%ld", &t);
		      			productinfo tmp;
				        FILE *fp;
				        FILE *temp;
      					fp = fopen("PRODUCT.txt", "r");
			        	temp = fopen("tmp.txt", "w"); 
				        while(fread(&tmp, sizeof(tmp), 1, fp)) 
				                if(tmp.prnumb != t)
				                        fwrite(&tmp, sizeof(tmp), 1, temp);
				        fclose(fp);
			        	fclose(temp);
				        remove("PRODUCT.txt");
				        rename("tmp.txt", "PRODUCT.txt");
				}
/*It will display the statistics of sale*/
				else if(adminchoice == STATS) {
					wclear(adminwin);
					FILE *stat;
					productinfo st, pst;
					FILE *stprod;
					long int tquantity = 0;
					int c = 0, get;
					stprod = fopen("PRODUCT.txt", "r");
					wprintw(adminwin, "LIST OFPRODUCTS SOLD TODAY : \n\n");
					while(fread(&pst, sizeof(pst), 1, stprod)) {
						stat = fopen("STATFILE.txt", "r");
						while(fread(&st, sizeof(st), 1, stat)) {
							if(strcmp(st.productname, pst.productname) == 0) 
								tquantity += st.quantity;
						} 
						wprintw(adminwin, "PRODUCT NAME : %s", pst.productname);
						wprintw(adminwin, "\nQUANTITY SOLD : %ld", tquantity);
						wprintw(adminwin, "\n\n");
						wrefresh(adminwin);
						c++;
						if(c % 12 == 0) {
							get = wgetch(adminwin);
							wclear(adminwin);
							wrefresh(adminwin);
						}	
						tquantity = 0;
						fclose(stat);
					}
					wgetch(adminwin);
					fclose(stprod);
				}
				else if(adminchoice == END) {
					FILE *rm;
					rm = fopen("STATFILE.txt", "w");
					fclose(rm);
				}
/* It will add a new product to the supermarket*/
				else if(adminchoice == ADDPROD) {
					wclear(adminwin);
					wmove(adminwin, 0, 0);
					FILE *fp = fopen("PRODUCT.txt", "a");
       			        	productinfo a;
	     		  	        wprintw(adminwin, "Enter the productnumber : ");	
				        wscanw(adminwin, "%ld", &(a.prnumb));
	        	 	        wprintw(adminwin, "Enter the stock of the product : ");
	    			        wscanw(adminwin, "%ld", &(a.stock));
		                	wprintw(adminwin, "Enter the productname : ");
			                wscanw(adminwin, "%s", a.productname);
			                wprintw(adminwin, "Enter the quantity : ");
			                wscanw(adminwin, "%ld", &(a.quantity));
		        	        wprintw(adminwin, "Enter the discount : ");
		                	wscanw(adminwin, "%f", &(a.discount));
					wprintw(adminwin, "Enter the price : ");
					wscanw(adminwin, "%f", &(a.price));
			                wprintw(adminwin, "Enter the manufcturing date (dd mm yy) : ");
		        	        wscanw(adminwin, "%d%d%d", &(a.manudate.dd), &(a.manudate.mm), &(a.manudate.yy));
		                	wprintw(adminwin, "Enter the expiry date (dd mm yy) : ");
			                wscanw(adminwin, "%d%d%d", &(a.expdate.dd), &(a.expdate.mm), &(a.expdate.yy));
			                fwrite(&a, sizeof(a), 1, fp);
			                fclose(fp);
				}
/* it will modify the information like price, discount and the stock of the quantity*/
				else if(adminchoice == MODIFYPROD) {
					wclear(adminwin);
					keypad(adminwin, TRUE);
					mvwprintw(adminwin, 1, 0, "ENTER THE DETAIL WHICH HAS TO BE CHANGED : ");
					wattron(adminwin, COLOR_PAIR(1));
					mvwprintw(adminwin, 2, 0, "1. PRICE");
					wattroff(adminwin, COLOR_PAIR(1));
					mvwprintw(adminwin, 3, 0, "2. DISCOUNT");
					mvwprintw(adminwin, 4, 0, "3. QUANTITY");
					a = 0;
					int modchoice = -1;
					wmove(adminwin, 2, 0);
					while(a != '\n') {
						a = wgetch(adminwin);
						int nowy, nowx;
						getyx(adminwin, nowy, nowx);
						if(a == KEY_UP && nowy == 2) {
							mvwprintw(adminwin, 1, 0, "ENTER THE DETAIL WHICH HAS TO BE CHANGED : ");
							wattron(adminwin, COLOR_PAIR(1));
							mvwprintw(adminwin, 2, 0, "1. PRICE");
							wattroff(adminwin, COLOR_PAIR(1));
							mvwprintw(adminwin, 3, 0, "2. DISCOUNT");
							mvwprintw(adminwin, 4, 0, "3. QUANTITY");
							wmove(adminwin, 2, 0);
							wrefresh(adminwin);
							modchoice = MODPRICE;
						}	
						else if(a == KEY_UP && nowy == 3) {
							mvwprintw(adminwin, 1, 0, "ENTER THE DETAIL WHICH HAS TO BE CHANGED : ");
							wattron(adminwin, COLOR_PAIR(1));
							mvwprintw(adminwin, 2, 0, "1. PRICE");
							wattroff(adminwin, COLOR_PAIR(1));
							mvwprintw(adminwin, 3, 0, "2. DISCOUNT");
							mvwprintw(adminwin, 4, 0, "3. QUANTITY");
							wmove(adminwin, 2, 0);
							wrefresh(adminwin);
							modchoice = MODPRICE;
						}	
						else if(a == KEY_UP && nowy == 4) {
							mvwprintw(adminwin, 1, 0, "ENTER THE DETAIL WHICH HAS TO BE CHANGED : ");
							mvwprintw(adminwin, 2, 0, "1. PRICE");
							wattron(adminwin, COLOR_PAIR(1));
							mvwprintw(adminwin, 3, 0, "2. DISCOUNT");
							wattroff(adminwin, COLOR_PAIR(1));
							mvwprintw(adminwin, 4, 0, "3. QUANTITY");
							wmove(adminwin, 3, 0);
							wrefresh(adminwin);
							modchoice = MODDISC;
						}	
						else if(a == KEY_DOWN && nowy == 2) {
							mvwprintw(adminwin, 1, 0, "ENTER THE DETAIL WHICH HAS TO BE CHANGED : ");
							mvwprintw(adminwin, 2, 0, "1. PRICE");
							wattron(adminwin, COLOR_PAIR(1));
							mvwprintw(adminwin, 3, 0, "2. DISCOUNT");
							wattroff(adminwin, COLOR_PAIR(1));
							mvwprintw(adminwin, 4, 0, "3. QUANTITY");
							wmove(adminwin, 3, 0);
							wrefresh(adminwin);
							modchoice = MODDISC;
						}	
						else if(a == KEY_DOWN && nowy == 3) {
							mvwprintw(adminwin, 1, 0, "ENTER THE DETAIL WHICH HAS TO BE CHANGED : ");
							mvwprintw(adminwin, 2, 0, "1. PRICE");
							mvwprintw(adminwin, 3, 0, "2. DISCOUNT");
							wattron(adminwin, COLOR_PAIR(1));
							mvwprintw(adminwin, 4, 0, "3. QUANTITY");
							wattroff(adminwin, COLOR_PAIR(1));
							wmove(adminwin, 4, 0);
							wrefresh(adminwin);
							modchoice = MODQTY;
						}	
						else if(a == KEY_DOWN && nowy == 4) {
							mvwprintw(adminwin, 1, 0, "ENTER THE DETAIL WHICH HAS TO BE CHANGED : ");
							mvwprintw(adminwin, 2, 0, "1. PRICE");
							mvwprintw(adminwin, 3, 0, "2. DISCOUNT");
							wattron(adminwin, COLOR_PAIR(1));
							mvwprintw(adminwin, 4, 0, "3. QUANTITY");
							wattroff(adminwin, COLOR_PAIR(1));
							wmove(adminwin, 4, 0);
							wrefresh(adminwin);
							modchoice = MODQTY;
						}	
					}
					if(modchoice == -1)
						modchoice = MODPRICE;
					if(modchoice == MODPRICE) {/*modifies price*/
						wclear(adminwin);
						char str[100];
						wprintw(adminwin, "ENTER THE PRODUCT NAME : ");
						wscanw(adminwin, "%s", str);
						wprintw(adminwin, "ENTER THE NEW PRICE : ");
						float f;
						wscanw(adminwin, "%f", &f);
						productinfo tmp;
				        	FILE *fp;
					        FILE *temp;
					        fp = fopen("PRODUCT.txt", "r");
					        temp = fopen("tmp.txt", "w");
	 				        while(fread(&tmp, sizeof(tmp), 1, fp)) {
					                if(strcmp(tmp.productname, str) != 0)
				        	                fwrite(&tmp, sizeof(tmp), 1, temp);
	                				else {
								tmp.price = f;
								fwrite(&tmp, sizeof(tmp), 1, temp);
							}
					        }
	   				        fclose(fp);
					        fclose(temp);
				        	remove("PRODUCT.txt");
					        rename("tmp.txt", "PRODUCT.txt");
					}
					else if(modchoice == MODQTY) {/*Modifies quantity*/
						wclear(adminwin);
						char str[100];
						wprintw(adminwin, "ENTER THE PRODUCT NAME : ");
						wscanw(adminwin, "%s", str);
						wprintw(adminwin, "ENTER THE NEW QUANTITY : ");
						long int l;
						wscanw(adminwin, "%ld", &l);
						productinfo tmp;
				        	FILE *fp;
					        FILE *temp;
					        fp = fopen("PRODUCT.txt", "r");
					        temp = fopen("tmp.txt", "w");
	 				        while(fread(&tmp, sizeof(tmp), 1, fp)) {
					                if(strcmp(tmp.productname, str) != 0)
				        	                fwrite(&tmp, sizeof(tmp), 1, temp);
		                			else {
								tmp.quantity = l;
								fwrite(&tmp, sizeof(tmp), 1, temp);
							}
					        }
	   			        	fclose(fp);
					        fclose(temp);
					        remove("PRODUCT.txt");
					        rename("tmp.txt", "PRODUCT.txt");
					}
					else if(modchoice == MODDISC) {/*modifies discount*/
						wclear(adminwin);
						char str[100];
						wprintw(adminwin, "ENTER THE PRODUCT NAME : ");
						wscanw(adminwin, "%s", str);
						wprintw(adminwin, "ENTER THE NEW DISCOUNT : ");
						float f;
						wscanw(adminwin, "%f", &f);
						productinfo tmp;
					        FILE *fp;
					        FILE *temp;
					        fp = fopen("PRODUCT.txt", "r");
				        	temp = fopen("tmp.txt", "w");
 				        	while(fread(&tmp, sizeof(tmp), 1, fp)) {
				                	if(strcmp(tmp.productname, str) != 0)
				                        	fwrite(&tmp, sizeof(tmp), 1, temp);
 	              	 			else {
								tmp.discount = f;
								fwrite(&tmp, sizeof(tmp), 1, temp);
							}
					        }
   				        	fclose(fp);
					        fclose(temp);
					        remove("PRODUCT.txt");
					        rename("tmp.txt", "PRODUCT.txt");
					}
				}		
				wclear(adminwin);
			}
		}
			else if(startchoice == USER) {
			nindex = 1;
			wclear(userwin);
			float amount = 0.0;
			long int usr = 0;
		        productinfo cf;
		        FILE *fq;
		        fq = fopen("PRODUCT.txt", "r");				//fq is for products
		        if(fq == NULL) 
		                return;
			fclose(fq);
			FILE *statfile;						//statfile is for stats
			statfile = fopen("STATFILE.txt", "a");
		        FILE *custfile;
		        custfile = fopen("BILLING.txt", "w");			//custfile is for billing
		        if(custfile == NULL)
		                return;
//	        FILE *fr;
//	        fr = fopen("STATISTICS.txt", "a");			//fr is for statistics
//       	if(fr == NULL) 
//	                return;
        	        int c = 0;
		        while(usr != -1) {
				int f = 0;
				wclear(userwin);
		                wprintw(userwin, "ENTER THE PRODUCT NUMBER : ");
		                wscanw(userwin, "%ld", &usr);
				wrefresh(userwin);
				fq = fopen("PRODUCT.txt", "r");
				FILE *temporary = fopen("tmp.txt", "w");
		                while(fread(&cf, sizeof(cf), 1, fq)) {
		                        if(cf.prnumb == usr) {
		                                wprintw(userwin, "ENTER THE QUANTITY : ");
        	                    	        wscanw(userwin, "%d", &c);
						if(c > cf.quantity) { 
							fwrite(&cf, sizeof(cf), 1, temporary);
							wprintw(userwin, "REQUIRED QUANTITY NOT AVAILABLE\n");
							f = 1;
							wrefresh(userwin);
							wgetch(userwin);
						}
						else {
							int t = cf.quantity;
							cf.quantity = t - c;
							fwrite(&cf, sizeof(cf), 1, temporary);
		                	                cf.quantity = c;
		                        	        fwrite(&cf, sizeof(cf), 1, custfile);
							fwrite(&cf, sizeof(cf), 1, statfile);
							f = 1;
						}
	                        	}
					else
						fwrite(&cf, sizeof(cf), 1, temporary);
                		}
				if(!f &&(usr != -1)) {
					wprintw(userwin, "PRODUCT NOT FOUND !");
					wrefresh(userwin);
					wgetch(userwin);
					f = 0;
				}
				fclose(fq);
				fclose(temporary);
				remove("PRODUCT.txt");
				rename("tmp.txt", "PRODUCT.txt");
			}
			fclose(statfile);
		        fclose(custfile);		
//	        FILE *fr;
//	        fr = fopen("STOCKUPDATE.txt", "r");
//	        stockupdate su;
		        fq = fopen("BILLING.txt", "r");
//	        FILE *fn;
//	        fn = fopen("tmp.txt", "w");
			wclear(userwin);
			wprintw(userwin, "YOUR FINAL BILL IS \n");
		        while(fread(&cf, sizeof(cf), 1, fq)) {
//	                while(fread(&su, sizeof(su), 1, fr)) {
//	                        if(strcmp(su.productname, cf.productname) == 0) {
//	                                su.revgen = su.revgen + cf.price - (cf.discount * (cf.price));
//	                                fwrite(&su, sizeof(su), 1, fn);
//	                        }
//	                        else
//	                                fwrite(&su, sizeof(su), 1, fn);
//	                }
//	                fclose(fr);
//	                fopen(fr);
				wprintw(userwin, "\nPRODUCT NAME : %s\n", cf.productname);
				wprintw(userwin, "QUANTITY : %ld\n", cf.quantity);
				wprintw(userwin, "PRICE (AFTER DISCOUNT) : %f\n", cf.quantity * ((cf.price) - (cf.discount * (cf.price))));
				wrefresh(userwin);
	   	                amount = amount + cf.quantity * ((cf.price) - (cf.discount * (cf.price)));	//A 5 p.c disc is inputed as 0.05, so no need of div by 100
        		}
//	        fclose(fn);
		        fclose(fq);
//	        remove("STOCKUPDATE.txt");
//	        rename("tmp.txt", "STOCKUPDATE.txt");
		        wprintw(userwin, "\nTOTAL AMOUNT IS : %f", amount);
			wrefresh(userwin);
		        wprintw(userwin, "\nARE YOU A NEW CUSTOMER (y/n) ? ");
			wrefresh(userwin);
		        char ch;
			long int g = 1;
		        wscanw(userwin, "%c", &ch);
		        if(ch == 'y' || ch == 'Y') {
				wclear(userwin);
				wprintw(userwin, "DO YOU WANT TO REGISTER IN OUR DATABASE ? (y/n) ");
				wrefresh(userwin);
				char chh;
				wscanw(userwin, "%c", &chh);
				if(chh == 'y') {
			                FILE *fd;
			                fd = fopen("CARDNUMBER.txt", "a+");
					long int num;
					int x = fread(&num, sizeof(num), 1, fd); 
					if(!x) {
						num = g = 1;
						fwrite(&num, sizeof(num), 1, fd);
						fclose(fd);
					}
					else {
						fclose(fd);
						fd = fopen("CARDNUMBER.txt", "r");
						while(fread(&num, sizeof(num), 1, fd)) 
							g++;
						fclose(fd);
						fd = fopen("CARDNUMBER.txt", "a");
						fwrite(&g, sizeof(g), 1, fd);
						fclose(fd);
					}
			                FILE *fp;
			                int c;
			                int i = 0;
/*Customer details*/
/*Every customer will get 1 point for shopping of Rs 10*/
			                fp = fopen("CUSTOMER.txt", "a");
			                custoinfo a;
					wclear(userwin);
			                wprintw(userwin, "ENTER YOUR NAME : ");
					wrefresh(userwin);
		        	        wscanw(userwin, "%[^\n]", a.name);
		                	wprintw(userwin, "ENTER YOUR MAIL ID : ");
					wrefresh(userwin);
			                wscanw(userwin, "%[^\n]", a.e_mailid);
			                wprintw(userwin, "ENTER YOUR ADDRESS : ");
					wrefresh(userwin);
		                	wscanw(userwin, "%[^\n]", a.address);
			                wprintw(userwin, "ENTER YOUR MOBILE NUMBER : ");
					wrefresh(userwin);
			                wscanw(userwin, "%ld", &(a.mobilenumber));
		        	        a.cardnumber = g;
		       		         a.points = amount / 10;
			                fwrite(&a, 1, sizeof(a), fp);
		        	        fclose(fp);
					wclear(userwin);
					wprintw(userwin, "THANK YOU. YOU HAVE BEEN REGISTERED\n");
					wprintw(userwin, "YOUR CARD NUMBER IS : %ld\nDUE AMOUNT : %f\nPRESS ANY KEY TO COMPLETE TRANSACTION\n", g, amount);
					wrefresh(userwin);
					wgetch(userwin);
		        	}
				else {
					wclear(userwin);
					wprintw(userwin, "DUE AMOUNT : %f\nPRESS ANY KEY TO COMPLETE TRANSACTION\n", g, amount);
					wrefresh(userwin);
					wgetch(userwin);
				}
			}
		        else {
				wclear(userwin);
		                wprintw(userwin, "ENTER YOUR CARD NUMBER : ");
				wrefresh(userwin);
	        	        long int num;
		                wscanw(userwin, "%ld", &num);
				FILE *fp = fopen("CUSTOMER.txt", "r");
	        	        custoinfo a;
	                	while(fread(&a, sizeof(a), 1, fp))
		                        if(a.cardnumber == num) {
		                                wprintw(userwin, "YOU HAVE %ld POINTS AVAILABLE\n", a.points);
	        	                        break;
	                	        }
		                fclose(fp);
		                wprintw(userwin, "DO YOU WANT TO REDEEM YOUR POINTS ? (y/n)");
				wrefresh(userwin);
		                char ch;
	        	        wscanw(userwin, "%c", &ch);
		                if(ch == 'Y' || ch == 'y') {
		                        float temp;
	        	                temp = amount - (a.points * 10);
                       			if(temp < 0)
	        	        	        temp = 0.0;
		                        fp = fopen("CUSTOMER.txt", "r");
		        	        FILE *tmp;
	        	                tmp = fopen("tmp.txt", "w");
	        		        while(fread(&a, sizeof(a), 1, fp)) {
	        	                        if(a.cardnumber == num) {
	        	                                a.points = 0;
	        	                                fwrite(&a, sizeof(a), 1, tmp);
	        	                        }
	        	                        else
	        	                                fwrite(&a, sizeof(a), 1, tmp);
	        	                }
	        	                fclose(fp);
	        	                fclose(tmp);
	        	                remove("CUSTOMER.txt");
	        	                rename("tmp.txt", "CUSTOMER.txt");
					wclear(userwin);
					wprintw(userwin, "DUE AMOUNT : %f\nPRESS ANY KEY TO COMPLETE TRANSACTION\n", temp);
					wrefresh(userwin);
					wgetch(userwin);	
				}
				else {
					wclear(userwin);
	        	                fp = fopen("CUSTOMER.txt", "r");
	        	                FILE *tmp;
	        	                tmp = fopen("tmp.txt", "w");
	        	                while(fread(&a, sizeof(a), 1, fp)) {
	        	                        if(a.cardnumber == num) {
	        	                                a.points = a.points + amount / 10;
	        	                                fwrite(&a, sizeof(a), 1, tmp);
	        	                        }
	        	                        else
	        	                                fwrite(&a, sizeof(a), 1, tmp);
	        	                }
	        	                fclose(fp);
	        	                fclose(tmp);
	        	                remove("CUSTOMER.txt");
	        	                rename("tmp.txt", "CUSTOMER.txt");
					wprintw(userwin, "DUE AMOUNT : %f\nPRESS ANY KEY TO COMPLETE TRANSACTION", amount);
					wrefresh(userwin);
					wgetch(userwin);
				}
		        }
/*
	        fr = fopen("STATISTICS.txt", "r");
	        printf("Do you want to check the statistics of today's sale\n");
	        char ch;
	        char statname[51];
	        int ams = 0;
	        int tqs = 0;
	        long int i = 0;
	        scanf("%c", &ch);
	        if(ch == 'Y' || ch == 'y') {
	                long int x = 0;
	                while(fread(&cf, sizeof(cf), 1, fr)) {
	                        if(cf.prnumb > x)
	                                x = cf.prnumb;
	                }
	                for(i = 1; i < x; i++) {
	                        while(fread(&cf, sizeof(cf), 1, fr)) {
	                                if(i == cf.prnumb) {
	                                        ams = ams + cf.price;
	                                        tqs = tqs + cf.quantity;
	                                        strcpy(statname, cf.productname);
	                                }
	                        }
	                        printf("Total amount of %[^\n] sold with product number %ld is %d", statname, i, ams);
	                        printf("Total sale of %[^\n] with product number %ld is %d", statname, i, tqs);
	                }
	        }
	        fclose(fr);
		*/
		}
	}
	endwin();
	return 0;
}	

