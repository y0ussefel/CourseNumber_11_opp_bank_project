
#include <iostream>
#include "clsInputValidate.h"
#include "clsDate.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include "clsMainScreen.h"
#include "clsLoginScreen.h"
#include <iomanip>
using namespace std;


template <typename T,typename T2> T MyMax(T message, T Number)
{
    T Tst = message + to_string(Number);
    return Tst;
}
int main()
{

   
    //clsMainScreen::ShowMainMenue();
   while (true)
    {
      if(!clsLoginScreen::ShowLoginScreen())
          break;

  }
    //clsTransferLogScreen::ShowTransferLogScreen();
    //clsLoginRegisterScreen::ShowLoginRegisterScreen();
    //UpdateClient();
    //AddNewClient();
    //DeleteClient();
    //ShowTotalBalances();
   // ShowClientsList();
    system("pause>0");
    return 0;

}

