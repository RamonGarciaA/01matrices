#include <iostream>

using namespace std;

//I had to make some global constants for the code to be able to work. I just did this because I had
//memory allocation issues since the code is suboptimal


//const int n=4;
//const int n=5;
//const int n=6;
//const int n=7;
const int n=8;
//const int n=9;


//k is the value of 2*n-4 choose n-2
//const int k=6;
//const int k=20;
//const int k=70;
//const int k=280;
const int k=924;
//const int k=1716;


//Value of n!
//const int fact=24;
//const int fact=120;
//const int fact=720;
//const int fact=5040;
const int fact=40320;
//const int fact=9*40320;


//I declare these arrays as global variables in order to get more memory for them
bool A[n][n];
int sigma[fact][n];
int tau[fact][n];
bool updown[k][2*n-4];




//function that prints square n by n boolean matrix
void printMatrix(bool A[n][n]){
   for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout<<A[i][j]<<" ";
        cout<<endl;
    }
}



//function that fills the matrix with 0's
void fillmatrix(bool A[n][n]){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            A[i][j]=0;
}

//function that calculates 2^m
int power2(int m){
    if(m==0){
        return 1;
    }
    return power2(m-1)*2;
}




//function that calculates the permanent
int Permanent(bool A[n][n], int tau[fact][n]){
int permanent=0;
int temporal=1;
for(int i=0; i<fact; i++){
    temporal=1;
    for(int j=0; j<n; j++){
        temporal=temporal*int(A[j][tau[i][j]]);
    }
    permanent=permanent+temporal;
}
return permanent;
}


int ShowPermanent(bool A[n][n], int tau[fact][n]){
int permanent=0;
int temporal=1;
for(int i=0; i<fact; i++){
    temporal=1;
    for(int j=0; j<n; j++){
        temporal=temporal*int(A[j][tau[i][j]]);
    }
    if(temporal>0){
        for(int j=0; j<n; j++)
            cout<<tau[i][j]<<" ";
        cout<<endl;
    }
    permanent=permanent+temporal;
}
return permanent;
}

//self explanaory
int factorial(int m){
    if(m==0){
        return 1;
    }
    return factorial(m-1)*m;
}

int binomial(int m, int k){
    if (k>m){
        return 0;
    }
return factorial(m)/(factorial(k)*factorial(m-k));
}



int main()
{
    bool binary[power2(2*n-4)][2*n-4];
    int aux=0;
    int a=0;
    int x=0;
    int indicator=0;
    int counter=0;
    int maximum=1;



for(int i=0; i<power2(2*n-4); i++){
    for(int j=0; j<2*n-4; j++){
        binary[i][j]=0;
    }
}




//this section of the code fills all the possible 2^(2*n-4) binary strings
aux=0;
for(int i=0; i<power2(2*n-4); i++){
    a=i;
    x=0;
    while(a>0){
        binary[aux][x]=a%2;
        a=a/2;
        x+=1;
    }
    aux=aux+1;
}

//this section fills tau with 0's
for(int i=0; i<fact; i++){
    for(int j=0; j<n; j++){
        tau[i][j]=-1;
        sigma[i][j]=0;
    }
}

//this section of the code fills all the 2*n-4 choose n-2 possible 0-1 vectors for the zig zags
aux=0;
for(int i=0; i<power2(2*n-4); i++){
    a=0;
    for(int j=0; j<2*n-4; j++){
        a=a+binary[i][j];
    }
    if(a==(n-2)){
        for(int j=0; j<2*n-4; j++){
            updown[aux][j]=binary[i][j];
        }
        aux+=1;
    }
}


//this section of the code fills all the permutation vectors
aux=0;
for(int i=0; i<factorial(n); i++){
        aux=i;
        for(int j=0; j<n; j++){
            sigma[i][j]=aux/factorial(n-j-1);
            //cout<<sigma[i][j]<<" ";
            aux=aux%factorial(n-j-1);
        }
       //cout<<endl;
}
//cout<<endl<<endl;


//this section does the translation to permutation vectors
for(int i=0; i<factorial(n); i++){
    for(int j=0; j<n;j++){
        aux=0;
        a=0;
        while(aux<sigma[i][j]+1){
            if(tau[i][a]==-1){
                aux+=1;
            }
            a+=1;
        }
        tau[i][a-1]=j;
    }

}
//printing to check everything is fine
/*for(int i=0; i<fact; i++){
    for(int j=0; j<n; j++){
        cout<<tau[i][j]<<" ";
    }
    cout<<endl;
}*/

//This section prints all the zigzag paths
cout<<endl;
counter=0;
fillmatrix(A);
for(int i=0; i<k; i++){
    for(int z=0; z<i+1; z++){
        indicator=0;
        aux=n-1;
        a=1;

        A[0][n-1]=1;
        A[1][n-1]=1;
        A[n-1][0]=1;
        A[n-1][1]=1;
        for(int j=0; j<2*n-4;j++){
                if(updown[i][j]==1){
                    aux=aux-1;
                    A[aux][a]=1;
                }
                if(updown[i][j]==0){
                    a+=1;
                    A[aux][a]=1;
                }
        }
        A[0][n-2]=1;
        A[n-2][0]=1;
        aux=n-2;
        a=0;
        for(int j=0; j<2*n-5; j++){
            if(updown[z][j]==1){
                    a+=1;
                    if(A[aux][a]==1)
                        indicator=1;
                    A[aux][a]=1;
                }
            if(updown[z][j]==0){
                    aux=aux-1;
                    if(A[aux][a]==1)
                        indicator=1;
                    A[aux][a]=1;
                }
        }
        if(indicator==0){
            if(Permanent(A,tau)>=maximum){
                printMatrix(A);
                maximum=Permanent(A,tau);
                cout<<endl<<"Permanent: "<<maximum<<endl;
                if(n<=5){
                    ShowPermanent(A,tau);
                }
            }
        }

 //       cout<<endl<<indicator<<endl;
        fillmatrix(A);
    }
}




    return 0;


}


