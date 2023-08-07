#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculate.h"
using std::string;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("标准计算器"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_0_clicked()
{
    expression+="0";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_1_clicked()
{
    expression+="1";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_2_clicked()
{
    expression+="2";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_3_clicked()
{
    expression+="3";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_4_clicked()
{
    expression+="4";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_5_clicked()
{
    expression+="5";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_6_clicked()
{
    expression+="6";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_7_clicked()
{
    expression+="7";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_8_clicked()
{
    expression+="8";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_9_clicked()
{
    expression+="9";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_point_clicked()
{
    expression+=".";
    ui->lineEdit->setText(expression);
}


void MainWindow::on_pushButton_add_clicked()
{
    expression+="+";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_subtract_clicked()
{
    expression+="-";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_multiply_clicked()
{
    expression+="*";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_divide_clicked()
{
    expression+="/";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_pow_clicked()
{
    expression+="^";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_fact_clicked()
{
    expression+="!";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_sqrt_clicked()
{
    expression+="v";
    ui->lineEdit->setText(expression);
}
void MainWindow::on_pushButton_leftbracket_clicked()
{
    expression+="(";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_rightbracket_clicked()
{
    expression+=")";
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_backspace_clicked()
{
    expression.chop(1);
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_allclear_clicked()
{
    expression.clear();
    ui->lineEdit->setText(expression);
}

void MainWindow::on_pushButton_equal_clicked()
{
    //公式为空，不做任何操作
    if(!ui->lineEdit->text().isEmpty())
    {
        expression=ui->lineEdit->text();
        if(!IsValid(expression))//公式不合法，不做任何操作
        {
             QMessageBox::warning(this,tr("计算式出错"),tr("计算式存在错误，请正确输入计算式"));
        }
        else
        {
            if(CalculateMode==1)
            {

                expression=CalculateResult(expression);
            }

            else
                if(CalculateMode==2)
                {
                    expression=CalculateResultLarge(expression);
                }
            ui->lineEdit->setText(expression);
        }

    }
}
void MainWindow::on_action_2_triggered()
{
    CalculateMode=2;
    ui->pushButton_point->setEnabled(false);
    ui->pushButton_pow->setEnabled(false);
    ui->pushButton_fact->setEnabled(false);
    ui->pushButton_sqrt->setEnabled(false);
    this->setWindowTitle(tr("大数计算器"));
}

void MainWindow::on_action_triggered()
{
    ui->pushButton_pow->setEnabled(true);
    ui->pushButton_fact->setEnabled(true);
    ui->pushButton_sqrt->setEnabled(true);
    CalculateMode=1;
    ui->pushButton_point->setEnabled(true);
    this->setWindowTitle(tr("标准计算器"));
    statusTip().clear();
}

void MainWindow::on_action_3_triggered()
{
   Instructions Instruction(this);
   Instruction.show();
   Instruction.exec();
}
