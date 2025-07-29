#include<iostream>
#include<vector>
#include<iomanip>
#include<list>
#include<queue>
#include<string>

using namespace std;

const int ROWS=7;
const int COL=10;


struct Price
{
	string type;
	int price;
};

struct Food
{
    string name;
    float price;
};

struct Order
{
    string customerName;
    vector<Food> items;
    float totalBill;

    Order(string name) {
        customerName = name;
        totalBill = 0;
    }
};

struct RatingNode
{

	float rating;
	string movieName;
	RatingNode *left,*right;
	RatingNode(float r, string name) {
        rating=r;
        movieName=name;
        left=right=nullptr;
    }
};
	struct Showtime
{
	string time;
	int availableSeats;
	string grid[ROWS][COL];
	Showtime(string t, int aSeats)
	{
		time = t;
		availableSeats = aSeats;
		createGrid();
	}
	void createGrid()
	{
		for(int i=0;i<ROWS;i++)
		{
			for(int j=0;j<COL;j++)
			{
				grid[i][j]="O";
			}
		}
	}

	void displayGrid()
	{
		cout<<"  ";
		for(int j=0;j<COL;j++)
		{
			cout<<j<<" ";
		}
		cout<<endl;
		for(int i=0;i<ROWS;i++)
		{
			cout<<char('A'+i)<<" ";
			for(int j=0;j<COL;j++)
			{
				cout<<grid[i][j]<<" ";
			}
			cout<<endl;
		}
	}

	void updateGrid(int rowIndex, int colIndex,string status) {
		grid[rowIndex][colIndex] = status;
	}

};



struct Movie
{
	string title;
	string genre;
	string duration;
	vector<Showtime> showtimes;

	void displayMovieAndShowtimes()
	{
		cout<<title<<" ("<<genre<<")"<<endl;
		cout<<"Duration: "<<duration<<endl;
		cout<<"Available Times:"<<endl;
		for(int j = 0; j < showtimes.size(); j++)
		{
			cout<<showtimes[j].time<<"-Seats Available:"<<showtimes[j].availableSeats<<endl;
		}
		cout<<endl;
	}

	void createGrids()
	{
		for(int j=0;j<showtimes.size();j++)
		{
			showtimes[j].createGrid();
		}
	}
};



struct BookingHistory
{
	int BookingId;
	string customerName;
	string movieTitle;
	string timeSlot;
	int numTickets;
	string ticketType;
	int totalBill;
	string paymentMethod;
	vector <string>bookedSeats;

static list<BookingHistory> bookingList;

	static void displayHistory()
	{
		if (bookingList.empty())
	{
		cout << "No history of Booking found!!!" << endl;
		return;
	}

	for (const BookingHistory& booking : bookingList)
	{

		cout << "Booking ID: " << booking.BookingId << endl;
		cout << "Customer Name: " << booking.customerName << endl;
		cout << "Movie Title: " << booking.movieTitle << endl;
		cout << "Time Slot: " << booking.timeSlot << endl;
		cout << "Number of Tickets: " << booking.numTickets << endl;
		cout << "Ticket Type: " << booking.ticketType << endl;
		cout << "Total Bill: Rs." << booking.totalBill << endl;
		cout << "Payment Method: " << booking.paymentMethod << endl;

		cout << "Seats: ";
		for (const string& seat : booking.bookedSeats)
		{
			cout << seat << " ";
		}
		cout << endl << endl;
	}
	}

