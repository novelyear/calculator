#include"calculate.h"
#include <cmath>

bool IsOperator(char c)//判断运算符
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '!' || c == 'v')
        return true;
    else
        return false;
}

bool IsDigit(char c)//判断数字
{
    if (c >= '0'&&c <= '9')
        return true;
    else
        return false;
}

double ReadValue(std::string::iterator &it)//读取数
{
    double result(0);
    int power(0);

    while (IsDigit(*it))
    {
        result = result * 10 + (*it - '0');
        ++it;
    }

    if (*it == '.')
    {
        ++it;
        while (IsDigit(*it))
        {
            result = result * 10 + (*it - '0');
            ++it;
            ++power;
        }
    }
    return result / pow(10, power);
}

//?????
int Priority(char c)//划定优先级
{
    if (c == 'v' || c == '!')
        return 4;
    if (c == 'm')
        return 3;
    if (c == '(')
        return 0;

    if (c == '+' || c == '-')
        return 1;

    if (c == '*' || c == '/')
        return 2;
    else
        return -1;
}
double factorial(int m)//阶乘
{
    double result = 1;
    for(int i = m; i > 0; i--){
        result *= i;
    }
    return result;
}

std::string Postfix(const std::string &expr)//中缀表达式转为后缀表达式
{
    std::string postfix;
    std::stack<char> cstack;

    auto it = expr.begin();
    while (it != expr.end())
    {
        if (IsDigit(*it) || *it == '.')//数字或点，直接入串
        {
            postfix.push_back(*it);
        }
        else
            if (*it == '(')// '('直接入栈
                cstack.push(*it);
            else
                if (*it == ')')// 若右括号，
                {
                    while (cstack.top() != '(')//直到出栈的为左括号
                    {
                        postfix.push_back(cstack.top());
                        cstack.pop();
                    }
                    cstack.pop();//左括号也出来
                }
                else
                    if (IsOperator(*it))//运算符
                    {
                        postfix.push_back(' ');//遇到运算符先分隔
                        while (!cstack.empty() && (Priority(*it) <= Priority(cstack.top())))//优先级比较
                        {
                            postfix.push_back(cstack.top());
                            cstack.pop();
                        }
                        cstack.push(*it);
                    }
        ++it;
    }
    postfix.push_back(' ');//最后一个元素
    while (!cstack.empty())
    {
        postfix.push_back(cstack.top());
        cstack.pop();
    }
    return postfix;
}


double PostfixValue(std::string &expr)//后缀表达式求值
{

    std::stack<double> dstack;
    double a, b;
    auto it = expr.begin();
    while (it != expr.end())
    {
        if (IsDigit(*it))//数字直接入栈
        {
            dstack.push(ReadValue(it));
        }
        else
            if (*it == ' ')//空格跳过
            {
                ++it;
                continue;
            }
            else
                if (*it == '+')
                {
                    b = dstack.top();
                    dstack.pop();
                    a = dstack.top();
                    dstack.pop();
                    dstack.push(a + b);
                    ++it;
                }
                else
                    if (*it == '-')
                    {
                        b = dstack.top();
                        dstack.pop();
                        a = dstack.top();
                        dstack.pop();
                        dstack.push(a - b);
                        ++it;
                    }
                    else
                        if (*it == '*')
                        {
                            b = dstack.top();
                            dstack.pop();
                            a = dstack.top();
                            dstack.pop();
                            dstack.push(a * b);
                            ++it;
                        }
                        else
                            if (*it == '/')
                            {
                                b = dstack.top();
                                dstack.pop();
                                a = dstack.top();
                                dstack.pop();
                                dstack.push(a / b);
                                ++it;
                            }
                            else
                                if (*it == '!')//阶乘
                                {
                                     a = dstack.top();
                                     dstack.pop();
                                     b = factorial(int(a));
                                     dstack.push(b);//运算完毕后再次入栈
                                     ++it;
                                }
                                else
                                    if (*it == '^')//乘方
                                    {
                                        b = dstack.top();
                                        dstack.pop();
                                        a = dstack.top();
                                        dstack.pop();
                                        dstack.push(pow(a,b));
                                        ++it;
                                    }
                                    else
                                        if (*it == 'v')//开方
                                        {
                                            b = dstack.top();
                                            dstack.pop();
                                            a = std::sqrt(b);
                                            dstack.push(a);
                                            ++it;
                                        }
    }
    a = dstack.top();
    dstack.pop();
    return a;
}


bool IsValid(const QString &Qstr)//
{
    std::string expr=Qstr.toStdString();
    int left=0,right=0;
    if(expr.back() != '!' && IsOperator(expr.back()))//最后一个是运算符，非法
        return false;
    for(auto &c:expr)
    {
        if(!IsDigit(c)&&!IsOperator(c)&&c!='.')
        {
            if(c=='(')
                ++left;
            else if(c==')')
                    ++right;
            else
            return true;
        }
    }
    if(left!=right)
        return false;
    return true;
}

LargeNumber ReadValueLarge(std::string::iterator &it)//读取值
{
    LargeNumber result("0");
    while (IsDigit(*it))
    {
        result = result*LargeNumber("10") + LargeNumber(*it);
        ++it;
    }
    return result;
}

LargeNumber PostfixValueLarge(std::string &expr)//后缀表达式计算
{
    std::stack<LargeNumber> Lstack;
    LargeNumber a, b;
    auto it = expr.begin();
    while (it!=expr.end())
    {
        if (IsDigit(*it))
            Lstack.push(ReadValueLarge(it));
        else
            if (*it == ' ')
                ++it;
            else
                if (*it == '+')
                {
                    b = Lstack.top();
                    Lstack.pop();
                    a = Lstack.top();
                    Lstack.pop();
                    Lstack.push(a + b);
                    ++it;
                }
                else
                    if (*it == '-')
                    {
                        b = Lstack.top();
                        Lstack.pop();
                        a = Lstack.top();
                        Lstack.pop();
                        Lstack.push(a - b);
                        ++it;
                    }
                    else
                        if (*it == '*')
                        {
                            b = Lstack.top();
                            Lstack.pop();
                            a = Lstack.top();
                            Lstack.pop();
                            Lstack.push(a * b);
                            ++it;
                        }
                        else
                            if (*it == '/')
                            {
                                b = Lstack.top();
                                Lstack.pop();
                                a = Lstack.top();
                                Lstack.pop();
                                Lstack.push(a / b);
                                ++it;
                            }

    }
    return Lstack.top();
}
QString CalculateResult(const QString &Qstr)
{
    std::string expr=Qstr.toStdString();//将Qstring转为stdstring
    expr=Postfix(expr);//stdstring转为后缀表达式
    double result=PostfixValue(expr);//计算后缀表达式值，返回double
    return QString::number(result,'f',6);//double转成QString返回
}

QString CalculateResultLarge(const QString &Qstr)
{
    std::string expr=Qstr.toStdString();//将QString转为stdstring
    expr=Postfix(expr);//stdstring转为后缀表达式
    LargeNumber result=PostfixValueLarge(expr);//使用大数计算后缀表达式,返回Largenumber类
    return QString::fromStdString(result.number());//使用stdstring转换为QString返回
}
