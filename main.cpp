#include <iostream>
#include <fstream>
#define MAX 107
#define NOT_CONNECTED -1



int distance[MAX][MAX];
int distance2[MAX][MAX];

int nodesCount;

//initialize all distances to
void Initialize1(){
    for (int i=0;i<MAX;++i){
        for (int j=0;j<MAX;++j){
            distance[i][j]=NOT_CONNECTED;
        }
        distance[i][i]=0;
    }
}


struct matr{
    int a;
    int b;
    int c;
};

void Initialize2(){
    for (int i=0;i<MAX;++i){
        for (int j=0;j<MAX;++j){

            distance2[i][j]=NOT_CONNECTED;

        }
        distance2[i][i]=0;
    }
}

int main(){
    Initialize1();
    scanf("%d", &nodesCount);
    int m;
    scanf("%d", &m);
    matr* matrix = new matr[m];
    int d = m;
    int i =0;
    while(m!=0){
        std::cin>>matrix[i].a;
        std::cin>>matrix[i].b;
        std::cin>>matrix[i].c;
        distance[matrix[i].a][matrix[i].b]=matrix[i].c;
        i++;
        m=m-1;
    }

           std::cout << "Матрица смежности: " <<  std::endl;
           for(int i=1;i<=nodesCount;i++)
           {
               for(int j=1;j<=nodesCount;j++)
               {
                   std::cout << distance[i][j]<< " ";
               }
               std::cout <<  std::endl;
           }

    std::ofstream out("matr.txt", std::ios::binary );
        out.write((char*)&matrix,sizeof(matr));
        out.close();

    matr* matrix2= new matr[d];
    std::ifstream in("matr.txt", std::ios::binary);
    in.read((char*)&matrix2,sizeof(matr));
        in.close();
    
    i=0;
    Initialize2();
    while(d!=0){
        distance2[matrix2[i].a][matrix2[i].b]=matrix2[i].c;
        i++;
        d=d-1;
    }
    
    std::cout << "Матрица смежности из файла: " <<  std::endl;
    for(int i=1;i<=nodesCount;i++)
    {
        for(int j=1;j<=nodesCount;j++)
        {
            std::cout << distance2[i][j]<< " ";
        }
        std::cout <<  std::endl;
    }

//    Floyd-Warshall
    for (int k=1;k<=nodesCount;++k){
        for (int i=1;i<=nodesCount;++i){
            if (distance2[i][k]!=NOT_CONNECTED){
                for (int j=1;j<=nodesCount;++j){
                    if (distance2[k][j]!=NOT_CONNECTED && (distance2[i][j]==NOT_CONNECTED || distance2[i][k]+distance2[k][j]<distance2[i][j])){
                        distance2[i][j]=distance2[i][k]+distance2[k][j];
                    }
                }
            }
        }
    }
    

    int diameter=-1;
    std::cout <<  std::endl;
    for (int i=1;i<=nodesCount;++i){
        for (int j=1;j<=nodesCount;++j){
            if (diameter<distance2[i][j]){
                diameter=distance2[i][j];
                printf("%d %d\n", i, j);
            }
        }
    }

    std::cout<<"Diametr : ";
    printf("%d\n", diameter);

    
    return 0;
}