	static void cancelBooking(vector<Movie>& movies)
	{
		int cancelId=-1;
		bool found=false;
		cout<<"Enter Booking ID you want to delete:";
		cin>>cancelId;

		for (auto node = bookingList.begin(); node != bookingList.end(); ++node)
    {
        if (node->BookingId == cancelId)
        {
            found = true;

            for (int j = 0; j < movies.size(); j++)
            {
                if (movies[j].title == node->movieTitle)
                {
                    for (int k = 0; k < movies[j].showtimes.size(); k++)
                    {
                        if (movies[j].showtimes[k].time == node->timeSlot)
                        {
                            for (int l = 0; l < node->numTickets; l++)
                            {
                                string str = node->bookedSeats[l];
                                int row = toupper(str[0]) - 'A';
                                int col = stoi(str.substr(1));
                                movies[j].showtimes[k].updateGrid(row, col, "O");
                            }
                            movies[j].showtimes[k].availableSeats += node->numTickets;
                            break;
                        }
                    }
                    break;
                }
            }
            bookingList.erase(node);
            break;
        }
    }
		if(found==false)
		{
			cout<<"Invalid Booking ID.ID not found!!!"<<endl;
			return;
		}
		else
		{
			cout<<"Successful cancellation of booking!!!"<<endl;
		}
	}
};
list<BookingHistory> BookingHistory::bookingList;

struct Theatre{
	string name;
	string location;
	vector<Movie> movies;
};

vector <Movie> movies={
		{"Avengers","Action","3:30 hrs",{{"10:00 AM",ROWS*COL},{"02:30 PM",ROWS*COL},{"07:00 PM",ROWS*COL}}},
		{"3 Idiots","Drama","2:50 hrs",{{"10:15 AM",ROWS*COL},{"03:00 PM",ROWS*COL},{"08:45 PM",ROWS*COL}}},
		{"Dangal","Sports","2:35 hrs",{{"09:00 AM",ROWS*COL},{"01:30 PM",ROWS*COL},{"07:15 PM",ROWS*COL}}},
		{"Pathan","Thriller","2:26 hrs",{{"11:45 AM",ROWS*COL},{"4:15 PM",ROWS*COL},{"9:30 PM",ROWS*COL}}},
		{"Inception","Sci-Fi","2:28 hrs",{{"10:00 AM",ROWS*COL},{"02:30 PM",ROWS*COL},{"07:00 PM",ROWS*COL}}},
		{"Titanic","Romance","3:15 hrs",{{"10:00 AM",ROWS*COL},{"2:45 PM",ROWS*COL},{"7:30 PM",ROWS*COL}}},
		{"Avatar","Sci-Fi","2:40 hrs",{{"10:00 AM",ROWS*COL},{"02:30 PM",ROWS*COL},{"07:00 PM",ROWS*COL}}},
		{"Spider-Man","Fantasy","2:28 hrs",{{"12:30 PM",ROWS*COL},{"5:30 PM",ROWS*COL},{"10:15 PM",ROWS*COL}}},
		{"Shershaah","War","2:15 hrs",{{"10:15 AM",ROWS*COL},{"03:00 PM",ROWS*COL},{"08:45 PM",ROWS*COL}}},
		{"Zindagi Na Milegi Dobara","Adventure","3:00 hrs",{{"09:00 AM",ROWS*COL},{"02:30 PM",ROWS*COL},{"07:15 PM",ROWS*COL}}}
	};

vector<Price> prices=
	{
		{"Standard",700},{"Premium",1200},{"Luxury",2000}
	};

vector<Food> foodMenu={
    {"Popcorn",500},
    {"Coke",150},
    {"Nachos",200},
    {"French Fries",100},
    {"Ice cream",170}};

vector <Theatre> theatre={
	{"Cue Cinema-Johar Town","Johar Town",{movies[0],movies[2],movies[4]}},
	{"Cue Cinema-Model Town","Model Town",{movies[1],movies[5],movies[6]}},
	{"Cue Cinema-Bahria Town","Bahria Town",{movies[3],movies[7],movies[9]}},
	{"Cue Cinema-Wapda Town","Wapda Town",{movies[1],movies[3],movies[8]}},
	{"Cue Cinema-Muslim Town","Muslim Town",{movies[0],movies[5],movies[7]}},
	{"Cue Cinema-DHA","DHA",{movies[2],movies[6],movies[9]}}
};

