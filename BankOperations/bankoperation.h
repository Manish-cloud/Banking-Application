#ifndef BANKOPERATION_H
#define BANKOPERATION_H

#include <QMainWindow>

namespace Ui {
class BankOperation;
}

class BankOperation : public QMainWindow
{
    Q_OBJECT

public:
    explicit BankOperation(QWidget *parent = 0);
    ~BankOperation();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::BankOperation *ui;
};

#endif // BANKOPERATION_H
