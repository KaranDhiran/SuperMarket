//This is the information of the products in the shop.
typedef struct productinformation {
	long int prnumb;
	long int stock;
	char productname[51];		/*BRAND_PRODUCTNAME*/
	long int quantity;
	float discount, price;
	struct date {
		int dd;
		int mm;
		int yy;
	}manudate, expdate;
}productinfo;	