void BookingTickets(vector<Theatre>& theatre)
{
	BookingHistory bookingHistory;

	int moviesChoice=-1,timeSlot=-1,theatreChoice=-1;
	string customerName;
	cout<<"Customer Name: ";
	cin>>customerName;

	if (theatre.empty()) {
		cout << "No theatres available.\n";
		return;
	}

	cout<<"Which Theatre would you like to choose:\n";
	for(int i=0;i<theatre.size();i++)
	{
		cout<<i+1<<"."<<theatre[i].name<<"("<<theatre[i].location<<")"<<endl;
	}
	cin>>theatreChoice;
	if(!(theatreChoice >= 1 && theatreChoice <=theatre.size()))
	{
		cout<<"Invalid theatre selection\n";
		return;
	}

	if (theatre[theatreChoice - 1].movies.empty()) {
		cout << "No movies available in selected theatre.\n";
		return;
	}

	cout<<"Movies Available at this Theatre are:\n";
	for(int i=0;i< theatre[theatreChoice - 1].movies.size();i++)
	{
		cout<<i+1<<"."<<theatre[theatreChoice - 1].movies[i].title<<"("<<theatre[theatreChoice - 1].movies[i].genre<<")\n";
	}
	cout<<endl;
	cin>>moviesChoice;
	if (!(moviesChoice >= 1 && moviesChoice <= theatre[theatreChoice - 1].movies.size())) {
		cout << "Invalid movie selection\n";
		return;
	}

	cout<<"You chose:";
	cout<<theatre[theatreChoice - 1].movies[moviesChoice-1].title<<endl;

	if (theatre[theatreChoice - 1].movies[moviesChoice - 1].showtimes.empty()) {
		cout << "No showtimes available for this movie.\n";
		return;
	}

	cout<<"Available Times:\n";
	for(int j=0;j<theatre[theatreChoice - 1].movies[moviesChoice-1].showtimes.size();j++)
	{
		cout<<j+1<<"."<<theatre[theatreChoice - 1].movies[moviesChoice-1].showtimes[j].time<<"-Seats Available:"<<theatre[theatreChoice - 1].movies[moviesChoice-1].showtimes[j].availableSeats<<endl;
	}
	cout<<"Which time slot would you like to choose:"<<endl;
	cin>>timeSlot;

	if (!(timeSlot >= 1 && timeSlot <= theatre[theatreChoice - 1].movies[moviesChoice - 1].showtimes.size())) {
		cout << "Invalid time slot.\n";
		return;
	}

	cout<<"You chose:"<<theatre[theatreChoice - 1].movies[moviesChoice-1].showtimes[timeSlot-1].time<<endl;

	int availableSeats=theatre[theatreChoice - 1].movies[moviesChoice-1].showtimes[timeSlot-1].availableSeats;
	cout<<"Seats Available:"<<availableSeats<<endl;
	cout<<"\nSeating Plan:"<<endl;
	theatre[theatreChoice - 1].movies[moviesChoice-1].showtimes[timeSlot - 1].displayGrid();

	int numTickets=-1,paymentMethod=-1,pin=-1,totalBill=-1,ticketType=-1,singleTicketPrice=-1;
	string phoneNumber=" ";
	cout <<"\nNumber of Tickets you want:";
	cin>>numTickets;
	if (numTickets <= 0) {
		cout << "You must book at least 1 ticket.\n";
		return;
	}
	if (numTickets > theatre[theatreChoice - 1].movies[moviesChoice-1].showtimes[timeSlot-1].availableSeats) {
		cout << "Not enough seats available!\n";
		return;
	}

	cout<<"\nChoose Seat Type:"<<endl;
	for(int i=0;i<prices.size();i++)
	{
		cout<<i+1<<". "<<prices[i].type<<"-Price: Rs"<<prices[i].price<<endl;
	}
	cin>>ticketType;

	if (!(ticketType >= 1 && ticketType <= prices.size())) {
		cout << "Invalid ticket type selection.\n";
		return;
	}

	singleTicketPrice=prices[ticketType-1].price;
	vector<string> seats;
	for(int i=0 ; i<numTickets ; i++)
	{
		while(true)
		{
			string Seat;
			cout<<"Choose Seat: (A3,G6):";
			cin>>Seat;
			if (Seat.length() < 2) {
				cout << "Invalid seat input. Try again.\n";
				continue;
			}
			char rowChar=toupper(Seat[0]);
			int colIndex;
			try {
				colIndex = stoi(Seat.substr(1));
			} catch (...) {
				cout << "Invalid column number. Try again.\n";
				continue;
			}
			int rowIndex=rowChar-'A';
			if (rowChar < 'A' || rowChar >= 'A' + ROWS || colIndex < 0 || colIndex >= COL) {
            cout << "Invalid seat! Valid rows: A-G and columns: 0-9. Try again.\n";
            continue;
            }

			if(theatre[theatreChoice - 1].movies[moviesChoice - 1].showtimes[timeSlot - 1].grid[rowIndex][colIndex]=="X")
			{
				cout<<"Seat already booked!!choose another seat!!"<<endl;
				continue;
			}
			seats.push_back(Seat);
			theatre[theatreChoice - 1].movies[moviesChoice - 1].showtimes[timeSlot - 1].updateGrid(rowIndex,colIndex,"X");
			break;
		}
	}
	cout<<"\nSEAT BOOKED!!!!Updated Seating Plan"<<endl;
	theatre[theatreChoice - 1].movies[moviesChoice - 1].showtimes[timeSlot - 1].displayGrid();

	cout<<"\nTotal Amount to Pay";
	totalBill=numTickets*singleTicketPrice;

	string pinStr=" ";
	cout<<"\nChoose Payment Method:\n1.EasyPaisa\n2.Card\n3.Wallet\n4.Cash\n";
	cin>>paymentMethod;

	if (!(paymentMethod >= 1 && paymentMethod <= 4)) {
		cout << "Invalid payment method selected.\n";
		return;
	}

	switch(paymentMethod)
	{
		case 1:
			cout<<"---EasyPaisa Payment---"<<endl;
			cout<<"Enter your registered Phone Number:";
			cin>>phoneNumber;
			cout<<"Enter 4-digit EasyPaisa Pin:";
			cin>>pin;
			pinStr=to_string(pin);
			if(pinStr.length()==4)
			{
				cout<<"Payment successful via EasyPaisa..."<<endl;
			}
			else
			{
				cout<<"Invalid Pin. Payment Failed"<<endl;
				return;
			}
			break;
		case 2:
			cout<<"---Payment Via Card---"<<endl;
			cout<<"Enter your Card Number:";
			cin>>phoneNumber;
			cout<<"Enter 4-digit Card Pin:";
			cin>>pin;
			pinStr=to_string(pin);
			if(pinStr.length()==4)
			{
				cout<<"Payment successful via Card..."<<endl;
			}
			else
			{
				cout<<"Invalid Pin. Payment Failed"<<endl;
				return;
			}
			break;
		case 3:
			cout<<"---Payment Via Wallet---"<<endl;
			cout<<"Enter Wallet ID:";
			cin>>phoneNumber;
			cout<<"Enter 4-digit Wallet Pin:";
			cin>>pin;
			pinStr=to_string(pin);
			if(pinStr.length()==4)
			{
				cout<<"Payment successful via Wallet..."<<endl;
			}
			else
			{
				cout<<"Invalid Pin. Payment Failed"<<endl;
				return;
			}
			break;
		case 4:
			cout<<"---Payment Via Cash---"<<endl;
			cout<<"Pay the cash at counter"<<endl;
			break;
	}

	cout<<"Booking Successful!!!"<<endl;

	theatre[theatreChoice - 1].movies[moviesChoice-1].showtimes[timeSlot-1].availableSeats-=numTickets;

	BookingHistory booking
	{
		static_cast<int>(BookingHistory::bookingList.size()) + 1,
		customerName,
		theatre[theatreChoice - 1].movies[moviesChoice-1].title,
		theatre[theatreChoice - 1].movies[moviesChoice-1].showtimes[timeSlot-1].time,
		numTickets,
		prices[ticketType-1].type,
		totalBill,
		(paymentMethod == 1) ? "EasyPaisa" :
		(paymentMethod == 2) ? "Card" :
		(paymentMethod == 3) ? "Wallet" : "Cash",
		seats
	};

	BookingHistory::bookingList.push_back(booking);
}


