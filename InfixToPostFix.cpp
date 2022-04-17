#include <QCoreApplication>
#include<QDebug>
#include<QStack>

bool isValidExpression(const QString & expression);
QString infixToPostFix(const QString & infixString,bool & ok);

QMap<QChar,int> operatorsPrecedenceMap({
                                           QPair<QChar,int>('+',1),
                                            QPair<QChar,int>('-',1),

                                            QPair<QChar,int>('*',2) ,
                                            QPair<QChar,int>('/',2) ,

                                            QPair<QChar,int>('^',3)
                                       });

QVector<QChar> operators({ '+' ,'-' , '*','/','^'});


bool isOperator(const QChar & symbol){
    return operators.contains(symbol);
}

bool isGreatorOrEqualPrecedence(QChar opInstack  , QChar currentOp ){
       return operatorsPrecedenceMap[opInstack] >= operatorsPrecedenceMap[currentOp];
}


QString infixToPostFix(const QString & infixString,bool & ok){
    QString result;
    QStack<QChar> stack;
    ok = isValidExpression(infixString);
    if(ok){
        foreach(QChar symbol , infixString){

            if(isOperator(symbol)){
                if(stack.isEmpty()) stack.push(symbol);
                else{
                    while(  !stack.isEmpty() && isGreatorOrEqualPrecedence(stack.top() , symbol ) )
                           result.append(stack.pop());
                    stack.push(symbol);
                }
            }
            else if(symbol=='('){
                stack.push('(');
            }
            else if(symbol==')'){
                QChar data = stack.pop();
                result.append(data);

                while(data!='(' ){
                    data = stack.pop();
                    result.append(data);
                }
                result.resize(result.size()-1);
            }
            else{ // operand
                result.append(symbol);
            }

        }
    }

     while(!stack.isEmpty()){
         QChar data = stack.pop();
         if(data!='(' && data!= ')')
         result.append(data);
     }

    return result;
}

bool isValidExpression(const QString & expression){
    if(expression.size()%2!=0){
        QChar first  = *expression.data();
        QChar last =   *(expression.data()+expression.size()-1);
        if(isOperator(first))return false;
        if(isOperator(last)) return false;
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString infixString =  "7+5*3/5^1+(3-2)" ;
    bool ok= false;
    QString result = infixToPostFix(infixString,ok);
    if(!ok) qDebug()<<"Invalid expression";
    else qDebug()<<"Postfix : "<<result;
    if("753*51^/+32-+"==result)qInfo()<<"Test passed";
    return a.exec();
}
