#include <QCoreApplication>
#include<QHash>
#include<QList>

class Block{
public:
    Block(uint prevBlockSign,QString transactions){
        m_prevBlockSign = prevBlockSign;
        m_transactions = transactions;
        m_signature = hash();
    }

    bool isEmpty()const{
        return m_transactions.isEmpty() || m_transactions.isNull() || m_prevBlockSign==0;
    }

    uint prevBlockSignature(){ return m_prevBlockSign;}
    QString transactions(){ return m_transactions; }
    uint signature() const{  return m_signature;}

private:
    uint  m_prevBlockSign;
    QString m_transactions;
    uint m_signature;

    uint hash(uint seed=0){
        if(isEmpty()) return seed;
        else{
            QString data = m_transactions+QString::number(m_prevBlockSign);
            return qHash(data);
        }
    }
};


QList<Block>  generateBlockChain(const QString & genesisData){

    QList<Block>  blockChain;
    Block genesisBlock = Block(1,genesisData);
    Block lastBlock = genesisBlock;
    blockChain.append(genesisBlock);
    for( int index =0; index<100; index++){
        Block block(lastBlock.signature(),QString::number(index)+" bitcoin");
        lastBlock = block;
        blockChain.append(block);
    }
    return blockChain;
}

void printSignature(QList<Block>  & blockChain){
    foreach(Block block,blockChain)
        qDebug()<<block.signature();
}

void printSignature(QList<Block>  & blockChain1 ,QList<Block>  & blockChain2 ){

    if(blockChain1.size()!=blockChain2.size())return;
    for( int index =0 ;index<blockChain1.size() ; index++){
         qDebug()<<"old sign "<<blockChain1.at(index).signature()
                <<" new sign "<<blockChain2.at(index).signature();
    }

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<Block>  blockChain1 = generateBlockChain("Ramesh sent 100 bitcoin");
    QList<Block>  blockChain2 = generateBlockChain("Ramesh sent 101 bitcoin");
    printSignature(blockChain1,blockChain2);
    return a.exec();
}
