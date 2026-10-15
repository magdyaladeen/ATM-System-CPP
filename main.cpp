
#include <iostream>
#include <string>  
#include  <vector>  
#include  <fstream>  
#include <iomanip>
using   namespace std;         
string  namefile = "Clientfile.txt";
enum enATmmenue {
    QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, checkBalances = 4, logout = 5
};

struct   infooacount
{
    string  accountnumber;
    string  pincode;
    string name;
    string  iphone;
    double  accountbalance = 0;
    bool  markfordelte = false;
};
infooacount    dateClient;  
void     showAtmMenue();   
void ShowQuickWithdrawScreen();   
void ShowNormalWithDrawScreen();   
void         login();
vector<string> splitstring(string S1, string Delim)
{
    vector<string> vString;
    int pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}
infooacount  convortfromstringtostruct(string word, string dlim = "#//#")
{
    infooacount stinffoo;
    vector  <string >  vstring;
    vstring = splitstring(word, dlim);

    stinffoo.accountnumber = vstring[0];
    stinffoo.pincode = vstring[1];
    stinffoo.name = vstring[2];
    stinffoo.iphone = vstring[3];
    stinffoo.accountbalance = stod(vstring[4]); // cast string to 




    return   stinffoo;

}
vector < infooacount>    loaddatefromfile(string  namefile)
{
    fstream   myfile;
    vector  < infooacount>  vdate;
    myfile.open(namefile, ios::in);
    if (myfile.is_open())
    {

        string  line;
        infooacount  date;
        while (getline(myfile, line))
        {
            date = convortfromstringtostruct(line);

            vdate.push_back(date);


        }
        myfile.close();
    }
    return vdate;
}

bool  FindUserByUsernameAndPassword(string nameusers, string password, infooacount& dateusers)
{
    vector < infooacount  >  vdate;
    vdate = loaddatefromfile(namefile);
    for (infooacount& date : vdate)
    {
        if (date.accountnumber == nameusers && date.pincode == password)
        {
            dateusers = date;
            return   true;
        }
    }

    return  false;
}
bool  LoadUserInfo(string nameusers, string password, infooacount& dateusers)
{
    if (FindUserByUsernameAndPassword(nameusers, password, dateusers))
    {
        return   true;
    }
    else
    {

        return   false;
    }
}      
string  convortstrct(infooacount  claint, string     dlim = "#//#")
{

    string s = "";
    s += claint.accountnumber + dlim;
    s += claint.pincode + dlim;
    s += claint.name + dlim;
    s += claint.iphone + dlim;
    s += to_string(claint.accountbalance) + dlim;

    return  s;
}

vector  < infooacount >  saveClientRecord(string namefile, vector < infooacount >  vdate)
{

    fstream  myfile;

    string   line;
    myfile.open(namefile, ios::out);

    if (myfile.is_open())
    {

        for (infooacount& date : vdate)
        {

            if (date.markfordelte == false)
            {

                line = convortstrct(date);

                myfile << line << endl;
            }

        }

        myfile.close();
    }

    return vdate;
}

void  gobacktomenueATm()
{


    cout << "press any key to go back to main menue " << endl;

    system("pause>0");
    system("cls  ");
    showAtmMenue();



}      
void  gobackQuickWithdraw()
{


    cout << "press any key to go back to main menue " << endl;

    system("pause>0");
    system("cls  ");
    ShowQuickWithdrawScreen();



}  
double  ReadDepositAmount()
{


    double  amount;
    cout << "Place enter  Deposit postive  amount ?  ";
    cin >> amount;


    while (amount <= 0)
    {

        cout << "Place enter  Deposit postive  amount ?  ";
        cin >> amount;


    }



    return amount;



}


bool DepositBalancetoClientByAccountNumber(vector < infooacount >  vClient, string nameaccount, double  amount)
{

    char  areyou = 'y';
    cout << "are  you sure you want perfrom this transaction y/n ? ";
    cin >> areyou;

    while (areyou == 'Y' || areyou == 'y')
    {

        for (infooacount& date : vClient)
        {
            if (date.accountnumber == nameaccount)
            {

                date.accountbalance += amount;


                cout << "Done  successsfuly  new balance  " << date.accountbalance << endl;
                saveClientRecord(namefile, vClient);

                return true;
            }

        }
    }
    return false;
}

short QuickAmount(short   option)
{
    short    amount = 0;
    switch (option)
    {
    case 1:
        return  20;
    case 2:
        return 50;
    case  3:
        return 100;
    case 4:
        return 200;
    case 5:
        return 400;
    case  6:
        return 600;
    case 7:
        return 800;
    case 8:
        return 1000;
    default  : 
        return  0;  
    }

}

short  ReadMainMenueATM()
{

    short   num = 0;
    cout << "choose  what do you want to do  ? [1to 6 ] ? ";
    cin >> num;   
    while (num  <  1 || num > 5)
    {


        cout << "choose  what do you want to do  ? [1to 6 ] ? ";
        cin >> num;
 




    }
    return  num;



} 
short  ReadQuickWithdraw()
{

    short   num = 0;
    cout << "choose  what to Withdraw from  [1] to  [8] ? ";
    cin >> num;  
    while (num < 1 || num > 9)
    {
        cout << "choose  what to Withdraw from  [1] to  [8] ? ";
        cin >> num;
    }
    return  num;



}   
int  homanyamountWithdraw()
{


    int  amount;
    cout << "Enter an amount multible of 5 s ?  ";
    cin >> amount;


    while (amount % 5 != 0)
    {

        cout << "Enter an amount multible of 5 s ?  ";
        cin >> amount;

    }
    return amount;


}

