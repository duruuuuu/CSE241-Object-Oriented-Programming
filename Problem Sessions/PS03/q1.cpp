#include <iostream>

using namespace std;

class HotDogStand
{
private:
    int idNo;
    int soldToday;
    static int totalHotDogsSold;

public:
    // Constructors
    HotDogStand() {} // Default Constructor

    HotDogStand(int id, int sold) // Constructor which initializes stand's ID number and # of hotdogs sold today
    {
        idNo = id;
        soldToday = sold;

        totalHotDogsSold += sold;
    }

    // Member Functions
    void JustSold()
    {
        // Increments the stand'd sold number and the total sold amount
        cout << "stand #" << idNo << " just made a sale!\n"
             << endl;
        soldToday++;
        totalHotDogsSold++;
    }

    // Getter functions
    int get_hotdogs_sold() { return soldToday; }
    int get_total_hotdogs_sold() { return totalHotDogsSold; }
    int get_id() { return idNo; }
};

// Initializing static integer
int HotDogStand::totalHotDogsSold = 0;

int main()
{
    HotDogStand stand1(1, 0);
    HotDogStand stand2(2, 100);
    HotDogStand stand3(3, 23);

    cout << "Stand 1 sold today: " << stand1.get_hotdogs_sold() << endl;
    cout << "Stand 2 sold today: " << stand2.get_hotdogs_sold() << endl;
    cout << "Stand 3 sold today: " << stand3.get_hotdogs_sold() << endl;
    cout << "Total number of hotdogs sold ever by everyone: " << stand1.get_total_hotdogs_sold() << endl;

    stand1.JustSold();

    cout << "Stand 1 sold today: " << stand1.get_hotdogs_sold() << endl;

    stand2.JustSold();
    stand2.JustSold();
    stand3.JustSold();
    stand1.JustSold();
    stand3.JustSold();
    stand3.JustSold();

    cout << "==============\nThe hotdog stands are now closed." << endl;
    cout << "Stand 1 sold today: " << stand1.get_hotdogs_sold() << endl;
    cout << "Stand 2 sold today: " << stand2.get_hotdogs_sold() << endl;
    cout << "Stand 3 sold today: " << stand3.get_hotdogs_sold() << endl;
    cout << "Total number of hotdogs sold ever by everyone: " << stand1.get_total_hotdogs_sold() << endl;
}