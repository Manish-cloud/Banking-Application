#include "bankoperation.h"
#include "ui_bankoperation.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <QString>
#include <ctime>
#include "QMessageBox"
#include "QPixmap"

using namespace std;

long long int AccountNumber;
int accountPinNumber;
string accountName;
string accountType;
double accountBalance;
int flag=0;
int flag1=0;

struct Member
{
    string name;
    long long int accountNumber;
    string accountType;
    double balance;
    int pin;
    Member * next;
};
Member * header=NULL;
class Bank
{
public:
    Member * newMember;

        void setDetails(string str1 , string str2);
        void create(string str1 , string str2);
        void display(long long int accNumber, int accPinNumber);
        void deposit(long long int accNum, double amount);
        void withdraw(long long int accNumber, int accPinNumber , double amount);
        static int c;
};
int Bank::c;

Bank acc;

void Bank::setDetails(string str1 , string str2)                                                 //function to accept details
    {
        newMember->name = str1;
        newMember->accountType = str2;
        newMember->accountNumber=10000+c;
        srand(time(0));
        newMember->pin=1000+rand()%8999;
        AccountNumber = newMember->accountNumber;
        accountPinNumber = newMember->pin;
        accountName=newMember->name;
        accountType=newMember->accountType;
        newMember->balance=0;
        newMember->next=NULL;
        c++;
    }

void Bank::create(string str1 , string str2)
    {
        Member * currentNode;
        newMember=new Member;

        setDetails(str1 , str2);

        if(header==NULL)
            header=newMember;

        else
        {
            currentNode=header;
            while(currentNode->next!=NULL)
               {
                    currentNode=currentNode->next;
               }
            currentNode->next=newMember;
        }
    }

void Bank::display(long long accNumber ,int accPinNumber)                                                    //function to display details
    {
       flag=0;
       Member * currentNode=NULL;
       currentNode=header;
        while(currentNode!=NULL)
       {
            if(currentNode->accountNumber == accNumber && currentNode->pin == accPinNumber)
            {
                        flag=1;
                        accountName = currentNode->name;
                        accountBalance = currentNode->balance;
                        break;
            }
            currentNode=currentNode->next;

        }
    }

 void Bank::deposit(long long int accNumber, double amount)                                                   //function to deposit an money
    {
        flag=0;
        Member * currentNode=NULL;
        currentNode=header;

        while(currentNode!=NULL)
        {
             if(currentNode->accountNumber==accNumber)
             {
                        currentNode->balance=currentNode->balance+amount;
                        flag=1;
                        break;
             }
             currentNode=currentNode->next;
         }


    }

   void Bank::withdraw(long long int accNumber, int accPinNumber , double amount)                                                //function to withdraw an money
    {
        flag=0;
        flag1=0;
        Member * currentNode;
        currentNode=header;

        while(currentNode!=NULL)
        {
             if(currentNode->accountNumber==accNumber && currentNode->pin==accPinNumber)
             {
                 flag=1;
                 {
                     if(amount > currentNode->balance )
                     {
                        flag1=1;
                        break;
                     }
                     else
                         currentNode->balance = currentNode->balance - amount;

                 }
                 break;
             }
             currentNode=currentNode->next;
         }
    }