void perfromainoptionNormalWithdraw()
{
    int   WithDrawBalance = homanyamountWithdraw();
    while (WithDrawBalance > dateClient.accountbalance)
    {

        cout << "the amount exceeds your balance , make anther choice ." << endl;
        cout << "Press Anykey to continue...";  
        system("pause>0");
        ShowNormalWithDrawScreen();

    }
    vector < infooacount  >   vClient;
    vClient = loaddatefromfile(namefile);

    DepositBalancetoClientByAccountNumber(vClient, dateClient.accountnumber, WithDrawBalance * -1);
    dateClient.accountbalance -= WithDrawBalance;








}
void   PerfromQuickWithdrawOption(short  QuickWithDrawOption)
{ 
    vector < infooacount  >   vClient;
    vClient = loaddatefromfile(namefile);
    if (QuickWithDrawOption == 9)
    {
        return ; 
    } 
    short WithDrawBalance = QuickAmount(QuickWithDrawOption); 
        while (WithDrawBalance > dateClient.accountbalance)
    {
        
        cout << "the amount exceeds your balance , make anther choice ." << endl; 
        cout << "Press Anykey to continue...";
        system("pause>0");
        ShowQuickWithdrawScreen();
    }
    DepositBalancetoClientByAccountNumber(vClient, dateClient.accountnumber, WithDrawBalance * -1);
    dateClient.accountbalance -= WithDrawBalance;




}       
void  PerfromDepositOption()
 { 

    double   DepositAmount = ReadDepositAmount();
    vector < infooacount  >   vClient;
    vClient = loaddatefromfile(namefile);
    DepositBalancetoClientByAccountNumber(vClient, dateClient.accountnumber, DepositAmount);
    dateClient.accountbalance += DepositAmount; 
 }
void   ShowDepositScreen()
{
    system("cls");
    cout << "----------------------------------------------------" << endl;
    cout << "\t Deposit Screen  " << endl;
    cout << "----------------------------------------------------" << endl;    
    PerfromDepositOption();  
}

void   ShowNormalWithDrawScreen()
{
    system("cls");
    cout << "----------------------------------------------------" << endl;
    cout << "\t   Normal  Withdraw   Screen  " << endl;
    cout << "----------------------------------------------------" << endl; 
    perfromainoptionNormalWithdraw();
}
void showBalanceScreen()
{
    system("cls");
    cout << "----------------------------------------------------" << endl;
    cout << "\t Check Balance  Screen " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Your  Balance is " << dateClient.accountbalance << endl;
}

void   ShowQuickWithdrawScreen()
{
    system("cls");
    cout << "----------------------------------------------------" << endl;
    cout << "\t   Quick  Withdraw   Screen  " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "\t [1] 20 \t\t [2] 50 " << endl;
    cout << "\t [3] 100 \t\t [4] 200 " << endl;
    cout << "\t [5] 400 \t \t [6] 600 " << endl;
    cout << "\t [7] 800 \t \t [8] 1000 " << endl;
    cout << "\t [9] Exit " << endl;
    cout << "Your Balance is " << dateClient.accountbalance ;

     PerfromQuickWithdrawOption(ReadQuickWithdraw ()) ;

}
void perfromainoptiontransction(enATmmenue  stcase)
{

    switch (stcase)
    {
    case enATmmenue::QuickWithdraw:
        system("cls");
        ShowQuickWithdrawScreen();
        gobacktomenueATm();
        break;
    case enATmmenue::NormalWithdraw:
        system("cls");
        ShowNormalWithDrawScreen();
        gobacktomenueATm();
        break;
    case  enATmmenue::Deposit:
        system("cls");
        ShowDepositScreen();
        gobacktomenueATm();
        break;
    case  enATmmenue::checkBalances:
        system("cls");
        showBalanceScreen();
        gobacktomenueATm();
        break;
    case enATmmenue::logout:
        system("cls");
        login();

    }

}

void  showAtmMenue()
{

    cout << "\n----------------------------------------------------\n" << endl;
    cout << "\t  ATM Main Menue  Screen  " << endl;
    cout << "\n----------------------------------------------------\n" << endl;
    cout << "\t [1] Quick Withdraw . " << endl;
    cout << "\t [2] Normal Withdraw." << endl;
    cout << "\t [3] Deposit      ." << endl;
    cout << "\t [4] Check Balances . " << endl;
    cout << "\t [5] logout . " << endl;
    perfromainoptiontransction(enATmmenue(ReadMainMenueATM()));
}

void login()
{
    cout << "\n----------------------------------------------------\n" << endl;
    cout << "\t Login Screen " << endl;
    cout << "\n----------------------------------------------------\n" << endl;

    string nameusers;
    string password;
    bool  Login = false;
    do
    {
        if (Login)
        {
            system("cls");

            cout << "Invalid Username / Password ! " << endl;
        }
        cout << "Enter ACcount Number " << endl;
        getline(cin >> ws, nameusers);
        cout << "Enter pinCode " << endl;
        cin >> password;   
        Login = !LoadUserInfo(nameusers, password, dateClient);

    } while (Login);
    system("cls");

    showAtmMenue();

}

int main()
{



    login();   





}

