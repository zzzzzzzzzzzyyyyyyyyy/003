#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class formula
{
private:
    char a,b;
    string s;
    stack<double> x;
    stack<string> y;
    vector<char> X;
    vector<double> Y;
    int T;
public:
    void dispose()
    {
        T=-1;
        double num;
        int temp=-1;
        cout<<"> ";
        cin>>s;
        b='0';
        x.push(0);
//        y.push("(");
//        s+=')';
        y.push("=");
        s+=',';
        for(int i=0;i<s.length();i++)
        {
            a=b;
            b=s[i];
            cout<<b<<endl;
            if(b>='0'&&b<='9')
            {
                num=b-'0';
                if(a>='0'&&a<='9')
                {
                    num+=x.top()*10;x.pop();
                }
                x.push(num);
            }
            else if((b>='a'&&b<='z')||(b>='A'&&b<='Z'))
            {
                temp=find(b);
                if(temp==-1)
                {
                    X.push_back(b);
                    Y.push_back(0);
                }
                if(s[i+1]=='='&&s[i+2]!='=')
                {
                    temp=find(b);
                    T=temp;
                }
                else
                {
                    x.push(Y[temp]);
                }
            }
            else if(b=='.')
            {
                double j=0.1;
                for(i++;i<s.length();i++)
                {
                    a=b;
                    b=s[i];
                    cout<<b<<endl;
                    if(b>='0'&&b<='9')
                    {
                        num=b-'0';
                        num=x.top()+num*j;x.pop();
                        x.push(num);
                        j*=0.1;
                    }
                    else
                    {
                        formula_character(i);
                        break;
                    }
                }
            }
            else
            {
                formula_character(i);
            }
        }
        cout<<"> "<<x.top()<<endl;
    }
    int find(char a)
    {
        for(int i=0;i<X.size();i++)
        {
            if(X[i]==a)
            {
                return i;
            }
        }
        return -1;
    }
    void formula_character(int &i)
    {
        double num1,num2,num;
        string p,q;
        p=b;
        if((p=="="&&s[i+1]!='=')||exam(s[i+1])||p=="("||p==")"||p==",")
        {
            ;
        }
        else
        {
            p+=s[++i];
        }
        if(p=="("||p=="=")
        {
            y.push(p);
        }
        else if(p==",")
        {
            while(y.top()!="=")
            {
                q=y.top();y.pop();
                num1=x.top();x.pop();
                num2=x.top();x.pop();
                if(y.top()=="-")
                {
                    num2=0-num2;
                    y.pop();
                    if(y.top()=="("||y.top()=="=")
                    {
                        ;
                    }
                    else
                        y.push("+");
                }
                num=math(q,num1,num2);
                x.push(num);
                cout<<num1<<" "<<num2<<" "<<num<<endl;
            }
            y.pop();
            if(T==-1)
            {
                ;
            }
            else
            {
                Y[T]=x.top();
            }
            cout<<Y[T]<<endl;
        }
        else if(y.top()=="("||y.top()=="="||String(p)>=String(y.top()))
        {
            q=y.top();y.pop();
            if(q=="(")
            {
                if(p==")")
                {
                    ;
                }
                else
                {
                    y.push(q);
                    y.push(p);
                }
            }
            else if(q=="=")
            {
                if(p==",")
                {
                    ;
                }
                else
                {
                    y.push(q);
                    y.push(p);
                }
            }
            else
            {
                y.push(q);
                y.push(p);
            }
        }
        else
        {
            while(y.top()=="("||y.top()=="="||String(p)<String(y.top())||p==",")
            {
                q=y.top();y.pop();
                if(q=="(")
                {
                    if(p==")")
                    {
                        break;
                    }
                    y.push(q);
                    break;
                }
                else if(q=="=")
                {
                    if(p==",")
                    {
                        break;
                    }
                    y.push(q);
                    break;
                }
                else
                {
                    if(q=="=")
                    {
                        if(T==-1)
                        {
                            ;
                        }
                        else
                            Y[T]=x.top();
                        cout<<Y[T]<<endl;
                    }
                    else
                    {
                        num1=x.top();x.pop();
                        num2=x.top();x.pop();
                        if(y.top()=="-")
                        {
                            num2=0-num2;
                            y.pop();
                            if(y.top()!="("||y.top()!="=")
                            {
                                y.push("+");
                                cout<<"改"<<endl;
                            }
                            cout<<num2<<endl;
                        }
                        num=math(q,num1,num2);
                        x.push(num);
                        cout<<num1<<" "<<num2<<" "<<num<<endl;
                    }
                }
            }
            if(p==")"||p==","||p=="=")
            {
                ;
            }
            else
            {
                y.push(p);
            }
        }
    }
    bool exam(char a)
    {
        if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9')||a=='('||a==')'||a==',')
        {
            return true;
        }
        else
            return false;
    }
    int String(string a)
    {
        if(a=="("||a==")")
        {
            return 0;
        }
        else if(a=="="||a==",")
        {
            return 1;
        }
        else if(a=="&&"||a=="||")
        {
            return 2;
        }
        else if(a=="!="||a=="=="||a==">"||a=="<"||a==">="||a=="<=")
        {
            return 3;
        }
        else if(a=="+="||a=="-="||a=="*="||a=="/=")
        {
            return 4;
        }
        else if(a=="+"||a=="-")
        {
            return 5;
        }
        else if(a=="*"||a=="/"||a=="%")
        {
            return 6;
        }
        else
            return -1;
    }
    double math(string a,double x,double y)
    {
        if(a=="+")
        {
            return y+x;
        }
        else if(a=="-")
        {
            return y-x;
        }
        else if(a=="*")
        {
            return y*x;
        }
        else if(a=="/")
        {
            return y/x;
        }
        else if(a=="%")
        {
            return (int)y%(int)x;
        }
        else if(a=="+=")
        {
            return y+x;
        }
        else if(a=="-=")
        {
            return y-x;
        }
        else if(a=="*=")
        {
            return y*x;
        }
        else if(a=="/=")
        {
            return y/x;
        }
        else if(a==">")
        {
            if(y>x)
            {
                return 1;
            }
            else
                return 0;
        }
        else if(a=="<")
        {
            if(y<x)
            {
                return 1;
            }
            else
                return 0;
        }
        else if(a==">=")
        {
            if(y>=x)
            {
                return 1;
            }
            else
                return 0;
        }
        else if(a=="<=")
        {
            if(y<=x)
            {
                return 1;
            }
            else
                return 0;
        }
        else if(a=="&&")
        {
            if(y==1&&x==1)
            {
                return 1;
            }
            else
                return 0;
        }
        else if(a=="||")
        {
            if(y==1||x==1)
            {
                return 1;
            }
            else
                return 0;
        }
        else if(a=="!=")
        {
            if(y!=x)
            {
                return 1;
            }
            else
                return 0;
        }
        else if(a=="==")
        {
            if(y==x)
            {
                return 1;
            }
            else
                return 0;
        }
        else
        {
            cout<<"错误"<<endl;
        }
    }
};


int main()
{
    formula f;
    while(1)
    {
        f.dispose();
    }
    return 0;
}