BankOperation::BankOperation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BankOperation)
{
    ui->setupUi(this);
    QPixmap pix (":/resource/img/a.jpg");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();

    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

BankOperation::~BankOperation()
{
    delete ui;
}

void BankOperation::on_pushButton_clicked()             // Account Creation
{
    QString name = ui->lineEdit->text();
    string accName = name.toStdString();
    QString type = ui->lineEdit_2->text();
    string accType = type.toStdString();
    acc.Bank::create(accName , accType);

    long long int accNum = AccountNumber;
    int accPin = accountPinNumber;
    string accname = accountName;
    string acctype = accountType;

    QString AccNum;
    AccNum.setNum(accNum);
    QString AccPin;
    AccPin.setNum(accPin);
    QString Accname = QString::fromStdString(accname);
    QString Acctype = QString::fromStdString(acctype);

    ui->label_25->setText(Accname);
    ui->label_26->setText(Acctype);
    ui->label_7->setText(AccNum);
    ui->label_8->setText(AccPin);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

void BankOperation::on_pushButton_2_clicked()                       // Display Button
{
    bool ok;
    QString accnum = ui->lineEdit_3->text();
    long long int accNum = accnum.toInt(&ok,10);
    QString accpin = ui->lineEdit_4->text();
    int accPin = accpin.toInt(&ok,10);
    acc.Bank::display(accNum,accPin);

    string accname = accountName;
    double accbalance = accountBalance;

    QString AccName = QString::fromStdString(accname);
    QString AccBalance;
    AccBalance.setNum(accbalance);

    if(flag==0)
    {
        QMessageBox::StandardButton reply = QMessageBox::warning(this,"Warning","PLEASE CHECK ACCOUNT NUMBER AND PIN",QMessageBox::Yes);
        if(reply==QMessageBox::Yes)
        {
            AccName.clear();
            AccBalance.clear();
            ui->label_14->setText(AccName);
            ui->label_15->setText(AccBalance);

            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
        }
    }

    else
    {
        ui->label_14->setText(AccName);
        ui->label_15->setText(AccBalance);
    }

    accountName.clear();
    accountBalance=0;
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}


void BankOperation::on_pushButton_3_clicked()                       //Deposit Button
{
    bool ok;
    QString accnum = ui->lineEdit_5->text();
    QString amount = ui->lineEdit_6->text();

    long long int accNum = accnum.toInt(&ok,10);
    double Amount = amount.toInt(&ok,10);
    acc.Bank::deposit(accNum,Amount);

    if(flag==0)
    {
        QMessageBox::StandardButton reply = QMessageBox::warning(this,"Warning","PLEASE CHECK ACCOUNT NUMBER",QMessageBox::Yes);

    }

    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
}


void BankOperation::on_pushButton_4_clicked()                       //Withdraw Button
{
    bool ok;
    QString accnum = ui->lineEdit_7->text();
    QString accpin = ui->lineEdit_8->text();
    QString withdrawamount = ui->lineEdit_9->text();

    long long int accNum = accnum.toInt(&ok,10);
    int accPin = accpin.toInt(&ok,10);
    double withdrawAmount = withdrawamount.toInt(&ok,10);

    acc.Bank::withdraw(accNum , accPin , withdrawAmount);
    if(flag==0)
    {
    QMessageBox::StandardButton reply = QMessageBox::warning(this,"Warning","PLEASE CHECK ACCOUNT NUMBER AND PIN",QMessageBox::Yes);
    if(reply==QMessageBox::Yes)
        {
            ui->lineEdit_7->clear();
            ui->lineEdit_8->clear();
            ui->lineEdit_9->clear();
        }

    }

    if(flag1==1)
    {
        QMessageBox::StandardButton reply = QMessageBox::warning(this,"Warning","INSUFFICIENT BALANCE!!!",QMessageBox::Yes);
        if(reply==QMessageBox::Yes)
            {
                ui->lineEdit_7->clear();
                ui->lineEdit_8->clear();
                ui->lineEdit_9->clear();
            }

    }

    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();

    if(flag==1&&flag1==0)
    {
        ui->label_27->setText("Amount Successfully Withdrawn!!!");
    }
    else
        ui->label_27->setText("Transaction failed!!!");
}

void BankOperation::on_pushButton_5_clicked()
{
    ui->label_25->clear();
    ui->label_26->clear();
    ui->label_7->clear();
    ui->label_8->clear();
}

void BankOperation::on_pushButton_6_clicked()
{
    ui->label_14->clear();
    ui->label_15->clear();
}