const int tcount = 6;
int distanceMatrix[tcount][tcount] = {
    {0, 5, 10, 15, 20, 25},
    {5, 0, 8, 12, 18, 22},
    {10, 8, 0, 6, 14, 17},
    {15, 12, 6, 0, 9, 11},
    {20, 18, 14, 9, 0, 7},
    {25, 22, 17, 11, 7, 0}
};

vector<int> dijkstra(int start) {
    vector<int> dist(tcount, 1000000);
    vector<bool> visited(tcount, false);
    dist[start] = 0;

    for (int i = 0; i < tcount; i++) {
        int u = -1;
        int minDist = 1000000;
        for (int j = 0; j < tcount; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visited[u] = true;
        for (int v = 0; v < tcount; v++) {
            if (!visited[v] && distanceMatrix[u][v] != 0 && dist[u] + distanceMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + distanceMatrix[u][v];
            }
        }
    }
    return dist;
}

int findNearestTheater(int start) {
    vector<int> distances = dijkstra(start);
    int minDist = 1000000;
    int nearest = -1;
    for (int i = 0; i < tcount; i++) {
        if (i != start && distances[i] < minDist) {
            minDist = distances[i];
            nearest = i;
        }
    }
    return nearest;
}

void ShowNearestTheater() {
    cout << "Choose your current theater location:\n";
    for (int i = 0; i < theatre.size(); i++) {
        cout << i + 1 << ". " << theatre[i].name << " (" << theatre[i].location << ")\n";
    }
    int currentIndex;
    cin >> currentIndex;
    if (currentIndex < 1 || currentIndex > theatre.size()) {
        cout << "Invalid theater choice\n";
        return;
    }
    currentIndex--; // zero based index
    int nearestIndex = findNearestTheater(currentIndex);
    if (nearestIndex == -1) {
        cout << "No nearby theaters found.\n";
    } else {
        cout << "Nearest theater to " << theatre[currentIndex].name << " is:\n";
        cout << theatre[nearestIndex].name << " located at " << theatre[nearestIndex].location << endl;
    }
}

RatingNode *insert(RatingNode *root,float rating,string name)
{
    if (root == NULL)
        return new RatingNode(rating, name);

    if (rating < root->rating)
        root->left = insert(root->left, rating, name);
    else
        root->right = insert(root->right, rating, name);

    return root;
}
RatingNode *ratingRoot=NULL;

void searchRatingsByName(RatingNode* root, string& name, bool &found, float& sum, int& cont) {
    if (root == NULL) {
        return;
    }
    searchRatingsByName(root->left, name, found, sum, cont);

    if (root->movieName == name) {
        cout << "Rating for " << name << ": " << root->rating << endl;
        sum += root->rating;
        cont++;
        found = true;
    }

    searchRatingsByName(root->right, name, found, sum, cont);
}



void searchRatings() {
    cout << "Choose the Movie you want to Search Ratings for:\n";
    for (int i = 0; i < movies.size(); i++) {
        cout << i + 1 << ". " << movies[i].title << endl;
    }
    int choice;
    cout << "Enter the movie number to search: ";
    cin >> choice;
    if (choice < 1 || choice > movies.size()) {
        cout << "Invalid choice.\n";
        return;
    }
    bool found = false;
    float sum = 0;
    int cont = 0;
    cout << "---Ratings for " << movies[choice - 1].title << "---" << endl;
    searchRatingsByName(ratingRoot, movies[choice - 1].title, found, sum, cont);
    if (!found) {
        cout << "No ratings found yet!\n";
    } else {
        cout << "Average rating: " << (sum / cont) << endl;
    }
}


void RateMovie()
{
	cout<<"Choose the Movie you watch:\n";
	for (int i = 0; i < movies.size(); i++) {
        cout << i + 1 << ". " << movies[i].title << endl;
    }
    int choice;
    cout << "Enter the movie number to ratings:\n ";
    cin >> choice;
    if (choice < 1 || choice > movies.size()) {
        cout << "Invalid choice.\n";
        return;
    }
    float userRating;
    cout << "Enter your rating (0.0 to 5.0): \n";
    cin >> userRating;
    while (userRating < 0.0 || userRating > 5.0) {
    cout << "Invalid!Should have entered a rating between 0.0 and 5.0!!! ";
    return;
}
    ratingRoot=insert(ratingRoot,userRating,movies[choice-1].title);
    cout<<"Thank you for your review regarding "<<movies[choice-1].title<<"!!! \n";
}


queue<Order> foodQueue;

void foodOrder()
{
    string customerName;
    cout << "Enter customer name: ";
    cin >> customerName;
    Order order(customerName);
    char add;
    do {
        cout << "---Food Menu---\n";
        for (int i = 0; i < foodMenu.size(); i++) {
            cout << i + 1 << ". " << foodMenu[i].name << " - Rs " << foodMenu[i].price << endl;
        }
        int choice;
        cout << "Enter item number to order: ";
        cin >> choice;
        if (choice >= 1 && choice <= foodMenu.size()) {
            order.items.push_back(foodMenu[choice - 1]);
            order.totalBill += foodMenu[choice - 1].price;
            cout << "Item added.\n";
        } else {
            cout << "Invalid choice.\n";
            return;
        }
        cout << "Add more items? (y/n): ";
        cin >> add;
    } while (add == 'y' || add == 'Y');

    foodQueue.push(order);
    cout << "Order placed successfully for " << customerName << endl;
}

void serveOrder() {
    if (foodQueue.empty()) {
        cout << "No food orders in the queue.\n";
        return;
    }

    Order currentOrder = foodQueue.front();
    foodQueue.pop();

    cout << "--- Serving Order ---\n";
    cout << "Customer: " << currentOrder.customerName << endl;
    for (Food item : currentOrder.items) {
        cout << "- " << item.name << " Rs " << item.price << endl;
    }
    cout << "Total Bill: Rs " << currentOrder.totalBill << endl;
}

void displayOrders() {
    if (foodQueue.empty()) {
        cout << "No food orders in queue.\n";
        return;
    }
    cout << "\n--- Food Orders in Queue ---\n";
    queue<Order> tempQueue = foodQueue;
    while (!tempQueue.empty()) {
        Order order = tempQueue.front();
        cout << "Customer: " << order.customerName << "\n";
        cout << "Items Ordered:\n";
        for (const Food& food : order.items) {
            cout << "  - " << food.name << " (Rs. " << food.price << ")\n";
        }
        cout << "Total Bill: Rs. " << order.totalBill << "\n";
        cout << "--------------------------\n";
        tempQueue.pop();
    }
}


int main()
{
	for(auto &movie : movies) {
		movie.createGrids();
	}

	int choice=-1;
	cout<<"---Welcome to Cue Cinema Booking System---"<<endl;
	while(choice!=0)
	{
		cout<<"\nMenu\n";
		cout<<"1. Book Tickets\n";
		cout<<"2. Cancel Booking\n";
		cout<<"3. Display Booking History\n";
		cout<<"4. Find Nearest Theater\n";
		cout<<"5. Dislay Movies and Showtimes\n";
		cout<<"6. Rate a Movie\n";
		cout<<"7. Show Movie Ratings By Name\n";
		cout<<"8. Place Order\n";
		cout<<"9. Serve Next Order\n";
		cout<<"10. Display Food Orders\n";
		cout<<"0. Exit\n";

		cin>>choice;
		switch(choice)
		{
			case 1:
				BookingTickets(theatre);
				break;
			case 2:
				BookingHistory::cancelBooking(movies);
				break;
			case 3:
				BookingHistory::displayHistory();
				break;
            case 4:
                ShowNearestTheater();
                break;
            case 5:
            	for (auto &movie : movies) {
        	movie.displayMovieAndShowtimes();
   			 }
   				break;
   			case 6:
   				RateMovie();
   				break;
   			case 7:
   				searchRatings();
   				break;
   			case 8:
   				foodOrder();
   				break;
   			case 9:
   				serveOrder();
   				break;
   			case 10:
   				displayOrders();
   				break;
			case 0:
				cout<<"Thanks for using Cue Cinema Booking System. Goodbye!"<<endl;
				exit(0);
			default:
				cout<<"Invalid choice"<<endl;
		}
	}
	return 0;
}
